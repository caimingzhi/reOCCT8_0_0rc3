

#include <Standard_Type.hpp>
#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve,
                           StepGeom_BSplineCurve)

StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::
  StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve() = default;

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_BSplineCurveWithKnots>& aBSplineCurveWithKnots,
  const occ::handle<StepGeom_RationalBSplineCurve>&  aRationalBSplineCurve)
{

  bSplineCurveWithKnots = aBSplineCurveWithKnots;
  rationalBSplineCurve  = aRationalBSplineCurve;

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);
}

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<NCollection_HArray1<int>>&                                  aKnotMultiplicities,
  const occ::handle<NCollection_HArray1<double>>&                               aKnots,
  const StepGeom_KnotType                                                       aKnotSpec,
  const occ::handle<NCollection_HArray1<double>>&                               aWeightsData)
{

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);

  bSplineCurveWithKnots = new StepGeom_BSplineCurveWithKnots();
  bSplineCurveWithKnots->Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect,
                              aKnotMultiplicities,
                              aKnots,
                              aKnotSpec);

  rationalBSplineCurve = new StepGeom_RationalBSplineCurve();
  rationalBSplineCurve->Init(aName,
                             aDegree,
                             aControlPointsList,
                             aCurveForm,
                             aClosedCurve,
                             aSelfIntersect,
                             aWeightsData);
}

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::SetBSplineCurveWithKnots(
  const occ::handle<StepGeom_BSplineCurveWithKnots>& aBSplineCurveWithKnots)
{
  bSplineCurveWithKnots = aBSplineCurveWithKnots;
}

occ::handle<StepGeom_BSplineCurveWithKnots> StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::
  BSplineCurveWithKnots() const
{
  return bSplineCurveWithKnots;
}

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::SetRationalBSplineCurve(
  const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve)
{
  rationalBSplineCurve = aRationalBSplineCurve;
}

occ::handle<StepGeom_RationalBSplineCurve> StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::
  RationalBSplineCurve() const
{
  return rationalBSplineCurve;
}

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::SetKnotMultiplicities(
  const occ::handle<NCollection_HArray1<int>>& aKnotMultiplicities)
{
  bSplineCurveWithKnots->SetKnotMultiplicities(aKnotMultiplicities);
}

occ::handle<NCollection_HArray1<int>> StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::
  KnotMultiplicities() const
{
  return bSplineCurveWithKnots->KnotMultiplicities();
}

int StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::KnotMultiplicitiesValue(
  const int num) const
{
  return bSplineCurveWithKnots->KnotMultiplicitiesValue(num);
}

int StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::NbKnotMultiplicities() const
{
  return bSplineCurveWithKnots->NbKnotMultiplicities();
}

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::SetKnots(
  const occ::handle<NCollection_HArray1<double>>& aKnots)
{
  bSplineCurveWithKnots->SetKnots(aKnots);
}

occ::handle<NCollection_HArray1<double>> StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::
  Knots() const
{
  return bSplineCurveWithKnots->Knots();
}

double StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::KnotsValue(const int num) const
{
  return bSplineCurveWithKnots->KnotsValue(num);
}

int StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::NbKnots() const
{
  return bSplineCurveWithKnots->NbKnots();
}

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::SetKnotSpec(
  const StepGeom_KnotType aKnotSpec)
{
  bSplineCurveWithKnots->SetKnotSpec(aKnotSpec);
}

StepGeom_KnotType StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::KnotSpec() const
{
  return bSplineCurveWithKnots->KnotSpec();
}

void StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::SetWeightsData(
  const occ::handle<NCollection_HArray1<double>>& aWeightsData)
{
  rationalBSplineCurve->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray1<double>> StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::
  WeightsData() const
{
  return rationalBSplineCurve->WeightsData();
}

double StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::WeightsDataValue(const int num) const
{
  return rationalBSplineCurve->WeightsDataValue(num);
}

int StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve::NbWeightsData() const
{
  return rationalBSplineCurve->NbWeightsData();
}
