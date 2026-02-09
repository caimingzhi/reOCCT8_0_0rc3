#pragma once

#include <Standard.hpp>

#include <StepAP203_WorkItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ActionAssignment.hpp>
class StepBasic_Action;

class StepAP203_Change : public StepBasic_ActionAssignment
{

public:
  Standard_EXPORT StepAP203_Change();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Action>& aActionAssignment_AssignedAction,
                            const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_WorkItem>> Items() const;

  Standard_EXPORT void SetItems(const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_Change, StepBasic_ActionAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_WorkItem>> theItems;
};
