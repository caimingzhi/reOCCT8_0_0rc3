

#include <Standard_Type.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <StepGeom_UniformCurve.hpp>
#include <StepGeom_UniformCurveAndRationalBSplineCurve.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_UniformCurveAndRationalBSplineCurve, StepGeom_BSplineCurve)

StepGeom_UniformCurveAndRationalBSplineCurve::StepGeom_UniformCurveAndRationalBSplineCurve() =
  default;

void StepGeom_UniformCurveAndRationalBSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_UniformCurve>&                                     aUniformCurve,
  const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve)
{

  uniformCurve         = aUniformCurve;
  rationalBSplineCurve = aRationalBSplineCurve;

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);
}

void StepGeom_UniformCurveAndRationalBSplineCurve::Init(
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

  rationalBSplineCurve = new StepGeom_RationalBSplineCurve();
  rationalBSplineCurve->Init(aName,
                             aDegree,
                             aControlPointsList,
                             aCurveForm,
                             aClosedCurve,
                             aSelfIntersect,
                             aWeightsData);

  uniformCurve = new StepGeom_UniformCurve();
  uniformCurve->Init(aName, aDegree, aControlPointsList, aCurveForm, aClosedCurve, aSelfIntersect);
}

void StepGeom_UniformCurveAndRationalBSplineCurve::SetUniformCurve(
  const occ::handle<StepGeom_UniformCurve>& aUniformCurve)
{
  uniformCurve = aUniformCurve;
}

occ::handle<StepGeom_UniformCurve> StepGeom_UniformCurveAndRationalBSplineCurve::UniformCurve()
  const
{
  return uniformCurve;
}

void StepGeom_UniformCurveAndRationalBSplineCurve::SetRationalBSplineCurve(
  const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve)
{
  rationalBSplineCurve = aRationalBSplineCurve;
}

occ::handle<StepGeom_RationalBSplineCurve> StepGeom_UniformCurveAndRationalBSplineCurve::
  RationalBSplineCurve() const
{
  return rationalBSplineCurve;
}

void StepGeom_UniformCurveAndRationalBSplineCurve::SetWeightsData(
  const occ::handle<NCollection_HArray1<double>>& aWeightsData)
{
  rationalBSplineCurve->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray1<double>> StepGeom_UniformCurveAndRationalBSplineCurve::WeightsData()
  const
{
  return rationalBSplineCurve->WeightsData();
}

double StepGeom_UniformCurveAndRationalBSplineCurve::WeightsDataValue(const int num) const
{
  return rationalBSplineCurve->WeightsDataValue(num);
}

int StepGeom_UniformCurveAndRationalBSplineCurve::NbWeightsData() const
{
  return rationalBSplineCurve->NbWeightsData();
}
