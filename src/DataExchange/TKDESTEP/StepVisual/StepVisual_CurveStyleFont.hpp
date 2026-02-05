#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepVisual_CurveStyleFontPattern.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepVisual_CurveStyleFontPattern;

class StepVisual_CurveStyleFont : public Standard_Transient
{

public:
  //! Returns a CurveStyleFont
  Standard_EXPORT StepVisual_CurveStyleFont();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>>&
      aPatternList);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetPatternList(
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>>&
      aPatternList);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>>
                  PatternList() const;

  Standard_EXPORT occ::handle<StepVisual_CurveStyleFontPattern> PatternListValue(
    const int num) const;

  Standard_EXPORT int NbPatternList() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CurveStyleFont, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                                           name;
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>> patternList;
};
