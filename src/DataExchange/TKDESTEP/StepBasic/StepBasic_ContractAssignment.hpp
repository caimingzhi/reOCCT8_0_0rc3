#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Contract;

class StepBasic_ContractAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ContractAssignment();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Contract>& aAssignedContract);

  Standard_EXPORT occ::handle<StepBasic_Contract> AssignedContract() const;

  Standard_EXPORT void SetAssignedContract(const occ::handle<StepBasic_Contract>& AssignedContract);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ContractAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Contract> theAssignedContract;
};
