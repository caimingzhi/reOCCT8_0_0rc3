

#include <Standard_Type.hpp>
#include <StepGeom_BezierSurface.hpp>
#include <StepGeom_BezierSurfaceAndRationalBSplineSurface.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_BezierSurfaceAndRationalBSplineSurface, StepGeom_BSplineSurface)

StepGeom_BezierSurfaceAndRationalBSplineSurface::StepGeom_BezierSurfaceAndRationalBSplineSurface() =
  default;

void StepGeom_BezierSurfaceAndRationalBSplineSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aUDegree,
  const int                                                                     aVDegree,
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineSurfaceForm                                             aSurfaceForm,
  const StepData_Logical                                                        aUClosed,
  const StepData_Logical                                                        aVClosed,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_BezierSurface>&                                    aBezierSurface,
  const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface)
{

  bezierSurface          = aBezierSurface;
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

void StepGeom_BezierSurfaceAndRationalBSplineSurface::Init(
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

  bezierSurface = new StepGeom_BezierSurface();
  bezierSurface->Init(aName,
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

void StepGeom_BezierSurfaceAndRationalBSplineSurface::SetBezierSurface(
  const occ::handle<StepGeom_BezierSurface>& aBezierSurface)
{
  bezierSurface = aBezierSurface;
}

occ::handle<StepGeom_BezierSurface> StepGeom_BezierSurfaceAndRationalBSplineSurface::BezierSurface()
  const
{
  return bezierSurface;
}

void StepGeom_BezierSurfaceAndRationalBSplineSurface::SetRationalBSplineSurface(
  const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface)
{
  rationalBSplineSurface = aRationalBSplineSurface;
}

occ::handle<StepGeom_RationalBSplineSurface> StepGeom_BezierSurfaceAndRationalBSplineSurface::
  RationalBSplineSurface() const
{
  return rationalBSplineSurface;
}

void StepGeom_BezierSurfaceAndRationalBSplineSurface::SetWeightsData(
  const occ::handle<NCollection_HArray2<double>>& aWeightsData)
{
  rationalBSplineSurface->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray2<double>> StepGeom_BezierSurfaceAndRationalBSplineSurface::
  WeightsData() const
{
  return rationalBSplineSurface->WeightsData();
}

double StepGeom_BezierSurfaceAndRationalBSplineSurface::WeightsDataValue(const int num1,
                                                                         const int num2) const
{
  return rationalBSplineSurface->WeightsDataValue(num1, num2);
}

int StepGeom_BezierSurfaceAndRationalBSplineSurface::NbWeightsDataI() const
{
  return rationalBSplineSurface->NbWeightsDataI();
}

int StepGeom_BezierSurfaceAndRationalBSplineSurface::NbWeightsDataJ() const
{
  return rationalBSplineSurface->NbWeightsDataJ();
}
