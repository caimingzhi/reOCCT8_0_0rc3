#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESBasic_SubfigureDef.hpp>
#include <IGESGeom_Point.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_Point, IGESData_IGESEntity)

IGESGeom_Point::IGESGeom_Point() = default;

void IGESGeom_Point::Init(const gp_XYZ& aPoint, const occ::handle<IGESBasic_SubfigureDef>& aSymbol)
{
  thePoint  = aPoint;
  theSymbol = aSymbol;
  InitTypeAndForm(116, 0);
}

gp_Pnt IGESGeom_Point::Value() const
{
  return gp_Pnt(thePoint);
}

gp_Pnt IGESGeom_Point::TransformedValue() const
{
  gp_XYZ Val = thePoint;
  if (HasTransf())
    Location().Transforms(Val);
  gp_Pnt transVal(Val);
  return transVal;
}

bool IGESGeom_Point::HasDisplaySymbol() const
{
  return (!theSymbol.IsNull());
}

occ::handle<IGESBasic_SubfigureDef> IGESGeom_Point::DisplaySymbol() const
{
  return theSymbol;
}
