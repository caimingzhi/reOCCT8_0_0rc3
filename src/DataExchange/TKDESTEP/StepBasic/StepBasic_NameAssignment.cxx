#include <StepBasic_NameAssignment.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_NameAssignment, Standard_Transient)

//=================================================================================================

StepBasic_NameAssignment::StepBasic_NameAssignment() = default;

//=================================================================================================

void StepBasic_NameAssignment::Init(const occ::handle<TCollection_HAsciiString>& aAssignedName)
{

  theAssignedName = aAssignedName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_NameAssignment::AssignedName() const
{
  return theAssignedName;
}

//=================================================================================================

void StepBasic_NameAssignment::SetAssignedName(
  const occ::handle<TCollection_HAsciiString>& aAssignedName)
{
  theAssignedName = aAssignedName;
}
