/*! \file
	Description: Generic Inline Tag Replacement
	
	Copyright Notice:

	Copyright (C) 1990-2015, International Business Machines
	Corporation and others. All rights reserved
*/


#define INCL_EQF_TP               // public translation processor functions
#define INCL_EQF_EDITORAPI        // editor API
#define INCL_EQF_TAGTABLE         // tagtable defines and functions
#define INCL_EQF_ANALYSIS         // analysis functions
#define INCL_EQF_TM               // general Transl. Memory functions
#define INCL_EQF_TMREMOTE         // remote Transl. Memory functions (U-Code)
#define INCL_EQF_DLGUTILS         // dialog utilities
#define INCL_EQF_MORPH
#define INCL_EQF_DAM
#include <EQF.H>                  // General Translation Manager include file

#define INCL_EQFMEM_DLGIDAS
#include <tm.h>               // Private header file of Translation Memory
#include <EQFTPI.H>               // Private header file of Standard Editor
#include <EQFMORPI.H>
#include <EQFEVENT.H>             // event logging
#include "../utilities/LogWrapper.h"

static VOID
MakeHashValueW
(
  PULONG    pulRandom,                 // array of random numbers for hashing
  USHORT    usMaxRandom,               // maximum random numbers
  PSZ_W     pData,                     // ptr to data to be hashed
  PULONG    pulHashVal                 // resulting hash value
);


static
BOOL NTMPrepareTokens
(
  PTMX_SUBSTPROP       pSubstProp,
  PSZ_W                pData,
  PFUZZYTOK           *ppTokData,
  PUSHORT              pusTokens,
  PTMX_TAGTABLE_RECORD pTagRecord,
  SHORT                sLangID,
  ULONG                ulOemCP
);

static BOOL
NTMFuzzyReplace
(
  PTMX_SUBSTPROP pSubstProp,
  PSZ_W     pSource,                   // source string
  PSZ_W     pProp,                     // proposal string
  PSZ_W     pTrans,                    // translation string
  PREPLLIST pReplPropSrc,              // list of same tokens in source and prop
  PREPLLIST pReplaceList               // list of tokens to be replaced
);

#ifdef ACTIVATE_NTMGenericDelete 
static BOOL
NTMGenericDelete
(
  PTMX_SUBSTPROP pSubstProp,
  PSZ       pSource,                   // source string
  PSZ       pProp,                     // proposal string
  PSZ       pTrans,                    // translation string
  PREPLLIST pReplPropSrc,              // list of same tokens in source and prop
  PREPLLIST pReplaceList               // list of tokens to be replaced
);
#endif


static BOOL NTMCheckTagPairs
(
  PTMX_SUBSTPROP pSubstProp,
  PREPLLIST pReplPropSrc,              // list of same tokens in source and prop
  PREPLLIST pReplaceList,              // list of tokens to be replaced
  BOOL      fRespectLFs
);


static PTMX_REPLTAGPAIR
NTMFindTagPair
(
  PFUZZYTOK         pTempTok,
  PSZ_W             pTempTokData,
  PTMX_SUBSTPROP    pSubstProp,
  PTMX_REPLTAGPAIR  pCurTagPair,
  BOOL              fRespectLFs
);


static BOOL
NTMReplaceTags
(
  PTMX_SUBSTPROP pSubstProp,
  BOOL           fRespectLFs
);

static BOOL
NTMCopyTokData
(
   PSZ_W      pTempData,
   SHORT      sLen,
   PSZ_W *    ppNewData,
   PLONG      plNewLen
);


static PFUZZYTOK
NTMSplitAndAddTokens ( PTMX_SUBSTPROP,
                       PFUZZYTOK, PUSHORT, USHORT, SHORT,
                       USHORT, PSZ_W, SHORT, ULONG);

BOOL NTMAlignTags( PFUZZYTOK pTokSource, PFUZZYTOK pTokTarget, PREPLLIST *ppReplaceList );

// helper function for token logging
#ifdef INLINE_TAG_REPL_LOGGING

void NTMListToken
( 
  PSZ          pszToken,
  PFUZZYTOK    pToken 
)
{
  std::string type;
  int len = pToken->usStop - pToken->usStart + 1;
  CHAR_W chTemp = pToken->pData[len];
  pToken->pData[len] = 0;
  if ( pToken->sType == -1 )
  {
    type = "Text";
  }
  else if ( pToken->sType == -7 )
  {
    type = "Tag";
  }
  else 
  {
    type = std::to_string( pToken->sType );    
  } /* endif */
  T5LOG(T5INFO) << pszToken <<" : Hash="<<pToken->ulHash<<"  Length="<< len<<"  Type="<<type<<" Connected="<<pToken->fConnected<<" Data=\"" << pToken->pData << "\"";
  pToken->pData[len] = chTemp;
} /* end of function NTMListToken */

void NTMListTokens
(  
  PSZ          pszName,
  PFUZZYTOK    pToken 
)
{
  int i = 1;
  T5LOG(T5INFO) << "\n"<<pszName <<" token list\n"; 
  while ( pToken->ulHash )
  {
    std::string tokenName = "Token " + i;
    NTMListToken( (char*) tokenName.c_str() , pToken ); 
    pToken++; i++;
  } /*endwhile */
} /* end of function NTMListTokens */

#endif


#ifdef INLINE_TAG_REPL_LOGGING
void NTMMarkCRLF( PSZ_W pszSource, PSZ_W pszTarget );
#endif

//+----------------------------------------------------------------------------+
//|External function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMTagSubst                                              |
//+----------------------------------------------------------------------------+
//|Function call:     NTMTagSubst( pSubstProp );                               |
//+----------------------------------------------------------------------------+
//|Description:       GENERIC TM: substitute tags if substitution of all       |
//|                   is possible                                              |
//+----------------------------------------------------------------------------+
//|Parameters:        PTMX_SUBSTPROP pSubstProp ptr to substitution struct     |
//+----------------------------------------------------------------------------+
//|Returncode type:   USHORT                                                   |
//+----------------------------------------------------------------------------+
//|Returncodes:       1 all tagging in proposal replaced                       |
//|                   0        nothing replaced                                |
//+----------------------------------------------------------------------------+
//|Function flow:     Prepare a token list for current src, src of prop and    |
//|                      tgt of prop                                           |
//|                   call LCS for data pair src - src of prop                 |
//|                   call LCS for data pair src of prop - tgt of prop         |
//|                   determine which tags can be replaced                     |
//|                   if so,                                                   |
//|                     if all tags can be replaced                            |
//|                       replace them                                         |
//+----------------------------------------------------------------------------+
BOOL     NTMTagSubst
(
  PTMX_SUBSTPROP pSubstProp,
  ULONG          ulSrcOemCP,
  ULONG          ulTgtOemCP
)
{
  BOOL      fOK;
  PREPLLIST pReplaceList       = NULL;
  PREPLLIST pReplaceSourceList = NULL;
  PFUZZYTOK pCopyTokList1      = NULL;
  PFUZZYTOK pCopyTokList2      = NULL;
  PFUZZYTOK pTempList;
  PBYTE     pTokBuf = NULL;
  USHORT    k;                            //index variable
  BOOL      fConnected;                          // temp variable for connection state
  BOOL      fReplaced = FALSE;
  BOOL      fDelete   = FALSE;
  SHORT     sSrcLangID = 0;
  SHORT     sTgtLangID = 0;
  PSZ_W     pInBuf;
#ifdef INLINE_TAG_REPL_LOGGING
  static CHAR_W szSegBuf[4096];
#endif

  // ignore LFs in inline tagging only for IBMDITA markup
  BOOL       fRespectLFs = (_stricmp( pSubstProp->szSourceTagTable, "IBMDITA" ) != 0);

  UtlAlloc((PVOID *) &pInBuf, 0L, (LONG) IO_BUFFER_SIZE * sizeof(CHAR_W), ERROR_STORAGE );
  UtlAlloc((PVOID *) &pTokBuf, 0L, (LONG) TOK_BUFFER_SIZE, ERROR_STORAGE );
  fOK = ( pInBuf && pTokBuf ) ;

#ifdef INLINE_TAG_REPL_LOGGING
  if ( T5Logger::GetInstance()->CheckLogLevel(T5DEBUG) )
  {
    T5LOG(T5DEBUG) << "*** NTMTagSubst ***\n" ;
    NTMMarkCRLF( pSubstProp->szSource, szSegBuf );
    T5LOG(T5DEBUG) << "<Segment>"<< szSegBuf << "</Segment>\n";
    NTMMarkCRLF( pSubstProp->szPropSource, szSegBuf );
    T5LOG(T5DEBUG) << "<PropSource>"<<szSegBuf<<"</PropSource>\n";
    NTMMarkCRLF( pSubstProp->szPropTarget, szSegBuf );
    T5LOG(T5DEBUG) << "<PropTarget>"<<szSegBuf<<"</PropTarget>\n";
  } /* endif */
  #endif
  

  /******************************************************************/
  /* prepare token structure                                        */
  /******************************************************************/
  if (fOK )
  {
    fOK = (MorphGetLanguageID(pSubstProp->szSourceLanguage, &sSrcLangID )==MORPH_OK);
  } /* endif */

  if (fOK && (MorphGetLanguageID( pSubstProp->szTargetLanguage,
              &sTgtLangID ) != MORPH_OK) )
  {
     sTgtLangID = sSrcLangID ;
  } /* endif */

  if (fOK )
  {
    fOK = NTMPrepareTokens( pSubstProp, pSubstProp->szSource,
                            (PFUZZYTOK *)&pSubstProp->pTokSource,
                            &pSubstProp->usTokenSource,
                            nullptr, //pSubstProp->pTagsSource, 
                            sSrcLangID, ulSrcOemCP );
  #ifdef INLINE_TAG_REPL_LOGGING
  if(T5Logger::GetInstance()->CheckLogLevel(T5DEBUG))
    if ( fOK ) NTMListTokens(  "Source", (PFUZZYTOK)pSubstProp->pTokSource );
  #endif

  } /* endif */

  if ( fOK )
  {
    fOK = NTMPrepareTokens( pSubstProp, pSubstProp->szPropSource,
                            (PFUZZYTOK *)&pSubstProp->pTokPropSource,
                            &pSubstProp->usTokenPropSource,
                            nullptr, //pSubstProp->pTagsPropSource, 
                            sSrcLangID, ulSrcOemCP );
#ifdef INLINE_TAG_REPL_LOGGING
    if ( fOK ) NTMListTokens( "PropSource", (PFUZZYTOK)pSubstProp->pTokPropSource );
#endif
  } /* endif */

  if ( fOK )
  { // P018276: use TgtOemCP!! (must fit to sTgtLangID)
    fOK = NTMPrepareTokens( pSubstProp, pSubstProp->szPropTarget,
                            (PFUZZYTOK *)&pSubstProp->pTokPropTarget,
                            &pSubstProp->usTokenPropTarget,
                            nullptr,//pSubstProp->pTagsPropTarget, 
                            sTgtLangID, ulTgtOemCP );
#ifdef INLINE_TAG_REPL_LOGGING
    if ( fOK ) NTMListTokens( "PropTarget", (PFUZZYTOK)pSubstProp->pTokPropTarget );
#endif
  } /* endif */

  if ( fOK )
  {
    /******************************************************************/
    /* temporary store values                                         */
    /******************************************************************/
    UtlAlloc( (PVOID *) &pCopyTokList1, 0L, (LONG)(pSubstProp->usTokenPropSource+1)*sizeof(FUZZYTOK), NOMSG );
    UtlAlloc( (PVOID *) &pCopyTokList2, 0L, (LONG)(pSubstProp->usTokenPropTarget+1)*sizeof(FUZZYTOK), NOMSG );
    fOK = ( pCopyTokList1 && pCopyTokList2 );
  } /* endif */


  if ( fOK )
  {
    memcpy( pCopyTokList1, pSubstProp->pTokPropSource, pSubstProp->usTokenPropSource * sizeof(FUZZYTOK));
    memcpy( pCopyTokList2, pSubstProp->pTokPropTarget, pSubstProp->usTokenPropTarget * sizeof(FUZZYTOK));

    /******************************************************************/
    /* now do the alignments....                                      */
    /******************************************************************/
//#define USEOLDALIGN

#ifdef USEOLDALIGN
    fOK = (BOOL)FuzzyLCSReplList( (PFUZZYTOK)pSubstProp->pTokPropSource, (PFUZZYTOK)pSubstProp->pTokPropTarget, &pReplaceList,
                                  pSubstProp->usTokenPropSource, pSubstProp->usTokenPropTarget, NULL, TRUE );
#else
    fOK = NTMAlignTags( (PFUZZYTOK)pSubstProp->pTokPropSource, (PFUZZYTOK)pSubstProp->pTokPropTarget, &pReplaceList );
#endif
    /******************************************************************/
    /* restore original content, but keep fConnected...               */
    /* The original content is modified in the FuzzyLCSReplList func. */
    /******************************************************************/
    pTempList = (PFUZZYTOK) pSubstProp->pTokPropSource;
    for ( k=0; k < pSubstProp->usTokenPropSource+1; k++ )
    {
      fConnected            = pTempList->fConnected;
      *pTempList            = *(pCopyTokList1+k);
      pTempList->fConnected = (EQF_BOOL)fConnected;
      pTempList++;
    } /* endfor */

    pTempList = (PFUZZYTOK) pSubstProp->pTokPropTarget;
    for ( k=0; k < pSubstProp->usTokenPropTarget+1; k++ )
    {
      fConnected            = pTempList->fConnected;
      *pTempList            = *(pCopyTokList2+k);
      pTempList->fConnected = (EQF_BOOL)fConnected;
      pTempList++;
    } /* endfor */
  #ifdef INLINE_TAG_REPL_LOGGING
      NTMListTokens( "Connected PropSource", (PFUZZYTOK)pSubstProp->pTokPropSource );
      NTMListTokens( "Connected PropTarget", (PFUZZYTOK)pSubstProp->pTokPropTarget );
  #endif

    /******************************************************************/
    /* free CopyTokList2                                              */
    /******************************************************************/
    UtlAlloc( (PVOID*)&pCopyTokList2, 0L, 0L, NOMSG);
  } /* endif */

  if ( fOK && pReplaceList )
  {
    /******************************************************************/
    /* temporary store values                                         */
    /******************************************************************/
    UtlAlloc( (PVOID *) &pCopyTokList2, 0L, (LONG)(pSubstProp->usTokenSource+1)*sizeof(FUZZYTOK), NOMSG );
    fOK = ( pCopyTokList2 != NULL );
  } /* endif */

  if ( fOK && pReplaceList )
  {
    memcpy( pCopyTokList2, pSubstProp->pTokSource, pSubstProp->usTokenSource * sizeof(FUZZYTOK));
    fOK = (BOOL)FuzzyLCSReplList( (PFUZZYTOK)pSubstProp->pTokPropSource,
                                  (PFUZZYTOK)pSubstProp->pTokSource,
                                  &pReplaceSourceList,
                                  pSubstProp->usTokenPropSource,
                                  pSubstProp->usTokenSource,
                                  NULL, TRUE );
    //                              #endif
    /******************************************************************/
    /* restore original content, but keep fConnected...               */
    /******************************************************************/
    pTempList = (PFUZZYTOK) pSubstProp->pTokPropSource;
    for ( k=0; k < pSubstProp->usTokenPropSource+1; k++ )
    {
      fConnected            = pTempList->fConnected;
      *pTempList            = *(pCopyTokList1+k);
      pTempList->fConnected = (EQF_BOOL)fConnected;
      pTempList++;
    } /* endfor */

    pTempList = (PFUZZYTOK) pSubstProp->pTokSource;
    for ( k=0; k < pSubstProp->usTokenSource+1; k++ )
    {
      fConnected            = pTempList->fConnected;
      *pTempList            = *(pCopyTokList2+k);
      pTempList->fConnected = (EQF_BOOL)fConnected;
      pTempList++;
    } /* endfor */
  #ifdef INLINE_TAG_REPL_LOGGING
      T5LOG(T5DEBUG) << "after FuzzyLCSReplList on source and proposal source" ;
      NTMListTokens( "Connected Source", (PFUZZYTOK)pSubstProp->pTokSource );
      NTMListTokens(  "Connected PropSource", (PFUZZYTOK)pSubstProp->pTokPropSource );
  #endif

  } /* endif */

  /********************************************************************/
  /* find out which tags can be replaced by each other                */
  /********************************************************************/
  if ( fOK && pReplaceSourceList )
  {
    T5LOG(T5DEBUG) << "replace source list exists\n" ;

    /*************************************************************/
    /* insert a dummy token at the beginning of the pReplaceSourcList */
    /* list to have an anchor where to start from...             */
    /*************************************************************/
    memmove( pReplaceSourceList+1, pReplaceSourceList, sizeof( REPLLIST ) * MAX_REPL);

    pReplaceSourceList->pSrcTok = (PFUZZYTOK)pSubstProp->pTokPropSource;
    pReplaceSourceList->pTgtTok = (PFUZZYTOK)pSubstProp->pTokSource;

    fReplaced = NTMFuzzyReplace ( pSubstProp, pSubstProp->szSource,
                                  pSubstProp->szPropSource,
                                  pSubstProp->szPropTarget,
                                  pReplaceSourceList, pReplaceList
                                  );

     T5LOG(T5DEBUG) << "After NTMFuzzyReplace: fReplaced = " <<  fReplaced  ;

#ifdef ACTIVATE_NTMGenericDelete 
  fDelete    = NTMGenericDelete ( pSubstProp, pSubstProp->szSource,
                                pSubstProp->szPropSource,
                                pSubstProp->szPropTarget,
                                pReplaceSourceList, pReplaceList );
#endif

    if (fReplaced || fDelete)
    {
      /****************************************************************/
      /* check whether all tags can be replaced                       */
      /****************************************************************/

      if (NTMCheckTagPairs(pSubstProp, pReplaceSourceList, pReplaceList, fRespectLFs ))
      {
        /**************************************************************/
        /* replace all tags possible                                  */
        /**************************************************************/
        fReplaced = NTMReplaceTags(pSubstProp, fRespectLFs );
        #ifdef INLINE_TAG_REPL_LOGGING
        if ( T5Logger::GetInstance()->CheckLogLevel(T5DEBUG)) 
        {
          T5LOG(T5DEBUG) << "After NTMReplaceTags: fReplaced = " << ( ( fReplaced ) ? "True" : "False" );
          if ( fReplaced )
          {
            NTMMarkCRLF( pSubstProp->szPropSource, szSegBuf );
            T5LOG(T5DEBUG) << "<New PropSource>"<<szSegBuf<<"</PropSource>\n";
            NTMMarkCRLF( pSubstProp->szPropTarget, szSegBuf );
            T5LOG(T5DEBUG) << "<New PropTarget>"<<szSegBuf<<"</PropTarget>\n";
          } /* endif */
        }
        #endif
      }
      else
      {
        fReplaced = FALSE;
        T5LOG(T5DEBUG) << "After NTMCheckTagPairs: fReplaced = " <<  fReplaced  ;

      } /* endif */
    } /* endif */
  } /* endif */

  // add tagging function of generic inline tag replacement
  if ( fOK && !fReplaced )
  {
    BOOL fAddTags = TRUE;
    PSZ_W pSegmentEndTags = NULL;         // ptr to segment end tagging
    PSZ_W pSegmentText = NULL;            // ptr to segment text portion

    #define TOKEN_TYPE_TAG  -7
    #define TOKEN_TYPE_TEXT -1

    // 1. check that proposal does not have any inline tagging
    if ( fAddTags )
    {
        PFUZZYTOK pToken = (PFUZZYTOK)pSubstProp->pTokPropSource; 
        while ( pToken->ulHash )
        {
          if ( pToken->sType != TOKEN_TYPE_TEXT )
          {
            fAddTags = FALSE;
          } /* endif */
          pToken++;
        } /*endwhile */
    } /* endif */

    // 2. check that source has tagging only at the beginning and at the end of the segment
    if ( fAddTags )
    {
        PFUZZYTOK pToken = (PFUZZYTOK)pSubstProp->pTokSource; 

        // handle tags at segment start
        if ( pToken->sType == TOKEN_TYPE_TAG )
        {
          while ( pToken->ulHash && (pToken->sType == TOKEN_TYPE_TAG) )
          {
            pToken++;
          } /*endwhile */
        }
        else
        {
          // no tags at segment start
          fAddTags = FALSE;
        } /* endif */

        // handle text part of segment
        if ( pToken->ulHash &&(pToken->sType == TOKEN_TYPE_TEXT) )
        {
          pSegmentText = pToken->pData;         // remember start of text portion

          while ( pToken->ulHash && (pToken->sType == TOKEN_TYPE_TEXT) )
          {
            pToken++;
          } /*endwhile */
        }
        else
        {
          // no text portion following tags
          fAddTags = FALSE;
        } /* endif */

        // handle tags at segment end
        if ( pToken->ulHash &&(pToken->sType == TOKEN_TYPE_TAG) )
        {
          pSegmentEndTags = pToken->pData;         // remember start of tagging at segment end

          while ( pToken->ulHash && (pToken->sType == TOKEN_TYPE_TAG) )
          {
            pToken++;
          } /*endwhile */

          if ( pToken->ulHash && (pToken->pData[0] != 0) )
          {
            // somethig is following tagging at segment end
            fAddTags = FALSE;
          } /* endif */
        }
        else
        {
          // no tagging at segment end
          fAddTags = FALSE;
        } /* endif */
    } /* endif */

    // 3. check that proposal text and segment text is identical
    if ( fAddTags )
    {
        PFUZZYTOK    pToken = (PFUZZYTOK)pSubstProp->pTokSource; 
        PFUZZYTOK    pPropToken = (PFUZZYTOK)pSubstProp->pTokPropSource; 
        while ( pToken->ulHash && (pToken->pData[0] != 0) && pPropToken->ulHash && (pPropToken->pData[0] != 0))
        {
          // skip any tags
          while ( (pToken->ulHash && (pToken->pData[0] != 0)) && (pToken->sType == TOKEN_TYPE_TAG) )
          {
            pToken++;
          } /*endwhile */

          if ( !pToken->ulHash || (pToken->pData[0] == 0))
          {
            // end of source segment
            fAddTags = FALSE;
          } 
          else if ( (pToken->sType == TOKEN_TYPE_TEXT) && (pPropToken->sType == TOKEN_TYPE_TEXT ) )
          {
            if ( wcsncmp( pToken->pData, pPropToken->pData, pToken->usStop - pToken->usStart + 1 ) != 0 )
            {
              // text does not match
              fAddTags = FALSE;
            } /* endif */
          }
          else
          {
            // not same number of text tokens
            fAddTags = FALSE;
          } /* endif */

          // next token
          if ( pToken->ulHash ) pToken++;
          if ( pPropToken->ulHash ) pPropToken++;
        } /*endwhile */
    } /* endif */

    // 4. check that source segment tagging is of correct type
    if ( fAddTags )
    {
        PFUZZYTOK    pToken = (PFUZZYTOK)pSubstProp->pTokSource; 

        if ( (pToken->pData[0] != L'<') || (pSegmentEndTags[0] != L'<') || (pSegmentEndTags[1] != L'/') )
        {
          // incorrect type of tagging
          fAddTags = FALSE;
        }
        else
        {
          // test characters of start and end tag 
          PSZ_W pszStartTag = pToken->pData + 1;
          PSZ_W pszEndTag = pSegmentEndTags + 2;
          while ( fAddTags && isalpha(*pszEndTag) )
          //while ( fAddTags && iswalpha(*pszEndTag) )
          {
            if ( *pszStartTag == *pszEndTag )
            {
              pszStartTag++;
              pszEndTag++;
            }
            else
            {
              // tag names do not match
              fAddTags = FALSE;
            } /* endif */
          } /*endwhile */
        } /* endif */
    } /* endif */


    // add the tags when every test succeeded 
    if ( fAddTags )
    {
      PFUZZYTOK pToken = (PFUZZYTOK)pSubstProp->pTokSource; 
      PSZ_W  pStartTag = pToken->pData;
      int iStartTagLen = pSegmentText - pStartTag;
      int iEndTagLen = wcslen( pSegmentEndTags );
      int iSourceTextLen = wcslen(pSubstProp->szPropSource);
      int iTargetTextLen = wcslen(pSubstProp->szPropTarget);

      if ( ( (iStartTagLen + iSourceTextLen + iEndTagLen) < MAX_SEGMENT_SIZE) &&
           ( (iStartTagLen + iTargetTextLen + iEndTagLen) < MAX_SEGMENT_SIZE) )
      {
        // change proposal source
        memmove( pSubstProp->szPropSource + iStartTagLen, pSubstProp->szPropSource, (iSourceTextLen + 1) * sizeof(CHAR_W) );
        memcpy( pSubstProp->szPropSource, pStartTag, iStartTagLen * sizeof(CHAR_W) );
        wcscpy( pSubstProp->szPropSource + wcslen(pSubstProp->szPropSource), pSegmentEndTags );

        // change proposal target
        memmove( pSubstProp->szPropTarget + iStartTagLen, pSubstProp->szPropTarget, (iTargetTextLen+1) * sizeof(CHAR_W) );
        memcpy( pSubstProp->szPropTarget, pStartTag, iStartTagLen * sizeof(CHAR_W) );
        wcscpy( pSubstProp->szPropTarget + wcslen(pSubstProp->szPropTarget), pSegmentEndTags );

        fReplaced = TRUE;
      } /* endif */
    } /* endif */
  } /* endif */

  /********************************************************************/
  /* free allocated resources                                         */
  /********************************************************************/
  if ( pCopyTokList1 )
     UtlAlloc( (PVOID*)&pCopyTokList1, 0L, 0L, NOMSG);
  if ( pCopyTokList2 )
     UtlAlloc( (PVOID*)&pCopyTokList2, 0L, 0L, NOMSG);
  if ( pSubstProp->pTokSource )
     UtlAlloc( (PVOID*)&pSubstProp->pTokSource, 0L, 0L, NOMSG);
  if ( pSubstProp->pTokPropSource )
     UtlAlloc( (PVOID*)&pSubstProp->pTokPropSource, 0L, 0L, NOMSG);
  if ( pSubstProp->pTokPropTarget )
     UtlAlloc( (PVOID*)&pSubstProp->pTokPropTarget, 0L, 0L, NOMSG);
  if (pInBuf )
     UtlAlloc((PVOID *) &pInBuf, 0L, 0L, NOMSG );
  if (pTokBuf )
     UtlAlloc((PVOID *) &pTokBuf, 0L, 0L, NOMSG );
  if (pReplaceList )
    UtlAlloc((PVOID *) &pReplaceList, 0L, 0L, NOMSG);
  if (pReplaceSourceList )
    UtlAlloc((PVOID *) &pReplaceSourceList, 0L, 0L, NOMSG);
  return (fReplaced);

}

//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMPrepareTokens                                         |
//+----------------------------------------------------------------------------+
//|Function call:     BOOL NTMPrepareTokens                                    |
//|                   ( PTMX_SUBSTPROP       pSubstProp,                       |
//|                     PSZ                  pData,                            |
//|                     PFUZZYTOK           *ppTokData,                        |
//|                     PUSHORT              pusToken,                         |
//|                     PTMX_TAGTABLE_RECORD pTagRecord,                       |
//|                      SHORT                sLangID )                        |
//+----------------------------------------------------------------------------+
//|Description:                                                                |
//+----------------------------------------------------------------------------+
//|Parameters:        PTMX_SUBSTPROP       pSubstProp,                         |
//|                   PSZ                  pData,                              |
//|                   PFUZZYTOK           *ppTokData,                          |
//|                   PUSHORT              pusToken,                           |
//|                   PTMX_TAGTABLE_RECORD pTagRecord,                         |
//|                   SHORT                sLangID                             |
//+----------------------------------------------------------------------------+
//|Returncode type:   BOOL                                                     |
//+----------------------------------------------------------------------------+
//|Function flow:                                                              |
//+----------------------------------------------------------------------------+
#define TAG_TOKEN   -7

static
BOOL  isWhiteSpaceW( PSZ_W pData )
{
  PSZ_W pTemp = pData;
  CHAR_W c;
  //while ( ((c = *pTemp)!= NULC) && iswspace( c ) )
  while ( ((c = *pTemp)!= NULC) && isspace( c ) )
  {
    pTemp++;
  } /* endwhile */
  return (*pTemp == EOS);
}


static
BOOL NTMPrepareTokens
(
  PTMX_SUBSTPROP       pSubstProp,
  PSZ_W                pData,
  PFUZZYTOK           *ppTokData,
  PUSHORT              pusToken,
  PTMX_TAGTABLE_RECORD pTagRecord,
  SHORT                sLangID,
  ULONG                ulOemCP
)
{
  BOOL      fOK = TRUE;
  USHORT    usStringPos;
  USHORT    usTagRecordPos;   // in # of bytes

  PSZ_W         pTokBuf  = pSubstProp->chBuffer;
  PFUZZYTOK     pCurrent = (PFUZZYTOK)pTokBuf;
  ULONG         ulCurStop;
  BOOL          fEndReached = FALSE;
  USHORT        usRandomIndex;           // index in random sequence
  PTMX_TAGENTRY pTagEntry = NULL;      //ptr to tag entries in tag table record
  PBYTE         pByte = (PBYTE)pTagRecord;
  USHORT        usMaxToksInBuffer = (sizeof(pSubstProp->chBuffer) /
                                      sizeof(FUZZYTOK)) - 2;


  if ( !pSubstProp->ulRandom[0] )
  {
    /********************************************************************/
    /* random sequences, see e.g. the book of Wirth...                  */
    /********************************************************************/
    pSubstProp->ulRandom[0] = 0xABCDEF01;
    for (usRandomIndex = 1; usRandomIndex < MAX_RANDOM; usRandomIndex++)
    {
        pSubstProp->ulRandom[usRandomIndex] =
                   pSubstProp->ulRandom[usRandomIndex - 1] * 5 + 0xABCDEF01;
    }  /* endfor*/
  } /* endif */

  // usFirstTagEntry is in number of bytes!
  pByte += pTagRecord->usFirstTagEntry;

  //there is tag info so go through all tag entries and add tags to outstring
  pTagEntry = (PTMX_TAGENTRY)pByte;

  //start of for loop
  usStringPos = 0;
  //initial positioning st beginning of first tag entry
  // in # of bytes
  usTagRecordPos = sizeof(TMX_TAGTABLE_RECORD);

  /********************************************************************/
  /* add first entry                                                  */
  /********************************************************************/
  memset( pTokBuf, 0, sizeof( pSubstProp->chBuffer ));

  if ( usTagRecordPos < RECLEN(pTagRecord) )
  {
    if (pTagEntry->usOffset )
    {
      ulCurStop = pTagEntry->usOffset - 1;
      pCurrent = NTMSplitAndAddTokens(pSubstProp, pCurrent,
                                    &usMaxToksInBuffer,
                                    0,
                                    (SHORT)TEXT_TOKEN,
                                    (USHORT)ulCurStop,
                                    pData, sLangID, ulOemCP);
    } /* endif */
  }
  else
  {
    ulCurStop = UTF16strlenCHAR(pData);
    pCurrent = NTMSplitAndAddTokens(pSubstProp, pCurrent,
                                    &usMaxToksInBuffer,
                                    0,
                                    (SHORT)TEXT_TOKEN,
                                    (USHORT)ulCurStop,
                                    pData, sLangID, ulOemCP);
  } /* endif */



  while ( !fEndReached && (usTagRecordPos < RECLEN(pTagRecord) )
             && (usMaxToksInBuffer > 0)  )
  {
    ULONG  ulNewStart;
    /******************************************************************/
    /* fill in tag record                                             */
    /******************************************************************/
    ulNewStart = pTagEntry->usOffset;
    pCurrent = NTMSplitAndAddTokens(pSubstProp, pCurrent,
                              &usMaxToksInBuffer,
                              (USHORT)ulNewStart,
                              (SHORT)TAG_TOKEN,
                              (USHORT) (ulNewStart + pTagEntry->usTagLen-1),
                              pData, sLangID, ulOemCP);

    ulNewStart +=  pTagEntry->usTagLen;

  // pTagEntry->usTagLen is in # of w's, but usTagRecordPos counts bytes
  // also pByte is a byte ptr

    usTagRecordPos += sizeof(TMX_TAGENTRY)
                  + sizeof(CHAR_W) * (pTagEntry->usTagLen);

    pByte += sizeof(TMX_TAGENTRY) + sizeof(CHAR_W) * (pTagEntry->usTagLen);
    pTagEntry = (PTMX_TAGENTRY)pByte;

    if ( usTagRecordPos < RECLEN(pTagRecord) )
    {
      ulCurStop = pTagEntry->usOffset -1;
    }
    else
    {
      ulCurStop  = UTF16strlenCHAR( pData );   // we reached the end
      fEndReached = TRUE;
    } /* endif */
    /******************************************************************/
    /* split text record into word tokens                             */
    /* and fill into pCurrent struct                                  */
    /******************************************************************/
    if (usMaxToksInBuffer > 0 )
    {
      pCurrent = NTMSplitAndAddTokens(pSubstProp, pCurrent,
                                      &usMaxToksInBuffer,
                                      (USHORT)ulNewStart,
                                      (SHORT)TEXT_TOKEN,
                                      (USHORT)ulCurStop,
                                      pData, sLangID, ulOemCP);
    } /* endif */
  } /* endwhile */
  /********************************************************************/
  /* terminate start-stop table                                       */
  /********************************************************************/
  if (usMaxToksInBuffer > 0 )
  {
    memset(pCurrent, 0,sizeof(FUZZYTOK));

    *pusToken = (USHORT)(pCurrent - (PFUZZYTOK) pTokBuf);

    pCurrent++;

    fOK = UtlAlloc( (PVOID *)ppTokData, 0L, (PBYTE)pCurrent - (PBYTE)pTokBuf, NOMSG);
    if ( fOK )
    {
      memcpy( *ppTokData, pTokBuf, ((PBYTE)pCurrent-(PBYTE)pTokBuf));
    } /* endif */
  }
  else
  {
    fOK = FALSE;
    *ppTokData = NULL;
    *pusToken = 0;
  } /* endif */

  /********************************************************************/
  /* clean list of tokens to combine consecutive tags only intercepted*/
  /* by whitespaces returned as TEXT_TOKENS  (KBT0492)                */
  /********************************************************************/
  if ( fOK && (*pusToken > 2) )
  {
    USHORT k = 0;
    USHORT usNum = *pusToken;
    PFUZZYTOK pNew;
    CHAR_W chTemp;
    pNew = pCurrent = (PFUZZYTOK) *ppTokData;

    while ( k <= usNum )
    {
      switch ( pCurrent->sType )
      {
        case TAG_TOKEN:
          if ( k < usNum - 2 )
          {
            PFUZZYTOK pNext = pCurrent+1;
            USHORT    usTextLen = (pNext->usStop - pNext->usStart + 1);
            chTemp = *(pNext->pData + usTextLen);
            *(pNext->pData + usTextLen) = EOS;

            if ( (pNext->sType == TEXT_TOKEN) &&
                 ((pCurrent+2)->sType == TAG_TOKEN) &&
                 isWhiteSpaceW( pNext->pData ) )
            {
              /**********************************************************/
              /* combine tag - whitespace - tag sequence into one token */
              /**********************************************************/
              *(pNext->pData + usTextLen) = chTemp;
              memcpy( pNew, pCurrent, sizeof( FUZZYTOK ));

              pNext = pCurrent + 2;
              usTextLen = (pNext->usStop - pNext->usStart + 1);
              chTemp = *(pNext->pData + usTextLen);
              *(pNext->pData + usTextLen) = EOS;
              MakeHashValueW ( pSubstProp->ulRandom, MAX_RANDOM,
                              pNew->pData, &pNew->ulHash );
              *(pNext->pData + usTextLen) = chTemp;

              pNew->usStop = (pCurrent+2)->usStop;
              pNew++; pCurrent+=3; k+=3;
            }
            else
            {
              /**********************************************************/
              /* no special handling necessary                          */
              /**********************************************************/
              *(pNext->pData + usTextLen) = chTemp;
              memcpy( pNew, pCurrent, sizeof( FUZZYTOK ));
              pNew++; pCurrent++; k++;
            } /* endif */
          }
          else
          {
            /**********************************************************/
            /* no special handling necessary                          */
            /**********************************************************/
            memcpy( pNew, pCurrent, sizeof( FUZZYTOK ));
            pNew++; pCurrent++; k++;
          } /* endif */
          break;
        case TEXT_TOKEN:
        default:
          memcpy( pNew, pCurrent, sizeof( FUZZYTOK ));
          pNew++; pCurrent++; k++;
          break;
      } /* endswitch */
    } /* endwhile */

    /******************************************************************/
    /* adjust length                                                  */
    /******************************************************************/
    *pusToken = (USHORT)( pNew- (PFUZZYTOK) *ppTokData ) -1;

    while (pNew < pCurrent )
    {
      memset(pNew, 0,sizeof(FUZZYTOK));
      pNew++;
    } /* endwhile */
  } /* endif */

  return fOK;
}

static PFUZZYTOK
NTMSplitAndAddTokens
(
  PTMX_SUBSTPROP     pSubstProp,
  PFUZZYTOK          pstCurrent,
  PUSHORT            pusMaxFreeToksInBuffer,
  USHORT             usStart,
  SHORT              sType,
  USHORT             usStop,
  PSZ_W              pString,
  SHORT              sLangID,
  ULONG              ulOemCP
)
{
  CHAR_W        chTemp;
  USHORT        usListSize = 0;
  TERMLENOFFS*  pTermList = NULL;      // ptr to created term list
  TERMLENOFFS*  pActTerm;              // actual term
  PSZ_W         pCurWord;
  USHORT        usCurStart;
  ULONG         ulCurStop;
  USHORT        usRC;

  /********************************************************************/
  /* if token is text token, make one token for each word             */
  /********************************************************************/
  if (*pusMaxFreeToksInBuffer > 0)
  {
    if ( sType == TEXT_TOKEN )
    {
      chTemp = *(pString + (usStop+(USHORT)1));
      *(pString + (usStop+(USHORT)1)) = EOS;
      
      usRC = MorphTokenizeW( sLangID, pString+usStart,
                            &usListSize, &pTermList,
                            MORPH_OFFSLIST, ulOemCP );

      *(pString + (usStop+(USHORT)1)) = chTemp;

      if ( pTermList )
      {
        pActTerm = pTermList;
        if ( pTermList->iLength>0 && (*pusMaxFreeToksInBuffer > 0))
        {
          while ( pActTerm->iLength>0 && (*pusMaxFreeToksInBuffer > 0))
          {
            pCurWord = pString + usStart + pActTerm->iOffset;
            /**********************************************************/
            /* ignore the linefeeds in the matching                   */
            /**********************************************************/
            if ( *pCurWord != LF )
            {
              usCurStart = (USHORT)(usStart + pActTerm->iOffset);
              ulCurStop = usCurStart + pActTerm->iLength - 1;

              pstCurrent->pData = pCurWord;
              pstCurrent->usStart = usCurStart;
              pstCurrent->sType   = sType;
              pstCurrent->usStop  = (USHORT)ulCurStop;
              pstCurrent->fConnected = FALSE;

              chTemp = *(pString + (ulCurStop+(USHORT)1));
              *(pString + (ulCurStop+(USHORT)1)) = EOS;
              MakeHashValueW ( pSubstProp->ulRandom, MAX_RANDOM,
                              pString + usCurStart, &pstCurrent->ulHash );
              *(pString + (ulCurStop+(USHORT)1)) = chTemp;
              pstCurrent++;
              (*pusMaxFreeToksInBuffer)--;
            } /* endif */
            pActTerm++;
          } /* endwhile */
        }
        else
        {
          pstCurrent->pData = pString+usStart;
          pstCurrent->usStart = usStart;
          pstCurrent->sType   = sType;
          pstCurrent->usStop  = usStop;
          pstCurrent->fConnected = FALSE;
          chTemp = *(pString + (usStop+(USHORT)1));
          *(pString + (usStop+(USHORT)1)) = EOS;
          MakeHashValueW ( pSubstProp->ulRandom, MAX_RANDOM,
                          pString + usStart, &pstCurrent->ulHash );
          *(pString + (usStop+(USHORT)1)) = chTemp;
          pstCurrent++;
          (*pusMaxFreeToksInBuffer)--;

        } /* endif */
      } /* endif */
      /****************************************************************/
      /* free allocated resource ...                                  */
      /****************************************************************/
      UtlAlloc( (PVOID *)&pTermList, 0L, 0L, NOMSG );
    }
    else
    {
      pstCurrent->pData = pString+usStart;
      pstCurrent->usStart = usStart;
      pstCurrent->sType   = sType;
      pstCurrent->usStop  = usStop;
      pstCurrent->fConnected = FALSE;
      chTemp = *(pString + (usStop+(USHORT)1));
      *(pString + (usStop+(USHORT)1)) = EOS;
      MakeHashValueW( pSubstProp->ulRandom, MAX_RANDOM,
                      pString+usStart , &pstCurrent->ulHash );
      *(pString + (usStop+(USHORT)1)) = chTemp;
      pstCurrent++;
      (*pusMaxFreeToksInBuffer)--;
    } /* endif */
  } /* endif */
  return (pstCurrent);

}

//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     MakeHashValues                                           |
//+----------------------------------------------------------------------------+
//|Function call:     MakeHashValues( pulRandom, usMaxNum, pszString, pulHash);|
//+----------------------------------------------------------------------------+
//|Description:       build a quasi hash value of the passed string            |
//+----------------------------------------------------------------------------+
//|Parameters:        PULONG    pulRandom,     array of random numbers         |
//|                   USHORT    usMaxRandom,   maximum random numbers          |
//|                   PSZ       pData,         ptr to data to be hashed        |
//|                   PULONG    pulHashVal     resulting hash value            |
//+----------------------------------------------------------------------------+
//|Returncode type:   VOID                                                     |
//+----------------------------------------------------------------------------+
//|Function flow:     go through the passed string and build hashvalue         |
//|                   of all characters up to the specified max value          |
//|                   Characters not in the alphanumeric range are ignored..   |
//|                   (Check in case of DBCS might be necessary...)            |
//+----------------------------------------------------------------------------+
static VOID
MakeHashValueW
(
  PULONG    pulRandom,                 // array of random numbers for hashing
  USHORT    usMaxRandom,               // maximum random numbers
  PSZ_W     pData,                     // ptr to data to be hashed
  PULONG    pulHashVal                 // resulting hash value
)
{
  USHORT usRandomIndex = 0;
  ULONG  ulHashVal = 0;
  CHAR_W c;
  UCHAR  cSingle;

  while ( ((c = *pData++)!= NULC) && (usRandomIndex < usMaxRandom))
  {
  cSingle = (UCHAR) c;
    if ( !isspace( cSingle ) )
    {
      ulHashVal += pulRandom[usRandomIndex++] * c;
    } /* endif */
  } /* endwhile */
  /********************************************************************/
  /* normalize hashvalue, just in case it is 0 and we may look at it  */
  /* as the end of our further processing....                         */
  /********************************************************************/
  if ( ulHashVal == 0L )
  {
    ulHashVal = 1L;
  } /* endif */

  *pulHashVal = ulHashVal;

  return;
} /* end of function MakeHashValue */

//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMFuzzyReplace                                          |
//+----------------------------------------------------------------------------+
//|Function call:     NTMFuzzyReplace( pSource, pProp, pTrans,                 |
//|                                 pReplPropSrc, pReplaceList );              |
//+----------------------------------------------------------------------------+
//|Description:       replace found tokens in translation with original ones   |
//+----------------------------------------------------------------------------+
//|Parameters:        PSZ       pSource,       source string                   |
//|                   PSZ       pProp,         proposal string                 |
//|                   PSZ       pTrans,        translation string              |
//|                   PREPLLIST pReplPropSrc,  list of same tokens in source   |
//|                   PREPLLIST pReplaceList   list of tokens to be replaced   |
//+----------------------------------------------------------------------------+
//|Returncode type:   VOID                                                     |
//+----------------------------------------------------------------------------+
//|Prerequesits:      pTrans is large enough to hold a total segment in length |
//|                   of MAX_SEGMENT size                                      |
//+----------------------------------------------------------------------------+
//|Function flow:     loop thru the list of candidates                         |
//|                     if next proposal token is part of the possible repl.   |
//|                     list, we've found one match.                           |
//|                     We have to compare until the next match between Source |
//|                     and proposal is detected or the end of the list ...    |
//|                      if we found a fuzzy match, we have to replace it now..|
//|                   endwhile                                                 |
//+----------------------------------------------------------------------------+
static BOOL
NTMFuzzyReplace
(
  PTMX_SUBSTPROP pSubstProp,
  PSZ_W     pSource,                   // source string
  PSZ_W     pProp,                     // proposal string
  PSZ_W     pTrans,                    // translation string
  PREPLLIST pReplPropSrc,              // list of same tokens in source and prop
  PREPLLIST pReplaceList               // list of tokens to be replaced
)
{
  PFUZZYTOK  pSrcTok;                  // source token
  PFUZZYTOK  pEndSrcTok;               // search until you detect this token
  PFUZZYTOK  pEndTgtTok;               // search until you detect this token
  PFUZZYTOK  pPropTok;                 // proposal token
  ULONG      ulTgtLen;                 // target length
  PREPLLIST  pTempRepl;                // pointer to temp repl element
  BOOL       fFound;                   // match found
  BOOL       fReplaced = FALSE;        // nothing replaced yet
  BOOL       fFirstInLoop = TRUE;      // sep. handling 1st time
  USHORT     usNumOfPairs = 0;
  BOOL       fOK = TRUE;

  pSource;
  pProp;
  ulTgtLen = UTF16strlenCHAR( pTrans );

  T5LOG(T5DEBUG) << "NTMFuzzyReplace\n" ;
  pSubstProp->pTagPairs = (PTMX_REPLTAGPAIR) (pSubstProp->chBuffer);
  /********************************************************************/
  /* replace found tokens in translation with original ones....       */
  /********************************************************************/
  while ( pReplPropSrc->pSrcTok )
  {
    pSrcTok = pReplPropSrc->pTgtTok;
    pPropTok   = pReplPropSrc->pSrcTok;

#ifdef INLINE_TAG_REPL_LOGGING
      T5LOG(T5DEBUG) << "Testing token";
      NTMListToken( "SourceToken", pReplPropSrc->pSrcTok ); 
      NTMListToken( "TargetToken", pReplPropSrc->pTgtTok ); 
#endif

    /******************************************************************/
    /* if next proposal token is part of the possible replacement list*/
    /* we've found one match ...                                      */
    /* we have to compare until the next match between Source and     */
    /* Proposal is detected or the end of the list ....               */
    /******************************************************************/
    pEndSrcTok = (pReplPropSrc+1)->pTgtTok;
    pEndTgtTok = (pReplPropSrc+1)->pSrcTok;

    if ( !pEndSrcTok )
    {
      pEndSrcTok = pSrcTok;
      while ( pEndSrcTok->ulHash )
      {
        pEndSrcTok++;
      } /* endwhile */
    } /* endif */

    if ( !pEndTgtTok )
    {
      pEndTgtTok = pPropTok;
      while ( pEndTgtTok->ulHash )
      {
        pEndTgtTok++;
      } /* endwhile */
    } /* endif */
    /******************************************************************/
    /* adjustment for 1st time, earlier decreasing may affect         */
    /* pEndSrcTok/pEndTgtTok, if only 1 token in segment              */
    /******************************************************************/
    if ( fFirstInLoop )                                        /* @KIT1171A */
    {                                                          /* @KIT1171A */
      fFirstInLoop = FALSE;                                    /* @KIT1171A */
      pSrcTok--;                                               /* @KIT1171A */
      pPropTok--;                                              /* @KIT1171A */
    } /* endif */                                              /* @KIT1171A */

    while ( ++pSrcTok && ++pPropTok &&
             (pSrcTok < pEndSrcTok ) && (pPropTok < pEndTgtTok) )
    {
      pTempRepl = pReplaceList;
      fFound = FALSE;
      /****************************************************************/
      /* only replace of tagging done here                            */
      /****************************************************************/
      if ((pSrcTok->sType == TAG_TOKEN ) && (pPropTok->sType == TAG_TOKEN))
      {
        while ( pTempRepl->pSrcTok && !fFound )
        {
          if ( pTempRepl->pSrcTok == pPropTok )
          {
            fFound = TRUE;
            pSubstProp->pTagPairs->pSrcTok = (PBYTE)pSrcTok;
            pSubstProp->pTagPairs->pPropTok = (PBYTE)pPropTok;
            pSubstProp->pTagPairs ++;
            usNumOfPairs ++;
          }
          else
          {
            pTempRepl++;
          } /* endif */
        } /* endwhile */
      } /* endif */

    } /* endwhile */
    pReplPropSrc++;                    // point to next one
  } /* endwhile */
  if (usNumOfPairs)
  {
    fReplaced = TRUE;
  //allocate for pairs
    fOK = UtlAlloc( (PVOID *) &(pSubstProp->pTagPairs), 0L,
                    (LONG)((usNumOfPairs+1) * sizeof(TMX_REPLTAGPAIR)), NOMSG );

    if (fOK )
    {
      //copy source string for later compare function
      memcpy( pSubstProp->pTagPairs, pSubstProp->chBuffer,
              (USHORT)( usNumOfPairs * sizeof(TMX_REPLTAGPAIR)));
    } /* endif */
  }
  else
  {
    pSubstProp->pTagPairs = NULL;
  } /* endif */
  return( fReplaced );
} /* end of function NTMFuzzyReplace */

#ifdef ACTIVATE_NTMGenericDelete 

//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMGenericDelete                                         |
//+----------------------------------------------------------------------------+
//|Function call:     NTMGenericDelete( pSource, pProp, pTrans,                |
//|                                 pReplPropSrc, pReplaceList );              |
//+----------------------------------------------------------------------------+
//|Description:       delete tags                                              |
//+----------------------------------------------------------------------------+
//|Parameters:        PSZ       pSource,       source string                   |
//|                   PSZ       pProp,         proposal string                 |
//|                   PSZ       pTrans,        translation string              |
//|                   PREPLLIST pReplPropSrc,  list of same tokens in source   |
//|                   PREPLLIST pReplaceList   list of tokens to be replaced   |
//+----------------------------------------------------------------------------+
//|Returncode type:   VOID                                                     |
//+----------------------------------------------------------------------------+
//|Prerequesits:      pTrans is large enough to hold a total segment in length |
//|                   of MAX_SEGMENT size                                      |
//+----------------------------------------------------------------------------+
//|Function flow:     loop thru the list of candidates                         |
//|                   endwhile                                                 |
//+----------------------------------------------------------------------------+
static BOOL
NTMGenericDelete
(
  PTMX_SUBSTPROP pSubstProp,
  PSZ       pSource,                   // source string
  PSZ       pProp,                     // proposal string
  PSZ       pTrans,                    // translation string
  PREPLLIST pReplaceSource,            // list of same toks in src & srcofprop
  PREPLLIST pReplaceList               // eq. toks in src & tgt of prop
)
{
  PFUZZYTOK  pSrcTok;                  // source token
  PFUZZYTOK  pEndSrcTok;               // search until you detect this token
  PFUZZYTOK  pEndTgtTok;               // search until you detect this token
  PFUZZYTOK  pSrcOfPropTok;            // proposal token
  USHORT     ulTgtLen;                 // target length
  PREPLLIST  pTempRepl;                // pointer to temp repl element
  BOOL       fFound;                   // match found
  BOOL       fReplaced = FALSE;        // nothing replaced yet
  BOOL       fFirstInLoop = TRUE;      // sep. handling 1st time
  USHORT     usNumOfPairs = 0;
  BOOL       fOK = TRUE;

  ulTgtLen = strlen( pTrans );

  pSubstProp->pDelTagPairs = (PTMX_REPLTAGPAIR) (pSubstProp->chBuffer);
  /********************************************************************/
  /* replace found tokens in translation with original ones....       */
  /********************************************************************/
  while ( pReplaceSource->pSrcTok )
  {
    pSrcTok = pReplaceSource->pTgtTok;             // cur source
    pSrcOfPropTok   = pReplaceSource->pSrcTok;          // src of prop

    /******************************************************************/
    /* if next proposal token is part of the possible replacement list*/
    /* we've found one match ...                                      */
    /* we have to compare until the next match between Source and     */
    /* Proposal is detected or the end of the list ....               */
    /******************************************************************/
    pEndSrcTok = (pReplaceSource+1)->pTgtTok;
    pEndTgtTok = (pReplaceSource+1)->pSrcTok;

    if ( !pEndSrcTok )
    {
      pEndSrcTok = pSrcTok;
      while ( pEndSrcTok->ulHash )
      {
        pEndSrcTok++;
      } /* endwhile */
      pEndSrcTok--;
      /*****************************************************************/
      /* force that tags to be deleted at end of proposal are detected */
      /*****************************************************************/
      if (!fFirstInLoop )
      {
        pSrcTok = pEndSrcTok;
        pSrcTok--;
      } /* endif */
    } /* endif */

    if ( !pEndTgtTok )
    {
      pEndTgtTok = pSrcOfPropTok;
      while ( pEndTgtTok->ulHash )
      {
        pEndTgtTok++;
      } /* endwhile */
      pEndTgtTok--;
    } /* endif */
    /******************************************************************/
    /* adjustment for 1st time, earlier decreasing may affect         */
    /* pEndSrcTok/pEndTgtTok, if only 1 token in segment              */
    /******************************************************************/
    if ( fFirstInLoop )
    {
      fFirstInLoop = FALSE;
      pSrcTok = pEndSrcTok;   // force that they are equal
      pSrcTok--;
      pSrcOfPropTok = (PFUZZYTOK) pSubstProp->pTokPropSource;   // nec if tag at begin
      pSrcOfPropTok--;
    } /* endif */

    pSrcTok++;
    fFound = TRUE;

    while ( pSrcTok && ++pSrcOfPropTok
            && (pSrcTok == pEndSrcTok ) && (pSrcOfPropTok < pEndTgtTok)
            && fFound )
    {
      if (pSrcOfPropTok->sType == TAG_TOKEN )
      {
        pTempRepl = pReplaceList;    // eq toks in src&tgt of prop
        fFound = FALSE;
        /****************************************************************/
        /* only delete  of tagging in src/tgt of proposal checked here  */
        /****************************************************************/
        while ( pTempRepl->pSrcTok && !fFound )
        {
          if ( pTempRepl->pSrcTok == pSrcOfPropTok )
          {
            /************************************************************/
            /* tgt of proposal is eq to  src of prop   !!               */
            /************************************************************/
            fFound = TRUE;
            pSubstProp->pDelTagPairs->pSrcTok = (PBYTE)pTempRepl->pTgtTok;
            pSubstProp->pDelTagPairs->pPropTok = (PBYTE)pSrcOfPropTok;

            pSubstProp->pDelTagPairs ++;
            usNumOfPairs ++;
          }
          else
          {
            pTempRepl++;
          } /* endif */
        } /* endwhile */
      } /* endif */

    } /* endwhile */
    pReplaceSource++;                    // point to next one
  } /* endwhile */
  if (usNumOfPairs)
  {
    fReplaced = TRUE;
  //allocate for pairs
    fOK = UtlAlloc( (PVOID *) &(pSubstProp->pDelTagPairs), 0L,
                    (LONG)((usNumOfPairs+1) * sizeof(TMX_REPLTAGPAIR)), NOMSG );

    if (fOK )
    {
      //copy source string for later compare function
      memcpy( pSubstProp->pDelTagPairs, pSubstProp->chBuffer,
              (USHORT)( usNumOfPairs * sizeof(TMX_REPLTAGPAIR)));
    } /* endif */
  }
  else
  {
    pSubstProp->pDelTagPairs = NULL;
  } /* endif */
  return( fReplaced );
} /* end of function NTMGenericDelete */ 
#endif

//reset replace tag pair used flags
static void NTMResetUsedFlag( PTMX_REPLTAGPAIR pCurTagPair ) 
{
  while ( pCurTagPair )
  {
    if ( pCurTagPair->pPropTok )
    {
      pCurTagPair->fUsed = FALSE;
      pCurTagPair++;
    }
    else
    {
      pCurTagPair = NULL;
    } /* endif */
  } /*endwhile */
} /* end of function NTMResetUsedFlag */


//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMCheckTagPairs                                         |
//+----------------------------------------------------------------------------+
//|Function call:     NTMCheckTagPairs(pSubstProp)                             |
//+----------------------------------------------------------------------------+
//|Description:       check whether all tags in src and target of proposal     |
//|                   can be replaced                                          |
//+----------------------------------------------------------------------------+
//|Parameters:        PTMX_SUBSTPROP pSubstProp                                |
//+----------------------------------------------------------------------------+
//|Returncode type:   BOOL                                                     |
//+----------------------------------------------------------------------------+
//|Prerequesits:      -                                                        |
//+----------------------------------------------------------------------------+
//|Function flow:                                                              |
//+----------------------------------------------------------------------------+
static BOOL
NTMCheckTagPairs
(
  PTMX_SUBSTPROP pSubstProp,
  PREPLLIST pReplaceSourceList,         // list of same tokens in source and prop
  PREPLLIST pReplaceList,              // toklist to be replaced in prop src+tgt
  BOOL      fRespectLFs
)
{
  BOOL                fAllReplace = TRUE;
  PTMX_REPLTAGPAIR    pCurTagPair = pSubstProp->pTagPairs;
  PFUZZYTOK           pTempTok;
  USHORT              k;
  PREPLLIST           pReplTest = NULL;
  PREPLLIST           pReplProp = NULL;
  USHORT              usStart= 0;


  /********************************************************************/
  /* tags which are same in both srces and in propsrc-tgt, need not   */
  /* to be replaced. Hence for ease of use change sType to TEXT_TOKEN */
  /********************************************************************/

  pReplTest = pReplaceSourceList;
  pReplTest++;                                 // 1st entry is dummy
  pReplProp = pReplaceList;
  while ( pReplTest->pSrcTok)
  {
    pTempTok = pReplTest->pSrcTok;         // toks of src of prop
    if (pTempTok->sType == TAG_TOKEN )
    {
      usStart = pTempTok->usStart;
      /****************************************************************/
      /* tag in src of prop which is equal to a tag in current src    */
      /****************************************************************/
      while ( pReplProp->pSrcTok &&
             (pReplProp->pSrcTok->usStart <= usStart ))
      {
        if (pReplProp->pSrcTok == pTempTok )
        {
          /************************************************************/
          /* tag equal in all three sentence!!! no replace nec.       */
          /************************************************************/
          pTempTok->sType = TEXT_TOKEN;
          pReplTest->pTgtTok->sType = TEXT_TOKEN;
          pReplProp->pTgtTok->sType = TEXT_TOKEN;
        } /* endif */
        pReplProp++;
      } /* endwhile */

    } /* endif */
    pReplTest++;
  } /* endwhile */

#ifdef INLINE_TAG_REPL_LOGGING
    PREPLLIST           pRepl = pReplaceSourceList;
    T5LOG(T5DEBUG) << "Replace source list" ;
    while ( pRepl->pSrcTok)
    {
      NTMListToken(  "SourceToken", pRepl->pSrcTok );
      NTMListToken(  "TargetToken", pRepl->pTgtTok );
      pRepl++;
    } /*endwhile */

    T5LOG(T5DEBUG) << "Replace list" ;
    pRepl = pReplaceList;
    while ( pRepl->pSrcTok)
    {
      NTMListToken(  "SourceToken", pRepl->pSrcTok );
      NTMListToken(  "TargetToken", pRepl->pTgtTok );
      pRepl++;
    } /*endwhile */
#endif

  /********************************************************************/
  /* check all remaining tags in source of proposal                   */
  /********************************************************************/
  pTempTok = (PFUZZYTOK) pSubstProp->pTokPropSource;
  k = 0;
  NTMResetUsedFlag( pSubstProp->pTagPairs  );
  while ( (k<pSubstProp->usTokenPropSource) && fAllReplace )
  {
    if (pTempTok->sType == TAG_TOKEN )
    {
      pCurTagPair = NTMFindTagPair ( pTempTok,
                                     pSubstProp->szPropSource,
                                     pSubstProp, pSubstProp->pTagPairs, fRespectLFs );

      if (pCurTagPair == NULL )
      {
        pCurTagPair = NTMFindTagPair (pTempTok,
                                      pSubstProp->szPropSource,
                                      pSubstProp, pSubstProp->pDelTagPairs, fRespectLFs );
        if (pCurTagPair == NULL )
        {
          fAllReplace = FALSE;
#ifdef INLINE_TAG_REPL_LOGGING
          
            T5LOG(T5DEBUG) << "No tag pair found for" ;
            NTMListToken( "Temp token", pTempTok );
#endif
        } /* endif */
      }
      else
      {
        if ( pCurTagPair->fUsed )
        {
          // this tag pair has been used already
          fAllReplace = FALSE;
        }
        else
        {
          pCurTagPair->fUsed = TRUE;
        } /* endif */
      } /* endif */
    } /* endif */

    pTempTok++;
    k++;
  } /* endwhile */

  /********************************************************************/
  /* check all tags in target of proposal                             */
  /********************************************************************/
  pTempTok = (PFUZZYTOK) pSubstProp->pTokPropTarget;
  k = 0;
  NTMResetUsedFlag( pSubstProp->pTagPairs );
  while ( (k<pSubstProp->usTokenPropTarget) && fAllReplace )
  {
    if (pTempTok->sType == TAG_TOKEN )
    {
      pCurTagPair = NTMFindTagPair ( pTempTok, pSubstProp->szPropTarget, pSubstProp, pSubstProp->pTagPairs, fRespectLFs );
      if (pCurTagPair == NULL )
      {
        pCurTagPair = NTMFindTagPair (pTempTok, pSubstProp->szPropTarget, pSubstProp, pSubstProp->pDelTagPairs, fRespectLFs );
        if (pCurTagPair == NULL )
        {
#ifdef INLINE_TAG_REPL_LOGGING
          
            T5LOG(T5DEBUG) << "No tag pair found in target\n" ;
            NTMListToken( "Temp token", pTempTok );
#endif
          fAllReplace = FALSE;
        } /* endif */
      }
      else
      {
        if ( pCurTagPair->fUsed )
        {
          // this tag pair has been used already
          fAllReplace = FALSE;
        }
        else
        {
          pCurTagPair->fUsed = TRUE;
        } /* endif */
      } /* endif */
    } /* endif */

    pTempTok++;
    k++;
  } /* endwhile */


  return(fAllReplace);
} /* end of function NTMCheckTagPairs */

//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMReplaceTags                                           |
//+----------------------------------------------------------------------------+
//|Function call:     NTMReplaceTags  (pSubstProp)                             |
//+----------------------------------------------------------------------------+
//|Description:       build up new src and tgt of proposal with replaced       |
//|                   tagging                                                  |
//+----------------------------------------------------------------------------+
//|Parameters:        PTMX_SUBSTPROP pSubstProp                                |
//+----------------------------------------------------------------------------+
//|Returncode type:   BOOL                                                     |
//+----------------------------------------------------------------------------+
//|Function flow:     replace tags in target of proposal                       |
//|                   replace tags in source of proposal                       |
//+----------------------------------------------------------------------------+
static BOOL
NTMReplaceTags
(
  PTMX_SUBSTPROP pSubstProp,
  BOOL              fRespectLFs
)
{
  BOOL                fAllReplace = TRUE;
  PTMX_REPLTAGPAIR    pCurTagPair = pSubstProp->pTagPairs;
  PFUZZYTOK           pTempTok;
  USHORT              k;
  PFUZZYTOK           pCurPairSrcTok;
  SHORT               sLen;
  PSZ_W               pTempData;
  LONG                lNewLen = 0;
  PSZ_W               pNewData;

  /********************************************************************/
  /* replace all tags in target of proposal                           */
  /********************************************************************/
  pTempTok = (PFUZZYTOK) pSubstProp->pTokPropTarget;
  k = 0;
  lNewLen = 0;
  pNewData = pSubstProp->chBuffer;
  NTMResetUsedFlag( pSubstProp->pTagPairs  );
  while ( (k<pSubstProp->usTokenPropTarget) && fAllReplace )
  {
    if (pTempTok->sType == TAG_TOKEN )
    {
      pCurTagPair = NTMFindTagPair ( pTempTok,
                                     pSubstProp->szPropTarget,
                                     pSubstProp, pSubstProp->pTagPairs, fRespectLFs );
      if (pCurTagPair != NULL )
      {
        /****************************************************************/
        /* pTempTok points to a tag token; current pCurTagPair          */
        /* contains tag from current active source segment              */
        /* which replaces tag from TranslationMemory                    */
        /****************************************************************/
        pCurTagPair->fUsed = TRUE;
        pCurPairSrcTok = (PFUZZYTOK) pCurTagPair->pSrcTok;
        pTempData = pSubstProp->szSource + pCurPairSrcTok->usStart;
        sLen = pCurPairSrcTok->usStop - pCurPairSrcTok->usStart +1;
        fAllReplace = NTMCopyTokData ( pTempData, sLen, &pNewData, &lNewLen);

        if (fAllReplace )
        {
          pCurPairSrcTok->fConnected = TRUE;
        } /* endif */

        /****************************************************************/
        /* copy "space" between tagtoken in prop and next tok in prop   */
        /****************************************************************/
        if ((pTempTok + 1)-> ulHash && (pTempTok+1)->usStart )
        {
          if ( (pTempTok->usStop + 1 < (pTempTok+1)->usStart) )
          {
            sLen = (pTempTok+1)->usStart - pTempTok->usStop - 1;
            pTempData = pSubstProp->szPropTarget + pTempTok->usStop+1;
            fAllReplace = NTMCopyTokData ( pTempData, sLen,
                                          &pNewData, &lNewLen);
          } /* endif */
        } /* endif */
      }
      else         // check whether tag should be deleted
      {
        pCurTagPair = NTMFindTagPair ( pTempTok,
                                       pSubstProp->szPropTarget,
                                       pSubstProp, pSubstProp->pDelTagPairs, fRespectLFs );
        if (pCurTagPair == NULL )
        {
          fAllReplace = FALSE;
        } /* endif */
      } /*endif */

    }
    else
    {
      /****************************************************************/
      /* pTempTok points to a text token; copy it into target         */
      /****************************************************************/
      pTempData = pSubstProp->szPropTarget + pTempTok->usStart;
      if ((pTempTok + 1)-> ulHash && (pTempTok+1)->usStart )
      {
        if ( (pTempTok->usStop < (pTempTok+1)->usStart) )
        {
          /************************************************************/
          /* adjust so that spaces between words are copied too       */
          /************************************************************/
          pTempTok->usStop = (pTempTok+1)->usStart - 1;
        } /* endif */
      }
      else
      {
        // we are at the end of the token list, ensure that we do not miss any trailing blanks
        pTempTok->usStop = (USHORT)(pTempTok->usStart + wcslen( pTempData ) - 1);
      } /* endif */
      sLen = pTempTok->usStop - pTempTok->usStart +1;
      fAllReplace = NTMCopyTokData ( pTempData, sLen, &pNewData, &lNewLen);
    } /* endif */

    pTempTok++;
    k++;
  } /* endwhile */

  if (fAllReplace )
  {
    *pNewData = EOS;
    lNewLen++;
    UTF16strcpy ( pSubstProp->szPropTarget, pSubstProp->chBuffer);
  } /* endif */

  /********************************************************************/
  /* replace all tags in source of proposal                           */
  /* build new string in chBuffer and copy it at the end in szPropSource*/
  /********************************************************************/
  pTempTok = (PFUZZYTOK) pSubstProp->pTokPropSource;
  k = 0;
  pNewData = pSubstProp->chBuffer;
  lNewLen = 0;
  NTMResetUsedFlag( pSubstProp->pTagPairs  );
  while ( (k<pSubstProp->usTokenPropSource) && fAllReplace )
  {
    if (pTempTok->sType == TAG_TOKEN )
    {
      pCurTagPair = NTMFindTagPair ( pTempTok,
                                     pSubstProp->szPropSource,
                                     pSubstProp, pSubstProp->pTagPairs, fRespectLFs );
      if (pCurTagPair != NULL )
      {
        /****************************************************************/
        /* pTempTok points to a tag token; current pCurTagPair          */
        /* contains tag from current active source segment              */
        /* which replaces tag from TranslationMemory                    */
        /****************************************************************/
        pCurTagPair->fUsed = TRUE;
        pCurPairSrcTok = (PFUZZYTOK) pCurTagPair->pSrcTok;
        pTempData = pSubstProp->szSource + pCurPairSrcTok->usStart;
        sLen = pCurPairSrcTok->usStop - pCurPairSrcTok->usStart +1;

        fAllReplace = NTMCopyTokData ( pTempData, sLen, &pNewData, &lNewLen);
        /****************************************************************/
        /* copy "space" between tagtoken in prop and next tok in prop   */
        /****************************************************************/
        if ((pTempTok + 1)-> ulHash && (pTempTok+1)->usStart )
        {
          if ( (pTempTok->usStop + 1 < (pTempTok+1)->usStart) )
          {
            sLen = (pTempTok+1)->usStart - pTempTok->usStop - 1;
            pTempData = pSubstProp->szPropSource + pTempTok->usStop+1;
            fAllReplace = NTMCopyTokData ( pTempData, sLen,
                                          &pNewData, &lNewLen);
          } /* endif */
        } /* endif */
      }
      else
      {
        pCurTagPair = NTMFindTagPair ( pTempTok,
                                       pSubstProp->szPropSource,
                                       pSubstProp, pSubstProp->pDelTagPairs, fRespectLFs );
        if (pCurTagPair == NULL )
        {
          fAllReplace = FALSE;
        } /* endif */
      } /*endif */
    }
    else
    {
      /****************************************************************/
      /* pTempTok points to a text token; copy it into target         */
      /****************************************************************/
      pTempData = pSubstProp->szPropSource + pTempTok->usStart;
      if ((pTempTok + 1)-> ulHash && (pTempTok+1)->usStart )
      {
        if ( (pTempTok->usStop < (pTempTok+1)->usStart) )
        {
          /************************************************************/
          /* adjust so that spaces between words are copied too       */
          /************************************************************/
          pTempTok->usStop = (pTempTok+1)->usStart - 1;
        } /* endif */
      }
      else
      {
        // we are at the end of the token list, ensure that we do not miss any trailing blanks
        pTempTok->usStop = (USHORT)(pTempTok->usStart + wcslen( pTempData ) - 1);
      } /* endif */
      sLen = pTempTok->usStop - pTempTok->usStart +1;
      fAllReplace = NTMCopyTokData ( pTempData, sLen, &pNewData, &lNewLen);
    } /* endif */

    pTempTok++;
    k++;
  } /* endwhile */

  if (fAllReplace )
  {
    *pNewData = EOS;
    lNewLen++;
    UTF16strcpy ( pSubstProp->szPropSource, pSubstProp->chBuffer);
    /******************************************************************/
    /* after this strcpy ALL pCurTagPair->pSrcTok and ALL pSrcTok     */
    /* which point on szPropSource are INVALID                        */
    /* Therefore replace in szPropTarget takes place before           */
    /* replace in szPropSource !!!                                    */
    /******************************************************************/
  } /* endif */
  return(fAllReplace);
} /* end of function NTMReplaceTags */

//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMFindTagPair                                           |
//+----------------------------------------------------------------------------+
//|Function call:     NTMFindTagPair  (pSubstProp)                             |
//+----------------------------------------------------------------------------+
//|Description:       find tag pair which has to be replaced by each other     |
//+----------------------------------------------------------------------------+
//|Parameters:        PFUZZYTOK      pTempTok,                                 |
//|                   PSZ            pTempTokData,                             |
//|                   PTMX_SUBSTPROP pSubstProp                                |
//+----------------------------------------------------------------------------+
//|Returncode type:   PTMX_REPLTAGPAIR                                         |
//+----------------------------------------------------------------------------+
//|Function flow:     find tag pair                                            |
//+----------------------------------------------------------------------------+
static PTMX_REPLTAGPAIR
NTMFindTagPair
(
  PFUZZYTOK        pTempTok,
  PSZ_W            pTempTokData,
  PTMX_SUBSTPROP   pSubstProp,
  PTMX_REPLTAGPAIR pCurTagPair,
  BOOL             fRespectLFs

)
{
  PTMX_REPLTAGPAIR  pFoundTagPair = NULL;
  BOOL              fFound = FALSE;
  SHORT             sLen;
  PFUZZYTOK         pCurPairPropTok;
  PSZ_W             pPairData;
  PSZ_W             pTempData;


  pTempData = pTempTokData + pTempTok->usStart;          // prop src or tgt
  sLen = pTempTok->usStop - pTempTok->usStart +1;
  if (pCurTagPair )
  {
    pCurPairPropTok = (PFUZZYTOK) pCurTagPair->pPropTok;   //src of proposal

    while (!fFound && pCurPairPropTok )
    {
      if ( pCurTagPair->fUsed )
      {
        // ignore this entry
      }
      else if (pCurPairPropTok == pTempTok )
      {
        fFound = TRUE;
      }
      else
      {
        pPairData = pSubstProp->szPropSource + pCurPairPropTok->usStart;
        if (sLen == (pCurPairPropTok->usStop -pCurPairPropTok->usStart + 1 ))
        {
          if ( fRespectLFs )
          {
            if ( memcmp( (PBYTE)pTempData,(PBYTE)pPairData, sLen * sizeof(CHAR_W)) == 0)
            {
              fFound = TRUE;
            } /* endif */
          }
          else
          {
            CHAR_W chTemp1 = pTempTokData[pTempTok->usStop+1];
            CHAR_W chTemp2 = pSubstProp->szPropSource[pCurPairPropTok->usStop+1];
            pTempTokData[pTempTok->usStop+1] = 0;  
            pSubstProp->szPropSource[pCurPairPropTok->usStop+1] = 0;

            T5LOG(T5FATAL) << "TEMPORARY_COMMENTED in NTMFindTagPair::UtlCompIgnWhiteSpaceW";
            #ifdef TEMPORARY_COMMENTED
            fFound = (UtlCompIgnWhiteSpaceW( pTempData, pPairData, 0 ) == 0 );
            #endif
            pTempTokData[pTempTok->usStop+1] = chTemp1;  
            pSubstProp->szPropSource[pCurPairPropTok->usStop+1] = chTemp2;
          } /* endif */
        } /* endif */
      } /* endif */
      if (!fFound )
      {
        pCurTagPair++;
        if (pCurTagPair )
        {
          pCurPairPropTok = (PFUZZYTOK)pCurTagPair->pPropTok;
        }
        else
        {
          pCurPairPropTok = NULL;
        } /* endif */
      }
      else
      {
        pFoundTagPair = pCurTagPair;
      } /* endif */
    } /* endwhile */

  } /* endif */
  return(pFoundTagPair);
} /* end of function NTMFindTagPair */


//+----------------------------------------------------------------------------+
//|Internal function                                                           |
//+----------------------------------------------------------------------------+
//|Function name:     NTMCopyTokData                                           |
//+----------------------------------------------------------------------------+
//|Function call:     NTMCopyTokdata  (pSubstProp)                             |
//+----------------------------------------------------------------------------+
//|Description:       copy data into the new buffer                            |
//+----------------------------------------------------------------------------+
//|Parameters:        PSZ    pTempData,                                        |
//|                   SHORT  sLen,                                             |
//|                   PSZ *  ppNewData,                                        |
//|                   PSHORT pulNewLen                                         |
//+----------------------------------------------------------------------------+
//|Returncode type:   PTMX_REPLTAGPAIR                                         |
//+----------------------------------------------------------------------------+
//|Function flow:     copy data                                                |
//+----------------------------------------------------------------------------+
static BOOL
NTMCopyTokData
(
  PSZ_W  pTempData,
  SHORT  sLen,
  PSZ_W *ppNewData,
  PLONG  plNewLen

)
{
  BOOL   fAllReplace = TRUE;
  PSZ_W  pData;

  pData = *ppNewData;

  if (*plNewLen + sLen < MAX_SEGMENT_SIZE )
  {
    memcpy((PBYTE)pData, (PBYTE)pTempData, sLen*sizeof(CHAR_W));
    pData += sLen;
    *ppNewData = pData;
    *(plNewLen) += sLen;
  }
  else
  {
    fAllReplace = FALSE;
  } /*endif */

  return (fAllReplace);
}

typedef struct _NTMGETMATCHLEVELDATA
{
  CHAR             szSegmentTagTable[MAX_EQF_PATH];        // tag table name for segment markup
  CHAR             szProposalTagTable[MAX_EQF_PATH];       // tag table name for proposal markup
  CHAR_W           szSegment[8096];                        // buffer for segment data
  BYTE             bTokenBuffer[40000];                    // buffer for tokenizer in replace match detection
                                                           // this buffer has to hold token entries with a size of 18 bytes each
                                                           // theoratically a segmet could contain 2047 tokens....
  BYTE             bBuffer[40000];                         // general purpose buffer
  CHAR             szLang1[MAX_LANG_LENGTH];               // language buffer 1
  CHAR             szLang2[MAX_LANG_LENGTH];               // language buffer 2
} NTMGETMATCHLEVELDATA, *PNTMGETMATCHLEVELDATA;

// static data of NTMGetMatchLevelData
static char szLastSourceLang[MAX_LANG_LENGTH] = "";
static char szLastTargetLang[MAX_LANG_LENGTH] = "";
static ULONG ulLastSrcOemCP = 0;
static ULONG ulLastTgtOemCP = 0;               





// free tag substitution data area
void NTMFreeSubstProp( PTMX_SUBSTPROP pSubstProp )
{
  if ( pSubstProp )
  {
    if ( pSubstProp->pTokSource )
      UtlAlloc( (PVOID*) &pSubstProp->pTokSource, 0L, 0L, NOMSG );
    if ( pSubstProp->pTokPropSource )
      UtlAlloc( (PVOID*) &pSubstProp->pTokPropSource, 0L, 0L, NOMSG );
    if ( pSubstProp->pTokPropTarget )
      UtlAlloc( (PVOID*) &pSubstProp->pTokPropTarget, 0L, 0L, NOMSG );
    if ( pSubstProp->pTagPairs )
      UtlAlloc( (PVOID*) &pSubstProp->pTagPairs, 0L, 0L, NOMSG );
    if ( pSubstProp->pDelTagPairs )
      UtlAlloc( (PVOID*) &pSubstProp->pDelTagPairs, 0L, 0L, NOMSG );
    UtlAlloc( (PVOID*)&pSubstProp, 0L, 0L, NOMSG);
  } /* endif */
  return;
} /* end of function NTMFreeSubstProp */


// function aligning tags between source and target of a proposal
BOOL NTMAlignTags
( 
  PFUZZYTOK   pTokListSource,                     // list of proposal source token
  PFUZZYTOK   pTokListTarget,                    // list of proposal target token
  PREPLLIST   *ppReplaceList                     // adress of caller's replacement list pointer
)
{
  PREPLLIST    pReplaceList = NULL;              // pointer to replace list
  int          iSourceTags = 0;                  // number of tags in source token list
  PFUZZYTOK    pTokSource = pTokListSource;      // pointer for source token processing
  PFUZZYTOK    pTokTarget = pTokListTarget;      // pointer for target token processing
  BOOL         fOK = TRUE;                       // function return code

  // count number of tags in source of proposal
  while ( pTokSource->ulHash )
  {
    if ( pTokSource->sType == TAG_TOKEN )
    {
      iSourceTags++;
    } /* endif */
    pTokSource++; 
  } /*endwhile */

  // allocate replacement list
  int iSize =  MAX_REPL > iSourceTags?  MAX_REPL : iSourceTags;
  iSize++;
  fOK = UtlAlloc( (PVOID *)ppReplaceList, 0L, iSize * sizeof(REPLLIST), ERROR_STORAGE );
  pReplaceList = *ppReplaceList;

  // look for source tags in proposal target
  if ( fOK )
  {
    PREPLLIST    pReplaceEntry = pReplaceList; 

    pTokSource = pTokListSource;      
    pTokTarget = pTokListTarget;
    while ( pTokSource->ulHash )
    {
      if ( pTokSource->sType == TAG_TOKEN )
      {
        BOOL fFound = FALSE;
        PFUZZYTOK pTargetStart = pTokTarget;
        do
        {
          if ( (pTokTarget->sType == TAG_TOKEN) && (pTokTarget->ulHash == pTokSource->ulHash) && !pTokTarget->fConnected )
          {
            pReplaceEntry->pSrcTok = pTokSource;
            pReplaceEntry->pTgtTok = pTokTarget;
            pTokSource->fConnected = TRUE;
            pTokTarget->fConnected = TRUE;
            pReplaceEntry++;
            fFound = TRUE;
          }
          else
          {
            // try next target token, wrap-around at end of list
            pTokTarget++;
            if ( !pTokTarget->ulHash )
            {
              pTokTarget = pTokListTarget;
            } /* endif */
          } /* endif */
        } while ( !fFound && (pTargetStart != pTokTarget) );  // while not found and not through list
      } /* endif */
      pTokSource++; 
    } /*endwhile */

    pTokTarget = pTokListTarget;
    pReplaceList = NULL;              // pointer to replace list
  } /* endif */

  return( fOK );
} /* end of function NTMAlignTags */
