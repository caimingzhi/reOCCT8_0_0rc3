#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ActionAssignment;
class StepBasic_ActionRequestAssignment;
class StepBasic_ApprovalAssignment;
class StepBasic_ApprovalDateTime;
class StepBasic_CertificationAssignment;
class StepBasic_ContractAssignment;
class StepBasic_DocumentReference;
class StepBasic_EffectivityAssignment;
class StepBasic_GroupAssignment;
class StepBasic_NameAssignment;
class StepBasic_SecurityClassificationAssignment;

//! Representation of STEP SELECT type RoleSelect
class StepBasic_RoleSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepBasic_RoleSelect();

  //! Recognizes a kind of RoleSelect select type
  //! 1 -> ActionAssignment from StepBasic
  //! 2 -> ActionRequestAssignment from StepBasic
  //! 3 -> ApprovalAssignment from StepBasic
  //! 4 -> ApprovalDateTime from StepBasic
  //! 5 -> CertificationAssignment from StepBasic
  //! 6 -> ContractAssignment from StepBasic
  //! 7 -> DocumentReference from StepBasic
  //! 8 -> EffectivityAssignment from StepBasic
  //! 9 -> GroupAssignment from StepBasic
  //! 10 -> NameAssignment from StepBasic
  //! 11 -> SecurityClassificationAssignment from StepBasic
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ActionAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ActionAssignment> ActionAssignment() const;

  //! Returns Value as ActionRequestAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ActionRequestAssignment> ActionRequestAssignment() const;

  //! Returns Value as ApprovalAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ApprovalAssignment> ApprovalAssignment() const;

  //! Returns Value as ApprovalDateTime (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ApprovalDateTime> ApprovalDateTime() const;

  //! Returns Value as CertificationAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_CertificationAssignment> CertificationAssignment() const;

  //! Returns Value as ContractAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ContractAssignment> ContractAssignment() const;

  //! Returns Value as DocumentReference (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_DocumentReference> DocumentReference() const;

  //! Returns Value as EffectivityAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_EffectivityAssignment> EffectivityAssignment() const;

  //! Returns Value as GroupAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_GroupAssignment> GroupAssignment() const;

  //! Returns Value as NameAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_NameAssignment> NameAssignment() const;

  //! Returns Value as SecurityClassificationAssignment (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_SecurityClassificationAssignment>
                  SecurityClassificationAssignment() const;
};
