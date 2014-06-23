/*------------------------------------------------------------------------
$Workfile: $
$Archive: $
$Author: Tom Wolf $
$Revision: $
$Date: $

Description:
	
  Copyright © 2013 Overwolf Ltd. All rights reserved.
------------------------------------------------------------------------*/
#ifndef COMMON_UTILS_SINGLETONCLASS_H_
#define COMMON_UTILS_SINGLETONCLASS_H_

// Put this in the private: declarations for a class to be uncopyable.
#define DISALLOW_COPY(TypeName) \
    TypeName(const TypeName&)

// Put this in the private: declarations for a class to be unassignable.
#define DISALLOW_ASSIGN(TypeName) \
    void operator=(const TypeName&)

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);               \
    void operator=(const TypeName&)

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
    TypeName();                                    \
    DISALLOW_COPY_AND_ASSIGN(TypeName)

/*------------------------------------------------------------------------
template <class T>
class SingletonClassStack

	Inherits From:
		            This method is safer for two reasons:
                     1. At the end of the process it will call the class's
                        destructor
                     2. There is no global initialization race
	Description:
		
	Data members:
		
------------------------------------------------------------------------*/
template <class T>
class SingletonClassStack {
public:
   static T& GetInstance() {
      static T obj;
      return obj;
   }

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(SingletonClassStack);
};


/*------------------------------------------------------------------------
template <class T>
class SingletonClassHeap

	Inherits From:
		
	Description:
		
	Data members:
		
------------------------------------------------------------------------*/
template <class T>
class SingletonClassHeap {
public:
   static T* GetInstance() {
      if (NULL == m_lpObj) {
         m_lpObj = new T;
      }

      return m_lpObj;
   }

   static void DeleteInstance() {
      if (NULL != m_lpObj) {
         delete m_lpObj;
         m_lpObj = NULL;
      }
   }

private:
    DISALLOW_IMPLICIT_CONSTRUCTORS(SingletonClassHeap);

    static T* m_lpObj;
};

template <class T> T* SingletonClassHeap<T>::m_lpObj = NULL;

#endif // COMMON_UTILS_SINGLETONCLASS_H_
