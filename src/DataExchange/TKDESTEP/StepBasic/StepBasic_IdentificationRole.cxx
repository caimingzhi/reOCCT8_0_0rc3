#include <StepBasic_IdentificationRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_IdentificationRole, Standard_Transient)

//=================================================================================================

StepBasic_IdentificationRole::StepBasic_IdentificationRole()
{
  defDescription = false;
}

//=================================================================================================

void StepBasic_IdentificationRole::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                        const bool                                   hasDescription,
                                        const occ::handle<TCollection_HAsciiString>& aDescription)
{

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_IdentificationRole::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_IdentificationRole::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_IdentificationRole::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_IdentificationRole::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepBasic_IdentificationRole::HasDescription() const
{
  return defDescription;
}
