

#include <Standard_Type.hpp>
#include <StepBasic_DerivedUnit.hpp>
#include <StepBasic_DerivedUnitElement.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DerivedUnit, Standard_Transient)

StepBasic_DerivedUnit::StepBasic_DerivedUnit() = default;

void StepBasic_DerivedUnit::Init(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>& elements)
{
  theElements = elements;
}

void StepBasic_DerivedUnit::SetElements(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>& elements)
{
  theElements = elements;
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>> StepBasic_DerivedUnit::
  Elements() const
{
  return theElements;
}

int StepBasic_DerivedUnit::NbElements() const
{
  return theElements->Length();
}

occ::handle<StepBasic_DerivedUnitElement> StepBasic_DerivedUnit::ElementsValue(const int num) const
{
  return theElements->Value(num);
}
