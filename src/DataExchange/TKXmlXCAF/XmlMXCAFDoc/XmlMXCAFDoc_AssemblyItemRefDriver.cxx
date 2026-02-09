#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_AssemblyItemRef.hpp>
#include <XmlMXCAFDoc_AssemblyItemRefDriver.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_AssemblyItemRefDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(Path, "path")
IMPLEMENT_DOMSTRING(AttrGUID, "guid")
IMPLEMENT_DOMSTRING(SubshapeIndex, "subshape_index")

XmlMXCAFDoc_AssemblyItemRefDriver::XmlMXCAFDoc_AssemblyItemRefDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_AssemblyItemRef)->Name())
{
}

occ::handle<TDF_Attribute> XmlMXCAFDoc_AssemblyItemRefDriver::NewEmpty() const
{
  return new XCAFDoc_AssemblyItemRef();
}

bool XmlMXCAFDoc_AssemblyItemRefDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                              const occ::handle<TDF_Attribute>& theTarget,
                                              XmlObjMgt_RRelocationTable&) const
{
  const XmlObjMgt_Element& anElement = theSource;

  XmlObjMgt_DOMString aPath = anElement.getAttribute(::Path());
  if (aPath == nullptr)
    return false;

  occ::handle<XCAFDoc_AssemblyItemRef> aThis = occ::down_cast<XCAFDoc_AssemblyItemRef>(theTarget);
  if (aThis.IsNull())
    return false;

  aThis->SetItem(aPath.GetString());

  XmlObjMgt_DOMString anAttrGUID = anElement.getAttribute(::AttrGUID());
  if (anAttrGUID != nullptr)
  {
    Standard_GUID aGUID(anAttrGUID.GetString());
    aThis->SetGUID(aGUID);
    return true;
  }

  XmlObjMgt_DOMString aSubshapeIndex = anElement.getAttribute(::SubshapeIndex());
  if (aSubshapeIndex != nullptr)
  {
    int anIndex;
    if (!aSubshapeIndex.GetInteger(anIndex))
      return false;

    aThis->SetSubshapeIndex(anIndex);
    return true;
  }

  return true;
}

void XmlMXCAFDoc_AssemblyItemRefDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                              XmlObjMgt_Persistent&             theTarget,
                                              XmlObjMgt_SRelocationTable&) const
{
  occ::handle<XCAFDoc_AssemblyItemRef> aThis = occ::down_cast<XCAFDoc_AssemblyItemRef>(theSource);

  XmlObjMgt_DOMString aPath(aThis->GetItem().ToString().ToCString());
  theTarget.Element().setAttribute(::Path(), aPath);

  if (aThis->IsGUID())
  {
    Standard_GUID aGUID = aThis->GetGUID();
    char          aGUIDStr[Standard_GUID_SIZE + 1];
    aGUID.ToCString(aGUIDStr);
    aGUIDStr[Standard_GUID_SIZE] = '\0';
    XmlObjMgt_DOMString anAttrGUID(aGUIDStr);
    theTarget.Element().setAttribute(::AttrGUID(), anAttrGUID);
  }
  else if (aThis->IsSubshapeIndex())
  {
    TCollection_AsciiString aSubshapeIndexStr(aThis->GetSubshapeIndex());
    XmlObjMgt_DOMString     aSubshapeIndex(aSubshapeIndexStr.ToCString());
    theTarget.Element().setAttribute(::SubshapeIndex(), aSubshapeIndex);
  }
}
