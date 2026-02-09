#pragma once

#include <Message_Messenger.hpp>
#include <Message_Gravity.hpp>
#include <Message_MetricType.hpp>
#include <NCollection_Vector.hpp>
#include <OSD_MemInfo.hpp>

#include <TCollection_AsciiString.hpp>

class Message_Report;

class Message
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static const occ::handle<Message_Messenger>& DefaultMessenger();

public:
  static Message_Messenger::StreamBuffer Send(Message_Gravity theGravity)
  {
    return DefaultMessenger()->Send(theGravity);
  }

  static void Send(const TCollection_AsciiString& theMessage, Message_Gravity theGravity)
  {
    DefaultMessenger()->Send(theMessage, theGravity);
  }

  static Message_Messenger::StreamBuffer SendFail() { return DefaultMessenger()->SendFail(); }

  static Message_Messenger::StreamBuffer SendAlarm() { return DefaultMessenger()->SendAlarm(); }

  static Message_Messenger::StreamBuffer SendWarning() { return DefaultMessenger()->SendWarning(); }

  static Message_Messenger::StreamBuffer SendInfo() { return DefaultMessenger()->SendInfo(); }

  static Message_Messenger::StreamBuffer SendTrace() { return DefaultMessenger()->SendTrace(); }

  static void SendFail(const TCollection_AsciiString& theMessage)
  {
    return DefaultMessenger()->SendFail(theMessage);
  }

  static void SendAlarm(const TCollection_AsciiString& theMessage)
  {
    return DefaultMessenger()->SendAlarm(theMessage);
  }

  static void SendWarning(const TCollection_AsciiString& theMessage)
  {
    return DefaultMessenger()->SendWarning(theMessage);
  }

  static void SendInfo(const TCollection_AsciiString& theMessage)
  {
    return DefaultMessenger()->SendInfo(theMessage);
  }

  static void SendTrace(const TCollection_AsciiString& theMessage)
  {
    return DefaultMessenger()->SendTrace(theMessage);
  }

public:
  Standard_EXPORT static TCollection_AsciiString FillTime(const int    Hour,
                                                          const int    Minute,
                                                          const double Second);

public:
  Standard_EXPORT static const occ::handle<Message_Report>& DefaultReport(
    const bool theToCreate = false);

  Standard_EXPORT static bool MetricFromString(const char* theString, Message_MetricType& theType);

  Standard_EXPORT static const char* MetricToString(const Message_MetricType theType);

  static Message_MetricType MetricFromString(const char* theString)
  {
    Message_MetricType aMetric = Message_MetricType_None;
    MetricFromString(theString, aMetric);
    return aMetric;
  }

  static Standard_EXPORT bool ToOSDMetric(const Message_MetricType theMetric,
                                          OSD_MemInfo::Counter&    theMemInfo);

  static Standard_EXPORT bool ToMessageMetric(const OSD_MemInfo::Counter theMemInfo,
                                              Message_MetricType&        theMetric);
};
