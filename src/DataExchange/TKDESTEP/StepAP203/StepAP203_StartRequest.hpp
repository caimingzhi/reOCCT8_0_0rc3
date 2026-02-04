#pragma once


#include <Standard.hpp>

#include <StepAP203_StartRequestItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ActionRequestAssignment.hpp>
class StepBasic_VersionedActionRequest;

//! Representation of STEP entity StartRequest
class StepAP203_StartRequest : public StepBasic_ActionRequestAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP203_StartRequest();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<StepBasic_VersionedActionRequest>&
      aActionRequestAssignment_AssignedActionRequest,
    const occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>> Items() const;

  //! Set field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP203_StartRequest, StepBasic_ActionRequestAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP203_StartRequestItem>> theItems;
};

