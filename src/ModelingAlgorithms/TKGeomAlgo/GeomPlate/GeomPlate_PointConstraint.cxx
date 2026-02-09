#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <GeomAPI_ProjectPointOnSurf.hpp>
#include <GeomPlate_PointConstraint.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomPlate_PointConstraint, Standard_Transient)

GeomPlate_PointConstraint::GeomPlate_PointConstraint(const gp_Pnt& Pt,
                                                     const int     Order,
                                                     const double  TolDist)
    : myOrder(Order),
      myLProp(2, TolDist),
      myPoint(Pt),
      myU(0.0),
      myV(0.0),
      myTolDist(TolDist),
      myTolAng(0.0),
      myTolCurv(0.0),
      hasPnt2dOnSurf(false)
{
  if ((myOrder > 1) || (myOrder < -1))
    throw Standard_Failure("GeomPlate_PointConstraint : the constraint must 0 or -1 with a point");
}

GeomPlate_PointConstraint::GeomPlate_PointConstraint(const double                     U,
                                                     const double                     V,
                                                     const occ::handle<Geom_Surface>& Surf,
                                                     const int                        Order,
                                                     const double                     TolDist,
                                                     const double                     TolAng,
                                                     const double                     TolCurv)
    : myOrder(Order),
      myLProp(2, TolDist),
      mySurf(Surf),
      myU(U),
      myV(V),
      myTolDist(TolDist),
      myTolAng(TolAng),
      myTolCurv(TolCurv),
      hasPnt2dOnSurf(false)

{
  Surf->D2(myU, myV, myPoint, myD11, myD12, myD21, myD22, myD23);
  myLProp.SetSurface(Surf);
}

void GeomPlate_PointConstraint::D0(gp_Pnt& P) const
{
  P = myPoint;
}

void GeomPlate_PointConstraint::D1(gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  P  = myPoint;
  V1 = myD11;
  V2 = myD12;
}

void GeomPlate_PointConstraint::D2(gp_Pnt& P,
                                   gp_Vec& V1,
                                   gp_Vec& V2,
                                   gp_Vec& V3,
                                   gp_Vec& V4,
                                   gp_Vec& V5) const
{
  P  = myPoint;
  V1 = myD11;
  V2 = myD12;
  V3 = myD21;
  V4 = myD22;
  V5 = myD23;
}

void GeomPlate_PointConstraint ::SetG0Criterion(const double TolDist)
{
  myTolDist = TolDist;
}

void GeomPlate_PointConstraint ::SetG1Criterion(const double TolAng)
{
  myTolAng = TolAng;
}

void GeomPlate_PointConstraint ::SetG2Criterion(const double TolCurv)
{
  myTolCurv = TolCurv;
}

double GeomPlate_PointConstraint::G0Criterion() const
{
  return myTolDist;
}

double GeomPlate_PointConstraint::G1Criterion() const
{
  return myTolAng;
}

double GeomPlate_PointConstraint::G2Criterion() const
{
  return myTolCurv;
}

GeomLProp_SLProps& GeomPlate_PointConstraint::LPropSurf()
{

  myLProp.SetParameters(myU, myV);
  return myLProp;
}

int GeomPlate_PointConstraint::Order() const
{
  return myOrder;
}

void GeomPlate_PointConstraint::SetOrder(const int Order)
{
  myOrder = Order;
}

bool GeomPlate_PointConstraint::HasPnt2dOnSurf() const
{
  return hasPnt2dOnSurf;
}

void GeomPlate_PointConstraint::SetPnt2dOnSurf(const gp_Pnt2d& Pnt2d)
{
  myPt2d         = Pnt2d;
  hasPnt2dOnSurf = true;
}

gp_Pnt2d GeomPlate_PointConstraint::Pnt2dOnSurf() const
{
  return myPt2d;
}
