#include <IGESAppli_LevelToPWBLayerMap.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_LevelToPWBLayerMap, IGESData_IGESEntity)

IGESAppli_LevelToPWBLayerMap::IGESAppli_LevelToPWBLayerMap() = default;

void IGESAppli_LevelToPWBLayerMap::Init(
  const int                                                                      nbPropVal,
  const occ::handle<NCollection_HArray1<int>>&                                   allExchLevels,
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allNativeLevels,
  const occ::handle<NCollection_HArray1<int>>&                                   allPhysLevels,
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allExchIdents)
{
  int num = allExchLevels->Length();
  if (allExchLevels->Lower() != 1
      || (allNativeLevels->Lower() != 1 || allNativeLevels->Length() != num)
      || (allPhysLevels->Lower() != 1 || allPhysLevels->Length() != num)
      || (allExchIdents->Lower() != 1 || allExchIdents->Length() != num))
    throw Standard_DimensionMismatch("IGESAppli_LevelToPWBLayerMap: Init");
  theNbPropertyValues        = nbPropVal;
  theExchangeFileLevelNumber = allExchLevels;
  theNativeLevel             = allNativeLevels;
  thePhysicalLayerNumber     = allPhysLevels;
  theExchangeFileLevelIdent  = allExchIdents;
  InitTypeAndForm(406, 24);
}

int IGESAppli_LevelToPWBLayerMap::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESAppli_LevelToPWBLayerMap::NbLevelToLayerDefs() const
{
  return theExchangeFileLevelNumber->Length();
}

int IGESAppli_LevelToPWBLayerMap::ExchangeFileLevelNumber(const int Index) const
{
  return theExchangeFileLevelNumber->Value(Index);
}

occ::handle<TCollection_HAsciiString> IGESAppli_LevelToPWBLayerMap::NativeLevel(
  const int Index) const
{
  return theNativeLevel->Value(Index);
}

int IGESAppli_LevelToPWBLayerMap::PhysicalLayerNumber(const int Index) const
{
  return thePhysicalLayerNumber->Value(Index);
}

occ::handle<TCollection_HAsciiString> IGESAppli_LevelToPWBLayerMap::ExchangeFileLevelIdent(
  const int Index) const
{
  return theExchangeFileLevelIdent->Value(Index);
}
