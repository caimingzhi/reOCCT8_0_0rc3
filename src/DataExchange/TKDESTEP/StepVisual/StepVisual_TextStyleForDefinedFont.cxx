

#include <Standard_Type.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_TextStyleForDefinedFont.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TextStyleForDefinedFont, Standard_Transient)

StepVisual_TextStyleForDefinedFont::StepVisual_TextStyleForDefinedFont() = default;

void StepVisual_TextStyleForDefinedFont::Init(const occ::handle<StepVisual_Colour>& aTextColour)
{

  textColour = aTextColour;
}

void StepVisual_TextStyleForDefinedFont::SetTextColour(
  const occ::handle<StepVisual_Colour>& aTextColour)
{
  textColour = aTextColour;
}

occ::handle<StepVisual_Colour> StepVisual_TextStyleForDefinedFont::TextColour() const
{
  return textColour;
}
