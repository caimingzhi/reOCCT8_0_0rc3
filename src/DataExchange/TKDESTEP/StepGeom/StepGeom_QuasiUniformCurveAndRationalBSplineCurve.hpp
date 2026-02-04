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
class StepGeom_QuasiUniformCurve;
class StepGeom_RationalBSplineCurve;
class TCollection_HAsciiString;

class StepGeom_QuasiUniformCurveAndRationalBSplineCurve : public StepGeom_BSplineCurve
{

public:
  //! Returns a QuasiUniformCurveAndRationalBSplineCurve
  Standard_EXPORT StepGeom_QuasiUniformCurveAndRationalBSplineCurve();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aDegree,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>&
                                                      aControlPointsList,
    const StepGeom_BSplineCurveForm                   aCurveForm,
    const StepData_Logical                            aClosedCurve,
    const StepData_Logical                            aSelfIntersect,
    const occ::handle<StepGeom_QuasiUniformCurve>&    aQuasiUniformCurve,
    const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aDegree,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>&
                                                    aControlPointsList,
    const StepGeom_BSplineCurveForm                 aCurveForm,
    const StepData_Logical                          aClosedCurve,
    const StepData_Logical                          aSelfIntersect,
    const occ::handle<NCollection_HArray1<double>>& aWeightsData);

  Standard_EXPORT void SetQuasiUniformCurve(
    const occ::handle<StepGeom_QuasiUniformCurve>& aQuasiUniformCurve);

  Standard_EXPORT occ::handle<StepGeom_QuasiUniformCurve> QuasiUniformCurve() const;

  Standard_EXPORT void SetRationalBSplineCurve(
    const occ::handle<StepGeom_RationalBSplineCurve>& aRationalBSplineCurve);

  Standard_EXPORT occ::handle<StepGeom_RationalBSplineCurve> RationalBSplineCurve() const;

  Standard_EXPORT void SetWeightsData(const occ::handle<NCollection_HArray1<double>>& aWeightsData);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> WeightsData() const;

  Standard_EXPORT double WeightsDataValue(const int num) const;

  Standard_EXPORT int NbWeightsData() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_QuasiUniformCurveAndRationalBSplineCurve, StepGeom_BSplineCurve)

private:
  occ::handle<StepGeom_QuasiUniformCurve>    quasiUniformCurve;
  occ::handle<StepGeom_RationalBSplineCurve> rationalBSplineCurve;
};

