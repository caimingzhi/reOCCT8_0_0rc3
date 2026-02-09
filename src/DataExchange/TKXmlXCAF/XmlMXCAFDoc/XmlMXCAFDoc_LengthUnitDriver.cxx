

#include <XmlMXCAFDoc_LengthUnitDriver.hpp>

#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_LengthUnit.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_LengthUnitDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(UnitScaleValue, "value")

XmlMXCAFDoc_LengthUnitDriver::XmlMXCAFDoc_LengthUnitDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, "xcaf", "LengthUnit")
{
}

occ::handle<TDF_Attribute> XmlMXCAFDoc_LengthUnitDriver::NewEmpty() const
{
  return (new XCAFDoc_LengthUnit());
}

bool XmlMXCAFDoc_LengthUnitDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         XmlObjMgt_RRelocationTable&) const
{
  XmlObjMgt_DOMString aNameStr = XmlObjMgt::GetStringValue(theSource);

  if (aNameStr == nullptr)
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve LengthUnit attribute");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }
  const XmlObjMgt_Element& anElement       = theSource;
  XmlObjMgt_DOMString      aUnitScaleValue = anElement.getAttribute(::UnitScaleValue());
  if (aUnitScaleValue == nullptr)
  {
    TCollection_ExtendedString aMessageString("Cannot retrieve LengthUnit scale factor");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }
  TCollection_AsciiString aScaleFactor(aUnitScaleValue.GetString());
  TCollection_AsciiString anUnitName(aNameStr.GetString());
  if (!aScaleFactor.IsRealValue(true))
  {
    TCollection_ExtendedString aMessageString("Cannot retrieve LengthUnit scale factor");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  occ::handle<XCAFDoc_LengthUnit> anInt = occ::down_cast<XCAFDoc_LengthUnit>(theTarget);
  anInt->Set(anUnitName, aScaleFactor.RealValue());
  return true;
}

void XmlMXCAFDoc_LengthUnitDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                         XmlObjMgt_Persistent&             theTarget,
                                         XmlObjMgt_SRelocationTable&) const
{
  occ::handle<XCAFDoc_LengthUnit> anAtt     = occ::down_cast<XCAFDoc_LengthUnit>(theSource);
  XmlObjMgt_DOMString             aNameUnit = anAtt->GetUnitName().ToCString();
  XmlObjMgt_DOMString aValueUnit = TCollection_AsciiString(anAtt->GetUnitValue()).ToCString();
  XmlObjMgt::SetStringValue(theTarget, aNameUnit);
  theTarget.Element().setAttribute(::UnitScaleValue(), aValueUnit);
}
