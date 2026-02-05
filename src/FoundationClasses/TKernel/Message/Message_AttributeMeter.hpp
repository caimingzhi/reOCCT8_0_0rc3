#pragma once

#include <Message_Attribute.hpp>
#include <Message_MetricType.hpp>
#include <TCollection_AsciiString.hpp>

#include <NCollection_IndexedDataMap.hpp>

class Message_AlertExtended;

//! Alert object storing alert metrics values.
//! Start and stop values for each metric.
class Message_AttributeMeter : public Message_Attribute
{
public:
  //! Returns default value of the metric when it is not defined
  //! @return undefined value
  static double UndefinedMetricValue() { return -1.0; }

public:
  //! Constructor with string argument
  Standard_EXPORT Message_AttributeMeter(
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  //! Checks whether the attribute has values for the metric
  //! @param[in] theMetric  metric type
  //! @return true if the metric values exist in the attribute
  Standard_EXPORT bool HasMetric(const Message_MetricType& theMetric) const;

  //! Returns true when both values of the metric are set.
  //! @param[in] theMetric  metric type
  //! @return true if metric values are valid
  Standard_EXPORT bool IsMetricValid(const Message_MetricType& theMetric) const;

  //! Returns start value for the metric
  //! @param[in] theMetric  metric type
  //! @return real value
  Standard_EXPORT double StartValue(const Message_MetricType& theMetric) const;

  //! Sets start values for the metric
  //! @param[in] theMetric  metric type
  Standard_EXPORT void SetStartValue(const Message_MetricType& theMetric, const double theValue);

  //! Returns stop value for the metric
  //! @param[in] theMetric  metric type
  //! @return real value
  Standard_EXPORT double StopValue(const Message_MetricType& theMetric) const;

  //! Sets stop values for the metric
  //! @param[in] theMetric  metric type
  Standard_EXPORT void SetStopValue(const Message_MetricType& theMetric, const double theValue);

public:
  //! Sets start values of default report metrics into the alert
  //! @param theAlert an alert
  static void StartAlert(const occ::handle<Message_AlertExtended>& theAlert)
  {
    SetAlertMetrics(theAlert, true);
  }

  //! Sets stop values of default report metrics into the alert
  //! @param theAlert an alert
  static void StopAlert(const occ::handle<Message_AlertExtended>& theAlert)
  {
    SetAlertMetrics(theAlert, false);
  }

  //! Sets current values of default report metrics into the alert.
  //! Processed only alert with Message_AttributeMeter attribute
  //! @param theAlert an alert
  //! @param theStartValue flag, if true, the start value is collected otherwise stop
  static Standard_EXPORT void SetAlertMetrics(const occ::handle<Message_AlertExtended>& theAlert,
                                              const bool theStartValue);

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Message_AttributeMeter, Message_Attribute)

private:
  typedef std::pair<double, double> StartToStopValue;
  // clang-format off
  NCollection_IndexedDataMap<Message_MetricType, StartToStopValue> myMetrics; //!< computed metrics
  // clang-format on
};
