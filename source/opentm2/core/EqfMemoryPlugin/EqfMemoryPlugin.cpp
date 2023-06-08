/*! \file
	Copyright Notice:

	Copyright (C) 1990-2016, International Business Machines
	Corporation and others. All rights reserved
*/

#include "PluginManager.h"
#include "Property.h"
#include "tm.h"
#include "EQFSETUP.H"
#include "FilesystemHelper.h"
#include "LogWrapper.h"
#include "EQF.H"

#include "string"
#include "vector"
#include <fstream>
#include "requestdata.h"
#include "FilesystemWrapper.h"

// some constant values
static char *pszPluginName = "EqfMemoryPlugin";
static char *pszShortDescription = "TranslationMemoryPlugin";
static char *pszLongDescription	= "This is the standard Translation-Memory implementation";
static char *pszVersion = "1.0";
static char *pszSupplier = "International Business Machines Corporation";
//EqfMemoryPlugin* EqfMemoryPlugin::_instance = NULL;

EqfMemoryPlugin::EqfMemoryPlugin()
{
    pluginType = eTranslationMemoryType;
    name = pszPluginName;
    shortDesc = pszShortDescription;
    longDesc = pszLongDescription;
    version = pszVersion;
    supplier = pszSupplier;
    descrType   = "Local Standard Translation Memory";

    iLastError  = 0;
    pluginType  = OtmPlugin::eTranslationMemoryType;
    usableState = OtmPlugin::eUsable;
    UtlGetCheckedEqfDrives( szSupportedDrives );
}

EqfMemoryPlugin::~EqfMemoryPlugin()
{
}

EqfMemoryPlugin* EqfMemoryPlugin::GetInstance(){
  static EqfMemoryPlugin instance;
  return &instance;
}

const char* EqfMemoryPlugin::getName()
{
	return name.c_str();
}

const char* EqfMemoryPlugin::getShortDescription()
{
	return shortDesc.c_str();
}

const char* EqfMemoryPlugin::getLongDescription()
{
	return longDesc.c_str();
}

const char* EqfMemoryPlugin::getVersion()
{
	return version.c_str();
}

const char* EqfMemoryPlugin::getSupplier()
{
	return supplier.c_str();
}

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
NTMFillCreateInStruct( const char*     pszPathMem,
                       const char*     pszSourceLang,
                       const char*     pszDescription,
                       PTMX_CREATE_IN  pstCreateIn)
{
  USHORT        usRc=NO_ERROR;
  
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
  if ( !strcmp( strrchr( pszPathMem, '.'), EXT_OF_TMDATA ) )
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
  
  return usRc;
} /* end of function NTMFillCreateInStruct */




EqfMemory* EqfMemoryPlugin::openMemoryNew(
  const std::string& memName			 
  //,unsigned short usAccessMode
){
  USHORT usRC = 0;
  // use old memory open code
  //std::string path = FilesystemHelper::GetMemDir() + memName + EXT_OF_TMDATA;
  EqfMemory* pMemory = new EqfMemory(memName);
  if(pMemory){
    usRC = pMemory->OpenX();
  }else{
    usRC = ERROR_NOT_ENOUGH_MEMORY;
  } 
  // create memory object if create function completed successfully
  if ( (usRC != 0) && (usRC != BTREE_CORRUPTED) /*&& (usAccessMode == FOR_ORGANIZE)*/){
    T5LOG(T5ERROR) << "EqfMemoryPlugin::openMemory:: TmOpen fails, fName = "<< memName<< "; error = "<< this->strLastError<<"; iLastError = "<< 
        this->iLastError << "; rc = " << usRC;
    //if ( pMemory != 0 ) 
    //  TmClose( pMemory, NULL,  FALSE,  NULL );
  } /* end */       
  return pMemory;
} /* end */     


/*! \brief Close a memory
  \param pMemory pointer to memory object
*/
int EqfMemoryPlugin::closeMemory(
	EqfMemory *pMemory			 
)
{
  T5LOG(T5ERROR) <<  "unimplemented funtion";
  return( 0 );
}


///*! \brief set description of a memory
//  \param pszName name of the memory
//  \param pszDesc description information
//	\returns 0 if successful or error return code
//*/
int EqfMemoryPlugin::setDescription(const char* pszName, const char* pszDesc)
{
    if(pszName==NULL || pszDesc==NULL)
        return 0;

   std::shared_ptr<EqfMemory>  pMemInfo = this->findMemory( (PSZ)pszName );
    if ( pMemInfo.get() == NULL )
    {
      // no memory found
      handleError( ERROR_MEMORY_NOTFOUND, (PSZ)pszName, NULL, NULL, this->strLastError, this->iLastError );
      return( ERROR_MEMORY_NOTFOUND );
    }

    // firstly change in memory
    int tLen = sizeof(pMemInfo.get()->szDescription)/sizeof(pMemInfo.get()->szDescription[0])-1;
    strncpy( pMemInfo.get()->szDescription, pszDesc, tLen );
    pMemInfo.get()->szDescription[tLen] = '\0';

    // then change in disk
    char szPathMem[512];
    memset(szPathMem, 0, 512);
    
    //UtlMakeEQFPath( szPathMem, NULC, PROPERTY_PATH, NULL );
    Properties::GetInstance()->get_value(KEY_MEM_DIR, szPathMem, 512);
    strcat(szPathMem, "/");
    Utlstrccpy( szPathMem+strlen(szPathMem), UtlGetFnameFromPath( pMemInfo.get()->szFullPath ), DOT );
    strcat( szPathMem, EXT_OF_MEM );

    ULONG ulRead;
    PPROP_NTM pProp = NULL;
    BOOL fOK = UtlLoadFileL( szPathMem, (PVOID*)&pProp, &ulRead, FALSE, FALSE );

    if(!fOK || pProp == NULL)
        return -1;

    int length = sizeof(pProp->stTMSignature.szDescription)/sizeof(pProp->stTMSignature.szDescription[0])-1;
    strncpy(pProp->stTMSignature.szDescription, pszDesc, length);
    pProp->stTMSignature.szDescription[length]='\0';

    int res = UtlWriteFileL( szPathMem, ulRead, (PVOID)pProp, FALSE );

    // relase memory
    UtlAlloc( (PVOID *)&pProp, 0, 0, NOMSG );

    return res;
}

/*! \brief Get the error message for the last error occured

    \param strError reference to a string receiving the error mesage text
  	\returns last error code
*/
int EqfMemoryPlugin::getLastError
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
int EqfMemoryPlugin::getLastError
(
  char *pszError,
  int iBufSize
)
{
  strncpy( pszError, this->strLastError.c_str(), iBufSize );
  return( this->iLastError );
}


int tryStrCpy(char* dest, const char* src, const char* def){
  if(src && strlen(src)){
    strcpy(dest,src);
    return 1;
  }
  else{
    strcpy(dest, def);
    return 2;
  }
  
}

/*! \brief Find memory in our memory list and return pointer to memory info 
  \param pszName name of the memory  
	\returns std::shared_ptr<EqfMemory>  pInfo pointer to memory info or NULL in case of errors
*/
std::shared_ptr<EqfMemory>  EqfMemoryPlugin::findMemory
(
   const char *pszName
)
{
  int idx = findMemoryIndex(pszName);
  if( idx>=0 && idx<((int)m_MemInfoVector.size()) )
  {
      return m_MemInfoVector[idx];
  }
  return nullptr;
}

// return the memory index of the specified memory name
int EqfMemoryPlugin::findMemoryIndex
(
   const char *pszName
)
{
    for ( int i = 0; i < (int)m_MemInfoVector.size(); i++ )
    {
        EqfMemory *  pInfo = (m_MemInfoVector[i]).get();
        if ( strcasecmp( pszName, pInfo->szName) == 0 )
        {
            return i;
        }
    }
  
    return (-1);
}


bool EqfMemoryPlugin::stopPlugin( bool fForce  )
{

  // TODO: check for active objects..
  bool fActiveObjects = false;

  // decline stop if we have active objects
  if ( !fForce && fActiveObjects )
  {
    return( false );
  }

  // TODO: terminate active objects, cleanup, free allocated resources

  // de-register plugin
	PluginManager *pPluginManager = PluginManager::getInstance();
	pPluginManager->deregisterPlugin( (OtmPlugin *)this );

  return( true );
}

//__attribute__((visibility("default")))
USHORT registerPlugins()
{
	PluginManager::eRegRc eRc = PluginManager::eSuccess;
	PluginManager *manager = PluginManager::getInstance();
  
  EqfMemoryPlugin* plugin = EqfMemoryPlugin::GetInstance();
  eRc = manager->registerPlugin((OtmPlugin*) plugin);
  USHORT usRC = (USHORT) eRc;
  return usRC;
}

/*! \brief Private data area for the memory import from data files */
typedef struct _MEMIMPORTFROMFILEDATA
{
  EqfMemory *pInputMemory;             // input memory
  EqfMemory *pOutputMemory;            // output memory
  OtmProposal  Proposal;               // currently processed proposal
  std::string strPropFile;             // property file of the imorted memory
  std::string strDataFile;             // data file of the imorted memory
  std::string strIndexFile;            // index file of the imorted memory
  char  szBuffer[1014];                // general purpose buffer

} MEMIMPORTFROMFILEDATA, *PMEMIMPORTFROMFILEDATA;


/*! \brief Handle a return code from the memory functions and create the approbriate error message text for it
    \param iRC return code from memory function
    \param pszMemName long memory name
    \param pszMarkup markup table name or NULL if not available
    \param pszMemPath fully qualified memory path name or NULL if not available
    \param strLastError reference to string object receiving the message text
    \param iLastError reference to a integer variable receiving the error code
  	\returns original or modified error return code
*/
int EqfMemoryPlugin::handleError( int iRC, char *pszMemName, char *pszMarkup, char *pszMemPath, std::string &strLastError, int &iLastError )
{
  char*          pReplAddr[2];

  if ( iRC == 0 ) return( iRC );

  char *pszErrorTextBuffer = (char *)malloc(8096);
  if ( pszErrorTextBuffer == NULL ) return( iRC );
  pszErrorTextBuffer[0] = '\0';
  
  pReplAddr[0] = pszMemName;

  switch ( iRC )
  {
   case ERROR_TA_ACC_TAGTABLE:
     if (pszMarkup != NULL)
        pReplAddr[0] = pszMarkup;
     else
        strcpy(pReplAddr[0], "n/a");
     UtlGetMsgTxt( ERROR_TA_ACC_TAGTABLE, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case ERROR_SHARING_VIOLATION:
   case BTREE_DICT_LOCKED:
   case BTREE_ENTRY_LOCKED:
   case BTREE_ACCESS_ERROR:
     UtlGetMsgTxt( ERROR_MEM_NOT_ACCESSIBLE, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TMERR_NO_MORE_MEMORY_AVAILABLE:
   case ERROR_NOT_ENOUGH_MEMORY:
   case BTREE_NO_ROOM:
   case BTREE_NO_BUFFER:
     UtlGetMsgTxt( ERROR_STORAGE, pszErrorTextBuffer, 0, NULL );
     break;

   case VERSION_MISMATCH:
   case CORRUPT_VERSION_MISMATCH:
   case ERROR_VERSION_NOT_SUPPORTED:
     UtlGetMsgTxt( ERROR_MEM_VERSION_NOT_SUPPORTED, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case FILE_MIGHT_BE_CORRUPTED:
   case BTREE_CORRUPTED:
   case BTREE_USERDATA:
   case ERROR_OLD_PROPERTY_FILE:
     UtlGetMsgTxt( ITM_TM_NEEDS_ORGANIZE, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case BTREE_DISK_FULL:
   case BTREE_WRITE_ERROR   :
   case DISK_FULL:
     {
       char szDrive[2];
       if ( pszMemPath != NULL )
       {
         szDrive[0] = *pszMemPath;
         szDrive[1] = '\0';
       }
       if (pszMemPath != NULL)
        pReplAddr[0] = szDrive;
       else
        strcpy(pReplAddr[0], "n/a");
       UtlGetMsgTxt( ERROR_DISK_FULL_MSG, pszErrorTextBuffer, 1, pReplAddr );
     }
     break;

   case DB_FULL:
   case BTREE_LOOKUPTABLE_TOO_SMALL:
     UtlGetMsgTxt( ERROR_MEM_DB_FULL, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case FILE_ALREADY_EXISTS:
     UtlGetMsgTxt( ERROR_MEM_NAME_INVALID, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case NOT_REPLACED_OLD_SEGMENT:
     UtlGetMsgTxt( ERROR_MEM_NOT_REPLACED, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TM_FILE_SCREWED_UP:
   case NOT_A_MEMORY_DATABASE:
   case BTREE_ILLEGAL_FILE:
     UtlGetMsgTxt( ERROR_MEM_DESTROYED, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TM_FILE_NOT_FOUND:
   case BTREE_FILE_NOTFOUND:
     UtlGetMsgTxt( ERROR_TM_FILE_NOT_FOUND, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TMERR_TM_OPENED_EXCLUSIVELY:
     UtlGetMsgTxt( ERROR_TM_OPENED_EXCLUSIVELY, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TMERR_PROP_EXIST:
     UtlGetMsgTxt( ERROR_PROP_EXIST, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TMERR_PROP_WRITE_ERROR:
     UtlGetMsgTxt( ERROR_PROP_WRITE, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TM_PROPERTIES_NOT_OPENED:
     UtlGetMsgTxt( ERROR_OPEN_TM_PROPERTIES, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case ERROR_NETWORK_ACCESS_DENIED :
   case BTREE_NETWORK_ACCESS_DENIED:
     UtlGetMsgTxt( ERROR_ACCESS_DENIED_MSG, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case SEGMENT_BUFFER_FULL:
   case BTREE_BUFFER_SMALL:
     UtlGetMsgTxt( ERROR_MEM_SEGMENT_TOO_LARGE, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case ERROR_INTERNAL :                                      
     UtlGetMsgTxt( ERROR_INTERNAL, pszErrorTextBuffer, 0, NULL );
     break;                                                   

   case ERROR_INTERNAL_PARM:
     UtlGetMsgTxt( ERROR_INTERNAL_PARM, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case  BTREE_IN_USE:
     UtlGetMsgTxt( ERROR_MEM_NOT_ACCESSIBLE, pszErrorTextBuffer, 1, pReplAddr );
     break;

   case TMERR_TM_OPENED_SHARED:
   case ERROR_PATH_NOT_FOUND:
   case ERROR_INVALID_DRIVE:
   case BTREE_INVALID_DRIVE :
   default:
     {
       char szError[20];
       sprintf( szError, "%ld", iRC );
       pReplAddr[1] = szError;
       T5LOG(T5ERROR) <<  ":: error " << iRC;
       UtlGetMsgTxt( ERROR_MEM_UNDEFINED, pszErrorTextBuffer, 2, pReplAddr );
     }
 }

 strLastError = pszErrorTextBuffer;
 iLastError = iRC;
 free( pszErrorTextBuffer );

 return( iRC );
}

unsigned short getPluginInfo( POTMPLUGININFO pPluginInfo )
{
  strcpy( pPluginInfo->szName, pszPluginName );
  strcpy( pPluginInfo->szShortDescription, pszShortDescription );
  strcpy( pPluginInfo->szLongDescription, pszLongDescription );
  strcpy( pPluginInfo->szVersion, pszVersion );
  strcpy( pPluginInfo->szSupplier, pszSupplier );
  pPluginInfo->eType = OtmPlugin::eTranslationMemoryType;
  strcpy( pPluginInfo->szDependencies, "" );
  pPluginInfo->iMinOpenTM2Version = -1;
  return( 0 );
}
