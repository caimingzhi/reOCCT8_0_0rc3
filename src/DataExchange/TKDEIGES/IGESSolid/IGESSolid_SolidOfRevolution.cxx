#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_SolidOfRevolution.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_SolidOfRevolution, IGESData_IGESEntity)

IGESSolid_SolidOfRevolution::IGESSolid_SolidOfRevolution() = default;

void IGESSolid_SolidOfRevolution::Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                                       const double                            Fract,
                                       const gp_XYZ&                           AxisPnt,
                                       const gp_XYZ&                           Direction)
{
  theCurve     = aCurve;
  theFraction  = Fract;
  theAxisPoint = AxisPnt;
  theAxis      = Direction;
  InitTypeAndForm(162, FormNumber());
}

void IGESSolid_SolidOfRevolution::SetClosedToAxis(const bool F)
{
  InitTypeAndForm(162, (F ? 0 : 1));
}

bool IGESSolid_SolidOfRevolution::IsClosedToAxis() const
{
  return (FormNumber() == 0);
}

occ::handle<IGESData_IGESEntity> IGESSolid_SolidOfRevolution::Curve() const
{
  return theCurve;
}

double IGESSolid_SolidOfRevolution::Fraction() const
{
  return theFraction;
}

gp_Pnt IGESSolid_SolidOfRevolution::AxisPoint() const
{
  return gp_Pnt(theAxisPoint);
}

gp_Pnt IGESSolid_SolidOfRevolution::TransformedAxisPoint() const
{
  if (!HasTransf())
    return gp_Pnt(theAxisPoint);
  else
  {
    gp_XYZ tmp = theAxisPoint;
    Location().Transforms(tmp);
    return gp_Pnt(tmp);
  }
}

gp_Dir IGESSolid_SolidOfRevolution::Axis() const
{
  return gp_Dir(theAxis);
}

gp_Dir IGESSolid_SolidOfRevolution::TransformedAxis() const
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
