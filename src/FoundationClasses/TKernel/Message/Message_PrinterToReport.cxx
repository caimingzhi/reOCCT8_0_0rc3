

#include <Message_PrinterToReport.hpp>

#include <Message.hpp>
#include <Message_AttributeMeter.hpp>
#include <Message_AttributeObject.hpp>
#include <Message_AttributeStream.hpp>
#include <Message_Report.hpp>

#include <Standard_Dump.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_PrinterToReport, System::log::Message_Printer)

const occ::handle<System::log::Message_Report>& System::log::Message_PrinterToReport::Report() const
{
  if (!myReport.IsNull())
  {
    return myReport;
  }

  return System::log::Message::DefaultReport(true);
}

void System::log::Message_PrinterToReport::SendStringStream(const Standard_SStream& theStream,
                                               const Message_Gravity   theGravity) const
{
  const occ::handle<System::log::Message_Report>& aReport = Report();
  if (!aReport->ActiveMetrics().IsEmpty())
  {
    sendMetricAlert(theStream.str().c_str(), theGravity);
    return;
  }
  if (Standard_Dump::HasChildKey(Standard_Dump::Text(theStream)))
  {
    System::log::Message_AlertExtended::AddAlert(aReport,
                                    new System::log::Message_AttributeStream(theStream, myName),
                                    theGravity);
    myName.Clear();
  }
  else
  {
    if (!myName.IsEmpty())
    {
      TCollection_AsciiString aName = myName;
      myName.Clear();
      send(aName, theGravity);
    }
    myName = Standard_Dump::Text(theStream);
  }
}

void System::log::Message_PrinterToReport::SendObject(const occ::handle<Standard_Transient>& theObject,
                                         const Message_Gravity                  theGravity) const
{
  const occ::handle<System::log::Message_Report>& aReport = Report();
  if (!aReport->ActiveMetrics().IsEmpty())
  {
    sendMetricAlert(myName, theGravity);
    return;
  }

  System::log::Message_AlertExtended::AddAlert(aReport,
                                  new System::log::Message_AttributeObject(theObject, myName),
                                  theGravity);
}

void System::log::Message_PrinterToReport::send(const TCollection_AsciiString& theString,
                                   const Message_Gravity          theGravity) const
{
  if (!myName.IsEmpty())
  {
    TCollection_AsciiString aName = myName;
    myName.Clear();
    send(aName, theGravity);
  }

  const occ::handle<System::log::Message_Report>& aReport = Report();
  if (!aReport->ActiveMetrics().IsEmpty())
  {
    sendMetricAlert(theString, theGravity);
    return;
  }
  System::log::Message_AlertExtended::AddAlert(aReport, new System::log::Message_Attribute(theString), theGravity);
}

void System::log::Message_PrinterToReport::sendMetricAlert(const TCollection_AsciiString& theValue,
                                              const Message_Gravity          theGravity) const
{
  System::log::Message_AlertExtended::AddAlert(Report(), new System::log::Message_AttributeMeter(theValue), theGravity);
}
