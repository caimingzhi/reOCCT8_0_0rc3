#pragma once

#include <Message_Attribute.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DefineAlloc.hpp>

class Message_AttributeObject : public Message_Attribute
{
  DEFINE_STANDARD_RTTIEXT(Message_AttributeObject, Message_Attribute)
public:
  Standard_EXPORT Message_AttributeObject(
    const occ::handle<Standard_Transient>& theObject,
    const TCollection_AsciiString&         theName = TCollection_AsciiString::EmptyString());

  const occ::handle<Standard_Transient>& Object() const { return myObject; }

  void SetObject(const occ::handle<Standard_Transient>& theObject) { myObject = theObject; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  occ::handle<Standard_Transient> myObject;
};
