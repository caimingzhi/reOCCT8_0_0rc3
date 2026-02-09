#include <Message_Messenger.hpp>

#include <Message_Printer.hpp>
#include <Message_PrinterOStream.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Message_Messenger, Standard_Transient)

Message_Messenger::Message_Messenger()
{
  AddPrinter(new Message_PrinterOStream);
}

Message_Messenger::Message_Messenger(const occ::handle<Message_Printer>& thePrinter)
{
  AddPrinter(thePrinter);
}

bool Message_Messenger::AddPrinter(const occ::handle<Message_Printer>& thePrinter)
{

  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (aPrinter == thePrinter)
    {
      return false;
    }
  }

  myPrinters.Append(thePrinter);
  return true;
}

bool Message_Messenger::RemovePrinter(const occ::handle<Message_Printer>& thePrinter)
{

  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (aPrinter == thePrinter)
    {
      myPrinters.Remove(aPrinterIter);
      return true;
    }
  }
  return false;
}

int Message_Messenger::RemovePrinters(const occ::handle<Standard_Type>& theType)
{

  int nb = 0;
  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();)
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (!aPrinter.IsNull() && aPrinter->IsKind(theType))
    {
      myPrinters.Remove(aPrinterIter);
      nb++;
    }
    else
    {
      aPrinterIter.Next();
    }
  }
  return nb;
}

void Message_Messenger::Send(const char* theString, const Message_Gravity theGravity) const
{
  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (!aPrinter.IsNull())
    {
      aPrinter->Send(theString, theGravity);
    }
  }
}

void Message_Messenger::Send(const Standard_SStream& theStream,
                             const Message_Gravity   theGravity) const
{
  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (!aPrinter.IsNull())
    {
      aPrinter->SendStringStream(theStream, theGravity);
    }
  }
}

void Message_Messenger::Send(const TCollection_AsciiString& theString,
                             const Message_Gravity          theGravity) const
{
  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (!aPrinter.IsNull())
    {
      aPrinter->Send(theString, theGravity);
    }
  }
}

void Message_Messenger::Send(const TCollection_ExtendedString& theString,
                             const Message_Gravity             theGravity) const
{
  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (!aPrinter.IsNull())
    {
      aPrinter->Send(theString, theGravity);
    }
  }
}

void Message_Messenger::Send(const occ::handle<Standard_Transient>& theObject,
                             const Message_Gravity                  theGravity) const
{
  for (NCollection_Sequence<occ::handle<Message_Printer>>::Iterator aPrinterIter(myPrinters);
       aPrinterIter.More();
       aPrinterIter.Next())
  {
    const occ::handle<Message_Printer>& aPrinter = aPrinterIter.Value();
    if (!aPrinter.IsNull())
    {
      aPrinter->SendObject(theObject, theGravity);
    }
  }
}

void Message_Messenger::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myPrinters.Size())
}
