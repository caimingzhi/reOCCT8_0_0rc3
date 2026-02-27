

#include <Message_AttributeObject.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_AttributeObject, System::log::Message_Attribute)

System::log::Message_AttributeObject::Message_AttributeObject(const occ::handle<Standard_Transient>& theObject,
                                                 const TCollection_AsciiString&         theName)
    : System::log::Message_Attribute(theName)
{
  myObject = theObject;
}

void System::log::Message_AttributeObject::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, System::log::Message_Attribute)

  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myObject.get())
}
