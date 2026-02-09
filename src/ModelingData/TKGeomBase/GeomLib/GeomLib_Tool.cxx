#include <GeomLib_Tool.hpp>

#include <ElCLib.hpp>
#include <Extrema_ExtPC.hpp>
#include <Extrema_ExtPC2d.hpp>
#include <Extrema_ExtPS.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <math_PSO.hpp>

static const double PARTOLERANCE = 1.e-9;

bool GeomLib_Tool::Parameter(const occ::handle<Geom_Curve>& Curve,
                             const gp_Pnt&                  Point,
                             const double                   MaxDist,
                             double&                        U)
{
  if (Curve.IsNull())
    return false;

  U           = 0.;
  double aTol = MaxDist * MaxDist;

  GeomAdaptor_Curve aGAC(Curve);
  Extrema_ExtPC     extrema(Point, aGAC);

  if (!extrema.IsDone())
    return false;

  int n = extrema.NbExt();
  if (n <= 0)
    return false;

  int    i = 0, iMin = 0;
  double Dist2Min = RealLast();
  for (i = 1; i <= n; i++)
  {
    if (extrema.SquareDistance(i) < Dist2Min)
    {
      iMin     = i;
      Dist2Min = extrema.SquareDistance(i);
    }
  }
  if (iMin != 0 && Dist2Min <= aTol)
  {
    U = (extrema.Point(iMin)).Parameter();
  }
  else
  {
    return false;
  }

  return true;
}

bool GeomLib_Tool::Parameters(const occ::handle<Geom_Surface>& Surface,
                              const gp_Pnt&                    Point,
                              const double                     MaxDist,
                              double&                          U,
                              double&                          V)
{
  if (Surface.IsNull())
    return false;

  U           = 0.;
  V           = 0.;
  double aTol = MaxDist * MaxDist;

  GeomAdaptor_Surface aGAS(Surface);
  double              aTolU = PARTOLERANCE, aTolV = PARTOLERANCE;

  Extrema_ExtPS extrema(Point, aGAS, aTolU, aTolV, Extrema_ExtFlag_MIN);

  if (!extrema.IsDone())
    return false;

  int n = extrema.NbExt();
  if (n <= 0)
    return false;

  double Dist2Min = RealLast();
  int    i = 0, iMin = 0;
  for (i = 1; i <= n; i++)
  {
    if (extrema.SquareDistance(i) < Dist2Min)
    {
      Dist2Min = extrema.SquareDistance(i);
      iMin     = i;
    }
  }
  if (iMin != 0 && Dist2Min <= aTol)
  {
    extrema.Point(iMin).Parameter(U, V);
  }
  else
  {
    return false;
  }

  return true;
}

bool GeomLib_Tool::Parameter(const occ::handle<Geom2d_Curve>& Curve,
                             const gp_Pnt2d&                  Point,
                             const double                     MaxDist,
                             double&                          U)
{
  if (Curve.IsNull())
    return false;

  U           = 0.;
  double aTol = MaxDist * MaxDist;

  Geom2dAdaptor_Curve aGAC(Curve);
  Extrema_ExtPC2d     extrema(Point, aGAC);
  if (!extrema.IsDone())
    return false;
  int n = extrema.NbExt();
  if (n <= 0)
    return false;
  int    i = 0, iMin = 0;
  double Dist2Min = RealLast();
  for (i = 1; i <= n; i++)
  {
    if (extrema.SquareDistance(i) < Dist2Min)
    {
      Dist2Min = extrema.SquareDistance(i);
      iMin     = i;
    }
  }
  if (iMin != 0 && Dist2Min <= aTol)
  {
    U = (extrema.Point(iMin)).Parameter();
  }
  else
  {
    return false;
  }

  return true;
}

namespace
{

  class FuncSolveDeviation : public math_MultipleVarFunction
  {
  public:
    FuncSolveDeviation(const Geom2dAdaptor_Curve& theCurve, const gp_XY& thePf, const gp_XY& thePl)
        : myCurve(theCurve),
          myPRef(thePf)
    {
      myDirRef  = thePl - thePf;
      mySqMod   = myDirRef.SquareModulus();
      myIsValid = (mySqMod > Precision::SquarePConfusion());
    }

    void UpdateFields(const double theParam)
    {
      myCurve.D0(theParam, myPointOnCurve);
      const gp_XY aVt = myPointOnCurve.XY() - myPRef;
      myVecCurvLine   = aVt.Dot(myDirRef) * myDirRef / mySqMod - aVt;
    }

    void ValueAndDerives(const double theParam, double& theVal, double& theD1, double& theD2)
    {
      gp_Vec2d aD1;
      gp_Vec2d aD2;
      myCurve.D2(theParam, myPointOnCurve, aD1, aD2);

      const gp_XY aVt = myPointOnCurve.XY() - myPRef;
      theVal          = aVt.Crossed(myDirRef);
      theD1           = aD1.Crossed(myDirRef);
      theD2           = 2.0 * (theD1 * theD1 + theVal * aD2.Crossed(myDirRef));
      theD1 *= 2.0 * theVal;
      theVal *= theVal / mySqMod;
    }

    bool IsValid() const { return myIsValid; }

    int NbVariables() const override { return 1; }

    const gp_Pnt2d& PointOnCurve() const { return myPointOnCurve; }

    const gp_Vec2d& VecCurveLine() const { return myVecCurvLine; }

    void GetLine(gp_Lin2d* const theLine) const
    {
      if (theLine == nullptr)
      {
        return;
      }
      theLine->SetDirection(myDirRef);
      theLine->SetLocation(myPRef);
    }

    bool Value(const math_Vector& thePrm, double& theVal) override
    {
      double aD1;
      double aD2;
      ValueAndDerives(thePrm.Value(thePrm.Lower()), theVal, aD1, aD2);
      theVal = -theVal;
      return true;
    }

    int GetStateNumber() override { return 0; }

  private:
    Geom2dAdaptor_Curve myCurve;

    double mySqMod;

    bool myIsValid;

    gp_XY myPRef, myDirRef;

    gp_Pnt2d myPointOnCurve;

    gp_Vec2d myVecCurvLine;
  };
} // namespace

double GeomLib_Tool::ComputeDeviation(const Geom2dAdaptor_Curve& theCurve,
                                      const double               theFPar,
                                      const double               theLPar,
                                      const double               theStartParameter,
                                      const int                  theNbIters,
                                      double* const              thePrmOnCurve,
                                      gp_Pnt2d* const            thePtOnCurve,
                                      gp_Vec2d* const            theVecCurvLine,
                                      gp_Lin2d* const            theLine)
{

  if ((theStartParameter < theFPar) || (theStartParameter > theLPar))
  {
    return -1.0;
  }

  const gp_Pnt2d aPf(theCurve.Value(theFPar));
  const gp_Pnt2d aPl(theCurve.Value(theLPar));

  FuncSolveDeviation aFunc(theCurve, aPf.XY(), aPl.XY());

  if (!aFunc.IsValid())
  {
    return -1.0;
  }

  aFunc.GetLine(theLine);

  constexpr double aTolDefl = Precision::PConfusion();

  double aD1   = 0.0;
  double aD2   = 0.0;
  double aU0   = theStartParameter;
  double aUmax = theStartParameter;
  double aSqDefl;
  aFunc.ValueAndDerives(aU0, aSqDefl, aD1, aD2);
  for (int anItr = 1; anItr <= theNbIters; anItr++)
  {
    if (std::abs(aD2) < Precision::PConfusion())
    {
      break;
    }
    const double aDelta = aD1 / aD2;
    const double aU1    = aU0 - aDelta;

    if ((aU1 < theFPar) || (aU1 > theLPar))
    {
      break;
    }
    double aSqD = aSqDefl;
    aFunc.ValueAndDerives(aU1, aSqD, aD1, aD2);
    if (aSqD > aSqDefl)
    {
      aUmax = aU1;
      const double aDD =
        aSqDefl > 0.0 ? std::abs(std::sqrt(aSqD) - std::sqrt(aSqDefl)) : std::sqrt(aSqD);
      aSqDefl = aSqD;
      if (aDD < aTolDefl)
      {
        break;
      }
    }

    if (std::abs(aU0 - aU1) < Precision::PConfusion())
    {
      break;
    }
    aU0 = aU1;
  }
  if (aSqDefl < 0.0)
  {
    return aSqDefl;
  }
  if (thePrmOnCurve)
  {
    *thePrmOnCurve = aUmax;
  }
  if ((thePtOnCurve != nullptr) || (theVecCurvLine != nullptr))
  {
    aFunc.UpdateFields(aUmax);

    if (thePtOnCurve != nullptr)
    {
      thePtOnCurve->SetXY(aFunc.PointOnCurve().XY());
    }

    if (theVecCurvLine != nullptr)
    {
      theVecCurvLine->SetXY(aFunc.VecCurveLine().XY());
    }
  }
  return std::sqrt(aSqDefl);
}

double GeomLib_Tool::ComputeDeviation(const Geom2dAdaptor_Curve& theCurve,
                                      const double               theFPar,
                                      const double               theLPar,
                                      const int                  theNbSubIntervals,
                                      const int                  theNbIters,
                                      double* const              thePrmOnCurve)
{

  const gp_Pnt2d aPf(theCurve.Value(theFPar));
  const gp_Pnt2d aPl(theCurve.Value(theLPar));

  FuncSolveDeviation aFunc(theCurve, aPf.XY(), aPl.XY());

  if (!aFunc.IsValid())
  {
    return -1.0;
  }
  const math_Vector aFPar(1, 1, theFPar);
  const math_Vector aLPar(1, 1, theLPar);
  const math_Vector aStep(1, 1, (theLPar - theFPar) / (10.0 * theNbSubIntervals));
  math_Vector       anOutputPnt(1, 1, theFPar);
  math_PSO          aMPSO(&aFunc, aFPar, aLPar, aStep, theNbSubIntervals, theNbIters);

  double aSqDefl = RealLast();
  aMPSO.Perform(aStep, aSqDefl, anOutputPnt, theNbIters);

  if (aSqDefl == RealLast())
  {
    return -1.0;
  }
  if (thePrmOnCurve)
  {
    *thePrmOnCurve = anOutputPnt(1);
  }
  return std::sqrt(std::abs(aSqDefl));
}
