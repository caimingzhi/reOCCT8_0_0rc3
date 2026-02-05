#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <IGESDimen_BasicDimension.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_BasicDimension, IGESData_IGESEntity)

IGESDimen_BasicDimension::IGESDimen_BasicDimension() = default;

void IGESDimen_BasicDimension::Init(const int    nbPropVal,
                                    const gp_XY& thell,
                                    const gp_XY& thelr,
                                    const gp_XY& theur,
                                    const gp_XY& theul)
{
  theNbPropertyValues = nbPropVal;
  theLowerLeft        = thell;
  theLowerRight       = thelr;
  theUpperRight       = theur;
  theUpperLeft        = theul;
  InitTypeAndForm(406, 31);
}

int IGESDimen_BasicDimension::NbPropertyValues() const
{
  return theNbPropertyValues;
}

gp_Pnt2d IGESDimen_BasicDimension::LowerLeft() const
{
  gp_Pnt2d g(theLowerLeft);
  return g;
}

gp_Pnt2d IGESDimen_BasicDimension::LowerRight() const
{
  gp_Pnt2d g(theLowerRight);
  return g;
}

gp_Pnt2d IGESDimen_BasicDimension::UpperRight() const
{
  gp_Pnt2d g(theUpperRight);
  return g;
}

gp_Pnt2d IGESDimen_BasicDimension::UpperLeft() const
{
  gp_Pnt2d g(theUpperLeft);
  return g;
}
