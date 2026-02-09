#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_UAttribute.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_UAttributeDriver.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_UAttributeDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(GuidString, "guid")

XmlMDataStd_UAttributeDriver::XmlMDataStd_UAttributeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_UAttributeDriver::NewEmpty() const
{
  return (new TDataStd_UAttribute());
}

bool XmlMDataStd_UAttributeDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         XmlObjMgt_RRelocationTable&) const
{
  XmlObjMgt_DOMString aGuidDomStr = theSource.Element().getAttribute(::GuidString());
  const char*         aGuidStr    = (const char*)aGuidDomStr.GetString();
  if (aGuidStr[0] == '\0')
  {
    myMessageDriver->Send("error retrieving GUID for type TDataStd_UAttribute", Message_Fail);
    return false;
  }

  occ::down_cast<TDataStd_UAttribute>(theTarget)->SetID(aGuidStr);
  return true;
}

void XmlMDataStd_UAttributeDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                         XmlObjMgt_Persistent&             theTarget,
                                         XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_UAttribute> aName = occ::down_cast<TDataStd_UAttribute>(theSource);

  char                aGuidStr[40];
  Standard_PCharacter pGuidStr;
  pGuidStr = aGuidStr;
  aName->ID().ToCString(pGuidStr);

  theTarget.Element().setAttribute(::GuidString(), aGuidStr);
}
