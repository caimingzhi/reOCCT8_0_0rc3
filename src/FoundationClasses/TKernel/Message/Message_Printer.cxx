#include <Message_Printer.hpp>

#include <Standard_Dump.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Message_Printer, Standard_Transient)

//=================================================================================================

Message_Printer::Message_Printer()
    : myTraceLevel(Message_Info)
{
}

//=================================================================================================

void Message_Printer::Send(const char* theString, const Message_Gravity theGravity) const
{
  if (theGravity >= myTraceLevel)
  {
    send(TCollection_AsciiString(theString), theGravity);
  }
}

//=================================================================================================

void Message_Printer::Send(const TCollection_ExtendedString& theString,
                           const Message_Gravity             theGravity) const
{
  if (theGravity >= myTraceLevel)
  {
    send(TCollection_AsciiString(theString), theGravity);
  }
}

//=================================================================================================

void Message_Printer::Send(const TCollection_AsciiString& theString,
                           const Message_Gravity          theGravity) const
{
  if (theGravity >= myTraceLevel)
  {
    send(theString, theGravity);
  }
}

//=================================================================================================

void Message_Printer::SendStringStream(const Standard_SStream& theStream,
                                       const Message_Gravity   theGravity) const
{
  if (theGravity >= myTraceLevel)
  {
    send(theStream.str().c_str(), theGravity);
  }
}

//=================================================================================================

void Message_Printer::SendObject(const occ::handle<Standard_Transient>& theObject,
                                 const Message_Gravity                  theGravity) const
{
  if (!theObject.IsNull() && theGravity >= myTraceLevel)
  {
    send(TCollection_AsciiString(theObject->DynamicType()->Name()) + ": "
           + Standard_Dump::GetPointerInfo(theObject),
         theGravity);
  }
}
