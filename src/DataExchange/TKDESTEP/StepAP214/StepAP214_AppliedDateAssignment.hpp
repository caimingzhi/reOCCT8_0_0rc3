#pragma once


#include <Standard.hpp>

#include <StepAP214_DateItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_DateAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_Date;
class StepBasic_DateRole;
class StepAP214_DateItem;

class StepAP214_AppliedDateAssignment : public StepBasic_DateAssignment
{

public:
  //! Returns a AppliedDateAssignment
  Standard_EXPORT StepAP214_AppliedDateAssignment();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Date>&     aAssignedDate,
                            const occ::handle<StepBasic_DateRole>& aRole,
                            const occ::handle<NCollection_HArray1<StepAP214_DateItem>>& aItems);

  Standard_EXPORT void SetItems(const occ::handle<NCollection_HArray1<StepAP214_DateItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_DateItem>> Items() const;

  Standard_EXPORT StepAP214_DateItem ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedDateAssignment, StepBasic_DateAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_DateItem>> items;
};

