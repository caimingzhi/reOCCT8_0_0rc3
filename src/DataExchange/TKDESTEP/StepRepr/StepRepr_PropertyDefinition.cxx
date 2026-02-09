#include <StepRepr_PropertyDefinition.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_PropertyDefinition, Standard_Transient)

StepRepr_PropertyDefinition::StepRepr_PropertyDefinition()
{
  defDescription = false;
}

void StepRepr_PropertyDefinition::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const bool                                   hasDescription,
                                       const occ::handle<TCollection_HAsciiString>& aDescription,
                                       const StepRepr_CharacterizedDefinition&      aDefinition)
{

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theDefinition = aDefinition;
}

occ::handle<TCollection_HAsciiString> StepRepr_PropertyDefinition::Name() const
{
  return theName;
}

void StepRepr_PropertyDefinition::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_PropertyDefinition::Description() const
{
  return theDescription;
}

void StepRepr_PropertyDefinition::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

bool StepRepr_PropertyDefinition::HasDescription() const
{
  return defDescription;
}

StepRepr_CharacterizedDefinition StepRepr_PropertyDefinition::Definition() const
{
  return theDefinition;
}

void StepRepr_PropertyDefinition::SetDefinition(const StepRepr_CharacterizedDefinition& aDefinition)
{
  theDefinition = aDefinition;
}
