#pragma once

#include <Standard.hpp>

#include <StepAP203_WorkItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ActionAssignment.hpp>
class StepBasic_Action;

//! Representation of STEP entity StartWork
class StepAP203_StartWork : public StepBasic_ActionAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP203_StartWork();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_Action>& aActionAssignment_AssignedAction,
                            const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_WorkItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(const occ::handle<NCollection_HArray1<StepAP203_WorkItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_StartWork, StepBasic_ActionAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_WorkItem>> theItems;
};
