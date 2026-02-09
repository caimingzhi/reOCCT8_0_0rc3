

#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_EvaluatedDegeneratePcurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_EvaluatedDegeneratePcurve, StepGeom_DegeneratePcurve)

StepGeom_EvaluatedDegeneratePcurve::StepGeom_EvaluatedDegeneratePcurve() = default;

void StepGeom_EvaluatedDegeneratePcurve::Init(
  const occ::handle<TCollection_HAsciiString>&            aName,
  const occ::handle<StepGeom_Surface>&                    aBasisSurface,
  const occ::handle<StepRepr_DefinitionalRepresentation>& aReferenceToCurve,
  const occ::handle<StepGeom_CartesianPoint>&             aEquivalentPoint)
{

  equivalentPoint = aEquivalentPoint;

  StepGeom_DegeneratePcurve::Init(aName, aBasisSurface, aReferenceToCurve);
}

void StepGeom_EvaluatedDegeneratePcurve::SetEquivalentPoint(
  const occ::handle<StepGeom_CartesianPoint>& aEquivalentPoint)
{
  equivalentPoint = aEquivalentPoint;
}

occ::handle<StepGeom_CartesianPoint> StepGeom_EvaluatedDegeneratePcurve::EquivalentPoint() const
{
  return equivalentPoint;
}
