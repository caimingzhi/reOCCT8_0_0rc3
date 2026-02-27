#include <OSD_Timer.hpp>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <sys/time.h>
#endif

namespace
{

  static void timeToHoursMinutesSeconds(double  theTimeSec,
                                        int&    theHours,
                                        int&    theMinutes,
                                        double& theSeconds)
  {
    int aSec   = (int)theTimeSec;
    theHours   = aSec / 3600;
    theMinutes = (aSec - theHours * 3600) / 60;
    theSeconds = theTimeSec - theHours * 3600 - theMinutes * 60;
  }

#ifdef _WIN32

  struct PerfCounterFreq
  {
    LARGE_INTEGER Freq;
    bool          IsOk;

    PerfCounterFreq() { IsOk = QueryPerformanceFrequency(&Freq) != FALSE; }
  };
#endif
} // namespace

double System::os::OSD_Timer::GetWallClockTime()
{
#ifdef _WIN32

  static const PerfCounterFreq aFreq;

  LARGE_INTEGER aTime;
  return aFreq.IsOk && QueryPerformanceCounter(&aTime)
           ? (double)aTime.QuadPart / (double)aFreq.Freq.QuadPart
  #if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0600)
           : 0.001 * GetTickCount64();
  #else
           : 0.001 * GetTickCount();
  #endif
#else
  struct timeval aTime;

  static const time_t aStartSec = (gettimeofday(&aTime, nullptr) == 0 ? aTime.tv_sec : 0);
  return gettimeofday(&aTime, nullptr) == 0 ? (aTime.tv_sec - aStartSec) + 0.000001 * aTime.tv_usec
                                            : 0.0;
#endif
}

System::os::OSD_Timer::OSD_Timer(bool theThisThreadOnly)
    : System::os::OSD_Chronometer(theThisThreadOnly),
      myTimeStart(0.0),
      myTimeCumul(0.0)
{
}

void System::os::OSD_Timer::Reset(const double theTimeElapsedSec)
{
  myTimeStart = 0.0;
  myTimeCumul = theTimeElapsedSec;
  System::os::OSD_Chronometer::Reset();
}

void System::os::OSD_Timer::Reset()
{
  myTimeStart = myTimeCumul = 0.0;
  System::os::OSD_Chronometer::Reset();
}

void System::os::OSD_Timer::Restart()
{
  myTimeStart = GetWallClockTime();
  myTimeCumul = 0.0;
  System::os::OSD_Chronometer::Restart();
}

void System::os::OSD_Timer::Show() const
{
  Show(std::cout);
}

double System::os::OSD_Timer::ElapsedTime() const
{
  if (myIsStopped)
  {
    return myTimeCumul;
  }

  return myTimeCumul + GetWallClockTime() - myTimeStart;
}

void System::os::OSD_Timer::Show(double& theSeconds, int& theMinutes, int& theHours, double& theCPUtime) const
{
  const double aTimeCumul =
    myIsStopped ? myTimeCumul : myTimeCumul + GetWallClockTime() - myTimeStart;
  timeToHoursMinutesSeconds(aTimeCumul, theHours, theMinutes, theSeconds);
  System::os::OSD_Chronometer::Show(theCPUtime);
}

void System::os::OSD_Timer::Show(Standard_OStream& theOStream) const
{
  const double aTimeCumul = ElapsedTime();

  int    anHours, aMinutes;
  double aSeconds;
  timeToHoursMinutesSeconds(aTimeCumul, anHours, aMinutes, aSeconds);

  std::streamsize prec = theOStream.precision(12);
  theOStream << "Elapsed time: " << anHours << " Hours " << aMinutes << " Minutes " << aSeconds
             << " Seconds\n";
  System::os::OSD_Chronometer::Show(theOStream);
  theOStream.precision(prec);
}

void System::os::OSD_Timer::Stop()
{
  if (!myIsStopped)
  {
    myTimeCumul += GetWallClockTime() - myTimeStart;
    System::os::OSD_Chronometer::Stop();
  }
}

void System::os::OSD_Timer::Start()
{
  if (myIsStopped)
  {
    myTimeStart = GetWallClockTime();
    System::os::OSD_Chronometer::Start();
  }
}
