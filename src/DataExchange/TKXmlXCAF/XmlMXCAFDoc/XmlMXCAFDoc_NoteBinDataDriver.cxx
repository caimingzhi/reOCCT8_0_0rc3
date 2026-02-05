#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_NoteBinData.hpp>
#include <XmlObjMgt.hpp>
#include <XmlMXCAFDoc_NoteBinDataDriver.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <LDOM_OSStream.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_NoteBinDataDriver, XmlMXCAFDoc_NoteDriver)
IMPLEMENT_DOMSTRING(Title, "title")
IMPLEMENT_DOMSTRING(MIMEtype, "mime_type")
IMPLEMENT_DOMSTRING(Size, "size")

//=================================================================================================

XmlMXCAFDoc_NoteBinDataDriver::XmlMXCAFDoc_NoteBinDataDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMXCAFDoc_NoteDriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_NoteBinData)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> XmlMXCAFDoc_NoteBinDataDriver::NewEmpty() const
{
  return new XCAFDoc_NoteBinData();
}

//=================================================================================================

bool XmlMXCAFDoc_NoteBinDataDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                          const occ::handle<TDF_Attribute>& theTarget,
                                          XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  XmlMXCAFDoc_NoteDriver::Paste(theSource, theTarget, theRelocTable);

  const XmlObjMgt_Element& anElement = theSource;

  XmlObjMgt_DOMString aTitle    = anElement.getAttribute(::Title());
  XmlObjMgt_DOMString aMIMEtype = anElement.getAttribute(::MIMEtype());
  XmlObjMgt_DOMString aSize     = anElement.getAttribute(::Size());
  if (aTitle == nullptr || aMIMEtype == nullptr || aSize == nullptr)
    return false;

  occ::handle<XCAFDoc_NoteBinData> aNote = occ::down_cast<XCAFDoc_NoteBinData>(theTarget);
  if (aNote.IsNull())
    return false;

  int nbSize = 0;
  if (!aSize.GetInteger(nbSize))
    return false;

  XmlObjMgt_DOMString aDataStr = XmlObjMgt::GetStringValue(theSource);
  Standard_SStream    anSS(aDataStr.GetString());

  occ::handle<NCollection_HArray1<uint8_t>> aData = new NCollection_HArray1<uint8_t>(1, nbSize);
  for (int i = 1; i <= nbSize; ++i)
  {
    uint8_t aValue;
    anSS >> aValue;
    aData->ChangeValue(i) = aValue;
  }

  aNote->Set(aTitle.GetString(), aMIMEtype.GetString(), aData);

  return true;
}

//=================================================================================================

void XmlMXCAFDoc_NoteBinDataDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                          XmlObjMgt_Persistent&             theTarget,
                                          XmlObjMgt_SRelocationTable&       theRelocTable) const
{
  XmlMXCAFDoc_NoteDriver::Paste(theSource, theTarget, theRelocTable);

  occ::handle<XCAFDoc_NoteBinData> aNote = occ::down_cast<XCAFDoc_NoteBinData>(theSource);

  XmlObjMgt_DOMString aTitle(TCollection_AsciiString(aNote->Title()).ToCString());
  XmlObjMgt_DOMString aMIMEtype(aNote->MIMEtype().ToCString());

  theTarget.Element().setAttribute(::Title(), aTitle);
  theTarget.Element().setAttribute(::MIMEtype(), aMIMEtype);
  theTarget.Element().setAttribute(::Size(), aNote->Size());

  if (aNote->Size() > 0)
  {
    const occ::handle<NCollection_HArray1<uint8_t>>& aData = aNote->Data();
    LDOM_OSStream                                    anOSS(aNote->Size());
    for (int i = aData->Lower(); i <= aData->Upper(); ++i)
    {
      anOSS << std::hex << aData->Value(i);
    }
    // clang-format off
    char* dump = (char*)anOSS.str(); // copying! Don't forget to delete it.
    // clang-format on
    XmlObjMgt::SetStringValue(theTarget, dump, true);
    delete[] dump;
  }
}
