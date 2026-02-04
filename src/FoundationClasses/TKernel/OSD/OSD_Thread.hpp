#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
// Created on: 2006-03-10
// Created by: data exchange team
// Copyright (c) 2006-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


//! Typedef for prototype of function to be used as main function of a thread.
//!
//! Note: currently we use the same prototype for thread functions on all platforms,
//! in order to make user programs less platform-dependent.
//! However, there is a distinction in returned value for the thread function
//! on UNIX/Linux (void*) and Windows (DWORD) systems.
//! Thus on Windows we have to encode returned void* as DWORD.
//! It is OK for WIN32, but potentially problem on WIN64.
//! To avoid any problems with this, for better application portability it is recommended
//! that the thread function returns just integer (casted to void*).
//! This shall work on all platforms.
typedef void* (*OSD_ThreadFunction)(void* data);

// #ifdef _WIN32
// typedef LPTHREAD_START_ROUTINE OSD_ThreadFunction;
// #endif

// Created on: 2006-03-10
// Created by: data exchange team
// Copyright (c) 2006-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


// Platform-dependent definition of the thread handle type

#ifdef _WIN32

  #include <windows.h>
typedef HANDLE OSD_PThread;
  #define OSD_PTHREAD_NULL nullptr

#else

  #include <pthread.h>
typedef pthread_t OSD_PThread;
  // NOLINTBEGIN(modernize-use-nullptr)
  #define OSD_PTHREAD_NULL 0
  // NOLINTEND(modernize-use-nullptr)

#endif


#include <Standard_ThreadId.hpp>
#include <Standard_Boolean.hpp>

//! A simple platform-intependent interface to execute
//! and control threads.
class OSD_Thread
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT OSD_Thread();

  //! Initialize the tool by the thread function
  //!
  //! Note: On Windows, you might have to take an address of the thread
  //! function explicitly to pass it to this constructor without compiler error
  Standard_EXPORT OSD_Thread(const OSD_ThreadFunction& func);

  //! Copy constructor
  Standard_EXPORT OSD_Thread(const OSD_Thread& other);

  //! Copy thread handle from other OSD_Thread object.
  Standard_EXPORT void Assign(const OSD_Thread& other);

  void operator=(const OSD_Thread& other) { Assign(other); }

  //! Destructor. Detaches the thread if it wasn't done already.
  Standard_EXPORT ~OSD_Thread();

  Standard_EXPORT void SetPriority(const int thePriority);

  //! Initialize the tool by the thread function.
  //! If the current thread handle is not null, nullifies it.
  //!
  //! Note: On Windows, you might have to take an address of the thread
  //! function explicitly to pass it to this method without compiler error
  Standard_EXPORT void SetFunction(const OSD_ThreadFunction& func);

  //! Starts a thread with thread function given in constructor,
  //! passing the specified input data (as void *) to it.
  //! The parameter \a WNTStackSize (on Windows only)
  //! specifies size of the stack to be allocated for the thread
  //! (by default - the same as for the current executable).
  //! Returns True if thread started successfully
  Standard_EXPORT bool Run(void* const data = nullptr, const int WNTStackSize = 0);

  //! Detaches the execution thread from this Thread object,
  //! so that it cannot be waited.
  //! Note that mechanics of this operation is different on
  //! UNIX/Linux (the thread is put to detached state) and Windows
  //! (the handle is closed).
  //! However, the purpose is the same: to instruct the system to
  //! release all thread data upon its completion.
  Standard_EXPORT void Detach();

  //! Waits till the thread finishes execution.
  bool Wait()
  {
    void* aRes = nullptr;
    return Wait(aRes);
  }

  //! Wait till the thread finishes execution.
  //! Returns True if wait was successful, False in case of error.
  //!
  //! If successful and \a result argument is provided, saves the pointer
  //! (void*) returned by the thread function in \a result.
  //!
  //! Note however that it is advisable not to rely upon returned result
  //! value, as it is not always the value actually returned by the thread
  //! function. In addition, on Windows it is converted via DWORD.
  Standard_EXPORT bool Wait(void*& theResult);

  //! Waits for some time and if the thread is finished,
  //! it returns the result.
  //! The function returns false if the thread is not finished yet.
  Standard_EXPORT bool Wait(const int time, void*& theResult);

  //! Returns ID of the currently controlled thread ID,
  //! or 0 if no thread is run
  Standard_EXPORT Standard_ThreadId GetId() const;

  //! Auxiliary: returns ID of the current thread
  Standard_EXPORT static Standard_ThreadId Current();

private:
  OSD_ThreadFunction myFunc;
  OSD_PThread        myThread;
  Standard_ThreadId  myThreadId;
  int                myPriority;
};

