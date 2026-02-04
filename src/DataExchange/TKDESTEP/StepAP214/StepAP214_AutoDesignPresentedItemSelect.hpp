#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinitionRelationship;
class StepBasic_ProductDefinition;
class StepRepr_ProductDefinitionShape;
class StepRepr_RepresentationRelationship;
class StepRepr_ShapeAspect;
class StepBasic_DocumentRelationship;

class StepAP214_AutoDesignPresentedItemSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a AutoDesignPresentedItemSelect SelectType
  Standard_EXPORT StepAP214_AutoDesignPresentedItemSelect();

  //! Recognizes a AutoDesignPresentedItemSelect Kind Entity that is :
  //! 1 -> ProductDefinition,
  //! 2 -> ProductDefinitionRelationship,
  //! 3 -> ProductDefinitionShape
  //! 4 -> RepresentationRelationship
  //! 5 -> ShapeAspect
  //! 6 -> DocumentRelationship,
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ProductDefinitionRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  //! returns Value as a ProductDefinition (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! returns Value as a ProductDefinitionShape (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> ProductDefinitionShape() const;

  //! returns Value as a RepresentationRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_RepresentationRelationship> RepresentationRelationship()
    const;

  //! returns Value as a ShapeAspect (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  //! returns Value as a DocumentRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_DocumentRelationship> DocumentRelationship() const;
};

