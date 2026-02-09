#pragma once

#include <Standard.hpp>

#include <StepAP203_ChangeRequestItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ActionRequestAssignment.hpp>
class StepBasic_VersionedActionRequest;

class StepAP203_ChangeRequest : public StepBasic_ActionRequestAssignment
{

public:
  Standard_EXPORT StepAP203_ChangeRequest();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_VersionedActionRequest>&
      aActionRequestAssignment_AssignedActionRequest,
    const occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>> Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_ChangeRequest, StepBasic_ActionRequestAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_ChangeRequestItem>> theItems;
};
