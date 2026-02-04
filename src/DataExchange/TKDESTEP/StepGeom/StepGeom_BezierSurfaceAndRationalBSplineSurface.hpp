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
class StepGeom_BezierSurface;
class StepGeom_RationalBSplineSurface;
class TCollection_HAsciiString;

class StepGeom_BezierSurfaceAndRationalBSplineSurface : public StepGeom_BSplineSurface
{

public:
  //! Returns a BezierSurfaceAndRationalBSplineSurface
  Standard_EXPORT StepGeom_BezierSurfaceAndRationalBSplineSurface();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aUDegree,
    const int                                    aVDegree,
    const occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>>&
                                                        aControlPointsList,
    const StepGeom_BSplineSurfaceForm                   aSurfaceForm,
    const StepData_Logical                              aUClosed,
    const StepData_Logical                              aVClosed,
    const StepData_Logical                              aSelfIntersect,
    const occ::handle<StepGeom_BezierSurface>&          aBezierSurface,
    const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface);

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
    const occ::handle<NCollection_HArray2<double>>& aWeightsData);

  Standard_EXPORT void SetBezierSurface(const occ::handle<StepGeom_BezierSurface>& aBezierSurface);

  Standard_EXPORT occ::handle<StepGeom_BezierSurface> BezierSurface() const;

  Standard_EXPORT void SetRationalBSplineSurface(
    const occ::handle<StepGeom_RationalBSplineSurface>& aRationalBSplineSurface);

  Standard_EXPORT occ::handle<StepGeom_RationalBSplineSurface> RationalBSplineSurface() const;

  Standard_EXPORT void SetWeightsData(const occ::handle<NCollection_HArray2<double>>& aWeightsData);

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> WeightsData() const;

  Standard_EXPORT double WeightsDataValue(const int num1, const int num2) const;

  Standard_EXPORT int NbWeightsDataI() const;

  Standard_EXPORT int NbWeightsDataJ() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_BezierSurfaceAndRationalBSplineSurface, StepGeom_BSplineSurface)

private:
  occ::handle<StepGeom_BezierSurface>          bezierSurface;
  occ::handle<StepGeom_RationalBSplineSurface> rationalBSplineSurface;
};

