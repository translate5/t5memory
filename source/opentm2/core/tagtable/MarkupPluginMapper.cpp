/*! \file
	This  source provides a C based function call interface to the
  markup table plugin functionality and provides some helper functions to
  simplify the access to the active markup table plugins
  
	Copyright Notice:

	Copyright (C) 1990-2016, International Business Machines
	Corporation and others. All rights reserved
*/

#include "vector"
#include "../pluginmanager/PluginManager.h"
#include "../pluginmanager/OtmMarkup.h"
#include "../pluginmanager/OtmMarkupPlugin.h"
#include "../utilities/LogWrapper.h"


#define INCL_EQF_TAGTABLE         // tag table and format functions

//#pragma pack( push, TM2StructPacking, 1 )
#include "EQF.H"                  // General .H for EQF
#include "EQFTAG00.H"             // markup table info
//#pragma pack( pop, TM2StructPacking )


// internal functions
BOOL MUMakeCLBListItem( OtmMarkupPlugin *plugin, OtmMarkup *markup, char *pszBuffer, int iBufSize );



/*! \brief Structure for the list of available markup tables
*/
typedef struct _MARKUPENTRY
{
  OtmMarkupPlugin *plugin;
  OtmMarkup *markup;
} MARKUPENTRY, *P_MARKUPENTRY;

 static std::vector<OtmMarkupPlugin *> *pluginList = NULL;



	/*! \brief Initializes the markup table plugin wrapper 
   
   During initialization a list of all available markup table plugins
   and markup table objects is created
	
	*/

void InitMarkupPluginMapper()
{
  OtmMarkupPlugin* curPlugin = NULL;

  // access plugin manager
	PluginManager* thePluginManager = PluginManager::getInstance();

  // iterate through all markup table plugins
  pluginList = new std::vector<OtmMarkupPlugin *>;
  int i = 0;
  do
  {
    i++;
    curPlugin = (OtmMarkupPlugin*) thePluginManager->getPlugin(OtmPlugin::eMarkupType, i );
    if ( curPlugin != NULL ) pluginList->push_back( curPlugin );
  }  while ( curPlugin != NULL ); /* end */     
}


/*! \brief Fills a listbox with markup table names or markup table info

    \param hwndLBox handle of listbox control
    \param pszBuffer buffer for preparation of markup info (only used for MUFILL_CLBITEMS)
    \param eFillType fill mode, either MUFILL_CLBITEMS for column list box items or MUFILL_NAMES for names only
	
*/

// find a markup table object by markup table name

 OtmMarkup *GetMarkupObject( char *pszMarkup, char *pszPlugin )
{
  OtmMarkup *pMarkup = NULL;

  // loop through all markup table plugins 
  for( int i = 0; i < (int)pluginList->size(); i++) {
     OtmMarkupPlugin* curPlugin = (*pluginList)[i];
     if ( ( pszPlugin == NULL ) || 
          ( ! strcasecmp( curPlugin->getName(), pszPlugin ) ) ||
          ( ! strcasecmp( curPlugin->getShortName(), pszPlugin ) ) ) 
     { 
        pMarkup = curPlugin->getMarkup( pszMarkup );
        if ( pMarkup != NULL ) 
        {
           return( pMarkup );
        } 
     }
  }
  return( NULL );
}

// find a markup table plugin object by plugin name

 OtmMarkupPlugin *GetMarkupPluginObject( char *pszPlugin )
{
  OtmMarkup *pMarkup = NULL;

  // loop through all markup table plugins 
  for( int i = 0; i < (int)pluginList->size(); i++) {
     OtmMarkupPlugin* curPlugin = (*pluginList)[i];
     if ( ( ! strcasecmp( curPlugin->getName(), pszPlugin ) ) ||
          ( ! strcasecmp( curPlugin->getShortName(), pszPlugin ) ) ) 
     { 
        return( curPlugin );
     }
  }
  return( NULL );
}

// get the markup table plugin providing a specific markup table 

OtmMarkupPlugin *GetMarkupPlugin( char *pszMarkupName )
{
  // loop through all markup table plugins 
  for( int i = 0; i < (int)pluginList->size(); i++)
  {
    OtmMarkupPlugin* curPlugin = (*pluginList)[i];
    OtmMarkup *pMarkup = curPlugin->getMarkup( pszMarkupName );
    if ( pMarkup != NULL )
    {
      return( curPlugin );
    } /* end */       
  }
  return( NULL );
}

BOOL isMarkupDeletable( char *pszMarkup, char *pszPlugin )
{
  OtmMarkup *markup = GetMarkupObject( pszMarkup, pszPlugin );
  if ( markup != NULL )
  {
    return( markup->isDeletable() );
  } /* end */     
  return( false );
}



BOOL isMarkupImportable( char *pszMarkup, char *pszPlugin )
{
  OtmMarkup *markup = GetMarkupObject( pszMarkup, pszPlugin );
  if ( markup != NULL )
  {
    return( markup->isImportable() );
  } /* end */     
  return( true );  // allow import of new markup tables
}



BOOL isMarkupExportable( char *pszMarkup, char *pszPlugin )
{
  OtmMarkup *markup = GetMarkupObject( pszMarkup, pszPlugin );
  if ( markup != NULL )
  {
    return( markup->isExportable() );
  } /* end */     
  return( false ); 
}



BOOL isMarkupProtected( char *pszMarkup, char *pszPlugin )
{
  OtmMarkup *markup = GetMarkupObject( pszMarkup, pszPlugin );
  if ( markup != NULL )
  {
    return( markup->isProtected() );
  } /* end */     
  return( false ); 
}



// make CLB list box item for a markup table

BOOL TagMakeListItem( PSZ pszMarkup, PSZ pszPlugin, PSZ pszBuffer, int iBufSize )
{
  OtmMarkupPlugin *curPlugin = NULL ;
  PSZ      pMarkup = pszMarkup ;
  PSZ      pPlugin = pszPlugin ;
  int i ;

  if ( strchr( pszMarkup, ':' ) ) {
     strcpy( pszBuffer, pszMarkup ) ;
     pPlugin = pszBuffer ;
     pMarkup = strchr( pPlugin, ':' ) ;
     *pMarkup++ = '\0' ; 
  } 

  OtmMarkup *markup = GetMarkupObject( pMarkup, pPlugin );
  if ( markup != NULL  ) {
     if ( pPlugin ) {
        for( i = 0; i < (int)pluginList->size(); i++) {
           curPlugin = (*pluginList)[i];
           if ( ( ! strcasecmp( curPlugin->getName(), pPlugin ) ) ||
                ( ! strcasecmp( curPlugin->getShortName(), pPlugin ) ) ) { 
              break;
           }
        }
        if ( i >= (int)pluginList->size() ) 
           curPlugin = NULL ;
     }
    return( MUMakeCLBListItem( curPlugin, markup, pszBuffer, iBufSize ) );
  } /* end */     
  return( false );
}


// make CLB list box item for a markup table object
BOOL MUMakeCLBListItem( OtmMarkupPlugin *plugin, OtmMarkup *markup, char *pszBuffer, int iBufSize )
{
  int iUsed = 0;
  int iRemaining = iBufSize;
  *pszBuffer = '\0';

  // object name = plugin name + markup name
  if ( plugin != NULL )
  {
    strcpy( pszBuffer, plugin->getName() );
    strcat( pszBuffer, ":" );
    iUsed = strlen(pszBuffer);
    iRemaining -= iUsed;
  } /* end */     
  iUsed += markup->getName( pszBuffer + iUsed, iBufSize - iUsed ) - 1 ;
  strcpy( pszBuffer + iUsed++, X15_STR );

  // markup name 
  iUsed += markup->getName( pszBuffer + iUsed, iBufSize - iUsed ) - 1;
  strcpy( pszBuffer + iUsed++, X15_STR );

  // short description 
  iUsed += markup->getShortDescription( pszBuffer + iUsed, iBufSize - iUsed ) - 1;
  strcpy( pszBuffer + iUsed++, X15_STR );

  // long description
  iUsed += markup->getLongDescription( pszBuffer + iUsed, iBufSize - iUsed ) - 1;
  strcpy( pszBuffer + iUsed++, X15_STR );

  // version     
  iUsed += markup->getVersion( pszBuffer + iUsed, iBufSize - iUsed ) - 1;
  strcpy( pszBuffer + iUsed++, X15_STR );

  // plugin name 
  if ( plugin != NULL ) {
     strncpy( pszBuffer+iUsed, plugin->getShortName(), iBufSize-iUsed ) ;
     *(pszBuffer+iBufSize-1) = '\0' ;
     iUsed = strlen(pszBuffer) ;
     strcpy( pszBuffer + iUsed++, X15_STR );

     // suppler         
     strncpy( pszBuffer+iUsed, plugin->getSupplier(), iBufSize-iUsed ) ;
     *(pszBuffer+iBufSize-1) = '\0' ;
     iUsed = strlen(pszBuffer) ;
     strcpy( pszBuffer + iUsed++, X15_STR );
  }

  return( true );
}

// get the file name of the markup table file

BOOL MUGetMarkupTableFileName( char *pszMarkup, char *pszPlugin, char *pszBuffer, int iBufSize )
{
   strncpy( pszBuffer, pszMarkup, iBufSize ) ;
   *(pszBuffer+iBufSize-1) = '\0' ;

  OtmMarkup *markup = GetMarkupObject( pszMarkup, pszPlugin );
  if ( markup != NULL )
  {
    markup->getTableFileName( pszBuffer, iBufSize );
    return( true );
  }
  return( false );
}


// get the path of the markup table file

BOOL MUGetMarkupTableFilePath( char *pszMarkup, char *pszPlugin, char *pszBuffer, int iBufSize )
{
  strncpy( pszBuffer, pszMarkup, iBufSize ) ;
  *(pszBuffer+iBufSize-1) = '\0' ;

  if ( pszPlugin != NULL ) {
     for( int i = 0; i < (int)pluginList->size(); i++) {
        OtmMarkupPlugin* curPlugin = (*pluginList)[i];
        if ( ( ! strcasecmp( curPlugin->getName(), pszPlugin ) ) ||
             ( ! strcasecmp( curPlugin->getShortName(), pszPlugin ) ) ) { 
           strncpy( pszBuffer, curPlugin->getTablePath(), iBufSize ) ;
           pszBuffer[iBufSize-strlen(pszMarkup)-6] = NULL ;
           strcat( pszBuffer, "\\" ) ;
           strcat( pszBuffer, pszMarkup ) ;
           strcat( pszBuffer, ".TBL" ) ;
           return( true ) ;
        }
     }
  }
  return( false );
}


// get the file name of the markup table user exit

BOOL MUGetUserExitFileName( char *pszMarkup, char *pszPlugin, char *pszBuffer, int iBufSize )
{
  *pszBuffer = '\0' ;
  OtmMarkup *markup = GetMarkupObject( pszMarkup, pszPlugin );
  if ( markup != NULL )
  {
    return( markup->getUserExitFileName( pszBuffer, iBufSize ) != 0 );
  } /* end */     
  return( false );
}

// get the name of the markup table plugin responsible for the given markup

BOOL MUGetMarkupTablePlugin( char *pszMarkup, char *pszBuffer, int iBufSize )
{
   *pszBuffer = '\0' ;
   iBufSize;

  OtmMarkupPlugin *pMarkupPlugin = GetMarkupPlugin( pszMarkup );
  if ( pMarkupPlugin != NULL )
  {
    strcpy( pszBuffer, pMarkupPlugin->getName() ); 
    return ( true );
  } /* end */     
  return( false );
}


// update the files of a markup table

BOOL MUUpdateMarkupTableFiles( 
       char   *pszMarkupTableName,
       char   *pszPluginName,
       char   *pszShortDescription,
       char   *pszLongDescription,
       char   *pszMarkupTableVersion,
       char   *pszTableFileName,
       char   *pszUserExitFilename,
       char   *pszFileList
)
{
   static char   szBuffer[MAX_LONGFILESPEC]; // buffer for markup names
  BOOL  bReturn = false ;

  if ( ( pszPluginName ) && 
       ( pszMarkupTableName ) ) {

     // loop through all markup table plugins 
     for( int i = 0 ; i < (int)pluginList->size() ; i++ ) {
        OtmMarkupPlugin* curPlugin = (*pluginList)[i];
        if ( ( ! strcmp( curPlugin->getName(), pszPluginName ) ) ||
             ( ! strcmp( curPlugin->getShortName(), pszPluginName ) ) ) {
           int iReturn = curPlugin->updateFiles( pszMarkupTableName,
                         pszShortDescription, pszLongDescription, 
                         pszMarkupTableVersion, pszTableFileName,
                         pszUserExitFilename, pszFileList ) ;
           if ( iReturn != UPDATE_MARKUP_ERROR ) {
              bReturn = true;
       //     OtmMarkup *markup = curPlugin->getMarkup( pszMarkupTableName );
       //     if ( markup ) {
       //        markup->updateInfo( pszMarkupTableName,
       //                            pszShortDescription, pszLongDescription,
       //                            NULL, pszUserExitFilename ) ;
       //     }
           }
        }
     }
  }

  return( bReturn );
}


// delete a markup table 

BOOL MUDeleteMarkupTable( 
       char   *pszMarkupName,
       char   *pszPluginName
)
{
  BOOL  bReturn = false ;

  if ( pszMarkupName ) {

     // loop through all markup table plugins 
     for( int i = 0 ; i < (int)pluginList->size() ; i++ ) {
        OtmMarkupPlugin* curPlugin = (*pluginList)[i];
        OtmMarkup* pMarkup = curPlugin->getMarkup( pszMarkupName );
        if ( ( ( ( pszPluginName ) &&
                 ( ( ! strcmp( curPlugin->getName(), pszPluginName ) ) ||
                   ( ! strcmp( curPlugin->getShortName(), pszPluginName ) ) ) )  ||
               ( pszPluginName == NULL ) ) &&
             ( pMarkup != NULL ) ) {
           if ( pMarkup->isDeletable() ) {
              bReturn = curPlugin->deleteMarkup( pszMarkupName ) ;
           }
           break;
        }
     }
  }

  return( bReturn );
}
