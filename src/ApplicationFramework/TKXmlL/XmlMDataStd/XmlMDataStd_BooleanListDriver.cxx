#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_BooleanList.hpp>
#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataStd_BooleanListDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_BooleanListDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(FirstIndexString, "first")
IMPLEMENT_DOMSTRING(LastIndexString, "last")
IMPLEMENT_DOMSTRING(AttributeIDString, "boollistattguid")

//=================================================================================================

XmlMDataStd_BooleanListDriver::XmlMDataStd_BooleanListDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

//=================================================================================================

occ::handle<TDF_Attribute> XmlMDataStd_BooleanListDriver::NewEmpty() const
{
  return new TDataStd_BooleanList();
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================
bool XmlMDataStd_BooleanListDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                          const occ::handle<TDF_Attribute>& theTarget,
                                          XmlObjMgt_RRelocationTable&) const
{
  int                      aFirstInd, aLastInd, aValue, ind;
  const XmlObjMgt_Element& anElement = theSource;

  // Read the FirstIndex; if the attribute is absent initialize to 1
  XmlObjMgt_DOMString aFirstIndex = anElement.getAttribute(::FirstIndexString());
  if (aFirstIndex == nullptr)
    aFirstInd = 1;
  else if (!aFirstIndex.GetInteger(aFirstInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the first index"
                                 " for BooleanList attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  // Read the LastIndex; the attribute should be present
  if (!anElement.getAttribute(::LastIndexString()).GetInteger(aLastInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for BooleanList attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  const occ::handle<TDataStd_BooleanList> aBooleanList =
    occ::down_cast<TDataStd_BooleanList>(theTarget);

  // attribute id
  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_BooleanList::GetID(); // default case
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString())); // user defined case

  aBooleanList->SetID(aGUID);

  if (aLastInd == 0)
    aFirstInd = 0;
  if (aFirstInd == aLastInd && aLastInd > 0)
  {
    if (!XmlObjMgt::GetStringValue(anElement).GetInteger(aValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve integer member"
                                   " for BooleanList attribute as \"");
      myMessageDriver->Send(aMessageString, Message_Warning);
      aValue = 0;
    }
    aBooleanList->Append(aValue != 0);
  }
  else if (aLastInd >= 1)
  {
    const char* aValueStr =
      static_cast<const char*>(XmlObjMgt::GetStringValue(anElement).GetString());
    for (ind = aFirstInd; ind <= aLastInd; ind++)
    {
      if (!XmlObjMgt::GetInteger(aValueStr, aValue))
      {
        TCollection_ExtendedString aMessageString =
          TCollection_ExtendedString("Cannot retrieve integer member"
                                     " for BooleanList attribute as \"")
          + aValueStr + "\"";
        myMessageDriver->Send(aMessageString, Message_Warning);
        aValue = 0;
      }
      aBooleanList->Append(aValue != 0);
    }
  }

  return true;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================
void XmlMDataStd_BooleanListDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                          XmlObjMgt_Persistent&             theTarget,
                                          XmlObjMgt_SRelocationTable&) const
{
  const occ::handle<TDataStd_BooleanList> aBooleanList =
    occ::down_cast<TDataStd_BooleanList>(theSource);

  int anU = aBooleanList->Extent();
  theTarget.Element().setAttribute(::LastIndexString(), anU);
  // Allocation of 1 char for each boolean value + a space.
  NCollection_LocalArray<char> str(2 * anU + 1);
  if (anU == 0)
    str[0] = 0;
  else if (anU >= 1)
  {
    int                                 iChar(0);
    NCollection_List<uint8_t>::Iterator itr(aBooleanList->List());
    for (; itr.More(); itr.Next())
    {
      const uint8_t& byte = itr.Value();
      iChar += Sprintf(&(str[iChar]), "%d ", byte);
    }
  }
  XmlObjMgt::SetStringValue(theTarget, (char*)str, true);

  if (aBooleanList->ID() != TDataStd_BooleanList::GetID())
  {
    // convert GUID
    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    aBooleanList->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
