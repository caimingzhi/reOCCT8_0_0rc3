

#include <Standard_Type.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <StepGeom_UniformSurface.hpp>
#include <StepGeom_UniformSurfaceAndRationalBSplineSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_UniformSurfaceAndRationalBSplineSurface,
                           StepGeom_BSplineSurface)

StepGeom_UniformSurfaceAndRationalBSplineSurface::
  StepGeom_UniformSurfaceAndRationalBSplineSurface() = default;

void StepGeom_UniformSurfaceAndRationalBSplineSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aUDegree,
  const int                                                                     aVDegree,
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineSurfaceForm                                             aSurfaceForm,
  const StepData_Logical                                                        aUClosed,
  const StepData_Logical                                                        aVClosed,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_UniformSurface>&                                   aUniformSurface,
  const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface)
{

  uniformSurface         = aUniformSurface;
  rationalBSplineSurface = aRationalBSplineSurface;

  StepGeom_BSplineSurface::Init(aName,
                                aUDegree,
                                aVDegree,
                                aControlPointsList,
                                aSurfaceForm,
                                aUClosed,
                                aVClosed,
                                aSelfIntersect);
}

void StepGeom_UniformSurfaceAndRationalBSplineSurface::Init(
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

  StepGeom_BSplineSurface::Init(aName,
                                aUDegree,
                                aVDegree,
                                aControlPointsList,
                                aSurfaceForm,
                                aUClosed,
                                aVClosed,
                                aSelfIntersect);

  rationalBSplineSurface = new StepGeom_RationalBSplineSurface();
  rationalBSplineSurface->Init(aName,
                               aUDegree,
                               aVDegree,
                               aControlPointsList,
                               aSurfaceForm,
                               aUClosed,
                               aVClosed,
                               aSelfIntersect,
                               aWeightsData);

  uniformSurface = new StepGeom_UniformSurface();
  uniformSurface->Init(aName,
                       aUDegree,
                       aVDegree,
                       aControlPointsList,
                       aSurfaceForm,
                       aUClosed,
                       aVClosed,
                       aSelfIntersect);
}

void StepGeom_UniformSurfaceAndRationalBSplineSurface::SetUniformSurface(
  const occ::handle<StepGeom_UniformSurface>& aUniformSurface)
{
  uniformSurface = aUniformSurface;
}

occ::handle<StepGeom_UniformSurface> StepGeom_UniformSurfaceAndRationalBSplineSurface::
  UniformSurface() const
{
  return uniformSurface;
}

void StepGeom_UniformSurfaceAndRationalBSplineSurface::SetRationalBSplineSurface(
  const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface)
{
  rationalBSplineSurface = aRationalBSplineSurface;
}

occ::handle<StepGeom_RationalBSplineSurface> StepGeom_UniformSurfaceAndRationalBSplineSurface::
  RationalBSplineSurface() const
{
  return rationalBSplineSurface;
}

void StepGeom_UniformSurfaceAndRationalBSplineSurface::SetWeightsData(
  const occ::handle<NCollection_HArray2<double>>& aWeightsData)
{
  rationalBSplineSurface->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray2<double>> StepGeom_UniformSurfaceAndRationalBSplineSurface::
  WeightsData() const
{
  return rationalBSplineSurface->WeightsData();
}

double StepGeom_UniformSurfaceAndRationalBSplineSurface::WeightsDataValue(const int num1,
                                                                          const int num2) const
{
  return rationalBSplineSurface->WeightsDataValue(num1, num2);
}

int StepGeom_UniformSurfaceAndRationalBSplineSurface::NbWeightsDataI() const
{
  return rationalBSplineSurface->NbWeightsDataI();
}

int StepGeom_UniformSurfaceAndRationalBSplineSurface::NbWeightsDataJ() const
{
  return rationalBSplineSurface->NbWeightsDataJ();
}
