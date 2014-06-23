/*
  Overwolf Sample Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/

/*
  Steps to create a plugin for Overwolf:

  1. Make sure ..\xulrunner-sdk folder exists
  
      Download from: https://developer.mozilla.org/en/docs/Gecko_SDK
      Was tested successfully with version: Gecko 1.9.2 (Firefox 3.6)

  2. Best to rename the output file from npOverwolfSamplePlugin to your
      own name

  3. Edit npOverwolfSamplePlugin.rc version resource to your own properties

      Most importantly, change MIMEType to your own name - Overwolf doesn't
      currently support plugin isolation...

  4. Implement your own API interface by overriding/reimplementing 
      nsScriptableObjectOVerwolfSample

  
  This file holds global functions that provide our NPAPI interface
  with the browser. This interface will then provide the script-able
  object with the specific implementation.

  The main flow is:

  1. Browser ---> NP_Initialize(browser_public_methods)

  2. Browser ---> NP_GetEntryPoints() 
                          - we return our public methods (like |NPP_New|)

  3. Browser ---> NPP_New() ---> NS_NewPluginInstance() 
                                            ---> new nsPluginInstance()

  4. Browser ---> nsPluginInstance::NPPVpluginScriptableNPObject(
                                              NPPVpluginScriptableNPObject)
                             - we return new nsScriptableObjectOverwolfSample()

  5. Script ---> plugin().exampleAsyncFunction("hi", function(echo) {}) --->
                       nsScriptableObjectOverwolfSample::Invoke() --->
                       nsScriptableObjectOverwolfSample::ExampleAsyncFunction


  How to debug:
    You need to attach the debugger to the process that is hosting the plugin.
    Once you run your Overwolf app, look for the OverwolfBrowser.exe process 
    that has the --plugin command line - and get it's process id.  Then just 
    attach to it.

    You can also use other ways, like a ::MessageBox or DebugBreak();
*/
#include "nsPluginInstanceOverwolfSample.h"

// this defines the mime-type when using <object> or <embed>
// NOTE: this is actually really declared in the Version resource of the dll
char kMimeType[] = "application/x-overwolf-sample-plugin";

//////////////////////////////////////
//
// general initialization and shutdown
//
NPError NS_PluginInitialize() {
  return NPERR_NO_ERROR;
}

void NS_PluginShutdown() {
}

/////////////////////////////////////////////////////////////
//
// construction and destruction of our plugin instance object
//
// these are called from npp_gate
nsPluginInstanceBase* NS_NewPluginInstance(
  nsPluginCreateData * aCreateDataStruct) {

  if(!aCreateDataStruct) {
    return nullptr;
  }

  nsPluginInstanceOverwolfSample* plugin = 
    new nsPluginInstanceOverwolfSample(aCreateDataStruct->instance);

  return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin) {
  if(aPlugin) {
    delete (nsPluginInstanceOverwolfSample*)aPlugin;
  }
}

char* NPP_GetMIMEDescription(void) {
  return kMimeType;
}