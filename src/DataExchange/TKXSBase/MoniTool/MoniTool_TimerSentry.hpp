#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
class MoniTool_Timer;

//! A tool to facilitate using MoniTool_Timer functionality
//! by automatically ensuring consistency of start/stop actions
//!
//! When instance of TimerSentry is created, a timer
//! with corresponding name is started
//! When instance is deleted, timer stops
class MoniTool_TimerSentry
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor creates an instance and runs the corresponding timer
  MoniTool_TimerSentry(const char* cname);

  //! Constructor creates an instance and runs the corresponding timer
  MoniTool_TimerSentry(const occ::handle<MoniTool_Timer>& timer);

  //! Destructor stops the associated timer
  ~MoniTool_TimerSentry();

  occ::handle<MoniTool_Timer> Timer() const;

  //! Manually stops the timer
  void Stop();

private:
  occ::handle<MoniTool_Timer> myTimer;
};
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#include <MoniTool_Timer.hpp>

//=================================================================================================

inline MoniTool_TimerSentry::MoniTool_TimerSentry(const char* cname)
    : myTimer(MoniTool_Timer::Timer(cname))
{
  myTimer->Start();
}

//=================================================================================================

inline MoniTool_TimerSentry::MoniTool_TimerSentry(const occ::handle<MoniTool_Timer>& timer)
{
  myTimer = timer;
  myTimer->Start();
}

//=======================================================================
// function : Destructor
// purpose  : make stop for corresponding timer before destroying
//=======================================================================

inline MoniTool_TimerSentry::~MoniTool_TimerSentry()
{
  if (!myTimer.IsNull())
    myTimer->Stop();
}

//=================================================================================================

inline occ::handle<MoniTool_Timer> MoniTool_TimerSentry::Timer() const
{
  return myTimer;
}

//=================================================================================================

inline void MoniTool_TimerSentry::Stop()
{
  if (!myTimer.IsNull())
    myTimer->Stop();
  myTimer.Nullify();
}


