#include <StepBasic_ExternalIdentificationAssignment.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ExternalIdentificationAssignment,
                           StepBasic_IdentificationAssignment)

//=================================================================================================

StepBasic_ExternalIdentificationAssignment::StepBasic_ExternalIdentificationAssignment() = default;

//=================================================================================================

void StepBasic_ExternalIdentificationAssignment::Init(
  const occ::handle<TCollection_HAsciiString>&     aIdentificationAssignment_AssignedId,
  const occ::handle<StepBasic_IdentificationRole>& aIdentificationAssignment_Role,
  const occ::handle<StepBasic_ExternalSource>&     aSource)
{
  StepBasic_IdentificationAssignment::Init(aIdentificationAssignment_AssignedId,
                                           aIdentificationAssignment_Role);

  theSource = aSource;
}

//=================================================================================================

occ::handle<StepBasic_ExternalSource> StepBasic_ExternalIdentificationAssignment::Source() const
{
  return theSource;
}

//=================================================================================================

void StepBasic_ExternalIdentificationAssignment::SetSource(
  const occ::handle<StepBasic_ExternalSource>& aSource)
{
  theSource = aSource;
}
