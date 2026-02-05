#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Contract;

//! Representation of STEP entity ContractAssignment
class StepBasic_ContractAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ContractAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_Contract>& aAssignedContract);

  //! Returns field AssignedContract
  Standard_EXPORT occ::handle<StepBasic_Contract> AssignedContract() const;

  //! Set field AssignedContract
  Standard_EXPORT void SetAssignedContract(const occ::handle<StepBasic_Contract>& AssignedContract);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ContractAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Contract> theAssignedContract;
};
