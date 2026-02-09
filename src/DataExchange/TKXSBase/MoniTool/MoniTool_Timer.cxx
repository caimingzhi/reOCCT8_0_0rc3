

#include <Standard_CString.hpp>
#include <Standard_CStringHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <MoniTool_Timer.hpp>
#include <MoniTool_TimerSentry.hpp>
#include <OSD_Timer.hpp>
#include <Standard_Type.hpp>

#include <cstdio>

class MoniTool_Timer;
IMPLEMENT_STANDARD_RTTIEXT(MoniTool_Timer, Standard_Transient)

void MoniTool_Timer::Dump(Standard_OStream& ostr)
{
  int    hours, minutes;
  double seconds, CPUtime, user, system;

  myTimer.Show(seconds, minutes, hours, CPUtime);
  myTimer.OSD_Chronometer::Show(user, system);

  double elapsed = seconds + minutes * 60 + hours * 3600;

  char buff[1024];
  Sprintf(buff,
          "Elapsed:%6.1f sec, CPU User:%9.4f sec, CPU Sys:%9.4f sec, hits: %d",
          elapsed,
          user,
          system,
          myCount);

  ostr << buff << std::endl;
}

NCollection_DataMap<const char*, occ::handle<MoniTool_Timer>, Standard_CStringHasher>&
  MoniTool_Timer::Dictionary()
{
  static NCollection_DataMap<const char*, occ::handle<MoniTool_Timer>, Standard_CStringHasher> dic;
  return dic;
}

occ::handle<MoniTool_Timer> MoniTool_Timer::Timer(const char* name)
{

  NCollection_DataMap<const char*, occ::handle<MoniTool_Timer>, Standard_CStringHasher>& dic =
    Dictionary();
  if (dic.IsBound(name))
    return dic.Find(name);
  occ::handle<MoniTool_Timer> MT = new MoniTool_Timer;
  MT->Timer().Reset();
  dic.Bind(name, MT);
  return MT;
}

void MoniTool_Timer::ClearTimers()
{
  Dictionary().Clear();
}

void MoniTool_Timer::DumpTimers(Standard_OStream& ostr)
{
  NCollection_DataMap<const char*, occ::handle<MoniTool_Timer>, Standard_CStringHasher>& dic =
    Dictionary();
  NCollection_DataMap<const char*, occ::handle<MoniTool_Timer>, Standard_CStringHasher>::Iterator
    iter(dic);

  int NbTimers = dic.Extent();

  ostr << "DUMP OF TIMERS:" << std::endl;
  const char** keys = new const char*[NbTimers];
  int          i    = 0;
  for (; iter.More() && i < NbTimers; iter.Next())
  {
    keys[i++] = iter.Key();
  }
  for (i = 0; i < NbTimers; i++)
  {
    int         ntmp = 0;
    const char* stmp = nullptr;
    for (int j = 0; j < NbTimers; j++)
    {
      if (keys[j] && (!stmp || strcmp(stmp, keys[j]) > 0))
      {
        ntmp = j;
        stmp = keys[j];
      }
    }

    char buff[1024];
    Sprintf(buff, "%-20s\t", stmp);
    ostr << "TIMER: " << buff;

    Timer(stmp)->Dump(ostr);
    keys[ntmp] = nullptr;
    if (Timer(stmp)->IsRunning())
      std::cerr << "Warning: timer " << stmp << " is running" << std::endl;
  }
  delete[] keys;
}

static double amAccess = 0., amInternal = 0., amExternal = 0., amError = 0.;

void MoniTool_Timer::ComputeAmendments()
{
  const int NBTESTS = 100000;

  int i;

  occ::handle<MoniTool_Timer> MT0 = MoniTool_Timer::Timer("_mt_amend_0_");
  occ::handle<MoniTool_Timer> MT1 = MoniTool_Timer::Timer("_mt_amend_1_");
  occ::handle<MoniTool_Timer> MT2 = MoniTool_Timer::Timer("_mt_amend_2_");
  occ::handle<MoniTool_Timer> MT3 = MoniTool_Timer::Timer("_mt_amend_3_");
  MT0->Reset();
  MT1->Reset();
  MT2->Reset();
  MT3->Reset();
  MoniTool_Timer::Timer("_mt_amend_t1_")->Reset();
  MoniTool_Timer::Timer("_mt_amend_t2_")->Reset();
  MoniTool_Timer::Timer("_mt_amend_t3_")->Reset();

  MT0->Start();
  for (i = 1; i <= NBTESTS; i++)
  {
    for (int k = 1; k <= 100; k++) [[maybe_unused]]
      const double aDummy = std::sqrt(i + k);
  }
  MT0->Stop();

  occ::handle<MoniTool_Timer> MT = MoniTool_Timer::Timer("_mt_amend_t1_");
  MT1->Start();
  for (i = 1; i <= NBTESTS; i++)
  {
    MT->Start();
    for (int k = 1; k <= 100; k++) [[maybe_unused]]
      const double aDummy = std::sqrt(i + k);
    MT->Stop();
  }
  MT1->Stop();

  MT2->Start();
  for (i = 1; i <= NBTESTS; i++)
  {
    MoniTool_TimerSentry TS("_mt_amend_t2_");
    for (int k = 1; k <= 100; k++)
    {
      [[maybe_unused]] double aVal = std::sqrt(i + k);
    }
  }
  MT2->Stop();

  MT3->Start();
  for (i = 1; i <= NBTESTS; i++)
  {
    MoniTool_Timer::Start("_mt_amend_t3_");
    for (int k = 1; k <= 100; k++)
    {
      [[maybe_unused]] double aVal = std::sqrt(i + k);
    }
    MoniTool_Timer::Stop("_mt_amend_t3_");
  }
  MT3->Stop();

  double cpu0, cpu1, cpu2, cpu3, cput1, cput2, cput3;
  cpu0  = MoniTool_Timer::Timer("_mt_amend_0_")->CPU();
  cpu1  = MoniTool_Timer::Timer("_mt_amend_1_")->CPU();
  cput1 = MT->CPU();
  cpu2  = MoniTool_Timer::Timer("_mt_amend_2_")->CPU();
  cput2 = MoniTool_Timer::Timer("_mt_amend_t2_")->CPU();
  cpu3  = MoniTool_Timer::Timer("_mt_amend_3_")->CPU();
  cput3 = MoniTool_Timer::Timer("_mt_amend_t3_")->CPU();

  amExternal += (cpu1 - cpu0) / NBTESTS;
  amInternal += (cput1 - cpu0) / NBTESTS;
  amAccess += (0.5 * (cpu3 - cpu1)) / NBTESTS;
  amError = std::abs(cpu1 + cpu3 - 2 * cpu2) / NBTESTS;

  std::cout << "CPU 0: " << cpu0 << std::endl;
  std::cout << "CPU 1: " << cpu1 << " INTERNAL: " << cput1 << std::endl;
  std::cout << "CPU 2: " << cpu2 << " INTERNAL: " << cput2 << std::endl;
  std::cout << "CPU 3: " << cpu3 << " INTERNAL: " << cput3 << std::endl;
  std::cout << "Access: " << amAccess << ", External: " << amExternal
            << ", Internal: " << amInternal << ", Error: " << amError << std::endl;
}

void MoniTool_Timer::GetAmendments(double& access,
                                   double& internal,
                                   double& external,
                                   double& error10)
{
  access   = amAccess;
  internal = amInternal;
  external = amExternal;
  error10  = amError;
}

static occ::handle<MoniTool_Timer> myActive;

void MoniTool_Timer::AmendAccess()
{
  double amend = amAccess;
  for (occ::handle<MoniTool_Timer> act = myActive; !act.IsNull(); act = act->myNext)
    act->myAmend += amend;
}

void MoniTool_Timer::AmendStart()
{
  double amend = amExternal;
  for (occ::handle<MoniTool_Timer> act = myActive; !act.IsNull(); act = act->myNext)
    act->myAmend += amend;
  myAmend += amInternal;

  if (!myActive.IsNull())
  {
    myActive->myPrev = this;
    myNext           = myActive;
  }
  myActive = this;
}

void MoniTool_Timer::AmendStop()
{
  occ::handle<MoniTool_Timer> thisActive(this);
  if (myActive == thisActive)
    myActive = myNext;

  if (!myPrev.IsNull())
    myPrev->myNext = myNext;
  if (!myNext.IsNull())
    myNext->myPrev = myPrev;

  myNext = myPrev = nullptr;
}
