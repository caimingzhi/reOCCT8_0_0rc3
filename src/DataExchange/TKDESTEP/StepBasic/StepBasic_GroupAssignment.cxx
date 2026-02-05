#include <Standard_Type.hpp>
#include <StepBasic_Group.hpp>
#include <StepBasic_GroupAssignment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_GroupAssignment, Standard_Transient)

//=================================================================================================

StepBasic_GroupAssignment::StepBasic_GroupAssignment() = default;

//=================================================================================================

void StepBasic_GroupAssignment::Init(const occ::handle<StepBasic_Group>& aAssignedGroup)
{

  theAssignedGroup = aAssignedGroup;
}

//=================================================================================================

occ::handle<StepBasic_Group> StepBasic_GroupAssignment::AssignedGroup() const
{
  return theAssignedGroup;
}

//=================================================================================================

void StepBasic_GroupAssignment::SetAssignedGroup(const occ::handle<StepBasic_Group>& aAssignedGroup)
{
  theAssignedGroup = aAssignedGroup;
}
