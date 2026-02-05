#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESGeom_Flash.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_Flash, IGESData_IGESEntity)

IGESGeom_Flash::IGESGeom_Flash() = default;

void IGESGeom_Flash::Init(const gp_XY&                            aPoint,
                          const double                            aDim1,
                          const double                            aDim2,
                          const double                            aRotation,
                          const occ::handle<IGESData_IGESEntity>& aReference)
{
  thePoint     = aPoint;
  theDim1      = aDim1;
  theDim2      = aDim2;
  theRotation  = aRotation;
  theReference = aReference;
  InitTypeAndForm(125, FormNumber());
  // FormNumber : 0-4, Shape of the Flash
}

void IGESGeom_Flash::SetFormNumber(const int form)
{
  if (form < 0 || form > 4)
    throw Standard_OutOfRange("IGESGeom_Flash : SetFormNumber");
  InitTypeAndForm(125, form);
}

gp_Pnt2d IGESGeom_Flash::ReferencePoint() const
{
  return (gp_Pnt2d(thePoint));
}

gp_Pnt IGESGeom_Flash::TransformedReferencePoint() const
{
  gp_XYZ Point(thePoint.X(), thePoint.Y(), 0.0);
  if (HasTransf())
    Location().Transforms(Point);
  return gp_Pnt(Point);
}

double IGESGeom_Flash::Dimension1() const
{
  return theDim1;
}

double IGESGeom_Flash::Dimension2() const
{
  return theDim2;
}

double IGESGeom_Flash::Rotation() const
{
  return theRotation;
}

bool IGESGeom_Flash::HasReferenceEntity() const
{
  return (!theReference.IsNull());
}

occ::handle<IGESData_IGESEntity> IGESGeom_Flash::ReferenceEntity() const
{
  return theReference;
}
