#include <Standard_Transient.hpp>
#include <StepFEA_ElementGroup.hpp>
#include <StepFEA_ElementOrElementGroup.hpp>
#include <StepFEA_ElementRepresentation.hpp>

StepFEA_ElementOrElementGroup::StepFEA_ElementOrElementGroup() = default;

int StepFEA_ElementOrElementGroup::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepFEA_ElementRepresentation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepFEA_ElementGroup)))
    return 2;
  return 0;
}

occ::handle<StepFEA_ElementRepresentation> StepFEA_ElementOrElementGroup::ElementRepresentation()
  const
{
  return occ::down_cast<StepFEA_ElementRepresentation>(Value());
}

occ::handle<StepFEA_ElementGroup> StepFEA_ElementOrElementGroup::ElementGroup() const
{
  return occ::down_cast<StepFEA_ElementGroup>(Value());
}
