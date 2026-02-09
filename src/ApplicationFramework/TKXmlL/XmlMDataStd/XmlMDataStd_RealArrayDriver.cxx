#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_RealArray.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <XmlMDataStd.hpp>
#include <XmlMDataStd_RealArrayDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_RealArrayDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(FirstIndexString, "first")
IMPLEMENT_DOMSTRING(LastIndexString, "last")
IMPLEMENT_DOMSTRING(IsDeltaOn, "delta")
IMPLEMENT_DOMSTRING(AttributeIDString, "realarrattguid")

XmlMDataStd_RealArrayDriver::XmlMDataStd_RealArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_RealArrayDriver::NewEmpty() const
{
  return (new TDataStd_RealArray());
}

bool XmlMDataStd_RealArrayDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        XmlObjMgt_RRelocationTable&       theRelocTable) const
{

  occ::handle<TDataStd_RealArray> aRealArray = occ::down_cast<TDataStd_RealArray>(theTarget);
  const XmlObjMgt_Element&        anElement  = theSource;

  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_RealArray::GetID();
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));
  aRealArray->SetID(aGUID);

  int aFirstInd, aLastInd, ind;

  XmlObjMgt_DOMString aFirstIndex = anElement.getAttribute(::FirstIndexString());
  if (aFirstIndex == nullptr)
    aFirstInd = 1;
  else if (!aFirstIndex.GetInteger(aFirstInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the first index"
                                 " for RealArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (!anElement.getAttribute(::LastIndexString()).GetInteger(aLastInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for RealArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  aRealArray->Init(aFirstInd, aLastInd);

  const XmlObjMgt_DOMString& aString = XmlObjMgt::GetStringValue(anElement);
  if (aString.Type() == LDOMBasicString::LDOM_Integer)
  {
    if (aFirstInd == aLastInd)
    {
      int anIntValue;
      if (aString.GetInteger(anIntValue))
        aRealArray->SetValue(aFirstInd, double(anIntValue));
    }
    else
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve array of real members"
                                   " for RealArray attribute from Integer \"")
        + aString + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
  }
  else
  {
    double      aValue;
    const char* aValueStr = static_cast<const char*>(aString.GetString());
    for (ind = aFirstInd; ind <= aLastInd; ind++)
    {
      if (!XmlObjMgt::GetReal(aValueStr, aValue))
      {
        TCollection_ExtendedString aMessageString =
          TCollection_ExtendedString("Cannot retrieve real member"
                                     " for RealArray attribute as \"")
          + aValueStr + "\"";
        myMessageDriver->Send(aMessageString, Message_Warning);

        while (*aValueStr != 0 && IsSpace(*aValueStr))
          ++aValueStr;

        while (*aValueStr != 0 && !IsSpace(*aValueStr))
          ++aValueStr;
      }
      aRealArray->SetValue(ind, aValue);
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
                                   " for RealArray attribute as \"")
        + aDeltaValue + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
    else
      aDelta = aDeltaValue != 0;
  }
  aRealArray->SetDelta(aDelta);

  return true;
}

void XmlMDataStd_RealArrayDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                        XmlObjMgt_Persistent&             theTarget,
                                        XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_RealArray> aRealArray = occ::down_cast<TDataStd_RealArray>(theSource);
  const occ::handle<NCollection_HArray1<double>>& hRealArray = aRealArray->Array();
  const NCollection_Array1<double>&               realArray  = hRealArray->Array1();
  int                                             aL = realArray.Lower(), anU = realArray.Upper();

  if (aL != 1)
    theTarget.Element().setAttribute(::FirstIndexString(), aL);
  theTarget.Element().setAttribute(::LastIndexString(), anU);
  theTarget.Element().setAttribute(::IsDeltaOn(), aRealArray->GetDelta() ? 1 : 0);

  int                          iChar = 0;
  NCollection_LocalArray<char> str;
  if (realArray.Length())
  {
    try
    {
      OCC_CATCH_SIGNALS
      str.Allocate(25 * realArray.Length() + 1);
    }
    catch (Standard_OutOfMemory const&)
    {

      char buf[25];
      int  i(aL), nbChars(0);
      while (i <= anU)
      {
        nbChars += Sprintf(buf, "%.17g ", realArray.Value(i++)) + 1;
      }
      if (nbChars)
        str.Allocate(nbChars);
    }
  }

  int i = aL;
  for (;;)
  {
    iChar += Sprintf(&(str[iChar]), "%.17g ", realArray.Value(i));
    if (i >= anU)
      break;
    ++i;
  }

  if (realArray.Length())
  {
    str[iChar - 1] = '\0';
    XmlObjMgt::SetStringValue(theTarget, (char*)str, true);
  }
  if (aRealArray->ID() != TDataStd_RealArray::GetID())
  {

    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    aRealArray->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
