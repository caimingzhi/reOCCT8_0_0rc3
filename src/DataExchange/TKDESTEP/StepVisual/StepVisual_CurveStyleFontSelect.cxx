

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_CurveStyleFont.hpp>
#include <StepVisual_CurveStyleFontSelect.hpp>
#include <StepVisual_ExternallyDefinedCurveFont.hpp>
#include <StepVisual_PreDefinedCurveFont.hpp>

StepVisual_CurveStyleFontSelect::StepVisual_CurveStyleFontSelect() = default;

int StepVisual_CurveStyleFontSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_CurveStyleFont)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PreDefinedCurveFont)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_ExternallyDefinedCurveFont)))
    return 3;
  return 0;
}

occ::handle<StepVisual_CurveStyleFont> StepVisual_CurveStyleFontSelect::CurveStyleFont() const
{
  return GetCasted(StepVisual_CurveStyleFont, Value());
}

occ::handle<StepVisual_PreDefinedCurveFont> StepVisual_CurveStyleFontSelect::PreDefinedCurveFont()
  const
{
  return GetCasted(StepVisual_PreDefinedCurveFont, Value());
}

occ::handle<StepVisual_ExternallyDefinedCurveFont> StepVisual_CurveStyleFontSelect::
  ExternallyDefinedCurveFont() const
{
  return GetCasted(StepVisual_ExternallyDefinedCurveFont, Value());
}
