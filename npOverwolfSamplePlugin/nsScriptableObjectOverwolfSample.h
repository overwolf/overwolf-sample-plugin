/*
  Overwolf Sample Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#ifndef NNSSCRIPTABLEOBJECTOVERWOLFSAMPLE_H_
#define NNSSCRIPTABLEOBJECTOVERWOLFSAMPLE_H_

#include "nsScriptableObjectBase.h"
#include <map>

namespace utils {
class Thread; // forward declaration
}

class nsScriptableObjectOverwolfSample : public nsScriptableObjectBase {
public:
  nsScriptableObjectOverwolfSample(NPP npp);
  virtual ~nsScriptableObjectOverwolfSample(void);

public:
  bool Init();

// nsScriptableObjectBase overrides
public:
  virtual bool HasMethod(NPIdentifier name);
  virtual bool Invoke(
    NPIdentifier name, 
    const NPVariant *args, 
    uint32_t argCount, 
    NPVariant *result);
  virtual bool HasProperty(NPIdentifier name);
  virtual bool GetProperty(NPIdentifier name, NPVariant *result);
  virtual bool SetProperty(NPIdentifier name, const NPVariant *value);

// public methods
private:
  // Because we want to have a responsive plugin - we make sure that all
  // our functions run on a separate thread (not on the main browser
  // thread).  To achieve this, we create a Task function (see Thread.h) that 
  // runs on a separate thread triggers a callback

  // echo("echoMessage", function(echoMessage) { console.log(echoMessage) });
  bool Echo(
    NPIdentifier name, 
    const NPVariant *args, 
    uint32_t argCount, 
    NPVariant *result);

  // add(first, second, function(answer) { console.log(answer) })
  bool Add(
    NPIdentifier name, 
    const NPVariant *args, 
    uint32_t argCount, 
    NPVariant *result);


// These are the functions that run on a separate thread - 
// there is one for each public function we expose.
// Eventually, they will run TriggerCallbackOnMainThread
private:
  void EchoTask(
    const std::string& message,
    NPObject* callback);

  void AddTask(
    double first,
    double second,
    NPObject* callback);


// member variables
private:
  // defines a generic method
  typedef bool (nsScriptableObjectOverwolfSample::*MethodHandle)(
    NPIdentifier,
    const NPVariant*, 
    uint32_t, 
    NPVariant*);

  // holds the public methods
  typedef std::map<NPIdentifier, MethodHandle> MethodsMap;
  MethodsMap methods_;

  double sample_property_;

  // good idea for when having an autonomous thread sending callbacks
  bool shutting_down_;

  // this allows us to run our code on a separate thread than the 
  // main browser thread - to be more responsive
  std::auto_ptr<utils::Thread> thread_;
};

// declare our NPObject-derived scriptable object class
DECLARE_NPOBJECT_CLASS_WITH_BASE(
  nsScriptableObjectOverwolfSample, 
  AllocateNpObject<nsScriptableObjectOverwolfSample>);


#endif // NNSSCRIPTABLEOBJECTOVERWOLFSAMPLE_H_