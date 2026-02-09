

#include <Standard_Type.hpp>
#include <StepGeom_QuasiUniformCurve.hpp>
#include <StepGeom_QuasiUniformCurveAndRationalBSplineCurve.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_QuasiUniformCurveAndRationalBSplineCurve, StepGeom_BSplineCurve)

StepGeom_QuasiUniformCurveAndRationalBSplineCurve::
  StepGeom_QuasiUniformCurveAndRationalBSplineCurve() = default;

void StepGeom_QuasiUniformCurveAndRationalBSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_QuasiUniformCurve>&                                aQuasiUniformCurve,
  const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve)
{

  quasiUniformCurve    = aQuasiUniformCurve;
  rationalBSplineCurve = aRationalBSplineCurve;

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);
}

void StepGeom_QuasiUniformCurveAndRationalBSplineCurve::Init(
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

  quasiUniformCurve = new StepGeom_QuasiUniformCurve();
  quasiUniformCurve
    ->Init(aName, aDegree, aControlPointsList, aCurveForm, aClosedCurve, aSelfIntersect);

  rationalBSplineCurve = new StepGeom_RationalBSplineCurve();
  rationalBSplineCurve->Init(aName,
                             aDegree,
                             aControlPointsList,
                             aCurveForm,
                             aClosedCurve,
                             aSelfIntersect,
                             aWeightsData);
}

void StepGeom_QuasiUniformCurveAndRationalBSplineCurve::SetQuasiUniformCurve(
  const occ::handle<StepGeom_QuasiUniformCurve>& aQuasiUniformCurve)
{
  quasiUniformCurve = aQuasiUniformCurve;
}

occ::handle<StepGeom_QuasiUniformCurve> StepGeom_QuasiUniformCurveAndRationalBSplineCurve::
  QuasiUniformCurve() const
{
  return quasiUniformCurve;
}

void StepGeom_QuasiUniformCurveAndRationalBSplineCurve::SetRationalBSplineCurve(
  const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve)
{
  rationalBSplineCurve = aRationalBSplineCurve;
}

occ::handle<StepGeom_RationalBSplineCurve> StepGeom_QuasiUniformCurveAndRationalBSplineCurve::
  RationalBSplineCurve() const
{
  return rationalBSplineCurve;
}

void StepGeom_QuasiUniformCurveAndRationalBSplineCurve::SetWeightsData(
  const occ::handle<NCollection_HArray1<double>>& aWeightsData)
{
  rationalBSplineCurve->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray1<double>> StepGeom_QuasiUniformCurveAndRationalBSplineCurve::
  WeightsData() const
{
  return rationalBSplineCurve->WeightsData();
}

double StepGeom_QuasiUniformCurveAndRationalBSplineCurve::WeightsDataValue(const int num) const
{
  return rationalBSplineCurve->WeightsDataValue(num);
}

int StepGeom_QuasiUniformCurveAndRationalBSplineCurve::NbWeightsData() const
{
  return rationalBSplineCurve->NbWeightsData();
}
