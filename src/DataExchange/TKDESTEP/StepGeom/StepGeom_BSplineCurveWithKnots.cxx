

#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_BSplineCurveWithKnots, StepGeom_BSplineCurve)

StepGeom_BSplineCurveWithKnots::StepGeom_BSplineCurveWithKnots() = default;

void StepGeom_BSplineCurveWithKnots::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<NCollection_HArray1<int>>&                                  aKnotMultiplicities,
  const occ::handle<NCollection_HArray1<double>>&                               aKnots,
  const StepGeom_KnotType                                                       aKnotSpec)
{

  knotMultiplicities = aKnotMultiplicities;
  knots              = aKnots;
  knotSpec           = aKnotSpec;

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);
}

void StepGeom_BSplineCurveWithKnots::SetKnotMultiplicities(
  const occ::handle<NCollection_HArray1<int>>& aKnotMultiplicities)
{
  knotMultiplicities = aKnotMultiplicities;
}

occ::handle<NCollection_HArray1<int>> StepGeom_BSplineCurveWithKnots::KnotMultiplicities() const
{
  return knotMultiplicities;
}

int StepGeom_BSplineCurveWithKnots::KnotMultiplicitiesValue(const int num) const
{
  return knotMultiplicities->Value(num);
}

int StepGeom_BSplineCurveWithKnots::NbKnotMultiplicities() const
{
  return knotMultiplicities->Length();
}

void StepGeom_BSplineCurveWithKnots::SetKnots(
  const occ::handle<NCollection_HArray1<double>>& aKnots)
{
  knots = aKnots;
}

occ::handle<NCollection_HArray1<double>> StepGeom_BSplineCurveWithKnots::Knots() const
{
  return knots;
}

double StepGeom_BSplineCurveWithKnots::KnotsValue(const int num) const
{
  return knots->Value(num);
}

int StepGeom_BSplineCurveWithKnots::NbKnots() const
{
  return knots->Length();
}

void StepGeom_BSplineCurveWithKnots::SetKnotSpec(const StepGeom_KnotType aKnotSpec)
{
  knotSpec = aKnotSpec;
}

StepGeom_KnotType StepGeom_BSplineCurveWithKnots::KnotSpec() const
{
  return knotSpec;
}
