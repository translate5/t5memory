/*! \brief OTMFUNC.C
	Copyright (c) 1999-2016, International Business Machines Corporation and others. All rights reserved.
*/

#include <time.h>
#define INCL_EQF_FOLDER                // folder functions
#define INCL_EQF_ANALYSIS              // analysis functions
#define INCL_EQF_DLGUTILS              // dialog utilities (for EQFTMI.H!)
#define INCL_EQF_TM                    // general Transl. Memory functions
#define DLLIMPORTRESMOD              // resource module handle imported from DLL

#include "EQF.H"
#include "EQFTOPS.H"
#include "OTMFUNC.H"
#include "EQFFUNCI.H"
#include "EQFSTART.H"                  // for TwbGetCheckProfileData
#include "core/utilities/FilesystemWrapper.h"
#include "core/utilities/FilesystemHelper.h"

#define INCL_EQFMEM_DLGIDAS            // include dialog IDA definitions

#include <EQFTMI.H>                    // Private header file of Translation Memory
#include "EQFSETUP.H"                  // directory names
#include "EQFRPT.H"
#include "EQFSERNO.H"

#include "core/document/InitPlugins.h"
#include "core/pluginmanager/PluginManager.h"    // Add for P403138
#include "core/EqfMemoryPlugin/MemoryFactory.h"
#include "core/utilities/LanguageFactory.H"
#include "core/utilities/PropertyWrapper.H"
#include "core/utilities/LogWrapper.h"
#include "core/utilities/ThreadingWrapper.h"
#include "core/utilities/EncodingHelper.h"
#include "win_types.h"

//#define SESSIONLOG
//#define DEBUGAPI

#ifdef DEBUGAPI
  FILE *hLog = NULL;
  char szLogFile[512];
  BOOL fLog = FALSE;
  int iLogLevel = 0;
  #define EQFAPI_TRIGGER "EQFAPI.TRG"
  #define EQFAPI_LOGFILE "EQFAPI.LOG"
#endif

#ifdef DEBUGAPI
  #define LOGFORCEWRITE() if ( fLog ) { fclose(hLog); hLog = fopen( szLogFile, "a" ); }
#else
  #define LOGFORCEWRITE()
#endif

#ifdef DEBUGAPI
  #define LOGWRITE1( p1 ) { if ( fLog && hLog ) { fprintf( hLog, p1 ); LOGFORCEWRITE(); } }
#else
  #define LOGWRITE1( p1 )
#endif

#ifdef DEBUGAPI
  #define LOGWRITE2( p1, p2 ) { if ( fLog && hLog ) { fprintf( hLog, p1, p2 ); LOGFORCEWRITE(); } }
#else
  #define LOGWRITE2( p1, p2 )
#endif

#ifdef DEBUGAPI
  #define LOGWRITE3( p1, p2, p3 ) { if ( fLog && hLog ) { fprintf( hLog, p1, p2, p3 ); LOGFORCEWRITE(); } }
#else
  #define LOGWRITE3( p1, p2, p3 )
#endif

#ifdef DEBUGAPI
  #define LOGWRITE4( p1, p2, p3, p4 ) { if ( fLog && hLog ) { fprintf( hLog, p1, p2, p3, p4 ); LOGFORCEWRITE(); }}
#else
  #define LOGWRITE4( p1, p2, p3, p4 )
#endif

#ifdef DEBUGAPI
  #define LOGWRITE5( p1, p2, p3, p4, p5 ) { if ( fLog && hLog ) { fprintf( hLog, p1, p2, p3, p4, p5 ); LOGFORCEWRITE(); } }
#else
  #define LOGWRITE5( p1, p2, p3, p4, p5 )
#endif

#ifdef DEBUGAPI
  #define LOGPARMSTRING( name, value ) { if ( fLog && hLog ) { fprintf( hLog, "  %s=\"%s\"\n", name, (value) ? value : "<NULL>" ); LOGFORCEWRITE(); } }
#else
  #define LOGPARMSTRING( name, value )
#endif

#ifdef DEBUGAPI
  #define LOGPARMSTRINGW( name, value ) { if ( fLog && hLog ) { fprintf( hLog, "  %S=\"%s\"\n", name, (value) ? value : "<NULL>" ); LOGFORCEWRITE(); } }
#else
  #define LOGPARMSTRINGW( name, value )
#endif

#ifdef DEBUGAPI
  #define LOGPARMCHAR( name, value ) { if ( fLog && hLog ) { fprintf( hLog, "  %s=\'%c\'\n", name, (value) ? value : ' ' ); LOGFORCEWRITE(); } }
#else
  #define LOGPARMCHAR( name, value )
#endif

#ifdef DEBUGAPI
  #define LOGPARMOPTION( name, value ) { if ( fLog && hLog ) { fprintf( hLog, "  %s=%8.8lX\n", name, value ); LOGFORCEWRITE(); }}
#else
  #define LOGPARMOPTION( name, value )
#endif

#ifdef DEBUGAPI
  #define LOGPARMUSHORT( name, value ) { if ( fLog && hLog ) { fprintf( hLog, "  %s=%u\n", name, value ); LOGFORCEWRITE(); }}
#else
  #define LOGPARMUSHORT( name, value )
#endif

#ifdef DEBUGAPI
  #define LOGPARMLONG( name, value ) { if ( fLog && hLog ) { fprintf( hLog, "  %s=%ld\n", name, value ); LOGFORCEWRITE(); }}
#else
  #define LOGPARMLONG( name, value )
#endif


#ifdef DEBUGAPI
  #define LOGCLOSE() { if ( hLog ) fclose( hLog ); hLog = NULLHANDLE; }
#else
  #define LOGCLOSE()
#endif

// OtmMemoryService
// import a Translation Memory
USHORT EqfImportMem
(
  HSESSION    hSession,                // Eqf session handle
  PSZ         pszMemName,              // name of Translation Memory
  PSZ         pszInFile,               // fully qualified name of input file
  LONG        lOptions,                 // options for Translation Memory import
  PSZ         errorBuff,
  ImportStatusDetails*     pImportData
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area


  // validate session handle
  usRC = FctValidateSession( hSession, &pData );
  
  LogMessage2(INFO, "==EQFImportMem== Memory: ", pszMemName);
  
  if(!pData){
    LogMessage1(WARNING, "EqfImportMem::pData is NULL");
  }

  if ( pData && (pData->fComplete || (pData->sLastFunction != FCT_EQFIMPORTMEM)) )
  {
    LogMessage4(INFO, "InFile = ", pszInFile, ", Options = ", toStr(lOptions).c_str() );
  } /* endif */


  // check sequence of calls
  if ( (usRC == NO_ERROR ) && !(lOptions & COMPLETE_IN_ONE_CALL_OPT) )
  {
    if ( !pData->fComplete && (pData->sLastFunction != FCT_EQFIMPORTMEM) )
    {
      usRC = LASTTASK_INCOMPLETE_RC;
    } /* endif */
  } /* endif */

  // call TM import
  if ( usRC == NO_ERROR )
  {
    LogMessage1(INFO, "EqfImportMem:: call TM import");
    if ( !( lOptions & COMPLETE_IN_ONE_CALL_OPT ) ) 
      pData->sLastFunction = FCT_EQFIMPORTMEM;
    usRC = MemFuncImportMem( pData, pszMemName, pszInFile, NULL, NULL, NULL, NULL, lOptions, pImportData );
    strcpy(errorBuff, pData->szError);
  } /* endif */

  if ( !( lOptions & COMPLETE_IN_ONE_CALL_OPT ) )
  {
    if ( ( usRC == NO_ERROR ) && !pData->fComplete )
    {
      usRC = CONTINUE_RC;
    } /* endif */
  }

  if ( !usRC )
  {
      SetSharingFlag( EQF_REFR_MEMLIST );
  }

  if ( pData && (pData->fComplete || (lOptions & COMPLETE_IN_ONE_CALL_OPT ) ) ) 
    LogMessage2(INFO, "EqfImportMem:: RC=", toStr(usRC).c_str() );

  return( usRC );
} /* end of function EqfImportMem */

// OtmMemoryService
// export a Translation Memory
USHORT EqfExportMem
(
  HSESSION    hSession,                // Eqf session handle
  PSZ         pszMemName,              // name of Translation Memory
  PSZ         pszOutFile,              // fully qualified name of output file
  LONG        lOptions                 // options for Translation Memory export
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area


  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData && (pData->fComplete || (pData->sLastFunction != FCT_EQFEXPORTMEM) || (lOptions & COMPLETE_IN_ONE_CALL_OPT)) )
  {
    LogMessage2(DEBUG, "==EQFExportMem==, Options = ", toStr(lOptions).c_str());
    if(pszMemName){
      LogMessage2(DEBUG,"EqfExportMem:: Memory = ", pszMemName);
    }else{
      LogMessage1(ERROR,"EqfExportMem:: Memory = NULL");
    }

    if(pszOutFile){
      LogMessage2(DEBUG,"EqfExportMem:: Output File = ", pszOutFile);
    }else{
      LogMessage1(ERROR,"EqfExportMem:: Output File = NULL");
    }
  } /* endif */

  // check sequence of calls
  if ( (usRC == NO_ERROR) && !( lOptions & COMPLETE_IN_ONE_CALL_OPT ) )
  {
    if ( !pData->fComplete && (pData->sLastFunction != FCT_EQFEXPORTMEM) )
    {
      usRC = LASTTASK_INCOMPLETE_RC;
    } /* endif */
  } /* endif */

  // call TM export
  if ( usRC == NO_ERROR )
  {
    if ( !( lOptions & COMPLETE_IN_ONE_CALL_OPT ) ) pData->sLastFunction = FCT_EQFEXPORTMEM;
    if(pData->pImportData == nullptr){
      pData->pImportData  = new ImportStatusDetails;
      pData->pImportData->reset();
    }
    usRC = MemFuncExportMem( pData, pszMemName, pszOutFile, lOptions );
  } /* endif */

  if ( !( lOptions & COMPLETE_IN_ONE_CALL_OPT ) && (usRC == NO_ERROR) && !pData->fComplete )
  {
    usRC = CONTINUE_RC;
  } /* endif */

  if ( pData && (pData->fComplete || ( lOptions & COMPLETE_IN_ONE_CALL_OPT ) ) ){
    if(usRC){
      LogMessage2(ERROR , "end of function EqfExportMem with error code::  RC = ", toStr(usRC).c_str() );
    }else{ 
      LogMessage1(DEBUG,"end of function EqfExportMem::success ");
    }
  }
  return( usRC );
} /* end of function EqfExportMem */

// OtmMemoryService
// create a new Translation Memory
USHORT EqfCreateMem
(
  HSESSION      hSession,                // Eqf session handle
  const char*   pszMemName,              // name of new Translation Memory
  const char*   pszDescription,          // description for new Translation Memory or NULL
  const char*   pszSourceLanguage,       // Translation Memory source language
  LONG          lOptions                 // type of new Translation Memory
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  if(CheckLogLevel(DEBUG)){
    char buff[255];
    sprintf(buff, "EqfCreateMem( Memory = %s; Description = %s; Sourcelanguage = %s; Options = %d",
              pszMemName, pszDescription, pszSourceLanguage, lOptions);
    LogMessage1(INFO, buff);
  }

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  // call TM create function
  if ( usRC == NO_ERROR )
  {
    usRC = MemFuncCreateMem( pszMemName, pszDescription, 
                             pszSourceLanguage, lOptions );
    pData->fComplete = TRUE;   // one-shot function are always complete
  } /* endif */

  if ( !usRC )
  {
      SetSharingFlag( EQF_REFR_MEMLIST );
  }

  LogMessage2(INFO, "EqfCreateMem() done ::RC=", toStr(usRC).c_str());

  return( usRC );
} /* end of function EqfCreateMem */

// OtmMemoryService
// delete a Translation Memory
USHORT EqfDeleteMem
(
  HSESSION    hSession,                // Eqf session handle
  PSZ         pszMemName               // Translation Memory being deleted
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  LogMessage2(DEBUG, "==EQFDeleteMem==::memName = ", pszMemName);

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  // call TM delete function
  if ( usRC == NO_ERROR )
  {
    usRC = MemFuncDeleteMem( pszMemName );
    pData->fComplete = TRUE;   // one-shot function are always complete
  }else{
    LogMessage4(ERROR, "Error in EQFDeleteMem::FctValidateSession:: MemName = ", pszMemName, "; RC = ", toStr(usRC).c_str());
  } /* endif */

  if ( !usRC )
  {
    SetSharingFlag( EQF_REFR_MEMLIST );
  }

  LogMessage4(INFO, "End of EQFDeleteMem:: MemName = ", pszMemName, "; RC = ", toStr(usRC).c_str());

  return( usRC );
} /* end of function EqfDeleteMem */

// OtmMemoryService
USHORT EqfStartSession
(
  PHSESSION   phSession                // ptr to callers Eqf session handle variable
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

    if (SetupMAT())
        LogMessage1(ERROR, "Failed to setup property files");

  // allocate internal data area
  UtlAlloc( (PVOID *)&pData, 0L, sizeof(FCTDATA), NOMSG );
  if ( pData != NULL )
  {
    pData->lMagicWord = FCTDATA_IDENTIFIER;
    pData->hwndErrMsg = HWND_FUNCIF;
//    FctBuildCheckSum( pData, &pData->lCheckSum );
    pData->fComplete = TRUE;   // no incomplete function yet
  }
  else
  {
    LogMessage1(ERROR, "EqfStartSession():: Not enought memory for pData"  );

    usRC = ERROR_NOT_ENOUGH_MEMORY;
  } /* endif */

  // initialize utilities
  if ( usRC == NO_ERROR )
  {
    UtlSetUShort( QS_RUNMODE, FUNCCALL_RUNMODE );
    UtlSetUShort( QS_PROGRAMID, NONDDEAPI_PROGID );

    if ( !UtlInitUtils( NULLHANDLE ) )
    {
      usRC = ERROR_READ_SYSTEMPROPERTIES;
    } /* endif */
  } /* endif */

  // get profile data and initialize error handler
  if ( usRC == NO_ERROR )
  {
    BOOL fContinue = TwbGetCheckProfileData( pData->szMsgFile,
                                             pData->szSystemPropPath,
                                             pData->szEqfResFile );

    //  Initialize error handler to allow handling of error messages
    UtlInitError( NULLHANDLE, HWND_FUNCIF, (HWND)&(pData->LastMessage),
                  pData->szMsgFile );

    if ( !fContinue )
    {
      LogMessage1(ERROR, "EqfStartSession():: fContinue is false");
      usRC = 1;
    } /* endif */
  } /* endif */

  // set directory strings and main drive
  if ( usRC == NO_ERROR )
  {
    PPROPSYSTEM  pPropSys = GetSystemPropPtr();

    if ( pPropSys != NULL )
    {
      UtlSetString( QST_PRIMARYDRIVE, pPropSys->szPrimaryDrive );
      UtlSetString( QST_LANDRIVE,     pPropSys->szLanDrive );
      UtlSetString( QST_PROPDIR,      pPropSys->szPropertyPath );
      UtlSetString( QST_CONTROLDIR,   pPropSys->szCtrlPath );
      UtlSetString( QST_PROGRAMDIR,   pPropSys->szProgramPath );
      UtlSetString( QST_DICDIR,       pPropSys->szDicPath );
      UtlSetString( QST_MEMDIR,       pPropSys->szMemPath );
      UtlSetString( QST_TABLEDIR,     pPropSys->szTablePath );
      UtlSetString( QST_LISTDIR,      pPropSys->szListPath );
      UtlSetString( QST_SOURCEDIR,    pPropSys->szDirSourceDoc );
      UtlSetString( QST_SEGSOURCEDIR, pPropSys->szDirSegSourceDoc );
      UtlSetString( QST_SEGTARGETDIR, pPropSys->szDirSegTargetDoc );
      UtlSetString( QST_TARGETDIR,    pPropSys->szDirTargetDoc );
      UtlSetString( QST_DLLDIR,       pPropSys->szDllPath );
      UtlSetString( QST_MSGDIR,       pPropSys->szMsgPath );
      UtlSetString( QST_EXPORTDIR,    pPropSys->szExportPath );
      UtlSetString( QST_BACKUPDIR,    pPropSys->szBackupPath );
      UtlSetString( QST_IMPORTDIR,    pPropSys->szDirImport );
      UtlSetString( QST_COMMEMDIR,    pPropSys->szDirComMem );
      UtlSetString( QST_COMPROPDIR,   pPropSys->szDirComProp );
      UtlSetString( QST_COMDICTDIR,   pPropSys->szDirComDict );
 
      UtlSetString( QST_DIRSEGNOMATCHDIR, "SNOMATCH" );
      UtlSetString( QST_MTLOGPATH,    "MTLOG" );
      UtlSetString( QST_DIRSEGMTDIR, "MT" );
      UtlSetString( QST_DIRSEGRTFDIR, "RTF" );
      UtlSetString( QST_PRTPATH,      pPropSys->szPrtPath );
      if ( pPropSys->szWinPath[0] )
      {
        UtlSetString( QST_WINPATH,    pPropSys->szWinPath );
      }
      else
      {
        UtlSetString( QST_WINPATH,      WINDIR );
      } /* endif */
      if ( pPropSys->szEADataPath[0] )
      {
        UtlSetString( QST_EADATAPATH,   pPropSys->szEADataPath );
      }
      else
      {
        UtlSetString( QST_EADATAPATH,   EADATADIR );
      } /* endif */
      UtlSetString( QST_LOGPATH,           "LOGS" );
      UtlSetString( QST_XLIFFPATH,         "XLIFF" );
      UtlSetString( QST_METADATAPATH,      "METADATA" );
      UtlSetString( QST_JAVAPATH,          "JAVA" );
      UtlSetString( QST_MISCPATH,          "MISC" );

      if ( pPropSys->szPluginPath[0] )
      {
        UtlSetString( QST_PLUGINPATH,   pPropSys->szPluginPath );
      }
      else
      {
        UtlSetString( QST_PLUGINPATH,        "PLUGINS" );
      }
      UtlSetString( QST_ENTITY,            "ENTITY" );
      UtlSetString( QST_REMOVEDDOCDIR,     "REMOVED" );

      UtlSetString( QST_ORGEQFDRIVES, pPropSys->szDriveList );
      UtlSetString( QST_VALIDEQFDRIVES, pPropSys->szDriveList );

      // force a refresh of QST_VALIDEQFDRIVES string
      {
        CHAR  szDriveList[MAX_DRIVELIST];
        UtlGetCheckedEqfDrives( szDriveList );
      }

      // set fuzziness limits
      if ( !pPropSys->lSmallLkupFuzzLevel )  
          pPropSys->lSmallLkupFuzzLevel = 3300;
      UtlSetULong( QL_SMALLLOOKUPFUZZLEVEL,    pPropSys->lSmallLkupFuzzLevel );
      if ( !pPropSys->lMediumLkupFuzzLevel ) 
          pPropSys->lMediumLkupFuzzLevel = 3300;
      UtlSetULong( QL_MEDIUMLOOKUPFUZZLEVEL,   pPropSys->lMediumLkupFuzzLevel );
      if ( !pPropSys->lLargeLkupFuzzLevel )  
          pPropSys->lLargeLkupFuzzLevel = 3300;
      UtlSetULong( QL_LARGELOOKUPFUZZLEVEL,    pPropSys->lLargeLkupFuzzLevel );

      if ( !pPropSys->lSmallFuzzLevel )  
          pPropSys->lSmallFuzzLevel = 3300;
	    UtlSetULong( QL_SMALLFUZZLEVEL,    pPropSys->lSmallFuzzLevel );
	    if ( !pPropSys->lMediumFuzzLevel ) 
          pPropSys->lMediumFuzzLevel = 3300;
	    UtlSetULong( QL_MEDIUMFUZZLEVEL,   pPropSys->lMediumFuzzLevel );
	    if ( !pPropSys->lLargeFuzzLevel )  
          pPropSys->lLargeFuzzLevel = 3300;
      UtlSetULong( QL_LARGEFUZZLEVEL,    pPropSys->lLargeFuzzLevel );

      // set SGML/DITA processing flag
      UtlSetUShort( QS_SGMLDITAPROCESSING, (USHORT)!pPropSys->fNoSgmlDitaProcessing );

      UtlSetUShort( QS_ENTITYPROCESSING, (USHORT)pPropSys->fEntityProcessing );

      UtlSetUShort( QS_MEMIMPMRKUPACTION, (USHORT)pPropSys->usMemImpMrkupAction );

    }
    else
    {
      LogMessage1(ERROR, "EqfStartSession()::ERROR_READ_SYSTEMPROPERTIES");
      // access to system properties failed
      usRC = ERROR_READ_SYSTEMPROPERTIES;
    } /* endif */
  } /* endif */


  // set caller's session handle
  if ( usRC == NO_ERROR )
  {
#ifdef DEBUGAPI
    {
      FILETIME  ftSysTime;
      LARGE_INTEGER liTime;
      LONG lTime = 0;

        iLogLevel = 0;

      
      GetSystemTimeAsFileTime( &ftSysTime );
      memcpy( &liTime, &ftSysTime, sizeof(liTime ) );

      UtlMakeEQFPath( szLogFile, NULC, LOG_PATH, NULL );
      strcat( szLogFile, "\\" );
      //strcat( szLogFile, EQFAPI_LOGFILE );
      sprintf( szLogFile + strlen(szLogFile), "OTMFUNC-%I64d-%ld.log", liTime, (LONG)pData );

      hLog = fopen( szLogFile, "a" ); 
      if ( hLog != NULLHANDLE ) 
      { 
        fLog = TRUE;
        time( &lTime ); 
        fprintf( hLog, "===== EQFAPI Log Started %s", ctime( &lTime ) ); 
      } 
      else
      {
        fLog = FALSE;
      } /* endif */
    }
#endif

  LogMessage1(DEBUG, "==EQFSTARTSESSION==\n  Starting plugins...\n" );


  // initialie plugins
  if ( usRC == NO_ERROR )
  {
    char szPluginPath[MAX_EQF_PATH];
    int errCode = properties_get_str_or_default(KEY_OTM_DIR, szPluginPath, MAX_EQF_PATH,"");

		usRC = InitializePlugins( szPluginPath );    // add return value for P402974
        // Add for P403115;
        if (usRC != PluginManager::ePluginExpired)
        {
            // Add for P403138
            char strParam[1024];
            memset(strParam, 0x00, sizeof(strParam));

            PluginManager* thePluginManager = PluginManager::getInstance();
            if (!thePluginManager->ValidationCheck(strParam))
            {
                usRC = NO_ERROR;
            }
            else
            {
                usRC = ERROR_PLUGIN_INVALID;
                PSZ pszParam = strParam;
                UtlError(ERROR_PLUGIN_INVALID, MB_OK , 1, &pszParam, EQF_WARNING);
            }
            // Add end
        }
        else
        {
            LogMessage1(ERROR, "EqfSessioStart()::usRC = ERROR_PLUGIN_EXPIRED");
            usRC = ERROR_PLUGIN_EXPIRED;
        }
        // Add end
  }

  LogMessage1( INFO,"   ...Plugins have been started\n" );
    {
      char szBuf[10];
      int i = 0;
      //UtlLogStart( "TMSession" );
      LogMessage1(INFO, "TMSession");
      i = _getpid();
      sprintf( szBuf, "%ld", i );
      //UtlLogWriteString( "EqfStartSession: Process ID is %s", szBuf );
      LogMessage2(INFO,"EqfStartSession: Process ID is ", szBuf);
    }
    *phSession = (LONG)pData;
  }
  else
  {
    *phSession = NULLHANDLE;
  } /* endif */

  LogMessage2(INFO, "  RC=", toStr(usRC).c_str() );

  return( usRC );
} /* end of function EqfStartSession */

// OtmMemoryService
USHORT EqfGetLastError
(
  HSESSION    hSession,                // Eqf session handle
  PUSHORT     pusRC,                   // ptr to buffer for last return code
  PSZ         pszMsgBuffer,            // ptr to buffer receiving the message
  USHORT      usBufSize                // size of message buffer in bytes
)
{
  PFCTDATA    pData = NULL;            // ptr to function data area
  USHORT      usRC = NO_ERROR;         // function return code

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( usRC == NO_ERROR )
  {
    *pusRC = (USHORT)pData->LastMessage.sErrNumber;
    strncpy( pszMsgBuffer, pData->LastMessage.chMsgText, usBufSize );
    pszMsgBuffer[usBufSize-1] = EOS;

    pData->LastMessage.sErrNumber = 0;
    pData->LastMessage.chMsgText[0] = EOS;
  } /* endif */

  return( usRC );
} /* end of function EqfGetLastError */

// OtmMemoryService
USHORT EqfGetLastErrorW
(
  HSESSION    hSession,                // Eqf session handle
  PUSHORT     pusRC,                   // ptr to buffer for last return code
  wchar_t    *pszMsgBuffer,            // ptr to buffer receiving the message
  USHORT      usBufSize                // size of message buffer in bytes
)
{
  PFCTDATA    pData = NULL;            // ptr to function data area
  USHORT      usRC = NO_ERROR;         // function return code

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( usRC == NO_ERROR )
  {
    *pusRC = (USHORT)pData->LastMessage.sErrNumber;
    //MultiByteToWideChar( CP_OEMCP, 0, pData->LastMessage.chMsgText, -1, pszMsgBuffer, usBufSize );

    pData->LastMessage.sErrNumber = 0;
    pData->LastMessage.chMsgText[0] = EOS;
  } /* endif */

  return( usRC );
} /* end of function EqfGetLastErrorW */

// FctValidateSession: check and convert a session handle to a FCTDATA pointer
USHORT FctValidateSession
(
  HSESSION    hSession,                // session handle being validated
  PFCTDATA   *ppData                   // address of caller's FCTDATA pointer
)
{
  // convert handle to pointer
  PFCTDATA    pData = (PFCTDATA)hSession;;                   // pointer to FCTDATA area
  USHORT      usRC = NO_ERROR;         // function return code

  // test magic word and checksum
  if ( pData == NULL )
  {
    LogMessage1(ERROR,"FctValidateSession()::ERROR_INVALID_SESSION_HANDLE, pData == NULL");
    usRC = ERROR_INVALID_SESSION_HANDLE;
  }
  else if ( pData->lMagicWord != FCTDATA_IDENTIFIER )
  {
    LogMessage1(ERROR,"FctValidateSession()::ERROR_INVALID_SESSION_HANDLE, pData->lMagicWord != FCTDATA_IDENTIFIER ");
    usRC = ERROR_INVALID_SESSION_HANDLE;
  }
  
  if ( usRC == NO_ERROR )
  {
     *ppData = pData;
  } /* endif */
  LogMessage2(DEBUG, "FctValidateSession() usRC = ", toStr(usRC).c_str());
  return( usRC );
} /* end of function FctValidateSession */

void SetSharingFlag(ULONG ulRefreshFlag)
{

}

// OtmMemoryService
// API function checking the existence of a translation memory
// 
USHORT EqfMemoryExists
(
  HSESSION    hSession,                // Eqf session handle
  PSZ         pszMemoryName            // name of the memory
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  // check if folder exists
  if ( usRC == NO_ERROR )
  {
    if ( (pszMemoryName == NULL) || (*pszMemoryName == EOS) )
    {
      usRC = TA_MANDFOLDER;
      LogMessage4(ERROR, __func__, ":: rc = ", toStr(usRC).c_str(), " EQF_ERROR" );
    }
    else
    {    
      //FilesystemHelper::FileExists(pszMemoryName);
      char fname[MAX_EQF_PATH];
      properties_get_str(KEY_MEM_DIR, fname, MAX_EQF_PATH);
      strcat(fname, pszMemoryName);
      strcat(fname, ".MEM");

      bool exists = !FilesystemHelper::FindFiles(fname).empty();
      if(!exists){
        usRC = -1;
      }
    } /* endif */
  } /* endif */

  return( usRC );
} /* end of function EqfMemoryExists */

// OtmMemoryService
/*! \brief Import a memory using the internal memory files
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemory name of the memory being imported
  \param pszMemoryPackage name of a ZIP archive containing the memory files
  \param lOptions options for searching fuzzy segments
         - OVERWRITE_OPT overwrite any existing memory with the given name
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfImportMemInInternalFormat
(
  HSESSION    hSession, 
  PSZ         pszMemoryName,
  PSZ         pszMemoryPackage,
  LONG        lOptions 
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LOGWRITE1( "==EqfImportMemInInternalFormat==\n" );
    LOGPARMSTRING( "Memory", pszMemoryName );
    LOGPARMSTRING( "Package", pszMemoryPackage );
    LOGPARMOPTION( "Options", lOptions );
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC = MemoryFactory::getInstance()->APIImportMemInInternalFormat( pszMemoryName, pszMemoryPackage, lOptions );
  } /* endif */

  if ( pData )
  {
    LOGWRITE2( "  RC=%u\n", usRC );
  }

  return( usRC );
}

// OtmMemoryService
/*! \brief Export a memory to a ZIP package
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemory name of the memory being exported
  \param pszMemoryPackage name of a new ZIP archive receiving the memory files
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfExportMemInInternalFormat
(
  HSESSION    hSession, 
  PSZ         pszMemoryName,
  PSZ         pszMemoryPackage,
  LONG        lOptions 
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LOGWRITE1( "==EqfExportMemInInternalFormat==\n" );
    LOGPARMSTRING( "Memory", pszMemoryName );
    LOGPARMSTRING( "Package", pszMemoryPackage );
    LOGPARMOPTION( "Options", lOptions );
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC = MemoryFactory::getInstance()->APIExportMemInInternalFormat( pszMemoryName, pszMemoryPackage, lOptions );
  } /* endif */

  if ( pData )
  {
    LOGWRITE2( "  RC=%u\n", usRC );
  }

  return( usRC );
}

// OtmMemoryService
/*! \brief Open the specified translation memory
  \param hSession the session handle returned by the EqfStartSession call
  \param pszMemory name of the memory being opened
  \param plHandle buffer to a long value receiving the handle of the opened memory or -1 in case of failures
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfOpenMem
(
  HSESSION    hSession,
  PSZ         pszMemoryName, 
  LONG        *plHandle,
  LONG        lOptions 
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LogMessage4(INFO,"==EqfOpenMem==, Memory = ", pszMemoryName, "; lOptions = ", toStr(lOptions).c_str());
  }else{
    LogMessage1(ERROR, "Error in EqfOpenMem:: pData == NULL");
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC = MemoryFactory::getInstance()->APIOpenMem( pszMemoryName, plHandle, lOptions );
  }else{
    LogMessage2(ERROR,"EqfOpenMem error in FctValidateSession::EqfOpenMem::RC = ", toStr(usRC).c_str());
  } /* endif */

  LogMessage2(INFO,"EqfOpenMem finished::EqfOpenMem::RC = ", toStr(usRC).c_str());
  
  return( usRC );
}

// OtmMemoryService
/*! \brief Close the translation memory referred by the handle
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfCloseMem
(
  HSESSION    hSession, 
  LONG        lHandle,
  LONG        lOptions 
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LOGWRITE1( "==EqfCloseMem==\n" );
    LOGPARMLONG( "Handle", lHandle );
    LOGPARMOPTION( "Options", lOptions );
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC =  MemoryFactory::getInstance()->APICloseMem( lHandle, lOptions );
  } /* endif */

  if ( pData )
  {
    LOGWRITE2( "  RC=%u\n", usRC );
  }

  return( usRC );
}

/*! \brief Lookup a segment in the memory
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param pSearchKey pointer to a MemProposal structure containing the searched criteria
  \param *piNumOfProposals pointer to the number of requested memory proposals, will be changed on return to the number of proposals found
  \param pProposals pointer to a array of MemProposal structures receiving the search results
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfQueryMem
(
  HSESSION    hSession,    
  LONG        lHandle,          
  PMEMPROPOSAL pSearchKey, 
  int         *piNumOfProposals,
  PMEMPROPOSAL pProposals, 
  LONG        lOptions     
)
{
  PFCTDATA    pData = NULL;            // ptr to function data area
  // validate session handle
  USHORT usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LogMessage4(INFO,"EqfQueryMem:: handle = ", toStr(lHandle).c_str(), "; options = ", toStr(lOptions).c_str());
  }else{
    LogMessage1(ERROR,"ERROR in EqfQueryMem:: pData is null");
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC =  MemoryFactory::getInstance()->APIQueryMem( lHandle, pSearchKey, piNumOfProposals, pProposals, lOptions );
  } /* endif */

  LOGLEVEL logLevel = usRC? ERROR : INFO;
  LogMessage2(logLevel,"End of EqfQueryMem, RC = ", toStr(usRC).c_str());

  return( usRC );
}

// OtmMemoryService
/*! \brief Search the given text string in the memory
\param hSession the session handle returned by the EqfStartSession call
\param lHandle handle of a previously opened memory
\param pszSearchString pointer to the search string (in UTF-16 encoding)
\param pszStartPosition pointer to a buffer (min size = 20 charachters) containing the start position, on completion this buffer is filled with the next search position
\param pProposal pointer to an MemProposal structure receiving the next matching segment
\param lSearchTime max time in milliseconds to search for a matching proposal, 0 for no search time restriction
\param lOptions processing options
SEARCH_IN_SOURCE_OPT  search in source
SEARCH_IN_TARGET_OPT  search in target
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfSearchMem
(
  HSESSION    hSession,
  LONG        lHandle,
  CHAR_W      *pszSearchString,
  const char* pszSrcLang, 
  const char* pszTrgLang,
  PSZ         pszStartPosition,
  PMEMPROPOSAL pProposal,
  LONG        lSearchTime,
  LONG        lOptions
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LogMessage8(INFO, "EqfSearchMem::Handle", toStr(lHandle).c_str(),"; SearchString = ", EncodingHelper::convertToUTF8(pszSearchString).c_str(), "; StartPosition = ", pszStartPosition,"; Options = ", toStr(lOptions).c_str());
  }else{
    LogMessage1(ERROR, "Error in EqfSearchMem:: pData == NULL");
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC =  MemoryFactory::getInstance()->APISearchMem( lHandle, pszSearchString, pszSrcLang, pszTrgLang, pszStartPosition, pProposal, lSearchTime, lOptions );
  } /* endif */

  if ( usRC && usRC != ENDREACHED_RC)//
  {
    if(usRC == TIMEOUT_RC){
      LogMessage2(INFO, "Timeout reached in EqfSearchMem for ", EncodingHelper::convertToUTF8(pszSearchString).c_str() );
    }else{
      LogMessage2(ERROR, "Error in EqfSearchMem::  RC=", toStr(usRC).c_str() );
    }
  }else{
    LogMessage1(INFO, "Success in EqfSearchMem" );
  }

  return( usRC );
}

// OtmMemoryService
/*! \brief Update a segment in the memory
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param pNewProposal pointer to an MemProposal structure containing the segment data
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfUpdateMem
(
  HSESSION    hSession,
  LONG        lHandle, 
  PMEMPROPOSAL pNewProposal,
  LONG        lOptions
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LogMessage5( DEBUG, __func__, ":: Handle = ", toStr(lHandle).c_str(), "; Options = ", toStr(lOptions).c_str() );
  }else{
    LogMessage2( ERROR,__func__,"::pData is nullptr");
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC =  MemoryFactory::getInstance()->APIUpdateMem( lHandle, pNewProposal, lOptions );
  } /* endif */

  auto logLevel = usRC? ERROR : DEBUG;
  LogMessage3(logLevel, __func__, ":: RC = ",toStr(usRC).c_str());

  return( usRC );
}


// OtmMemoryService
/*! \brief Delete a segment in the memory
  \param hSession the session handle returned by the EqfStartSession call
  \param lHandle handle of a previously opened memory
  \param pProposalToDelete pointer to an MemProposal structure containing the segment data
  \param lOptions processing options 
  \returns 0 if successful or an error code in case of failures
*/
USHORT EqfUpdateDeleteMem
(
  HSESSION    hSession,
  LONG        lHandle, 
  PMEMPROPOSAL pProposalToDelete,
  LONG        lOptions,
  char*       errorStr
)
{         
  PFCTDATA    pData = NULL;            // ptr to function data area

  // validate session handle
  USHORT usRC = FctValidateSession( hSession, &pData ); 
  if ( pData )
  {
    LogMessage5( INFO, __func__, ":: Handle = ", toStr(lHandle).c_str(), "; Options = ", toStr(lOptions).c_str() );
  }else{
    LogMessage2( ERROR,__func__,"::pData is nullptr");
  } /* endif */

  // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC = MemoryFactory::getInstance()->APIUpdateDeleteMem( lHandle, pProposalToDelete, lOptions , errorStr);
  } /* endif */

  auto logLevel = usRC && usRC != 6020 ? ERROR : INFO;
  LogMessage3(logLevel, __func__, ":: RC = ",toStr(usRC).c_str());

  return( usRC );
}

// OtmMemoryService
/*! \brief List the name of all memories
\param hSession the session handle returned by the EqfStartSession call
\param pszBuffer pointer to a buffer reiceiving the comma separated list of memory names or NULL to get the required length for the list
\param plLength pointer to a variable containing the size of the buffer area, on return the length of name list is stored in this variable
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfListMem
(
  HSESSION    hSession,
  PSZ         pszBuffer,
  PLONG       plLength
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

                                       // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LOGWRITE1( "==EqfUpdateMem==\n" );
    LOGPARMLONG( "Handle", lHandle );
    LOGPARMOPTION( "Options", lOptions );
  } /* endif */

    // call the memory factory to process the request
  if ( usRC == NO_ERROR )
  {
    usRC =  MemoryFactory::getInstance()->APIListMem( pszBuffer, plLength );
  } /* endif */

  if ( pData )
  {
    LOGWRITE2( "  RC=%u\n", usRC );
  }

  return( usRC );
}

std::vector<std::string> GetListOfLanguagesFromFamily(PSZ pszIsoLang){
  return LanguageFactory::getInstance()->getListOfLanguagesFromTheSameFamily( pszIsoLang );
}

// OtmMemoryService
/*! \brief Get the OpenTM2 language name for a ISO language identifier
\param hSession the session handle returned by the EqfStartSession call
\param pszISOLang pointer to ISO language name (e.g. en-US )
\param pszOpenTM2Lang buffer for the OpenTM2 language name
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetOpenTM2Lang
(
  HSESSION         hSession,
  char*         pszISOLang,
  char*         pszOpenTM2Lang,
  bool*       pfPrefered
)
{
  PFCTDATA    pData = NULL;            // ptr to function data area
                                       // validate session handle
  USHORT usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LogMessage3(INFO, "==EqfGetOpenTM2Lang== :: ", "ISOLang = ", pszISOLang);
  } /* endif */

  if ( (usRC == NO_ERROR ) && (pszISOLang == NULL) ) 
  {
    char*  pszParm = "pointer to ISO language id";
    usRC = DDE_MANDPARAMISSING;
    LogMessage2(ERROR,"EqfGetOpenTM2Lang()::DDE_MANDPARAMISSING, (usRC == NO_ERROR ) && (pszISOLang == NULL), pszParam =" , pszParm);
  } /* endif */

  if ( (usRC == NO_ERROR ) && (pszOpenTM2Lang == NULL) ) 
  {
    char* pszParm = "buffer for OpenTM2 language name";
    usRC = DDE_MANDPARAMISSING;
    LogMessage2(ERROR, "EqfGetOpenTM2Lang()::DDE_MANDPARAMISSING, (usRC == NO_ERROR ) && (pszOpenTM2Lang == NULL), pszParam = ", pszParm);
  } /* endif */


  // use the language factory to process the request
  if ( usRC == NO_ERROR )
  {
    LanguageFactory *pLangFactory = LanguageFactory::getInstance();
    pLangFactory->getOpenTM2NameFromISO( pszISOLang, pszOpenTM2Lang, pfPrefered );
  } /* endif */

  if ( pData )
  {
    LogMessage6(INFO, "EqfGetOpenTM2Lang()::pData != NULL, RC=", toStr(usRC).c_str(),"; pszISOLang = ",pszISOLang,"; pszOpenTM2Lang = ", pszOpenTM2Lang);
  }

  return( usRC );
}

// OtmMemoryService
/*! \brief Get the ISO language identifier for a OpenTM2 language name
\param hSession the session handle returned by the EqfStartSession call
\param pszOpenTM2Lang pointer to the OpenTM2 language name
\param pszISOLang pointer to a buffer for the ISO language identifier
\returns 0 if successful or an error code in case of failures
*/
USHORT EqfGetIsoLang
(
  HSESSION    hSession,
  PSZ         pszOpenTM2Lang,
  PSZ         pszISOLang
)
{
  USHORT      usRC = NO_ERROR;         // function return code
  PFCTDATA    pData = NULL;            // ptr to function data area

                                       // validate session handle
  usRC = FctValidateSession( hSession, &pData );

  if ( pData )
  {
    LOGWRITE1( "==EqfGetIsoTM2Lang==\n" );
    LOGPARMSTRING( "OpenTM2Lang", pszOpenTM2Language );
  } /* endif */

  if ( (usRC == NO_ERROR ) && (pszOpenTM2Lang == NULL) ) 
  {
    PSZ pszParm = "pointer to OpenTM2 language name";
    LogMessage3(ERROR, __func__, ":: DDE_MANDPARAMISSING ::", pszParm);
    usRC = DDE_MANDPARAMISSING;
  } /* endif */

  if ( (usRC == NO_ERROR ) && (pszOpenTM2Lang == NULL) ) 
  {
    PSZ pszParm = "buffer for ISO language id";
    LogMessage3(ERROR, __func__, ":: DDE_MANDPARAMISSING :: ", pszParm);
    usRC = DDE_MANDPARAMISSING;
  } /* endif */


  // use the language factory to process the request
  if ( usRC == NO_ERROR )
  {
    LanguageFactory *pLangFactory = LanguageFactory::getInstance();
    pLangFactory->getISOName( pszOpenTM2Lang, pszISOLang );
  } /* endif */

  if ( pData )
  {
    LOGWRITE2( "  RC=%u\n", usRC );
  }

  return( usRC );
}
