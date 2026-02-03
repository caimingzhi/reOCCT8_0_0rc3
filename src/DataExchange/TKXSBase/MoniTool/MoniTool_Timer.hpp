// Created on: 2001-12-13
// Created by: Sergey KUUl
// Copyright (c) 2001-2014 OPEN CASCADE SAS
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

#ifndef _MoniTool_Timer_HeaderFile
#define _MoniTool_Timer_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <OSD_Timer.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
#include <Standard_CString.hpp>
#include <Standard_CStringHasher.hpp>
#include <NCollection_DataMap.hpp>

//! Provides convenient service on global timers
//! accessed by string name, mostly aimed for debugging purposes
//!
//! As an instance, envelopes the OSD_Timer to have it as Handle
//!
//! As a tool, supports static dictionary of timers
//! and provides static methods to easily access them
class MoniTool_Timer : public Standard_Transient
{

public:
  //! Create timer in empty state
  MoniTool_Timer();

  const OSD_Timer& Timer() const;

  //! Return reference to embedded OSD_Timer
  OSD_Timer& Timer();

  void Start();

  void Stop();

  //! Start, Stop and reset the timer
  //! In addition to doing that to embedded OSD_Timer,
  //! manage also counter of hits
  void Reset();

  //! Return value of hits counter (count of Start/Stop pairs)
  int Count() const;

  //! Returns value of nesting counter
  int IsRunning() const;

  //! Return value of CPU time minus accumulated amendment
  double CPU();

  //! Return value of accumulated amendment on CPU time
  double Amend() const;

  //! Dumps current state of a timer shortly (one-line output)
  Standard_EXPORT void Dump(Standard_OStream& ostr);

  //! Returns a timer from a dictionary by its name
  //! If timer not existed, creates a new one
  Standard_EXPORT static occ::handle<MoniTool_Timer> Timer(const char* name);

  static void Start(const char* name);

  //! Inline methods to conveniently start/stop timer by name
  //! Shortcut to Timer(name)->Start/Stop()
  static void Stop(const char* name);

  //! Returns map of timers
  Standard_EXPORT static NCollection_DataMap<const char*,
                                             occ::handle<MoniTool_Timer>,
                                             Standard_CStringHasher>&
    Dictionary();

  //! Clears map of timers
  Standard_EXPORT static void ClearTimers();

  //! Dumps contents of the whole dictionary
  Standard_EXPORT static void DumpTimers(Standard_OStream& ostr);

  //! Computes and remembers amendments for times to
  //! access, start, and stop of timer, and estimates
  //! second-order error measured by 10 nested timers
  Standard_EXPORT static void ComputeAmendments();

  //! The computed amendmens are returned (for information only)
  Standard_EXPORT static void GetAmendments(double& Access,
                                            double& Internal,
                                            double& External,
                                            double& Error10);

  DEFINE_STANDARD_RTTIEXT(MoniTool_Timer, Standard_Transient)

private:
  Standard_EXPORT static void AmendAccess();

  Standard_EXPORT void AmendStart();

  //! Internal functions to amend other timers to avoid
  //! side effects of operations with current one
  Standard_EXPORT void AmendStop();

  OSD_Timer                   myTimer;
  int                         myCount;
  int                         myNesting;
  double                      myAmend;
  occ::handle<MoniTool_Timer> myPrev;
  occ::handle<MoniTool_Timer> myNext;
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

//=================================================================================================

inline MoniTool_Timer::MoniTool_Timer()
    : myCount(0),
      myNesting(0),
      myAmend(0)
{
}

//=================================================================================================

inline OSD_Timer& MoniTool_Timer::Timer()
{
  return myTimer;
}

//=================================================================================================

inline const OSD_Timer& MoniTool_Timer::Timer() const
{
  return myTimer;
}

//=================================================================================================

inline void MoniTool_Timer::Start()
{
  //  AmendStart();
  if (!myNesting)
    myTimer.Start();
  myCount++;
  myNesting++;
}

//=================================================================================================

inline void MoniTool_Timer::Stop()
{
  myNesting--;
  if (!myNesting)
    myTimer.Stop();
  //  AmendStop();
}

//=================================================================================================

inline void MoniTool_Timer::Reset()
{
  myTimer.Reset();
  myCount = myNesting = 0;
  myAmend             = 0;
}

//=================================================================================================

inline int MoniTool_Timer::Count() const
{
  return myCount;
}

//=================================================================================================

inline int MoniTool_Timer::IsRunning() const
{
  return myNesting;
}

//=================================================================================================

inline double MoniTool_Timer::Amend() const
{
  return myAmend;
}

//=================================================================================================

inline double MoniTool_Timer::CPU()
{
  int    minutes, hours;
  double seconds, cpu;
  myTimer.Show(seconds, minutes, hours, cpu);
  return cpu - myAmend;
}

//=================================================================================================

inline void MoniTool_Timer::Start(const char* name)
{
  Timer(name)->Start();
}

//=================================================================================================

inline void MoniTool_Timer::Stop(const char* name)
{
  Timer(name)->Stop();
}

class MoniTool_Timer;

#endif // _MoniTool_Timer_HeaderFile
