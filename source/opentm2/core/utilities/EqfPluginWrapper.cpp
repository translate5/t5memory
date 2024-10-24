#include "EqfPluginWrapper.h"
#include "EQF.H"
#include "PropertyWrapper.H"

void EqfPluginWrapper::init(){

}

void EqfPluginWrapper::deinit(){

}

USHORT EqfPluginWrapper::MemExportStart     (PLONG plHandle, char*  pszOutFile, PMEMEXPIMPINFO pMemInfo ){
    return EXTMEMEXPORTSTART(plHandle, pszOutFile, pMemInfo);   
}

USHORT EqfPluginWrapper::MemExportProcess   (LONG plHandle, PMEMEXPIMPSEG pSeg){
    return EXTMEMEXPORTPROCESS(plHandle, pSeg);
}

USHORT EqfPluginWrapper::MemExportEnd       (LONG plHandle  ){
    return EXTMEMEXPORTEND(plHandle);
}

USHORT EqfPluginWrapper::MemImportStart     (PLONG plHandle,  PSZ pszInFile, PMEMEXPIMPINFO pMemInfo ){
    return EXTMEMIMPORTSTART(plHandle, pszInFile, pMemInfo);
}

USHORT EqfPluginWrapper::MemImportProcess   (LONG plHandle,  PFN_MEMINSERTSEGMENT pfnInsertSegment, LONG lMemHandle, PLONG lProgress ){
    return EXTMEMIMPORTPROCESS(plHandle, pfnInsertSegment, lMemHandle, lProgress);
}

USHORT EqfPluginWrapper::MemImportEnd       (LONG plHandle ){
    return EXTMEMIMPORTEND(plHandle);
}

