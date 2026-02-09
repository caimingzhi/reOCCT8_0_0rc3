

#include <StepVisual_TextLiteral.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TextLiteral, StepGeom_GeometricRepresentationItem)

StepVisual_TextLiteral::StepVisual_TextLiteral() = default;

void StepVisual_TextLiteral::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                  const occ::handle<TCollection_HAsciiString>& aLiteral,
                                  const StepGeom_Axis2Placement&               aPlacement,
                                  const occ::handle<TCollection_HAsciiString>& aAlignment,
                                  const StepVisual_TextPath                    aPath,
                                  const StepVisual_FontSelect&                 aFont)
{

  literal   = aLiteral;
  placement = aPlacement;
  alignment = aAlignment;
  path      = aPath;
  font      = aFont;

  StepRepr_RepresentationItem::Init(aName);
}

void StepVisual_TextLiteral::SetLiteral(const occ::handle<TCollection_HAsciiString>& aLiteral)
{
  literal = aLiteral;
}

occ::handle<TCollection_HAsciiString> StepVisual_TextLiteral::Literal() const
{
  return literal;
}

void StepVisual_TextLiteral::SetPlacement(const StepGeom_Axis2Placement& aPlacement)
{
  placement = aPlacement;
}

StepGeom_Axis2Placement StepVisual_TextLiteral::Placement() const
{
  return placement;
}

void StepVisual_TextLiteral::SetAlignment(const occ::handle<TCollection_HAsciiString>& aAlignment)
{
  alignment = aAlignment;
}

occ::handle<TCollection_HAsciiString> StepVisual_TextLiteral::Alignment() const
{
  return alignment;
}

void StepVisual_TextLiteral::SetPath(const StepVisual_TextPath aPath)
{
  path = aPath;
}

StepVisual_TextPath StepVisual_TextLiteral::Path() const
{
  return path;
}

void StepVisual_TextLiteral::SetFont(const StepVisual_FontSelect& aFont)
{
  font = aFont;
}

StepVisual_FontSelect StepVisual_TextLiteral::Font() const
{
  return font;
}
