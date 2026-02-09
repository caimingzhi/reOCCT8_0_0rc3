

#include <Standard_Type.hpp>
#include <StepGeom_QuasiUniformSurface.hpp>
#include <StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface,
                           StepGeom_BSplineSurface)

StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::
  StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface() = default;

void StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aUDegree,
  const int                                                                     aVDegree,
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineSurfaceForm                                             aSurfaceForm,
  const StepData_Logical                                                        aUClosed,
  const StepData_Logical                                                        aVClosed,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_QuasiUniformSurface>&    aQuasiUniformSurface,
  const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface)
{

  quasiUniformSurface    = aQuasiUniformSurface;
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

void StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::Init(
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

  quasiUniformSurface = new StepGeom_QuasiUniformSurface();
  quasiUniformSurface->Init(aName,
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
}

void StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::SetQuasiUniformSurface(
  const occ::handle<StepGeom_QuasiUniformSurface>& aQuasiUniformSurface)
{
  quasiUniformSurface = aQuasiUniformSurface;
}

occ::handle<StepGeom_QuasiUniformSurface> StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::
  QuasiUniformSurface() const
{
  return quasiUniformSurface;
}

void StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::SetRationalBSplineSurface(
  const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface)
{
  rationalBSplineSurface = aRationalBSplineSurface;
}

occ::handle<StepGeom_RationalBSplineSurface> StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::
  RationalBSplineSurface() const
{
  return rationalBSplineSurface;
}

void StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::SetWeightsData(
  const occ::handle<NCollection_HArray2<double>>& aWeightsData)
{
  rationalBSplineSurface->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray2<double>> StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::
  WeightsData() const
{
  return rationalBSplineSurface->WeightsData();
}

double StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::WeightsDataValue(const int num1,
                                                                               const int num2) const
{
  return rationalBSplineSurface->WeightsDataValue(num1, num2);
}

int StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::NbWeightsDataI() const
{
  return rationalBSplineSurface->NbWeightsDataI();
}

int StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface::NbWeightsDataJ() const
{
  return rationalBSplineSurface->NbWeightsDataJ();
}
