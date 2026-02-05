#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_CylindricalSurface, IGESData_IGESEntity)

IGESSolid_CylindricalSurface::IGESSolid_CylindricalSurface() = default;

void IGESSolid_CylindricalSurface::Init(const occ::handle<IGESGeom_Point>&     aLocation,
                                        const occ::handle<IGESGeom_Direction>& anAxis,
                                        const double                           aRadius,
                                        const occ::handle<IGESGeom_Direction>& aRefdir)
{
  theLocationPoint = aLocation;
  theAxis          = anAxis;
  theRadius        = aRadius;
  theRefDir        = aRefdir;
  InitTypeAndForm(192, (theRefDir.IsNull() ? 0 : 1));
}

occ::handle<IGESGeom_Point> IGESSolid_CylindricalSurface::LocationPoint() const
{
  return theLocationPoint;
}

occ::handle<IGESGeom_Direction> IGESSolid_CylindricalSurface::Axis() const
{
  return theAxis;
}

double IGESSolid_CylindricalSurface::Radius() const
{
  return theRadius;
}

occ::handle<IGESGeom_Direction> IGESSolid_CylindricalSurface::ReferenceDir() const
{
  return theRefDir;
}

bool IGESSolid_CylindricalSurface::IsParametrised() const
{
  return (!theRefDir.IsNull());
}
