#include <TopoDS_AlertAttribute.hpp>

#include <Message_PrinterToReport.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_AlertAttribute, System::log::Message_Attribute)

TopoDS_AlertAttribute::TopoDS_AlertAttribute(const TopoDS_Shape&            theShape,
                                             const TCollection_AsciiString& theName)
    : System::log::Message_AttributeStream(Standard_SStream(), theName),
      myShape(theShape)
{
  Standard_SStream aStream;
  theShape.DumpJson(aStream);

  SetStream(aStream);
}

void TopoDS_AlertAttribute::Send(const occ::handle<System::log::Message_Messenger>& theMessenger,
                                 const TopoDS_Shape&                   theShape)
{
  for (NCollection_Sequence<occ::handle<System::log::Message_Printer>>::Iterator aPrinterIter(
         theMessenger->Printers());
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<System::log::Message_Printer>& aPrinter = aPrinterIter.Value();
    if (!aPrinter->IsKind(STANDARD_TYPE(System::log::Message_PrinterToReport)))
    {
      continue;
    }

    occ::handle<System::log::Message_PrinterToReport> aPrinterToReport =
      occ::down_cast<System::log::Message_PrinterToReport>(aPrinter);
    const occ::handle<System::log::Message_Report>& aReport = aPrinterToReport->Report();

    System::log::Message_AlertExtended::AddAlert(aReport, new TopoDS_AlertAttribute(theShape), Message_Info);
  }
}

void TopoDS_AlertAttribute::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, System::log::Message_Attribute)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myShape)
}
