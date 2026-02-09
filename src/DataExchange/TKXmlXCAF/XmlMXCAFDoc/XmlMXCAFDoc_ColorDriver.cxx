#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_Color.hpp>
#include <XmlMXCAFDoc_ColorDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_ColorDriver, XmlMDF_ADriver)

XmlMXCAFDoc_ColorDriver::XmlMXCAFDoc_ColorDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, "xcaf", "Color")
{
}

occ::handle<TDF_Attribute> XmlMXCAFDoc_ColorDriver::NewEmpty() const
{
  return (new XCAFDoc_Color());
}

bool XmlMXCAFDoc_ColorDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                    const occ::handle<TDF_Attribute>& theTarget,
                                    XmlObjMgt_RRelocationTable&) const
{
  int                 aValue;
  XmlObjMgt_DOMString anIntStr = XmlObjMgt::GetStringValue(theSource);

  if (!anIntStr.GetInteger(aValue))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve Color attribute from \"") + anIntStr + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  occ::handle<XCAFDoc_Color> anInt = occ::down_cast<XCAFDoc_Color>(theTarget);
  anInt->Set((Quantity_NameOfColor)aValue);

  return true;
}

void XmlMXCAFDoc_ColorDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                    XmlObjMgt_Persistent&             theTarget,
                                    XmlObjMgt_SRelocationTable&) const
{
  occ::handle<XCAFDoc_Color> anInt = occ::down_cast<XCAFDoc_Color>(theSource);
  XmlObjMgt::SetStringValue(theTarget, (int)anInt->GetNOC());
}
