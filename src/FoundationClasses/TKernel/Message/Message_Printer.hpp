#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Message_Gravity.hpp>
#include <Standard_Transient.hpp>
#include <Standard_SStream.hpp>

class TCollection_ExtendedString;
class TCollection_AsciiString;

//! Abstract interface class defining printer as output context for text messages
//!
//! The message, besides being text string, has associated gravity
//! level, which can be used by printer to decide either to process a message or ignore it.
class Message_Printer : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Message_Printer, Standard_Transient)
public:
  //! Return trace level used for filtering messages;
  //! messages with lover gravity will be ignored.
  Message_Gravity GetTraceLevel() const { return myTraceLevel; }

  //! Set trace level used for filtering messages.
  //! By default, trace level is Message_Info, so that all messages are output
  void SetTraceLevel(const Message_Gravity theTraceLevel) { myTraceLevel = theTraceLevel; }

  //! Send a string message with specified trace level.
  //! The last Boolean argument is deprecated and unused.
  //! Default implementation redirects to send().
  Standard_EXPORT virtual void Send(const TCollection_ExtendedString& theString,
                                    const Message_Gravity             theGravity) const;

  //! Send a string message with specified trace level.
  //! The last Boolean argument is deprecated and unused.
  //! Default implementation redirects to send().
  Standard_EXPORT virtual void Send(const char* theString, const Message_Gravity theGravity) const;

  //! Send a string message with specified trace level.
  //! The last Boolean argument is deprecated and unused.
  //! Default implementation redirects to send().
  Standard_EXPORT virtual void Send(const TCollection_AsciiString& theString,
                                    const Message_Gravity          theGravity) const;

  //! Send a string message with specified trace level.
  //! Stream is converted to string value.
  //! Default implementation calls first method Send().
  Standard_EXPORT virtual void SendStringStream(const Standard_SStream& theStream,
                                                const Message_Gravity   theGravity) const;

  //! Send a string message with specified trace level.
  //! The object is converted to string in format: <object kind> : <object pointer>.
  //! Default implementation calls first method Send().
  Standard_EXPORT virtual void SendObject(const occ::handle<Standard_Transient>& theObject,
                                          const Message_Gravity                  theGravity) const;

protected:
  //! Empty constructor with Message_Info trace level
  Standard_EXPORT Message_Printer();

  //! Send a string message with specified trace level.
  //! This method must be redefined in descendant.
  Standard_EXPORT virtual void send(const TCollection_AsciiString& theString,
                                    const Message_Gravity          theGravity) const = 0;

protected:
  Message_Gravity myTraceLevel;
};
