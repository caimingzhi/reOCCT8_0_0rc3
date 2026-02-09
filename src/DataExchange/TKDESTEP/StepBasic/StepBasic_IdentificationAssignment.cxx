#include <StepBasic_IdentificationAssignment.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_IdentificationAssignment, Standard_Transient)

StepBasic_IdentificationAssignment::StepBasic_IdentificationAssignment() = default;

void StepBasic_IdentificationAssignment::Init(
  const occ::handle<TCollection_HAsciiString>&     aAssignedId,
  const occ::handle<StepBasic_IdentificationRole>& aRole)
{

  theAssignedId = aAssignedId;

  theRole = aRole;
}

occ::handle<TCollection_HAsciiString> StepBasic_IdentificationAssignment::AssignedId() const
{
  return theAssignedId;
}

void StepBasic_IdentificationAssignment::SetAssignedId(
  const occ::handle<TCollection_HAsciiString>& aAssignedId)
{
  theAssignedId = aAssignedId;
}

occ::handle<StepBasic_IdentificationRole> StepBasic_IdentificationAssignment::Role() const
{
  return theRole;
}

void StepBasic_IdentificationAssignment::SetRole(
  const occ::handle<StepBasic_IdentificationRole>& aRole)
{
  theRole = aRole;
}
