#pragma once

#include <Message_Alert.hpp>
#include <Message_Gravity.hpp>
#include <TCollection_AsciiString.hpp>

class Message_Attribute;
class Message_Report;

class Message_CompositeAlerts;

class Message_AlertExtended : public Message_Alert
{
public:
  Standard_EXPORT static occ::handle<Message_Alert> AddAlert(
    const occ::handle<Message_Report>&    theReport,
    const occ::handle<Message_Attribute>& theAttribute,
    const Message_Gravity                 theGravity);

public:
  Message_AlertExtended()
      : Message_Alert()
  {
  }

  Standard_EXPORT const char* GetMessageKey() const override;

  const occ::handle<Message_Attribute>& Attribute() const { return myAttribute; }

  void SetAttribute(const occ::handle<Message_Attribute>& theAttribute)
  {
    myAttribute = theAttribute;
  }

  Standard_EXPORT occ::handle<Message_CompositeAlerts> CompositeAlerts(
    const bool theToCreate = false);

  Standard_EXPORT bool SupportsMerge() const override;

  Standard_EXPORT bool Merge(const occ::handle<Message_Alert>& theTarget) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Message_AlertExtended, Message_Alert)

protected:
  occ::handle<Message_CompositeAlerts> myCompositAlerts;

  occ::handle<Message_Attribute> myAttribute;
};
