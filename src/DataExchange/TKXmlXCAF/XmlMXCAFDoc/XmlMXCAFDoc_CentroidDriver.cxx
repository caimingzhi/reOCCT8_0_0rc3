#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_Centroid.hpp>
#include <XmlMXCAFDoc_CentroidDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_CentroidDriver, XmlMDF_ADriver)

XmlMXCAFDoc_CentroidDriver::XmlMXCAFDoc_CentroidDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, "xcaf", "Centroid")
{
}

occ::handle<TDF_Attribute> XmlMXCAFDoc_CentroidDriver::NewEmpty() const
{
  return (new XCAFDoc_Centroid());
}

bool XmlMXCAFDoc_CentroidDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       XmlObjMgt_RRelocationTable&) const
{
  occ::handle<XCAFDoc_Centroid> aTPos = occ::down_cast<XCAFDoc_Centroid>(theTarget);

  XmlObjMgt_DOMString aPosStr = XmlObjMgt::GetStringValue(theSource.Element());
  if (aPosStr == nullptr)
  {
    myMessageDriver->Send("Cannot retrieve position string from element", Message_Fail);
    return false;
  }

  gp_Pnt      aPos;
  double      aValue;
  const char* aValueStr = static_cast<const char*>(aPosStr.GetString());

  if (!XmlObjMgt::GetReal(aValueStr, aValue))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString(
        "Cannot retrieve X coordinate for XCAFDoc_Centroid attribute as \"")
      + aValueStr + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }
  aPos.SetX(aValue);

  if (!XmlObjMgt::GetReal(aValueStr, aValue))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString(
        "Cannot retrieve Y coordinate for XCAFDoc_Centroid attribute as \"")
      + aValueStr + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }
  aPos.SetY(aValue);

  if (!XmlObjMgt::GetReal(aValueStr, aValue))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString(
        "Cannot retrieve Z coordinate for XCAFDoc_Centroid attribute as \"")
      + aValueStr + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }
  aPos.SetZ(aValue);

  aTPos->Set(aPos);

  return true;
}

void XmlMXCAFDoc_CentroidDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                       XmlObjMgt_Persistent&             theTarget,
                                       XmlObjMgt_SRelocationTable&) const
{
  occ::handle<XCAFDoc_Centroid> aTPos = occ::down_cast<XCAFDoc_Centroid>(theSource);
  if (!aTPos.IsNull())
  {
    gp_Pnt aPos = aTPos->Get();
    char   buf[75];
    Sprintf(buf, "%.17g %.17g %.17g", aPos.X(), aPos.Y(), aPos.Z());
    XmlObjMgt::SetStringValue(theTarget.Element(), buf);
  }
}
