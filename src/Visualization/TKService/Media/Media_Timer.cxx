#include <Media_Timer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Media_Timer, Standard_Transient)

void Media_Timer::Pause()
{
  myTimer.Stop();
  myTimerFrom += myTimer.ElapsedTime() * myTimerSpeed;
  myTimer.Reset();
}

void Media_Timer::Stop()
{
  myTimer.Stop();
  myTimer.Reset();
  myTimerFrom = 0.0;
}

void Media_Timer::SetPlaybackSpeed(const double theSpeed)
{
  if (!myTimer.IsStarted())
  {
    myTimerSpeed = theSpeed;
    return;
  }

  myTimer.Stop();
  myTimerFrom += myTimer.ElapsedTime() * myTimerSpeed;
  myTimer.Reset();
  myTimerSpeed = theSpeed;
  myTimer.Start();
}

void Media_Timer::Seek(const double theTime)
{
  const bool isStarted = myTimer.IsStarted();
  myTimer.Stop();
  myTimer.Reset();
  myTimerFrom = theTime;
  if (isStarted)
  {
    myTimer.Start();
  }
}
