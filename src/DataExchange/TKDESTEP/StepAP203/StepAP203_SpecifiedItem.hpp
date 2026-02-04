#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinition;
class StepRepr_ShapeAspect;

//! Representation of STEP SELECT type SpecifiedItem
class StepAP203_SpecifiedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepAP203_SpecifiedItem();

  //! Recognizes a kind of SpecifiedItem select type
  //! 1 -> ProductDefinition from StepBasic
  //! 2 -> ShapeAspect from StepRepr
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ProductDefinition (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! Returns Value as ShapeAspect (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;
};

