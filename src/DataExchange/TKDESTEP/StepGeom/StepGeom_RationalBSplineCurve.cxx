

#include <StepGeom_RationalBSplineCurve.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_RationalBSplineCurve, StepGeom_BSplineCurve)

StepGeom_RationalBSplineCurve::StepGeom_RationalBSplineCurve() = default;

void StepGeom_RationalBSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<NCollection_HArray1<double>>&                               aWeightsData)
{

  weightsData = aWeightsData;

  StepGeom_BSplineCurve::Init(aName,
                              aDegree,
                              aControlPointsList,
                              aCurveForm,
                              aClosedCurve,
                              aSelfIntersect);
}

void StepGeom_RationalBSplineCurve::SetWeightsData(
  const occ::handle<NCollection_HArray1<double>>& aWeightsData)
{
  weightsData = aWeightsData;
}

occ::handle<NCollection_HArray1<double>> StepGeom_RationalBSplineCurve::WeightsData() const
{
  return weightsData;
}

double StepGeom_RationalBSplineCurve::WeightsDataValue(const int num) const
{
  return weightsData->Value(num);
}

int StepGeom_RationalBSplineCurve::NbWeightsData() const
{
  return weightsData->Length();
}
