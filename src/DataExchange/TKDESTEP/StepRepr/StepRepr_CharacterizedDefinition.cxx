#include <Standard_Transient.hpp>
#include <StepBasic_CharacterizedObject.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepRepr_CharacterizedDefinition.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>

//=================================================================================================

StepRepr_CharacterizedDefinition::StepRepr_CharacterizedDefinition() = default;

//=================================================================================================

int StepRepr_CharacterizedDefinition::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_CharacterizedObject)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ProductDefinitionShape)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentFile)))
    return 7;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_CharacterizedObject> StepRepr_CharacterizedDefinition::CharacterizedObject()
  const
{
  return occ::down_cast<StepBasic_CharacterizedObject>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinition> StepRepr_CharacterizedDefinition::ProductDefinition() const
{
  return occ::down_cast<StepBasic_ProductDefinition>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionRelationship> StepRepr_CharacterizedDefinition::
  ProductDefinitionRelationship() const
{
  return occ::down_cast<StepBasic_ProductDefinitionRelationship>(Value());
}

//=================================================================================================

occ::handle<StepRepr_ProductDefinitionShape> StepRepr_CharacterizedDefinition::
  ProductDefinitionShape() const
{
  return occ::down_cast<StepRepr_ProductDefinitionShape>(Value());
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepRepr_CharacterizedDefinition::ShapeAspect() const
{
  return occ::down_cast<StepRepr_ShapeAspect>(Value());
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspectRelationship> StepRepr_CharacterizedDefinition::
  ShapeAspectRelationship() const
{
  return occ::down_cast<StepRepr_ShapeAspectRelationship>(Value());
}

//=================================================================================================

occ::handle<StepBasic_DocumentFile> StepRepr_CharacterizedDefinition::DocumentFile() const
{
  return occ::down_cast<StepBasic_DocumentFile>(Value());
}
