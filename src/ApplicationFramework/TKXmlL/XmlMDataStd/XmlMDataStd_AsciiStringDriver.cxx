#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_AsciiStringDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_AsciiStringDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(AttributeIDString, "asciiguid")

XmlMDataStd_AsciiStringDriver::XmlMDataStd_AsciiStringDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_AsciiStringDriver::NewEmpty() const
{
  return (new TDataStd_AsciiString());
}

bool XmlMDataStd_AsciiStringDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                          const occ::handle<TDF_Attribute>& theTarget,
                                          XmlObjMgt_RRelocationTable&) const
{
  if (!theTarget.IsNull())
  {
    const TCollection_AsciiString aString = XmlObjMgt::GetStringValue(theSource);
    occ::down_cast<TDataStd_AsciiString>(theTarget)->Set(aString);

    Standard_GUID            aGUID;
    const XmlObjMgt_Element& anElement = theSource;
    XmlObjMgt_DOMString      aGUIDStr  = anElement.getAttribute(::AttributeIDString());
    if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
      aGUID = TDataStd_AsciiString::GetID();
    else
      aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));

    occ::down_cast<TDataStd_AsciiString>(theTarget)->SetID(aGUID);
    return true;
  }
  myMessageDriver->Send("error retrieving AsciiString for type TDataStd_AsciiString", Message_Fail);
  return false;
}

void XmlMDataStd_AsciiStringDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                          XmlObjMgt_Persistent&             theTarget,
                                          XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_AsciiString> aS = occ::down_cast<TDataStd_AsciiString>(theSource);
  if (aS.IsNull())
    return;
  XmlObjMgt_DOMString aString = aS->Get().ToCString();
  XmlObjMgt::SetStringValue(theTarget, aString);
  if (aS->ID() != TDataStd_AsciiString::GetID())
  {

    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    aS->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
