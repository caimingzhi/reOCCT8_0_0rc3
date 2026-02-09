

#include <StepVisual_TextStyle.hpp>
#include <StepVisual_TextStyleForDefinedFont.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TextStyle, Standard_Transient)

StepVisual_TextStyle::StepVisual_TextStyle() = default;

void StepVisual_TextStyle::Init(
  const occ::handle<TCollection_HAsciiString>&           aName,
  const occ::handle<StepVisual_TextStyleForDefinedFont>& aCharacterAppearance)
{

  name                = aName;
  characterAppearance = aCharacterAppearance;
}

void StepVisual_TextStyle::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_TextStyle::Name() const
{
  return name;
}

void StepVisual_TextStyle::SetCharacterAppearance(
  const occ::handle<StepVisual_TextStyleForDefinedFont>& aCharacterAppearance)
{
  characterAppearance = aCharacterAppearance;
}

occ::handle<StepVisual_TextStyleForDefinedFont> StepVisual_TextStyle::CharacterAppearance() const
{
  return characterAppearance;
}
