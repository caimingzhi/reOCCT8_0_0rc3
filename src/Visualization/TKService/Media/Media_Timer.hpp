#pragma once


#include <OSD_Timer.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

//! Auxiliary class defining the animation timer.
class Media_Timer : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Timer, Standard_Transient)
public:
  //! Empty constructor.
  Media_Timer()
      : myTimerFrom(0.0),
        myTimerSpeed(1.0)
  {
  }

  //! Return elapsed time in seconds.
  double ElapsedTime() const { return myTimerFrom + myTimer.ElapsedTime() * myTimerSpeed; }

  //! Return playback speed coefficient (1.0 means normal speed).
  double PlaybackSpeed() const { return myTimerSpeed; }

  //! Setup playback speed coefficient.
  Standard_EXPORT void SetPlaybackSpeed(const double theSpeed);

  //! Return true if timer has been started.
  bool IsStarted() const { return myTimer.IsStarted(); }

  //! Start the timer.
  void Start() { myTimer.Start(); }

  //! Pause the timer.
  Standard_EXPORT void Pause();

  //! Stop the timer.
  Standard_EXPORT void Stop();

  //! Seek the timer to specified position.
  Standard_EXPORT void Seek(const double theTime);

protected:
  OSD_Timer myTimer;
  double    myTimerFrom;
  double    myTimerSpeed;
};

