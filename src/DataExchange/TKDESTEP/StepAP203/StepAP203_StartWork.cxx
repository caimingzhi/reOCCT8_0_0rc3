#include <StepAP203_StartWork.hpp>
#include <StepBasic_Action.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_StartWork, StepBasic_ActionAssignment)

//=================================================================================================

StepAP203_StartWork::StepAP203_StartWork() = default;

//=================================================================================================

void StepAP203_StartWork::Init(
  const occ::handle<StepBasic_Action>&                        aActionAssignment_AssignedAction,
  const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& aItems)
{
  StepBasic_ActionAssignment::Init(aActionAssignment_AssignedAction);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP203_WorkItem>> StepAP203_StartWork::Items() const
{
  return theItems;
}

//=================================================================================================

void StepAP203_StartWork::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& aItems)
{
  theItems = aItems;
}
