#include <StepVisual_StyledItemTarget.hpp>
#include <MoniTool_Macros.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_Representation.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>

StepVisual_StyledItemTarget::StepVisual_StyledItemTarget() = default;

int StepVisual_StyledItemTarget::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_GeometricRepresentationItem)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MappedItem)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepShape_TopologicalRepresentationItem)))
    return 4;
  return 0;
}

occ::handle<StepGeom_GeometricRepresentationItem> StepVisual_StyledItemTarget::
  GeometricRepresentationItem() const
{
  return GetCasted(StepGeom_GeometricRepresentationItem, Value());
}

occ::handle<StepRepr_MappedItem> StepVisual_StyledItemTarget::MappedItem() const
{
  return GetCasted(StepRepr_MappedItem, Value());
}

occ::handle<StepRepr_Representation> StepVisual_StyledItemTarget::Representation() const
{
  return GetCasted(StepRepr_Representation, Value());
}

occ::handle<StepShape_TopologicalRepresentationItem> StepVisual_StyledItemTarget::
  TopologicalRepresentationItem() const
{
  return GetCasted(StepShape_TopologicalRepresentationItem, Value());
}
