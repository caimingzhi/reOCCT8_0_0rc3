#pragma once

#include <Standard.hpp>

#include <StepAP214_ExternalIdentificationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ExternalIdentificationAssignment.hpp>
class TCollection_HAsciiString;
class StepBasic_IdentificationRole;
class StepBasic_ExternalSource;

class StepAP214_AppliedExternalIdentificationAssignment
    : public StepBasic_ExternalIdentificationAssignment
{

public:
  Standard_EXPORT StepAP214_AppliedExternalIdentificationAssignment();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     aIdentificationAssignment_AssignedId,
    const occ::handle<StepBasic_IdentificationRole>& aIdentificationAssignment_Role,
    const occ::handle<StepBasic_ExternalSource>&     aExternalIdentificationAssignment_Source,
    const occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>> Items()
    const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>>& Items);

  DEFINE_STANDARD_RTTIEXT(StepAP214_AppliedExternalIdentificationAssignment,
                          StepBasic_ExternalIdentificationAssignment)

private:
  occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>> theItems;
};
