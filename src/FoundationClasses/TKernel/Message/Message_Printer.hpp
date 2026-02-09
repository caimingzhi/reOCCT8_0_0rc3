#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Message_Gravity.hpp>
#include <Standard_Transient.hpp>
#include <Standard_SStream.hpp>

class TCollection_ExtendedString;
class TCollection_AsciiString;

class Message_Printer : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Message_Printer, Standard_Transient)
public:
  Message_Gravity GetTraceLevel() const { return myTraceLevel; }

  void SetTraceLevel(const Message_Gravity theTraceLevel) { myTraceLevel = theTraceLevel; }

  Standard_EXPORT virtual void Send(const TCollection_ExtendedString& theString,
                                    const Message_Gravity             theGravity) const;

  Standard_EXPORT virtual void Send(const char* theString, const Message_Gravity theGravity) const;

  Standard_EXPORT virtual void Send(const TCollection_AsciiString& theString,
                                    const Message_Gravity          theGravity) const;

  Standard_EXPORT virtual void SendStringStream(const Standard_SStream& theStream,
                                                const Message_Gravity   theGravity) const;

  Standard_EXPORT virtual void SendObject(const occ::handle<Standard_Transient>& theObject,
                                          const Message_Gravity                  theGravity) const;

protected:
  Standard_EXPORT Message_Printer();

  Standard_EXPORT virtual void send(const TCollection_AsciiString& theString,
                                    const Message_Gravity          theGravity) const = 0;

protected:
  Message_Gravity myTraceLevel;
};
