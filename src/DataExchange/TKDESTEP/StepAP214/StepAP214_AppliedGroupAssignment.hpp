#pragma once


#include <Standard.hpp>

#include <StepAP214_GroupItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_GroupAssignment.hpp>
class StepBasic_Group;

//! Representation of STEP entity AppliedGroupAssignment
class StepAP214_AppliedGroupAssignment : public StepBasic_GroupAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP214_AppliedGroupAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_Group>& aGroupAssignment_AssignedGroup,
                            const occ::handle<NCollection_HArray1<StepAP214_GroupItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_GroupItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(const occ::handle<NCollection_HArray1<StepAP214_GroupItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedGroupAssignment, StepBasic_GroupAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_GroupItem>> theItems;
};

