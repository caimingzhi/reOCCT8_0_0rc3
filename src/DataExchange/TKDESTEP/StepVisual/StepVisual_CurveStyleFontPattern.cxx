

#include <Standard_Type.hpp>
#include <StepVisual_CurveStyleFontPattern.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CurveStyleFontPattern, Standard_Transient)

StepVisual_CurveStyleFontPattern::StepVisual_CurveStyleFontPattern() = default;

void StepVisual_CurveStyleFontPattern::Init(const double aVisibleSegmentLength,
                                            const double aInvisibleSegmentLength)
{

  visibleSegmentLength   = aVisibleSegmentLength;
  invisibleSegmentLength = aInvisibleSegmentLength;
}

void StepVisual_CurveStyleFontPattern::SetVisibleSegmentLength(const double aVisibleSegmentLength)
{
  visibleSegmentLength = aVisibleSegmentLength;
}

double StepVisual_CurveStyleFontPattern::VisibleSegmentLength() const
{
  return visibleSegmentLength;
}

void StepVisual_CurveStyleFontPattern::SetInvisibleSegmentLength(
  const double aInvisibleSegmentLength)
{
  invisibleSegmentLength = aInvisibleSegmentLength;
}

double StepVisual_CurveStyleFontPattern::InvisibleSegmentLength() const
{
  return invisibleSegmentLength;
}
