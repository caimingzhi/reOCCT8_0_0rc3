#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_ToroidalSurface, IGESData_IGESEntity)

IGESSolid_ToroidalSurface::IGESSolid_ToroidalSurface() = default;

void IGESSolid_ToroidalSurface::Init(const occ::handle<IGESGeom_Point>&     aCenter,
                                     const occ::handle<IGESGeom_Direction>& anAxis,
                                     const double                           majRadius,
                                     const double                           minRadius,
                                     const occ::handle<IGESGeom_Direction>& Refdir)
{
  theCenter      = aCenter;
  theAxis        = anAxis;
  theMajorRadius = majRadius;
  theMinorRadius = minRadius;
  theRefDir      = Refdir;
  InitTypeAndForm(198, (theRefDir.IsNull() ? 0 : 1));
}

occ::handle<IGESGeom_Point> IGESSolid_ToroidalSurface::Center() const
{
  return theCenter;
}

gp_Pnt IGESSolid_ToroidalSurface::TransformedCenter() const
{
  if (!HasTransf())
    return theCenter->Value();
  else
  {
    gp_XYZ tmp = theCenter->Value().XYZ();
    Location().Transforms(tmp);
    return gp_Pnt(tmp);
  }
}

occ::handle<IGESGeom_Direction> IGESSolid_ToroidalSurface::Axis() const
{
  return theAxis;
}

double IGESSolid_ToroidalSurface::MajorRadius() const
{
  return theMajorRadius;
}

double IGESSolid_ToroidalSurface::MinorRadius() const
{
  return theMinorRadius;
}

occ::handle<IGESGeom_Direction> IGESSolid_ToroidalSurface::ReferenceDir() const
{
  return theRefDir;
}

bool IGESSolid_ToroidalSurface::IsParametrised() const
{
  return !(theRefDir.IsNull());
}
