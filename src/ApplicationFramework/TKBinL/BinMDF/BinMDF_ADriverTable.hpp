#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BinMDF_ADriver.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DoubleMap.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
class BinMDF_ADriver;

class BinMDF_ADriverTable : public Standard_Transient
{

public:
  Standard_EXPORT BinMDF_ADriverTable();

  Standard_EXPORT void AddDriver(const occ::handle<BinMDF_ADriver>& theDriver);

  Standard_EXPORT void AddDerivedDriver(const occ::handle<TDF_Attribute>& theInstance);

  Standard_EXPORT const occ::handle<Standard_Type>& AddDerivedDriver(const char* theDerivedType);

  Standard_EXPORT void AssignIds(
    const NCollection_IndexedMap<occ::handle<Standard_Transient>>& theTypes);

  Standard_EXPORT void AssignIds(const NCollection_Sequence<TCollection_AsciiString>& theTypeNames);

  int GetDriver(const occ::handle<Standard_Type>& theType, occ::handle<BinMDF_ADriver>& theDriver);

  occ::handle<BinMDF_ADriver> GetDriver(const int theTypeId);

  DEFINE_STANDARD_RTTIEXT(BinMDF_ADriverTable, Standard_Transient)

private:
  void AssignId(const occ::handle<Standard_Type>& theType, const int theId);

  NCollection_DataMap<occ::handle<Standard_Type>, occ::handle<BinMDF_ADriver>> myMap;
  NCollection_DoubleMap<occ::handle<Standard_Type>, int>                       myMapId;
};

inline void BinMDF_ADriverTable::AssignId(const occ::handle<Standard_Type>& theType,
                                          const int                         theId)
{
  myMapId.Bind(theType, theId);
}

inline int BinMDF_ADriverTable::GetDriver(const occ::handle<Standard_Type>& theType,
                                          occ::handle<BinMDF_ADriver>&      theDriver)
{
  if (!myMap.IsBound(theType))
  {
    AddDerivedDriver(theType->Name());
  }

  int anId = 0;
  if (myMap.IsBound(theType))
  {
    theDriver = myMap(theType);
    if (myMapId.IsBound1(theType))
      anId = myMapId.Find1(theType);
  }
  return anId;
}

inline occ::handle<BinMDF_ADriver> BinMDF_ADriverTable::GetDriver(const int theTypeId)
{
  occ::handle<BinMDF_ADriver> aDriver;
  if (myMapId.IsBound2(theTypeId))
  {
    const occ::handle<Standard_Type>& aType = myMapId.Find2(theTypeId);
    aDriver                                 = myMap(aType);
  }
  return aDriver;
}
