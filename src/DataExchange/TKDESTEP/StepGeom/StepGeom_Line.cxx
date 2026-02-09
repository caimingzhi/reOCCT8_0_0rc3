

#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Line.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Line, StepGeom_Curve)

StepGeom_Line::StepGeom_Line() = default;

void StepGeom_Line::Init(const occ::handle<TCollection_HAsciiString>& aName,
                         const occ::handle<StepGeom_CartesianPoint>&  aPnt,
                         const occ::handle<StepGeom_Vector>&          aDir)
{

  pnt = aPnt;
  dir = aDir;

  StepRepr_RepresentationItem::Init(aName);
}

void StepGeom_Line::SetPnt(const occ::handle<StepGeom_CartesianPoint>& aPnt)
{
  pnt = aPnt;
}

occ::handle<StepGeom_CartesianPoint> StepGeom_Line::Pnt() const
{
  return pnt;
}

void StepGeom_Line::SetDir(const occ::handle<StepGeom_Vector>& aDir)
{
  dir = aDir;
}

occ::handle<StepGeom_Vector> StepGeom_Line::Dir() const
{
  return dir;
}
