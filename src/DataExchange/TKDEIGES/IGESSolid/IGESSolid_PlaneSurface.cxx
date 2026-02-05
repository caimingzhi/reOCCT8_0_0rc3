#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESSolid_PlaneSurface.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_PlaneSurface, IGESData_IGESEntity)

IGESSolid_PlaneSurface::IGESSolid_PlaneSurface() = default;

void IGESSolid_PlaneSurface::Init(const occ::handle<IGESGeom_Point>&     aLocation,
                                  const occ::handle<IGESGeom_Direction>& aNormal,
                                  const occ::handle<IGESGeom_Direction>& Refdir)
{
  theLocationPoint = aLocation;
  theNormal        = aNormal;
  theRefDir        = Refdir;
  InitTypeAndForm(190, (theRefDir.IsNull() ? 0 : 1));
}

occ::handle<IGESGeom_Point> IGESSolid_PlaneSurface::LocationPoint() const
{
  return theLocationPoint;
}

occ::handle<IGESGeom_Direction> IGESSolid_PlaneSurface::Normal() const
{
  return theNormal;
}

occ::handle<IGESGeom_Direction> IGESSolid_PlaneSurface::ReferenceDir() const
{
  return theRefDir;
}

bool IGESSolid_PlaneSurface::IsParametrised() const
{
  return (!theRefDir.IsNull());
}
