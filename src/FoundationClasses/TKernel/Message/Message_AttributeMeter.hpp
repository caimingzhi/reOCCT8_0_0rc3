#pragma once

#include <Message_Attribute.hpp>
#include <Message_MetricType.hpp>
#include <TCollection_AsciiString.hpp>

#include <NCollection_IndexedDataMap.hpp>

class Message_AlertExtended;

class Message_AttributeMeter : public Message_Attribute
{
public:
  static double UndefinedMetricValue() { return -1.0; }

public:
  Standard_EXPORT Message_AttributeMeter(
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  Standard_EXPORT bool HasMetric(const Message_MetricType& theMetric) const;

  Standard_EXPORT bool IsMetricValid(const Message_MetricType& theMetric) const;

  Standard_EXPORT double StartValue(const Message_MetricType& theMetric) const;

  Standard_EXPORT void SetStartValue(const Message_MetricType& theMetric, const double theValue);

  Standard_EXPORT double StopValue(const Message_MetricType& theMetric) const;

  Standard_EXPORT void SetStopValue(const Message_MetricType& theMetric, const double theValue);

public:
  static void StartAlert(const occ::handle<Message_AlertExtended>& theAlert)
  {
    SetAlertMetrics(theAlert, true);
  }

  static void StopAlert(const occ::handle<Message_AlertExtended>& theAlert)
  {
    SetAlertMetrics(theAlert, false);
  }

  static Standard_EXPORT void SetAlertMetrics(const occ::handle<Message_AlertExtended>& theAlert,
                                              const bool theStartValue);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Message_AttributeMeter, Message_Attribute)

private:
  typedef std::pair<double, double> StartToStopValue;

  NCollection_IndexedDataMap<Message_MetricType, StartToStopValue> myMetrics;
};
