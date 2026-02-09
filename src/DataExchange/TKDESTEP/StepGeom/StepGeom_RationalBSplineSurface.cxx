

#include <StepGeom_RationalBSplineSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_RationalBSplineSurface, StepGeom_BSplineSurface)

StepGeom_RationalBSplineSurface::StepGeom_RationalBSplineSurface() = default;

void StepGeom_RationalBSplineSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aUDegree,
  const int                                                                     aVDegree,
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineSurfaceForm                                             aSurfaceForm,
  const StepData_Logical                                                        aUClosed,
  const StepData_Logical                                                        aVClosed,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<NCollection_HArray2<double>>&                               aWeightsData)
{

  weightsData = aWeightsData;

  StepGeom_BSplineSurface::Init(aName,
                                aUDegree,
                                aVDegree,
                                aControlPointsList,
                                aSurfaceForm,
                                aUClosed,
                                aVClosed,
                                aSelfIntersect);
}

void StepGeom_RationalBSplineSurface::SetWeightsData(
  const occ::handle<NCollection_HArray2<double>>& aWeightsData)
{
  weightsData = aWeightsData;
}

occ::handle<NCollection_HArray2<double>> StepGeom_RationalBSplineSurface::WeightsData() const
{
  return weightsData;
}

double StepGeom_RationalBSplineSurface::WeightsDataValue(const int num1, const int num2) const
{
  return weightsData->Value(num1, num2);
}

int StepGeom_RationalBSplineSurface::NbWeightsDataI() const
{
  return weightsData->UpperRow() - weightsData->LowerRow() + 1;
}

int StepGeom_RationalBSplineSurface::NbWeightsDataJ() const
{
  return weightsData->UpperCol() - weightsData->LowerCol() + 1;
}
