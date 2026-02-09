#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <StepElement_SurfaceSection.hpp>

class StepElement_UniformSurfaceSection : public StepElement_SurfaceSection
{

public:
  Standard_EXPORT StepElement_UniformSurfaceSection();

  Standard_EXPORT void Init(
    const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_Offset,
    const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_NonStructuralMass,
    const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_NonStructuralMassOffset,
    const double                                 aThickness,
    const StepElement_MeasureOrUnspecifiedValue& aBendingThickness,
    const StepElement_MeasureOrUnspecifiedValue& aShearThickness);

  Standard_EXPORT double Thickness() const;

  Standard_EXPORT void SetThickness(const double Thickness);

  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue BendingThickness() const;

  Standard_EXPORT void SetBendingThickness(
    const StepElement_MeasureOrUnspecifiedValue& BendingThickness);

  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue ShearThickness() const;

  Standard_EXPORT void SetShearThickness(
    const StepElement_MeasureOrUnspecifiedValue& ShearThickness);

  DEFINE_STANDARD_RTTIEXT(StepElement_UniformSurfaceSection, StepElement_SurfaceSection)

private:
  double                                theThickness;
  StepElement_MeasureOrUnspecifiedValue theBendingThickness;
  StepElement_MeasureOrUnspecifiedValue theShearThickness;
};
