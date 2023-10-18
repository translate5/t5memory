/*! \file

Description: Implementation of the abstract OtmMemory class


Copyright Notice:

	Copyright (C) 1990-2016, International Business Machines
	Corporation and others. All rights reserved
*/

#define INCL_EQF_TAGTABLE         // tag table and format functions
#define INCL_EQF_TP
#define INCL_EQF_TM
#define INCL_EQF_DAM
//#define INCL_EQF_ANALYSIS         // analysis functions
//#include <eqf.h>                  // General Translation Manager include file

#include "../../core/pluginmanager/PluginManager.h"
#include "../../core/utilities/LogWrapper.h"
#include "../../core/utilities/EncodingHelper.h"
#include "../../core/utilities/PropertyWrapper.H"
#include "../../core/utilities/FilesystemHelper.h"
#include "OtmProposal.h"
#include "EqfMemory.h"

#include <EQFTMI.H>               // Private header file of Translation Memory
#include <EQFQDAMI.H>             // Private header file of QDAM 
#include "EQFRDICS.H"             // remote dictionary functions
#include "LanguageFactory.H"

// activate the folllowing define to activate logging
/*! \brief Prototypes of helper functions */
static int CopyToBuffer( char *pszSource, char *pszBuffer, int iBufSize );
OtmProposal::eProposalType FlagToProposalType( USHORT usTranslationFlag );

EqfMemory::EqfMemory( EqfMemoryPlugin *pPlugin, HTM htmIn, char *pszName )
{

  this->htm = htmIn;
  this->pMemoryPlugin = pPlugin;
  strcpy( this->szName, pszName );
  if ( this->htm != 0 )
  {
    this->pTmClb = (PTMX_CLB)this->htm;
  }
  else
  {
    this->pTmClb = NULL;
  } /* end */     
  this->pTmExtIn = NULL;
  this->pTmExtOut = NULL;
  this->pTmPutIn = NULL;
  this->pTmPutOut = NULL;
  this->pTmGetIn = NULL;
  this->pTmGetOut = NULL;
  this->pvGlobalMemoryOptions = NULL;

}


EqfMemory::~EqfMemory()
{
  if ( this->pTmExtIn != NULL )  delete  this->pTmExtIn ;
  if ( this->pTmExtOut != NULL ) delete  this->pTmExtOut ;
  if ( this->pTmPutIn != NULL )  delete  this->pTmPutIn ;
  if ( this->pTmPutOut != NULL ) delete  this->pTmPutOut ;
  if ( this->pTmGetIn != NULL )  delete  this->pTmGetIn ;
  if ( this->pTmGetOut != NULL ) delete  this->pTmGetOut;


}

/*! \brief Get number of markups used for the proposals in this mmoryProvides a part of the memory in binary format
  	\returns number of markups used by the memory proposals or 0 if no markup information can be provided
*/
int EqfMemory::getNumOfMarkupNames()
{
  if ( this->pTmClb != NULL )
  {
    return( (int)(this->pTmClb->pTagTables->ulMaxEntries) );
  }
  else
  {
    return( 0 );
  } /* end */     
}

/*! \brief Get markup name at position n [n = 0.. GetNumOfMarkupNames()-1]
    \param iPos position of markup table name
    \param pszBuffer pointer to a buffer for the markup table name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
int EqfMemory::getMarkupName
(
  int iPos,
  char *pszBuffer,
  int iSize
)
{
  if ( this->pTmClb != NULL )
  {
    if ( (iPos >= 0) && (iPos < (int)(this->pTmClb->pTagTables->ulMaxEntries)) )
    {
      PTMX_TABLE_ENTRY pEntry = &(this->pTmClb->pTagTables->stTmTableEntry);
      pEntry += iPos;
      return( CopyToBuffer( pEntry->szName, pszBuffer, iSize ) );
    }
    else
    {
      return( 0 );
    } /* end */     
  }
  else
  {
    return( 0 );
  } /* end */     
}

/*! \brief Get source language of the memory
    \param pszBuffer pointer to a buffer for the source language name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to the buffer
*/
int EqfMemory::getSourceLanguage
(
  char *pszBuffer,
  int iSize
)
{
  if ( this->pTmClb != NULL )
  {
    return( CopyToBuffer( pTmClb->stTmSign.szSourceLanguage, pszBuffer, iSize ) );
  }
  else
  {
    return( 0 );
  } /* end */     
}

/*! \brief Get description of the memory
    \param pszBuffer pointer to a buffer for the description
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to the buffer
*/
int EqfMemory::getDescription
(
  char *pszBuffer,
  int iSize
)
{
  if ( this->pTmClb != NULL )
  {
    return( CopyToBuffer( pTmClb->stTmSign.szDescription, pszBuffer, iSize ) );
  }
  else
  {
    return( 0 );
  } /* endif */     
}

/*! \brief Set the description of the memory
  \param pszBuffer pointer to the description text
*/
void EqfMemory::setDescription
(
  char *pszBuffer
)
{
  if ( this->pTmClb != NULL )
  {
    BOOL fOK = TRUE;
    PTMX_SIGN pTmSign = new(TMX_SIGN);

    // get current signature record
    USHORT usSignLen = sizeof(TMX_SIGN);
    USHORT usRc = EQFNTMSign1( this->pTmClb->pstTmBtree, (PCHAR)pTmSign, &usSignLen );
    fOK = (usRc == NO_ERROR);

     // update description field
     if ( fOK )
     {
       strncpy( pTmSign->szDescription, pszBuffer, sizeof(pTmSign->szDescription)-1 );
       pTmSign->szDescription[sizeof(pTmSign->szDescription)-1] = EOS;

       //trigger plugin to set description
       pMemoryPlugin->setDescription(szName,pTmSign->szDescription);
     } /* endif */

     // re-write signature record
     if ( fOK )
     {
       usRc = EQFNTMUpdSign( this->pTmClb->pstTmBtree, (PCHAR)pTmSign, sizeof(TMX_SIGN) );
       fOK = (usRc == NO_ERROR);
      } /* endif */

      // free any allocated buffer
      delete ( pTmSign );
  } /* endif */     
  return;
}





/*! \brief Get the name of the memory
    \param pszBuffer pointer to a buffer for the name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to the buffer
*/
int EqfMemory::getName
(
  char *pszBuffer,
  int iSize
)
{
  if ( this->pTmClb != NULL )
  {
    return( CopyToBuffer( this->szName, pszBuffer, iSize ) );
  }
  else
  {
    return( 0 );
  } /* endif */     
}

/*! \brief Get the name of the memory
    \param strName reference of a string receiving the memory name
*/
int EqfMemory::getName
(
  std::string &strName
)
{
  if ( this->pTmClb != NULL )
  {
    strName = this->szName;
    return( 0 );
  }
  else
  {
    strName = "";
    return( -1 );
  } /* endif */     
}


/*! \brief Get overall file size of this memory
  	\returns size of memory in number of bytes
*/
unsigned long EqfMemory::getFileSize()
{
  ULONG ulFileSize = 0;         // size of TM files

  if ( this->pTmClb != NULL )
  {
    EqfMemoryPlugin *pPlugin = (EqfMemoryPlugin *)this->getPlugin();

    PBTREE pDataTree = (PBTREE)this->pTmClb->pstTmBtree;
    PBTREE pIndexTree = (PBTREE)this->pTmClb->pstInBtree;

    unsigned long ulDataSize  = FilesystemHelper::GetFileSize( pDataTree->pBTree->fp );
    unsigned long ulIndexSize = FilesystemHelper::GetFileSize( pIndexTree->pBTree->fp );

    ulFileSize = ulDataSize + ulIndexSize;
  }
  return( ulFileSize );
}


USHORT TmtXReplace( PTMX_CLB, PTMX_PUT_IN_W, PTMX_PUT_OUT_W );

/*! \brief Store the supplied proposal in the memory
    When the proposal aready exists it will be overwritten with the supplied data

    \param pProposal pointer to a OtmProposal object

  	\returns 0 or error code in case of errors
*/
int EqfMemory::putProposal
(
  OtmProposal &Proposal
)
{
  int iRC = 0;

  if ( this->pTmPutIn == NULL ) this->pTmPutIn = new (TMX_PUT_IN_W);
  if ( this->pTmPutOut == NULL ) this->pTmPutOut = new (TMX_PUT_OUT_W);
  memset( this->pTmPutIn, 0, sizeof(TMX_PUT_IN_W) );
  memset( this->pTmPutOut, 0, sizeof(TMX_PUT_OUT_W) );

  this->OtmProposalToPutIn( Proposal, this->pTmPutIn );

  if(T5Logger::GetInstance()->CheckLogLevel(T5INFO)){
    std::string source = EncodingHelper::convertToUTF8(this->pTmPutIn->stTmPut.szSource);
    T5LOG( T5INFO) <<"EqfMemory::putProposal, source = " << source;
  }

  /********************************************************************/
  /* fill the TMX_PUT_IN prefix structure                             */
  /* stPrefixIn.usLengthInput                                         */
  /* stPrefixIn.usTmCommand                                           */
  /* the TMX_PUT_IN structure must not be filled it is provided       */
  /* by the caller                                                    */
  /********************************************************************/
  pTmPutIn->stPrefixIn.usLengthInput = sizeof( TMX_PUT_IN_W );
  pTmPutIn->stPrefixIn.usTmCommand   = TMC_REPLACE;

  /********************************************************************/
  /* call TmtXReplace                                                 */
  /********************************************************************/
  iRC = TmtXReplace ( (PTMX_CLB)htm, pTmPutIn, pTmPutOut );

  if ( iRC != 0 && (iRC != 5019 ||  T5Logger::GetInstance()->CheckLogLevel(T5DEBUG))){
      T5LOG(T5ERROR) <<  "EqfMemory::putProposal result = " << iRC;   
      //handleError( iRC, this->szName, this->pTmPutIn->stTmPut.szTagTable );
  }

  if ( ( iRC == 0 ) &&
       ( this->pTmPutIn->stTmPut.fMarkupChanged ) ) {
     iRC = SEG_RESET_BAD_MARKUP ;
  }

  return( iRC );
}


/*! \brief Get the the first proposal from the memory and prepare sequential access
    \param pProposal pointer to a OtmProposal object which will be filled with the proposal data
  	\returns 0 or error code in case of errors
*/
  int EqfMemory::getFirstProposal
  (
    OtmProposal &Proposal
  )
  {
    return( this->getFirstProposal( Proposal, NULL ) );
  }

  /*! \brief Get the the first proposal from the memory and prepare sequential access
    \param pProposal pointer to a OtmProposal object which will be filled with the proposal data
    \param piProgress pointer to buffer for progress indicator, this indicator goes from 0 up to 100
  	\returns 0 or error code in case of errors
*/
  int EqfMemory::getFirstProposal
  (
    OtmProposal &Proposal,
    int *piProgress
  )
  {
    this->ulNextKey = FIRST_KEY;
    this->usNextTarget = 1;

    return( this->getNextProposal( Proposal, piProgress ) );
  }

/*! \brief Get the next proposal from the memory 
    \param lHandle the hande returned by GetFirstProposal
    \param pProposal pointer to a OtmProposal object which will be filled with the proposal data
  	\returns 0 or error code in case of errors
*/
int EqfMemory::getNextProposal
(
  OtmProposal &Proposal
)
{
 return( this->getNextProposal( Proposal, NULL ) );
}


/*! \brief Get the next proposal from the memory 
    \param lHandle the hande returned by GetFirstProposal
    \param pProposal pointer to a OtmProposal object which will be filled with the proposal data
    \param piProgress pointer to buffer for progress indicator, this indicator goes from 0 up to 100
  	\returns 0 or error code in case of errors
*/
int EqfMemory::getNextProposal
(
  OtmProposal &Proposal,
  int *piProgress
)
{
  int iRC = 0;

  if ( this->pTmExtIn == NULL ) this->pTmExtIn = new (TMX_EXT_IN_W);
  if ( this->pTmExtOut == NULL ) this->pTmExtOut = new (TMX_EXT_OUT_W);
  memset( this->pTmExtIn, 0, sizeof(TMX_EXT_IN_W) );
  memset( this->pTmExtOut, 0, sizeof(TMX_EXT_OUT_W) );

  Proposal.clear();
  this->pTmExtIn->ulTmKey      = this->ulNextKey;
  this->pTmExtIn->usNextTarget = this->usNextTarget;
  this->pTmExtIn->usConvert    = MEM_OUTPUT_ASIS;

  iRC = (int)TmtXExtract(  this->pTmClb,  this->pTmExtIn,  this->pTmExtOut);

  if ( (iRC == 0) || (iRC == BTREE_CORRUPTED) )
  {
    if ( (piProgress != NULL) && (this->pTmExtOut->ulMaxEntries != 0) )
    {
      *piProgress =  (int)((this->pTmExtIn->ulTmKey - FIRST_KEY) * 100) /  (int)this->pTmExtOut->ulMaxEntries;
    } /* endif */     
  } /* endif */       

  if ( iRC == 0 )
  {
    this->ExtOutToOtmProposal( this->pTmExtOut, Proposal );

    // set current proposal internal key ,which is used in updateProposal
    this->SetProposalKey( this->pTmExtIn->ulTmKey,this->pTmExtIn->usNextTarget, &Proposal );
  } /* endif */       

  if ( (iRC == 0) || (iRC == BTREE_CORRUPTED) )
  {
    this->ulNextKey = pTmExtOut->ulTmKey;
    this->usNextTarget = pTmExtOut->usNextTarget;
  } /* endif */       

  if ( iRC == 0 )
  {
    // nothing to do
  }
  else if ( iRC == BTREE_EOF_REACHED )
  {
    iRC = INFO_ENDREACHED;
  }
  else
  {
    handleError( iRC, this->szName, this->pTmPutIn->stTmPut.szTagTable );
    if ( iRC == BTREE_CORRUPTED ) iRC = ERROR_ENTRYISCORRUPTED;
  }

  return( iRC );
}

  /*! \brief Get the current sequential access key (the key for the next proposal in the memory) 
  \param pszKeyBuffer pointer to the buffer to store the sequential access key
  \param iKeyBufferSize size of the key buffer in number of characters
  \returns 0 or error code in case of errors
*/
int EqfMemory::getSequentialAccessKey
(
  char *pszKeyBuffer,
  int  iKeyBufferSize
)
{
  int iRC = 0;
  char szKey[20];

  sprintf( szKey, "%lu:%u", this->ulNextKey, this->usNextTarget );
  if ( strlen(szKey)+1 <= iKeyBufferSize )
  {
    strcpy( pszKeyBuffer, szKey );
  }
  else
  {
    iRC = ERROR_BUFFERTOOSMALL;
  }
  return( iRC );
}

    
/*! \brief Set the current sequential access key to resume the sequential access at the given position
  \param pszKey a sequential access key previously returned by getSequentialAccessKey
  \returns 0 or error code in case of errors
*/
int EqfMemory::setSequentialAccessKey
(
  char *pszKey
)
{
  int iRC = this->SplitProposalKeyIntoRecordAndTarget( pszKey, &(this->ulNextKey), &(this->usNextTarget) );
  return( iRC );
}



/*! \brief Get the the proposal having the supplied key (InternalKey from the OtmProposal)
    \param pszKey internal key of the proposal
    \param Proposal buffer for the returned proposal data
  	\returns 0 or error code in case of errors
*/
int EqfMemory::getProposal
(
  char *pszKey,
  OtmProposal &Proposal
)
{
  int iRC = 0;

  if ( this->pTmExtIn == NULL ) this->pTmExtIn = new (TMX_EXT_IN_W);
  if ( this->pTmExtOut == NULL ) this->pTmExtOut = new (TMX_EXT_OUT_W);
  memset( this->pTmExtIn, 0, sizeof(TMX_EXT_IN_W) );
  memset( this->pTmExtOut, 0, sizeof(TMX_EXT_OUT_W) );

  Proposal.clear();

  iRC = this->SplitProposalKeyIntoRecordAndTarget( pszKey, &(this->pTmExtIn->ulTmKey), &(this->pTmExtIn->usNextTarget) );
  this->pTmExtIn->usConvert    = MEM_OUTPUT_ASIS;

  if ( iRC == 0 )
  {
    iRC = (int)TmtXExtract(  this->pTmClb,  this->pTmExtIn,  this->pTmExtOut);
  } /* endif */     

  if ( iRC == 0 )
  {
    this->ExtOutToOtmProposal( this->pTmExtOut, Proposal );

    // set current proposal internal key ,which is used in updateProposal
    this->SetProposalKey( this->pTmExtIn->ulTmKey,this->pTmExtIn->usNextTarget, &Proposal );

    this->ulNextKey = pTmExtOut->ulTmKey;
    this->usNextTarget = pTmExtOut->usNextTarget;
  } /* endif */       

  if ( iRC != 0 ) handleError( iRC, this->szName, this->pTmPutIn->stTmPut.szTagTable );

  return( iRC );

}




/*! \brief Provides a part of the memory in binary format

     The binary format is used by the folder export to add the memory
     in the internal format to the exported folder.

    \param pMemoryPartData pointer to the data area for the extraxt om binary format

  	\returns 0 or error code in case of errors
*/
int EqfMemory::getMemoryPart
(
  PMEMORYPARTDATA pData           // points to data area supplied by the caller
)
{
  int iRC = 0;

  // values for the type of currently processed file
  #define MEMGETPART_PROPID 1
  #define MEMGETPART_DATAID 2
  #define MEMGETPART_INDEXID 3

  // prepare our privatefields when this is the first get call for this file
  if ( pData->fFirstCall )
  {
    // reset fields
    pData->fFileIsComplete = FALSE;
    pData->ulFilePos = 0;
    pData->ulRemaining = 0;
    pData->ulTotalSize = 0;

    // get type of file being extracted
    PSZ pszExt = strrchr( pData->szFileName, '.' );
    if ( pszExt == NULL )
    {
      iRC = 0;
    }
    else if ( strcmp( pszExt, EXT_OF_MEM ) == 0 )
    {
      pData->ulState = MEMGETPART_PROPID;
      USHORT usOpenAction = 0;
      UtlOpen( pData->szFileName, (PHFILE)pData->pPrivatData, &usOpenAction, 0L, FILE_NORMAL, FILE_OPEN, OPEN_ACCESS_READONLY | OPEN_SHARE_DENYWRITE, 0L, FALSE );
      UtlGetFileSize( (HFILE)*((int *)pData->pPrivatData), &pData->ulTotalSize, FALSE );
      pData->ulRemaining = pData->ulTotalSize;
    }
    else if ( strcmp( pszExt, EXT_OF_TMDATA ) == 0 )
    {
      PBTREE pTree = (PBTREE)this->pTmClb->pstTmBtree;
      pData->ulState = MEMGETPART_DATAID;
      UtlGetFileSize( pTree->pBTree->fp, &pData->ulTotalSize, FALSE );
      pData->ulRemaining = pData->ulTotalSize;
    }
    else if ( strcmp( pszExt, EXT_OF_TMINDEX ) == 0 )
    {
      PBTREE pTree = (PBTREE)this->pTmClb->pstInBtree;
      pData->ulState = MEMGETPART_INDEXID;
      UtlGetFileSize( pTree->pBTree->fp, &pData->ulTotalSize, FALSE );
      pData->ulRemaining = pData->ulTotalSize;
    }
    else 
    {
      iRC = OtmMemory::ERROR_INVALIDREQUEST;
    } /* endif */       

    pData->fFirstCall = FALSE;
  } /* endif */     


  // get next part of requested file
  if ( iRC == 0 )
  {
    USHORT usRC = 0;
    ULONG ulNewPos = 0;
    PBTREE pTree = NULL;

    switch ( pData->ulState )
    {
      case MEMGETPART_PROPID:
        usRC = UtlChgFilePtr( (HFILE)*((int*)pData->pPrivatData), pData->ulFilePos, FILE_BEGIN, &ulNewPos, FALSE );

        if ( !usRC )                             //no error until now
        {
          usRC = UtlReadL( (HFILE)*((int*)pData->pPrivatData), pData->pbBuffer, pData->ulBytesToRead, &(pData->ulBytesRead), FALSE );
        } /*endif*/

        if ( !usRC )          
        {
           pData->ulFilePos = ulNewPos + pData->ulBytesRead;
           pData->ulRemaining -= pData->ulBytesRead;
           pData->fFileIsComplete = (pData->ulRemaining == 0);
           if ( pData->fFileIsComplete  )
           {
             UtlClose( (HFILE)*((int*)pData->pPrivatData), FALSE ); 
           } /* end */              
        }/*endif*/
        break;

      case MEMGETPART_DATAID:
        pTree = (PBTREE)this->pTmClb->pstTmBtree;
        usRC = UtlChgFilePtr( pTree->pBTree->fp, pData->ulFilePos, FILE_BEGIN, &ulNewPos, FALSE );

        if ( !usRC )                             //no error until now
        {
          usRC = UtlReadL( pTree->pBTree->fp, pData->pbBuffer, pData->ulBytesToRead, &(pData->ulBytesRead), FALSE );
        } /*endif*/

        if ( !usRC )          
        {
           pData->ulFilePos = ulNewPos + pData->ulBytesRead;
           pData->ulRemaining -= pData->ulBytesRead;
           pData->fFileIsComplete = (pData->ulRemaining == 0);
        }/*endif*/
        break;

      case MEMGETPART_INDEXID:
        pTree = (PBTREE)this->pTmClb->pstInBtree;
        usRC = UtlChgFilePtr( pTree->pBTree->fp, pData->ulFilePos, FILE_BEGIN, &ulNewPos, FALSE );

        if ( !usRC )                             //no error until now
        {
          usRC = UtlReadL( pTree->pBTree->fp, pData->pbBuffer, pData->ulBytesToRead, &(pData->ulBytesRead), FALSE );
        } /*endif*/

        if ( !usRC )          
        {
           pData->ulFilePos = ulNewPos + pData->ulBytesRead;
           pData->ulRemaining -= pData->ulBytesRead;
           pData->fFileIsComplete = (pData->ulRemaining == 0);
        }/*endif*/
        break;
    } /* endswitch */       
  } /* end */     

  return( iRC );
}

/*! \brief Get a list of memory proposals matching the given search key

    This method uses the search data contained in the search key to find one or more
    matching proposals in the memory. At least the szSource and the szTargetLang members of the
    search key have to be filled by the caller.
    The caller provides a list of OtmProposals which will be filled with the data of the matching 
    proposals. The number of requested proposals is determined by the number
    of proposals in the list.

    \param SearchKey proposal containing search string and meta data
    \param FoundProposals refernce to vector with OtmProposal objects
    \param ulOptions options for the lookup

  	\returns 0 or error code in case of errors
*/
int EqfMemory::searchProposal
(
  OtmProposal &SearchKey,
  std::vector<OtmProposal *> &FoundProposals,
  unsigned long ulOptions
)
{
  int iRC = 0;

  if ( this->pTmGetIn == NULL ) this->pTmGetIn = new (TMX_GET_IN_W);
  if ( this->pTmGetOut == NULL ) this->pTmGetOut = new (TMX_GET_OUT_W);
  memset( this->pTmGetIn, 0, sizeof(TMX_GET_IN_W) );
  memset( this->pTmGetOut, 0, sizeof(TMX_GET_OUT_W) );

  this->OtmProposalToGetIn( SearchKey, this->pTmGetIn );
  this->pTmGetIn->stTmGet.usConvert = MEM_OUTPUT_ASIS;
  this->pTmGetIn->stTmGet.usRequestedMatches = (USHORT)FoundProposals.size();
  this->pTmGetIn->stTmGet.ulParm = ulOptions;
  this->pTmGetIn->stTmGet.pvGMOptList = this->pvGlobalMemoryOptions;

  if(T5Logger::GetInstance()->CheckLogLevel(T5DEBUG)){
    auto str = EncodingHelper::convertToUTF8(this->pTmGetIn->stTmGet.szSource);
    T5LOG( T5DEBUG) <<"EqfMemory::searchProposal::*** method: searchProposal, looking for " <<  str;
  } 
  iRC = (int)TmGetW ( this->htm,  NULL,  this->pTmGetIn,  this->pTmGetOut, FALSE );

  if ( iRC == 0 )
  {
    T5LOG( T5DEBUG) <<"EqfMemory::searchProposal::   lookup complete, found " << this->pTmGetOut->usNumMatchesFound << " proposals"   ;
    wchar_t szRequestedString[2049];
    SearchKey.getSource( szRequestedString, sizeof(szRequestedString) );

    for ( int i = 0; i < (int)FoundProposals.size(); i++ )
    {
      if ( i >= this->pTmGetOut->usNumMatchesFound )
      {
        FoundProposals[i]->clear();
      }
      else
      {
        if(T5Logger::GetInstance()->CheckLogLevel(T5DEBUG)){
          auto strSource = EncodingHelper::convertToUTF8(pTmGetOut->stMatchTable[i].szSource );
          T5LOG( T5DEBUG) <<"EqfMemory::searchProposal::   proposal " << i << ": match=" << pTmGetOut->stMatchTable[i].usMatchLevel << ", source=", strSource;
        }
        //replace tags for proposal
        auto result = EncodingHelper::ReplaceOriginalTagsWithPlaceholders(pTmGetOut->stMatchTable[i].szSource, 
                                                                                     pTmGetOut->stMatchTable[i].szTarget, 
                                                                                     szRequestedString); 
        wcscpy(pTmGetOut->stMatchTable[i].szSource, result[0].c_str());
        wcscpy(pTmGetOut->stMatchTable[i].szTarget, result[1].c_str());

        
        if( pTmGetOut->stMatchTable[i].usMatchLevel >= 100){
          //correct match rate for exact match based on whitespace difference
          int wsDiff = 0;
          UtlCompIgnWhiteSpaceW(szRequestedString, pTmGetOut->stMatchTable[i].szSource, 0, &wsDiff);
          pTmGetOut->stMatchTable[i].usMatchLevel -= wsDiff;
          
        }

        this->MatchToOtmProposal( pTmGetOut->stMatchTable + i, FoundProposals[i] );
      } /* end */         
    } /* end */       
  }
  else
  {
    T5LOG( T5DEBUG) <<"EqfMemory::searchProposal::  lookup failed, rc=" << iRC;
  } /* end */     

  if ( iRC != 0 ) handleError( iRC, this->szName, this->pTmGetIn->stTmGet.szTagTable );

  return( iRC );
}

/*! \brief Updates some fields of a specific proposal in the memory

    \param Proposal reference to a OtmProposal object containing the data being changed
    \param usUpdateFlags Flags selecting the update fields

  	\returns 0 or error code in case of errors
*/
int EqfMemory::updateProposal
(
  OtmProposal &Proposal,
  USHORT      usUpdateFlags
)
{
  int iRC = 0;
  ULONG ulKey = 0;
  USHORT usTarget = 0;

  if ( this->pTmPutIn == NULL ) this->pTmPutIn = new (TMX_PUT_IN_W);
  memset( this->pTmPutIn, 0, sizeof(TMX_PUT_IN_W) );

  if ( !iRC ) iRC = this->OtmProposalToPutIn( Proposal, this->pTmPutIn );
  if ( !iRC ) iRC = this->SplitProposalKeyIntoRecordAndTarget( Proposal, &ulKey, &usTarget );
  if ( !iRC ) iRC = TmUpdSegW( this->htm,  NULL,  this->pTmPutIn,  ulKey,  usTarget,  usUpdateFlags,  FALSE );

  if ( iRC != 0 ) handleError( iRC, this->szName, this->pTmPutIn->stTmPut.szTagTable );

  return( iRC );
}


/*! \brief Delete a specific proposal from the memory

    \param Proposal reference to a OtmProposal object

  	\returns 0 or error code in case of errors
*/
int EqfMemory::deleteProposal
(
  OtmProposal &Proposal
)  
{
  if ( this->pTmPutIn == NULL ) 
    this->pTmPutIn = new (TMX_PUT_IN_W);
  memset( this->pTmPutIn, 0, sizeof(TMX_PUT_IN_W) );
  if ( this->pTmPutOut == NULL ) 
    this->pTmPutOut = new (TMX_PUT_OUT_W);
  memset( this->pTmPutOut, 0, sizeof(TMX_PUT_OUT_W) );
  int iRC = this->OtmProposalToPutIn( Proposal, this->pTmPutIn );
  
  this->pTmPutIn->stPrefixIn.usLengthInput = sizeof( TMX_PUT_IN_W );
  this->pTmPutIn->stPrefixIn.usTmCommand   = TMC_DELETE;

	if ( !iRC ) 
    iRC = TmtXDelSegm ( (PTMX_CLB)htm, this->pTmPutIn, this->pTmPutOut );

  if ( iRC != 0  
      && iRC != 6020) // seg not found 
    handleError( iRC, this->szName, this->pTmPutIn->stTmPut.szTagTable );
  
  return( iRC );
}

/*! \brief Rebuild internal index after mass updates
  This method is called after mass updates (e.g. memory import) has beebn performed.
  The memory can rebuild or optimize its internal index when necessary.

  \returns 0 or error code in case of errors
*/
int EqfMemory::rebuildIndex
(
)
{
  int iRC = 0;

  if ( !iRC ) iRC = NTMOrganizeIndexFile1( this->pTmClb );

  return( iRC );
}


/*! \brief Get plugin responsible for this memory
  	\returns pointer to memory plugin object
*/
void *EqfMemory::getPlugin()
{
  return( (void *)this->pMemoryPlugin );
}

/*! \brief Provide the internal memory handle
  	\returns memory handle
*/
HTM EqfMemory::getHTM()
{
  return( this->htm );
}

/*! \brief Get number of proposals in thismemory
  	\returns number of proposals
*/
unsigned long EqfMemory::getProposalNum()
{
  if ( this->pTmClb == NULL ) return( 0 );

  ULONG ulStartKey = 0;
  ULONG ulNextKey = 0;
T5LOG(T5ERROR) << ":: TEMPORARY_COMMENTED temcom_id = 15  EQFNTMGetNextNumber( this->pTmClb->pstTmBtree, &ulStartKey, &ulNextKey);";
#ifdef TEMPORARY_COMMENTED
  EQFNTMGetNextNumber( this->pTmClb->pstTmBtree, &ulStartKey, &ulNextKey);
#endif //TEMPORARY_COMMENTED
  return( (int)(ulNextKey - ulStartKey) );
}

/*! \brief Get the error message for the last error occured

    \param strError reference to a string receiving the error mesage text
  	\returns last error code
*/
int EqfMemory::getLastError
(
  std::string &strError
)
{
  strError = this->strLastError;
  return( this->iLastError );
}

  /*! \brief Get the error message for the last error occured

    \param pszError pointer to a buffer for the error text
    \param iBufSize size of error text buffer in number of characters
  	\returns last error code
*/
int EqfMemory::getLastError
(
  char *pszError,
  int iBufSize
)
{
  strncpy( pszError, this->strLastError.c_str(), iBufSize );
  return( this->iLastError );
}

/*! \brief Get number of different document names used in the memory
  	\returns number of markups used by the memory proposals or 0 if no document name information can be provided
*/
int EqfMemory::getNumOfDocumentNames()
{
  if ( this->pTmClb != NULL )
  {
    return( (int)(this->pTmClb->pLongNames->ulEntries) );
  }
  else
  {
    return( 0 );
  } /* end */     
}


/*! \brief Get document name at position n [n = 0.. GetNumOfDocumentNames()-1]
    \param iPos position of document name
    \param pszBuffer pointer to a buffer for the document name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
int EqfMemory::getDocumentName
(
  int iPos,
  char *pszBuffer,
  int iSize
)
{
  if ( this->pTmClb != NULL )
  {
    if ( (iPos >= 0) && (iPos < (int)(this->pTmClb->pLongNames->ulEntries)) )
    {
      return( CopyToBuffer( this->pTmClb->pLongNames->stTableEntry[iPos].pszLongName, pszBuffer, iSize ) );
    }
    else
    {
      return( 0 );
    } /* end */     
  }
  else
  {
    return( 0 );
  } /* end */     
}

  /*! \brief Get number of different document short names used in the memory
  	\returns number of document short names used by the memory proposals or 0 if no document short name information can be provided
*/
int EqfMemory::getNumOfDocumentShortNames()
{
  if ( this->pTmClb != NULL )
  {
    return( (int)(this->pTmClb->pFileNames->ulMaxEntries) );
  }
  else
  {
    return( 0 );
  } /* end */     
}

/*! \brief Get document name at position n [n = 0.. GetNumOfDocumentShortNames()-1]
    \param iPos position of document short name
    \param pszBuffer pointer to a buffer for the document name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
int EqfMemory::getDocumentShortName
(
  int iPos,
  char *pszBuffer,
  int iSize
)
{
  if ( this->pTmClb != NULL )
  {
    if ( (iPos >= 0) && (iPos < (int)(this->pTmClb->pFileNames->ulMaxEntries)) )
    {
      PTMX_TABLE_ENTRY pEntry = &(this->pTmClb->pFileNames->stTmTableEntry);
      pEntry += iPos;
      return( CopyToBuffer( pEntry->szName, pszBuffer, iSize ) );
    }
    else
    {
      return( 0 );
    } /* end */     
  }
  else
  {
    return( 0 );
  } /* end */     
}



/*! \brief Get number of different languages used in the memory
  	\returns number of languages used by the memory proposals or 0 if no language information can be provided
*/
int EqfMemory::getNumOfLanguages()
{
  if ( this->pTmClb != NULL )
  {
    return( (int)(this->pTmClb->pLanguages->ulMaxEntries) );
  }
  else
  {
    return( 0 );
  } /* end */     
}

/*! \brief Get language at position n [n = 0.. GetNumOfLanguages()-1]
    \param iPos position of language
    \param pszBuffer pointer to a buffer for the document name
    \param iSize size of buffer in number of characters
  	\returns number of characters copied to buffer
*/
int EqfMemory::getLanguage
(
  int iPos,
  char *pszBuffer,
  int iSize
)
{
  if ( this->pTmClb != NULL )
  {
    if ( (iPos >= 0) && (iPos < (int)(this->pTmClb->pLanguages->ulMaxEntries)) )
    {
      PTMX_TABLE_ENTRY pEntry = &(this->pTmClb->pLanguages->stTmTableEntry);
      pEntry += iPos;
      return( CopyToBuffer( pEntry->szName, pszBuffer, iSize ) );
    }
    else
    {
      return( 0 );
    } /* end */     
  }
  else
  {
    return( 0 );
  } /* end */     
}



/* private helper functions */

/*! \brief Build OtmProposal key from record number and target number
    \param ulKey key of record containing the proposal
    \param usTargetNum number of target within record 
    \param Proposal reference to the OtmProposal 
  	\returns 0 or error code in case of errors
*/
int EqfMemory::SetProposalKey
(
  ULONG   ulKey,
  USHORT  usTargetNum,
  OtmProposal *pProposal
)
{
  int iRC = 0;
  char szKey[20];

  sprintf( szKey, "%lu:%u", ulKey, usTargetNum );
  pProposal->setInternalKey( szKey );

  return( iRC );
}

/*! \brief Split an internal key into record number and target number
    \param Proposal reference to the OtmProposal 
    \param pulKey pointer to record number buffer
    \param pusTargetNum pointer to buffer for number of target within record 
  	\returns 0 or error code in case of errors
*/
int EqfMemory::SplitProposalKeyIntoRecordAndTarget
(
  OtmProposal &Proposal,
  ULONG   *pulKey,
  USHORT  *pusTargetNum
)
{
  int iRC = 0;
  char szKey[20]= {0};
  Proposal.getInternalKey( szKey, sizeof(szKey) );
  return( this->SplitProposalKeyIntoRecordAndTarget( szKey, pulKey, pusTargetNum ) );
}

/*! \brief Split an internal key into record number and target number
    \param Proposal reference to the OtmProposal 
    \param pulKey pointer to record number buffer
    \param pusTargetNum pointer to buffer for number of target within record 
  	\returns 0 or error code in case of errors
*/
int EqfMemory::SplitProposalKeyIntoRecordAndTarget
(
  char    *pszKey,
  ULONG   *pulKey,
  USHORT  *pusTargetNum
)
{
  int iRC = 0;
  char *pszTarget = strchr( pszKey, ':' );
  if ( pszTarget != NULL )
  {
    *pszTarget = '\0';
    *pulKey = atol( pszKey );
    *pusTargetNum = (USHORT)atoi( pszTarget + 1 );
  }
  else
  {
    iRC = OtmMemory::ERROR_INTERNALKEY_MISSING;
  } /* end */     

  return( iRC );
}




/*! \brief Fill OtmProposal from TMX_GET_OUT_W structure
    \param pExtOut pointer to the TMX_GET_OUT_W structure
    \param Proposal reference to the OtmProposal being filled
  	\returns 0 or error code in case of errors
*/
int EqfMemory::ExtOutToOtmProposal
(
  PTMX_EXT_OUT_W pExtOut,
  OtmProposal &Proposal
)
{
  int iRC = 0;

  Proposal.clear();
  Proposal.setSource( pExtOut->stTmExt.szSource );
  Proposal.setTarget( pExtOut->stTmExt.szTarget );
  Proposal.setAuthor( pExtOut->stTmExt.szAuthorName );
  Proposal.setMarkup( pExtOut->stTmExt.szTagTable );
  Proposal.setTargetLanguage( pExtOut->stTmExt.szTargetLanguage );
  Proposal.setSourceLanguage( this->pTmClb->stTmSign.szSourceLanguage);
  Proposal.setAddInfo( pExtOut->stTmExt.szAddInfo );
  Proposal.setContext( pExtOut->stTmExt.szContext );
  Proposal.setDocName( pExtOut->stTmExt.szLongName );
  Proposal.setDocShortName( pExtOut->stTmExt.szFileName );
  Proposal.setSegmentNum( pExtOut->stTmExt.ulSourceSegmentId );
  Proposal.setType( FlagToProposalType( pExtOut->stTmExt.usTranslationFlag ) );
  Proposal.setUpdateTime( pExtOut->stTmExt.lTargetTime );
  Proposal.setContextRanking( 0 );
  Proposal.setOriginalSourceLanguage( pExtOut->stTmExt.szOriginalSourceLanguage );

  return( iRC );
}

/*! \brief Fill OtmProposal from TMX_MATCH_TABLE_W structure
    \param pMatch pointer to the TMX_MATCH_TABLE_W structure
    \param Proposal reference to the OtmProposal being filled
  	\returns 0 or error code in case of errors
*/
int EqfMemory::MatchToOtmProposal
(
  PTMX_MATCH_TABLE_W pMatch,
  OtmProposal *pProposal
)
{
  int iRC = 0;

  pProposal->clear();
  pProposal->setSource( pMatch->szSource );
  pProposal->setTarget( pMatch->szTarget );
  pProposal->setAuthor( pMatch->szTargetAuthor );
  pProposal->setMarkup( pMatch->szTagTable );
  pProposal->setTargetLanguage( pMatch->szTargetLanguage );
  pProposal->setSourceLanguage( this->pTmClb->stTmSign.szSourceLanguage);
  pProposal->setAddInfo( pMatch->szAddInfo );
  pProposal->setContext( pMatch->szContext );
  pProposal->setDocName( pMatch->szLongName );
  pProposal->setDocShortName( pMatch->szFileName );
  pProposal->setSegmentNum( pMatch->ulSegmentId );
  pProposal->setType( FlagToProposalType( pMatch->usTranslationFlag ) );
  pProposal->setUpdateTime( pMatch->lTargetTime );
  this->SetProposalKey( pMatch->ulKey, pMatch->usTargetNum, pProposal );
  pProposal->setContextRanking( (int)pMatch->usContextRanking );
  pProposal->setMemoryIndex( pMatch->usDBIndex );
  pProposal->setWords( pMatch->iWords );
  pProposal->setDiffs( pMatch->iDiffs );
  pProposal->setOriginalSourceLanguage( pMatch->szOriginalSrcLanguage );
  
  switch ( pMatch->usMatchLevel )
  {
    case 102: 
      pProposal->setFuzziness( 100 ); 
      pProposal->setMatchType( OtmProposal::emtExactExact ); 
      break;
    case 101: 
      pProposal->setFuzziness( 100 ); 
      pProposal->setMatchType( OtmProposal::emtExactSameDoc ); 
      break;
    case 100: 
      pProposal->setFuzziness( 100 ); 
      pProposal->setMatchType( OtmProposal::emtExact ); 
      break;
    case  99: 
      pProposal->setFuzziness( (pMatch->usTranslationFlag == TRANSLFLAG_MACHINE) ? 100 : 99 ); 
      pProposal->setMatchType( (pMatch->usTranslationFlag == TRANSLFLAG_MACHINE) ? OtmProposal::emtExact : OtmProposal::emtFuzzy );
      break;
    default: 
      pProposal->setFuzziness( pMatch->usMatchLevel); 
      pProposal->setMatchType( OtmProposal::emtFuzzy ); 
      break;
  } /* end */     

  return( iRC );
}

/*! \brief Fill TMX_PUT_IN_W structure with OtmProposal data
    \param Proposal reference to the OtmProposal containing the data
    \param pPutIn pointer to the TMX_PUT_IN_W structure
  	\returns 0 or error code in case of errors
*/
int EqfMemory::OtmProposalToPutIn
(
  OtmProposal &Proposal,
  PTMX_PUT_IN_W pPutIn
)
{
  int iRC = 0;

  Proposal.getSource( pPutIn->stTmPut.szSource, sizeof(pPutIn->stTmPut.szSource) );
  Proposal.getTarget( pPutIn->stTmPut.szTarget, sizeof(pPutIn->stTmPut.szTarget) );
  Proposal.getAuthor( pPutIn->stTmPut.szAuthorName, sizeof(pPutIn->stTmPut.szAuthorName) );
  Proposal.getMarkup( pPutIn->stTmPut.szTagTable, sizeof(pPutIn->stTmPut.szTagTable)  );
  Proposal.getSourceLanguage( pPutIn->stTmPut.szSourceLanguage, sizeof(pPutIn->stTmPut.szSourceLanguage)  );
  Proposal.getTargetLanguage( pPutIn->stTmPut.szTargetLanguage, sizeof(pPutIn->stTmPut.szTargetLanguage)  );
  Proposal.getAddInfo( pPutIn->stTmPut.szAddInfo, sizeof(pPutIn->stTmPut.szAddInfo)  );
  Proposal.getContext( pPutIn->stTmPut.szContext, sizeof(pPutIn->stTmPut.szContext)  );
  Proposal.getDocName( pPutIn->stTmPut.szLongName, sizeof(pPutIn->stTmPut.szLongName)  );
  Proposal.getDocShortName( pPutIn->stTmPut.szFileName, sizeof(pPutIn->stTmPut.szFileName)  );
  pPutIn->stTmPut.ulSourceSegmentId = Proposal.getSegmentNum();
  switch ( Proposal.getType() )
  {
    case OtmProposal::eptManual: pPutIn->stTmPut.usTranslationFlag = TRANSLFLAG_NORMAL; break;
    case OtmProposal::eptMachine: pPutIn->stTmPut.usTranslationFlag = TRANSLFLAG_MACHINE; break;
    case OtmProposal::eptGlobalMemory: pPutIn->stTmPut.usTranslationFlag = TRANSLFLAG_GLOBMEM; break;
    case OtmProposal::eptGlobalMemoryStar: pPutIn->stTmPut.usTranslationFlag = TRANSLFLAG_GLOBMEMSTAR; break;
    default: pPutIn->stTmPut.usTranslationFlag = TRANSLFLAG_NORMAL; break;
  } /* endswitch */     
  pPutIn->stTmPut.lTime = Proposal.getUpdateTime();

  return( iRC );
}

/*! \brief Fill TMX_GET_IN_W structure with OtmProposal data
    \param Proposal reference to the OtmProposal containing the data
    \param pGetIn pointer to the TMX_GET_IN_W structure
  	\returns 0 or error code in case of errors
*/
int EqfMemory::OtmProposalToGetIn
(
  OtmProposal &Proposal,
  PTMX_GET_IN_W pGetIn
)
{
  int iRC = 0;

  memset( &(pGetIn->stTmGet), 0, sizeof(pGetIn->stTmGet) );
  Proposal.getSource( pGetIn->stTmGet.szSource, sizeof(pGetIn->stTmGet.szSource) );
  Proposal.getAuthor( pGetIn->stTmGet.szAuthorName, sizeof(pGetIn->stTmGet.szAuthorName) );
  Proposal.getMarkup( pGetIn->stTmGet.szTagTable, sizeof(pGetIn->stTmGet.szTagTable)  );
  Proposal.getSourceLanguage( pGetIn->stTmGet.szSourceLanguage, sizeof(pGetIn->stTmGet.szSourceLanguage)  );
  Proposal.getTargetLanguage( pGetIn->stTmGet.szTargetLanguage, sizeof(pGetIn->stTmGet.szTargetLanguage)  );
  Proposal.getAddInfo( pGetIn->stTmGet.szAddInfo, sizeof(pGetIn->stTmGet.szAddInfo)  );
  Proposal.getContext( pGetIn->stTmGet.szContext, sizeof(pGetIn->stTmGet.szContext)  );
  Proposal.getDocName( pGetIn->stTmGet.szLongName, sizeof(pGetIn->stTmGet.szLongName)  );
  Proposal.getDocShortName( pGetIn->stTmGet.szFileName, sizeof(pGetIn->stTmGet.szFileName)  );
  
  //pGetIn->stTmGet.usMatchThreshold = TM_DEFAULT_THRESHOLD;
  int threshold = TM_DEFAULT_THRESHOLD;
  properties_get_int_or_default(KEY_TRIPLES_THRESHOLD, threshold, threshold);
  pGetIn->stTmGet.usMatchThreshold = threshold;
  pGetIn->stTmGet.ulSegmentId = Proposal.getSegmentNum();
  pGetIn->stTmGet.pvReplacementList = (PVOID)Proposal.getReplacementList();
  pGetIn->stTmGet.fSourceLangIsPrefered= Proposal.isSourceLangIsPrefered();
  pGetIn->stTmGet.fTargetLangIsPrefered = LanguageFactory::getInstance()->findIfPreferedLanguage( pGetIn->stTmGet.szTargetLanguage ) >= 0;
  return( iRC );
}


int CopyToBuffer( char *pszSource, char *pszBuffer, int iBufSize )
{
  int iCopied = 0;
  iBufSize--;  // leave room for string terminator
  while ( (iCopied < iBufSize) && (*pszSource != '\0') )
  {
    *pszBuffer++ = *pszSource++;
    iCopied++;
  } /* end */     
  *pszBuffer = '\0';
  return( iCopied );
}

OtmProposal::eProposalType FlagToProposalType( USHORT usTranslationFlag )
{
  if ( usTranslationFlag == TRANSLFLAG_NORMAL ) return( OtmProposal::eptManual );
  if ( usTranslationFlag == TRANSLFLAG_MACHINE ) return( OtmProposal::eptMachine );
  if ( usTranslationFlag == TRANSLFLAG_GLOBMEM ) return( OtmProposal::eptGlobalMemory );
  if ( usTranslationFlag == TRANSLFLAG_GLOBMEMSTAR ) return( OtmProposal::eptGlobalMemoryStar );
  return( OtmProposal::eptUndefined );
}

/*! \brief Handle a return code from the memory functions and create 
    the approbriate error message text for it
    \param iRC return code from memory function
    \param pszMemName long memory name
    \param pszMarkup markup table name
  	\returns original or modified error return code
*/
int EqfMemory::handleError( int iRC, char *pszMemName, char *pszMarkup )
{
  PBTREE pDataTree = (PBTREE)this->pTmClb->pstTmBtree;

  return( EqfMemoryPlugin::handleError( iRC, pszMemName, pszMarkup, pDataTree->szFileName, this->strLastError, this->iLastError ) );
}

/*! \brief Set or clear the pointer to a loaded global memory option file

    This method sets a pointer to a loaded global memory option file.
    When set the option file will be used to decide how global memory proposals will be processed.

    \param pvGlobalMemoryOptionsIn pointer to a loaded global memory option file or NULL to clear the current option file pointer

  	\returns 0 or error code in case of errors
*/
int EqfMemory::setGlobalMemoryOptions
(
    void *pvGlobalMemoryOptionsIn
)
{
  this->pvGlobalMemoryOptions = pvGlobalMemoryOptionsIn;
  return( 0 );
}
