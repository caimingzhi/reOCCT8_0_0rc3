#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <OSD_Chronometer.hpp>
#include <Standard_OStream.hpp>

class OSD_Timer : public OSD_Chronometer
{
public:
  Standard_EXPORT static double GetWallClockTime();

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Timer(bool theThisThreadOnly = false);

  Standard_EXPORT void Reset(const double theTimeElapsedSec);

  Standard_EXPORT void Reset() override;

  Standard_EXPORT void Restart() override;

  Standard_EXPORT void Show() const override;

  Standard_EXPORT void Show(Standard_OStream& os) const override;

  Standard_EXPORT void Show(double& theSeconds,
                            int&    theMinutes,
                            int&    theHours,
                            double& theCPUtime) const;

  Standard_EXPORT void Stop() override;

  Standard_EXPORT void Start() override;

  Standard_EXPORT double ElapsedTime() const;

private:
  double myTimeStart;
  double myTimeCumul;
};
