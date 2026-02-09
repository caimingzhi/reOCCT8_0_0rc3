#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd_XLink.hpp>
#include <XmlMDocStd_XLinkDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDocStd_XLinkDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(DocEntryString, "documentEntry")

XmlMDocStd_XLinkDriver::XmlMDocStd_XLinkDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDocStd_XLinkDriver::NewEmpty() const
{
  return (new TDocStd_XLink());
}

bool XmlMDocStd_XLinkDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   XmlObjMgt_RRelocationTable&) const
{
  XmlObjMgt_DOMString anXPath = XmlObjMgt::GetStringValue(theSource);

  if (anXPath == nullptr)
  {
    myMessageDriver->Send("XLink: Cannot retrieve reference string from element", Message_Fail);
    return false;
  }

  TCollection_AsciiString anEntry;
  if (!XmlObjMgt::GetTagEntryString(anXPath, anEntry))
  {
    TCollection_ExtendedString aMessage =
      TCollection_ExtendedString("Cannot retrieve XLink reference from \"") + anXPath + '\"';
    myMessageDriver->Send(aMessage, Message_Fail);
    return false;
  }

  occ::handle<TDocStd_XLink> aRef = occ::down_cast<TDocStd_XLink>(theTarget);

  aRef->LabelEntry(anEntry);

  aRef->DocumentEntry(theSource.Element().getAttribute(::DocEntryString()));

  return true;
}

void XmlMDocStd_XLinkDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   XmlObjMgt_Persistent&             theTarget,
                                   XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDocStd_XLink> aRef = occ::down_cast<TDocStd_XLink>(theSource);
  if (!aRef.IsNull())
  {

    TCollection_AsciiString anEntry = aRef->LabelEntry();
    XmlObjMgt_DOMString     aDOMString;
    XmlObjMgt::SetTagEntryString(aDOMString, anEntry);
    XmlObjMgt::SetStringValue(theTarget, aDOMString);

    theTarget.Element().setAttribute(::DocEntryString(), aRef->DocumentEntry().ToCString());
  }
}
