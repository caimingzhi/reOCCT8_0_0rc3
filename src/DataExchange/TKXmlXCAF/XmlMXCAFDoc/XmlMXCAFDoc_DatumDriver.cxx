#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <XCAFDoc_Datum.hpp>
#include <XmlMXCAFDoc_DatumDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_DatumDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(DescrIndexString, "descr")
IMPLEMENT_DOMSTRING(IdIndexString, "ident")

//=================================================================================================

XmlMXCAFDoc_DatumDriver::XmlMXCAFDoc_DatumDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, "xcaf", "Datum")
{
}

//=================================================================================================

occ::handle<TDF_Attribute> XmlMXCAFDoc_DatumDriver::NewEmpty() const
{
  return (new XCAFDoc_Datum());
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================
bool XmlMXCAFDoc_DatumDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                    const occ::handle<TDF_Attribute>& theTarget,
                                    XmlObjMgt_RRelocationTable&) const
{
  XmlObjMgt_DOMString aNameStr = XmlObjMgt::GetStringValue(theSource);

  if (aNameStr == nullptr)
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve Datum attribute");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  const XmlObjMgt_Element& anElement = theSource;

  XmlObjMgt_DOMString aDescrStr = anElement.getAttribute(::DescrIndexString());
  XmlObjMgt_DOMString anIdStr   = anElement.getAttribute(::IdIndexString());
  if (aDescrStr == nullptr || anIdStr == nullptr)
  {
    TCollection_ExtendedString aMessageString(
      "Cannot retrieve Datum attribute description or identification");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString(aNameStr.GetString());
  occ::handle<TCollection_HAsciiString> aDescr =
    new TCollection_HAsciiString(aDescrStr.GetString());
  occ::handle<TCollection_HAsciiString> anId = new TCollection_HAsciiString(anIdStr.GetString());

  occ::handle<XCAFDoc_Datum> anAtt = occ::down_cast<XCAFDoc_Datum>(theTarget);
  anAtt->Set(aName, aDescr, anId);

  return true;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================
void XmlMXCAFDoc_DatumDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                    XmlObjMgt_Persistent&             theTarget,
                                    XmlObjMgt_SRelocationTable&) const
{
  occ::handle<XCAFDoc_Datum> anAtt = occ::down_cast<XCAFDoc_Datum>(theSource);

  XmlObjMgt_DOMString aNameString, aDescrString, anIdString;
  if (!anAtt->GetName().IsNull())
    aNameString = anAtt->GetName()->String().ToCString();
  if (!anAtt->GetDescription().IsNull())
    aDescrString = anAtt->GetDescription()->String().ToCString();
  if (!anAtt->GetIdentification().IsNull())
    anIdString = anAtt->GetIdentification()->String().ToCString();

  XmlObjMgt::SetStringValue(theTarget, aNameString);
  theTarget.Element().setAttribute(::DescrIndexString(), aDescrString);
  theTarget.Element().setAttribute(::IdIndexString(), anIdString);
}
