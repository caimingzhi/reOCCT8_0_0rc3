

#include <StepGeom_Hyperbola.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Hyperbola, StepGeom_Conic)

StepGeom_Hyperbola::StepGeom_Hyperbola() = default;

void StepGeom_Hyperbola::Init(const occ::handle<TCollection_HAsciiString>& aName,
                              const StepGeom_Axis2Placement&               aPosition,
                              const double                                 aSemiAxis,
                              const double                                 aSemiImagAxis)
{

  semiAxis     = aSemiAxis;
  semiImagAxis = aSemiImagAxis;

  StepGeom_Conic::Init(aName, aPosition);
}

void StepGeom_Hyperbola::SetSemiAxis(const double aSemiAxis)
{
  semiAxis = aSemiAxis;
}

double StepGeom_Hyperbola::SemiAxis() const
{
  return semiAxis;
}

void StepGeom_Hyperbola::SetSemiImagAxis(const double aSemiImagAxis)
{
  semiImagAxis = aSemiImagAxis;
}

double StepGeom_Hyperbola::SemiImagAxis() const
{
  return semiImagAxis;
}
