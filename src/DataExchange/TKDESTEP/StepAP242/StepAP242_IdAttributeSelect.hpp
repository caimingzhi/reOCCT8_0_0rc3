#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Action;
class StepBasic_Address;
class StepBasic_ApplicationContext;
class StepShape_DimensionalSize;
class StepDimTol_GeometricTolerance;
class StepBasic_Group;
class StepBasic_ProductCategory;
class StepRepr_PropertyDefinition;
class StepRepr_Representation;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;

class StepAP242_IdAttributeSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP242_IdAttributeSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Action> Action() const;

  Standard_EXPORT occ::handle<StepBasic_Address> Address() const;

  Standard_EXPORT occ::handle<StepBasic_ApplicationContext> ApplicationContext() const;

  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;

  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> GeometricTolerance() const;

  Standard_EXPORT occ::handle<StepBasic_Group> Group() const;

  Standard_EXPORT occ::handle<StepBasic_ProductCategory> ProductCategory() const;

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;
};
