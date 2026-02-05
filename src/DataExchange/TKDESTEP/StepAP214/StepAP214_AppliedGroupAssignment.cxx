#include <StepAP214_AppliedGroupAssignment.hpp>
#include <StepBasic_Group.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedGroupAssignment, StepBasic_GroupAssignment)

//=================================================================================================

StepAP214_AppliedGroupAssignment::StepAP214_AppliedGroupAssignment() = default;

//=================================================================================================

void StepAP214_AppliedGroupAssignment::Init(
  const occ::handle<StepBasic_Group>&                          aGroupAssignment_AssignedGroup,
  const occ::handle<NCollection_HArray1<StepAP214_GroupItem>>& aItems)
{
  StepBasic_GroupAssignment::Init(aGroupAssignment_AssignedGroup);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP214_GroupItem>> StepAP214_AppliedGroupAssignment::Items()
  const
{
  return theItems;
}

//=================================================================================================

void StepAP214_AppliedGroupAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_GroupItem>>& aItems)
{
  theItems = aItems;
}
