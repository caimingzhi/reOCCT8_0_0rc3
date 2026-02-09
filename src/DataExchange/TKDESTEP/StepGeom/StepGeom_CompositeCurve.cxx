

#include <StepGeom_CompositeCurve.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_CompositeCurve, StepGeom_BoundedCurve)

StepGeom_CompositeCurve::StepGeom_CompositeCurve() = default;

void StepGeom_CompositeCurve::Init(
  const occ::handle<TCollection_HAsciiString>&                                         aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>>& aSegments,
  const StepData_Logical aSelfIntersect)
{

  segments      = aSegments;
  selfIntersect = aSelfIntersect;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_CompositeCurve::SetSegments(
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>>& aSegments)
{
  segments = aSegments;
}

occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>>
  StepGeom_CompositeCurve::Segments() const
{
  return segments;
}

occ::handle<StepGeom_CompositeCurveSegment> StepGeom_CompositeCurve::SegmentsValue(
  const int num) const
{
  return segments->Value(num);
}

int StepGeom_CompositeCurve::NbSegments() const
{
  if (segments.IsNull())
    return 0;
  return segments->Length();
}

void StepGeom_CompositeCurve::SetSelfIntersect(const StepData_Logical aSelfIntersect)
{
  selfIntersect = aSelfIntersect;
}

StepData_Logical StepGeom_CompositeCurve::SelfIntersect() const
{
  return selfIntersect;
}
