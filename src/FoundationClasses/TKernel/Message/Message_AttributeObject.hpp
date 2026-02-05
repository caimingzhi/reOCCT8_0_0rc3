#pragma once

#include <Message_Attribute.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DefineAlloc.hpp>

//! Alert object storing a transient object
class Message_AttributeObject : public Message_Attribute
{
  DEFINE_STANDARD_RTTIEXT(Message_AttributeObject, Message_Attribute)
public:
  //! Constructor with string argument
  Standard_EXPORT Message_AttributeObject(
    const occ::handle<Standard_Transient>& theObject,
    const TCollection_AsciiString&         theName = TCollection_AsciiString::EmptyString());

  //! Returns object
  //! @return the object instance
  const occ::handle<Standard_Transient>& Object() const { return myObject; }

  //! Sets the object
  //! @param theObject an instance
  void SetObject(const occ::handle<Standard_Transient>& theObject) { myObject = theObject; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  occ::handle<Standard_Transient> myObject; //!< alert object
};
