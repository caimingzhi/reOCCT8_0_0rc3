

#include <StepRepr_MaterialDesignation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_MaterialDesignation, Standard_Transient)

StepRepr_MaterialDesignation::StepRepr_MaterialDesignation() = default;

void StepRepr_MaterialDesignation::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                        const StepRepr_CharacterizedDefinition&      aOfDefinition)
{
  name         = aName;
  ofDefinition = aOfDefinition;
}

void StepRepr_MaterialDesignation::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_MaterialDesignation::Name() const
{
  return name;
}

void StepRepr_MaterialDesignation::SetOfDefinition(
  const StepRepr_CharacterizedDefinition& aOfDefinition)
{
  ofDefinition = aOfDefinition;
}

StepRepr_CharacterizedDefinition StepRepr_MaterialDesignation::OfDefinition() const
{
  return ofDefinition;
}
