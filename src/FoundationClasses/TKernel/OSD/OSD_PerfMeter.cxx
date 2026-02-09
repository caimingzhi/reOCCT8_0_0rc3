

#include <OSD_PerfMeter.hpp>

#include <OSD_Chronometer.hpp>
#include <NCollection_DataMap.hpp>

class Stopwatch
{
public:
  Stopwatch();

  void Start();

  void Stop();

  double Elapsed() const;

  inline bool IsRunning() const;

  inline bool IsActive() const;

private:
  static double getTime();

private:
  double myStartTime;
  double myEndTime;

  bool myIsTicking;
};

Stopwatch::Stopwatch()
    : myStartTime(getTime()),
      myEndTime(myStartTime),
      myIsTicking(false)
{
}

void Stopwatch::Start()
{
  myStartTime = getTime();
  myIsTicking = true;
}

void Stopwatch::Stop()
{
  if (!myIsTicking)
  {
    return;
  }

  myEndTime   = getTime();
  myIsTicking = false;
}

double Stopwatch::Elapsed() const
{
  const double anEndTime = myIsTicking ? getTime() : myEndTime;
  return anEndTime - myStartTime;
}

bool Stopwatch::IsRunning() const
{
  return myIsTicking;
}

bool Stopwatch::IsActive() const
{
  return myIsTicking || (myEndTime - myStartTime) > 0.0;
}

double Stopwatch::getTime()
{
  double aUserSeconds   = 0.0;
  double aSystemSeconds = 0.0;
  OSD_Chronometer::GetThreadCPU(aUserSeconds, aSystemSeconds);
  (void)(aSystemSeconds);
  return aUserSeconds;
}

class StopwatchStorage
{
private:
  StopwatchStorage()                                   = default;
  StopwatchStorage(const StopwatchStorage&)            = delete;
  StopwatchStorage& operator=(const StopwatchStorage&) = delete;
  StopwatchStorage(StopwatchStorage&&)                 = delete;
  StopwatchStorage& operator=(StopwatchStorage&&)      = delete;

  ~StopwatchStorage() { PrintAll(); }

public:
  static StopwatchStorage& Instance();

  Stopwatch* GetStopwatch(const TCollection_AsciiString& theName);

  Stopwatch& CreateStopwatch(const TCollection_AsciiString& theName);

  bool HasStopwatch(const TCollection_AsciiString& theName) const;

  void KillStopwatch(const TCollection_AsciiString& theName);

  void Clear();

  TCollection_AsciiString Print(const TCollection_AsciiString& theName) const;

  TCollection_AsciiString PrintAll() const;

private:
  void print(const TCollection_AsciiString& theName, TCollection_AsciiString& theOutput) const;

private:
  NCollection_DataMap<TCollection_AsciiString, Stopwatch> myStopwatches;
};

StopwatchStorage& StopwatchStorage::Instance()
{
  static StopwatchStorage instance;
  return instance;
}

Stopwatch* StopwatchStorage::GetStopwatch(const TCollection_AsciiString& theName)
{
  return myStopwatches.ChangeSeek(theName);
}

Stopwatch& StopwatchStorage::CreateStopwatch(const TCollection_AsciiString& theName)
{
  return *myStopwatches.Bound(theName, Stopwatch());
}

bool StopwatchStorage::HasStopwatch(const TCollection_AsciiString& theName) const
{
  return myStopwatches.IsBound(theName);
}

void StopwatchStorage::KillStopwatch(const TCollection_AsciiString& theName)
{
  myStopwatches.UnBind(theName);
}

void StopwatchStorage::Clear()
{
  myStopwatches.Clear();
}

TCollection_AsciiString StopwatchStorage::Print(const TCollection_AsciiString& theName) const
{
  TCollection_AsciiString anOutput;
  if (myStopwatches.IsBound(theName))
  {
    print(theName, anOutput);
  }
  return anOutput;
}

TCollection_AsciiString StopwatchStorage::PrintAll() const
{
  TCollection_AsciiString anOutput;
  for (NCollection_DataMap<TCollection_AsciiString, Stopwatch>::Iterator anIter(myStopwatches);
       anIter.More();
       anIter.Next())
  {
    print(anIter.Key(), anOutput);
  }
  return anOutput;
}

void StopwatchStorage::print(const TCollection_AsciiString& theName,
                             TCollection_AsciiString&       theOutput) const
{
  const Stopwatch* aStopwatch = myStopwatches.Seek(theName);
  if (aStopwatch == nullptr)
  {
    return;
  }

  if (!aStopwatch->IsActive())
  {
    theOutput += TCollection_AsciiString("Stopwatch ") + theName + " have never been started.\n";
    return;
  }

  if (aStopwatch->IsRunning())
  {
    theOutput += TCollection_AsciiString("Warning: Stopwatch ") + theName + " is still running.\n";
    return;
  }
  theOutput += TCollection_AsciiString("Stopwatch ") + theName + ": "
               + TCollection_AsciiString(aStopwatch->Elapsed()) + " sec\n";
}

OSD_PerfMeter::OSD_PerfMeter(const TCollection_AsciiString& theMeterName, const bool theToAutoStart)
{
  Init(theMeterName);

  if (theToAutoStart)
  {
    Start();
  }
}

OSD_PerfMeter::~OSD_PerfMeter() = default;

void OSD_PerfMeter::Init(const TCollection_AsciiString& theMeterName)
{
  myMeterName = theMeterName;
  if (!StopwatchStorage::Instance().HasStopwatch(myMeterName))
  {
    StopwatchStorage::Instance().CreateStopwatch(myMeterName);
  }
}

void OSD_PerfMeter::Start() const
{
  Stopwatch* aStopwatch = StopwatchStorage::Instance().GetStopwatch(myMeterName);
  if (aStopwatch != nullptr)
  {
    aStopwatch->Start();
  }
}

void OSD_PerfMeter::Stop() const
{
  Stopwatch* aStopwatch = StopwatchStorage::Instance().GetStopwatch(myMeterName);
  if (aStopwatch != nullptr)
  {
    aStopwatch->Stop();
  }
}

double OSD_PerfMeter::Elapsed() const
{
  Stopwatch* aStopwatch = StopwatchStorage::Instance().GetStopwatch(myMeterName);
  return aStopwatch ? aStopwatch->Elapsed() : 0.0;
}

void OSD_PerfMeter::Kill() const
{
  StopwatchStorage::Instance().KillStopwatch(myMeterName);
}

TCollection_AsciiString OSD_PerfMeter::Print() const
{
  Stopwatch* aStopwatch = StopwatchStorage::Instance().GetStopwatch(myMeterName);
  if (aStopwatch != nullptr)
  {
    return StopwatchStorage::Instance().Print(myMeterName);
  }
  return "";
}

TCollection_AsciiString OSD_PerfMeter::PrintALL()
{
  return StopwatchStorage::Instance().PrintAll();
}

void OSD_PerfMeter::ResetALL()
{
  StopwatchStorage::Instance().Clear();
}
