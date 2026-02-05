#include <StepBasic_CharacterizedObject.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_CharacterizedObject, Standard_Transient)

//=================================================================================================

StepBasic_CharacterizedObject::StepBasic_CharacterizedObject()
{
  defDescription = false;
}

//=================================================================================================

void StepBasic_CharacterizedObject::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                         const bool hasDescription,
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

occ::handle<TCollection_HAsciiString> StepBasic_CharacterizedObject::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_CharacterizedObject::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_CharacterizedObject::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_CharacterizedObject::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepBasic_CharacterizedObject::HasDescription() const
{
  return defDescription;
}
