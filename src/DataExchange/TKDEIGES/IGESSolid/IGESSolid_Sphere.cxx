#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_Sphere.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Sphere, IGESData_IGESEntity)

IGESSolid_Sphere::IGESSolid_Sphere() = default;

void IGESSolid_Sphere::Init(const double aRadius, const gp_XYZ& aCenter)
{
  theRadius = aRadius;
  theCenter = aCenter; // default (0,0,0)
  InitTypeAndForm(158, 0);
}

double IGESSolid_Sphere::Radius() const
{
  return theRadius;
}

gp_Pnt IGESSolid_Sphere::Center() const
{
  return gp_Pnt(theCenter);
}

gp_Pnt IGESSolid_Sphere::TransformedCenter() const
{
  if (!HasTransf())
    return gp_Pnt(theCenter);
  else
  {
    gp_XYZ tmp = theCenter;
    Location().Transforms(tmp);
    return gp_Pnt(tmp);
  }
}
