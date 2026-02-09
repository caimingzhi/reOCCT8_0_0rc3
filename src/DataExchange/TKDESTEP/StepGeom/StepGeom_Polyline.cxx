

#include <StepGeom_Polyline.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Polyline, StepGeom_BoundedCurve)

StepGeom_Polyline::StepGeom_Polyline() = default;

void StepGeom_Polyline::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPoints)
{

  points = aPoints;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_Polyline::SetPoints(
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPoints)
{
  points = aPoints;
}

occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> StepGeom_Polyline::Points()
  const
{
  return points;
}

occ::handle<StepGeom_CartesianPoint> StepGeom_Polyline::PointsValue(const int num) const
{
  return points->Value(num);
}

int StepGeom_Polyline::NbPoints() const
{
  if (points.IsNull())
    return 0;
  return points->Length();
}
