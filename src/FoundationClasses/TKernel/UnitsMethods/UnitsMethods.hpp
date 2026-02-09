#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <UnitsMethods_LengthUnit.hpp>

class UnitsMethods
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double GetLengthFactorValue(const int theUnit);

  Standard_EXPORT static double GetCasCadeLengthUnit(
    const UnitsMethods_LengthUnit theBaseUnit = UnitsMethods_LengthUnit_Millimeter);

  Standard_EXPORT static void SetCasCadeLengthUnit(
    const double                  theUnitValue,
    const UnitsMethods_LengthUnit theBaseUnit = UnitsMethods_LengthUnit_Millimeter);

  Standard_EXPORT static void SetCasCadeLengthUnit(const int theUnit);

  Standard_EXPORT static double GetLengthUnitScale(const UnitsMethods_LengthUnit theFromUnit,
                                                   const UnitsMethods_LengthUnit theToUnit);

  Standard_EXPORT static UnitsMethods_LengthUnit GetLengthUnitByFactorValue(
    const double                  theFactorValue,
    const UnitsMethods_LengthUnit theBaseUnit = UnitsMethods_LengthUnit_Millimeter);

  Standard_EXPORT static const char* DumpLengthUnit(
    const double                  theScaleFactor,
    const UnitsMethods_LengthUnit theBaseUnit = UnitsMethods_LengthUnit_Millimeter);

  Standard_EXPORT static const char* DumpLengthUnit(const UnitsMethods_LengthUnit theUnit);

  Standard_EXPORT static UnitsMethods_LengthUnit LengthUnitFromString(const char* theStr,
                                                                      const bool  theCaseSensitive);
};
