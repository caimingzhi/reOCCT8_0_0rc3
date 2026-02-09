

#include <Message_Attribute.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Message_Attribute, Standard_Transient)

Message_Attribute::Message_Attribute(const TCollection_AsciiString& theName)
    : myName(theName)
{
}

const char* Message_Attribute::GetMessageKey() const
{
  return !myName.IsEmpty() ? myName.ToCString() : "";
}

void Message_Attribute::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myName)
}
