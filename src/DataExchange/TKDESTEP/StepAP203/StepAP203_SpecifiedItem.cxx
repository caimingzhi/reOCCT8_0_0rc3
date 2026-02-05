#include <Standard_Transient.hpp>
#include <StepAP203_SpecifiedItem.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepRepr_ShapeAspect.hpp>

//=================================================================================================

StepAP203_SpecifiedItem::StepAP203_SpecifiedItem() = default;

//=================================================================================================

int StepAP203_SpecifiedItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 2;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinition> StepAP203_SpecifiedItem::ProductDefinition() const
{
  return occ::down_cast<StepBasic_ProductDefinition>(Value());
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepAP203_SpecifiedItem::ShapeAspect() const
{
  return occ::down_cast<StepRepr_ShapeAspect>(Value());
}
