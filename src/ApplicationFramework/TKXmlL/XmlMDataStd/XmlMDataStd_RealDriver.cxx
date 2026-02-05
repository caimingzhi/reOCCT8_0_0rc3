#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_RealDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_RealDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(AttributeIDString, "realattguid")

//=================================================================================================

XmlMDataStd_RealDriver::XmlMDataStd_RealDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

//=================================================================================================

occ::handle<TDF_Attribute> XmlMDataStd_RealDriver::NewEmpty() const
{
  return (new TDataStd_Real());
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================
bool XmlMDataStd_RealDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   XmlObjMgt_RRelocationTable&) const
{
  // attribute id
  Standard_GUID            aGUID;
  const XmlObjMgt_Element& anElement = theSource;
  XmlObjMgt_DOMString      aGUIDStr  = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_Real::GetID(); // default case
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString())); // user defined case

  occ::down_cast<TDataStd_Real>(theTarget)->SetID(aGUID);

  double                     aValue(0.);
  const XmlObjMgt_DOMString& aRealStr  = XmlObjMgt::GetStringValue(theSource);
  const char*                aValueStr = static_cast<const char*>(aRealStr.GetString());
  if (!XmlObjMgt::GetReal(aRealStr, aValue))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve Real attribute from \"") + aValueStr + "\"";
    myMessageDriver->Send(aMessageString, Message_Warning);
  }
  occ::handle<TDataStd_Real> anAtt = occ::down_cast<TDataStd_Real>(theTarget);
  anAtt->Set(aValue);

  return true;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================
void XmlMDataStd_RealDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   XmlObjMgt_Persistent&             theTarget,
                                   XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_Real> anAtt = occ::down_cast<TDataStd_Real>(theSource);
  char                       aValueChar[32];
  Sprintf(aValueChar, "%.17g", anAtt->Get());
  TCollection_AsciiString aValueStr(aValueChar);
  // No occurrence of '&', '<' and other irregular XML characters
  XmlObjMgt::SetStringValue(theTarget, aValueStr.ToCString(), true);
  if (anAtt->ID() != TDataStd_Real::GetID())
  {
    // convert GUID
    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    anAtt->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
