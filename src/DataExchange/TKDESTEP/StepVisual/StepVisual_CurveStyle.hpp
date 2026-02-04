#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_CurveStyleFontSelect.hpp>
#include <StepBasic_SizeSelect.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepVisual_Colour;

class StepVisual_CurveStyle : public Standard_Transient
{

public:
  //! Returns a CurveStyle
  Standard_EXPORT StepVisual_CurveStyle();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepVisual_CurveStyleFontSelect&       aCurveFont,
                            const StepBasic_SizeSelect&                  aCurveWidth,
                            const occ::handle<StepVisual_Colour>&        aCurveColour);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetCurveFont(const StepVisual_CurveStyleFontSelect& aCurveFont);

  Standard_EXPORT StepVisual_CurveStyleFontSelect CurveFont() const;

  Standard_EXPORT void SetCurveWidth(const StepBasic_SizeSelect& aCurveWidth);

  Standard_EXPORT StepBasic_SizeSelect CurveWidth() const;

  Standard_EXPORT void SetCurveColour(const occ::handle<StepVisual_Colour>& aCurveColour);

  Standard_EXPORT occ::handle<StepVisual_Colour> CurveColour() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CurveStyle, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
  StepVisual_CurveStyleFontSelect       curveFont;
  StepBasic_SizeSelect                  curveWidth;
  occ::handle<StepVisual_Colour>        curveColour;
};

