#include <StepAP203_CcDesignDateAndTimeAssignment.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeRole.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP203_CcDesignDateAndTimeAssignment, StepBasic_DateAndTimeAssignment)

//=================================================================================================

StepAP203_CcDesignDateAndTimeAssignment::StepAP203_CcDesignDateAndTimeAssignment() = default;

//=================================================================================================

void StepAP203_CcDesignDateAndTimeAssignment::Init(
  const occ::handle<StepBasic_DateAndTime>&  aDateAndTimeAssignment_AssignedDateAndTime,
  const occ::handle<StepBasic_DateTimeRole>& aDateAndTimeAssignment_Role,
  const occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>>& aItems)
{
  StepBasic_DateAndTimeAssignment::Init(aDateAndTimeAssignment_AssignedDateAndTime,
                                        aDateAndTimeAssignment_Role);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>> StepAP203_CcDesignDateAndTimeAssignment::
  Items() const
{
  return theItems;
}

//=================================================================================================

void StepAP203_CcDesignDateAndTimeAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>>& aItems)
{
  theItems = aItems;
}
