

#include <StepShape_PolyLoop.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_PolyLoop, StepShape_Loop)

StepShape_PolyLoop::StepShape_PolyLoop() = default;

void StepShape_PolyLoop::Init(
  const occ::handle<TCollection_HAsciiString>&                                  aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPolygon)
{

  polygon = aPolygon;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_PolyLoop::SetPolygon(
  const occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>>& aPolygon)
{
  polygon = aPolygon;
}

occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> StepShape_PolyLoop::Polygon()
  const
{
  return polygon;
}

occ::handle<StepGeom_CartesianPoint> StepShape_PolyLoop::PolygonValue(const int num) const
{
  return polygon->Value(num);
}

int StepShape_PolyLoop::NbPolygon() const
{
  if (polygon.IsNull())
    return 0;
  return polygon->Length();
}
