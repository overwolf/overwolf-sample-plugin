/*
  Overwolf Sample Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#include "nsScriptableObjectBase.h"

nsScriptableObjectBase::nsScriptableObjectBase(NPP npp) : 
  npp_(npp) {
}

nsScriptableObjectBase::~nsScriptableObjectBase() {
}

void nsScriptableObjectBase::Invalidate() {
}

bool nsScriptableObjectBase::HasMethod(NPIdentifier name) {
   return false;
}

bool nsScriptableObjectBase::Invoke(
  NPIdentifier name, 
  const NPVariant *args, 
  uint32_t argCount, 
  NPVariant *result) {

  return false;
}

bool nsScriptableObjectBase::InvokeDefault(
  const NPVariant *args,
  uint32_t argCount, 
  NPVariant *result) {

  return false;
}

bool nsScriptableObjectBase::HasProperty(NPIdentifier name) {
#ifdef _DEBUG
  NPUTF8* utf8_name = NPN_UTF8FromIdentifier(name);
  NPN_MemFree((void*)utf8_name);
#endif
  return false;
}

bool nsScriptableObjectBase::GetProperty(
  NPIdentifier name, NPVariant *result) {

  return false;
}

bool nsScriptableObjectBase::SetProperty(
  NPIdentifier name, const NPVariant *value) {
  
  return false;
}

bool nsScriptableObjectBase::RemoveProperty(NPIdentifier name) {
  return false;
}

// static
void nsScriptableObjectBase::_Deallocate(NPObject *npobj) {
  // Call the virtual destructor.
  delete (nsScriptableObjectBase*)npobj;
}

// static
void nsScriptableObjectBase::_Invalidate(NPObject *npobj) {
  ((nsScriptableObjectBase*)npobj)->Invalidate();
}

// static
bool nsScriptableObjectBase::_HasMethod(
  NPObject *npobj, NPIdentifier name) {
  return ((nsScriptableObjectBase*)npobj)->HasMethod(name);
}

// static
bool nsScriptableObjectBase::_Invoke(
  NPObject *npobj, 
  NPIdentifier name,
  const NPVariant *args, 
  uint32_t argCount,
  NPVariant *result) {
  
  return ((nsScriptableObjectBase*)npobj)->Invoke(
    name, 
    args, 
    argCount, 
    result);
}

// static
bool nsScriptableObjectBase::_InvokeDefault(
  NPObject *npobj,
  const NPVariant *args,
  uint32_t argCount,
  NPVariant *result) {

  return ((nsScriptableObjectBase*)npobj)->
              InvokeDefault(args, argCount, result);
}

// static
bool nsScriptableObjectBase::_HasProperty(
  NPObject * npobj, NPIdentifier name) {
  return ((nsScriptableObjectBase*)npobj)->HasProperty(name);
}

// static
bool nsScriptableObjectBase::_GetProperty(
  NPObject *npobj, NPIdentifier name, NPVariant *result) {
  return ((nsScriptableObjectBase*)npobj)->GetProperty(name, result);
}

// static
bool nsScriptableObjectBase::_SetProperty(
  NPObject *npobj, NPIdentifier name, const NPVariant *value) {
  return ((nsScriptableObjectBase*)npobj)->SetProperty(name, value);
}

// static
bool nsScriptableObjectBase::_RemoveProperty(
  NPObject *npobj, NPIdentifier name) {
  return ((nsScriptableObjectBase*)npobj)->RemoveProperty(name);
}
