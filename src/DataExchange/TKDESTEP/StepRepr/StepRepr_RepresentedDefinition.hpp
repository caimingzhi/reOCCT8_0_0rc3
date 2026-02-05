#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_GeneralProperty;
class StepRepr_PropertyDefinition;
class StepRepr_PropertyDefinitionRelationship;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;

//! Representation of STEP SELECT type RepresentedDefinition
class StepRepr_RepresentedDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepRepr_RepresentedDefinition();

  //! Recognizes a kind of RepresentedDefinition select type
  //! 1 -> GeneralProperty from StepBasic
  //! 2 -> PropertyDefinition from StepRepr
  //! 3 -> PropertyDefinitionRelationship from StepRepr
  //! 4 -> ShapeAspect from StepRepr
  //! 5 -> ShapeAspectRelationship from StepRepr
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as GeneralProperty (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_GeneralProperty> GeneralProperty() const;

  //! Returns Value as PropertyDefinition (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  //! Returns Value as PropertyDefinitionRelationship (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_PropertyDefinitionRelationship>
                  PropertyDefinitionRelationship() const;

  //! Returns Value as ShapeAspect (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  //! Returns Value as ShapeAspectRelationship (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;
};
