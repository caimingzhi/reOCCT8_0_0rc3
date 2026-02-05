#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_KnotType.hpp>
#include <StepGeom_BSplineCurve.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_BSplineCurveForm.hpp>
#include <StepData_Logical.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

class StepGeom_BSplineCurveWithKnots : public StepGeom_BSplineCurve
{

public:
  //! Returns a BSplineCurveWithKnots
  Standard_EXPORT StepGeom_BSplineCurveWithKnots();

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
    const StepGeom_KnotType                         aKnotSpec);

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

  DEFINE_STANDARD_RTTIEXT(StepGeom_BSplineCurveWithKnots, StepGeom_BSplineCurve)

private:
  occ::handle<NCollection_HArray1<int>>    knotMultiplicities;
  occ::handle<NCollection_HArray1<double>> knots;
  StepGeom_KnotType                        knotSpec;
};
