#include <gp_GTrsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_Direction.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_Direction, IGESData_IGESEntity)

IGESGeom_Direction::IGESGeom_Direction() = default;

void IGESGeom_Direction::Init(const gp_XYZ& aDirection)
{
  theDirection = aDirection;
  InitTypeAndForm(123, 0);
}

gp_Vec IGESGeom_Direction::Value() const
{
  gp_Vec direction(theDirection);
  return direction;
}

gp_Vec IGESGeom_Direction::TransformedValue() const
{
  if (!HasTransf())
    return gp_Vec(theDirection);
  gp_XYZ   xyz(theDirection);
  gp_GTrsf loc = Location();
  loc.SetTranslationPart(gp_XYZ(0., 0., 0.));
  loc.Transforms(xyz);
  return gp_Vec(xyz);
}
