#include <TDataStd_IntPackedMap.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TColStd_HPackedMapOfInteger.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <TDataStd_DeltaOnModificationOfIntPackedMap.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_DefaultDeltaOnModification.hpp>
#include <TDF_DeltaOnModification.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_IntPackedMap, TDF_Attribute)

//=================================================================================================

const Standard_GUID& TDataStd_IntPackedMap::GetID()
{
  static Standard_GUID theGUID("7031faff-161e-44df-8239-7c264a81f5a1");
  return theGUID;
}

//=================================================================================================

occ::handle<TDataStd_IntPackedMap> TDataStd_IntPackedMap::Set(const TDF_Label& theLabel,
                                                              const bool       isDelta)
{
  occ::handle<TDataStd_IntPackedMap> anAtt;
  if (!theLabel.FindAttribute(TDataStd_IntPackedMap::GetID(), anAtt))
  {
    anAtt = new TDataStd_IntPackedMap;
    anAtt->Clear();
    anAtt->SetDelta(isDelta);
    theLabel.AddAttribute(anAtt);
  }
  return anAtt;
}

//=================================================================================================

TDataStd_IntPackedMap::TDataStd_IntPackedMap()
    : myIsDelta(false)
{
  myMap = new TColStd_HPackedMapOfInteger();
}

//=================================================================================================

bool TDataStd_IntPackedMap::ChangeMap(const occ::handle<TColStd_HPackedMapOfInteger>& theMap)
{
  if (theMap.IsNull())
    return false;
  if (myMap != theMap)
  {
    if (!myMap->Map().IsEqual(theMap->Map()))
    {
      Backup();
      myMap->ChangeMap().Assign(theMap->Map());
      return true;
    }
  }
  return false;
}

//=================================================================================================

bool TDataStd_IntPackedMap::ChangeMap(const TColStd_PackedMapOfInteger& theMap)
{
  if (!myMap->Map().IsEqual(theMap))
  {
    Backup();
    myMap->ChangeMap().Assign(theMap);
    return true;
  }
  return false;
}

//=================================================================================================

bool TDataStd_IntPackedMap::Clear()
{
  if (!myMap->Map().IsEmpty())
  {
    Backup();
    myMap = new TColStd_HPackedMapOfInteger;
    return true;
  }
  return false;
}

//=================================================================================================

bool TDataStd_IntPackedMap::Contains(const int theKey) const
{
  return myMap->Map().Contains(theKey);
}

//=================================================================================================

bool TDataStd_IntPackedMap::Add(const int theKey)
{
  bool aResult = !myMap->Map().Contains(theKey);
  if (aResult)
  {
    Backup();
    aResult = myMap->ChangeMap().Add(theKey);
  }
  return aResult;
}

//=================================================================================================

bool TDataStd_IntPackedMap::Remove(const int theKey)
{
  bool aResult = myMap->Map().Contains(theKey);
  if (aResult)
  {
    Backup();
    aResult = myMap->ChangeMap().Remove(theKey);
  }
  return aResult;
}

//=================================================================================================

occ::handle<TDF_Attribute> TDataStd_IntPackedMap::NewEmpty() const
{
  return new TDataStd_IntPackedMap;
}

//=================================================================================================

void TDataStd_IntPackedMap::Restore(const occ::handle<TDF_Attribute>& theWith)
{
  occ::handle<TDataStd_IntPackedMap> aWith = occ::down_cast<TDataStd_IntPackedMap>(theWith);
  if (aWith->myMap.IsNull())
    myMap.Nullify();
  else
  {
    myMap = new TColStd_HPackedMapOfInteger;
    myMap->ChangeMap().Assign(aWith->myMap->Map());
    myIsDelta = aWith->myIsDelta;
  }
}

//=================================================================================================

void TDataStd_IntPackedMap::Paste(const occ::handle<TDF_Attribute>& theInto,
                                  const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TDataStd_IntPackedMap> anInto = occ::down_cast<TDataStd_IntPackedMap>(theInto);
  if (!anInto.IsNull())
  {
    anInto->ChangeMap(myMap);
    anInto->SetDelta(myIsDelta);
  }
}

//=================================================================================================

const Standard_GUID& TDataStd_IntPackedMap::ID() const
{
  return GetID();
}

//=================================================================================================

Standard_OStream& TDataStd_IntPackedMap::Dump(Standard_OStream& theOS) const
{
  Standard_OStream& anOS = TDF_Attribute::Dump(theOS);
  anOS << "IntPackedMap size = " << Extent();
  anOS << " Delta is " << (myIsDelta ? "ON" : "OFF");
  anOS << std::endl;
  return anOS;
}

//=================================================================================================

occ::handle<TDF_DeltaOnModification> TDataStd_IntPackedMap::DeltaOnModification(
  const occ::handle<TDF_Attribute>& OldAttribute) const
{
  if (myIsDelta)
    return new TDataStd_DeltaOnModificationOfIntPackedMap(
      occ::down_cast<TDataStd_IntPackedMap>(OldAttribute));
  else
    return new TDF_DefaultDeltaOnModification(OldAttribute);
}

//=================================================================================================

void TDataStd_IntPackedMap::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  for (TColStd_PackedMapOfInteger::Iterator aMapIt(myMap->Map()); aMapIt.More(); aMapIt.Next())
  {
    int aKey = aMapIt.Key();
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, aKey)
  }

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsDelta)
}
