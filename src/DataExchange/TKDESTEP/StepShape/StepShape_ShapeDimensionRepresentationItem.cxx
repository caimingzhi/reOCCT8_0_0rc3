#include <StepShape_ShapeDimensionRepresentationItem.hpp>
#include <MoniTool_Macros.hpp>
#include <StepRepr_CompoundRepresentationItem.hpp>
#include <StepRepr_DescriptiveRepresentationItem.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>
#include <StepGeom_Placement.hpp>

StepShape_ShapeDimensionRepresentationItem::StepShape_ShapeDimensionRepresentationItem() = default;

int StepShape_ShapeDimensionRepresentationItem::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_CompoundRepresentationItem)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_DescriptiveRepresentationItem)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MeasureRepresentationItem)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Placement)))
    return 4;
  return 0;
}

occ::handle<StepRepr_CompoundRepresentationItem> StepShape_ShapeDimensionRepresentationItem::
  CompoundRepresentationItem() const
{
  return GetCasted(StepRepr_CompoundRepresentationItem, Value());
}

occ::handle<StepRepr_DescriptiveRepresentationItem> StepShape_ShapeDimensionRepresentationItem::
  DescriptiveRepresentationItem() const
{
  return GetCasted(StepRepr_DescriptiveRepresentationItem, Value());
}

occ::handle<StepRepr_MeasureRepresentationItem> StepShape_ShapeDimensionRepresentationItem::
  MeasureRepresentationItem() const
{
  return GetCasted(StepRepr_MeasureRepresentationItem, Value());
}

occ::handle<StepGeom_Placement> StepShape_ShapeDimensionRepresentationItem::Placement() const
{
  return GetCasted(StepGeom_Placement, Value());
}
