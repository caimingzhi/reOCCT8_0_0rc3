#pragma once

#include <Message_Printer.hpp>
#include <TCollection_AsciiString.hpp>

namespace System { namespace log {
class Message_PrinterSystemLog : public System::log::Message_Printer
{
  DEFINE_STANDARD_RTTIEXT(Message_PrinterSystemLog, Message_Printer)
public:
  Standard_EXPORT Message_PrinterSystemLog(const TCollection_AsciiString& theEventSourceName,
                                           const Message_Gravity theTraceLevel = Message_Info);

  Standard_EXPORT ~Message_PrinterSystemLog() override;

protected:
  Standard_EXPORT void send(const TCollection_AsciiString& theString,
                            const Message_Gravity          theGravity) const override;

private:
  TCollection_AsciiString myEventSourceName;
#ifdef _WIN32
  void* myEventSource;
#endif
};
}} // namespace System::log

