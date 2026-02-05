#include <TObj_TNameContainer.hpp>
#include <Standard_GUID.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_TNameContainer, TDF_Attribute)

//=================================================================================================

TObj_TNameContainer::TObj_TNameContainer() = default;

//=================================================================================================

const Standard_GUID& TObj_TNameContainer::GetID()
{
  static Standard_GUID theID("3bbefb47-e618-11d4-ba38-0060b0ee18ea");
  return theID;
}

//=================================================================================================

const Standard_GUID& TObj_TNameContainer::ID() const
{
  return GetID();
}

//=================================================================================================

occ::handle<TObj_TNameContainer> TObj_TNameContainer::Set(const TDF_Label& theLabel)
{
  occ::handle<TObj_TNameContainer> A;
  if (!theLabel.FindAttribute(TObj_TNameContainer::GetID(), A))
  {
    A = new TObj_TNameContainer;
    theLabel.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

void TObj_TNameContainer::RecordName(const occ::handle<TCollection_HExtendedString>& theName,
                                     const TDF_Label&                                theLabel)
{
  if (!IsRegistered(theName))
  {
    Backup();
    myMap.Bind(new TCollection_HExtendedString(theName->String()), theLabel);
  }
}

//=================================================================================================

void TObj_TNameContainer::RemoveName(const occ::handle<TCollection_HExtendedString>& theName)
{
  if (IsRegistered(theName))
  {
    Backup();
    myMap.UnBind(theName);
  }
}

void TObj_TNameContainer::Clear()
{
  Backup();
  myMap.Clear();
}

//=================================================================================================

bool TObj_TNameContainer::IsRegistered(
  const occ::handle<TCollection_HExtendedString>& theName) const
{
  return myMap.IsBound(theName);
}

//=================================================================================================

occ::handle<TDF_Attribute> TObj_TNameContainer::NewEmpty() const
{
  return new TObj_TNameContainer();
}

//=================================================================================================

void TObj_TNameContainer::Restore(const occ::handle<TDF_Attribute>& theWith)
{
  occ::handle<TObj_TNameContainer> R = occ::down_cast<TObj_TNameContainer>(theWith);

  myMap = R->Get();
}

//=================================================================================================

void TObj_TNameContainer::Paste(const occ::handle<TDF_Attribute>& theInto,
                                const occ::handle<TDF_RelocationTable>& /* RT */) const
{
  occ::handle<TObj_TNameContainer> R = occ::down_cast<TObj_TNameContainer>(theInto);
  R->Set(myMap);
}

//=================================================================================================

const NCollection_DataMap<occ::handle<TCollection_HExtendedString>, TDF_Label>&
  TObj_TNameContainer::Get() const
{
  return myMap;
}

//=================================================================================================

void TObj_TNameContainer::Set(
  const NCollection_DataMap<occ::handle<TCollection_HExtendedString>, TDF_Label>& theMap)
{
  Backup();
  myMap.Assign(theMap);
}
