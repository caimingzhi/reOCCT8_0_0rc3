#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinition;
class StepAP203_ChangeRequest;
class StepAP203_StartRequest;
class StepAP203_Change;
class StepAP203_StartWork;
class StepBasic_ApprovalPersonOrganization;
class StepBasic_Contract;
class StepBasic_SecurityClassification;
class StepBasic_Certification;

//! Representation of STEP SELECT type DateTimeItem
class StepAP203_DateTimeItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepAP203_DateTimeItem();

  //! Recognizes a kind of DateTimeItem select type
  //! 1 -> ProductDefinition from StepBasic
  //! 2 -> ChangeRequest from StepAP203
  //! 3 -> StartRequest from StepAP203
  //! 4 -> Change from StepAP203
  //! 5 -> StartWork from StepAP203
  //! 6 -> ApprovalPersonOrganization from StepBasic
  //! 7 -> Contract from StepBasic
  //! 8 -> SecurityClassification from StepBasic
  //! 9 -> Certification from StepBasic
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ProductDefinition (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! Returns Value as ChangeRequest (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_ChangeRequest> ChangeRequest() const;

  //! Returns Value as StartRequest (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_StartRequest> StartRequest() const;

  //! Returns Value as Change (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_Change> Change() const;

  //! Returns Value as StartWork (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_StartWork> StartWork() const;

  //! Returns Value as ApprovalPersonOrganization (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ApprovalPersonOrganization> ApprovalPersonOrganization()
    const;

  //! Returns Value as Contract (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Contract> Contract() const;

  //! Returns Value as SecurityClassification (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_SecurityClassification> SecurityClassification() const;

  //! Returns Value as Certification (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Certification> Certification() const;
};
