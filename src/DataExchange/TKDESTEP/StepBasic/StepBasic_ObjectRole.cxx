#include <StepBasic_ObjectRole.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ObjectRole, Standard_Transient)

//=================================================================================================

StepBasic_ObjectRole::StepBasic_ObjectRole()
{
  defDescription = false;
}

//=================================================================================================

void StepBasic_ObjectRole::Init(const occ::handle<TCollection_HAsciiString>& aName,
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

occ::handle<TCollection_HAsciiString> StepBasic_ObjectRole::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_ObjectRole::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ObjectRole::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_ObjectRole::SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepBasic_ObjectRole::HasDescription() const
{
  return defDescription;
}
