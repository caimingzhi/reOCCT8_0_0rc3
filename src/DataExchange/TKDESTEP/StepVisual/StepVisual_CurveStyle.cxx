

#include <StepVisual_Colour.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_CurveStyleFontSelect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CurveStyle, Standard_Transient)

StepVisual_CurveStyle::StepVisual_CurveStyle() = default;

void StepVisual_CurveStyle::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                 const StepVisual_CurveStyleFontSelect&       aCurveFont,
                                 const StepBasic_SizeSelect&                  aCurveWidth,
                                 const occ::handle<StepVisual_Colour>&        aCurveColour)
{

  name        = aName;
  curveFont   = aCurveFont;
  curveWidth  = aCurveWidth;
  curveColour = aCurveColour;
}

void StepVisual_CurveStyle::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_CurveStyle::Name() const
{
  return name;
}

void StepVisual_CurveStyle::SetCurveFont(const StepVisual_CurveStyleFontSelect& aCurveFont)
{
  curveFont = aCurveFont;
}

StepVisual_CurveStyleFontSelect StepVisual_CurveStyle::CurveFont() const
{
  return curveFont;
}

void StepVisual_CurveStyle::SetCurveWidth(const StepBasic_SizeSelect& aCurveWidth)
{
  curveWidth = aCurveWidth;
}

StepBasic_SizeSelect StepVisual_CurveStyle::CurveWidth() const
{
  return curveWidth;
}

void StepVisual_CurveStyle::SetCurveColour(const occ::handle<StepVisual_Colour>& aCurveColour)
{
  curveColour = aCurveColour;
}

occ::handle<StepVisual_Colour> StepVisual_CurveStyle::CurveColour() const
{
  return curveColour;
}
