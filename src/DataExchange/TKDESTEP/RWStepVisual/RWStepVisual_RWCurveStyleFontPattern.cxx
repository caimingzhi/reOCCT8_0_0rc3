

#include "RWStepVisual_RWCurveStyleFontPattern.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyleFontPattern.hpp>

RWStepVisual_RWCurveStyleFontPattern::RWStepVisual_RWCurveStyleFontPattern() = default;

void RWStepVisual_RWCurveStyleFontPattern::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepVisual_CurveStyleFontPattern>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "curve_style_font_pattern"))
    return;

  double aVisibleSegmentLength;

  data->ReadReal(num, 1, "visible_segment_length", ach, aVisibleSegmentLength);

  double aInvisibleSegmentLength;

  data->ReadReal(num, 2, "invisible_segment_length", ach, aInvisibleSegmentLength);

  ent->Init(aVisibleSegmentLength, aInvisibleSegmentLength);
}

void RWStepVisual_RWCurveStyleFontPattern::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepVisual_CurveStyleFontPattern>& ent) const
{

  SW.Send(ent->VisibleSegmentLength());

  SW.Send(ent->InvisibleSegmentLength());
}
