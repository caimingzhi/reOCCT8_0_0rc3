#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_ConeFrustum.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_ConeFrustum, IGESData_IGESEntity)

IGESSolid_ConeFrustum::IGESSolid_ConeFrustum() = default;

void IGESSolid_ConeFrustum::Init(const double  Ht,
                                 const double  R1,
                                 const double  R2,
                                 const gp_XYZ& Center,
                                 const gp_XYZ& anAxis)
{
  theHeight     = Ht;
  theR1         = R1;
  theR2         = R2;
  theFaceCenter = Center;
  theAxis       = anAxis;
  InitTypeAndForm(156, 0);
}

double IGESSolid_ConeFrustum::Height() const
{
  return theHeight;
}

double IGESSolid_ConeFrustum::LargerRadius() const
{
  return theR1;
}

double IGESSolid_ConeFrustum::SmallerRadius() const
{
  return theR2;
}

gp_Pnt IGESSolid_ConeFrustum::FaceCenter() const
{
  return gp_Pnt(theFaceCenter);
}

gp_Pnt IGESSolid_ConeFrustum::TransformedFaceCenter() const
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

gp_Dir IGESSolid_ConeFrustum::Axis() const
{
  return gp_Dir(theAxis);
}

gp_Dir IGESSolid_ConeFrustum::TransformedAxis() const
{
  if (!HasTransf())
    return gp_Dir(theAxis);
  else
  {
    gp_XYZ   xyz = theAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(xyz);
    return gp_Dir(xyz);
  }
}
