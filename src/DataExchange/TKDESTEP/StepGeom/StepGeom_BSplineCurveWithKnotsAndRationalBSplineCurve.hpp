#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_BSplineCurve.hpp>
#include <Standard_Integer.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_BSplineCurveForm.hpp>
#include <StepData_Logical.hpp>
#include <StepGeom_KnotType.hpp>
class StepGeom_BSplineCurveWithKnots;
class StepGeom_RationalBSplineCurve;
class TCollection_HAsciiString;

class StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve : public StepGeom_BSplineCurve
{

public:
  Standard_EXPORT StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aDegree,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>&
                                                       aControlPointsList,
    const StepGeom_BSplineCurveForm                    aCurveForm,
    const StepData_Logical                             aClosedCurve,
    const StepData_Logical                             aSelfIntersect,
    const occ::handle<StepGeom_BSplineCurveWithKnots>& aBSplineCurveWithKnots,
    const occ::handle<StepGeom_RationalBSplineCurve>&  aRationalBSplineCurve);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aDegree,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>&
                                                    aControlPointsList,
    const StepGeom_BSplineCurveForm                 aCurveForm,
    const StepData_Logical                          aClosedCurve,
    const StepData_Logical                          aSelfIntersect,
    const occ::handle<NCollection_HArray1<int>>&    aKnotMultiplicities,
    const occ::handle<NCollection_HArray1<double>>& aKnots,
    const StepGeom_KnotType                         aKnotSpec,
    const occ::handle<NCollection_HArray1<double>>& aWeightsData);

  Standard_EXPORT void SetBSplineCurveWithKnots(
    const occ::handle<StepGeom_BSplineCurveWithKnots>& aBSplineCurveWithKnots);

  Standard_EXPORT occ::handle<StepGeom_BSplineCurveWithKnots> BSplineCurveWithKnots() const;

  Standard_EXPORT void SetRationalBSplineCurve(
    const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve);

  Standard_EXPORT occ::handle<StepGeom_RationalBSplineCurve> RationalBSplineCurve() const;

  Standard_EXPORT void SetKnotMultiplicities(
    const occ::handle<NCollection_HArray1<int>>& aKnotMultiplicities);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> KnotMultiplicities() const;

  Standard_EXPORT int KnotMultiplicitiesValue(const int num) const;

  Standard_EXPORT int NbKnotMultiplicities() const;

  Standard_EXPORT void SetKnots(const occ::handle<NCollection_HArray1<double>>& aKnots);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Knots() const;

  Standard_EXPORT double KnotsValue(const int num) const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT void SetKnotSpec(const StepGeom_KnotType aKnotSpec);

  Standard_EXPORT StepGeom_KnotType KnotSpec() const;

  Standard_EXPORT void SetWeightsData(const occ::handle<NCollection_HArray1<double>>& aWeightsData);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> WeightsData() const;

  Standard_EXPORT double WeightsDataValue(const int num) const;

  Standard_EXPORT int NbWeightsData() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve,
                          StepGeom_BSplineCurve)

private:
  occ::handle<StepGeom_BSplineCurveWithKnots> bSplineCurveWithKnots;
  occ::handle<StepGeom_RationalBSplineCurve>  rationalBSplineCurve;
};
