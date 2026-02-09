

#include <StepGeom_Curve.hpp>
#include <StepGeom_SweptSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SweptSurface, StepGeom_Surface)

StepGeom_SweptSurface::StepGeom_SweptSurface() = default;

void StepGeom_SweptSurface::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                 const occ::handle<StepGeom_Curve>&           aSweptCurve)
{

  sweptCurve = aSweptCurve;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_SweptSurface::SetSweptCurve(const occ::handle<StepGeom_Curve>& aSweptCurve)
{
  sweptCurve = aSweptCurve;
}

occ::handle<StepGeom_Curve> StepGeom_SweptSurface::SweptCurve() const
{
  return sweptCurve;
}
