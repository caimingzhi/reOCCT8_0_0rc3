

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Curve.hpp>
#include <CPnts_AbscissaPoint.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom_BezierCurve.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <math_FunctionRoot.hpp>
#include <math_GaussSingleIntegration.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <StdFail_NotDone.hpp>

static double f3d(const double X, void* const C)
{
  gp_Pnt P;
  gp_Vec V;
  ((Adaptor3d_Curve*)C)->D1(X, P, V);
  return V.Magnitude();
}

static double f2d(const double X, void* const C)
{
  gp_Pnt2d P;
  gp_Vec2d V;
  ((Adaptor2d_Curve2d*)C)->D1(X, P, V);
  return V.Magnitude();
}

static int order(const Adaptor3d_Curve& C)
{
  switch (C.GetType())
  {

    case GeomAbs_Line:
      return 2;

    case GeomAbs_Parabola:
      return 5;

    case GeomAbs_BezierCurve:
      return std::min(24, 2 * C.Degree());

    case GeomAbs_BSplineCurve:
      return std::min(24, 2 * C.NbPoles() - 1);

    default:
      return 10;
  }
}

static int order(const Adaptor2d_Curve2d& C)
{
  switch (C.GetType())
  {

    case GeomAbs_Line:
      return 2;

    case GeomAbs_Parabola:
      return 5;

    case GeomAbs_BezierCurve:
      return std::min(24, 2 * C.Bezier()->Degree());

    case GeomAbs_BSplineCurve:
      return std::min(24, 2 * C.BSpline()->NbPoles() - 1);

    default:
      return 10;
  }
}

double CPnts_AbscissaPoint::Length(const Adaptor3d_Curve& C)
{
  return CPnts_AbscissaPoint::Length(C, C.FirstParameter(), C.LastParameter());
}

double CPnts_AbscissaPoint::Length(const Adaptor2d_Curve2d& C)
{
  return CPnts_AbscissaPoint::Length(C, C.FirstParameter(), C.LastParameter());
}

double CPnts_AbscissaPoint::Length(const Adaptor3d_Curve& C, const double Tol)
{
  return CPnts_AbscissaPoint::Length(C, C.FirstParameter(), C.LastParameter(), Tol);
}

double CPnts_AbscissaPoint::Length(const Adaptor2d_Curve2d& C, const double Tol)
{
  return CPnts_AbscissaPoint::Length(C, C.FirstParameter(), C.LastParameter(), Tol);
}

double CPnts_AbscissaPoint::Length(const Adaptor3d_Curve& C, const double U1, const double U2)
{
  CPnts_MyGaussFunction FG;

  CPnts_RealFunction rf = f3d;
  FG.Init(rf, (void*)&C);

  math_GaussSingleIntegration TheLength(FG, U1, U2, order(C));
  if (!TheLength.IsDone())
  {
    throw Standard_ConstructionError();
  }
  return std::abs(TheLength.Value());
}

double CPnts_AbscissaPoint::Length(const Adaptor2d_Curve2d& C, const double U1, const double U2)
{
  CPnts_MyGaussFunction FG;

  CPnts_RealFunction rf = f2d;
  FG.Init(rf, (void*)&C);

  math_GaussSingleIntegration TheLength(FG, U1, U2, order(C));
  if (!TheLength.IsDone())
  {
    throw Standard_ConstructionError();
  }
  return std::abs(TheLength.Value());
}

double CPnts_AbscissaPoint::Length(const Adaptor3d_Curve& C,
                                   const double           U1,
                                   const double           U2,
                                   const double           Tol)
{
  CPnts_MyGaussFunction FG;

  CPnts_RealFunction rf = f3d;
  FG.Init(rf, (void*)&C);

  math_GaussSingleIntegration TheLength(FG, U1, U2, order(C), Tol);
  if (!TheLength.IsDone())
  {
    throw Standard_ConstructionError();
  }
  return std::abs(TheLength.Value());
}

double CPnts_AbscissaPoint::Length(const Adaptor2d_Curve2d& C,
                                   const double             U1,
                                   const double             U2,
                                   const double             Tol)
{
  CPnts_MyGaussFunction FG;

  CPnts_RealFunction rf = f2d;
  FG.Init(rf, (void*)&C);

  math_GaussSingleIntegration TheLength(FG, U1, U2, order(C), Tol);
  if (!TheLength.IsDone())
  {
    throw Standard_ConstructionError();
  }
  return std::abs(TheLength.Value());
}

CPnts_AbscissaPoint::CPnts_AbscissaPoint()
    : myDone(false),
      myL(0.0),
      myParam(0.0),
      myUMin(0.0),
      myUMax(0.0)
{
}

CPnts_AbscissaPoint::CPnts_AbscissaPoint(const Adaptor3d_Curve& C,
                                         const double           Abscissa,
                                         const double           U0,
                                         const double           Resolution)
{

  Init(C, Resolution);

  Perform(Abscissa, U0, Resolution);
}

CPnts_AbscissaPoint::CPnts_AbscissaPoint(const Adaptor2d_Curve2d& C,
                                         const double             Abscissa,
                                         const double             U0,
                                         const double             Resolution)
{
  Init(C);
  Perform(Abscissa, U0, Resolution);
}

CPnts_AbscissaPoint::CPnts_AbscissaPoint(const Adaptor3d_Curve& C,
                                         const double           Abscissa,
                                         const double           U0,
                                         const double           Ui,
                                         const double           Resolution)
{
  Init(C);
  Perform(Abscissa, U0, Ui, Resolution);
}

CPnts_AbscissaPoint::CPnts_AbscissaPoint(const Adaptor2d_Curve2d& C,
                                         const double             Abscissa,
                                         const double             U0,
                                         const double             Ui,
                                         const double             Resolution)
{
  Init(C);
  Perform(Abscissa, U0, Ui, Resolution);
}

void CPnts_AbscissaPoint::Init(const Adaptor3d_Curve& C)
{
  Init(C, C.FirstParameter(), C.LastParameter());
}

void CPnts_AbscissaPoint::Init(const Adaptor2d_Curve2d& C)
{
  Init(C, C.FirstParameter(), C.LastParameter());
}

void CPnts_AbscissaPoint::Init(const Adaptor3d_Curve& C, const double Tol)
{
  Init(C, C.FirstParameter(), C.LastParameter(), Tol);
}

void CPnts_AbscissaPoint::Init(const Adaptor2d_Curve2d& C, const double Tol)
{
  Init(C, C.FirstParameter(), C.LastParameter(), Tol);
}

void CPnts_AbscissaPoint::Init(const Adaptor3d_Curve& C, const double U1, const double U2)
{

  CPnts_RealFunction rf = f3d;
  myF.Init(rf, (void*)&C, order(C));

  myL       = CPnts_AbscissaPoint::Length(C, U1, U2);
  myUMin    = std::min(U1, U2);
  myUMax    = std::max(U1, U2);
  double DU = myUMax - myUMin;
  myUMin    = myUMin - DU;
  myUMax    = myUMax + DU;
}

void CPnts_AbscissaPoint::Init(const Adaptor2d_Curve2d& C, const double U1, const double U2)
{

  CPnts_RealFunction rf = f2d;
  myF.Init(rf, (void*)&C, order(C));

  myL       = CPnts_AbscissaPoint::Length(C, U1, U2);
  myUMin    = std::min(U1, U2);
  myUMax    = std::max(U1, U2);
  double DU = myUMax - myUMin;
  myUMin    = myUMin - DU;
  myUMax    = myUMax + DU;
}

void CPnts_AbscissaPoint::Init(const Adaptor3d_Curve& C,
                               const double           U1,
                               const double           U2,
                               const double           Tol)
{

  CPnts_RealFunction rf = f3d;
  myF.Init(rf, (void*)&C, order(C));

  myL       = CPnts_AbscissaPoint::Length(C, U1, U2, Tol);
  myUMin    = std::min(U1, U2);
  myUMax    = std::max(U1, U2);
  double DU = myUMax - myUMin;
  myUMin    = myUMin - DU;
  myUMax    = myUMax + DU;
}

void CPnts_AbscissaPoint::Init(const Adaptor2d_Curve2d& C,
                               const double             U1,
                               const double             U2,
                               const double             Tol)
{

  CPnts_RealFunction rf = f2d;
  myF.Init(rf, (void*)&C, order(C));

  myL       = CPnts_AbscissaPoint::Length(C, U1, U2, Tol);
  myUMin    = std::min(U1, U2);
  myUMax    = std::max(U1, U2);
  double DU = myUMax - myUMin;
  myUMin    = myUMin - DU;
  myUMax    = myUMax + DU;
}

void CPnts_AbscissaPoint::Perform(const double Abscissa, const double U0, const double Resolution)
{
  if (myL < Precision::Confusion())
  {

    myDone  = true;
    myParam = U0;
  }
  else
  {
    double Ui = U0 + (Abscissa / myL) * (myUMax - myUMin) / 3.;

    Perform(Abscissa, U0, Ui, Resolution);
  }
}

void CPnts_AbscissaPoint::Perform(const double Abscissa,
                                  const double U0,
                                  const double Ui,
                                  const double Resolution)
{
  if (myL < Precision::Confusion())
  {

    myDone  = true;
    myParam = U0;
  }
  else
  {
    myDone = false;
    myF.Init(U0, Abscissa);

    math_FunctionRoot Solution(myF, Ui, Resolution, myUMin, myUMax);

    if (Solution.IsDone())
    {
      myDone  = true;
      myParam = Solution.Root();
    }
  }
}

void CPnts_AbscissaPoint::AdvPerform(const double Abscissa,
                                     const double U0,
                                     const double Ui,
                                     const double Resolution)
{
  if (myL < Precision::Confusion())
  {

    myDone  = true;
    myParam = U0;
  }
  else
  {
    myDone = false;

    myF.Init(U0, Abscissa, Resolution / 10);

    math_FunctionRoot Solution(myF, Ui, Resolution, myUMin, myUMax);

    if (Solution.IsDone())
    {
      myDone  = true;
      myParam = Solution.Root();
    }
  }
}
