#include <ElCLib.hpp>
#include <gp.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <ProjLib_Sphere.hpp>
#include <Standard_NotImplemented.hpp>
#include <StdFail_NotDone.hpp>

ProjLib_Sphere::ProjLib_Sphere() = default;

ProjLib_Sphere::ProjLib_Sphere(const gp_Sphere& Sp)
{
  Init(Sp);
}

ProjLib_Sphere::ProjLib_Sphere(const gp_Sphere& Sp, const gp_Circ& C)
{
  Init(Sp);
  Project(C);
}

void ProjLib_Sphere::Init(const gp_Sphere& Sp)
{
  myType       = GeomAbs_OtherCurve;
  mySphere     = Sp;
  myIsPeriodic = false;
  isDone       = false;
}

static gp_Pnt2d EvalPnt2d(const gp_Vec& P, const gp_Sphere& Sp)
{
  double X = P.Dot(gp_Vec(Sp.Position().XDirection()));
  double Y = P.Dot(gp_Vec(Sp.Position().YDirection()));
  double Z = P.Dot(gp_Vec(Sp.Position().Direction()));
  double U, V;

  if (std::abs(X) > Precision::PConfusion() || std::abs(Y) > Precision::PConfusion())
  {
    double UU = std::atan2(Y, X);
    U         = ElCLib::InPeriod(UU, 0., 2 * M_PI);
  }
  else
  {
    U = 0.;
  }

  if (Z > 1.)
    Z = 1.;
  else if (Z < -1.)
    Z = -1.;
  V = std::asin(Z);

  return gp_Pnt2d(U, V);
}

void ProjLib_Sphere::Project(const gp_Circ& C)
{
  gp_Pnt O;
  gp_Dir Xc, Yc, Zc;
  gp_Dir Xs, Ys, Zs;

  O  = mySphere.Location();
  Xc = C.Position().XDirection();
  Yc = C.Position().YDirection();
  Zc = Xc ^ Yc;
  Xs = mySphere.Position().XDirection();
  Ys = mySphere.Position().YDirection();
  Zs = mySphere.Position().Direction();

  bool             isIsoU, isIsoV;
  constexpr double Tol = Precision::Confusion();

  isIsoU = Zc.IsNormal(Zs, Tol) && O.IsEqual(C.Location(), Tol);
  isIsoV = Xc.IsNormal(Zs, Tol) && Yc.IsNormal(Zs, Tol);

  gp_Pnt2d P2d1, P2d2;
  gp_Dir2d D2d;

  if (isIsoU)
  {
    myType = GeomAbs_Line;

    P2d1 = EvalPnt2d(gp_Vec(Xc), mySphere);
    P2d2 = EvalPnt2d(gp_Vec(Yc), mySphere);

    if (isIsoU
        && (std::abs(P2d1.Y() - M_PI / 2.) < Precision::PConfusion()
            || std::abs(P2d1.Y() + M_PI / 2.) < Precision::PConfusion()))
    {

      P2d1.SetX(P2d2.X());
    }
    else if (std::abs(std::abs(P2d1.X() - P2d2.X()) - M_PI) < Precision::PConfusion())
    {

      P2d2.SetX(P2d1.X());
      if (P2d2.Y() < 0.)
        P2d2.SetY(-M_PI - P2d2.Y());
      else
        P2d2.SetY(M_PI - P2d2.Y());
    }
    else
    {
      P2d2.SetX(P2d1.X());
    }

    D2d    = gp_Dir2d(gp_Vec2d(P2d1, P2d2));
    isDone = true;
  }
  else if (isIsoV)
  {
    myType = GeomAbs_Line;

    double U = Xs.AngleWithRef(Xc, Xs ^ Ys);
    if (U < 0)
      U += 2 * M_PI;
    double Z = gp_Vec(O, C.Location()).Dot(Zs);
    double V = std::asin(Z / mySphere.Radius());
    P2d1     = gp_Pnt2d(U, V);
    D2d      = gp_Dir2d((Xc ^ Yc).Dot(Xs ^ Ys), 0.);
    isDone   = true;
  }
  myLin = gp_Lin2d(P2d1, D2d);
}

void ProjLib_Sphere::Project(const gp_Lin& L)
{
  ProjLib_Projector::Project(L);
}

void ProjLib_Sphere::Project(const gp_Elips& E)
{
  ProjLib_Projector::Project(E);
}

void ProjLib_Sphere::Project(const gp_Parab& P)
{
  ProjLib_Projector::Project(P);
}

void ProjLib_Sphere::Project(const gp_Hypr& H)
{
  ProjLib_Projector::Project(H);
}

void ProjLib_Sphere::SetInBounds(const double U)
{
  StdFail_NotDone_Raise_if(!isDone, "ProjLib_Sphere:SetInBounds");

  double newY, Y = ElCLib::Value(U, myLin).Y();
  newY = ElCLib::InPeriod(Y, -M_PI, M_PI);

  myLin.Translate(gp_Vec2d(0., newY - Y));

  gp_Pnt2d  P = ElCLib::Value(U, myLin);
  gp_Trsf2d Trsf;
  gp_Ax2d   Axis;
  double    Tol = 1.e-7;
  gp_Dir2d  D2d = myLin.Direction();

  if ((P.Y() - M_PI / 2 > Tol) ||

      (std::abs(P.Y() - M_PI / 2) < Tol && D2d.IsEqual(gp::DY2d(), Tol)))
  {
    Axis = gp_Ax2d(gp_Pnt2d(0., M_PI / 2.), gp::DX2d());
  }

  else if ((P.Y() + M_PI / 2 < -Tol) ||

           (std::abs(P.Y() + M_PI / 2) < Tol && D2d.IsOpposite(gp::DY2d(), Tol)))
  {
    Axis = gp_Ax2d(gp_Pnt2d(0., -M_PI / 2.), gp::DX2d());
  }
  else
    return;

  Trsf.SetMirror(Axis);
  myLin.Transform(Trsf);

  myLin.Translate(gp_Vec2d(M_PI, 0.));

  double newX, X = ElCLib::Value(U, myLin).X();
  newX = ElCLib::InPeriod(X, 0., 2. * M_PI);
  myLin.Translate(gp_Vec2d(newX - X, 0.));
}
