#include <StepAP214_AppliedExternalIdentificationAssignment.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AppliedExternalIdentificationAssignment,
                           StepBasic_ExternalIdentificationAssignment)

//=================================================================================================

StepAP214_AppliedExternalIdentificationAssignment::
  StepAP214_AppliedExternalIdentificationAssignment() = default;

//=================================================================================================

void StepAP214_AppliedExternalIdentificationAssignment::Init(
  const occ::handle<TCollection_HAsciiString>&     aIdentificationAssignment_AssignedId,
  const occ::handle<StepBasic_IdentificationRole>& aIdentificationAssignment_Role,
  const occ::handle<StepBasic_ExternalSource>&     aExternalIdentificationAssignment_Source,
  const occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>>& aItems)
{
  StepBasic_ExternalIdentificationAssignment::Init(aIdentificationAssignment_AssignedId,
                                                   aIdentificationAssignment_Role,
                                                   aExternalIdentificationAssignment_Source);

  theItems = aItems;
}

//=================================================================================================

occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>>
  StepAP214_AppliedExternalIdentificationAssignment::Items() const
{
  return theItems;
}

//=================================================================================================

void StepAP214_AppliedExternalIdentificationAssignment::SetItems(
  const occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>>& aItems)
{
  theItems = aItems;
}
