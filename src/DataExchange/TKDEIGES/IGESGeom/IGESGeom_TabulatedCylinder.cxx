#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_TabulatedCylinder.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_TabulatedCylinder, IGESData_IGESEntity)

IGESGeom_TabulatedCylinder::IGESGeom_TabulatedCylinder() = default;

void IGESGeom_TabulatedCylinder::Init(const occ::handle<IGESData_IGESEntity>& aDirectrix,
                                      const gp_XYZ&                           anEnd)
{
  theDirectrix = aDirectrix;
  theEnd       = anEnd;
  InitTypeAndForm(122, 0);
}

occ::handle<IGESData_IGESEntity> IGESGeom_TabulatedCylinder::Directrix() const
{
  return theDirectrix;
}

gp_Pnt IGESGeom_TabulatedCylinder::EndPoint() const
{
  return (gp_Pnt(theEnd));
}

gp_Pnt IGESGeom_TabulatedCylinder::TransformedEndPoint() const
{
  gp_XYZ EndPoint = theEnd;
  if (HasTransf())
    Location().Transforms(EndPoint);
  return (gp_Pnt(EndPoint));
}
