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

  //! Returns a IdAttributeSelect select type
  Standard_EXPORT StepAP242_IdAttributeSelect();

  //! Recognizes a IdAttributeSelect Kind Entity that is :
  //! 1 -> Action
  //! 2 -> Address
  //! 3 -> ApplicationContext
  //! 4 -> DimensionalSize
  //! 5 -> GeometricTolerance
  //! 6 -> Group
  //! 7 -> Reserved for OrganizatonalProject (not implemented in OCCT)
  //! 8 -> ProductCategory
  //! 9 -> PropertyDefinition
  //! 10 -> Representation
  //! 11 -> ShapeAspect
  //! 12 -> ShapeAspectRelationship
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Action (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Action> Action() const;

  //! returns Value as a Address (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Address> Address() const;

  //! returns Value as a ApplicationContext (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ApplicationContext> ApplicationContext() const;

  //! returns Value as a DimensionalSize (Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;

  //! returns Value as a GeometricTolerance (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> GeometricTolerance() const;

  //! returns Value as a Group (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Group> Group() const;

  //! returns Value as a ProductCategory (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductCategory> ProductCategory() const;

  //! returns Value as a PropertyDefinition (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  //! returns Value as a ShapeAspect (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  //! returns Value as a ShapeAspectRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;
};
