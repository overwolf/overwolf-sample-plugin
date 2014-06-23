//////////////////////////////////////////////////////////////
//
// Main plugin entry point implementation -- exports from the 
// plugin library
//
#include <Windows.h>
#include <stddef.h>

#include "npapi.h"
#include "npfunctions.h"

#ifndef HIBYTE
#define HIBYTE(x) ((((uint32_t)(x)) & 0xff00) >> 8)
#endif

NPNetscapeFuncs NPNFuncs;

#ifdef XP_WIN
NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* pFuncs)
{
   if(pFuncs == NULL)
      return NPERR_INVALID_FUNCTABLE_ERROR;

   if(pFuncs->size < (offsetof(NPPluginFuncs, setvalue) + sizeof(void*)))
      return NPERR_INVALID_FUNCTABLE_ERROR;

   pFuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
   pFuncs->newp          = NPP_New;
   pFuncs->destroy       = NPP_Destroy;
   pFuncs->setwindow     = NPP_SetWindow;
   pFuncs->newstream     = NPP_NewStream;
   pFuncs->destroystream = NPP_DestroyStream;
   pFuncs->asfile        = NPP_StreamAsFile;
   pFuncs->writeready    = NPP_WriteReady;
   pFuncs->write         = NPP_Write;
   pFuncs->print         = NPP_Print;
   pFuncs->event         = NPP_HandleEvent;
   pFuncs->urlnotify     = NPP_URLNotify;
   pFuncs->getvalue      = NPP_GetValue;
   pFuncs->setvalue      = NPP_SetValue;

   return NPERR_NO_ERROR;
}
#endif /* XP_WIN */

char *NPP_GetMIMEDescription();

char *
NP_GetMIMEDescription()
{
   return NPP_GetMIMEDescription();
}

NPError
NP_GetValue(void* future, NPPVariable variable, void *value)
{
   return NPP_GetValue((NPP_t *)future, variable, value);
}

NPError OSCALL
NP_Initialize(NPNetscapeFuncs* pFuncs
#ifdef XP_UNIX
              , NPPluginFuncs* pluginFuncs
#endif
              )
{
   if(NULL == pFuncs)
      return NPERR_INVALID_FUNCTABLE_ERROR;

   if(HIBYTE(pFuncs->version) > NP_VERSION_MAJOR)
      return NPERR_INCOMPATIBLE_VERSION_ERROR;

   if(pFuncs->size < sizeof(NPNetscapeFuncs))
      return NPERR_INVALID_FUNCTABLE_ERROR;

   NPNFuncs.size             = pFuncs->size;
   NPNFuncs.version          = pFuncs->version;
   NPNFuncs.geturlnotify     = pFuncs->geturlnotify;
   NPNFuncs.geturl           = pFuncs->geturl;
   NPNFuncs.posturlnotify    = pFuncs->posturlnotify;
   NPNFuncs.posturl          = pFuncs->posturl;
   NPNFuncs.requestread      = pFuncs->requestread;
   NPNFuncs.newstream        = pFuncs->newstream;
   NPNFuncs.write            = pFuncs->write;
   NPNFuncs.destroystream    = pFuncs->destroystream;
   NPNFuncs.status           = pFuncs->status;
   NPNFuncs.uagent           = pFuncs->uagent;
   NPNFuncs.memalloc         = pFuncs->memalloc;
   NPNFuncs.memfree          = pFuncs->memfree;
   NPNFuncs.memflush         = pFuncs->memflush;
   NPNFuncs.reloadplugins    = pFuncs->reloadplugins;
   NPNFuncs.getJavaEnv              = NULL;
   NPNFuncs.getJavaPeer             = NULL;
   NPNFuncs.getvalue         = pFuncs->getvalue;
   NPNFuncs.setvalue         = pFuncs->setvalue;
   NPNFuncs.invalidaterect   = pFuncs->invalidaterect;
   NPNFuncs.invalidateregion = pFuncs->invalidateregion;
   NPNFuncs.forceredraw      = pFuncs->forceredraw;
   NPNFuncs.getstringidentifier     = pFuncs->getstringidentifier;
   NPNFuncs.getstringidentifiers    = pFuncs->getstringidentifiers;
   NPNFuncs.getintidentifier        = pFuncs->getintidentifier;
   NPNFuncs.identifierisstring      = pFuncs->identifierisstring;
   NPNFuncs.utf8fromidentifier      = pFuncs->utf8fromidentifier;
   NPNFuncs.intfromidentifier       = pFuncs->intfromidentifier;
   NPNFuncs.createobject            = pFuncs->createobject;
   NPNFuncs.retainobject            = pFuncs->retainobject;
   NPNFuncs.releaseobject           = pFuncs->releaseobject;
   NPNFuncs.invoke                  = pFuncs->invoke;
   NPNFuncs.invokeDefault           = pFuncs->invokeDefault;
   NPNFuncs.evaluate                = pFuncs->evaluate;
   NPNFuncs.getproperty             = pFuncs->getproperty;
   NPNFuncs.setproperty             = pFuncs->setproperty;
   NPNFuncs.removeproperty          = pFuncs->removeproperty;
   NPNFuncs.hasproperty             = pFuncs->hasproperty;
   NPNFuncs.hasmethod               = pFuncs->hasmethod;
   NPNFuncs.releasevariantvalue     = pFuncs->releasevariantvalue;
   NPNFuncs.setexception            = pFuncs->setexception;

   // new stuff
   NPNFuncs.pluginthreadasynccall   = pFuncs->pluginthreadasynccall;
   NPNFuncs.enumerate               = pFuncs->enumerate;

#ifdef XP_UNIX
  /*
   * Set up the plugin function table that Netscape will use to
   * call us.  Netscape needs to know about our version and size
   * and have a UniversalProcPointer for every function we
   * implement.
   */
  pluginFuncs->version    = (NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR;
  pluginFuncs->size       = sizeof(NPPluginFuncs);
  pluginFuncs->newp       = (NPP_NewProcPtr)(NPP_New);
  pluginFuncs->destroy    = (NPP_DestroyProcPtr)(NPP_Destroy);
  pluginFuncs->setwindow  = (NPP_SetWindowProcPtr)(NPP_SetWindow);
  pluginFuncs->newstream  = (NPP_NewStreamProcPtr)(NPP_NewStream);
  pluginFuncs->destroystream = (NPP_DestroyStreamProcPtr)(NPP_DestroyStream);
  pluginFuncs->asfile     = (NPP_StreamAsFileProcPtr)(NPP_StreamAsFile);
  pluginFuncs->writeready = (NPP_WriteReadyProcPtr)(NPP_WriteReady);
  pluginFuncs->write      = (NPP_WriteProcPtr)(NPP_Write);
  pluginFuncs->print      = (NPP_PrintProcPtr)(NPP_Print);
  pluginFuncs->urlnotify  = (NPP_URLNotifyProcPtr)(NPP_URLNotify);
  pluginFuncs->event      = NULL;
  pluginFuncs->getvalue   = (NPP_GetValueProcPtr)(NPP_GetValue);
  pluginFuncs->javaClass  = NULL;

  NPP_Initialize();
#endif

  return NPERR_NO_ERROR;
}

NPError OSCALL NP_Shutdown()
{
   return NPERR_NO_ERROR;
}
