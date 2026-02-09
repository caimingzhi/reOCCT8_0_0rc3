#include <StepAP203_Change.hpp>
#include <StepBasic_Action.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_Change, StepBasic_ActionAssignment)

StepAP203_Change::StepAP203_Change() = default;

void StepAP203_Change::Init(const occ::handle<StepBasic_Action>& aActionAssignment_AssignedAction,
                            const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& aItems)
{
  StepBasic_ActionAssignment::Init(aActionAssignment_AssignedAction);

  theItems = aItems;
}

occ::handle<NCollection_HArray1<StepAP203_WorkItem>> StepAP203_Change::Items() const
{
  return theItems;
}

void StepAP203_Change::SetItems(const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& aItems)
{
  theItems = aItems;
}
