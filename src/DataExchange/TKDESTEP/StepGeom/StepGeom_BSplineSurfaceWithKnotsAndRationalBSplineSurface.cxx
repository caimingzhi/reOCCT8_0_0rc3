

#include <Standard_Type.hpp>
#include <StepGeom_BSplineSurfaceWithKnots.hpp>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface,
                           StepGeom_BSplineSurface)

StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::
  StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface() = default;

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aUDegree,
  const int                                                                     aVDegree,
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineSurfaceForm                                             aSurfaceForm,
  const StepData_Logical                                                        aUClosed,
  const StepData_Logical                                                        aVClosed,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<StepGeom_BSplineSurfaceWithKnots>& aBSplineSurfaceWithKnots,
  const occ::handle<StepGeom_RationalBSplineSurface>&  aRationalBSplineSurface)
{

  bSplineSurfaceWithKnots = aBSplineSurfaceWithKnots;
  rationalBSplineSurface  = aRationalBSplineSurface;

  StepGeom_BSplineSurface::Init(aName,
                                aUDegree,
                                aVDegree,
                                aControlPointsList,
                                aSurfaceForm,
                                aUClosed,
                                aVClosed,
                                aSelfIntersect);
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aUDegree,
  const int                                                                     aVDegree,
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineSurfaceForm                                             aSurfaceForm,
  const StepData_Logical                                                        aUClosed,
  const StepData_Logical                                                        aVClosed,
  const StepData_Logical                                                        aSelfIntersect,
  const occ::handle<NCollection_HArray1<int>>&                                  aUMultiplicities,
  const occ::handle<NCollection_HArray1<int>>&                                  aVMultiplicities,
  const occ::handle<NCollection_HArray1<double>>&                               aUKnots,
  const occ::handle<NCollection_HArray1<double>>&                               aVKnots,
  const StepGeom_KnotType                                                       aKnotSpec,
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

  bSplineSurfaceWithKnots = new StepGeom_BSplineSurfaceWithKnots();
  bSplineSurfaceWithKnots->Init(aName,
                                aUDegree,
                                aVDegree,
                                aControlPointsList,
                                aSurfaceForm,
                                aUClosed,
                                aVClosed,
                                aSelfIntersect,
                                aUMultiplicities,
                                aVMultiplicities,
                                aUKnots,
                                aVKnots,
                                aKnotSpec);

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

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetBSplineSurfaceWithKnots(
  const occ::handle<StepGeom_BSplineSurfaceWithKnots>& aBSplineSurfaceWithKnots)
{
  bSplineSurfaceWithKnots = aBSplineSurfaceWithKnots;
}

occ::handle<StepGeom_BSplineSurfaceWithKnots>
  StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::BSplineSurfaceWithKnots() const
{
  return bSplineSurfaceWithKnots;
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetRationalBSplineSurface(
  const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface)
{
  rationalBSplineSurface = aRationalBSplineSurface;
}

occ::handle<StepGeom_RationalBSplineSurface>
  StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::RationalBSplineSurface() const
{
  return rationalBSplineSurface;
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetUMultiplicities(
  const occ::handle<NCollection_HArray1<int>>& aUMultiplicities)
{
  bSplineSurfaceWithKnots->SetUMultiplicities(aUMultiplicities);
}

occ::handle<NCollection_HArray1<int>> StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::
  UMultiplicities() const
{
  return bSplineSurfaceWithKnots->UMultiplicities();
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::UMultiplicitiesValue(
  const int num) const
{
  return bSplineSurfaceWithKnots->UMultiplicitiesValue(num);
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::NbUMultiplicities() const
{
  return bSplineSurfaceWithKnots->NbUMultiplicities();
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetVMultiplicities(
  const occ::handle<NCollection_HArray1<int>>& aVMultiplicities)
{
  bSplineSurfaceWithKnots->SetVMultiplicities(aVMultiplicities);
}

occ::handle<NCollection_HArray1<int>> StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::
  VMultiplicities() const
{
  return bSplineSurfaceWithKnots->VMultiplicities();
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::VMultiplicitiesValue(
  const int num) const
{
  return bSplineSurfaceWithKnots->VMultiplicitiesValue(num);
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::NbVMultiplicities() const
{
  return bSplineSurfaceWithKnots->NbVMultiplicities();
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetUKnots(
  const occ::handle<NCollection_HArray1<double>>& aUKnots)
{
  bSplineSurfaceWithKnots->SetUKnots(aUKnots);
}

occ::handle<NCollection_HArray1<double>> StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::
  UKnots() const
{
  return bSplineSurfaceWithKnots->UKnots();
}

double StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::UKnotsValue(const int num) const
{
  return bSplineSurfaceWithKnots->UKnotsValue(num);
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::NbUKnots() const
{
  return bSplineSurfaceWithKnots->NbUKnots();
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetVKnots(
  const occ::handle<NCollection_HArray1<double>>& aVKnots)
{
  bSplineSurfaceWithKnots->SetVKnots(aVKnots);
}

occ::handle<NCollection_HArray1<double>> StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::
  VKnots() const
{
  return bSplineSurfaceWithKnots->VKnots();
}

double StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::VKnotsValue(const int num) const
{
  return bSplineSurfaceWithKnots->VKnotsValue(num);
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::NbVKnots() const
{
  return bSplineSurfaceWithKnots->NbVKnots();
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetKnotSpec(
  const StepGeom_KnotType aKnotSpec)
{
  bSplineSurfaceWithKnots->SetKnotSpec(aKnotSpec);
}

StepGeom_KnotType StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::KnotSpec() const
{
  return bSplineSurfaceWithKnots->KnotSpec();
}

void StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::SetWeightsData(
  const occ::handle<NCollection_HArray2<double>>& aWeightsData)
{
  rationalBSplineSurface->SetWeightsData(aWeightsData);
}

occ::handle<NCollection_HArray2<double>> StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::
  WeightsData() const
{
  return rationalBSplineSurface->WeightsData();
}

double StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::WeightsDataValue(
  const int num1,
  const int num2) const
{
  return rationalBSplineSurface->WeightsDataValue(num1, num2);
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::NbWeightsDataI() const
{
  return rationalBSplineSurface->NbWeightsDataI();
}

int StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface::NbWeightsDataJ() const
{
  return rationalBSplineSurface->NbWeightsDataJ();
}
