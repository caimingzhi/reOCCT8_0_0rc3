#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_TagSource.hpp>
#include <XmlMDF_TagSourceDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDF_TagSourceDriver, XmlMDF_ADriver)

XmlMDF_TagSourceDriver::XmlMDF_TagSourceDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDF_TagSourceDriver::NewEmpty() const
{
  return (new TDF_TagSource());
}

bool XmlMDF_TagSourceDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   XmlObjMgt_RRelocationTable&) const
{
  int                 aTag;
  XmlObjMgt_DOMString aTagStr = XmlObjMgt::GetStringValue(theSource.Element());

  if (!aTagStr.GetInteger(aTag))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve TagSource attribute from \"") + aTagStr + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (aTag < 0)
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Invalid value of TagSource retrieved: ") + aTag;
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  occ::handle<TDF_TagSource> aT = occ::down_cast<TDF_TagSource>(theTarget);
  aT->Set(aTag);

  return true;
}

void XmlMDF_TagSourceDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   XmlObjMgt_Persistent&             theTarget,
                                   XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDF_TagSource> aTag = occ::down_cast<TDF_TagSource>(theSource);

  XmlObjMgt::SetStringValue(theTarget.Element(), aTag->Get(), true);
}
