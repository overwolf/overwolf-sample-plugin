/*
  Overwolf Sample Plugin
  Copyright (c) 2014 Ovefwolf Ltd.
*/
#ifndef UTILS_CRITICAL_SECTION_LOCK_H_
#define UTILS_CRITICAL_SECTION_LOCK_H_

#include <Windows.h>

namespace utils {

class CriticalSection {
public:
    CriticalSection();
    virtual ~CriticalSection();

    void lock();
    void unlock();
private:
    CRITICAL_SECTION critical_section_;
}; // class CriticalSectionLock


class CriticalSectionLock {
public:
    CriticalSectionLock(CriticalSection& criticalSection);
    virtual ~CriticalSectionLock();

private:
    CriticalSection& critical_section_;
}; // class CriticalSectionLock

}; // namespace utils;

#endif // UTILS_CRITICAL_SECTION_LOCK_H_