#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

class OSD_Chronometer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Chronometer(bool theThisThreadOnly = false);

  Standard_EXPORT virtual ~OSD_Chronometer();

  bool IsStarted() const { return !myIsStopped; }

  Standard_EXPORT virtual void Reset();

  Standard_EXPORT virtual void Restart();

  Standard_EXPORT virtual void Stop();

  Standard_EXPORT virtual void Start();

  Standard_EXPORT virtual void Show() const;

  Standard_EXPORT virtual void Show(Standard_OStream& theOStream) const;

  double UserTimeCPU() const
  {
    double aUserTime = 0.0, aSysTime = 0.0;
    Show(aUserTime, aSysTime);
    return aUserTime;
  }

  double SystemTimeCPU() const
  {
    double aUserTime = 0.0, aSysTime = 0.0;
    Show(aUserTime, aSysTime);
    return aSysTime;
  }

  bool IsThisThreadOnly() const { return myIsThreadOnly; }

  Standard_EXPORT void SetThisThreadOnly(bool theIsThreadOnly);

  void Show(double& theUserSeconds) const { theUserSeconds = UserTimeCPU(); }

  Standard_EXPORT void Show(double& theUserSec, double& theSystemSec) const;

public:
  Standard_EXPORT static void GetProcessCPU(double& UserSeconds, double& SystemSeconds);

  Standard_EXPORT static void GetThreadCPU(double& UserSeconds, double& SystemSeconds);

protected:
  double myStartCpuUser;
  double myStartCpuSys;
  double myCumulCpuUser;
  double myCumulCpuSys;
  bool   myIsStopped;
  bool   myIsThreadOnly;
};
