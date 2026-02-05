#pragma once

#include <Message_Printer.hpp>
#include <TCollection_AsciiString.hpp>

//! Implementation of a message printer associated with system log.
//! Implemented for the following systems:
//! - Windows, through ReportEventW().
//! - Android, through __android_log_write().
//! - UNIX/Linux, through syslog().
class Message_PrinterSystemLog : public Message_Printer
{
  DEFINE_STANDARD_RTTIEXT(Message_PrinterSystemLog, Message_Printer)
public:
  //! Main constructor.
  Standard_EXPORT Message_PrinterSystemLog(const TCollection_AsciiString& theEventSourceName,
                                           const Message_Gravity theTraceLevel = Message_Info);

  //! Destructor.
  Standard_EXPORT ~Message_PrinterSystemLog() override;

protected:
  //! Puts a message to the system log.
  Standard_EXPORT void send(const TCollection_AsciiString& theString,
                            const Message_Gravity          theGravity) const override;

private:
  TCollection_AsciiString myEventSourceName;
#ifdef _WIN32
  void* myEventSource;
#endif
};
