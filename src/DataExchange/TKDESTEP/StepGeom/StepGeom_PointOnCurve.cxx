

#include <StepGeom_Curve.hpp>
#include <StepGeom_PointOnCurve.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_PointOnCurve, StepGeom_Point)

StepGeom_PointOnCurve::StepGeom_PointOnCurve() = default;

void StepGeom_PointOnCurve::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                 const occ::handle<StepGeom_Curve>&           aBasisCurve,
                                 const double                                 aPointParameter)
{

  basisCurve     = aBasisCurve;
  pointParameter = aPointParameter;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_PointOnCurve::SetBasisCurve(const occ::handle<StepGeom_Curve>& aBasisCurve)
{
  basisCurve = aBasisCurve;
}

occ::handle<StepGeom_Curve> StepGeom_PointOnCurve::BasisCurve() const
{
  return basisCurve;
}

void StepGeom_PointOnCurve::SetPointParameter(const double aPointParameter)
{
  pointParameter = aPointParameter;
}

double StepGeom_PointOnCurve::PointParameter() const
{
  return pointParameter;
}
