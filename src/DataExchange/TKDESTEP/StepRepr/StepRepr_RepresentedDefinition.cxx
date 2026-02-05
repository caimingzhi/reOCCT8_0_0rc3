#include <Standard_Transient.hpp>
#include <StepBasic_GeneralProperty.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_PropertyDefinitionRelationship.hpp>
#include <StepRepr_RepresentedDefinition.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>

//=================================================================================================

StepRepr_RepresentedDefinition::StepRepr_RepresentedDefinition() = default;

//=================================================================================================

int StepRepr_RepresentedDefinition::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GeneralProperty)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinitionRelationship)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship)))
    return 5;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_GeneralProperty> StepRepr_RepresentedDefinition::GeneralProperty() const
{
  return occ::down_cast<StepBasic_GeneralProperty>(Value());
}

//=================================================================================================

occ::handle<StepRepr_PropertyDefinition> StepRepr_RepresentedDefinition::PropertyDefinition() const
{
  return occ::down_cast<StepRepr_PropertyDefinition>(Value());
}

//=================================================================================================

occ::handle<StepRepr_PropertyDefinitionRelationship> StepRepr_RepresentedDefinition::
  PropertyDefinitionRelationship() const
{
  return occ::down_cast<StepRepr_PropertyDefinitionRelationship>(Value());
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepRepr_RepresentedDefinition::ShapeAspect() const
{
  return occ::down_cast<StepRepr_ShapeAspect>(Value());
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspectRelationship> StepRepr_RepresentedDefinition::
  ShapeAspectRelationship() const
{
  return occ::down_cast<StepRepr_ShapeAspectRelationship>(Value());
}
