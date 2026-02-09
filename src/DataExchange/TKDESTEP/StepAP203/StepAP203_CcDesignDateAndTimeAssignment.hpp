#pragma once

#include <Standard.hpp>

#include <StepAP203_DateTimeItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DateAndTimeAssignment.hpp>
class StepBasic_DateAndTime;
class StepBasic_DateTimeRole;

class StepAP203_CcDesignDateAndTimeAssignment : public StepBasic_DateAndTimeAssignment
{

public:
  Standard_EXPORT StepAP203_CcDesignDateAndTimeAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_DateAndTime>&  aDateAndTimeAssignment_AssignedDateAndTime,
    const occ::handle<StepBasic_DateTimeRole>& aDateAndTimeAssignment_Role,
    const occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>> Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_CcDesignDateAndTimeAssignment, StepBasic_DateAndTimeAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>> theItems;
};
