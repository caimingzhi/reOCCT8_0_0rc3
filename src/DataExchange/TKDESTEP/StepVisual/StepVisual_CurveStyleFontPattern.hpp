#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class StepVisual_CurveStyleFontPattern : public Standard_Transient
{

public:
  //! Returns a CurveStyleFontPattern
  Standard_EXPORT StepVisual_CurveStyleFontPattern();

  Standard_EXPORT void Init(const double aVisibleSegmentLength,
                            const double aInvisibleSegmentLength);

  Standard_EXPORT void SetVisibleSegmentLength(const double aVisibleSegmentLength);

  Standard_EXPORT double VisibleSegmentLength() const;

  Standard_EXPORT void SetInvisibleSegmentLength(const double aInvisibleSegmentLength);

  Standard_EXPORT double InvisibleSegmentLength() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CurveStyleFontPattern, Standard_Transient)

private:
  double visibleSegmentLength;
  double invisibleSegmentLength;
};

