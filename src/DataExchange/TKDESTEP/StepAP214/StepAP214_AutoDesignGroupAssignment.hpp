#pragma once


#include <Standard.hpp>

#include <StepAP214_AutoDesignGroupedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_GroupAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_Group;
class StepAP214_AutoDesignGroupedItem;

class StepAP214_AutoDesignGroupAssignment : public StepBasic_GroupAssignment
{

public:
  //! Returns a AutoDesignGroupAssignment
  Standard_EXPORT StepAP214_AutoDesignGroupAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_Group>&                                      aAssignedGroup,
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>> Items() const;

  Standard_EXPORT StepAP214_AutoDesignGroupedItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AutoDesignGroupAssignment, StepBasic_GroupAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_AutoDesignGroupedItem>> items;
};

