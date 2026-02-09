#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_IntegerArray.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <XmlMDataStd.hpp>
#include <XmlMDataStd_IntegerArrayDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_IntegerArrayDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(FirstIndexString, "first")
IMPLEMENT_DOMSTRING(LastIndexString, "last")
IMPLEMENT_DOMSTRING(IsDeltaOn, "delta")
IMPLEMENT_DOMSTRING(AttributeIDString, "intarrattguid")

XmlMDataStd_IntegerArrayDriver::XmlMDataStd_IntegerArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_IntegerArrayDriver::NewEmpty() const
{
  return (new TDataStd_IntegerArray());
}

bool XmlMDataStd_IntegerArrayDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                           const occ::handle<TDF_Attribute>& theTarget,
                                           XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  int                      aFirstInd, aLastInd, aValue, ind;
  const XmlObjMgt_Element& anElement = theSource;

  XmlObjMgt_DOMString aFirstIndex = anElement.getAttribute(::FirstIndexString());
  if (aFirstIndex == nullptr)
    aFirstInd = 1;
  else if (!aFirstIndex.GetInteger(aFirstInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the first index"
                                 " for IntegerArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (!anElement.getAttribute(::LastIndexString()).GetInteger(aLastInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for IntegerArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  occ::handle<TDataStd_IntegerArray> anIntArray = occ::down_cast<TDataStd_IntegerArray>(theTarget);
  anIntArray->Init(aFirstInd, aLastInd);

  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_IntegerArray::GetID();
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));
  anIntArray->SetID(aGUID);

  if (aFirstInd == aLastInd)
  {
    if (!XmlObjMgt::GetStringValue(anElement).GetInteger(aValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve integer member"
                                   " for IntegerArray attribute as \"");
      myMessageDriver->Send(aMessageString, Message_Warning);
      aValue = 0;
    }
    anIntArray->SetValue(aFirstInd, aValue);
  }
  else
  {

    const char* aValueStr =
      static_cast<const char*>(XmlObjMgt::GetStringValue(anElement).GetString());

    for (ind = aFirstInd; ind <= aLastInd; ind++)
    {
      if (!XmlObjMgt::GetInteger(aValueStr, aValue))
      {
        TCollection_ExtendedString aMessageString =
          TCollection_ExtendedString("Cannot retrieve integer member"
                                     " for IntegerArray attribute as \"")
          + aValueStr + "\"";
        myMessageDriver->Send(aMessageString, Message_Warning);
        aValue = 0;
      }
      anIntArray->SetValue(ind, aValue);
    }
  }
  bool aDelta(false);

  if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_3)
  {
    int aDeltaValue;
    if (!anElement.getAttribute(::IsDeltaOn()).GetInteger(aDeltaValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve the isDelta value"
                                   " for IntegerArray attribute as \"")
        + aDeltaValue + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
    else
      aDelta = aDeltaValue != 0;
  }

  anIntArray->SetDelta(aDelta);

  return true;
}

void XmlMDataStd_IntegerArrayDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                           XmlObjMgt_Persistent&             theTarget,
                                           XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_IntegerArray> anIntArray = occ::down_cast<TDataStd_IntegerArray>(theSource);
  const occ::handle<NCollection_HArray1<int>>& hIntArray = anIntArray->Array();
  const NCollection_Array1<int>&               intArray  = hIntArray->Array1();
  int                                          aL = intArray.Lower(), anU = intArray.Upper();

  if (aL != 1)
    theTarget.Element().setAttribute(::FirstIndexString(), aL);
  theTarget.Element().setAttribute(::LastIndexString(), anU);
  theTarget.Element().setAttribute(::IsDeltaOn(), anIntArray->GetDelta() ? 1 : 0);

  int                          iChar = 0;
  NCollection_LocalArray<char> str;
  if (intArray.Length())
    str.Allocate(12 * intArray.Length() + 1);

  int i = aL;
  for (;;)
  {
    iChar += Sprintf(&(str[iChar]), "%d ", intArray.Value(i));
    if (i >= anU)
      break;
    ++i;
  }

  if (intArray.Length())
  {

    str[iChar - 1] = '\0';
    XmlObjMgt::SetStringValue(theTarget, (char*)str, true);
  }
  if (anIntArray->ID() != TDataStd_IntegerArray::GetID())
  {

    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    anIntArray->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
