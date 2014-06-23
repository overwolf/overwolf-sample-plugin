/*
  Overwolf Sample Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#ifndef NSSCRIPTABLEOBJECTBASE_H_
#define NSSCRIPTABLEOBJECTBASE_H_

#include <windows.h>

//#include "plugin_common/npplat.h"
#include "plugin_common/pluginbase.h"

template<class T>
static NPObject* AllocateNpObject(NPP npp, NPClass*) {
  NPObject* obj = new T(npp);
  return obj;
}

/*------------------------------------------------------------------------
class nsScriptableObjectBase : public NPObject

	Inherits From:
		
	Description:   Helper class that can be used to map calls to the 
                  NPObject hooks into virtual methods on instances of 
                  classes that derive from this class.
		
	Data members:
		
------------------------------------------------------------------------*/
class nsScriptableObjectBase : public NPObject {
public:
  nsScriptableObjectBase(NPP npp);
  virtual ~nsScriptableObjectBase();

public:
  // Virtual NPObject hooks called through this base class. Override
  // as you see fit.
  virtual void Invalidate();
  virtual bool HasMethod(NPIdentifier name);
  virtual bool Invoke(NPIdentifier name, const NPVariant *args,
                    uint32_t argCount, NPVariant *result);
  virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount,
                            NPVariant *result);
  virtual bool HasProperty(NPIdentifier name);
  virtual bool GetProperty(NPIdentifier name, NPVariant *result);
  virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
  virtual bool RemoveProperty(NPIdentifier name);

public:
  static void _Deallocate(NPObject *npobj);
  static void _Invalidate(NPObject *npobj);
  static bool _HasMethod(NPObject *npobj, NPIdentifier name);
  static bool _Invoke(NPObject *npobj, NPIdentifier name,
                    const NPVariant *args, uint32_t argCount,
                    NPVariant *result);
  static bool _InvokeDefault(NPObject *npobj, const NPVariant *args,
                            uint32_t argCount, NPVariant *result);
  static bool _HasProperty(NPObject * npobj, NPIdentifier name);
  static bool _GetProperty(NPObject *npobj, NPIdentifier name,
                          NPVariant *result);
  static bool _SetProperty(NPObject *npobj, NPIdentifier name,
                          const NPVariant *value);
  static bool _RemoveProperty(NPObject *npobj, NPIdentifier name);

protected:
  NPP npp_;
};

#define DECLARE_NPOBJECT_CLASS_WITH_BASE(_class, ctor)   \
static NPClass s##_class##_NPClass = {                   \
  NP_CLASS_STRUCT_VERSION,                               \
  ctor,                                                  \
  nsScriptableObjectBase::_Deallocate,        \
  nsScriptableObjectBase::_Invalidate,        \
  nsScriptableObjectBase::_HasMethod,         \
  nsScriptableObjectBase::_Invoke,            \
  nsScriptableObjectBase::_InvokeDefault,     \
  nsScriptableObjectBase::_HasProperty,       \
  nsScriptableObjectBase::_GetProperty,       \
  nsScriptableObjectBase::_SetProperty,       \
  nsScriptableObjectBase::_RemoveProperty     \
}

#define GET_NPOBJECT_CLASS(_class) &s##_class##_NPClass

#endif // NSSCRIPTABLEOBJECTBASE_H_