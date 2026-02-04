#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_NamedUnit;

//! Added from StepBasic Rev2 to Rev4
class StepBasic_DerivedUnitElement : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DerivedUnitElement();

  Standard_EXPORT void Init(const occ::handle<StepBasic_NamedUnit>& aUnit, const double aExponent);

  Standard_EXPORT void SetUnit(const occ::handle<StepBasic_NamedUnit>& aUnit);

  Standard_EXPORT occ::handle<StepBasic_NamedUnit> Unit() const;

  Standard_EXPORT void SetExponent(const double aExponent);

  Standard_EXPORT double Exponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DerivedUnitElement, Standard_Transient)

private:
  occ::handle<StepBasic_NamedUnit> theUnit;
  double                           theExponent;
};

