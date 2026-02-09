#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>

enum UnitsAPI_SystemUnits
{
  UnitsAPI_DEFAULT,
  UnitsAPI_SI,
  UnitsAPI_MDTV
};

class Units_Dimensions;

class UnitsAPI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double CurrentToLS(const double aData, const char* aQuantity);

  Standard_EXPORT static double CurrentToSI(const double aData, const char* aQuantity);

  Standard_EXPORT static double CurrentFromLS(const double aData, const char* aQuantity);

  Standard_EXPORT static double CurrentFromSI(const double aData, const char* aQuantity);

  Standard_EXPORT static double AnyToLS(const double aData, const char* aUnit);

  Standard_EXPORT static double AnyToLS(const double                   aData,
                                        const char*                    aUnit,
                                        occ::handle<Units_Dimensions>& aDim);

  Standard_EXPORT static double AnyToSI(const double aData, const char* aUnit);

  Standard_EXPORT static double AnyToSI(const double                   aData,
                                        const char*                    aUnit,
                                        occ::handle<Units_Dimensions>& aDim);

  Standard_EXPORT static double AnyFromLS(const double aData, const char* aUnit);

  Standard_EXPORT static double AnyFromSI(const double aData, const char* aUnit);

  Standard_EXPORT static double CurrentToAny(const double aData,
                                             const char*  aQuantity,
                                             const char*  aUnit);

  Standard_EXPORT static double CurrentFromAny(const double aData,
                                               const char*  aQuantity,
                                               const char*  aUnit);

  Standard_EXPORT static double AnyToAny(const double aData,
                                         const char*  aUnit1,
                                         const char*  aUnit2);

  Standard_EXPORT static double LSToSI(const double aData, const char* aQuantity);

  Standard_EXPORT static double SIToLS(const double aData, const char* aQuantity);

  Standard_EXPORT static void SetLocalSystem(const UnitsAPI_SystemUnits aSystemUnit = UnitsAPI_SI);

  Standard_EXPORT static UnitsAPI_SystemUnits LocalSystem();

  Standard_EXPORT static void SetCurrentUnit(const char* aQuantity, const char* aUnit);

  Standard_EXPORT static const char* CurrentUnit(const char* aQuantity);

  Standard_EXPORT static void Save();

  Standard_EXPORT static void Reload();

  Standard_EXPORT static occ::handle<Units_Dimensions> Dimensions(const char* aQuantity);

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionLess();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionMass();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionLength();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionTime();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionElectricCurrent();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionThermodynamicTemperature();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionAmountOfSubstance();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionLuminousIntensity();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionPlaneAngle();

  Standard_EXPORT static occ::handle<Units_Dimensions> DimensionSolidAngle();

  Standard_EXPORT static bool Check(const char* aQuantity, const char* aUnit);

private:
  Standard_EXPORT static void CheckLoading(const UnitsAPI_SystemUnits aSystemUnit);
};
