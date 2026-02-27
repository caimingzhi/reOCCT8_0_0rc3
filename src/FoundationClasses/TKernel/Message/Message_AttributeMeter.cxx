

#include <Message_AttributeMeter.hpp>

#include <Message_Report.hpp>
#include <OSD_Timer.hpp>

#include <Precision.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_AttributeMeter, System::log::Message_Attribute)

System::log::Message_AttributeMeter::Message_AttributeMeter(const TCollection_AsciiString& theName)
    : System::log::Message_Attribute(theName)
{
}

bool System::log::Message_AttributeMeter::HasMetric(const Message_MetricType& theMetric) const
{
  return myMetrics.Contains(theMetric);
}

bool System::log::Message_AttributeMeter::IsMetricValid(const Message_MetricType& theMetric) const
{
  return std::abs(StartValue(theMetric) - UndefinedMetricValue()) > math::precision::Precision::Confusion()
         && std::abs(StopValue(theMetric) - UndefinedMetricValue()) > math::precision::Precision::Confusion();
}

double System::log::Message_AttributeMeter::StartValue(const Message_MetricType& theMetric) const
{
  if (!HasMetric(theMetric))
  {
    return UndefinedMetricValue();
  }

  return myMetrics.Seek(theMetric)->first;
}

void System::log::Message_AttributeMeter::SetStartValue(const Message_MetricType& theMetric,
                                           const double              theValue)
{
  if (StartToStopValue* aValPtr = myMetrics.ChangeSeek(theMetric))
  {
    aValPtr->first = theValue;
  }
  else
  {
    myMetrics.Add(theMetric, std::make_pair(theValue, UndefinedMetricValue()));
  }
}

double System::log::Message_AttributeMeter::StopValue(const Message_MetricType& theMetric) const
{
  if (!HasMetric(theMetric))
  {
    return UndefinedMetricValue();
  }
  return myMetrics.Seek(theMetric)->second;
}

void System::log::Message_AttributeMeter::SetStopValue(const Message_MetricType& theMetric,
                                          const double              theValue)
{
  if (StartToStopValue* aValPtr = myMetrics.ChangeSeek(theMetric))
  {
    aValPtr->second = theValue;
  }
}

void System::log::Message_AttributeMeter::SetAlertMetrics(const occ::handle<System::log::Message_AlertExtended>& theAlert,
                                             const bool theStartValue)
{
  if (theAlert.IsNull())
  {
    return;
  }

  occ::handle<System::log::Message_AttributeMeter> aMeterAttribute =
    occ::down_cast<System::log::Message_AttributeMeter>(theAlert->Attribute());
  if (aMeterAttribute.IsNull())
  {
    return;
  }

  occ::handle<System::log::Message_Report>                       aReport         = System::log::Message::DefaultReport(true);
  const NCollection_IndexedMap<Message_MetricType>& anActiveMetrics = aReport->ActiveMetrics();

  if (anActiveMetrics.Contains(Message_MetricType_WallClock))
  {
    System::os::OSD_Timer aTimer;
    aTimer.Start();
    double aTime = System::os::OSD_Timer::GetWallClockTime();
    if (theStartValue)
      aMeterAttribute->SetStartValue(Message_MetricType_WallClock, aTime);
    else
      aMeterAttribute->SetStopValue(Message_MetricType_WallClock, aTime);
  }
  if (anActiveMetrics.Contains(Message_MetricType_ProcessCPUUserTime)
      || anActiveMetrics.Contains(Message_MetricType_ProcessCPUSystemTime)
      || anActiveMetrics.Contains(Message_MetricType_ThreadCPUUserTime)
      || anActiveMetrics.Contains(Message_MetricType_ThreadCPUSystemTime))
  {
    if (anActiveMetrics.Contains(Message_MetricType_ProcessCPUUserTime)
        || anActiveMetrics.Contains(Message_MetricType_ProcessCPUSystemTime))
    {
      double aProcessUserTime, aProcessSystemTime;
      System::os::OSD_Chronometer::GetProcessCPU(aProcessUserTime, aProcessSystemTime);
      if (anActiveMetrics.Contains(Message_MetricType_ProcessCPUUserTime))
      {
        if (theStartValue)
        {
          aMeterAttribute->SetStartValue(Message_MetricType_ProcessCPUUserTime, aProcessUserTime);
        }
        else
        {
          aMeterAttribute->SetStopValue(Message_MetricType_ProcessCPUUserTime, aProcessUserTime);
        }
      }
      if (anActiveMetrics.Contains(Message_MetricType_ProcessCPUSystemTime))
      {
        if (theStartValue)
        {
          aMeterAttribute->SetStartValue(Message_MetricType_ProcessCPUSystemTime,
                                         aProcessSystemTime);
        }
        else
        {
          aMeterAttribute->SetStopValue(Message_MetricType_ProcessCPUSystemTime,
                                        aProcessSystemTime);
        }
      }
    }
    if (anActiveMetrics.Contains(Message_MetricType_ThreadCPUUserTime)
        || anActiveMetrics.Contains(Message_MetricType_ThreadCPUSystemTime))
    {
      double aThreadUserTime, aThreadSystemTime;
      System::os::OSD_Chronometer::GetThreadCPU(aThreadUserTime, aThreadSystemTime);
      if (anActiveMetrics.Contains(Message_MetricType_ThreadCPUUserTime))
      {
        if (theStartValue)
        {
          aMeterAttribute->SetStartValue(Message_MetricType_ThreadCPUUserTime, aThreadUserTime);
        }
        else
        {
          aMeterAttribute->SetStopValue(Message_MetricType_ThreadCPUUserTime, aThreadUserTime);
        }
      }
      if (anActiveMetrics.Contains(Message_MetricType_ThreadCPUSystemTime))
      {
        if (theStartValue)
        {
          aMeterAttribute->SetStartValue(Message_MetricType_ThreadCPUSystemTime, aThreadSystemTime);
        }
        else
        {
          aMeterAttribute->SetStopValue(Message_MetricType_ThreadCPUSystemTime, aThreadSystemTime);
        }
      }
    }
  }

  System::os::OSD_MemInfo aMemInfo(false);
  aMemInfo.SetActive(false);
  NCollection_IndexedMap<System::os::OSD_MemInfo::Counter> aCounters;
  for (NCollection_IndexedMap<Message_MetricType>::Iterator anIterator(anActiveMetrics);
       anIterator.More();
       anIterator.Next())
  {
    System::os::OSD_MemInfo::Counter anInfoCounter;
    if (!System::log::Message::ToOSDMetric(anIterator.Value(), anInfoCounter))
    {
      continue;
    }

    aCounters.Add(anInfoCounter);
    aMemInfo.SetActive(anInfoCounter, true);
  }
  if (aCounters.IsEmpty())
  {
    return;
  }

  aMemInfo.Update();
  Message_MetricType aMetricType;
  for (NCollection_IndexedMap<System::os::OSD_MemInfo::Counter>::Iterator anIterator(aCounters);
       anIterator.More();
       anIterator.Next())
  {
    if (!System::log::Message::ToMessageMetric(anIterator.Value(), aMetricType))
    {
      continue;
    }

    if (theStartValue)
    {
      aMeterAttribute->SetStartValue(aMetricType,
                                     (double)aMemInfo.ValuePreciseMiB(anIterator.Value()));
    }
    else
    {
      aMeterAttribute->SetStopValue(aMetricType,
                                    (double)aMemInfo.ValuePreciseMiB(anIterator.Value()));
    }
  }
}

void System::log::Message_AttributeMeter::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, System::log::Message_Attribute)

  for (NCollection_IndexedDataMap<Message_MetricType, StartToStopValue>::Iterator anIterator(
         myMetrics);
       anIterator.More();
       anIterator.Next())
  {
    OCCT_DUMP_VECTOR_CLASS(theOStream,
                           System::log::Message::MetricToString(anIterator.Key()),
                           2,
                           anIterator.Value().first,
                           anIterator.Value().second)
  }
}
