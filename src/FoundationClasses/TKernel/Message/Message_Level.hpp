#pragma once

#include <Message.hpp>
#include <Message_AlertExtended.hpp>
#include <Message_Gravity.hpp>
#include <Message_Messenger.hpp>
#include <TCollection_AsciiString.hpp>

#include <Standard.hpp>

class Message_Level
{
public:
  Standard_EXPORT Message_Level(
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  Standard_EXPORT ~Message_Level();

  const occ::handle<Message_AlertExtended>& RootAlert() const { return myRootAlert; }

  Standard_EXPORT void SetRootAlert(const occ::handle<Message_AlertExtended>& theAlert,
                                    const bool                                isRequiredToStart);

  Standard_EXPORT bool AddAlert(const Message_Gravity             theGravity,
                                const occ::handle<Message_Alert>& theAlert);

private:
  Standard_EXPORT void remove();

private:
  occ::handle<Message_AlertExtended> myRootAlert;
  occ::handle<Message_AlertExtended> myLastAlert;
};

#define OCCT_ADD_MESSAGE_LEVEL_SENTRY(theMessage) Message_Level aLevel(theMessage);
