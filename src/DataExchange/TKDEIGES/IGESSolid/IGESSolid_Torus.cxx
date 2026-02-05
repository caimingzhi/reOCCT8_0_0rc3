#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_Torus.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Torus, IGESData_IGESEntity)

IGESSolid_Torus::IGESSolid_Torus() = default;

void IGESSolid_Torus::Init(const double  R1,
                           const double  R2,
                           const gp_XYZ& Point,
                           const gp_XYZ& Axisdir)
{
  theR1    = R1;
  theR2    = R2;
  thePoint = Point;   // default (0,0,0)
  theAxis  = Axisdir; // default (0,0,1)
  InitTypeAndForm(160, 0);
}

double IGESSolid_Torus::MajorRadius() const
{
  return theR1;
}

double IGESSolid_Torus::DiscRadius() const
{
  return theR2;
}

gp_Pnt IGESSolid_Torus::AxisPoint() const
{
  return gp_Pnt(thePoint);
}

gp_Pnt IGESSolid_Torus::TransformedAxisPoint() const
{
  if (!HasTransf())
    return gp_Pnt(thePoint);
  else
  {
    gp_XYZ pnt = thePoint;
    Location().Transforms(pnt);
    return gp_Pnt(pnt);
  }
}

gp_Dir IGESSolid_Torus::Axis() const
{
  return gp_Dir(theAxis);
}

gp_Dir IGESSolid_Torus::TransformedAxis() const
{
  if (!HasTransf())
    return gp_Dir(theAxis);
  else
  {
    gp_XYZ   pnt = theAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(pnt);
    return gp_Dir(pnt);
  }
}
