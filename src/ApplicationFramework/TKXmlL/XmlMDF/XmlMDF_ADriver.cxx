#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDF_ADriver.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDF_ADriver, Standard_Transient)

XmlMDF_ADriver::XmlMDF_ADriver(const occ::handle<Message_Messenger>& theMsgDriver,
                               const char*                           theNS,
                               const char*                           theName)
    : myNamespace(theNS == nullptr ? "" : theNS),
      myMessageDriver(theMsgDriver)
{
  if (theNS != nullptr)
    if (theNS[0] != '\0')
    {
      myTypeName = theNS;
      myTypeName += ':';
    }
  if (theName != nullptr)
    myTypeName += theName;
}

int XmlMDF_ADriver::VersionNumber() const
{
  return 0;
}

occ::handle<Standard_Type> XmlMDF_ADriver::SourceType() const
{
  return NewEmpty()->DynamicType();
}

const TCollection_AsciiString& XmlMDF_ADriver::TypeName() const
{
  const char* aString = myTypeName.ToCString();
  if (myTypeName.Length() == 0 || aString[myTypeName.Length() - 1] == ':')
    (TCollection_AsciiString&)myTypeName += SourceType()->Name();
  return myTypeName;
}
