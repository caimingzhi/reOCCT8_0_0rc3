

#include <Standard_Type.hpp>
#include <StepGeom_BezierCurve.hpp>
#include <StepGeom_BezierCurveAndRationalBSplineCurve.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_BezierCurveAndRationalBSplineCurve, StepGeom_BSplineCurve)

StepGeom_BezierCurveAndRationalBSplineCurve::StepGeom_BezierCurveAndRationalBSplineCurve() =
  default;

void StepGeom_BezierCurveAndRationalBSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_BezierCurve>&                                      aBezierCurve,
  const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve)
{

  bezierCurve          = aBezierCurve;
  rationalBSplineCurve = aRationalBSplineCurve;

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);
}

void StepGeom_BezierCurveAndRationalBSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<NCollection_HArray1<double>>&                               aWeightsData)
{

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);

  bezierCurve = new StepGeom_BezierCurve();
  bezierCurve->Init(aName, aDegree, aControlPointsList, aCurveForm, aClosedCurve, aSelfIntersect);

  rationalBSplineCurve = new StepGeom_RationalBSplineCurve();
  rationalBSplineCurve->Init(aName,
                             aDegree,
                             aControlPointsList,
                             aCurveForm,
                             aClosedCurve,
                             aSelfIntersect,
                             aWeightsData);
}

void StepGeom_BezierCurveAndRationalBSplineCurve::SetBezierCurve(
  const occ::handle<StepGeom_BezierCurve>& aBezierCurve)
{
  bezierCurve = aBezierCurve;
}

occ::handle<StepGeom_BezierCurve> StepGeom_BezierCurveAndRationalBSplineCurve::BezierCurve() const
{
  return bezierCurve;
}

void StepGeom_BezierCurveAndRationalBSplineCurve::SetRationalBSplineCurve(
  const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve)
{
  rationalBSplineCurve = aRationalBSplineCurve;
}

occ::handle<StepGeom_RationalBSplineCurve> StepGeom_BezierCurveAndRationalBSplineCurve::
  RationalBSplineCurve() const
{
  return rationalBSplineCurve;
}

void StepGeom_BezierCurveAndRationalBSplineCurve::SetWeightsData(
  const occ::handle<NCollection_HArray1<double>>& aWeightsData)
{
  rationalBSplineCurve->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray1<double>> StepGeom_BezierCurveAndRationalBSplineCurve::WeightsData()
  const
{
  return rationalBSplineCurve->WeightsData();
}

double StepGeom_BezierCurveAndRationalBSplineCurve::WeightsDataValue(const int num) const
{
  return rationalBSplineCurve->WeightsDataValue(num);
}

int StepGeom_BezierCurveAndRationalBSplineCurve::NbWeightsData() const
{
  return rationalBSplineCurve->NbWeightsData();
}
