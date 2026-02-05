#include <gp_GTrsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_OffsetSurface.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_OffsetSurface, IGESData_IGESEntity)

IGESGeom_OffsetSurface::IGESGeom_OffsetSurface() = default;

void IGESGeom_OffsetSurface::Init(const gp_XYZ&                           anIndicator,
                                  const double                            aDistance,
                                  const occ::handle<IGESData_IGESEntity>& aSurface)
{
  theIndicator = anIndicator;
  theDistance  = aDistance;
  theSurface   = aSurface;
  InitTypeAndForm(140, 0);
}

gp_Vec IGESGeom_OffsetSurface::OffsetIndicator() const
{
  return gp_Vec(theIndicator);
}

gp_Vec IGESGeom_OffsetSurface::TransformedOffsetIndicator() const
{
  if (!HasTransf())
    return gp_Vec(theIndicator);
  gp_XYZ   temp(theIndicator);
  gp_GTrsf loc = Location();
  loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
  loc.Transforms(temp);
  return gp_Vec(temp);
}

double IGESGeom_OffsetSurface::Distance() const
{
  return theDistance;
}

occ::handle<IGESData_IGESEntity> IGESGeom_OffsetSurface::Surface() const
{
  return theSurface;
}
