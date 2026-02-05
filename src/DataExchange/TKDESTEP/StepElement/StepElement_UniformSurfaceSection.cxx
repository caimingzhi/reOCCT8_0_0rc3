#include <StepElement_UniformSurfaceSection.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_UniformSurfaceSection, StepElement_SurfaceSection)

//=================================================================================================

StepElement_UniformSurfaceSection::StepElement_UniformSurfaceSection() = default;

//=================================================================================================

void StepElement_UniformSurfaceSection::Init(
  const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_Offset,
  const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_NonStructuralMass,
  const StepElement_MeasureOrUnspecifiedValue& aSurfaceSection_NonStructuralMassOffset,
  const double                                 aThickness,
  const StepElement_MeasureOrUnspecifiedValue& aBendingThickness,
  const StepElement_MeasureOrUnspecifiedValue& aShearThickness)
{
  StepElement_SurfaceSection::Init(aSurfaceSection_Offset,
                                   aSurfaceSection_NonStructuralMass,
                                   aSurfaceSection_NonStructuralMassOffset);

  theThickness = aThickness;

  theBendingThickness = aBendingThickness;

  theShearThickness = aShearThickness;
}

//=================================================================================================

double StepElement_UniformSurfaceSection::Thickness() const
{
  return theThickness;
}

//=================================================================================================

void StepElement_UniformSurfaceSection::SetThickness(const double aThickness)
{
  theThickness = aThickness;
}

//=================================================================================================

StepElement_MeasureOrUnspecifiedValue StepElement_UniformSurfaceSection::BendingThickness() const
{
  return theBendingThickness;
}

//=================================================================================================

void StepElement_UniformSurfaceSection::SetBendingThickness(
  const StepElement_MeasureOrUnspecifiedValue& aBendingThickness)
{
  theBendingThickness = aBendingThickness;
}

//=================================================================================================

StepElement_MeasureOrUnspecifiedValue StepElement_UniformSurfaceSection::ShearThickness() const
{
  return theShearThickness;
}

//=================================================================================================

void StepElement_UniformSurfaceSection::SetShearThickness(
  const StepElement_MeasureOrUnspecifiedValue& aShearThickness)
{
  theShearThickness = aShearThickness;
}
