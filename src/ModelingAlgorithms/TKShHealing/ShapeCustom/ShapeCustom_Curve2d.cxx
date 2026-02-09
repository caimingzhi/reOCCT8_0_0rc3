#include <ElCLib.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <ShapeCustom_Curve2d.hpp>
#include <Standard_ErrorHandler.hpp>

static gp_Lin2d GetLine(const gp_Pnt2d& P1,
                        const gp_Pnt2d& P2,
                        const double    c1,
                        double&         cf,
                        double&         cl)
{
  gp_Vec2d avec(P1, P2);
  gp_Dir2d adir(avec);
  gp_Lin2d alin(P1, adir);
  alin.SetLocation(ElCLib::Value(c1, alin));
  cf = ElCLib::Parameter(alin, P1);
  cl = ElCLib::Parameter(alin, P2);
  return alin;
}

bool ShapeCustom_Curve2d::IsLinear(const NCollection_Array1<gp_Pnt2d>& thePoles,
                                   const double                        tolerance,
                                   double&                             Deviation)
{
  int nbPoles = thePoles.Length();
  if (nbPoles < 2)
    return false;

  double dMax  = 0;
  int    iMax1 = 0, iMax2 = 0;

  int i;
  for (i = 1; i < nbPoles; i++)
    for (int j = i + 1; j <= nbPoles; j++)
    {
      double dist = thePoles(i).SquareDistance(thePoles(j));
      if (dist > dMax)
      {
        dMax  = dist;
        iMax1 = i;
        iMax2 = j;
      }
    }

  constexpr double dPreci = Precision::PConfusion() * Precision::PConfusion();
  if (dMax < dPreci)
    return false;

  double   tol2 = tolerance * tolerance;
  gp_Vec2d avec(thePoles(iMax1), thePoles(iMax2));
  gp_Dir2d adir(avec);
  gp_Lin2d alin(thePoles(iMax1), adir);

  double aMax = 0.;
  for (i = 1; i <= nbPoles; i++)
  {
    double dist = alin.SquareDistance(thePoles(i));
    if (dist > tol2)
      return false;
    if (dist > aMax)
      aMax = dist;
  }
  Deviation = sqrt(aMax);

  return true;
}

occ::handle<Geom2d_Line> ShapeCustom_Curve2d::ConvertToLine2d(
  const occ::handle<Geom2d_Curve>& theCurve,
  const double                     c1,
  const double                     c2,
  const double                     theTolerance,
  double&                          cf,
  double&                          cl,
  double&                          theDeviation)
{
  occ::handle<Geom2d_Line> aLine2d;
  gp_Pnt2d                 P1     = theCurve->Value(c1);
  gp_Pnt2d                 P2     = theCurve->Value(c2);
  double                   dPreci = theTolerance * theTolerance;
  if (P1.SquareDistance(P2) < dPreci)
    return aLine2d;

  occ::handle<Geom2d_BSplineCurve> bsc = occ::down_cast<Geom2d_BSplineCurve>(theCurve);
  if (!bsc.IsNull())
  {
    int                          nbPoles = bsc->NbPoles();
    NCollection_Array1<gp_Pnt2d> Poles(1, nbPoles);
    bsc->Poles(Poles);
    if (!ShapeCustom_Curve2d::IsLinear(Poles, theTolerance, theDeviation))
      return aLine2d;
    gp_Lin2d alin = GetLine(P1, P2, c1, cf, cl);
    aLine2d       = new Geom2d_Line(alin);
    return aLine2d;
  }

  occ::handle<Geom2d_BezierCurve> bzc = occ::down_cast<Geom2d_BezierCurve>(theCurve);
  if (!bzc.IsNull())
  {
    int                          nbPoles = bzc->NbPoles();
    NCollection_Array1<gp_Pnt2d> Poles(1, nbPoles);
    bzc->Poles(Poles);
    if (!ShapeCustom_Curve2d::IsLinear(Poles, theTolerance, theDeviation))
      return aLine2d;
    gp_Lin2d alin = GetLine(P1, P2, c1, cf, cl);
    aLine2d       = new Geom2d_Line(alin);
    return aLine2d;
  }

  return aLine2d;
}

bool ShapeCustom_Curve2d::SimplifyBSpline2d(occ::handle<Geom2d_BSplineCurve>& theBSpline2d,
                                            const double                      theTolerance)
{
  int aInitNbK;
  int NbK = aInitNbK = theBSpline2d->NbKnots();

  bool IsToRemove = true;
  int  aKnotIndx  = NbK - 1;
  while (IsToRemove && NbK > 2)
  {
    int aMult   = theBSpline2d->Multiplicity(aKnotIndx);
    int DegMult = theBSpline2d->Degree() - aMult;
    if ((DegMult > 1) && theBSpline2d->IsCN(DegMult))
    {
      double   U     = theBSpline2d->Knot(aKnotIndx);
      gp_Vec2d aVec1 = theBSpline2d->LocalDN(U, aKnotIndx - 1, aKnotIndx, DegMult);
      gp_Vec2d aVec2 = theBSpline2d->LocalDN(U, aKnotIndx, aKnotIndx + 1, DegMult);

      if (aVec1.IsParallel(aVec2, Precision::Angular()))
      {

        try
        {
          OCC_CATCH_SIGNALS
          theBSpline2d->RemoveKnot(aKnotIndx, aMult - 1, theTolerance);
        }
        catch (Standard_Failure const&)
        {
        }
      }
    }
    aKnotIndx--;

    NbK = theBSpline2d->NbKnots();
    if (aKnotIndx == 1 || aKnotIndx == NbK)
      IsToRemove = false;
  }
  return (aInitNbK > NbK);
}
