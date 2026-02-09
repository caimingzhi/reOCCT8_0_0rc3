#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_BooleanArray.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_BooleanArrayDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_BooleanArrayDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(FirstIndexString, "first")
IMPLEMENT_DOMSTRING(LastIndexString, "last")
IMPLEMENT_DOMSTRING(AttributeIDString, "boolarrattguid")

XmlMDataStd_BooleanArrayDriver::XmlMDataStd_BooleanArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_BooleanArrayDriver::NewEmpty() const
{
  return new TDataStd_BooleanArray();
}

bool XmlMDataStd_BooleanArrayDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                           const occ::handle<TDF_Attribute>& theTarget,
                                           XmlObjMgt_RRelocationTable&) const
{
  int                      aFirstInd, aLastInd, aValue;
  const XmlObjMgt_Element& anElement = theSource;

  XmlObjMgt_DOMString aFirstIndex = anElement.getAttribute(::FirstIndexString());
  if (aFirstIndex == nullptr)
    aFirstInd = 1;
  else if (!aFirstIndex.GetInteger(aFirstInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the first index"
                                 " for BooleanArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (!anElement.getAttribute(::LastIndexString()).GetInteger(aLastInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for BooleanArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (aFirstInd > aLastInd)
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("The last index is greater than the first index"
                                 " for BooleanArray attribute \"");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  occ::handle<TDataStd_BooleanArray> aBooleanArray =
    occ::down_cast<TDataStd_BooleanArray>(theTarget);

  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_BooleanArray::GetID();
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));
  aBooleanArray->SetID(aGUID);

  aBooleanArray->Init(aFirstInd, aLastInd);
  int                                       length = aLastInd - aFirstInd + 1;
  occ::handle<NCollection_HArray1<uint8_t>> hArr = new NCollection_HArray1<uint8_t>(0, length >> 3);
  NCollection_Array1<uint8_t>&              arr  = hArr->ChangeArray1();
  int                                       i = 0, upper = arr.Upper();
  const char*                               aValueStr =
    static_cast<const char*>(XmlObjMgt::GetStringValue(anElement).GetString());

  for (; i <= upper; i++)
  {
    if (!XmlObjMgt::GetInteger(aValueStr, aValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve integer member"
                                   " for BooleanArray attribute as \"")
        + aValueStr + "\"";
      myMessageDriver->Send(aMessageString, Message_Warning);
      aValue = 0;
    }
    arr.SetValue(i, (uint8_t)aValue);
  }
  aBooleanArray->SetInternalArray(hArr);

  return true;
}

void XmlMDataStd_BooleanArrayDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                           XmlObjMgt_Persistent&             theTarget,
                                           XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_BooleanArray> aBooleanArray =
    occ::down_cast<TDataStd_BooleanArray>(theSource);

  int aL  = aBooleanArray->Lower();
  int anU = aBooleanArray->Upper();

  theTarget.Element().setAttribute(::FirstIndexString(), aL);
  theTarget.Element().setAttribute(::LastIndexString(), anU);

  const occ::handle<NCollection_HArray1<uint8_t>>& hArr = aBooleanArray->InternalArray();
  const NCollection_Array1<uint8_t>&               arr  = hArr->Array1();

  int                          iChar = 0;
  NCollection_LocalArray<char> str;
  if (!arr.IsEmpty())
  {
    str.Allocate(4 * arr.Length() + 1);
  }

  const int upper = arr.Upper();
  for (int i = arr.Lower(); i <= upper; i++)
  {
    const uint8_t& byte = arr.Value(i);
    iChar += Sprintf(&(str[iChar]), "%d ", byte);
  }

  if (!arr.IsEmpty())
  {
    XmlObjMgt::SetStringValue(theTarget, (char*)str, true);
  }

  if (aBooleanArray->ID() != TDataStd_BooleanArray::GetID())
  {

    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    aBooleanArray->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
