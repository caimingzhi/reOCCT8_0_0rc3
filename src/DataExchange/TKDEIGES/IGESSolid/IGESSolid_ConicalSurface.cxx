#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_ConicalSurface, IGESData_IGESEntity)

IGESSolid_ConicalSurface::IGESSolid_ConicalSurface() = default;

void IGESSolid_ConicalSurface::Init(const occ::handle<IGESGeom_Point>&     aLocation,
                                    const occ::handle<IGESGeom_Direction>& anAxis,
                                    const double                           aRadius,
                                    const double                           anAngle,
                                    const occ::handle<IGESGeom_Direction>& aRefdir)
{
  theLocationPoint = aLocation;
  theAxis          = anAxis;
  theRadius        = aRadius;
  theAngle         = anAngle;
  theRefDir        = aRefdir;
  InitTypeAndForm(194, (theRefDir.IsNull() ? 0 : 1));
}

occ::handle<IGESGeom_Point> IGESSolid_ConicalSurface::LocationPoint() const
{
  return theLocationPoint;
}

occ::handle<IGESGeom_Direction> IGESSolid_ConicalSurface::Axis() const
{
  return theAxis;
}

double IGESSolid_ConicalSurface::Radius() const
{
  return theRadius;
}

double IGESSolid_ConicalSurface::SemiAngle() const
{
  return theAngle;
}

occ::handle<IGESGeom_Direction> IGESSolid_ConicalSurface::ReferenceDir() const
{
  return theRefDir;
}

bool IGESSolid_ConicalSurface::IsParametrised() const
{
  return (!theRefDir.IsNull());
}
