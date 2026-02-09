

#include <Standard_Transient.hpp>
#include <StepBasic_SizeMember.hpp>
#include <StepBasic_SizeSelect.hpp>
#include <StepData_SelectMember.hpp>

StepBasic_SizeSelect::StepBasic_SizeSelect() = default;

int StepBasic_SizeSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SizeMember)))
    return 1;
  return 0;
}

occ::handle<StepData_SelectMember> StepBasic_SizeSelect::NewMember() const
{
  return new StepBasic_SizeMember;
}

int StepBasic_SizeSelect::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;

  if (ent->Matches("POSITIVE_LENGTH_MEASURE"))
    return 1;
  return 0;
}

void StepBasic_SizeSelect::SetRealValue(const double aRealValue)
{
  SetReal(aRealValue, "POSITIVE_LENGTH_MEASURE");
}

double StepBasic_SizeSelect::RealValue() const
{
  return Real();
}
