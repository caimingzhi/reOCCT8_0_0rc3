#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_CharacterizedObject;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionRelationship;
class StepRepr_ProductDefinitionShape;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;
class StepBasic_DocumentFile;

//! Representation of STEP SELECT type CharacterizedDefinition
class StepRepr_CharacterizedDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepRepr_CharacterizedDefinition();

  //! Recognizes a kind of CharacterizedDefinition select type
  //! 1 -> CharacterizedObject from StepBasic
  //! 2 -> ProductDefinition from StepBasic
  //! 3 -> ProductDefinitionRelationship from StepBasic
  //! 4 -> ProductDefinitionShape from StepRepr
  //! 5 -> ShapeAspect from StepRepr
  //! 6 -> ShapeAspectRelationship from StepRepr
  //! 7 -> DocumentFile from StepBasic
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as CharacterizedObject (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_CharacterizedObject> CharacterizedObject() const;

  //! Returns Value as ProductDefinition (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! Returns Value as ProductDefinitionRelationship (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  //! Returns Value as ProductDefinitionShape (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> ProductDefinitionShape() const;

  //! Returns Value as ShapeAspect (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  //! Returns Value as ShapeAspectRelationship (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;

  //! Returns Value as DocumentFile (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_DocumentFile> DocumentFile() const;
};
