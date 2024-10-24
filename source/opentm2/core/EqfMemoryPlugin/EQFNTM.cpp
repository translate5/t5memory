//------------------------------------------------------------------------------
// EQFNTM.C
//------------------------------------------------------------------------------
// Description: TranslationMemory interface functions.
//------------------------------------------------------------------------------
//|Copyright Notice:                                                           |
//|                                                                            |
//|      Copyright (C) 1990-2015, International Business Machines              |
//|      Corporation and others. All rights reserved                           |
//+----------------------------------------------------------------------------+
// Entry Points:
// C TmCreate
// C TmOpen
// C TmClose
// C TmReplace
// C TmGet
// C TmExtract
// C TmInfo
// C TmDeleteTm
// C TmDeleteSegment
//------------------------------------------------------------------------------
// Externals:
//------------------------------------------------------------------------------
// Internals:
// C NTMGetThresholdFromProperties
// C NTMFillCreateInStruct
//------------------------------------------------------------------------------

/**********************************************************************/
/* needed header files                                                */
/**********************************************************************/
#define INCL_EQF_ANALYSIS         // analysis functions
#define INCL_EQF_TM               // general Transl. Memory functions
#define INCL_EQF_DLGUTILS         // dialog utilities
#define INCL_EQF_TMREMOTE         // remote Transl. Memory functions (U-Code)
#include <EQF.H>                  // General Translation Manager include file

#include "LogWrapper.h"
#include <EQFSETUP.H>             // Directory name defines and other
#include "EQFDDE.H"               // Batch mode definitions
#include <EQFTMI.H>               // Private header file of Translation Memory
#include <EQFEVENT.H>             // Event logging
#include "FilesystemWrapper.h"
#include "PropertyWrapper.H"

#ifdef _DEBUG
  //#define SESSIONLOG
#endif
/**********************************************************************/
/* prototypes for internal functions                                  */
/**********************************************************************/
USHORT
C_TmCreate( PSZ         pszPathMem,      //(in)  full TM name x:\eqf\mem\mem.tmd
          HTM         *htm,            //(out) TM handle
          HTM         hModel,          //(in)  model handle
          PSZ         pszServer,       //(in)  server name or empty string
          PSZ         pszUserID,       //(in)  LAN USERID or empty string
          PSZ         pszSourceLang,   //(in)  source language or empty string
          PSZ         pszDescription,  //(in)  TM description or empty string
          USHORT      usMsgHandling,   //(in)  message handling parameter
                                       //      TRUE:  display error message
                                       //      FALSE: display no error message
          HWND        hwnd );           //(in)  handle for error messages
USHORT
C_TmOpen( PSZ        szMemFullPath,      //(in)  full TM name x:\eqf\mem\mem.tmd
        HTM        *phtm,              //(out) TM handle
        USHORT     usAccess,           //(in)  access mode: NON_EXCLUSIVE
                                       //                   EXCLUSIVE
                                       //                   FOR_ORGANIZE
        USHORT     usLocation,         //(in)  location:    TM_LOCAL
                                       //                   TM_REMOTE
                                       //                   TM_LOCAL_REMOTE
        USHORT     usMsgHandling,      //(in)  message handling parameter
                                       //      TRUE:  display error message
                                       //      FALSE: display no error message
        HWND       hwnd );              //(in)  handle for error messages
USHORT
C_TmClose( HTM        htm,               //(in) TM handle returned from open
         PSZ        szMemPath,         //(in) full TM name x:\eqf\mem\mem.tmd
         USHORT     usMsgHandling,     //(in) message handling parameter
                                   //     TRUE:  display error message
                                   //     FALSE: display no error message
         HWND       hwnd );         //(in) handle for error messages
USHORT
C_TmReplaceHwnd( HTM,           //(in)  TM handle
           PSZ,           //(in)  full TM name x:\eqf\mem\mem.mem
           PTMX_PUT_IN,   //(in)  pointer to put input structure
           PTMX_PUT_OUT,  //(out) pointer to put output structure
           USHORT,        //(in)  message handling parameter
                          //      TRUE:  display error message
                          //      FALSE: display no error message
           HWND );                     //(in) handle for error messages

USHORT
C_TmReplaceHwndW( HTM       htm,            //(in)  TM handle
           PSZ            szMemPath,      //(in)  full TM name x:\eqf\mem\mem
           PTMX_PUT_IN_W  pstPutIn,       //(in)  pointer to put input structure
           PTMX_PUT_OUT_W pstPutOut,      //(out) pointer to put output structure
           USHORT         usMsgHandling,  //(in)  message handling parameter
                                          //      TRUE:  display error message
                                          //      FALSE: display no error message
           HWND           hwnd );          //(in)  handle for error messages

USHORT
C_TmExtractHwnd( HTM,
           PSZ,
           PTMX_EXT_IN,
           PTMX_EXT_OUT,
           USHORT,
           HWND );                     //(in) handle for error messages

USHORT
C_TmExtractHwndW
  ( HTM          htm,              //(in)  TM handle
    PSZ          szMemPath,        //(in)  full TM name x:\eqf\mem\mem.tmd
    PTMX_EXT_IN_W  pstExtIn,       //(in)  pointer to extract input structure
    PTMX_EXT_OUT_W pstExtOut,      //(out) pointer to extract output structure
    USHORT       usMsgHandling,    //(in)  message handling parameter
                                   //      TRUE:  display error message
                                   //      FALSE: display no error message
    HWND         hwnd );            //(in)  handle for error messages

USHORT
C_TmGetW(HTM            htm,             //(in)  TM handle
       PSZ            szMemPath,       //(in)  full TM name x:\eqf\mem\mem.tmd
       PTMX_GET_IN_W  pstGetIn,        //(in)  pointer to get input structure
       PTMX_GET_OUT_W pstGetOut,       //(out) pointer to get output structure
       USHORT         usMsgHandling );  //(in)  message handling parameter

USHORT C_TmInfoHwnd( HTM, PSZ, USHORT, PTMX_INFO_IN, PTMX_INFO_OUT, USHORT, HWND );

USHORT C_TmUpdSegHwnd
(
  HTM         htm,                       //(in)  TM handle
  PSZ         szMemPath,                 //(in)  full TM name x:\eqf\mem\mem
  PTMX_PUT_IN pstPutIn,                  //(in)  pointer to put input structure
  ULONG       ulUpdKey,                  //(in)  key of record being updated
  USHORT      usUpdTarget,               //(in)  number of target being updated
  USHORT      usFlags,                   //(in)  flags controlling the updated fields
  USHORT      usMsgHandling,             //(in)  message handling parameter
                                         //      TRUE:  display error message
                                         //      FALSE: display no error message
  HWND        hwnd                       //(in)  handle for error messages
);

USHORT C_TmUpdSegHwndW
(
  HTM         htm,                       //(in)  TM handle
  PSZ         szMemPath,                 //(in)  full TM name x:\eqf\mem\mem
  PTMX_PUT_IN_W pstPutIn,                  //(in)  pointer to put input structure
  ULONG       ulUpdKey,                  //(in)  key of record being updated
  USHORT      usUpdTarget,               //(in)  number of target being updated
  USHORT      usFlags,                   //(in)  flags controlling the updated fields
  USHORT      usMsgHandling,             //(in)  message handling parameter
                                         //      TRUE:  display error message
                                         //      FALSE: display no error message
  HWND        hwnd                       //(in)  handle for error messages
);

USHORT
NTMFillCreateInStruct( HTM,
                       PSZ,
                       PSZ,
                       PSZ,
                       PSZ,
                       PSZ,
                       PTMX_CREATE_IN,
                       USHORT, HWND );
USHORT
NTMGetThresholdFromProperties( PSZ,
                               PUSHORT,
                               USHORT );



// utility to get the property file extension
char *GetPropFileExtension( char *pszMemPath )
{
  char *pszExt = strrchr( pszMemPath, '.' );
  if ( pszExt != NULL )
  {
    if ( strcmp( pszExt, EXT_OF_SHARED_MEM ) == 0 )
    {
      return( LANSHARED_MEM_PROP );
    }
    else
    {
      return( EXT_OF_MEM );
    }
  }
  else
  {
    return( EXT_OF_MEM );
  }
}

//------------------------------------------------------------------------------
// External function
//------------------------------------------------------------------------------
// Function name:     TmCreate
//------------------------------------------------------------------------------
// Function call:     USHORT
//                    TmCreate( PSZ         pszPathMem,
//                              HTM         *htm,
//                              HTM         hModel,
//                              PSZ         pszServer,
//                              PSZ         pszUserID,
//                              PSZ         pszSourceLang,
//                              PSZ         pszDescription,
//                              USHORT      usMsgHandling  )
//------------------------------------------------------------------------------
// Description:       TM interface function to create a TM
//------------------------------------------------------------------------------
// Parameters:        pszPathMem     - (in)  full TM name x:\eqf\mem\mem.tmd
//                    *htm           - (out) TM handle
//                    hModel         - (in)  model handle
//                    pszServer      - (in)  server name or empty string
//                    pszUserID      - (in)  LAN USERID or empty string
//                    pszSourceLang  - (in)  source language or empty string
//                    pszDescription - (in)  TM description or empty string
//                    usMsgHandling  - (in)  message handling parameter
//                                           TRUE:  display error message
//                                           FALSE: display no error message
//------------------------------------------------------------------------------
USHORT
TmCreate( PSZ         pszPathMem,      //(in)  full TM name x:\eqf\mem\mem.tmd
          HTM         *htm,            //(out) TM handle
          HTM         hModel,          //(in)  model handle
          PSZ         pszServer,       //(in)  server name or empty string
          PSZ         pszUserID,       //(in)  LAN USERID or empty string
          PSZ         pszSourceLang,   //(in)  source language or empty string
          PSZ         pszDescription,  //(in)  TM description or empty string
          USHORT      usMsgHandling,   //(in)  message handling parameter
                                       //      TRUE:  display error message
                                       //      FALSE: display no error message
          HWND        hwnd )           //(in)  handle for error messages
{
	return C_TmCreate(pszPathMem, htm, hModel, pszServer, pszUserID, pszSourceLang, pszDescription,
							usMsgHandling, hwnd);
}
USHORT
C_TmCreate( PSZ         pszPathMem,      //(in)  full TM name x:\eqf\mem\mem.tmd
          HTM         *htm,            //(out) TM handle
          HTM         hModel,          //(in)  model handle
          PSZ         pszServer,       //(in)  server name or empty string
          PSZ         pszUserID,       //(in)  LAN USERID or empty string
          PSZ         pszSourceLang,   //(in)  source language or empty string
          PSZ         pszDescription,  //(in)  TM description or empty string
          USHORT      usMsgHandling,   //(in)  message handling parameter
                                       //      TRUE:  display error message
                                       //      FALSE: display no error message
          HWND        hwnd )           //(in)  handle for error messages
{
  PTMX_CREATE_IN   pstCreateIn = NULL;    //pointer to create input structure
  PTMX_CREATE_OUT  pstCreateOut = NULL;   //pointer to create output structure
  BOOL             fOk = TRUE;            //processing flag
  USHORT           usRc = ERROR_NOT_ENOUGH_MEMORY; //function return code

  /********************************************************************/
  /* initialize TM handle                                             */
  /********************************************************************/
  *htm = NULLHANDLE;

  /********************************************************************/
  /* allocate storage for TMX_CREATE_IN and TMX_CREATE_OUT            */
  /********************************************************************/
  fOk = UtlAlloc( (PVOID *) &pstCreateIn, 0L,
                  (LONG)( sizeof( TMX_CREATE_IN ) +
                          sizeof( TMX_CREATE_OUT ) ),
                  FALSE );

  if ( fOk )
  {
    /******************************************************************/
    /* assign memory to pointer pstCreateOut                          */
    /******************************************************************/
    pstCreateOut = (PTMX_CREATE_OUT)(pstCreateIn + 1);

    /******************************************************************/
    /* call function to fill TMC_CREATE_IN structure                  */
    /******************************************************************/
    usRc = NTMFillCreateInStruct( hModel,
                                  pszPathMem,
                                  pszServer,
                                  pszUserID,
                                  pszSourceLang,
                                  pszDescription,
                                  pstCreateIn,
                                  usMsgHandling,
                                  hwnd );
    if ( usRc )
    {
      /****************************************************************/
      /* error from NTMFillCreateInStruct                             */
      /* stop further processing                                      */
      /****************************************************************/
      fOk = FALSE;
    } /* endif */

    if ( fOk )
    {
      /****************************************************************/
      /* call U code to pass TM command to server or handle it local  */
      /****************************************************************/
      
      usRc = TmtXCreate( pstCreateIn, pstCreateOut );      

      if ( !usRc )
      {
        /**************************************************************/
        /* no error,  return pointer to TM CLB as handle              */
        /**************************************************************/
        *htm = (HTM)pstCreateOut->pstTmClb;
      }
      else
      {
        /**************************************************************/
        /* error stop further processing                              */
        /**************************************************************/
        fOk = FALSE;
      } /* endif */
    } /* endif */
  } /* endif */

  /********************************************************************/
  /* if an error occured call MemRcHandling in dependency  of the     */
  /* mesage flag to display an error message                          */
  /********************************************************************/
  if ( !fOk )
  {
    LogMessage2(ERROR, __func__, "::TEMPORARY_COMMENTED in C_TmCreate:: MemRcHandlingHwnd");
#ifdef TEMPORARY_COMMENTED
      usRc = MemRcHandlingHwnd( usRc, pszPathMem, htm, pszServer, hwnd );
      #endif
  } /* endif */

  /********************************************************************/
  /* if memory for TMX_CREATE_IN and TMX_CREATE_OUT was allocated     */
  /* free the memory                                                  */
  /********************************************************************/
  if ( pstCreateIn )
  {
    UtlAlloc( (PVOID *) &pstCreateIn, 0L, 0L, NOMSG );
  } /* endif */

  return usRc;
} /* End of function TmCreate */

//------------------------------------------------------------------------------
// External function
//------------------------------------------------------------------------------
// Function name:     TmOpen
//------------------------------------------------------------------------------
// Function call:     USHORT
//                    TmOpen( PSZ        szMemFullPath,
//                            HTM        *phtm,
//                            USHORT     usAccess,
//                            USHORT     usLocation,
//                            USHORT     usMsgHandling )
//------------------------------------------------------------------------------
// Description:       TM interface function to open a TM
//------------------------------------------------------------------------------
// Parameters:        szMemFullPath  - (in)  full TM name x:\eqf\mem\mem.tmd
//                    *phtm          - (out) TM handle
//                    usAccess       - (in)  access mode: NON_EXCLUSIVE
//                                                        EXCLUSIVE
//                                                        FOR_ORGANIZE
//                    usLocation     - (in)  location:    TM_LOCAL
//                                                        TM_REMOTE
//                                                        TM_LOCAL_REMOTE
//                    usMsgHandling  - (in)  message handling parameter
//                                           TRUE:  display error message
//                                           FALSE: display no error message
//------------------------------------------------------------------------------
USHORT
TmOpen( PSZ        szMemFullPath,      //(in)  full TM name x:\eqf\mem\mem.tmd
        HTM        *phtm,              //(out) TM handle
        USHORT     usAccess,           //(in)  access mode: NON_EXCLUSIVE
                                       //                   EXCLUSIVE
                                       //                   FOR_ORGANIZE
        USHORT     usLocation,         //(in)  location:    TM_LOCAL
                                       //                   TM_REMOTE
                                       //                   TM_LOCAL_REMOTE
        USHORT     usMsgHandling,      //(in)  message handling parameter
                                       //      TRUE:  display error message
                                       //      FALSE: display no error message
        HWND       hwnd )              //(in)  handle for error messages
{
	return C_TmOpen(szMemFullPath,
        phtm,
        usAccess,
        usLocation,
        usMsgHandling,
        hwnd );
}

USHORT
C_TmOpen( PSZ        szMemFullPath,      //(in)  full TM name x:\eqf\mem\mem.tmd
        HTM        *phtm,              //(out) TM handle
        USHORT     usAccess,           //(in)  access mode: NON_EXCLUSIVE
                                       //                   EXCLUSIVE
                                       //                   FOR_ORGANIZE
        USHORT     usLocation,         //(in)  location:    TM_LOCAL
                                       //                   TM_REMOTE
                                       //                   TM_LOCAL_REMOTE
        USHORT     usMsgHandling,      //(in)  message handling parameter
                                       //      TRUE:  display error message
                                       //      FALSE: display no error message
        HWND       hwnd )              //(in)  handle for error messages
{
  USHORT            usRc;              //function return code
  BOOL              fOk;               //process flag
  PTMX_OPEN_IN      pstOpenIn  = NULL; //open input structure
  PTMX_OPEN_OUT     pstOpenOut = NULL; //open output structure
  USHORT            usUserPriviliges;  //returned from UtlGetLANUserID
  PSZ               pszTemp;           //temp ptr for UtlGetFnameFromPath

  DEBUGEVENT( TMOPEN_LOC, FUNCENTRY_EVENT, 0 );

  /********************************************************************/
  /* initialize function return code                                  */
  /********************************************************************/
  usRc = ERROR_NOT_ENOUGH_MEMORY;

  /********************************************************************/
  /* initialize TM handle                                             */
  /********************************************************************/
  *phtm = NULLHANDLE;

  /********************************************************************/
  /* allocate storage for TMX_OPEN_IN and TMX_OPEN_OUT                */
  /********************************************************************/
  fOk = UtlAlloc( (PVOID *) &pstOpenIn, 0L,
                  (LONG)( sizeof( TMX_OPEN_IN ) +
                          sizeof( TMX_OPEN_OUT ) ),
                  FALSE );
  if ( fOk )
  {
    /******************************************************************/
    /* set usRc to NO_ERROR                                           */
    /******************************************************************/
    usRc = NO_ERROR;

    /******************************************************************/
    /* assign memory to pointer pstOpenOut                           */
    /******************************************************************/
    pstOpenOut = (PTMX_OPEN_OUT)(pstOpenIn + 1);
    
    pstOpenIn->stTmOpen.szServer[0] = EOS;
    if ( usLocation != TM_LOCAL )
    {
      LogMessage1(FATAL, "NOT LOCAL TM IS NOT SUPPORTED");
      fOk = false;
    }

    if ( fOk )
    {
      /****************************************************************/
      /* fill the TMX_OPEN_IN structure                               */
      /* stPrefixIn.usLengthInput                                     */
      /* stPrefixIn.usTmCommand                                       */
      /* stTmOpen.szDataName                                          */
      /* stTmOpen.szIndexName                                         */
      /* stTmOpen.szServer                                            */
      /* stTmOpen.szUserID                                            */
      /* stTmOpen.usAccess                                            */
      /* stTmOpen.usThreshold                                         */
      /****************************************************************/
      pstOpenIn->stPrefixIn.usLengthInput = sizeof( TMX_OPEN_IN );
      pstOpenIn->stPrefixIn.usTmCommand = TMC_OPEN;
      strcpy( pstOpenIn->stTmOpen.szDataName, szMemFullPath );
      Utlstrccpy( pstOpenIn->stTmOpen.szIndexName, szMemFullPath, DOT );

      
      strcpy(pstOpenIn->stTmOpen.szIndexName,pstOpenIn->stTmOpen.szDataName);
      char * temp = strrchr(pstOpenIn->stTmOpen.szIndexName,'.');
      strcpy(temp, ".TMI");
    
      temp = strrchr(pstOpenIn->stTmOpen.szDataName,'.');
      strcpy(temp, ".TMD");
      
      pstOpenIn->stTmOpen.szServer[0] = EOS;
      pstOpenIn->stTmOpen.usAccess = usAccess;

      /****************************************************************/
      /* if a source TM should be opened during folder import and it  */
      /* is the source TM which contains the IMPORT path it is not    */
      /* needed to get the threshold from the properties because      */
      /* for this TM only TmExtract calls are used.                   */
      /* For this the threshold is not needed.                        */
      /****************************************************************/
      if ( strstr( szMemFullPath, IMPORTDIR ) == NULL )
      {
        /**************************************************************/
        /* IMPORTPATH not found                                       */
        /* call function to get threshold valur from the TM properties  */
        /****************************************************************/
        if ( (usRc = NTMGetThresholdFromProperties
                       ( szMemFullPath,
                        &pstOpenIn->stTmOpen.usThreshold,
                        usMsgHandling)) != NO_ERROR )
        {
          /**************************************************************/
          /* error from NTMGetThresholdFromProperties                   */
          /* stop further processing                                    */
          /* set usMsgHandling to FALSE because in case of an error     */
          /* the message is displayed by NTMGetThresholdFromProperties  */
          /**************************************************************/
          fOk           = FALSE;
          usMsgHandling = FALSE;
          LogMessage4(ERROR,"Error in C_TmOpen:: NTMGetThresholdFromProperties fails, memName = ", szMemFullPath,", usRC = ", toStr(usRc).c_str());
          DEBUGEVENT( TMOPEN_LOC, STATE_EVENT, 1 );
        } /* endif */
      } /* endif */

      if ( fOk )
      {
        /**************************************************************/
        /* call U code to pass TM command to server or handle it local*/
        /**************************************************************/
        usRc = TmtXOpen ( pstOpenIn, pstOpenOut );

        /**************************************************************/
        /* return pointer to TM CLB as handle                         */
        /* pstOpenOut->pstTmClb is a NULL pointer in error case       */
        /**************************************************************/
        *phtm = pstOpenOut->pstTmClb;
        switch ( usRc )
        {
          //-------------------------------------------------------------------
          case NO_ERROR:
            break;
          //-------------------------------------------------------------------
          case BTREE_CORRUPTED:
          case VERSION_MISMATCH :
            break;
          //-------------------------------------------------------------------
          default:
            /**********************************************************/
            /* set TM handle to NULL means that the TM is closed      */
            /* and stop further processing                            */
            /**********************************************************/
            *phtm = NULLHANDLE;
             fOk = FALSE;
            break;
        } /* endswitch */
      } /* endif */
    } /* endif */

    /******************************************************************/
    /* if memory for TMX_OPEN_IN and TMX_OPEN_OUT was allocated       */
    /* free the memory                                                */
    /******************************************************************/
    if ( pstOpenIn )
    {
      UtlAlloc( (PVOID *) &pstOpenIn, 0L, 0L, NOMSG );
    } /* endif */
  } /* endif */

  /********************************************************************/
  /* if an error occured and message handling flag is set             */
  /* call MemRcHandling to display error message                      */
  /********************************************************************/
  if ( usMsgHandling && usRc )
  {
    /******************************************************************/
    /* display error message                                          */
    /******************************************************************/
    DEBUGEVENT( TMOPEN_LOC, STATE_EVENT, 2 );
    DEBUGEVENT( TMOPEN_LOC, ERROR_EVENT, usRc );
    usRc = MemRcHandlingHwnd( usRc, szMemFullPath, phtm, NULL, hwnd );
    switch ( usRc )
    {
        case BTREE_CORRUPTED:
        case VERSION_MISMATCH :
          if ( *phtm )
          {
             TmClose( *phtm, szMemFullPath, FALSE, 0 );
          } /* endif */
          *phtm = NULLHANDLE;
          break;
      default:
        break;
    } /* endswitch */
  } /* endif */

  if ( usRc != NO_ERROR )
  {
    ERREVENT( TMOPEN_LOC, ERROR_EVENT, usRc );
  } /* endif */

  return usRc;
} /* end of function TmOpen */

//------------------------------------------------------------------------------
// External function
//------------------------------------------------------------------------------
// Function name:     TmClose
//------------------------------------------------------------------------------
// Function call:     USHORT
//                    TmClose( HTM        htm,
//                             PSZ        szMemPath,
//                             USHORT     usMsgHandling )
//------------------------------------------------------------------------------
// Description:       TM interface function to close a TM
//------------------------------------------------------------------------------
// Parameters:        htm           - (in) TM handle returned from open
//                    szMemPath     - (in) full TM name x:\eqf\mem\mem.tmd
//                    usMsgHandling - (in) message handling parameter
//                                         TRUE:  display error message
//                                         FALSE: display no error message
//------------------------------------------------------------------------------
USHORT
TmClose( HTM        htm,               //(in) TM handle returned from open
         PSZ        szMemPath,         //(in) full TM name x:\eqf\mem\mem.tmd
         USHORT     usMsgHandling,     //(in) message handling parameter
                                   //     TRUE:  display error message
                                   //     FALSE: display no error message
         HWND       hwnd )         //(in) handle for error messages
{
	return C_TmClose(htm, szMemPath, usMsgHandling, hwnd);
}
USHORT
C_TmClose( HTM        htm,               //(in) TM handle returned from open
         PSZ        szMemPath,         //(in) full TM name x:\eqf\mem\mem.tmd
         USHORT     usMsgHandling,     //(in) message handling parameter
                                   //     TRUE:  display error message
                                   //     FALSE: display no error message
         HWND       hwnd )         //(in) handle for error messages
{
  USHORT            usRc;               //function return code
  PTMX_CLOSE_IN     pstCloseIn  = NULL; //close input structure
  PTMX_CLOSE_OUT    pstCloseOut = NULL; //close output structure
  BOOL              fOk;                //process flag
  USHORT            usQRc;              //rc from EqfSend2Handler
  SERVERNAME        szServer;           //local var for server name

  ERREVENT( TMCLOSE_LOC, ERROR_EVENT, 0 );

  /********************************************************************/
  /* initialze function return code                                   */
  /********************************************************************/
  usRc = ERROR_NOT_ENOUGH_MEMORY;

  /********************************************************************/
  /* do processing only when a valid TM handle is passed              */
  /********************************************************************/
  if ( htm != NULLHANDLE )
  {
    /******************************************************************/
    /* allocate storage for TMX_CLOSE_IN and TMX_CLOSE_OUT            */
    /******************************************************************/
    fOk = UtlAlloc( (PVOID *) &pstCloseIn, 0L,
                    (LONG)( sizeof( TMX_CLOSE_IN ) +
                            sizeof( TMX_CLOSE_OUT ) ),
                    FALSE );
    if ( fOk )
    {
      /****************************************************************/
      /* assign memory to pointer pstCloseOut                         */
      /****************************************************************/
      pstCloseOut = (PTMX_CLOSE_OUT)(pstCloseIn + 1);

      /****************************************************************/
      /* fill the TMX_CLOSE_IN structure                              */
      /* stPrefixIn.usLengthInput                                     */
      /* stPrefixIn.usTmCommand                                       */
      /* stTmClb                                                      */
      /****************************************************************/
      pstCloseIn->stPrefixIn.usLengthInput = sizeof( TMX_CLOSE_IN );
      pstCloseIn->stPrefixIn.usTmCommand   = TMC_CLOSE;

      /****************************************************************/
      /* call U code to pass TM command to server or handle it local  */
      /****************************************************************/
      usRc = TmtXClose ( (PTMX_CLB)htm, pstCloseIn, pstCloseOut );

      /****************************************************************/
      /* if an error occured call MemRcHandling in dependency of      */
      /* the message flag to display error message                    */
      /****************************************************************/
      if ( usMsgHandling && usRc )
      {
        usRc = MemRcHandlingHwnd( usRc, szMemPath, &htm, NULL, hwnd );
      } /* endif */

      // cleanup
      UtlAlloc( (PVOID *) &pstCloseIn, 0L, 0L, NOMSG );
    } /* endif */
  }
  else
  {
    /******************************************************************/
    /* no valid TM handle was passed (handle is NULL)                 */
    /* handle this as no error                                        */
    /******************************************************************/
    usRc = NO_ERROR;
  } /* endif */

  if ( usRc != NO_ERROR )
  {
    ERREVENT( TMCLOSE_LOC, ERROR_EVENT, usRc );
  } /* endif */

  return usRc;
} /* end of function TmClose */


USHORT
C_TmReplaceW( HTM           htm,            //(in)  TM handle
           PSZ            szMemPath,      //(in)  full TM name x:\eqf\mem\mem
           PTMX_PUT_IN_W  pstPutInW,      //(in)  pointer to put input structure
           PTMX_PUT_OUT_W pstPutOutW,     //(out) pointer to put output structure
           USHORT         usMsgHandling ) //(in)  message handling parameter
                                          //      TRUE:  display error message
                                          //      FALSE: display no error message
{
  return( C_TmReplaceHwndW( htm, szMemPath, pstPutInW, pstPutOutW, usMsgHandling,
                         NULLHANDLE ) );
} /* end of function TmReplace */
USHORT
TmReplaceW( HTM           htm,            //(in)  TM handle
           PSZ            szMemPath,      //(in)  full TM name x:\eqf\mem\mem
           PTMX_PUT_IN_W  pstPutInW,      //(in)  pointer to put input structure
           PTMX_PUT_OUT_W pstPutOutW,     //(out) pointer to put output structure
           USHORT         usMsgHandling ) //(in)  message handling parameter
                                          //      TRUE:  display error message
                                          //      FALSE: display no error message
{
  return( C_TmReplaceW( htm, szMemPath, pstPutInW, pstPutOutW, usMsgHandling ) );
} /* end of function TmReplace */

USHORT
C_TmReplaceHwnd( HTM      htm,            //(in)  TM handle
           PSZ          szMemPath,      //(in)  full TM name x:\eqf\mem\mem
           PTMX_PUT_IN  pstPutIn,       //(in)  pointer to put input structure
           PTMX_PUT_OUT pstPutOut,      //(out) pointer to put output structure
           USHORT       usMsgHandling,  //(in)  message handling parameter
                                        //      TRUE:  display error message
                                        //      FALSE: display no error message
           HWND         hwnd )          //(in)  handle for error messages
{
  USHORT usRc;
  PTMX_PUT_IN_W  pstPutInW;
  PTMX_PUT_OUT_W pstPutOutW;
  ULONG   ulCP = 1L;

  UtlAlloc( (PVOID *) &pstPutInW,  0L, sizeof( TMX_PUT_IN_W ), NOMSG );
  UtlAlloc( (PVOID *) &pstPutOutW, 0L, sizeof( TMX_PUT_OUT_W ), NOMSG );

  // copy structures
  TMX_PUT_IN_ASCII2Unicode( pstPutIn, pstPutInW, ulCP );


  usRc = TmReplaceHwndW( htm, szMemPath,  pstPutInW, pstPutOutW, usMsgHandling, hwnd );
  // copy output structures back
  TMX_PUT_OUT_Unicode2ASCII( pstPutOutW, pstPutOut );

  UtlAlloc( (PVOID *) &pstPutInW,  0L, 0L, NOMSG );
  UtlAlloc( (PVOID *) &pstPutOutW, 0L, 0L, NOMSG );

  return usRc;
}

USHORT
TmReplaceHwndW( HTM       htm,            //(in)  TM handle
           PSZ            szMemPath,      //(in)  full TM name x:\eqf\mem\mem
           PTMX_PUT_IN_W  pstPutIn,       //(in)  pointer to put input structure
           PTMX_PUT_OUT_W pstPutOut,      //(out) pointer to put output structure
           USHORT         usMsgHandling,  //(in)  message handling parameter
                                          //      TRUE:  display error message
                                          //      FALSE: display no error message
           HWND           hwnd )          //(in)  handle for error messages
{
	return C_TmReplaceHwndW(htm,
           szMemPath,
           pstPutIn,
           pstPutOut,
           usMsgHandling,
           hwnd );
}
USHORT
C_TmReplaceHwndW( HTM       htm,            //(in)  TM handle
           PSZ            szMemPath,      //(in)  full TM name x:\eqf\mem\mem
           PTMX_PUT_IN_W  pstPutIn,       //(in)  pointer to put input structure
           PTMX_PUT_OUT_W pstPutOut,      //(out) pointer to put output structure
           USHORT         usMsgHandling,  //(in)  message handling parameter
                                          //      TRUE:  display error message
                                          //      FALSE: display no error message
           HWND           hwnd )          //(in)  handle for error messages
{
  USHORT     usRc;                       //function return code
  USHORT     usQRc;                      //rc from EqfSend2Handler
  SERVERNAME szServer;                   //local var for server name

  DEBUGEVENT( TMREPLACE_LOC, FUNCENTRY_EVENT, 0 );

  /********************************************************************/
  /* fill the TMX_PUT_IN prefix structure                             */
  /* stPrefixIn.usLengthInput                                         */
  /* stPrefixIn.usTmCommand                                           */
  /* the TMX_PUT_IN structure must not be filled it is provided       */
  /* by the caller                                                    */
  /********************************************************************/
  pstPutIn->stPrefixIn.usLengthInput = sizeof( TMX_PUT_IN_W );
  pstPutIn->stPrefixIn.usTmCommand   = TMC_REPLACE;

  /********************************************************************/
  /* call TmtXReplace                                                 */
  /********************************************************************/
  usRc = TmtXReplace ( (PTMX_CLB)htm, pstPutIn, pstPutOut );

  /********************************************************************/
  /* if an error occured call MemRcHandling in dependency of          */
  /* the message flag to display error message                        */
  /********************************************************************/
  if ( usMsgHandling && usRc )
  {
    /**************************************************************/
    /* get either server of TM for the error message or pass on   */
    /* the tagtable name (depending on usRc)                      */
    /**************************************************************/
    if ( usRc == ERROR_TA_ACC_TAGTABLE )
    {
      CHAR szTagTable[MAX_EQF_PATH];
      strcpy(szTagTable, pstPutIn->stTmPut.szTagTable);
      strcat( szTagTable, EXT_OF_FORMAT );
      usRc = MemRcHandlingHwnd( usRc, szMemPath, &htm, szTagTable, hwnd );
    }
    else
    {
     usRc = MemRcHandlingHwnd( usRc, szMemPath, &htm, NULL, hwnd );
    } /* endif */
  } /* endif */

  if ( usRc != NO_ERROR )
  {
    ERREVENT( TMREPLACE_LOC, ERROR_EVENT, usRc );
  } /* endif */

  return usRc;
} /* End of function TmReplace */


USHORT
C_TmGetW(HTM            htm,             //(in)  TM handle
       PSZ            szMemPath,       //(in)  full TM name x:\eqf\mem\mem.tmd
       PTMX_GET_IN_W  pstGetIn,        //(in)  pointer to get input structure
       PTMX_GET_OUT_W pstGetOut,       //(out) pointer to get output structure
       USHORT         usMsgHandling )  //(in)  message handling parameter
                                       //      TRUE:  display error message
                                       //      FALSE: display no error message
{
  USHORT      usRc;                    //U code rc
  USHORT      usQRc;                   //EqfSend2Handler
  SERVERNAME  szServer;                //var for server name
  BOOL        fOk;                     //rc from UtlAlloc
  PSZ_W       pszTempString;           //temp string for conversion of CRLF
  USHORT      usI;                     //index var for for loop

  DEBUGEVENT( TMGET_LOC, FUNCENTRY_EVENT, 0 );

  /********************************************************************/
  /* fill the TMX_GET_IN structure                                    */
  /* stPrefixIn.usLengthInput                                         */
  /* stPrefixIn.usTmCommand                                           */
  /* the TMX_GET_IN structure must not be filled it is provided       */
  /* by the caller                                                    */
  /********************************************************************/
  pstGetIn->stPrefixIn.usLengthInput = sizeof( TMX_GET_IN_W );
  pstGetIn->stPrefixIn.usTmCommand   = TMC_GET;

  /********************************************************************/
  /* call U code to pass TM command to server or handle it local      */
  /********************************************************************/
  PTMX_CLB ptmx = (PTMX_CLB)htm;
  usRc = TmtXGet( ptmx, pstGetIn, pstGetOut );

  if ( (usRc == NO_ERROR) && pstGetOut->usNumMatchesFound )
  {
    /******************************************************************/
    /* convert the output according to convert flag                   */
    /******************************************************************/
    if ( pstGetIn->stTmGet.usConvert != MEM_OUTPUT_ASIS )
    {
      /****************************************************************/
      /* allocate storage for temp string                             */
      /****************************************************************/
      fOk = UtlAlloc( (PVOID *) &pszTempString, 0L,
                      (ULONG)MAX_SEGMENT_SIZE * sizeof(CHAR_W),
                      NOMSG );
      if ( fOk )
      {
        /**************************************************************/
        /* loop over all found matches returned in get out struct     */
        /**************************************************************/
        for ( usI=0 ; usI < pstGetOut->usNumMatchesFound; usI++ )
        {
          /************************************************************/
          /* convert source string                                    */
          /************************************************************/
          LogMessage2(FATAL,__func__,"TEMPORARY_COMMENTED in C_TmGetW::NTMConvertCRLFW");
#ifdef TEMPORARY_COMMENTED
          NTMConvertCRLFW( pstGetOut->stMatchTable[usI].szSource,
                          pszTempString,
                          pstGetIn->stTmGet.usConvert );

          /************************************************************/
          /* convert target string                                    */
          /************************************************************/
          NTMConvertCRLFW( pstGetOut->stMatchTable[usI].szTarget,
                          pszTempString,
                          pstGetIn->stTmGet.usConvert );
          #endif
        } /* endfor */
        /**************************************************************/
        /* free storage for temp string                               */
        /**************************************************************/
        UtlAlloc( (PVOID *) &pszTempString, 0L, 0L, NOMSG );
      }
      else
      {
        usRc = ERROR_NOT_ENOUGH_MEMORY;
      } /* endif */
    } /* endif */
  } /* endif */

  /********************************************************************/
  /* if an error occured call MemRcHandling in dependency of          */
  /* the message flag to display error message                        */
  /********************************************************************/
  if ( usMsgHandling && usRc )
  {
    usRc = MemRcHandling( usRc, szMemPath, &htm, NULL );
  } /* endif */

  if ( usRc != NO_ERROR )
  {
    ERREVENT( TMGET_LOC, ERROR_EVENT, usRc );
  } /* endif */

  return usRc;
} /* End of function TmGet */

USHORT
TmGetW (HTM            htm,           //(in)  TM handle
       PSZ            pszMemPath,    //(in)  full TM name x:\eqf\mem\mem.tmd
       PTMX_GET_IN_W  pstGetIn,      //(in)  pointer to get input structure
       PTMX_GET_OUT_W pstGetOut,     //(out) pointer to get output structure
       USHORT         usMsgHandling )//(in)  message handling parameter
                                     //      TRUE:  display error message
                                     //      FALSE: display no error message
{
	return C_TmGetW(htm,
       pszMemPath,
       pstGetIn,
       pstGetOut,
       usMsgHandling );
}


USHORT
C_TmInfoHwnd( HTM           htm,            //(in)  TM handle
        PSZ           szMemPath,      //(in)  full TM name x:\eqf\mem\mem.tmd
        USHORT        usInfoLevel,    //(in)  information level
                                      //        TMINFO_SIGNATURE
        PTMX_INFO_IN  pstInfoIn,      //(in)  pointer to info input structure
        PTMX_INFO_OUT pstInfoOut,     //(out) pointer to info output structure
        USHORT        usMsgHandling,  //(in)  message handling parameter
                                      //      TRUE:  display error message
                                      //      FALSE: display no error message
        HWND          hwnd )          //(in)  handle for error messages
{
  USHORT      usRc;                   //function return code
  USHORT      usQRc;                  //rc from EqfSend2Handler
  SERVERNAME  szServer;               //local var for server name

  /********************************************************************/
  /* fill the TMX_INFO_IN structure                                   */
  /* stPrefixIn.usLengthInput                                         */
  /* stPrefixIn.usTmCommand                                           */
  /********************************************************************/
  pstInfoIn->stPrefixIn.usLengthInput = sizeof( TMX_INFO_IN );
  pstInfoIn->stPrefixIn.usTmCommand   = TMC_INFO;
  pstInfoIn->usInfoLevel = usInfoLevel;

  /********************************************************************/
  /* call U code to pass TM command to server or handle it local      */
  /********************************************************************/
  LogMessage2(ERROR,__func__, ":: TEMPORARY_COMMENTED temcom_id = 44 usRc = TmtXInfo( (PTMX_CLB)htm, pstInfoOut );");
#ifdef TEMPORARY_COMMENTED
  usRc = TmtXInfo( (PTMX_CLB)htm, pstInfoOut );
  #endif
//usRc = U( htm,
//          (PXIN)pstInfoIn,               // Pointer to input structure
//          (PXOUT)pstInfoOut,
//          NEW_TM );

  if ( usMsgHandling && usRc )
  {
    LogMessage2(ERROR,__func__, ":: TEMPORARY_COMMENTED temcom_id = 45 usRc = MemRcHandlingHwnd( usRc, szMemPath, &htm, NULL, hwnd );");
#ifdef TEMPORARY_COMMENTED
    usRc = MemRcHandlingHwnd( usRc, szMemPath, &htm, NULL, hwnd );
    #endif
  } /* endif */
  return usRc;
} /* End of function TmInfo */


/**********************************************************************/
/**********************************************************************/
/* Internal functions                                                 */
/**********************************************************************/
/**********************************************************************/
//------------------------------------------------------------------------------
// Function name:     NTMFillCreateInStruct
//------------------------------------------------------------------------------
// Function call:     USHORT
//                    NTMFillCreateInStruct( HTM             hModel,
//                                           PSZ             pszPathMem,
//                                           PSZ             pszServer,
//                                           PSZ             pszUserID,
//                                           PSZ             pszSourceLang,
//                                           PSZ             pszDescription,
//                                           PTMX_CREATE_IN  pstCreateIn,
//                                           USHORT          usMsgHandling )
//                                           HWND            hwnd )
//------------------------------------------------------------------------------
// Description:       Fills the TMX_CREATE_IN structure from the passed
//                    parameters or from a model handle.
//------------------------------------------------------------------------------
// Parameters:
//  hModel         - (in)  model handle
//  pszPathMem     - (in)  full TM name x:\eqf\mem\mem.tmd
//  pszServer      - (in)  model handle
//  pszUserID      - (in)  server name or empty str (when no model handle)
//  pszSourceLang  - (in)  LAN USERID or empty str  (when no model handle)
//  pszDescription - (in)  source language or empty str (when no model handle)
//  pstCreateIn    - (in)  TM description or empty str (when no model handle)
//  usMsgHandling  - (in)  message handling parameter
//                         TRUE:  display error message
//                         FALSE: display no error message
//------------------------------------------------------------------------------
// Prerequesits:      htm must be a valid TM handle returned from TmOpen
//                    The TM referenced by htm must be open.
//------------------------------------------------------------------------------
USHORT
NTMFillCreateInStruct( HTM             hModel,
                       PSZ             pszPathMem,
                       PSZ             pszServer,
                       PSZ             pszUserID,
                       PSZ             pszSourceLang,
                       PSZ             pszDescription,
                       PTMX_CREATE_IN  pstCreateIn,
                       USHORT          usMsgHandling,
                       HWND            hwnd )
{
  USHORT        usRc=NO_ERROR;
  USHORT        fOk;
  PTMX_INFO_IN  pstInfoIn;
  PTMX_INFO_OUT pstInfoOut;

  /********************************************************************/
  /* fill prefix of the TMX_CREATE_IN                                 */
  /* prefin.usLenIn     - length of the structure (TMX_CREATE_IN)     */
  /* prefin.usCommand   - the Tm command, here TMC_CREATE             */
  /********************************************************************/
  pstCreateIn->stPrefixIn.usLengthInput = sizeof( TMX_CREATE_IN );
  pstCreateIn->stPrefixIn.usTmCommand  = TMC_CREATE;

  if ( hModel )
  {
    /******************************************************************/
    /* model handle,get data for TMX_CREATE_IN stuc from model handle */
    /******************************************************************/
    /******************************************************************/
    /* initialize rc                                                  */
    /******************************************************************/
     usRc = ERROR_NOT_ENOUGH_MEMORY;

    /******************************************************************/
    /* allocate storage for TMX_INFO_IN and TMX_INFO_OUT              */
    /******************************************************************/
    fOk = (USHORT)UtlAlloc( (PVOID *) &pstInfoIn, 0L,
                    (LONG)( sizeof( TMX_INFO_IN ) +
                            sizeof( TMX_INFO_OUT ) ),
                            FALSE );
    if ( fOk )
    {
      /****************************************************************/
      /* assign memory to pointer pstInfoOut                          */
      /****************************************************************/
      pstInfoOut = (PTMX_INFO_OUT)(pstInfoIn + 1);

      /****************************************************************/
      /* fill prefix of TMX_INFO_IN structure                         */
      /****************************************************************/
      pstInfoIn->stPrefixIn.usLengthInput = sizeof(TMX_INFO_IN);
      pstInfoIn->stPrefixIn.usTmCommand = TMC_INFO;

      /****************************************************************/
      /* call function to get signature record of TM from model handle*/
      /****************************************************************/
      usRc = C_TmInfoHwnd( hModel,
                         pszPathMem,
                         TMINFO_SIGNATURE,
                         pstInfoIn,
                         pstInfoOut,
                         usMsgHandling,
                         hwnd );

      if ( !usRc )
      {
        /****************************************************************/
        /* fill the TMX_CREATE_IN structure from TmInfo ouput           */
        /* szDataName         - TM path and name X:\EQFD\MEM\MEM.TMD    */
        /* sIndexName         - TM path and name X:\EQFD\MEM\MEM.TMI    */
        /* szServer           - server name                             */
        /* szUserID           - LAN userid                              */
        /* szSourceLanguage   - source language name                    */
        /* szDescription      - description text                        */
        /* usThreshold        - threshold for return of fuzzy matches   */
        /* bLangTable         - language table                          */
        /****************************************************************/
        strcpy( pstCreateIn->stTmCreate.szDataName, pszPathMem );

        /**************************************************************/
        /* check if the extension of the passed TM name is a extension*/
        /* for a temporary TM used  by TM organize or the extension   */
        /* of a shared TM                                             */
        /**************************************************************/
        if ( strcmp( strrchr( pszPathMem, '.'), EXT_OF_SHARED_MEM ) == 0 )
        {
          /************************************************************/
          /* TM is a shared one, use "shared" index name              */
          /************************************************************/
          Utlstrccpy ( pstCreateIn->stTmCreate.szIndexName, pszPathMem, DOT );
          strcat( pstCreateIn->stTmCreate.szIndexName, EXT_OF_SHARED_MEMINDEX );
        }
        else if ( !strcmp( strrchr( pszPathMem, '.'), EXT_OF_TMDATA ) )
        {
          /************************************************************/
          /* TM is no temporaray TM, use "normal" index name          */
          /************************************************************/
          Utlstrccpy ( pstCreateIn->stTmCreate.szIndexName, pszPathMem, DOT );
          strcat( pstCreateIn->stTmCreate.szIndexName, EXT_OF_TMINDEX );
        }
        else
        {
          /************************************************************/
          /* TM is a temporary TM, use temporary index name           */
          /************************************************************/
          Utlstrccpy ( pstCreateIn->stTmCreate.szIndexName, pszPathMem, DOT );
          strcat( pstCreateIn->stTmCreate.szIndexName, EXT_OF_TEMP_TMINDEX );
        } /* endif */

        strcpy( pstCreateIn->stTmCreate.szSourceLanguage,
                pstInfoOut->stTmSign.szSourceLanguage );
        strcpy( pstCreateIn->stTmCreate.szDescription,
                pstInfoOut->stTmSign.szDescription );
        pstCreateIn->stTmCreate.usThreshold = pstInfoOut->usThreshold;
      } /* endif */
      /**************************************************************/
      /* free TMX_INFO_IN and TMX_INFO_OUT structure                */
      /**************************************************************/
      UtlAlloc( (PVOID *) &pstInfoIn, 0L, 0L, NOMSG );
    } /* endif */
  }
  else
  {
    /******************************************************************/
    /* no model handle get data for TMX_CREATE_IN stucture from input */
    /******************************************************************/
    /******************************************************************/
    /* fill the TMX_CREATE_IN structure                               */
    /* szDataName         - TM path and name X:\EQFD\MEM\MEM.TMD      */
    /* szIndexName        - TM path and name X:\EQFD\MEM\MEM.TMI      */
    /* szServer           - server name                               */
    /* szUserID           - LAN userid                                */
    /* szSourceLanguage   - source language name                      */
    /* szDescription      - description text                          */
    /* usThreshold        - threshold for return of fuzzy matches     */
    /* bLangTable         - language table                            */
    /******************************************************************/
    strcpy( pstCreateIn->stTmCreate.szDataName,       pszPathMem      );

    /**************************************************************/
    /* check if the extension of the passed TM name is a extension*/
    /* for a temporary TM used  by TM organize                    */
    /**************************************************************/
    if ( strcmp( strrchr( pszPathMem, '.'), EXT_OF_SHARED_MEM ) == 0 )
    {
      /************************************************************/
      /* TM is a shared one, use "shared" index name              */
      /************************************************************/
      LogMessage1(FATAL, "NTMFillCreateInStruct::Lan based shared mem not supported!");
      CopyFilePathReplaceExt(pstCreateIn->stTmCreate.szIndexName, pszPathMem, EXT_OF_SHARED_MEMINDEX);
    }
    else if ( !strcmp( strrchr( pszPathMem, '.'), EXT_OF_TMDATA ) )
    {
      /************************************************************/
      /* TM is no temporaray TM, use "normal" index name          */
      /************************************************************/
      CopyFilePathReplaceExt(pstCreateIn->stTmCreate.szIndexName, pszPathMem, EXT_OF_TMINDEX);
    }
    else
    {
      /************************************************************/
      /* TM is a temporary TM, use temporary index name           */
      /************************************************************/
      CopyFilePathReplaceExt(pstCreateIn->stTmCreate.szIndexName, pszPathMem, EXT_OF_TEMP_TMINDEX);
    } /* endif */

    strcpy( pstCreateIn->stTmCreate.szSourceLanguage, pszSourceLang   );
    strcpy( pstCreateIn->stTmCreate.szDescription,    pszDescription  );
    pstCreateIn->stTmCreate.usThreshold = TM_DEFAULT_THRESHOLD;
  } /* endif */

  return usRc;
} /* end of function NTMFillCreateInStruct */

//------------------------------------------------------------------------------
// Function name:     NTMGetThresholdFromProperties
//------------------------------------------------------------------------------
// Function call:     USHORT
//                    NTMGetThresholdFromProperties( PSZ     pszMemFullPath,
//                                                   PUSHORT pusThreshold,
//                                                   USHORT  usMsgHandling )
//------------------------------------------------------------------------------
// Description:       retrieves the threshold from the TM property file
//------------------------------------------------------------------------------
// Parameters:        pszMemFullPath - (in)  full TM name x:\eqf\mem\mem.tmd
//                    pusThreshold   - (out) threshold retrieved from property
//                    usMsgHandling  - (in)  message handling parameter
//                                            TRUE:  display error message
//                                            FALSE: display no error message
//------------------------------------------------------------------------------
USHORT
NTMGetThresholdFromProperties
  ( PSZ       pszMemFullPath,  //(in)  full TM name x:\eqf\mem\mem.tmd
    PUSHORT   pusThreshold,    //(out) threshold retrieved from property
    USHORT    usMsgHandling )  //(in)  message handling parameter
                               //TRUE:  display error message
                               //FALSE: display no error message
{
  CHAR      szSysPath[MAX_EQF_PATH];      //EQF system path X:\EQF
  szSysPath[0] = '\0';
  PSZ       pszTemp;                      //temp ptr for property name
  CHAR      szPropertyName[MAX_FILESPEC]; //property name TMTEST.MEM
  HPROP     hProp;                        //handle of TM properties
  PPROP_NTM pProp;                        //pointer to TM properties
  EQFINFO   ErrorInfo;                    //rc from OpenProperties
  USHORT    usRc;                         //funtion rc

  /********************************************************************/
  /* get the TM name (w/o ext) from the the full TM path and append   */
  /* the TM property extension                                        */
  /********************************************************************/
  pszTemp = UtlGetFnameFromPath( pszMemFullPath);
  Utlstrccpy( szPropertyName, pszTemp, DOT );
  strcat( szPropertyName, GetPropFileExtension(pszMemFullPath));

  /********************************************************************/
  /* get the EQF system path  X:\EQF                                  */
  /* NTMOpenProperties and therefore OpenProperties needs only the    */
  /* system path and the TM property name with ext                    */
  /********************************************************************/
  properties_get_str(KEY_MEM_DIR, szSysPath, MAX_EQF_PATH);

  /********************************************************************/
  /* open the properties of the TM                                    */
  /********************************************************************/
  usRc = NTMOpenProperties( &hProp,
                            (PVOID *)&pProp,
                            szPropertyName,
                            szSysPath,
                            PROP_ACCESS_READ,
                            usMsgHandling );

  if ( usRc == NO_ERROR || usRc == ERROR_OLD_PROPERTY_FILE )
  {
    /******************************************************************/
    /* if no error, return the threshold from the TM properties       */
    /******************************************************************/
    *pusThreshold = pProp->usThreshold;
    
    CloseProperties( hProp, PROP_QUIT, &ErrorInfo);
    
  } /* endif */

  return usRc;
} /* end of function NTMGetThresholdFromProperties */



VOID  TMX_PUT_IN_ASCII2Unicode( PTMX_PUT_IN pstPutIn, PTMX_PUT_IN_W pstPutInW, ULONG cp )
{
  PTMX_PUT   pstTmPut = &pstPutIn->stTmPut;
  PTMX_PUT_W pstTmPutW= &pstPutInW->stTmPut;

  ASCII2Unicode( pstTmPut->szSource, pstTmPutW->szSource, cp );
  ASCII2Unicode( pstTmPut->szTarget, pstTmPutW->szTarget, cp );

  strcpy( pstTmPutW->szSourceLanguage, pstTmPut->szSourceLanguage );
  strcpy( pstTmPutW->szTargetLanguage, pstTmPut->szTargetLanguage );
  strcpy( pstTmPutW->szAuthorName, pstTmPut->szAuthorName );
  pstTmPutW->usTranslationFlag = pstTmPut->usTranslationFlag;
  strcpy( pstTmPutW->szFileName, pstTmPut->szFileName );
  strcpy( pstTmPutW->szLongName, pstTmPut->szLongName );
  pstTmPutW->ulSourceSegmentId = pstTmPut->usSourceSegmentId;
  strcpy( pstTmPutW->szTagTable, pstTmPut->szTagTable );
  pstTmPutW->lTime = pstTmPut->lTime;

  memcpy( &pstPutInW->stPrefixIn, &pstPutIn->stPrefixIn, sizeof( TMX_PREFIX_IN ));
}


VOID  TMX_PUT_OUT_ASCII2Unicode( PTMX_PUT_OUT pstPutOut, PTMX_PUT_OUT_W pstPutOutW )
{
  memcpy( &pstPutOutW->stPrefixOut, &pstPutOut->stPrefixOut, sizeof( TMX_PREFIX_OUT ));
}

VOID  TMX_PUT_OUT_Unicode2ASCII( PTMX_PUT_OUT_W pstPutOutW, PTMX_PUT_OUT pstPutOut )
{
  memcpy( &pstPutOut->stPrefixOut, &pstPutOutW->stPrefixOut, sizeof( TMX_PREFIX_OUT ));
}
