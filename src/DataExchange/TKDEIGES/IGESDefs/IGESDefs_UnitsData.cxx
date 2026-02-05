#include <IGESDefs_UnitsData.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDefs_UnitsData, IGESData_IGESEntity)

IGESDefs_UnitsData::IGESDefs_UnitsData() = default;

void IGESDefs_UnitsData::Init(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& unitTypes,
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& unitValues,
  const occ::handle<NCollection_HArray1<double>>&                                unitScales)
{
  int length = unitTypes->Length();
  if (unitTypes->Lower() != 1 || (unitValues->Lower() != 1 || unitValues->Length() != length)
      || (unitScales->Lower() != 1 || unitScales->Length() != length))
    throw Standard_DimensionMismatch("IGESDefs_UnitsData : Init");
  theUnitTypes  = unitTypes;
  theUnitValues = unitValues;
  theUnitScales = unitScales;
  InitTypeAndForm(316, 0);
}

int IGESDefs_UnitsData::NbUnits() const
{
  return theUnitTypes->Length();
}

occ::handle<TCollection_HAsciiString> IGESDefs_UnitsData::UnitType(const int UnitNum) const
{
  return theUnitTypes->Value(UnitNum);
}

occ::handle<TCollection_HAsciiString> IGESDefs_UnitsData::UnitValue(const int UnitNum) const
{
  return theUnitValues->Value(UnitNum);
}

double IGESDefs_UnitsData::ScaleFactor(const int UnitNum) const
{
  return theUnitScales->Value(UnitNum);
}
