#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
class MoniTool_Timer;

class MoniTool_TimerSentry
{
public:
  DEFINE_STANDARD_ALLOC

  MoniTool_TimerSentry(const char* cname);

  MoniTool_TimerSentry(const occ::handle<MoniTool_Timer>& timer);

  ~MoniTool_TimerSentry();

  occ::handle<MoniTool_Timer> Timer() const;

  void Stop();

private:
  occ::handle<MoniTool_Timer> myTimer;
};

#include <MoniTool_Timer.hpp>

inline MoniTool_TimerSentry::MoniTool_TimerSentry(const char* cname)
    : myTimer(MoniTool_Timer::Timer(cname))
{
  myTimer->Start();
}

inline MoniTool_TimerSentry::MoniTool_TimerSentry(const occ::handle<MoniTool_Timer>& timer)
{
  myTimer = timer;
  myTimer->Start();
}

inline MoniTool_TimerSentry::~MoniTool_TimerSentry()
{
  if (!myTimer.IsNull())
    myTimer->Stop();
}

inline occ::handle<MoniTool_Timer> MoniTool_TimerSentry::Timer() const
{
  return myTimer;
}

inline void MoniTool_TimerSentry::Stop()
{
  if (!myTimer.IsNull())
    myTimer->Stop();
  myTimer.Nullify();
}
