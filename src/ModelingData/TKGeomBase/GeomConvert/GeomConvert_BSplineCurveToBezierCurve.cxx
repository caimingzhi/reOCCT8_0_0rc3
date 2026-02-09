#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomConvert_BSplineCurveToBezierCurve.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

GeomConvert_BSplineCurveToBezierCurve::GeomConvert_BSplineCurveToBezierCurve(
  const occ::handle<Geom_BSplineCurve>& BasisCurve)
{
  myCurve   = occ::down_cast<Geom_BSplineCurve>(BasisCurve->Copy());
  double Uf = myCurve->FirstParameter();
  double Ul = myCurve->LastParameter();
  myCurve->Segment(Uf, Ul);
  myCurve->IncreaseMultiplicity(myCurve->FirstUKnotIndex(),
                                myCurve->LastUKnotIndex(),
                                myCurve->Degree());
}

GeomConvert_BSplineCurveToBezierCurve::GeomConvert_BSplineCurveToBezierCurve(
  const occ::handle<Geom_BSplineCurve>& BasisCurve,
  const double                          U1,
  const double                          U2,
  const double                          ParametricTolerance)
{
  if (U2 - U1 < ParametricTolerance)
    throw Standard_DomainError("GeomConvert_BSplineCurveToBezierSurface");

  double Uf = U1, Ul = U2;
  double PTol = ParametricTolerance / 2;

  int I1, I2;
  myCurve = occ::down_cast<Geom_BSplineCurve>(BasisCurve->Copy());

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

occ::handle<Geom_BezierCurve> GeomConvert_BSplineCurveToBezierCurve::Arc(const int Index)
{
  if (Index < 1 || Index > myCurve->NbKnots() - 1)
  {
    throw Standard_OutOfRange("GeomConvert_BSplineCurveToBezierCurve");
  }
  int Deg = myCurve->Degree();

  NCollection_Array1<gp_Pnt> Poles(1, Deg + 1);

  occ::handle<Geom_BezierCurve> C;
  if (myCurve->IsRational())
  {
    NCollection_Array1<double> Weights(1, Deg + 1);
    for (int i = 1; i <= Deg + 1; i++)
    {
      Poles(i)   = myCurve->Pole(i + Deg * (Index - 1));
      Weights(i) = myCurve->Weight(i + Deg * (Index - 1));
    }
    C = new Geom_BezierCurve(Poles, Weights);
  }
  else
  {
    for (int i = 1; i <= Deg + 1; i++)
    {
      Poles(i) = myCurve->Pole(i + Deg * (Index - 1));
    }
    C = new Geom_BezierCurve(Poles);
  }
  return C;
}

void GeomConvert_BSplineCurveToBezierCurve::Arcs(
  NCollection_Array1<occ::handle<Geom_BezierCurve>>& Curves)
{
  int n = NbArcs();
  for (int i = 1; i <= n; i++)
  {
    Curves(i) = Arc(i);
  }
}

void GeomConvert_BSplineCurveToBezierCurve::Knots(NCollection_Array1<double>& TKnots) const
{
  int ii, kk;
  for (ii = 1, kk = TKnots.Lower(); ii <= myCurve->NbKnots(); ii++, kk++)
    TKnots(kk) = myCurve->Knot(ii);
}

int GeomConvert_BSplineCurveToBezierCurve::NbArcs() const
{
  return (myCurve->NbKnots() - 1);
}
