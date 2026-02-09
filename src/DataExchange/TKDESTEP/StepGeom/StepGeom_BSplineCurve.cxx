

#include <StepGeom_BSplineCurve.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_BSplineCurve, StepGeom_BoundedCurve)

StepGeom_BSplineCurve::StepGeom_BSplineCurve() = default;

void StepGeom_BSplineCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const int                                                                     aDegree,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList,
  const StepGeom_BSplineCurveForm                                               aCurveForm,
  const StepData_Logical                                                        aClosedCurve,
  const StepData_Logical                                                        aSelfIntersect)
{

  degree            = aDegree;
  controlPointsList = aControlPointsList;
  curveForm         = aCurveForm;
  closedCurve       = aClosedCurve;
  selfIntersect     = aSelfIntersect;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_BSplineCurve::SetDegree(const int aDegree)
{
  degree = aDegree;
}

int StepGeom_BSplineCurve::Degree() const
{
  return degree;
}

void StepGeom_BSplineCurve::SetControlPointsList(
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aControlPointsList)
{
  controlPointsList = aControlPointsList;
}

occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> StepGeom_BSplineCurve::
  ControlPointsList() const
{
  return controlPointsList;
}

occ::handle<StepGeom_CartesianPoint> StepGeom_BSplineCurve::ControlPointsListValue(
  const int num) const
{
  return controlPointsList->Value(num);
}

int StepGeom_BSplineCurve::NbControlPointsList() const
{
  if (controlPointsList.IsNull())
    return 0;
  return controlPointsList->Length();
}

void StepGeom_BSplineCurve::SetCurveForm(const StepGeom_BSplineCurveForm aCurveForm)
{
  curveForm = aCurveForm;
}

StepGeom_BSplineCurveForm StepGeom_BSplineCurve::CurveForm() const
{
  return curveForm;
}

void StepGeom_BSplineCurve::SetClosedCurve(const StepData_Logical aClosedCurve)
{
  closedCurve = aClosedCurve;
}

StepData_Logical StepGeom_BSplineCurve::ClosedCurve() const
{
  return closedCurve;
}

void StepGeom_BSplineCurve::SetSelfIntersect(const StepData_Logical aSelfIntersect)
{
  selfIntersect = aSelfIntersect;
}

StepData_Logical StepGeom_BSplineCurve::SelfIntersect() const
{
  return selfIntersect;
}
