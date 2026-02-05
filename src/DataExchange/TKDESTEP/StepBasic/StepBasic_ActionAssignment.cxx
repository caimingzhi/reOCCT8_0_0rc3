#include <Standard_Type.hpp>
#include <StepBasic_Action.hpp>
#include <StepBasic_ActionAssignment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ActionAssignment, Standard_Transient)

//=================================================================================================

StepBasic_ActionAssignment::StepBasic_ActionAssignment() = default;

//=================================================================================================

void StepBasic_ActionAssignment::Init(const occ::handle<StepBasic_Action>& aAssignedAction)
{

  theAssignedAction = aAssignedAction;
}

//=================================================================================================

occ::handle<StepBasic_Action> StepBasic_ActionAssignment::AssignedAction() const
{
  return theAssignedAction;
}

//=================================================================================================

void StepBasic_ActionAssignment::SetAssignedAction(
  const occ::handle<StepBasic_Action>& aAssignedAction)
{
  theAssignedAction = aAssignedAction;
}
