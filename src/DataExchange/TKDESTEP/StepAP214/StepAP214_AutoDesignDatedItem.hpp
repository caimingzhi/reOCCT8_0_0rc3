#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ApprovalPersonOrganization;
class StepAP214_AutoDesignDateAndPersonAssignment;
class StepBasic_ProductDefinitionEffectivity;

class StepAP214_AutoDesignDatedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a AutoDesignDatedItem SelectType
  Standard_EXPORT StepAP214_AutoDesignDatedItem();

  //! Recognizes a AutoDesignDatedItem Kind Entity that is :
  //! 1 -> ApprovalPersonOrganization
  //! 2 -> AutoDesignDateAndPersonAssignment
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ApprovalPersonOrganization (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ApprovalPersonOrganization> ApprovalPersonOrganization()
    const;

  //! returns Value as a AutoDesignDateAndPersonAssignment (Null if another type)
  Standard_EXPORT occ::handle<StepAP214_AutoDesignDateAndPersonAssignment>
                  AutoDesignDateAndPersonAssignment() const;

  //! returns Value as a ProductDefinitionEffectivity
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionEffectivity> ProductDefinitionEffectivity()
    const;
};
