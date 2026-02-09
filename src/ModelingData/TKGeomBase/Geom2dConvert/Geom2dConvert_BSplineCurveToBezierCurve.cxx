#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2dConvert_BSplineCurveToBezierCurve.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>

Geom2dConvert_BSplineCurveToBezierCurve::Geom2dConvert_BSplineCurveToBezierCurve(
  const occ::handle<Geom2d_BSplineCurve>& BasisCurve)
{
  myCurve = occ::down_cast<Geom2d_BSplineCurve>(BasisCurve->Copy());

  if (myCurve->IsPeriodic())
    myCurve->SetNotPeriodic();
  double Uf = myCurve->FirstParameter();
  double Ul = myCurve->LastParameter();
  myCurve->Segment(Uf, Ul);
  myCurve->IncreaseMultiplicity(myCurve->FirstUKnotIndex(),
                                myCurve->LastUKnotIndex(),
                                myCurve->Degree());
}

Geom2dConvert_BSplineCurveToBezierCurve::Geom2dConvert_BSplineCurveToBezierCurve(
  const occ::handle<Geom2d_BSplineCurve>& BasisCurve,
  const double                            U1,
  const double                            U2,
  const double                            ParametricTolerance)
{
  if (U2 - U1 < ParametricTolerance)
    throw Standard_DomainError("GeomConvert_BSplineCurveToBezierSurface");

  double Uf = U1, Ul = U2;
  double PTol = ParametricTolerance / 2;

  int I1, I2;
  myCurve = occ::down_cast<Geom2d_BSplineCurve>(BasisCurve->Copy());
  if (myCurve->IsPeriodic())
    myCurve->SetNotPeriodic();

  myCurve->LocateU(U1, PTol, I1, I2);
  if (I1 == I2)
  {
    if (myCurve->Knot(I1) > U1)
      Uf = myCurve->Knot(I1);
  }

  myCurve->LocateU(U2, PTol, I1, I2);
  if (I1 == I2)
  {
    if (myCurve->Knot(I1) < U2)
      Ul = myCurve->Knot(I1);
  }

  myCurve->Segment(Uf, Ul);
  myCurve->IncreaseMultiplicity(myCurve->FirstUKnotIndex(),
                                myCurve->LastUKnotIndex(),
                                myCurve->Degree());
}

occ::handle<Geom2d_BezierCurve> Geom2dConvert_BSplineCurveToBezierCurve::Arc(const int Index)
{
  if (Index < 1 || Index > myCurve->NbKnots() - 1)
  {
    throw Standard_OutOfRange("Geom2dConvert_BSplineCurveToBezierCurve");
  }
  int Deg = myCurve->Degree();

  NCollection_Array1<gp_Pnt2d> Poles(1, Deg + 1);

  occ::handle<Geom2d_BezierCurve> C;
  if (myCurve->IsRational())
  {
    NCollection_Array1<double> Weights(1, Deg + 1);
    for (int i = 1; i <= Deg + 1; i++)
    {
      Poles(i)   = myCurve->Pole(i + Deg * (Index - 1));
      Weights(i) = myCurve->Weight(i + Deg * (Index - 1));
    }
    C = new Geom2d_BezierCurve(Poles, Weights);
  }
  else
  {
    for (int i = 1; i <= Deg + 1; i++)
    {
      Poles(i) = myCurve->Pole(i + Deg * (Index - 1));
    }
    C = new Geom2d_BezierCurve(Poles);
  }
  return C;
}

void Geom2dConvert_BSplineCurveToBezierCurve::Arcs(
  NCollection_Array1<occ::handle<Geom2d_BezierCurve>>& Curves)
{
  int n = NbArcs();
  for (int i = 1; i <= n; i++)
  {
    Curves(i) = Arc(i);
  }
}

void Geom2dConvert_BSplineCurveToBezierCurve::Knots(NCollection_Array1<double>& TKnots) const
{
  int ii, kk;
  for (ii = 1, kk = TKnots.Lower(); ii <= myCurve->NbKnots(); ii++, kk++)
    TKnots(kk) = myCurve->Knot(ii);
}

int Geom2dConvert_BSplineCurveToBezierCurve::NbArcs() const
{
  return (myCurve->NbKnots() - 1);
}
