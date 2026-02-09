#include <gp_GTrsf.hpp>
#include <gp_XYZ.hpp>
#include <IGESSolid_SolidOfLinearExtrusion.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_SolidOfLinearExtrusion, IGESData_IGESEntity)

IGESSolid_SolidOfLinearExtrusion::IGESSolid_SolidOfLinearExtrusion() = default;

void IGESSolid_SolidOfLinearExtrusion::Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                                            const double                            Length,
                                            const gp_XYZ&                           Direction)
{
  theCurve     = aCurve;
  theLength    = Length;
  theDirection = Direction;
  InitTypeAndForm(164, 0);
}

occ::handle<IGESData_IGESEntity> IGESSolid_SolidOfLinearExtrusion::Curve() const
{
  return theCurve;
}

double IGESSolid_SolidOfLinearExtrusion::ExtrusionLength() const
{
  return theLength;
}

gp_Dir IGESSolid_SolidOfLinearExtrusion::ExtrusionDirection() const
{
  return gp_Dir(theDirection);
}

gp_Dir IGESSolid_SolidOfLinearExtrusion::TransformedExtrusionDirection() const
{
  if (!HasTransf())
    return gp_Dir(theDirection);
  else
  {
    gp_XYZ   tmp = theDirection;
    gp_GTrsf loc = Location();
    loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
    loc.Transforms(tmp);
    return gp_Dir(tmp);
  }
}
