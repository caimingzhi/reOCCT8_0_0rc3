

#include <StepVisual_CurveStyleFont.hpp>
#include <StepVisual_CurveStyleFontPattern.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CurveStyleFont, Standard_Transient)

StepVisual_CurveStyleFont::StepVisual_CurveStyleFont() = default;

void StepVisual_CurveStyleFont::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>>&
    aPatternList)
{

  name        = aName;
  patternList = aPatternList;
}

void StepVisual_CurveStyleFont::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepVisual_CurveStyleFont::Name() const
{
  return name;
}

void StepVisual_CurveStyleFont::SetPatternList(
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>>&
    aPatternList)
{
  patternList = aPatternList;
}

occ::handle<NCollection_HArray1<occ::handle<StepVisual_CurveStyleFontPattern>>>
  StepVisual_CurveStyleFont::PatternList() const
{
  return patternList;
}

occ::handle<StepVisual_CurveStyleFontPattern> StepVisual_CurveStyleFont::PatternListValue(
  const int num) const
{
  return patternList->Value(num);
}

int StepVisual_CurveStyleFont::NbPatternList() const
{
  if (patternList.IsNull())
    return 0;
  return patternList->Length();
}
