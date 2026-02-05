#pragma once

#include <Standard.hpp>

#include <StepAP214_AutoDesignDateAndTimeItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DateAndTimeAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_DateAndTime;
class StepBasic_DateTimeRole;
class StepAP214_AutoDesignDateAndTimeItem;

class StepAP214_AutoDesignActualDateAndTimeAssignment : public StepBasic_DateAndTimeAssignment
{

public:
  //! Returns a AutoDesignActualDateAndTimeAssignment
  Standard_EXPORT StepAP214_AutoDesignActualDateAndTimeAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_DateAndTime>&  aAssignedDateAndTime,
    const occ::handle<StepBasic_DateTimeRole>& aRole,
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>> Items()
    const;

  Standard_EXPORT StepAP214_AutoDesignDateAndTimeItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AutoDesignActualDateAndTimeAssignment,
                          StepBasic_DateAndTimeAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_AutoDesignDateAndTimeItem>> items;
};
