#pragma once

#include <OSD_Timer.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class Media_Timer : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Timer, Standard_Transient)
public:
  Media_Timer()
      : myTimerFrom(0.0),
        myTimerSpeed(1.0)
  {
  }

  double ElapsedTime() const { return myTimerFrom + myTimer.ElapsedTime() * myTimerSpeed; }

  double PlaybackSpeed() const { return myTimerSpeed; }

  Standard_EXPORT void SetPlaybackSpeed(const double theSpeed);

  bool IsStarted() const { return myTimer.IsStarted(); }

  void Start() { myTimer.Start(); }

  Standard_EXPORT void Pause();

  Standard_EXPORT void Stop();

  Standard_EXPORT void Seek(const double theTime);

protected:
  OSD_Timer myTimer;
  double    myTimerFrom;
  double    myTimerSpeed;
};
