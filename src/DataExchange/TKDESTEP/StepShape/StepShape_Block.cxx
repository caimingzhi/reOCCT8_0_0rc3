

#include <StepGeom_Axis2Placement3d.hpp>
#include <StepShape_Block.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Block, StepGeom_GeometricRepresentationItem)

StepShape_Block::StepShape_Block() = default;

void StepShape_Block::Init(const occ::handle<TCollection_HAsciiString>&  aName,
                           const occ::handle<StepGeom_Axis2Placement3d>& aPosition,
                           const double                                  aX,
                           const double                                  aY,
                           const double                                  aZ)
{

  position = aPosition;
  x        = aX;
  y        = aY;
  z        = aZ;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_Block::SetPosition(const occ::handle<StepGeom_Axis2Placement3d>& aPosition)
{
  position = aPosition;
}

occ::handle<StepGeom_Axis2Placement3d> StepShape_Block::Position() const
{
  return position;
}

void StepShape_Block::SetX(const double aX)
{
  x = aX;
}

double StepShape_Block::X() const
{
  return x;
}

void StepShape_Block::SetY(const double aY)
{
  y = aY;
}

double StepShape_Block::Y() const
{
  return y;
}

void StepShape_Block::SetZ(const double aZ)
{
  z = aZ;
}

double StepShape_Block::Z() const
{
  return z;
}
