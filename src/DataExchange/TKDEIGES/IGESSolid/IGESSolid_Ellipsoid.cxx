#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_Ellipsoid.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Ellipsoid, IGESData_IGESEntity)

IGESSolid_Ellipsoid::IGESSolid_Ellipsoid() = default;

void IGESSolid_Ellipsoid::Init(const gp_XYZ& aSize,
                               const gp_XYZ& aCenter,
                               const gp_XYZ& anXAxis,
                               const gp_XYZ& anZAxis)
{
  theSize   = aSize;
  theCenter = aCenter;
  theXAxis  = anXAxis;
  theZAxis  = anZAxis;
  InitTypeAndForm(168, 0);
}

gp_XYZ IGESSolid_Ellipsoid::Size() const
{
  return theSize;
}

double IGESSolid_Ellipsoid::XLength() const
{
  return theSize.X();
}

double IGESSolid_Ellipsoid::YLength() const
{
  return theSize.Y();
}

double IGESSolid_Ellipsoid::ZLength() const
{
  return theSize.Z();
}

gp_Pnt IGESSolid_Ellipsoid::Center() const
{
  return gp_Pnt(theCenter);
}

gp_Pnt IGESSolid_Ellipsoid::TransformedCenter() const
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

gp_Dir IGESSolid_Ellipsoid::XAxis() const
{
  return gp_Dir(theXAxis);
}

gp_Dir IGESSolid_Ellipsoid::TransformedXAxis() const
{
  if (!HasTransf())
    return gp_Dir(theXAxis);
  else
  {
    gp_XYZ   tmp = theXAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(tmp);
    return gp_Dir(tmp);
  }
}

gp_Dir IGESSolid_Ellipsoid::YAxis() const
{
  return gp_Dir(theXAxis ^ theZAxis);
}

gp_Dir IGESSolid_Ellipsoid::TransformedYAxis() const
{
  if (!HasTransf())
    return gp_Dir(theXAxis ^ theZAxis);
  else
  {
    gp_XYZ   tmp = theXAxis ^ theZAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(tmp);
    return gp_Dir(tmp);
  }
}

gp_Dir IGESSolid_Ellipsoid::ZAxis() const
{
  return gp_Dir(theZAxis);
}

gp_Dir IGESSolid_Ellipsoid::TransformedZAxis() const
{
  if (!HasTransf())
    return gp_Dir(theZAxis);
  else
  {
    gp_XYZ   tmp = theZAxis;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(tmp);
    return gp_Dir(tmp);
  }
}
