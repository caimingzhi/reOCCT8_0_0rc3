#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESAppli_LevelToPWBLayerMap : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_LevelToPWBLayerMap();

  Standard_EXPORT void Init(
    const int                                                                      nbPropVal,
    const occ::handle<NCollection_HArray1<int>>&                                   allExchLevels,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allNativeLevels,
    const occ::handle<NCollection_HArray1<int>>&                                   allPhysLevels,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allExchIdents);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int NbLevelToLayerDefs() const;

  Standard_EXPORT int ExchangeFileLevelNumber(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> NativeLevel(const int Index) const;

  Standard_EXPORT int PhysicalLayerNumber(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ExchangeFileLevelIdent(
    const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_LevelToPWBLayerMap, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<NCollection_HArray1<int>> theExchangeFileLevelNumber;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theNativeLevel;
  occ::handle<NCollection_HArray1<int>>                                   thePhysicalLayerNumber;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theExchangeFileLevelIdent;
};
