/*
  Overwolf Sample Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#include "nsPluginInstanceOverwolfSample.h"
#include "nsScriptableObjectOverwolfSample.h" // our specific API

// we use this to force our plugin container to shut down
// when no one is using it.  Browsers try to keep the plugin
// open for optimization reasons - we don't want it
int nsPluginInstanceOverwolfSample::ref_count_ = 0;

////////////////////////////////////////
//
// nsPluginInstanceOverwolfSample class implementation
//
nsPluginInstanceOverwolfSample::nsPluginInstanceOverwolfSample(NPP instance) :
  nsPluginInstanceBase(),
  instance_(instance),
  initialized_(FALSE),
  scriptable_object_(nullptr) {

  nsPluginInstanceOverwolfSample::ref_count_++;
}

nsPluginInstanceOverwolfSample::~nsPluginInstanceOverwolfSample() {
  nsPluginInstanceOverwolfSample::ref_count_--;

  if (0 == nsPluginInstanceOverwolfSample::ref_count_) {
    PostQuitMessage(0);
  }
}

// NOTE:
// ------
// Overwolf plugins should not implement windows - NPAPI will
// probably be removed in the near feature and will be changed
// by a different method that will only support non-visual
// plugins
NPBool nsPluginInstanceOverwolfSample::init(NPWindow* window) {
  // no GUI to init in windowless case
  initialized_ = TRUE;
  return TRUE;
}

void nsPluginInstanceOverwolfSample::shut() {
  if (nullptr != scriptable_object_) {
    NPN_ReleaseObject(scriptable_object_);
  }

  initialized_ = FALSE;
}

NPBool nsPluginInstanceOverwolfSample::isInitialized() {
  return initialized_;
}

// here we supply our scriptable object
NPError nsPluginInstanceOverwolfSample::GetValue(
  NPPVariable variable, void* ret_value) {
  
  NPError rv = NPERR_INVALID_PARAM;

  switch (variable) {
    case NPPVpluginScriptableNPObject:
    {
      if (nullptr == scriptable_object_) {
        scriptable_object_ = 
          NPN_CreateObject(
            instance_, 
            GET_NPOBJECT_CLASS(nsScriptableObjectOverwolfSample));

        NPN_RetainObject(scriptable_object_);

        ((nsScriptableObjectOverwolfSample*)scriptable_object_)->Init();
        *(NPObject **)ret_value = scriptable_object_;
      }

      rv = NPERR_NO_ERROR;
      return rv;
    }
    default:
      break;
  }

  return rv;
}