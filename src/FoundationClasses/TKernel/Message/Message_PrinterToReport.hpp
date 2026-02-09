#pragma once

#include <Message_Printer.hpp>
#include <TCollection_AsciiString.hpp>

class Message_Report;

class Message_PrinterToReport : public Message_Printer
{
  DEFINE_STANDARD_RTTIEXT(Message_PrinterToReport, Message_Printer)
public:
  Message_PrinterToReport() = default;

  ~Message_PrinterToReport() override = default;

  Standard_EXPORT const occ::handle<Message_Report>& Report() const;

  void SetReport(const occ::handle<Message_Report>& theReport) { myReport = theReport; }

  Standard_EXPORT void SendStringStream(const Standard_SStream& theStream,
                                        const Message_Gravity   theGravity) const override;

  Standard_EXPORT void SendObject(const occ::handle<Standard_Transient>& theObject,
                                  const Message_Gravity                  theGravity) const override;

protected:
  Standard_EXPORT void send(const TCollection_AsciiString& theString,
                            const Message_Gravity          theGravity) const override;

  Standard_EXPORT void sendMetricAlert(const TCollection_AsciiString& theValue,
                                       const Message_Gravity          theGravity) const;

private:
  mutable TCollection_AsciiString myName;
  occ::handle<Message_Report>     myReport;
};
