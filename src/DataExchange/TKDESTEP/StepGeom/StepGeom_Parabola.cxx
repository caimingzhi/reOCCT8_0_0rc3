

#include <StepGeom_Parabola.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Parabola, StepGeom_Conic)

StepGeom_Parabola::StepGeom_Parabola() = default;

void StepGeom_Parabola::Init(const occ::handle<TCollection_HAsciiString>& aName,
                             const StepGeom_Axis2Placement&               aPosition,
                             const double                                 aFocalDist)
{

  focalDist = aFocalDist;

  StepGeom_Conic::Init(aName, aPosition);
}

void StepGeom_Parabola::SetFocalDist(const double aFocalDist)
{
  focalDist = aFocalDist;
}

double StepGeom_Parabola::FocalDist() const
{
  return focalDist;
}
