#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_Colour;

class StepVisual_TextStyleForDefinedFont : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_TextStyleForDefinedFont();

  Standard_EXPORT void Init(const occ::handle<StepVisual_Colour>& aTextColour);

  Standard_EXPORT void SetTextColour(const occ::handle<StepVisual_Colour>& aTextColour);

  Standard_EXPORT occ::handle<StepVisual_Colour> TextColour() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TextStyleForDefinedFont, Standard_Transient)

private:
  occ::handle<StepVisual_Colour> textColour;
};
