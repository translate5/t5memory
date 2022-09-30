//+----------------------------------------------------------------------------+
//| OtmMemoryService.CPP                                                       |
//+----------------------------------------------------------------------------+
//|Copyright Notice:                                                           |
//|                                                                            |
//|      Copyright (c) 2016, QSoft GmbH. All rights reserved.                  |
//+----------------------------------------------------------------------------+
//| Author: Gerhard Queck                                                      |
//|                                                                            |
//+----------------------------------------------------------------------------+
//| Description: Web Server providing memory services using OpenTM2            |
//+----------------------------------------------------------------------------+
//

#include <time.h>
#include <stdarg.h>
#include <memory>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <functional>
#include <unistd.h>
#include <map>
#include <linux/limits.h>
#include <xercesc/util/PlatformUtils.hpp>
//#include <restbed>
#include "OTMMSJSONFactory.h"
#include "OtmMemoryService.h"
#include "OtmMemoryServiceWorker.h"
#include "EQFSERNO.H"
#include "win_types.h"
#include "config.h"
#include "opentm2/core/utilities/PropertyWrapper.H"
#include "opentm2/core/utilities/FilesystemWrapper.h"
#include "EQF.H"
#include "opentm2/core/utilities/LogWrapper.h"
#include "opentm2/core/utilities/EncodingHelper.h"
using namespace std;
//using namespace restbed;


const char szVersionID[] = "X-OpenTM2-Version";

static Service service;
static std::shared_ptr<restbed::Settings> pSettings = NULL;
static OtmMemoryServiceWorker *pMemService = NULL;
static char szLogFile[PATH_MAX];
static FILE *hfLog = NULL;

void restoreBlanks( std::string &strInOut );
void WriteCrashLog( char *pszLogDir );

// number of entries in the transaction log
#define NUM_OF_TRANSACTENTRIES 50

//  transaction IDs
typedef enum _TRANSACTID 
{
  UNUSED_TRANSACTID = 0, GET_LISTMEM_TRANSACTID, POST_CREATEMEM_TRANSACTID, POST_IMPORT_TRANSACTID,
  POST_FUZZYSEARCH_TRANSACTID, POST_CONCORDANCE_TRANSACTID, POST_UPDATEENTRY_TRANSACTID, POST_DELETEENTRY_TRANSACTID, DELETE_MEMORY_TRANSACTID, GET_MEMORY_TRANSACTID,
  GET_STATUS_TRANSACTID
} TRANSACTID;

// transaction log
typedef struct _TRANSACTLOG
{
  time_t lStartTimeStamp;
  time_t lStopTimeStamp;
  TRANSACTID Id;
  char szMemory[PATH_MAX];
} TRANSACTLOG;

static TRANSACTLOG *pTransActLog = NULL;
constexpr int RequestAdditionalLogLevel = DEBUG;
constexpr int RequestTransactionLogLevel = TRANSACTION;

inline std::string ToString(TRANSACTID id)
{
  const std::map<TRANSACTID,const char*> IdEnumToStringsMap {
        { UNUSED_TRANSACTID, "UNUSED_TRANSACTID" },
        { POST_CREATEMEM_TRANSACTID, "POST_IMPORT_TRANSACTID" },
        { POST_FUZZYSEARCH_TRANSACTID, "POST_FUZZYSEARCH_TRANSACTID" },
        { POST_CONCORDANCE_TRANSACTID, "POST_CONCORDANCE_TRANSACTID" },
        { POST_UPDATEENTRY_TRANSACTID, "POST_UPDATEENTRY_TRANSACTID" },
        { POST_DELETEENTRY_TRANSACTID, "POST_DELETEENTRY_TRANSACTID" },
        { DELETE_MEMORY_TRANSACTID, "DELETE_MEMORY_TRANSACTID" },
        { GET_MEMORY_TRANSACTID, "GET_MEMORY_TRANSACTID" },
        { GET_STATUS_TRANSACTID, "GET_STATUS_TRANSACTID" }

    };
    auto   it  = IdEnumToStringsMap.find(id);
    return it == IdEnumToStringsMap.end() ? "Out of range" : it->second;    
}

void ServiceThread(const signal_handler& sh)
{
  // allocate array for transaction logging
  pTransActLog = new( TRANSACTLOG[NUM_OF_TRANSACTENTRIES] );
  if ( pTransActLog ) memset( pTransActLog, 0, NUM_OF_TRANSACTENTRIES * sizeof( TRANSACTLOG ) );

    service.set_signal_handler(sh.signal, sh.handler);
  // start the service
	service.start(pSettings);
}

void delete_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );
  string strTM = request->get_path_parameter( "id", "" );
  restoreBlanks( strTM );

  LogMessage2(RequestTransactionLogLevel, "processing DELETE MEMORY request, mem = ", strTM.c_str() );

  string strResponseBody;
  //int rc = 200;
  int rc = pMemService->deleteMem( strTM, strResponseBody );

  char version[20];
  properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
  session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );

  LogMessage4(RequestAdditionalLogLevel,"DELETE MEMORY request::Done, , RC=",toStr(rc).c_str(),"; strResponseBody=", strResponseBody.c_str() );
}

void get_memory_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  std::string strAccept = request->get_header( "Accept", "" );
  string strTM = request->get_path_parameter( "id", "" );
  restoreBlanks( strTM );

  LogMessage5(RequestTransactionLogLevel, "processing EXPORT MEMORY request, Accept = \"", strAccept.c_str(), "\"; mem = \"", strTM.c_str(), "\"");

  restbed::Bytes vMemData;
  int rc = pMemService->getMem( strTM, strAccept, vMemData );
  
  char version[20];
  properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
  session->close( rc, vMemData, { { "Content-Length", ::to_string( vMemData.size() ) },{ "Content-Type", strAccept.c_str() },{ szVersionID, version } } );
  LogMessage2(RequestAdditionalLogLevel,"EXPORT memory request::Done, RC = ", toStr(rc).c_str());
}

void get_method_handler(const shared_ptr< Session > session)
{
	const auto request = session->get_request();

  LogMessage(RequestTransactionLogLevel, "processing GET LIST OF MEMORIES request");
  std::string strResponseBody = "Sample text";
  int ret = pMemService->list( strResponseBody );

  char version[20];
  properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
  session->close( OK, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );
  LogMessage4(RequestAdditionalLogLevel, "GET LIST OF MEMORIES done, strResponceBody: \"", strResponseBody.c_str(), "\" RC = ", toStr(OK).c_str());
}

void getStatus_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  string strTM = request->get_path_parameter( "id", "" );
  restoreBlanks( strTM );

  LogMessage3(RequestTransactionLogLevel, "processing GET MEM STATUS request, mem=\"",strTM.c_str() ,"\"");

  string strResponseBody;
  int iRC = pMemService->getStatus( strTM, strResponseBody );

  char version[20];
  properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
  session->close( iRC, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" }, { szVersionID, version } } );
  
} 


void saveAllOpenedTMService_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();
  LogMessage(RequestTransactionLogLevel, "processing saveAllOpenedTMService_method_handler");

  string strResponseBody;
  int iRC = pMemService->saveAllTmOnDisk( strResponseBody );

  char version[20];
  properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
  session->close( iRC, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" }, { szVersionID, version } } );
}

bool IsMemImportInProcess(){
  int memInImportProcess = pMemService->GetMemImportInProcess();
  return memInImportProcess >= 0;
}

void shutdownService_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();
  int iRC;
  string strResponseBody;
   
  {
    if( request->has_query_parameter("dontsave") ){
     LogMessage(RequestTransactionLogLevel, "called shutdownService_method_handler with saving turned off");
      strResponseBody = "{\n    'responce': 'shuting down service without saving tms'\n}";
    }else{
      LogMessage(RequestTransactionLogLevel, "called shutdownService_method_handler with saving turned on");
      saveAllOpenedTMService_method_handler(session);
      //iRC = pMemService->saveAllTmOnDisk( strResponseBody );
    }

    //int iRC = pMemService->shutdownService( strResponseBody );
    //session->close( iRC, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" }, { szVersionID, STR_DRIVER_LEVEL_NUMBER } } );
    //session->close( iRC, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" } } );
  }

  //wait till all import processes would end
  int i = 0;
  while(IsMemImportInProcess() && i<600){
    sleep(1000);
    i++;
  }
  xercesc::XMLPlatformUtils::Terminate();
  StopOtmMemoryService();
  session->close( iRC, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" } } );
}

// replace plus signs in string with blanks
/*void restoreBlanks( std::string &strInOut )
{
  int iLen = strInOut.length();
  for ( int i = 0; i < iLen; i++ )
  {
    if ( strInOut[i] == '+' )
    {
      strInOut[i] = ' ';
    }
  }
}//*/

void postImport_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );

  session->fetch( content_length, []( const shared_ptr< Session >& session, const Bytes& body )
  {
    const auto request = session->get_request();
    string strTM = request->get_path_parameter( "id", "" );
    restoreBlanks( strTM );
    string strInData = string( body.begin(), body.end() );
    string strResponseBody;
    if(CheckLogLevel(RequestTransactionLogLevel)){
      std::string truncatedInput = strInData.size() > 3000 ? strInData.substr(0, 3000) : strInData;
      LogMessage6(RequestTransactionLogLevel, "processing MEM IMPORT request, Memory name = \"", strTM.c_str(), "\"\n Input(truncated) = \n\"", truncatedInput.c_str(), 
      "\"\n content length = ", toStr(body.size()).c_str());
    }

    int rc = pMemService->import( strTM, strInData, strResponseBody );
    
    char version[20];
    properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
    session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );
    
    LogMessage5(RequestAdditionalLogLevel, "MEM IMPORT::Done, RC=", toStr(rc).c_str(),", Output:\n-----\n", strResponseBody.c_str() ,"\n-----\n====\n");
  } );
}

void post_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );

  session->fetch( content_length, []( const shared_ptr< Session >& session, const Bytes& body )
  {
    string strInData = string( body.begin(), body.end() );
    LogMessage4(RequestTransactionLogLevel, "processing CREATE MEM request,",
             //" content type, content type=\"", strType.c_str(),"\" content length = ", toStr(content_length).c_str(), 
            " Input: \"", strInData.c_str(), "\"" );
    string strResponseBody;
    
    int rc = pMemService->createMemory( strInData, strResponseBody );
    
    char version[20];
    properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
    session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );
    
    LogMessage4(RequestAdditionalLogLevel, "CREATE MEM::done, RC=", toStr(rc).c_str(),"; Output: ", strResponseBody.c_str());
  } );
}




void postTagReplacement_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();
  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );

  LogMessage4(RequestAdditionalLogLevel, "processing TAG REPLACEMENT request, content type=\"",strType.c_str(),"\", content length=", toStr( content_length ).c_str() );

  session->fetch( content_length, []( const shared_ptr< Session >& session, const Bytes& body )
  {
    char version[20];
    properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
    string strInData = string( body.begin(), body.end() );
    int rc = 0;
    std::string strResponseBody = pMemService->tagReplacement(strInData, rc );
    session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },
      { "Content-Type", "application/json" },
      { szVersionID, version } } );
    LogMessage5(RequestAdditionalLogLevel,  "Tag replacement::done, RC=",toStr(rc).c_str(),"\nOutput:\n-----\n", strResponseBody.c_str() ,"\n----\n====\n");
  });
}

void postFuzzySearch_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );

  session->fetch( content_length, []( const shared_ptr< Session >& session, const Bytes& body )
  {
    const auto request = session->get_request();
    string strTM = request->get_path_parameter( "id", "" );
    restoreBlanks( strTM );

    string strInData = string( body.begin(), body.end() );
    string strResponseBody = "{}";
    LogMessage5(RequestTransactionLogLevel, "processing FUZZY SEARCH request Memory name = \"", strTM.c_str() ,"\"\nInput:\n-----\n\"",strInData.c_str(),"\"\n----" );
    int rc = pMemService->search( strTM, strInData, strResponseBody );

    char version[20];
    properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
    session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );
    LogMessage5(RequestAdditionalLogLevel,  "FUZZY SEARCH::Done! RC=",toStr(rc).c_str(),"\nOutput:\n-----\n", strResponseBody.c_str() ,"\n----\n====\n");
  } );
}

void postConcordanceSearch_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );

  session->fetch( content_length, []( const shared_ptr< Session >& session, const Bytes& body )
  {
    const auto request = session->get_request();
    string strTM = request->get_path_parameter( "id", "" );
    restoreBlanks( strTM );

    string strInData = string( body.begin(), body.end() );
    string strResponseBody;
    LogMessage6(RequestTransactionLogLevel, "processing CONCORDANCE SEARCH request ", "Memory name = \"", strTM.c_str() ,"\"\nInput:\n-----\n\"",strInData.c_str(),"\"\n----" );
    
    int rc = pMemService->concordanceSearch( strTM, strInData, strResponseBody );
    
    char version[20];
    properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
    session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );
    LogMessage4(RequestAdditionalLogLevel,"CONCORDANCE SEARCH::Done! RC = ", toStr(rc).c_str(), "; Output = ", strResponseBody.c_str());
  } );
}

void postEntry_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );

  session->fetch( content_length, []( const shared_ptr< Session >& session, const Bytes& body )
  {
    const auto request = session->get_request();
    string strTM = request->get_path_parameter( "id", "" );
    restoreBlanks( strTM );

    string strInData = string( body.begin(), body.end() );
    string strResponseBody;

    LogMessage5(RequestTransactionLogLevel, "processing ENTRY UPDATE request, Memory name=\"",strTM.c_str(),"\"\nInput:\n-----\n", strInData.c_str(),"\n----\n" );
    int rc = pMemService->updateEntry( strTM, strInData, strResponseBody );
    
    char version[20];
    properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
    session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );
    
    LogMessage7(RequestAdditionalLogLevel,"ENTRY UPDATE::...Done, RC=",toStr(rc).c_str(),"\nOutput:\n-----\n", strResponseBody.c_str(),"\n----\nFor TM \'",strTM.c_str(),"\'====\n");
  } );
}


void postEntryDelete_method_handler( const shared_ptr< Session > session )
{
  const auto request = session->get_request();

  size_t content_length = request->get_header( "Content-Length", 0 );
  std::string strType = request->get_header( "Content-Type", "" );

  session->fetch( content_length, []( const shared_ptr< Session >& session, const Bytes& body )
  {
    const auto request = session->get_request();
    string strTM = request->get_path_parameter( "id", "" );
    restoreBlanks( strTM );

    string strInData = string( body.begin(), body.end() );
    string strResponseBody;

    LogMessage5(RequestTransactionLogLevel, "processing ENTRY DELETE request, Memory name=\"",strTM.c_str(),"\"\nInput:\n-----\n", strInData.c_str(),"\n----\n" );
    int rc = pMemService->deleteEntry( strTM, strInData, strResponseBody );
    
    char version[20];
    properties_get_str_or_default(KEY_APP_VERSION, version, 20, "");
    session->close( rc, strResponseBody, { { "Content-Length", ::to_string( strResponseBody.length() ) },{ "Content-Type", "application/json" },{ szVersionID, version } } );
    
    LogMessage7(RequestAdditionalLogLevel, "ENTRY DELETE ::Done, RC=",toStr(rc).c_str(),"\nOutput:\n-----\n", strResponseBody.c_str(),"\n----\nFor TM \'",strTM.c_str(),"\'====\n");
  } );
}

bool PrepareProxygenService( char *pszService, unsigned *puiPort ){
  LogMessage(TRANSACTION, "Trying to prepare otm memory service");
  pMemService = OtmMemoryServiceWorker::getInstance();
  if ( pMemService == NULL )
  {
    return FALSE;
  } /* endif */

  {
    char szServiceName[100] = "t5memory";
    char szOtmDirPath[255] ="";
    unsigned int uiPort = 8080;
    unsigned int uiWorkerThreads = 1;
    unsigned int uiTimeOut = 3600;
    unsigned int uiLogLevel = 2;
    unsigned int uiAllowedRAM = 1500; // MB
    unsigned int uiThreshold = 33;

    /* get configuration settings */
    {
        string defOtmDirPath, path = filesystem_get_home_dir();
        defOtmDirPath = path + "/.t5memory/";
        path = defOtmDirPath + "t5memory.conf";
        strncpy(szOtmDirPath, defOtmDirPath.c_str(), 254);

        config conf(path);
        int res = conf.parse();

        if (!res) {
            strncpy(szServiceName,
                conf.get_value("name", "t5memory").c_str(), 100);
            strncpy(szOtmDirPath,
                conf.get_value("otmdir", defOtmDirPath.c_str()).c_str(), 254);    
            uiPort = std::stoi(conf.get_value("port", "8080"));
            uiWorkerThreads = std::stoi(conf.get_value("threads", "10"));
            uiTimeOut = std::stoi(conf.get_value("timeout", "3600"));
            uiLogLevel = std::stoi(conf.get_value("logLevel","2"));
            uiAllowedRAM = std::stoi(conf.get_value(KEY_ALLOWED_RAM,"500"));
            uiThreshold = std::stoi(conf.get_value(KEY_TRIPLES_THRESHOLD, "33"));
        }else{
          LogMessage3(ERROR, __func__, ":: can't open t5memory.conf, path = ", path.c_str());
        }
    }
    
    properties_set_str_anyway(KEY_OTM_DIR, szOtmDirPath);
    properties_set_int_anyway(KEY_ALLOWED_RAM, uiAllowedRAM);// saving in megabytes to avoid int overflow
    properties_set_int_anyway(KEY_TRIPLES_THRESHOLD, uiThreshold);
    std::string memDir = szOtmDirPath;
    memDir += "/MEM/";
    properties_add_str(KEY_MEM_DIR, memDir.c_str());

    //From here we have logging in file turned on
    DesuppressLoggingInFile();

    LogMessage8(TRANSACTION, "PrepareOtmMemoryService::parsed service name = ", szServiceName, "; port = ", toStr(uiPort).c_str(), "; Worker threads = ", toStr(uiWorkerThreads).c_str(),
            "; timeout = ", toStr(uiTimeOut).c_str());
    LogMessage6(TRANSACTION,"PrepareOtmMemoryService:: otm dir = ", szOtmDirPath, "; logLevel = ", toStr(uiLogLevel).c_str(), 
                          "; triples_threshold = ", toStr(uiThreshold));
    SetLogLevel(uiLogLevel);
    // set caller's service name and port fields
    strcpy( pszService, szServiceName );
    *puiPort = uiPort;

    char szValue[150];

    // handler for resource URL w/o memory name
    auto resource = make_shared< Resource >();
    snprintf( szValue, 150, "/%s", szServiceName );
    resource->set_path( szValue );
    resource->set_method_handler( "GET", get_method_handler );

    service.publish( resource );

    LogMessage7(TRANSACTION,"PrepareOtmMemoryService:: done, port/path = :", toStr(uiPort).c_str(),"/", szServiceName,"; Allowed ram = ", toStr(uiAllowedRAM).c_str()," MB");
  }
  return( TRUE );

}

BOOL PrepareOtmMemoryService( char *pszService, unsigned *puiPort )
{
  LogMessage(TRANSACTION, "Trying to prepare otm memory service");
  pMemService = OtmMemoryServiceWorker::getInstance();
  if ( pMemService == NULL )
  {
    return FALSE;
  } /* endif */

  {
    char szServiceName[100] = "t5memory";
    char szOtmDirPath[255] ="";
    unsigned int uiPort = 8080;
    unsigned int uiWorkerThreads = 1;
    unsigned int uiTimeOut = 3600;
    unsigned int uiLogLevel = 2;
    unsigned int uiAllowedRAM = 1500; // MB
    unsigned int uiThreshold = 33;

    /* get configuration settings */
    {
        string defOtmDirPath, path = filesystem_get_home_dir();
        defOtmDirPath = path + "/.t5memory/";
        path = defOtmDirPath + "t5memory.conf";
        strncpy(szOtmDirPath, defOtmDirPath.c_str(), 254);

        config conf(path);
        int res = conf.parse();

        if (!res) {
            strncpy(szServiceName,
                conf.get_value("name", "t5memory").c_str(), 100);
            strncpy(szOtmDirPath,
                conf.get_value("otmdir", defOtmDirPath.c_str()).c_str(), 254);    
            uiPort = std::stoi(conf.get_value("port", "8080"));
            uiWorkerThreads = std::stoi(conf.get_value("threads", "10"));
            uiTimeOut = std::stoi(conf.get_value("timeout", "3600"));
            uiLogLevel = std::stoi(conf.get_value("logLevel","2"));
            uiAllowedRAM = std::stoi(conf.get_value(KEY_ALLOWED_RAM,"500"));
            uiThreshold = std::stoi(conf.get_value(KEY_TRIPLES_THRESHOLD, "33"));
        }else{
          LogMessage3(ERROR, __func__, ":: can't open t5memory.conf, path = ", path.c_str());
        }
    }
    
    properties_set_str_anyway(KEY_OTM_DIR, szOtmDirPath);
    properties_set_int_anyway(KEY_ALLOWED_RAM, uiAllowedRAM);// saving in megabytes to avoid int overflow
    properties_set_int_anyway(KEY_TRIPLES_THRESHOLD, uiThreshold);
    std::string memDir = szOtmDirPath;
    memDir += "/MEM/";
    properties_add_str(KEY_MEM_DIR, memDir.c_str());

    //From here we have logging in file turned on
    DesuppressLoggingInFile();

    LogMessage8(TRANSACTION, "PrepareOtmMemoryService::parsed service name = ", szServiceName, "; port = ", toStr(uiPort).c_str(), "; Worker threads = ", toStr(uiWorkerThreads).c_str(),
            "; timeout = ", toStr(uiTimeOut).c_str());
    LogMessage6(TRANSACTION,"PrepareOtmMemoryService:: otm dir = ", szOtmDirPath, "; logLevel = ", toStr(uiLogLevel).c_str(), 
                          "; triples_threshold = ", toStr(uiThreshold));
    SetLogLevel(uiLogLevel);
    // set caller's service name and port fields
    strcpy( pszService, szServiceName );
    *puiPort = uiPort;

    char szValue[150];

    // handler for resource URL w/o memory name
    auto resource = make_shared< Resource >();
    snprintf( szValue, 150, "/%s", szServiceName );
    resource->set_path( szValue );
    resource->set_method_handler( "GET", get_method_handler );
    resource->set_method_handler( "POST", post_method_handler );
    resource->set_method_handler("PUT", postTagReplacement_method_handler);

    // handler for resource URL w memory name/import
    auto tagReplacement = make_shared< Resource >();
    snprintf( szValue, 150, "/%s_service/tagreplacement", szServiceName );
    tagReplacement->set_path( szValue );
    tagReplacement->set_method_handler( "POST", postTagReplacement_method_handler );
  

    // handler for resource URL w memory name/import
    auto memImport = make_shared< Resource >();
    snprintf( szValue, 150, "/%s/{id: .+}/import", szServiceName );
    memImport->set_path( szValue );
    memImport->set_method_handler( "POST", postImport_method_handler );

    // handler for resource URL w memory name/fuzzysearch
    auto fuzzysearch = make_shared< Resource >();
    snprintf( szValue, 150, "/%s/{id: .+}/fuzzysearch", szServiceName );
    fuzzysearch->set_path( szValue );
    fuzzysearch->set_method_handler( "POST", postFuzzySearch_method_handler );

    // handler for resource URL w memory name/concordancesearch
    auto concordancesearch = make_shared< Resource >();
    snprintf( szValue, 150, "/%s/{id: .+}/concordancesearch", szServiceName );
    concordancesearch->set_path( szValue );
    concordancesearch->set_method_handler( "POST", postConcordanceSearch_method_handler );

    // handler for resource URL w memory name/entry
    auto postEntry = make_shared< Resource >();
    snprintf( szValue, 150, "/%s/{id: .+}/entry", szServiceName );
    postEntry->set_path( szValue );
    postEntry->set_method_handler( "POST", postEntry_method_handler );

    // handler for resource URL w memory name/entry
    auto postEntryDelete = make_shared< Resource >();
    snprintf( szValue, 150, "/%s/{id: .+}/entrydelete", szServiceName );
    postEntryDelete->set_path( szValue );
    postEntryDelete->set_method_handler( "POST", postEntryDelete_method_handler );

    // handler for resource URL w memory name
    auto memname = make_shared< Resource >();
    snprintf( szValue, 150, "/%s/{id: .+}", szServiceName );
    memname->set_path( szValue );
    memname->set_method_handler( "DELETE", delete_method_handler );
    memname->set_method_handler( "GET", get_memory_method_handler );

    // handler for resource URL w memory name/status
    auto getStatus = make_shared< Resource >();
    snprintf( szValue, 150, "/%s/{id: .+}/status", szServiceName );
    getStatus->set_path( szValue );
    getStatus->set_method_handler( "GET", getStatus_method_handler );

    // handler for resource URL service/shutdown
    auto shutdownService = make_shared< Resource >();
    snprintf( szValue, 150, "/%s_service/shutdown", szServiceName );
    shutdownService->set_path( szValue );
    shutdownService->set_method_handler( "GET", shutdownService_method_handler );

    // handler for resource service/save all tms
    auto saveTms = make_shared< Resource >();
    snprintf( szValue, 150, "/%s_service/savetms", szServiceName );
    saveTms->set_path( szValue );
    saveTms->set_method_handler( "GET", saveAllOpenedTMService_method_handler );

    pSettings = make_shared< Settings >();
    pSettings->set_port( (uint16_t)uiPort );
    pSettings->set_worker_limit( uiWorkerThreads );
    pSettings->set_default_header( "Connection", "close" );
    pSettings->set_connection_timeout( std::chrono::seconds( uiTimeOut ) );


    service.publish( resource );
    service.publish( tagReplacement);
    service.publish( shutdownService );
    service.publish( saveTms );
    service.publish( memImport );
    service.publish( fuzzysearch );
    service.publish( concordancesearch );
    service.publish( memname );
    service.publish( postEntry );
    service.publish( getStatus );
    service.publish( postEntryDelete );

    LogMessage7(TRANSACTION,"PrepareOtmMemoryService:: done, port/path = :", toStr(uiPort).c_str(),"/", szServiceName,"; Allowed ram = ", toStr(uiAllowedRAM).c_str()," MB");
  }
  return( TRUE );
}

BOOL StartOtmMemoryService(const signal_handler& sh)
{
    ServiceThread(sh);
    return(TRUE);
}

void StopOtmMemoryService()
{
  service.stop();
  pMemService->closeAll();
  //close log file
  LogStop();
	return;
}

void SetLogFile( FILE *hfLog )
{
  if ( pMemService != NULL ) pMemService->setLogFile( hfLog );
}

// convert time to a string
void MakeDateTimeString( time_t lTime, char chDateDelim, char chDateTimeDelim, char chTimeDelim, char *pszDateTime )
{
  char szBuffer[10];

  tm *pTime = localtime( &lTime );
  strncpy(szBuffer, std::to_string( pTime->tm_year + 1900 ).c_str(), 10);
  memcpy( pszDateTime, szBuffer, 4 );
  pszDateTime += 4;
  if ( chDateDelim != 0 ) *pszDateTime++ = chDateDelim;
  strncpy(szBuffer, std::to_string( pTime->tm_mon + 100 ).c_str(), 10);
  memcpy( pszDateTime, szBuffer + 1, 2 );
  pszDateTime += 2;
  if ( chDateDelim != 0 ) *pszDateTime++ = chDateDelim;
  strncpy(szBuffer, std::to_string( pTime->tm_mday + 100 ).c_str(), 10);
  memcpy( pszDateTime, szBuffer + 1, 2 );
  pszDateTime += 2;
  if ( chDateTimeDelim != 0 ) *pszDateTime++ = chDateTimeDelim;
  strncpy(szBuffer, std::to_string( pTime->tm_hour + 100 ).c_str(), 10);
  memcpy( pszDateTime, szBuffer + 1, 2 );
  pszDateTime += 2;
  if ( chTimeDelim != 0 ) *pszDateTime++ = chTimeDelim;
  strncpy(szBuffer, std::to_string( pTime->tm_min + 100 ).c_str(), 10);
  memcpy( pszDateTime, szBuffer + 1, 2 );
  pszDateTime += 2;
  if ( chTimeDelim != 0 ) *pszDateTime++ = chTimeDelim;
  strncpy(szBuffer, std::to_string( pTime->tm_sec + 100 ).c_str(), 10);
  memcpy( pszDateTime, szBuffer + 1, 2 );
  pszDateTime += 2;
  *pszDateTime = 0;
}

// write crash log
void WriteCrashLog( char *pszLogDir )
{
  static char szLogFile[PATH_MAX];
  time_t lTime = 0;
  time( &lTime );
  strcpy( szLogFile, pszLogDir );
  strcat( szLogFile, "\\OtmMemoryService-Crash-" );
  MakeDateTimeString( lTime, '\0', '-', '\0', szLogFile + strlen( szLogFile ) );
  strcat( szLogFile, ".log" );
  FILE *hfLog = fopen( szLogFile, "w" );
  if ( hfLog )
  {
    fprintf( hfLog, "OtmMemoryService terminated abnormally (unhandled exception)\n\n" );
    
    fclose( hfLog );
  }
}