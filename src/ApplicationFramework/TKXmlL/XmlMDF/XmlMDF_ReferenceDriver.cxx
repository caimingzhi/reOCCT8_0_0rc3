#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Reference.hpp>
#include <TDF_Tool.hpp>
#include <XmlMDF_ReferenceDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDF_ReferenceDriver, XmlMDF_ADriver)

XmlMDF_ReferenceDriver::XmlMDF_ReferenceDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDF_ReferenceDriver::NewEmpty() const
{
  return (new TDF_Reference());
}

bool XmlMDF_ReferenceDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   XmlObjMgt_RRelocationTable&) const
{
  XmlObjMgt_DOMString anXPath = XmlObjMgt::GetStringValue(theSource);

  if (anXPath == nullptr)
  {
    myMessageDriver->Send("Cannot retrieve reference string from element", Message_Fail);
    return false;
  }

  TCollection_AsciiString anEntry;
  if (!XmlObjMgt::GetTagEntryString(anXPath, anEntry))
  {
    TCollection_ExtendedString aMessage =
      TCollection_ExtendedString("Cannot retrieve reference from \"") + anXPath + '\"';
    myMessageDriver->Send(aMessage, Message_Fail);
    return false;
  }

  occ::handle<TDF_Reference> aRef = occ::down_cast<TDF_Reference>(theTarget);

  TDF_Label tLab;
  if (anEntry.Length() > 0)
  {
    TDF_Tool::Label(aRef->Label().Data(), anEntry, tLab, true);
  }

  aRef->Set(tLab);

  return true;
}

void XmlMDF_ReferenceDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   XmlObjMgt_Persistent&             theTarget,
                                   XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDF_Reference> aRef = occ::down_cast<TDF_Reference>(theSource);
  if (!aRef.IsNull())
  {
    const TDF_Label& lab    = aRef->Label();
    const TDF_Label& refLab = aRef->Get();
    if (!lab.IsNull() && !refLab.IsNull())
    {
      if (lab.IsDescendant(refLab.Root()))
      {

        TCollection_AsciiString anEntry;
        TDF_Tool::Entry(refLab, anEntry);

        XmlObjMgt_DOMString aDOMString;
        XmlObjMgt::SetTagEntryString(aDOMString, anEntry);

        XmlObjMgt::SetStringValue(theTarget, aDOMString, true);
      }
    }
  }
}
