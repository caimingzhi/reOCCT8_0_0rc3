#include <Approx_Curve2d.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomPlate_CurveConstraint.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Law_Function.hpp>
#include <ProjLib_ProjectedCurve.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomPlate_CurveConstraint, Standard_Transient)

GeomPlate_CurveConstraint ::GeomPlate_CurveConstraint()
    : myNbPoints(0),
      myOrder(0),
      myTang(0),
      myConstG0(false),
      myConstG1(false),
      myConstG2(false),
      myLProp(2, 1.e-4),
      myTolDist(0.0),
      myTolAng(0.0),
      myTolCurv(0.0),
      myTolU(0.0),
      myTolV(0.0)
{
}

GeomPlate_CurveConstraint ::GeomPlate_CurveConstraint(const occ::handle<Adaptor3d_Curve>& Boundary,
                                                      const int                           Tang,
                                                      const int                           NPt,
                                                      const double                        TolDist,
                                                      const double                        TolAng,
                                                      const double                        TolCurv)
    : myLProp(2, TolDist),
      myTolDist(TolDist),
      myTolAng(TolAng),
      myTolCurv(TolCurv)
{
  myOrder = Tang;
  if ((Tang < -1) || (Tang > 2))
    throw Standard_Failure("GeomPlate : The continuity is not G0 G1 or G2");
  myNbPoints = NPt;
  myConstG0  = true;
  myConstG1  = true;
  myConstG2  = true;

  myFrontiere = occ::down_cast<Adaptor3d_CurveOnSurface>(Boundary);

  if (myFrontiere.IsNull())
  {
    my3dCurve = Boundary;
  }
  else
  {
    occ::handle<Geom_Surface>        Surf;
    occ::handle<GeomAdaptor_Surface> GS1 =
      occ::down_cast<GeomAdaptor_Surface>(myFrontiere->GetSurface());

    if (!GS1.IsNull())
    {
      Surf = GS1->Surface();
    }
    else
    {

      throw Standard_Failure("GeomPlate_CurveConstraint : Surface must be GeomAdaptor_Surface");
    }

    myLProp.SetSurface(Surf);
  }

  my2dCurve.Nullify();
  myHCurve2d.Nullify();
  myTolU = 0.;
  myTolV = 0.;
  myG0Crit.Nullify();
  myG1Crit.Nullify();
  myG2Crit.Nullify();
}

double GeomPlate_CurveConstraint ::FirstParameter() const
{
  if (!myHCurve2d.IsNull())
    return myHCurve2d->FirstParameter();
  else if (my3dCurve.IsNull())
    return myFrontiere->FirstParameter();
  else
    return my3dCurve->FirstParameter();
}

double GeomPlate_CurveConstraint ::LastParameter() const
{
  if (!myHCurve2d.IsNull())
    return myHCurve2d->LastParameter();
  else if (my3dCurve.IsNull())
    return myFrontiere->LastParameter();
  else
    return my3dCurve->LastParameter();
}

double GeomPlate_CurveConstraint ::Length() const
{
  GCPnts_AbscissaPoint AP;
  if (my3dCurve.IsNull())
  {

    return GCPnts_AbscissaPoint::Length(*myFrontiere);
  }
  else
  {

    return GCPnts_AbscissaPoint::Length(*my3dCurve);
  }
}

void GeomPlate_CurveConstraint ::D0(const double U, gp_Pnt& P) const
{
  gp_Pnt2d P2d;

  if (my3dCurve.IsNull())
  {
    P2d = myFrontiere->GetCurve()->Value(U);
    myFrontiere->GetSurface()->D0(P2d.Coord(1), P2d.Coord(2), P);
  }
  else
    my3dCurve->D0(U, P);
}

void GeomPlate_CurveConstraint ::D1(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  gp_Pnt2d P2d;
  if (!my3dCurve.IsNull())
    throw Standard_Failure("GeomPlate_CurveConstraint.cxx : Curve must be on a Surface");

  P2d = myFrontiere->GetCurve()->Value(U);
  myFrontiere->GetSurface()->D1(P2d.Coord(1), P2d.Coord(2), P, V1, V2);
}

void GeomPlate_CurveConstraint ::D2(const double U,
                                    gp_Pnt&      P,
                                    gp_Vec&      V1,
                                    gp_Vec&      V2,
                                    gp_Vec&      V3,
                                    gp_Vec&      V4,
                                    gp_Vec&      V5) const
{
  gp_Pnt2d P2d;
  if (!my3dCurve.IsNull())
    throw Standard_Failure("GeomPlate_CurveConstraint.cxx : Curve must be on a Surface");

  P2d = myFrontiere->GetCurve()->Value(U);
  myFrontiere->GetSurface()->D2(P2d.Coord(1), P2d.Coord(2), P, V1, V2, V3, V4, V5);
}

void GeomPlate_CurveConstraint ::SetG0Criterion(const occ::handle<Law_Function>& G0Crit)
{
  myG0Crit  = G0Crit;
  myConstG0 = false;
}

void GeomPlate_CurveConstraint ::SetG1Criterion(const occ::handle<Law_Function>& G1Crit)
{
  if (!my3dCurve.IsNull())
    throw Standard_Failure("GeomPlate_CurveConstraint.cxx : Curve must be on a Surface");
  myG1Crit  = G1Crit;
  myConstG1 = false;
}

void GeomPlate_CurveConstraint ::SetG2Criterion(const occ::handle<Law_Function>& G2Crit)
{
  if (!my3dCurve.IsNull())
    throw Standard_Failure("GeomPlate_CurveConstraint.cxx : Curve must be on a Surface");
  myG2Crit  = G2Crit;
  myConstG2 = false;
}

double GeomPlate_CurveConstraint ::G0Criterion(const double U) const
{
  if (myConstG0)
    return myTolDist;
  else
    return myG0Crit->Value(U);
}

double GeomPlate_CurveConstraint ::G1Criterion(const double U) const
{
  if (!my3dCurve.IsNull())
    throw Standard_Failure("GeomPlate_CurveConstraint.cxx : Curve must be on a Surface");
  if (myConstG1)
    return myTolAng;
  else
    return myG1Crit->Value(U);
}

double GeomPlate_CurveConstraint ::G2Criterion(const double U) const
{
  if (!my3dCurve.IsNull())
    throw Standard_Failure("GeomPlate_CurveConstraint.cxx : Curve must be on a Surface");
  if (myConstG2)
    return myTolCurv;
  else
    return myG2Crit->Value(U);
}

occ::handle<Geom2d_Curve> GeomPlate_CurveConstraint ::Curve2dOnSurf() const
{
  if (my2dCurve.IsNull() && !myHCurve2d.IsNull())
  {
    occ::handle<Geom2d_Curve> C2d;
    GeomAbs_Shape             Continuity = GeomAbs_C1;
    int                       MaxDegree  = 10;
    int                       MaxSeg     = 20 + myHCurve2d->NbIntervals(GeomAbs_C3);
    Approx_Curve2d            appr(myHCurve2d,
                        myHCurve2d->FirstParameter(),
                        myHCurve2d->LastParameter(),
                        myTolU,
                        myTolV,
                        Continuity,
                        MaxDegree,
                        MaxSeg);
    C2d = appr.Curve();
    return C2d;
  }
  else
    return my2dCurve;
}

void GeomPlate_CurveConstraint ::SetCurve2dOnSurf(const occ::handle<Geom2d_Curve>& Curve)
{
  my2dCurve = Curve;
}

occ::handle<Adaptor2d_Curve2d> GeomPlate_CurveConstraint ::ProjectedCurve() const
{
  return myHCurve2d;
}

void GeomPlate_CurveConstraint ::SetProjectedCurve(const occ::handle<Adaptor2d_Curve2d>& Curve,
                                                   const double                          TolU,
                                                   const double                          TolV)
{
  myHCurve2d = Curve;
  myTolU     = TolU;
  myTolV     = TolV;
}

occ::handle<Adaptor3d_Curve> GeomPlate_CurveConstraint ::Curve3d() const
{
  if (my3dCurve.IsNull())
    return occ::handle<Adaptor3d_Curve>(myFrontiere);
  else
    return my3dCurve;
}

int GeomPlate_CurveConstraint::NbPoints() const
{
  return myNbPoints;
}

int GeomPlate_CurveConstraint::Order() const
{
  return myOrder;
}

void GeomPlate_CurveConstraint::SetNbPoints(const int NewNb)
{
  myNbPoints = NewNb;
}

void GeomPlate_CurveConstraint::SetOrder(const int Order)
{
  myOrder = Order;
}

GeomLProp_SLProps& GeomPlate_CurveConstraint::LPropSurf(const double U)
{
  if (myFrontiere.IsNull())
    throw Standard_Failure("GeomPlate_CurveConstraint.cxx : Curve must be on a Surface");
  gp_Pnt2d P2d = myFrontiere->GetCurve()->Value(U);
  myLProp.SetParameters(P2d.X(), P2d.Y());
  return myLProp;
}
