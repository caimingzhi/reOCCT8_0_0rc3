

#include <ElCLib.hpp>
#include <Extrema_ExtElC.hpp>
#include <Extrema_ExtElC2d.hpp>
#include <Extrema_POnCurv.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Dir.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <math_DirectPolynomialRoots.hpp>
#include <math_TrigonometricFunctionRoots.hpp>
#include <Precision.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

static void RefineDir(gp_Dir& aDir);

class ExtremaExtElC_TrigonometricRoots
{
private:
  double Roots[4];
  bool   done;
  int    NbRoots;
  bool   infinite_roots;

public:
  ExtremaExtElC_TrigonometricRoots(const double CC,
                                   const double SC,
                                   const double C,
                                   const double S,
                                   const double Cte,
                                   const double Binf,
                                   const double Bsup);

  bool IsDone() { return done; }

  bool IsARoot(double u)
  {
    double PIpPI, aEps;

    aEps  = RealEpsilon();
    PIpPI = M_PI + M_PI;
    for (int i = 0; i < NbRoots; i++)
    {
      if (std::abs(u - Roots[i]) <= aEps)
      {
        return true;
      }
      if (std::abs(u - Roots[i] - PIpPI) <= aEps)
      {
        return true;
      }
    }
    return false;
  }

  int NbSolutions()
  {
    if (!done)
    {
      throw StdFail_NotDone();
    }
    return NbRoots;
  }

  bool InfiniteRoots()
  {
    if (!done)
    {
      throw StdFail_NotDone();
    }
    return infinite_roots;
  }

  double Value(const int& n)
  {
    if ((!done) || (n > NbRoots))
    {
      throw StdFail_NotDone();
    }
    return Roots[n - 1];
  }
};

ExtremaExtElC_TrigonometricRoots::ExtremaExtElC_TrigonometricRoots(const double CC,
                                                                   const double SC,
                                                                   const double C,
                                                                   const double S,
                                                                   const double Cte,
                                                                   const double Binf,
                                                                   const double Bsup)
    : NbRoots(0),
      infinite_roots(false)
{
  int    i, nbessai;
  double cc, sc, c, s, cte;

  nbessai = 1;
  cc      = CC;
  sc      = SC;
  c       = C;
  s       = S;
  cte     = Cte;
  done    = false;
  while (nbessai <= 2 && !done)
  {

    math_TrigonometricFunctionRoots MTFR(cc, sc, c, s, cte, Binf, Bsup);

    if (MTFR.IsDone())
    {
      done = true;
      if (MTFR.InfiniteRoots())
      {
        infinite_roots = true;
      }
      else
      {
        bool   Triee;
        int    j, SvNbRoots;
        double aTwoPI, aMaxCoef, aPrecision;

        aTwoPI  = M_PI + M_PI;
        NbRoots = MTFR.NbSolutions();
        for (i = 0; i < NbRoots; ++i)
        {
          Roots[i] = MTFR.Value(i + 1);
          if (Roots[i] < 0.)
          {
            Roots[i] = Roots[i] + aTwoPI;
          }
          if (Roots[i] > aTwoPI)
          {
            Roots[i] = Roots[i] - aTwoPI;
          }
        }

        aMaxCoef   = std::max(CC, SC);
        aMaxCoef   = std::max(aMaxCoef, C);
        aMaxCoef   = std::max(aMaxCoef, S);
        aMaxCoef   = std::max(aMaxCoef, Cte);
        aPrecision = std::max(1.e-8, 1.e-12 * aMaxCoef);

        SvNbRoots = NbRoots;
        for (i = 0; i < SvNbRoots; ++i)
        {
          double y;
          double co = cos(Roots[i]);
          double si = sin(Roots[i]);
          y         = co * (CC * co + (SC + SC) * si + C) + S * si + Cte;

          if (std::abs(y) > aPrecision)
          {
            NbRoots--;
            Roots[i] = 1000.0;
          }
        }

        do
        {
          double t;

          Triee = true;
          for (i = 1, j = 0; i < SvNbRoots; ++i, ++j)
          {
            if (Roots[i] < Roots[j])
            {
              Triee    = false;
              t        = Roots[i];
              Roots[i] = Roots[j];
              Roots[j] = t;
            }
          }
        } while (!Triee);

        infinite_roots = false;
        if (NbRoots == 0)
        {
          if ((std::abs(CC) + std::abs(SC) + std::abs(C) + std::abs(S)) < 1e-10)
          {
            if (std::abs(Cte) < 1e-10)
            {
              infinite_roots = true;
            }
          }
        }
      }
    }
    else
    {

      if (std::abs(CC) < 1e-10)
      {
        cc = 0.0;
      }
      if (std::abs(SC) < 1e-10)
      {
        sc = 0.0;
      }
      if (std::abs(C) < 1e-10)
      {
        c = 0.0;
      }
      if (std::abs(S) < 1e-10)
      {
        s = 0.0;
      }
      if (std::abs(Cte) < 1e-10)
      {
        cte = 0.0;
      }
      nbessai++;
    }
  }
}

Extrema_ExtElC::Extrema_ExtElC()
{
  myDone  = false;
  myIsPar = false;
  myNbExt = 0;
  for (size_t anIdx = 0; anIdx < sizeof(mySqDist) / sizeof(mySqDist[0]); anIdx++)
  {
    mySqDist[anIdx] = RealLast();
  }
}

Extrema_ExtElC::Extrema_ExtElC(const gp_Lin& theC1, const gp_Lin& theC2, const double)

{
  myDone  = false;
  myNbExt = 0;
  myIsPar = false;
  for (size_t anIdx = 0; anIdx < sizeof(mySqDist) / sizeof(mySqDist[0]); anIdx++)
  {
    mySqDist[anIdx] = RealLast();
  }

  const gp_Dir &aD1 = theC1.Position().Direction(), &aD2 = theC2.Position().Direction();
  const double  aCosA   = aD1.Dot(aD2);
  const double  aSqSinA = 1.0 - aCosA * aCosA;
  double        aU1 = 0.0, aU2 = 0.0;
  if (aSqSinA < gp::Resolution() || aD1.IsParallel(aD2, Precision::Angular()))
  {
    myIsPar = true;
  }
  else
  {
    const gp_XYZ aL1L2 = theC2.Location().XYZ() - theC1.Location().XYZ();
    const double aD1L = aD1.XYZ().Dot(aL1L2), aD2L = aD2.XYZ().Dot(aL1L2);
    aU1 = (aD1L - aCosA * aD2L) / aSqSinA;
    aU2 = (aCosA * aD1L - aD2L) / aSqSinA;

    myIsPar = Precision::IsInfinite(aU1) || Precision::IsInfinite(aU2);
  }

  if (myIsPar)
  {
    mySqDist[0] = theC2.SquareDistance(theC1.Location());
    myNbExt     = 1;
    myDone      = true;
    return;
  }

  const gp_Pnt aP1(ElCLib::Value(aU1, theC1)), aP2(ElCLib::Value(aU2, theC2));
  mySqDist[myNbExt]   = aP1.SquareDistance(aP2);
  myPoint[myNbExt][0] = Extrema_POnCurv(aU1, aP1);
  myPoint[myNbExt][1] = Extrema_POnCurv(aU2, aP2);
  myNbExt             = 1;
  myDone              = true;
}

bool Extrema_ExtElC::PlanarLineCircleExtrema(const gp_Lin& theLin, const gp_Circ& theCirc)
{
  const gp_Dir &aDirC = theCirc.Axis().Direction(), &aDirL = theLin.Direction();

  if (std::abs(aDirC.Dot(aDirL)) > Precision::Angular())
    return false;

  const gp_XYZ& aCLoc = theCirc.Location().XYZ();
  const gp_XYZ &aDCx  = theCirc.Position().XDirection().XYZ(),
               &aDCy  = theCirc.Position().YDirection().XYZ();

  const gp_XYZ& aLLoc = theLin.Location().XYZ();
  const gp_XYZ& aLDir = theLin.Direction().XYZ();

  const gp_XYZ aVecCL(aLLoc - aCLoc);

  const gp_Pnt2d aPC(0.0, 0.0);

  gp_Ax22d  aCircAxis(aPC, gp_Dir2d(gp_Dir2d::D::X), gp_Dir2d(gp_Dir2d::D::Y));
  gp_Circ2d aCirc2d(aCircAxis, theCirc.Radius());

  gp_Pnt2d aPL(aVecCL.Dot(aDCx), aVecCL.Dot(aDCy));
  gp_Dir2d aDL(aLDir.Dot(aDCx), aLDir.Dot(aDCy));
  gp_Lin2d aLin2d(aPL, aDL);

  Extrema_ExtElC2d anExt2d(aLin2d, aCirc2d, Precision::Confusion());

  IntAna2d_AnaIntersection anInters(aLin2d, aCirc2d);

  myDone = anExt2d.IsDone() || anInters.IsDone();

  if (!myDone)
    return true;

  const int aNbExtr = anExt2d.NbExt();
  const int aNbSol  = anInters.NbPoints();

  const int aNbSum = aNbExtr + aNbSol;
  for (int anExtrID = 1; anExtrID <= aNbSum; anExtrID++)
  {
    const int aDelta = anExtrID - aNbExtr;

    double aLinPar = 0.0, aCircPar = 0.0;

    if (aDelta < 1)
    {
      Extrema_POnCurv2d aPLin2d, aPCirc2d;
      anExt2d.Points(anExtrID, aPLin2d, aPCirc2d);
      aLinPar  = aPLin2d.Parameter();
      aCircPar = aPCirc2d.Parameter();
    }
    else
    {
      aLinPar  = anInters.Point(aDelta).ParamOnFirst();
      aCircPar = anInters.Point(aDelta).ParamOnSecond();
    }

    const gp_Pnt aPOnL(ElCLib::LineValue(aLinPar, theLin.Position())),
      aPOnC(ElCLib::CircleValue(aCircPar, theCirc.Position(), theCirc.Radius()));

    mySqDist[myNbExt] = aPOnL.SquareDistance(aPOnC);
    myPoint[myNbExt][0].SetValues(aLinPar, aPOnL);
    myPoint[myNbExt][1].SetValues(aCircPar, aPOnC);
    myNbExt++;
  }

  return true;
}

Extrema_ExtElC::Extrema_ExtElC(const gp_Lin& C1, const gp_Circ& C2, const double)
{
  double Dx, Dy, Dz, aRO2O1, aTolRO2O1;
  double R, A1, A2, A3, A4, A5, aTol;
  gp_Dir x2, y2, z2, D, D1;

  myIsPar = false;
  myDone  = false;
  myNbExt = 0;
  for (size_t anIdx = 0; anIdx < sizeof(mySqDist) / sizeof(mySqDist[0]); anIdx++)
  {
    mySqDist[anIdx] = RealLast();
  }

  if (PlanarLineCircleExtrema(C1, C2))
  {
    return;
  }

  D  = C1.Direction();
  D1 = D;
  x2 = C2.XAxis().Direction();
  y2 = C2.YAxis().Direction();
  z2 = C2.Axis().Direction();
  Dx = D.Dot(x2);
  Dy = D.Dot(y2);
  Dz = D.Dot(z2);

  D.SetCoord(Dx, Dy, Dz);
  RefineDir(D);
  D.Coord(Dx, Dy, Dz);

  gp_Pnt O1 = C1.Location();
  gp_Pnt O2 = C2.Location();
  gp_Vec O2O1(O2, O1);

  aTolRO2O1 = gp::Resolution();
  aRO2O1    = O2O1.Magnitude();
  if (aRO2O1 > aTolRO2O1)
  {
    gp_Dir aDO2O1;

    O2O1.Multiply(1. / aRO2O1);
    aDO2O1.SetCoord(O2O1.Dot(x2), O2O1.Dot(y2), O2O1.Dot(z2));
    RefineDir(aDO2O1);
    O2O1.SetXYZ(aRO2O1 * aDO2O1.XYZ());
  }
  else
  {
    O2O1.SetCoord(O2O1.Dot(x2), O2O1.Dot(y2), O2O1.Dot(z2));
  }

  gp_XYZ Vxyz = (D.XYZ() * (O2O1.Dot(D))) - O2O1.XYZ();

  aTol = 1.e-12;

  R  = C2.Radius();
  A5 = R * Dx * Dy;
  A1 = -2. * A5;
  A2 = 0.5 * R * (Dx * Dx - Dy * Dy);
  A3 = Vxyz.Y();
  A4 = -Vxyz.X();

  if (A1 >= -aTol && A1 <= aTol)
  {
    A1 = 0.;
  }
  if (A2 >= -aTol && A2 <= aTol)
  {
    A2 = 0.;
  }
  if (A3 >= -aTol && A3 <= aTol)
  {
    A3 = 0.;
  }
  if (A4 >= -aTol && A4 <= aTol)
  {
    A4 = 0.;
  }
  if (A5 >= -aTol && A5 <= aTol)
  {
    A5 = 0.;
  }

  ExtremaExtElC_TrigonometricRoots Sol(A1, A2, A3, A4, A5, 0., M_PI + M_PI);
  if (!Sol.IsDone())
  {
    return;
  }
  if (Sol.InfiniteRoots())
  {
    myIsPar     = true;
    mySqDist[0] = R * R;
    myNbExt     = 1;
    myDone      = true;
    return;
  }

  int    NoSol, NbSol;
  double U1, U2;
  gp_Pnt P1, P2;

  NbSol = Sol.NbSolutions();
  for (NoSol = 1; NoSol <= NbSol; ++NoSol)
  {
    U2                = Sol.Value(NoSol);
    P2                = ElCLib::Value(U2, C2);
    U1                = (gp_Vec(O1, P2)).Dot(D1);
    P1                = ElCLib::Value(U1, C1);
    mySqDist[myNbExt] = P1.SquareDistance(P2);

    myPoint[myNbExt][0].SetValues(U1, P1);
    myPoint[myNbExt][1].SetValues(U2, P2);

    myNbExt++;
  }
  myDone = true;
}

Extrema_ExtElC::Extrema_ExtElC(const gp_Lin& C1, const gp_Elips& C2)
{

  myIsPar = false;
  myDone  = false;
  myNbExt = 0;
  for (size_t anIdx = 0; anIdx < sizeof(mySqDist) / sizeof(mySqDist[0]); anIdx++)
  {
    mySqDist[anIdx] = RealLast();
  }

  gp_Dir D  = C1.Direction();
  gp_Dir D1 = D;
  gp_Dir x2, y2, z2;
  x2        = C2.XAxis().Direction();
  y2        = C2.YAxis().Direction();
  z2        = C2.Axis().Direction();
  double Dx = D.Dot(x2);
  double Dy = D.Dot(y2);
  double Dz = D.Dot(z2);
  D.SetCoord(Dx, Dy, Dz);

  gp_Pnt O1 = C1.Location();
  gp_Pnt O2 = C2.Location();
  gp_Vec O2O1(O2, O1);
  O2O1.SetCoord(O2O1.Dot(x2), O2O1.Dot(y2), O2O1.Dot(z2));
  gp_XYZ Vxyz = (D.XYZ() * (O2O1.Dot(D))) - O2O1.XYZ();

  double MajR = C2.MajorRadius();
  double MinR = C2.MinorRadius();
  double A5   = MajR * MinR * Dx * Dy;
  double A1   = -2. * A5;
  double R2   = MajR * MajR;
  double r2   = MinR * MinR;
  double A2   = (R2 * Dx * Dx - r2 * Dy * Dy - R2 + r2) / 2.0;
  double A3   = MinR * Vxyz.Y();
  double A4   = -MajR * Vxyz.X();

  double aEps = 1.e-12;

  if (fabs(A5) <= aEps)
    A5 = 0.;
  if (fabs(A1) <= aEps)
    A1 = 0.;
  if (fabs(A2) <= aEps)
    A2 = 0.;
  if (fabs(A3) <= aEps)
    A3 = 0.;
  if (fabs(A4) <= aEps)
    A4 = 0.;

  ExtremaExtElC_TrigonometricRoots Sol(A1, A2, A3, A4, A5, 0., M_PI + M_PI);
  if (!Sol.IsDone())
  {
    return;
  }

  if (Sol.InfiniteRoots())
  {
    myIsPar     = true;
    gp_Pnt aP   = ElCLib::EllipseValue(0., C2.Position(), C2.MajorRadius(), C2.MinorRadius());
    mySqDist[0] = C1.SquareDistance(aP);
    myNbExt     = 1;
    myDone      = true;
    return;
  }

  gp_Pnt P1, P2;
  double U1, U2;
  int    NbSol = Sol.NbSolutions();
  for (int NoSol = 1; NoSol <= NbSol; NoSol++)
  {
    U2                  = Sol.Value(NoSol);
    P2                  = ElCLib::Value(U2, C2);
    U1                  = (gp_Vec(O1, P2)).Dot(D1);
    P1                  = ElCLib::Value(U1, C1);
    mySqDist[myNbExt]   = P1.SquareDistance(P2);
    myPoint[myNbExt][0] = Extrema_POnCurv(U1, P1);
    myPoint[myNbExt][1] = Extrema_POnCurv(U2, P2);
    myNbExt++;
  }
  myDone = true;
}

Extrema_ExtElC::Extrema_ExtElC(const gp_Lin& C1, const gp_Hypr& C2)
{

  myIsPar = false;
  myDone  = false;
  myNbExt = 0;
  for (size_t anIdx = 0; anIdx < sizeof(mySqDist) / sizeof(mySqDist[0]); anIdx++)
  {
    mySqDist[anIdx] = RealLast();
  }

  gp_Dir D  = C1.Direction();
  gp_Dir D1 = D;
  gp_Dir x2, y2, z2;
  x2        = C2.XAxis().Direction();
  y2        = C2.YAxis().Direction();
  z2        = C2.Axis().Direction();
  double Dx = D.Dot(x2);
  double Dy = D.Dot(y2);
  double Dz = D.Dot(z2);
  D.SetCoord(Dx, Dy, Dz);

  gp_Pnt O1 = C1.Location();
  gp_Pnt O2 = C2.Location();
  gp_Vec O2O1(O2, O1);
  O2O1.SetCoord(O2O1.Dot(x2), O2O1.Dot(y2), O2O1.Dot(z2));
  gp_XYZ Vxyz = (D.XYZ() * (O2O1.Dot(D))) - O2O1.XYZ();
  double Vx   = Vxyz.X();
  double Vy   = Vxyz.Y();

  double R  = C2.MajorRadius();
  double r  = C2.MinorRadius();
  double a  = -2 * R * r * Dx * Dy;
  double b  = -R * R * Dx * Dx - r * r * Dy * Dy + R * R + r * r;
  double A1 = a + b;
  double A2 = 2 * R * Vx + 2 * r * Vy;
  double A4 = -2 * R * Vx + 2 * r * Vy;
  double A5 = a - b;

  math_DirectPolynomialRoots Sol(A1, A2, 0.0, A4, A5);
  if (!Sol.IsDone())
  {
    return;
  }

  gp_Pnt P1, P2;
  double U1, U2, v;
  int    NbSol = Sol.NbSolutions();
  for (int NoSol = 1; NoSol <= NbSol; NoSol++)
  {
    v = Sol.Value(NoSol);
    if (v > 0.0)
    {
      U2                  = std::log(v);
      P2                  = ElCLib::Value(U2, C2);
      U1                  = (gp_Vec(O1, P2)).Dot(D1);
      P1                  = ElCLib::Value(U1, C1);
      mySqDist[myNbExt]   = P1.SquareDistance(P2);
      myPoint[myNbExt][0] = Extrema_POnCurv(U1, P1);
      myPoint[myNbExt][1] = Extrema_POnCurv(U2, P2);
      myNbExt++;
    }
  }
  myDone = true;
}

Extrema_ExtElC::Extrema_ExtElC(const gp_Lin& C1, const gp_Parab& C2)
{

  myIsPar = false;
  myDone  = false;
  myNbExt = 0;
  for (size_t anIdx = 0; anIdx < sizeof(mySqDist) / sizeof(mySqDist[0]); anIdx++)
  {
    mySqDist[anIdx] = RealLast();
  }

  gp_Dir D  = C1.Direction();
  gp_Dir D1 = D;
  gp_Dir x2, y2, z2;
  x2        = C2.XAxis().Direction();
  y2        = C2.YAxis().Direction();
  z2        = C2.Axis().Direction();
  double Dx = D.Dot(x2);
  double Dy = D.Dot(y2);
  double Dz = D.Dot(z2);
  D.SetCoord(Dx, Dy, Dz);

  gp_Pnt O1 = C1.Location();
  gp_Pnt O2 = C2.Location();
  gp_Vec O2O1(O2, O1);
  O2O1.SetCoord(O2O1.Dot(x2), O2O1.Dot(y2), O2O1.Dot(z2));
  gp_XYZ Vxyz = (D.XYZ() * (O2O1.Dot(D))) - O2O1.XYZ();

  double P  = C2.Parameter();
  double A1 = (1 - Dx * Dx) / (2.0 * P * P);
  double A2 = (-3.0 * Dx * Dy / (2.0 * P));
  double A3 = (1 - Dy * Dy + Vxyz.X() / P);
  double A4 = Vxyz.Y();

  math_DirectPolynomialRoots Sol(A1, A2, A3, A4);
  if (!Sol.IsDone())
  {
    return;
  }

  gp_Pnt P1, P2;
  double U1, U2;
  int    NbSol = Sol.NbSolutions();
  for (int NoSol = 1; NoSol <= NbSol; NoSol++)
  {
    U2                  = Sol.Value(NoSol);
    P2                  = ElCLib::Value(U2, C2);
    U1                  = (gp_Vec(O1, P2)).Dot(D1);
    P1                  = ElCLib::Value(U1, C1);
    mySqDist[myNbExt]   = P1.SquareDistance(P2);
    myPoint[myNbExt][0] = Extrema_POnCurv(U1, P1);
    myPoint[myNbExt][1] = Extrema_POnCurv(U2, P2);
    myNbExt++;
  }
  myDone = true;
}

Extrema_ExtElC::Extrema_ExtElC(const gp_Circ& C1, const gp_Circ& C2)
{
  bool   bIsSamePlane, bIsSameAxe;
  double aTolD, aTolD2, aTolA, aD2, aDC2;
  gp_Pnt aPc1, aPc2;
  gp_Dir aDc1, aDc2;

  myIsPar = false;
  myDone  = false;
  myNbExt = 0;
  for (size_t anIdx = 0; anIdx < sizeof(mySqDist) / sizeof(mySqDist[0]); anIdx++)
  {
    mySqDist[anIdx] = RealLast();
  }

  aTolA  = Precision::Angular();
  aTolD  = Precision::Confusion();
  aTolD2 = aTolD * aTolD;

  aPc1 = C1.Location();
  aDc1 = C1.Axis().Direction();

  aPc2 = C2.Location();
  aDc2 = C2.Axis().Direction();
  gp_Pln aPlc1(aPc1, aDc1);

  aD2          = aPlc1.SquareDistance(aPc2);
  bIsSamePlane = aDc1.IsParallel(aDc2, aTolA) && aD2 < aTolD2;
  if (!bIsSamePlane)
  {
    return;
  }

  aDC2       = aPc1.SquareDistance(aPc2);
  bIsSameAxe = aDC2 < aTolD2;

  if (bIsSameAxe)
  {
    myIsPar          = true;
    myNbExt          = 1;
    myDone           = true;
    const double aDR = C1.Radius() - C2.Radius();
    mySqDist[0]      = aDR * aDR;
    return;
  }

  bool    bIn, bOut;
  int     j1, j2;
  double  aR1, aR2, aD12, aT11, aT12, aT21, aT22;
  gp_Circ aC1, aC2;
  gp_Pnt  aP11, aP12, aP21, aP22;

  myDone = true;

  aR1 = C1.Radius();
  aR2 = C2.Radius();

  j1  = 0;
  j2  = 1;
  aC1 = C1;
  aC2 = C2;
  if (aR2 > aR1)
  {
    j1  = 1;
    j2  = 0;
    aC1 = C2;
    aC2 = C1;
  }

  aR1 = aC1.Radius();
  aR2 = aC2.Radius();

  aPc1 = aC1.Location();
  aPc2 = aC2.Location();

  aD12 = aPc1.Distance(aPc2);
  gp_Vec aVec12(aPc1, aPc2);
  gp_Dir aDir12(aVec12);

  myNbExt = 4;

  aP11.SetXYZ(aPc1.XYZ() - aR1 * aDir12.XYZ());
  aP12.SetXYZ(aPc1.XYZ() + aR1 * aDir12.XYZ());
  aP21.SetXYZ(aPc2.XYZ() - aR2 * aDir12.XYZ());
  aP22.SetXYZ(aPc2.XYZ() + aR2 * aDir12.XYZ());

  aT11 = ElCLib::Parameter(aC1, aP11);
  aT12 = ElCLib::Parameter(aC1, aP12);
  aT21 = ElCLib::Parameter(aC2, aP21);
  aT22 = ElCLib::Parameter(aC2, aP22);

  myPoint[0][j1].SetValues(aT11, aP11);
  myPoint[0][j2].SetValues(aT21, aP21);
  mySqDist[0] = aP11.SquareDistance(aP21);

  myPoint[1][j1].SetValues(aT11, aP11);
  myPoint[1][j2].SetValues(aT22, aP22);
  mySqDist[1] = aP11.SquareDistance(aP22);

  myPoint[2][j1].SetValues(aT12, aP12);
  myPoint[2][j2].SetValues(aT21, aP21);
  mySqDist[2] = aP12.SquareDistance(aP21);

  myPoint[3][j1].SetValues(aT12, aP12);
  myPoint[3][j2].SetValues(aT22, aP22);
  mySqDist[3] = aP12.SquareDistance(aP22);

  bOut = aD12 > (aR1 + aR2 + aTolD);
  bIn  = aD12 < (aR1 - aR2 - aTolD);
  if (!bOut && !bIn)
  {
    bool   bNbExt6;
    double aAlpha, aBeta, aT[2], aVal, aDist2;
    gp_Pnt aPt, aPL1, aPL2;
    gp_Dir aDLt;

    aAlpha = 0.5 * (aR1 * aR1 - aR2 * aR2 + aD12 * aD12) / aD12;
    aVal   = aR1 * aR1 - aAlpha * aAlpha;
    if (aVal < 0.)
    {
      aVal = -aVal;
    }
    aBeta = std::sqrt(aVal);
    aPt.SetXYZ(aPc1.XYZ() + aAlpha * aDir12.XYZ());

    aDLt = aDc1 ^ aDir12;
    aPL1.SetXYZ(aPt.XYZ() + aBeta * aDLt.XYZ());
    aPL2.SetXYZ(aPt.XYZ() - aBeta * aDLt.XYZ());

    aDist2  = aPL1.SquareDistance(aPL2);
    bNbExt6 = aDist2 > aTolD2;

    myNbExt = 5;
    aT[j1]  = ElCLib::Parameter(aC1, aPL1);
    aT[j2]  = ElCLib::Parameter(aC2, aPL1);
    myPoint[4][j1].SetValues(aT[j1], aPL1);
    myPoint[4][j2].SetValues(aT[j2], aPL1);
    mySqDist[4] = 0.;

    if (bNbExt6)
    {
      myNbExt = 6;
      aT[j1]  = ElCLib::Parameter(aC1, aPL2);
      aT[j2]  = ElCLib::Parameter(aC2, aPL2);
      myPoint[5][j1].SetValues(aT[j1], aPL2);
      myPoint[5][j2].SetValues(aT[j2], aPL2);
      mySqDist[5] = 0.;
    }
  }
}

bool Extrema_ExtElC::IsDone() const
{
  return myDone;
}

bool Extrema_ExtElC::IsParallel() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myIsPar;
}

int Extrema_ExtElC::NbExt() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myNbExt;
}

double Extrema_ExtElC::SquareDistance(const int N) const
{
  if (N < 1 || N > NbExt())
  {
    throw Standard_OutOfRange();
  }

  return mySqDist[N - 1];
}

void Extrema_ExtElC::Points(const int N, Extrema_POnCurv& P1, Extrema_POnCurv& P2) const
{
  if (N < 1 || N > NbExt())
  {
    throw Standard_OutOfRange();
  }

  P1 = myPoint[N - 1][0];
  P2 = myPoint[N - 1][1];
}

void RefineDir(gp_Dir& aDir)
{
  int    i, j, k, iK;
  double aCx[3], aEps, aX1, aX2, aOne;

  iK   = 3;
  aEps = RealEpsilon();
  aDir.Coord(aCx[0], aCx[1], aCx[2]);

  for (i = 0; i < iK; ++i)
  {
    aOne = (aCx[i] > 0.) ? 1. : -1.;
    aX1  = aOne - aEps;
    aX2  = aOne + aEps;

    if (aCx[i] > aX1 && aCx[i] < aX2)
    {
      j      = (i + 1) % iK;
      k      = (i + 2) % iK;
      aCx[i] = aOne;
      aCx[j] = 0.;
      aCx[k] = 0.;
      aDir.SetCoord(aCx[0], aCx[1], aCx[2]);
      return;
    }
  }
}
