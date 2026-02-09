#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_ByteArray.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <XmlMDataStd.hpp>
#include <XmlMDataStd_ByteArrayDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_DOMSTRING(AttributeIDString, "bytearrattguid")

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_ByteArrayDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(FirstIndexString, "first")
IMPLEMENT_DOMSTRING(LastIndexString, "last")
IMPLEMENT_DOMSTRING(IsDeltaOn, "delta")

XmlMDataStd_ByteArrayDriver::XmlMDataStd_ByteArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_ByteArrayDriver::NewEmpty() const
{
  return new TDataStd_ByteArray();
}

bool XmlMDataStd_ByteArrayDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        XmlObjMgt_RRelocationTable&       theRelocTable) const
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
                                 " for ByteArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (!anElement.getAttribute(::LastIndexString()).GetInteger(aLastInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for ByteArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (aFirstInd > aLastInd)
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("The last index is greater than the first index"
                                 " for ByteArray attribute \"");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  occ::handle<TDataStd_ByteArray> aByteArray = occ::down_cast<TDataStd_ByteArray>(theTarget);

  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_ByteArray::GetID();
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));

  aByteArray->SetID(aGUID);

  occ::handle<NCollection_HArray1<uint8_t>> hArr =
    new NCollection_HArray1<uint8_t>(aFirstInd, aLastInd);
  NCollection_Array1<uint8_t>& arr = hArr->ChangeArray1();

  const char* aValueStr =
    static_cast<const char*>(XmlObjMgt::GetStringValue(anElement).GetString());
  int i = arr.Lower(), upper = arr.Upper();
  for (; i <= upper; i++)
  {
    if (!XmlObjMgt::GetInteger(aValueStr, aValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve integer member"
                                   " for ByteArray attribute as \"")
        + aValueStr + "\"";
      myMessageDriver->Send(aMessageString, Message_Warning);
      aValue = 0;
    }
    arr.SetValue(i, (uint8_t)aValue);
  }
  aByteArray->ChangeArray(hArr);

  bool aDelta(false);

  if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_3)
  {
    int aDeltaValue;
    if (!anElement.getAttribute(::IsDeltaOn()).GetInteger(aDeltaValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve the isDelta value"
                                   " for ByteArray attribute as \"")
        + aDeltaValue + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
    else
      aDelta = aDeltaValue != 0;
  }
#ifdef OCCT_DEBUG
  std::cout << "Current Document Format Version = "
            << theRelocTable.GetHeaderData()->StorageVersion().IntegerValue() << std::endl;
#endif
  aByteArray->SetDelta(aDelta);

  return true;
}

void XmlMDataStd_ByteArrayDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                        XmlObjMgt_Persistent&             theTarget,
                                        XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_ByteArray> aByteArray = occ::down_cast<TDataStd_ByteArray>(theSource);

  int aL  = aByteArray->Lower();
  int anU = aByteArray->Upper();

  theTarget.Element().setAttribute(::FirstIndexString(), aL);
  theTarget.Element().setAttribute(::LastIndexString(), anU);
  theTarget.Element().setAttribute(::IsDeltaOn(), aByteArray->GetDelta() ? 1 : 0);

  const occ::handle<NCollection_HArray1<uint8_t>>& hArr = aByteArray->InternalArray();
  if (!hArr.IsNull() && hArr->Length())
  {

    const NCollection_Array1<uint8_t>& arr = hArr->Array1();

    NCollection_LocalArray<char> str(4 * arr.Length() + 1);

    int iChar = 0;

    int iByte = arr.Lower();
    for (; iByte <= arr.Upper(); ++iByte)
    {
      const uint8_t& byte = arr.Value(iByte);
      iChar += Sprintf(&(str[iChar]), "%d ", byte);
    }

    XmlObjMgt::SetStringValue(theTarget, (char*)str, true);
  }
  if (aByteArray->ID() != TDataStd_ByteArray::GetID())
  {

    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    aByteArray->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
