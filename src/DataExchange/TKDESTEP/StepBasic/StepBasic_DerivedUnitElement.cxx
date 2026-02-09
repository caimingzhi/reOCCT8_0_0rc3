

#include <Standard_Type.hpp>
#include <StepBasic_DerivedUnitElement.hpp>
#include <StepBasic_NamedUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DerivedUnitElement, Standard_Transient)

StepBasic_DerivedUnitElement::StepBasic_DerivedUnitElement() = default;

void StepBasic_DerivedUnitElement::Init(const occ::handle<StepBasic_NamedUnit>& aUnit,
                                        const double                            aExponent)
{
  theUnit     = aUnit;
  theExponent = aExponent;
}

void StepBasic_DerivedUnitElement::SetUnit(const occ::handle<StepBasic_NamedUnit>& aUnit)
{
  theUnit = aUnit;
}

occ::handle<StepBasic_NamedUnit> StepBasic_DerivedUnitElement::Unit() const
{
  return theUnit;
}

void StepBasic_DerivedUnitElement::SetExponent(const double aExponent)
{
  theExponent = aExponent;
}

double StepBasic_DerivedUnitElement::Exponent() const
{
  return theExponent;
}
