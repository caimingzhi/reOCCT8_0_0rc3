#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Group;

//! Representation of STEP entity GroupAssignment
class StepBasic_GroupAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_GroupAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_Group>& aAssignedGroup);

  //! Returns field AssignedGroup
  Standard_EXPORT occ::handle<StepBasic_Group> AssignedGroup() const;

  //! Set field AssignedGroup
  Standard_EXPORT void SetAssignedGroup(const occ::handle<StepBasic_Group>& AssignedGroup);

  DEFINE_STANDARD_RTTIEXT(StepBasic_GroupAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Group> theAssignedGroup;
};

