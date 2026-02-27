#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Message_Report.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>

namespace
{
  static const char* Message_Table_PrintMetricTypeEnum[13] = {"NONE",
                                                              "ThreadCPUUserTime",
                                                              "ThreadCPUSystemTime",
                                                              "ProcessCPUUserTime",
                                                              "ProcessCPUSystemTime",
                                                              "WallClock",
                                                              "MemPrivate",
                                                              "MemVirtual",
                                                              "MemWorkingSet",
                                                              "MemWorkingSetPeak",
                                                              "MemSwapUsage",
                                                              "MemSwapUsagePeak",
                                                              "MemHeapUsage"};
}

const occ::handle<System::log::Message_Messenger>& System::log::Message::DefaultMessenger()
{
  static occ::handle<System::log::Message_Messenger> aMessenger = new System::log::Message_Messenger;
  return aMessenger;
}

TCollection_AsciiString System::log::Message::FillTime(const int hour, const int minute, const double second)
{
  char t[30];
  if (hour > 0)
    Sprintf(t, "%02dh:%02dm:%.2fs", hour, minute, second);
  else if (minute > 0)
    Sprintf(t, "%02dm:%.2fs", minute, second);
  else
    Sprintf(t, "%.2fs", second);
  return TCollection_AsciiString(t);
}

const occ::handle<System::log::Message_Report>& System::log::Message::DefaultReport(const bool theToCreate)
{
  static occ::handle<System::log::Message_Report> MyReport;
  if (MyReport.IsNull() && theToCreate)
  {
    MyReport = new System::log::Message_Report();
  }
  return MyReport;
}

const char* System::log::Message::MetricToString(const Message_MetricType theType)
{
  return Message_Table_PrintMetricTypeEnum[theType];
}

bool System::log::Message::MetricFromString(const char* theString, Message_MetricType& theGravity)
{
  TCollection_AsciiString aName(theString);
  for (int aMetricIter = 0; aMetricIter <= Message_MetricType_MemHeapUsage; ++aMetricIter)
  {
    const char* aMetricName = Message_Table_PrintMetricTypeEnum[aMetricIter];
    if (aName == aMetricName)
    {
      theGravity = Message_MetricType(aMetricIter);
      return true;
    }
  }
  return false;
}

bool System::log::Message::ToOSDMetric(const Message_MetricType theMetric, System::os::OSD_MemInfo::Counter& theMemInfo)
{
  switch (theMetric)
  {
    case Message_MetricType_MemPrivate:
      theMemInfo = System::os::OSD_MemInfo::MemPrivate;
      break;
    case Message_MetricType_MemVirtual:
      theMemInfo = System::os::OSD_MemInfo::MemVirtual;
      break;
    case Message_MetricType_MemWorkingSet:
      theMemInfo = System::os::OSD_MemInfo::MemWorkingSet;
      break;
    case Message_MetricType_MemWorkingSetPeak:
      theMemInfo = System::os::OSD_MemInfo::MemWorkingSetPeak;
      break;
    case Message_MetricType_MemSwapUsage:
      theMemInfo = System::os::OSD_MemInfo::MemSwapUsage;
      break;
    case Message_MetricType_MemSwapUsagePeak:
      theMemInfo = System::os::OSD_MemInfo::MemSwapUsagePeak;
      break;
    case Message_MetricType_MemHeapUsage:
      theMemInfo = System::os::OSD_MemInfo::MemHeapUsage;
      break;
    default:
      return false;
  }
  return true;
}

bool System::log::Message::ToMessageMetric(const System::os::OSD_MemInfo::Counter theMemInfo, Message_MetricType& theMetric)
{
  switch (theMemInfo)
  {
    case System::os::OSD_MemInfo::MemPrivate:
      theMetric = Message_MetricType_MemPrivate;
      break;
    case System::os::OSD_MemInfo::MemVirtual:
      theMetric = Message_MetricType_MemVirtual;
      break;
    case System::os::OSD_MemInfo::MemWorkingSet:
      theMetric = Message_MetricType_MemWorkingSet;
      break;
    case System::os::OSD_MemInfo::MemWorkingSetPeak:
      theMetric = Message_MetricType_MemWorkingSetPeak;
      break;
    case System::os::OSD_MemInfo::MemSwapUsage:
      theMetric = Message_MetricType_MemSwapUsage;
      break;
    case System::os::OSD_MemInfo::MemSwapUsagePeak:
      theMetric = Message_MetricType_MemSwapUsagePeak;
      break;
    case System::os::OSD_MemInfo::MemHeapUsage:
      theMetric = Message_MetricType_MemHeapUsage;
      break;
    default:
      return false;
  }
  return true;
}
