#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <TDataStd_IntPackedMap.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <XmlMDataStd.hpp>
#include <XmlMDataStd_IntPackedMapDriver.hpp>
#include <XmlMDF_ADriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_IntPackedMapDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(IntPackedMapSize, "mapsize")
IMPLEMENT_DOMSTRING(IsDeltaOn, "delta")

//=================================================================================================

XmlMDataStd_IntPackedMapDriver::XmlMDataStd_IntPackedMapDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_IntPackedMap)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> XmlMDataStd_IntPackedMapDriver::NewEmpty() const
{
  return (new TDataStd_IntPackedMap());
}

//=======================================================================
// function : Paste()
// purpose  : persistent -> transient (retrieve)
//=======================================================================
bool XmlMDataStd_IntPackedMapDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                           const occ::handle<TDF_Attribute>& theTarget,
                                           XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  occ::handle<TDataStd_IntPackedMap> aPackedMap = occ::down_cast<TDataStd_IntPackedMap>(theTarget);
  if (!aPackedMap.IsNull())
  {
    int                      aSize;
    const XmlObjMgt_Element& anElement = theSource;
    XmlObjMgt_DOMString      aSizeDStr = anElement.getAttribute(::IntPackedMapSize());
    if (aSizeDStr == nullptr)
      aSize = 0;
    else if (!aSizeDStr.GetInteger(aSize))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve the Map size"
                                   " for IntPackedMap attribute as \"")
        + aSize + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
    occ::handle<TColStd_HPackedMapOfInteger> aHMap = new TColStd_HPackedMapOfInteger();
    bool                                     Ok    = true;
    if (aSize)
    {
      const char* aValueString =
        static_cast<const char*>(XmlObjMgt::GetStringValue(anElement).GetString());
      //      occ::handle<TColStd_HPackedMapOfInteger> aHMap = new TColStd_HPackedMapOfInteger ();
      for (int i = 1; i <= aSize; i++)
      {
        int aValue;
        if (!XmlObjMgt::GetInteger(aValueString, aValue))
        {
          Ok = false;
          break;
        }
        if (!aHMap->ChangeMap().Add(aValue))
        {
          Ok = false;
          break;
        }
      }
      if (!Ok)
      {
        TCollection_ExtendedString aMessageString =
          TCollection_ExtendedString("Cannot retrieve integer member"
                                     " for IntPackedMap attribute as \"")
          + aValueString + "\"";
        myMessageDriver->Send(aMessageString, Message_Fail);
        return false;
      }
      if (aPackedMap->ChangeMap(aHMap))
        Ok = true;
    }
    if (Ok)
    {
      bool aDelta(false);

      if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
          >= TDocStd_FormatVersion_VERSION_3)
      {
        int aDeltaValue;
        if (!anElement.getAttribute(::IsDeltaOn()).GetInteger(aDeltaValue))
        {
          TCollection_ExtendedString aMessageString =
            TCollection_ExtendedString("Cannot retrieve the isDelta value"
                                       " for IntPackedMap attribute as \"")
            + aDeltaValue + "\"";
          myMessageDriver->Send(aMessageString, Message_Fail);
          return false;
        }
        else
          aDelta = aDeltaValue != 0;
      }
      aPackedMap->SetDelta(aDelta);
      return true;
    }
  }
  myMessageDriver->Send("error retrieving Map for type TDataStd_IntPackedMap", Message_Fail);
  return false;
}

//=======================================================================
// function : Paste()
// purpose  : transient -> persistent (store)
//=======================================================================
void XmlMDataStd_IntPackedMapDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                           XmlObjMgt_Persistent&             theTarget,
                                           XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataStd_IntPackedMap> aS = occ::down_cast<TDataStd_IntPackedMap>(theSource);
  if (aS.IsNull())
  {
    myMessageDriver->Send("IntPackedMapDriver:: The source attribute is Null.", Message_Warning);
    return;
  }

  int aSize = (aS->IsEmpty()) ? 0 : aS->Extent();
  theTarget.Element().setAttribute(::IntPackedMapSize(), aSize);
  theTarget.Element().setAttribute(::IsDeltaOn(), aS->GetDelta() ? 1 : 0);

  if (aSize)
  {
    // Allocation of 12 chars for each integer including the space.
    // An example: -2 147 483 648
    int                          iChar = 0;
    NCollection_LocalArray<char> str(12 * aSize + 1);

    TColStd_MapIteratorOfPackedMapOfInteger anIt(aS->GetMap());
    for (; anIt.More(); anIt.Next())
    {
      const int intValue = anIt.Key();
      iChar += Sprintf(&(str[iChar]), "%d ", intValue);
    }

    // No occurrence of '&', '<' and other irregular XML characters
    XmlObjMgt::SetStringValue(theTarget, (char*)str, true);
  }
}
