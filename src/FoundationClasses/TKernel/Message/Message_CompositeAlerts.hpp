#pragma once

#include <Message_Alert.hpp>
#include <Message_Gravity.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>

class Message_CompositeAlerts : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Message_CompositeAlerts, Standard_Transient)
public:
  Message_CompositeAlerts() = default;

  Standard_EXPORT const NCollection_List<occ::handle<Message_Alert>>& Alerts(
    const Message_Gravity theGravity) const;

  Standard_EXPORT bool AddAlert(Message_Gravity                   theGravity,
                                const occ::handle<Message_Alert>& theAlert);

  Standard_EXPORT bool RemoveAlert(Message_Gravity                   theGravity,
                                   const occ::handle<Message_Alert>& theAlert);

  Standard_EXPORT bool HasAlert(const occ::handle<Message_Alert>& theAlert);

  Standard_EXPORT bool HasAlert(const occ::handle<Standard_Type>& theType,
                                Message_Gravity                   theGravity);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Clear(Message_Gravity theGravity);

  Standard_EXPORT void Clear(const occ::handle<Standard_Type>& theType);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  NCollection_List<occ::handle<Message_Alert>> myAlerts[Message_Fail + 1];
};
