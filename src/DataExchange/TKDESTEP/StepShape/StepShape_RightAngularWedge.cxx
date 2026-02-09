

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepShape_RightAngularWedge.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_RightAngularWedge, StepGeom_GeometricRepresentationItem)

StepShape_RightAngularWedge::StepShape_RightAngularWedge() = default;

void StepShape_RightAngularWedge::Init(const occ::handle<TCollection_HAsciiString>&  aName,
                                       const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                                       const double                                  aX,
                                       const double                                  aY,
                                       const double                                  aZ,
                                       const double                                  aLtx)
{

  position = aPosition;
  x        = aX;
  y        = aY;
  z        = aZ;
  ltx      = aLtx;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_RightAngularWedge::SetPosition(
  const occ::handle<StepGeom_Axis2Placement3d>& aPosition)
{
  position = aPosition;
}

occ::handle<StepGeom_Axis2Placement3d> StepShape_RightAngularWedge::Position() const
{
  return position;
}

void StepShape_RightAngularWedge::SetX(const double aX)
{
  x = aX;
}

double StepShape_RightAngularWedge::X() const
{
  return x;
}

void StepShape_RightAngularWedge::SetY(const double aY)
{
  y = aY;
}

double StepShape_RightAngularWedge::Y() const
{
  return y;
}

void StepShape_RightAngularWedge::SetZ(const double aZ)
{
  z = aZ;
}

double StepShape_RightAngularWedge::Z() const
{
  return z;
}

void StepShape_RightAngularWedge::SetLtx(const double aLtx)
{
  ltx = aLtx;
}

double StepShape_RightAngularWedge::Ltx() const
{
  return ltx;
}
