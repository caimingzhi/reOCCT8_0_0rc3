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

class StepBasic_RoleSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepBasic_RoleSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_ActionAssignment> ActionAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_ActionRequestAssignment> ActionRequestAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_ApprovalAssignment> ApprovalAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_ApprovalDateTime> ApprovalDateTime() const;

  Standard_EXPORT occ::handle<StepBasic_CertificationAssignment> CertificationAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_ContractAssignment> ContractAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_DocumentReference> DocumentReference() const;

  Standard_EXPORT occ::handle<StepBasic_EffectivityAssignment> EffectivityAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_GroupAssignment> GroupAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_NameAssignment> NameAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_SecurityClassificationAssignment>
                  SecurityClassificationAssignment() const;
};
