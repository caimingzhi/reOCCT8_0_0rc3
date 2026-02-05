#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_Cylinder.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Cylinder, IGESData_IGESEntity)

IGESSolid_Cylinder::IGESSolid_Cylinder() = default;

void IGESSolid_Cylinder::Init(const double  aHeight,
                              const double  aRadius,
                              const gp_XYZ& aCenter,
                              const gp_XYZ& anAxis)
{
  theHeight     = aHeight;
  theRadius     = aRadius;
  theFaceCenter = aCenter;
  theAxis       = anAxis;
  InitTypeAndForm(154, 0);
}

double IGESSolid_Cylinder::Height() const
{
  return theHeight;
}

double IGESSolid_Cylinder::Radius() const
{
  return theRadius;
}

gp_Pnt IGESSolid_Cylinder::FaceCenter() const
{
  return gp_Pnt(theFaceCenter);
}

gp_Pnt IGESSolid_Cylinder::TransformedFaceCenter() const
{
  if (!HasTransf())
    return gp_Pnt(theFaceCenter);
  else
  {
    gp_XYZ tmp = theFaceCenter;
    Location().Transforms(tmp);
    return gp_Pnt(tmp);
  }
}

gp_Dir IGESSolid_Cylinder::Axis() const
{
  return gp_Dir(theAxis);
}

gp_Dir IGESSolid_Cylinder::TransformedAxis() const
{
  if (!HasTransf())
    return gp_Dir(theAxis);
  else
  {
    gp_XYZ   tmp = theAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(tmp);
    return gp_Dir(tmp);
  }
}
