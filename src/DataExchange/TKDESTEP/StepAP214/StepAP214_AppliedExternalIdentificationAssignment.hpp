#pragma once


#include <Standard.hpp>

#include <StepAP214_ExternalIdentificationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ExternalIdentificationAssignment.hpp>
class TCollection_HAsciiString;
class StepBasic_IdentificationRole;
class StepBasic_ExternalSource;

//! Representation of STEP entity AppliedExternalIdentificationAssignment
class StepAP214_AppliedExternalIdentificationAssignment
    : public StepBasic_ExternalIdentificationAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP214_AppliedExternalIdentificationAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     aIdentificationAssignment_AssignedId,
    const occ::handle<StepBasic_IdentificationRole>& aIdentificationAssignment_Role,
    const occ::handle<StepBasic_ExternalSource>&     aExternalIdentificationAssignment_Source,
    const occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>>& aItems);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>> Items()
    const;

  //! Set field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedExternalIdentificationAssignment,
                          StepBasic_ExternalIdentificationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>> theItems;
};

