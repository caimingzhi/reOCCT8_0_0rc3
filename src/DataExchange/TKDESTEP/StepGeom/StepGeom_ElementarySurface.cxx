

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_ElementarySurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_ElementarySurface, StepGeom_Surface)

StepGeom_ElementarySurface::StepGeom_ElementarySurface() = default;

void StepGeom_ElementarySurface::Init(const occ::handle<TCollection_HAsciiString>&  aName,
                                      const occ::handle<StepGeom_Axis2Placement3d>& aPosition)
{

  position = aPosition;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_ElementarySurface::SetPosition(
  const occ::handle<StepGeom_Axis2Placement3d>& aPosition)
{
  position = aPosition;
}

occ::handle<StepGeom_Axis2Placement3d> StepGeom_ElementarySurface::Position() const
{
  return position;
}
