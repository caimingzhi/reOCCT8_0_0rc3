#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepBasic_DerivedUnit.hpp>
#include <StepBasic_NamedUnit.hpp>
#include <StepBasic_Unit.hpp>

StepBasic_Unit::StepBasic_Unit() = default;

int StepBasic_Unit::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_NamedUnit)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DerivedUnit)))
    return 2;
  return 0;
}

occ::handle<StepBasic_NamedUnit> StepBasic_Unit::NamedUnit() const
{
  return GetCasted(StepBasic_NamedUnit, Value());
}

occ::handle<StepBasic_DerivedUnit> StepBasic_Unit::DerivedUnit() const
{
  return GetCasted(StepBasic_DerivedUnit, Value());
}
