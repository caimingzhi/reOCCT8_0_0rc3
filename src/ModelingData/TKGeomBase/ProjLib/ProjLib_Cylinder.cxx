#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <ProjLib_Cylinder.hpp>
#include <Standard_NotImplemented.hpp>

ProjLib_Cylinder::ProjLib_Cylinder() = default;

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl)
{
  Init(Cyl);
}

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Lin& L)
{
  Init(Cyl);
  Project(L);
}

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Circ& C)
{
  Init(Cyl);
  Project(C);
}

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Elips& E)
{
  Init(Cyl);
  Project(E);
}

void ProjLib_Cylinder::Init(const gp_Cylinder& Cyl)
{
  myType       = GeomAbs_OtherCurve;
  myCylinder   = Cyl;
  myIsPeriodic = false;
  isDone       = false;
}

static gp_Pnt2d EvalPnt2d(const gp_Pnt& P, const gp_Cylinder& Cy)
{
  gp_Vec OP(Cy.Location(), P);
  double X = OP.Dot(gp_Vec(Cy.Position().XDirection()));
  double Y = OP.Dot(gp_Vec(Cy.Position().YDirection()));
  double Z = OP.Dot(gp_Vec(Cy.Position().Direction()));
  double U;

  if (std::abs(X) > Precision::PConfusion() || std::abs(Y) > Precision::PConfusion())
  {
    U = std::atan2(Y, X);
  }
  else
  {
    U = 0.;
  }
  return gp_Pnt2d(U, Z);
}

void ProjLib_Cylinder::Project(const gp_Lin& L)
{

  if (L.Direction().XYZ().CrossSquareMagnitude(myCylinder.Position().Direction().XYZ())
      > Precision::Angular() * Precision::Angular())
    return;

  myType = GeomAbs_Line;

  gp_Pnt2d P2d = EvalPnt2d(L.Location(), myCylinder);
  if (P2d.X() < 0.)
  {
    P2d.SetX(P2d.X() + 2 * M_PI);
  }
  double Signe = L.Direction().Dot(myCylinder.Position().Direction());
  Signe        = (Signe > 0.) ? 1. : -1.;
  gp_Dir2d D2d(0., Signe);

  myLin  = gp_Lin2d(P2d, D2d);
  isDone = true;
}

void ProjLib_Cylinder::Project(const gp_Circ& C)
{

  const gp_Ax3& aCylPos  = myCylinder.Position();
  const gp_Ax2& aCircPos = C.Position();
  if (aCylPos.Direction().XYZ().CrossSquareMagnitude(aCircPos.Direction().XYZ())
      > Precision::Angular() * Precision::Angular())
    return;

  myType = GeomAbs_Line;

  gp_Dir ZCyl = aCylPos.XDirection().Crossed(aCylPos.YDirection());

  double U = aCylPos.XDirection().AngleWithRef(aCircPos.XDirection(), ZCyl);

  gp_Vec OP(myCylinder.Location(), C.Location());
  double V = OP.Dot(gp_Vec(aCylPos.Direction()));

  gp_Pnt2d P2d1(U, V);
  gp_Dir2d D2d;
  if (ZCyl.Dot(aCircPos.Direction()) > 0.)
    D2d.SetCoord(1., 0.);
  else
    D2d.SetCoord(-1., 0.);

  myLin  = gp_Lin2d(P2d1, D2d);
  isDone = true;
}

void ProjLib_Cylinder::Project(const gp_Elips&) {}

void ProjLib_Cylinder::Project(const gp_Parab& P)
{
  ProjLib_Projector::Project(P);
}

void ProjLib_Cylinder::Project(const gp_Hypr& H)
{
  ProjLib_Projector::Project(H);
}
