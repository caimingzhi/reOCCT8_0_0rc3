#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepRepr_ProductDefinitionShape;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;

class StepRepr_ShapeDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ShapeDefinition SelectType
  Standard_EXPORT StepRepr_ShapeDefinition();

  //! Recognizes a ShapeDefinition Kind Entity that is :
  //! 1 -> ProductDefinitionShape
  //! 2 -> ShapeAspect
  //! 3 -> ShapeAspectRelationship
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ProductDefinitionShape (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> ProductDefinitionShape() const;

  //! returns Value as a ShapeAspect (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  //! returns Value as a ShapeAspectRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;
};
