#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

class IGESDefs_UnitsData : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_UnitsData();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& unitTypes,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& unitValues,
    const occ::handle<NCollection_HArray1<double>>&                                unitScales);

  Standard_EXPORT int NbUnits() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> UnitType(const int UnitNum) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> UnitValue(const int UnitNum) const;

  Standard_EXPORT double ScaleFactor(const int UnitNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_UnitsData, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theUnitTypes;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theUnitValues;
  occ::handle<NCollection_HArray1<double>>                                theUnitScales;
};
