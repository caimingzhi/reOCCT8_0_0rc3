

#include <StepRepr_RepresentationOrRepresentationReference.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationReference.hpp>

StepRepr_RepresentationOrRepresentationReference::
  StepRepr_RepresentationOrRepresentationReference() = default;

int StepRepr_RepresentationOrRepresentationReference::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationReference)))
    return 2;
  return 0;
}

occ::handle<StepRepr_Representation> StepRepr_RepresentationOrRepresentationReference::
  Representation() const
{
  return occ::down_cast<StepRepr_Representation>(Value());
}

occ::handle<StepRepr_RepresentationReference> StepRepr_RepresentationOrRepresentationReference::
  RepresentationReference() const
{
  return occ::down_cast<StepRepr_RepresentationReference>(Value());
}
