#include <StepBasic_Group.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Group, Standard_Transient)

//=================================================================================================

StepBasic_Group::StepBasic_Group()
{
  defDescription = false;
}

//=================================================================================================

void StepBasic_Group::Init(const occ::handle<TCollection_HAsciiString>& aName,
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

occ::handle<TCollection_HAsciiString> StepBasic_Group::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_Group::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_Group::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_Group::SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepBasic_Group::HasDescription() const
{
  return defDescription;
}
