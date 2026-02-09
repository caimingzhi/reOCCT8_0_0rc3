#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_BSplineCurveForm.hpp>
#include <StepData_Logical.hpp>
#include <StepGeom_BoundedCurve.hpp>
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;

class StepGeom_BSplineCurve : public StepGeom_BoundedCurve
{

public:
  Standard_EXPORT StepGeom_BSplineCurve();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const int                                    aDegree,
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>&
                                    aControlPointsList,
    const StepGeom_BSplineCurveForm aCurveForm,
    const StepData_Logical          aClosedCurve,
    const StepData_Logical          aSelfIntersect);

  Standard_EXPORT void SetDegree(const int aDegree);

  Standard_EXPORT int Degree() const;

  Standard_EXPORT void SetControlPointsList(
    const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>&
      aControlPointsList);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>
                  ControlPointsList() const;

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> ControlPointsListValue(const int num) const;

  Standard_EXPORT int NbControlPointsList() const;

  Standard_EXPORT void SetCurveForm(const StepGeom_BSplineCurveForm aCurveForm);

  Standard_EXPORT StepGeom_BSplineCurveForm CurveForm() const;

  Standard_EXPORT void SetClosedCurve(const StepData_Logical aClosedCurve);

  Standard_EXPORT StepData_Logical ClosedCurve() const;

  Standard_EXPORT void SetSelfIntersect(const StepData_Logical aSelfIntersect);

  Standard_EXPORT StepData_Logical SelfIntersect() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_BSplineCurve, StepGeom_BoundedCurve)

private:
  int                                                                    degree;
  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> controlPointsList;
  StepGeom_BSplineCurveForm                                              curveForm;
  StepData_Logical                                                       closedCurve;
  StepData_Logical                                                       selfIntersect;
};
