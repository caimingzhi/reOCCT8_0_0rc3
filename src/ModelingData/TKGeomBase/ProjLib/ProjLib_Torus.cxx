#include <gp.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <ProjLib_Torus.hpp>

ProjLib_Torus::ProjLib_Torus() = default;

ProjLib_Torus::ProjLib_Torus(const gp_Torus& To)
{
  Init(To);
}

ProjLib_Torus::ProjLib_Torus(const gp_Torus& To, const gp_Circ& C)
{
  Init(To);
  Project(C);
}

void ProjLib_Torus::Init(const gp_Torus& To)
{
  myType       = GeomAbs_OtherCurve;
  myTorus      = To;
  myIsPeriodic = false;
  isDone       = false;
}

static gp_Pnt2d EvalPnt2d(const gp_Vec& Ve, const gp_Torus& To)
{
  double X = Ve.Dot(gp_Vec(To.Position().XDirection()));
  double Y = Ve.Dot(gp_Vec(To.Position().YDirection()));
  double U, V;

  if (std::abs(X) > Precision::PConfusion() || std::abs(Y) > Precision::PConfusion())
  {
    U = std::atan2(Y, X);
  }
  else
  {
    U = 0.;
  }

  V = 0.;

  return gp_Pnt2d(U, V);
}

void ProjLib_Torus::Project(const gp_Circ& C)
{
  myType = GeomAbs_Line;

  gp_Vec Xc(C.Position().XDirection());
  gp_Vec Yc(C.Position().YDirection());
  gp_Vec Xt(myTorus.Position().XDirection());
  gp_Vec Yt(myTorus.Position().YDirection());
  gp_Vec Zt(myTorus.Position().Direction());
  gp_Vec OC(myTorus.Location(), C.Location());

  if (OC.Magnitude() < Precision::Confusion()
      || C.Position().Direction().IsParallel(myTorus.Position().Direction(), Precision::Angular()))
  {

    gp_Pnt2d P1 = EvalPnt2d(Xc, myTorus);
    gp_Pnt2d P2 = EvalPnt2d(Yc, myTorus);
    double   Z  = OC.Dot(myTorus.Position().Direction());
    Z /= myTorus.MinorRadius();

    double V;

    if (Z > 1.)
    {
      V = M_PI / 2.;
    }
    else if (Z < -1.)
    {
      V = -M_PI / 2;
    }
    else
    {
      V = std::asin(Z);
    }

    if (C.Radius() < myTorus.MajorRadius())
    {
      V = M_PI - V;
    }
    else if (V < 0.)
    {
      V += 2 * M_PI;
    }
    P1.SetY(V);
    P2.SetY(V);
    gp_Vec2d V2d(P1, P2);

    if (std::abs(P1.X() - P2.X()) > M_PI)
      V2d.Reverse();

    gp_Dir2d D2(V2d);
    if (P1.X() < 0)
      P1.SetX(2 * M_PI + P1.X());
    myLin = gp_Lin2d(P1, D2);
  }
  else
  {

    double U = Xt.AngleWithRef(OC, Xt ^ Yt);
    if (U < 0.)
      U += 2 * M_PI;

    double V1 = OC.AngleWithRef(Xc, OC ^ Zt);
    if (V1 < 0.)
      V1 += 2 * M_PI;

    gp_Pnt2d P1(U, V1);

    gp_Dir2d D2 = gp::DY2d();
    if (((OC ^ Zt) * (Xc ^ Yc)) < 0.)
    {
      D2.Reverse();
    }

    myLin = gp_Lin2d(P1, D2);
  }
  isDone = true;
}

void ProjLib_Torus::Project(const gp_Lin& L)
{
  ProjLib_Projector::Project(L);
}

void ProjLib_Torus::Project(const gp_Elips& E)
{
  ProjLib_Projector::Project(E);
}

void ProjLib_Torus::Project(const gp_Parab& P)
{
  ProjLib_Projector::Project(P);
}

void ProjLib_Torus::Project(const gp_Hypr& H)
{
  ProjLib_Projector::Project(H);
}
