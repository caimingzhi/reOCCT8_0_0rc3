

#include <StepGeom_RectangularCompositeSurface.hpp>
#include <StepGeom_SurfacePatch.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_RectangularCompositeSurface, StepGeom_BoundedSurface)

StepGeom_RectangularCompositeSurface::StepGeom_RectangularCompositeSurface() = default;

void StepGeom_RectangularCompositeSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                                aName,
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>>& aSegments)
{

  segments = aSegments;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_RectangularCompositeSurface::SetSegments(
  const occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>>& aSegments)
{
  segments = aSegments;
}

occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>>
  StepGeom_RectangularCompositeSurface::Segments() const
{
  return segments;
}

occ::handle<StepGeom_SurfacePatch> StepGeom_RectangularCompositeSurface::SegmentsValue(
  const int num1,
  const int num2) const
{
  return segments->Value(num1, num2);
}

int StepGeom_RectangularCompositeSurface::NbSegmentsI() const
{
  if (segments.IsNull())
    return 0;
  return segments->UpperRow() - segments->LowerRow() + 1;
}

int StepGeom_RectangularCompositeSurface::NbSegmentsJ() const
{
  if (segments.IsNull())
    return 0;
  return segments->UpperCol() - segments->LowerCol() + 1;
}
