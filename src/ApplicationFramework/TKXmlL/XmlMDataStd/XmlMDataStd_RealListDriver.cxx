#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_RealList.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_RealListDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_RealListDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(FirstIndexString, "first")
IMPLEMENT_DOMSTRING(LastIndexString, "last")
IMPLEMENT_DOMSTRING(AttributeIDString, "reallistattguid")

XmlMDataStd_RealListDriver::XmlMDataStd_RealListDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_RealListDriver::NewEmpty() const
{
  return new TDataStd_RealList();
}

bool XmlMDataStd_RealListDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       XmlObjMgt_RRelocationTable&) const
{
  const occ::handle<TDataStd_RealList> aRealList = occ::down_cast<TDataStd_RealList>(theTarget);
  const XmlObjMgt_Element&             anElement = theSource;

  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_RealList::GetID();
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));
  aRealList->SetID(aGUID);

  int                 aFirstInd, aLastInd, ind;
  XmlObjMgt_DOMString aFirstIndex = anElement.getAttribute(::FirstIndexString());
  if (aFirstIndex == nullptr)
    aFirstInd = 1;
  else if (!aFirstIndex.GetInteger(aFirstInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the first index"
                                 " for RealList attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (!anElement.getAttribute(::LastIndexString()).GetInteger(aLastInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for RealList attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  const XmlObjMgt_DOMString& aString = XmlObjMgt::GetStringValue(anElement);
  if (aLastInd == 0)
    aFirstInd = 0;
  if (aString.Type() == LDOMBasicString::LDOM_Integer)
  {
    if (aFirstInd == aLastInd && aLastInd > 0)
    {
      int anIntValue;
      if (aString.GetInteger(anIntValue))
        aRealList->Append(double(anIntValue));
    }
    else
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve array of real members"
                                   " for RealList attribute from Integer \"")
        + aString + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
  }
  else if (aLastInd >= 1)
  {
    const char* aValueStr = static_cast<const char*>(aString.GetString());
    for (ind = aFirstInd; ind <= aLastInd; ind++)
    {
      double aValue;
      if (!XmlObjMgt::GetReal(aValueStr, aValue))
      {
        TCollection_ExtendedString aMessageString =
          TCollection_ExtendedString("Cannot retrieve real member"
                                     " for RealList attribute as \"")
          + aValueStr + "\"";
        myMessageDriver->Send(aMessageString, Message_Warning);

        while (*aValueStr != 0 && IsSpace(*aValueStr))
          ++aValueStr;

        while (*aValueStr != 0 && !IsSpace(*aValueStr))
          ++aValueStr;
      }
      aRealList->Append(aValue);
    }
  }

  return true;
}

void XmlMDataStd_RealListDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                       XmlObjMgt_Persistent&             theTarget,
                                       XmlObjMgt_SRelocationTable&) const
{
  const occ::handle<TDataStd_RealList> aRealList = occ::down_cast<TDataStd_RealList>(theSource);

  int anU = aRealList->Extent();
  theTarget.Element().setAttribute(::LastIndexString(), anU);

  NCollection_LocalArray<char> str(25 * anU + 1);
  if (anU == 0)
    str[0] = 0;
  else if (anU >= 1)
  {
    int                                iChar = 0;
    NCollection_List<double>::Iterator itr(aRealList->List());
    for (; itr.More(); itr.Next())
    {
      const double& realValue = itr.Value();
      iChar += Sprintf(&(str[iChar]), "%.17g ", realValue);
    }
  }
  XmlObjMgt::SetStringValue(theTarget, (char*)str, true);

  if (aRealList->ID() != TDataStd_RealList::GetID())
  {

    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    aRealList->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
