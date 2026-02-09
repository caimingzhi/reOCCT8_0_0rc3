#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <OSD_Timer.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
#include <Standard_CString.hpp>
#include <Standard_CStringHasher.hpp>
#include <NCollection_DataMap.hpp>

class MoniTool_Timer : public Standard_Transient
{

public:
  MoniTool_Timer();

  const OSD_Timer& Timer() const;

  OSD_Timer& Timer();

  void Start();

  void Stop();

  void Reset();

  int Count() const;

  int IsRunning() const;

  double CPU();

  double Amend() const;

  Standard_EXPORT void Dump(Standard_OStream& ostr);

  Standard_EXPORT static occ::handle<MoniTool_Timer> Timer(const char* name);

  static void Start(const char* name);

  static void Stop(const char* name);

  Standard_EXPORT static NCollection_DataMap<const char*,
                                             occ::handle<MoniTool_Timer>,
                                             Standard_CStringHasher>&
    Dictionary();

  Standard_EXPORT static void ClearTimers();

  Standard_EXPORT static void DumpTimers(Standard_OStream& ostr);

  Standard_EXPORT static void ComputeAmendments();

  Standard_EXPORT static void GetAmendments(double& Access,
                                            double& Internal,
                                            double& External,
                                            double& Error10);

  DEFINE_STANDARD_RTTIEXT(MoniTool_Timer, Standard_Transient)

private:
  Standard_EXPORT static void AmendAccess();

  Standard_EXPORT void AmendStart();

  Standard_EXPORT void AmendStop();

  OSD_Timer                   myTimer;
  int                         myCount;
  int                         myNesting;
  double                      myAmend;
  occ::handle<MoniTool_Timer> myPrev;
  occ::handle<MoniTool_Timer> myNext;
};

inline MoniTool_Timer::MoniTool_Timer()
    : myCount(0),
      myNesting(0),
      myAmend(0)
{
}

inline OSD_Timer& MoniTool_Timer::Timer()
{
  return myTimer;
}

inline const OSD_Timer& MoniTool_Timer::Timer() const
{
  return myTimer;
}

inline void MoniTool_Timer::Start()
{

  if (!myNesting)
    myTimer.Start();
  myCount++;
  myNesting++;
}

inline void MoniTool_Timer::Stop()
{
  myNesting--;
  if (!myNesting)
    myTimer.Stop();
}

inline void MoniTool_Timer::Reset()
{
  myTimer.Reset();
  myCount = myNesting = 0;
  myAmend             = 0;
}

inline int MoniTool_Timer::Count() const
{
  return myCount;
}

inline int MoniTool_Timer::IsRunning() const
{
  return myNesting;
}

inline double MoniTool_Timer::Amend() const
{
  return myAmend;
}

inline double MoniTool_Timer::CPU()
{
  int    minutes, hours;
  double seconds, cpu;
  myTimer.Show(seconds, minutes, hours, cpu);
  return cpu - myAmend;
}

inline void MoniTool_Timer::Start(const char* name)
{
  Timer(name)->Start();
}

inline void MoniTool_Timer::Stop(const char* name)
{
  Timer(name)->Stop();
}

class MoniTool_Timer;
