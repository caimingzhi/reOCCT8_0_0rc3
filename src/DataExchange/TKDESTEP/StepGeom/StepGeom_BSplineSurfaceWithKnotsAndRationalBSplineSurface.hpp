#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineSurface.hpp>
#include <Standard_Integer.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepGeom_BSplineSurfaceForm.hpp>
#include <StepData_Logical.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_KnotType.hpp>
class StepGeom_BSplineSurfaceWithKnots;
class StepGeom_RationalBSplineSurface;
class TCollection_HAsciiString;

class StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface : public StepGeom_BSplineSurface
{

public:
  //! Returns a BSplineSurfaceWithKnotsAndRationalBSplineSurface
  Standard_EXPORT StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aUDegree,
    const int                                    aVDegree,
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>&
                                                         aControlPointsList,
    const StepGeom_BSplineSurfaceForm                    aSurfaceForm,
    const StepData_Logical                               aUClosed,
    const StepData_Logical                               aVClosed,
    const StepData_Logical                               aSelfIntersect,
    const occ::handle<StepGeom_BSplineSurfaceWithKnots>& aBSplineSurfaceWithKnots,
    const occ::handle<StepGeom_RationalBSplineSurface>&  aRationalBSplineSurface);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aUDegree,
    const int                                    aVDegree,
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>&
                                                    aControlPointsList,
    const StepGeom_BSplineSurfaceForm               aSurfaceForm,
    const StepData_Logical                          aUClosed,
    const StepData_Logical                          aVClosed,
    const StepData_Logical                          aSelfIntersect,
    const occ::handle<NCollection_HArray1<int>>&    aUMultiplicities,
    const occ::handle<NCollection_HArray1<int>>&    aVMultiplicities,
    const occ::handle<NCollection_HArray1<double>>& aUKnots,
    const occ::handle<NCollection_HArray1<double>>& aVKnots,
    const StepGeom_KnotType                         aKnotSpec,
    const occ::handle<NCollection_HArray2<double>>& aWeightsData);

  Standard_EXPORT void SetBSplineSurfaceWithKnots(
    const occ::handle<StepGeom_BSplineSurfaceWithKnots>& aBSplineSurfaceWithKnots);

  Standard_EXPORT occ::handle<StepGeom_BSplineSurfaceWithKnots> BSplineSurfaceWithKnots() const;

  Standard_EXPORT void SetRationalBSplineSurface(
    const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface);

  Standard_EXPORT occ::handle<StepGeom_RationalBSplineSurface> RationalBSplineSurface() const;

  Standard_EXPORT void SetUMultiplicities(
    const occ::handle<NCollection_HArray1<int>>& aUMultiplicities);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> UMultiplicities() const;

  Standard_EXPORT int UMultiplicitiesValue(const int num) const;

  Standard_EXPORT int NbUMultiplicities() const;

  Standard_EXPORT void SetVMultiplicities(
    const occ::handle<NCollection_HArray1<int>>& aVMultiplicities);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> VMultiplicities() const;

  Standard_EXPORT int VMultiplicitiesValue(const int num) const;

  Standard_EXPORT int NbVMultiplicities() const;

  Standard_EXPORT void SetUKnots(const occ::handle<NCollection_HArray1<double>>& aUKnots);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> UKnots() const;

  Standard_EXPORT double UKnotsValue(const int num) const;

  Standard_EXPORT int NbUKnots() const;

  Standard_EXPORT void SetVKnots(const occ::handle<NCollection_HArray1<double>>& aVKnots);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> VKnots() const;

  Standard_EXPORT double VKnotsValue(const int num) const;

  Standard_EXPORT int NbVKnots() const;

  Standard_EXPORT void SetKnotSpec(const StepGeom_KnotType aKnotSpec);

  Standard_EXPORT StepGeom_KnotType KnotSpec() const;

  Standard_EXPORT void SetWeightsData(const occ::handle<NCollection_HArray2<double>>& aWeightsData);

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> WeightsData() const;

  Standard_EXPORT double WeightsDataValue(const int num1, const int num2) const;

  Standard_EXPORT int NbWeightsDataI() const;

  Standard_EXPORT int NbWeightsDataJ() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface,
                          StepGeom_BSplineSurface)

private:
  occ::handle<StepGeom_BSplineSurfaceWithKnots> bSplineSurfaceWithKnots;
  occ::handle<StepGeom_RationalBSplineSurface>  rationalBSplineSurface;
};

