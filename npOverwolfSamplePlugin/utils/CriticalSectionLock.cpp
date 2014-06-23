/*
  Overwolf Sample Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#include "CriticalSectionLock.h"

using namespace utils;

CriticalSection::CriticalSection() {
  InitializeCriticalSection(&critical_section_);
}

CriticalSection::~CriticalSection() {
  DeleteCriticalSection(&critical_section_);
}

void CriticalSection::lock() {
  EnterCriticalSection(&critical_section_);
}

void CriticalSection::unlock() {
  LeaveCriticalSection(&critical_section_);
}



//////////////////////////////////////////////////////////////////////////
CriticalSectionLock::CriticalSectionLock(
  CriticalSection& criticalSection) :
  critical_section_(criticalSection) {
  
  critical_section_.lock();
}

CriticalSectionLock::~CriticalSectionLock() {
  critical_section_.unlock();
}
