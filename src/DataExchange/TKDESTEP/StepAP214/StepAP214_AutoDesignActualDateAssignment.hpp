#pragma once

#include <Standard.hpp>

#include <StepAP214_AutoDesignDatedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DateAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_Date;
class StepBasic_DateRole;
class StepAP214_AutoDesignDatedItem;

class StepAP214_AutoDesignActualDateAssignment : public StepBasic_DateAssignment
{

public:
  Standard_EXPORT StepAP214_AutoDesignActualDateAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Date>&                                     aAssignedDate,
    const occ::handle<StepBasic_DateRole>&                                 aRole,
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>> Items() const;

  Standard_EXPORT StepAP214_AutoDesignDatedItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AutoDesignActualDateAssignment, StepBasic_DateAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_AutoDesignDatedItem>> items;
};
