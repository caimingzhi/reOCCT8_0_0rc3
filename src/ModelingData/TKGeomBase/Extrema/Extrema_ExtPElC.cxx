

#include <ElCLib.hpp>
#include <Extrema_ExtPElC.hpp>
#include <Extrema_POnCurv.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <math_DirectPolynomialRoots.hpp>
#include <math_TrigonometricFunctionRoots.hpp>
#include <Precision.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

Extrema_ExtPElC::Extrema_ExtPElC()
{
  myDone  = false;
  myNbExt = 0;

  for (int i = 0; i < 4; i++)
  {
    mySqDist[i] = RealLast();
    myIsMin[i]  = false;
  }
}

Extrema_ExtPElC::Extrema_ExtPElC(const gp_Pnt& P,
                                 const gp_Lin& L,
                                 const double  Tol,
                                 const double  Uinf,
                                 const double  Usup)
{
  Perform(P, L, Tol, Uinf, Usup);
}

void Extrema_ExtPElC::Perform(const gp_Pnt& P,
                              const gp_Lin& L,
                              const double  Tol,
                              const double  Uinf,
                              const double  Usup)
{
  myDone  = false;
  myNbExt = 0;
  gp_Vec V1(L.Direction());
  gp_Pnt OR = L.Location();
  gp_Vec V(OR, P);
  double Mydist = V1.Dot(V);
  if ((Mydist >= Uinf - Tol) && (Mydist <= Usup + Tol))
  {

    gp_Pnt          MyP = OR.Translated(Mydist * V1);
    Extrema_POnCurv MyPOnCurve(Mydist, MyP);
    mySqDist[0] = P.SquareDistance(MyP);
    myPoint[0]  = MyPOnCurve;
    myIsMin[0]  = true;
    myNbExt     = 1;
    myDone      = true;
  }
}

Extrema_ExtPElC::Extrema_ExtPElC(const gp_Pnt&  P,
                                 const gp_Circ& C,
                                 const double   Tol,
                                 const double   Uinf,
                                 const double   Usup)
{
  Perform(P, C, Tol, Uinf, Usup);
}

void Extrema_ExtPElC::Perform(const gp_Pnt&  P,
                              const gp_Circ& C,
                              const double   Tol,
                              const double   Uinf,
                              const double   Usup)

{
  myDone  = false;
  myNbExt = 0;

  gp_Pnt O = C.Location();
  gp_Vec Axe(C.Axis().Direction());
  gp_Vec Trsl = Axe.Multiplied(-(gp_Vec(O, P).Dot(Axe)));
  gp_Pnt Pp   = P.Translated(Trsl);

  gp_Vec OPp(O, Pp);
  if (OPp.Magnitude() < Tol)
  {
    return;
  }
  double Usol[2];
  Usol[0] = C.XAxis().Direction().AngleWithRef(OPp, Axe);

  constexpr double aAngTol = Precision::Angular();
  if (Usol[0] + M_PI < aAngTol)
    Usol[0] = -M_PI;
  else if (Usol[0] - M_PI > -aAngTol)
    Usol[0] = M_PI;

  Usol[1] = Usol[0] + M_PI;

  double myuinf = Uinf;

  double TolU, aR;
  aR   = C.Radius();
  TolU = Precision::Infinite();
  if (aR > gp::Resolution())
  {
    TolU = Tol / aR;
  }

  ElCLib::AdjustPeriodic(Uinf, Uinf + 2 * M_PI, TolU, myuinf, Usol[0]);
  ElCLib::AdjustPeriodic(Uinf, Uinf + 2 * M_PI, TolU, myuinf, Usol[1]);
  if (((Usol[0] - 2 * M_PI - Uinf) < TolU) && ((Usol[0] - 2 * M_PI - Uinf) > -TolU))
    Usol[0] = Uinf;
  if (((Usol[1] - 2 * M_PI - Uinf) < TolU) && ((Usol[1] - 2 * M_PI - Uinf) > -TolU))
    Usol[1] = Uinf;

  gp_Pnt Cu;
  double Us;
  for (int NoSol = 0; NoSol <= 1; NoSol++)
  {
    Us = Usol[NoSol];
    if (((Uinf - Us) < TolU) && ((Us - Usup) < TolU))
    {
      Cu                = ElCLib::Value(Us, C);
      mySqDist[myNbExt] = Cu.SquareDistance(P);
      myIsMin[myNbExt]  = (NoSol == 0);
      myPoint[myNbExt]  = Extrema_POnCurv(Us, Cu);
      myNbExt++;
    }
  }
  myDone = true;
}

Extrema_ExtPElC::Extrema_ExtPElC(const gp_Pnt&   P,
                                 const gp_Elips& C,
                                 const double    Tol,
                                 const double    Uinf,
                                 const double    Usup)
{
  Perform(P, C, Tol, Uinf, Usup);
}

void Extrema_ExtPElC::Perform(const gp_Pnt&   P,
                              const gp_Elips& C,
                              const double    Tol,
                              const double    Uinf,
                              const double    Usup)

{
  myDone  = false;
  myNbExt = 0;

  gp_Pnt O = C.Location();
  gp_Vec Axe(C.Axis().Direction());
  gp_Vec Trsl = Axe.Multiplied(-(gp_Vec(O, P).Dot(Axe)));
  gp_Pnt Pp   = P.Translated(Trsl);

  int    NoSol, NbSol;
  double A = C.MajorRadius();
  double B = C.MinorRadius();
  gp_Vec OPp(O, Pp);
  double OPpMagn = OPp.Magnitude();
  if (OPpMagn < Tol)
  {
    if (std::abs(A - B) < Tol)
    {
      return;
    }
  }
  double X = OPp.Dot(gp_Vec(C.XAxis().Direction()));
  double Y = OPp.Dot(gp_Vec(C.YAxis().Direction()));

  double ko2 = (B * B - A * A) / 2., ko3 = -B * Y, ko4 = A * X;
  if (std::abs(ko3) < 1.e-16 * std::max(std::abs(ko2), std::abs(ko3)))
    ko3 = 0.0;

  math_TrigonometricFunctionRoots Sol(0., ko2, ko3, ko4, 0., Uinf, Usup);

  if (!Sol.IsDone())
  {
    return;
  }
  gp_Pnt Cu;
  double Us;
  NbSol = Sol.NbSolutions();
  for (NoSol = 1; NoSol <= NbSol; NoSol++)
  {
    Us                = Sol.Value(NoSol);
    Cu                = ElCLib::Value(Us, C);
    mySqDist[myNbExt] = Cu.SquareDistance(P);
    myPoint[myNbExt]  = Extrema_POnCurv(Us, Cu);
    Cu                = ElCLib::Value(Us + 0.1, C);
    myIsMin[myNbExt]  = mySqDist[myNbExt] < Cu.SquareDistance(P);
    myNbExt++;
  }
  myDone = true;
}

Extrema_ExtPElC::Extrema_ExtPElC(const gp_Pnt&  P,
                                 const gp_Hypr& C,
                                 const double   Tol,
                                 const double   Uinf,
                                 const double   Usup)
{
  Perform(P, C, Tol, Uinf, Usup);
}

void Extrema_ExtPElC::Perform(const gp_Pnt&  P,
                              const gp_Hypr& C,
                              const double   Tol,
                              const double   Uinf,
                              const double   Usup)

{
  myDone  = false;
  myNbExt = 0;

  gp_Pnt O = C.Location();
  gp_Vec Axe(C.Axis().Direction());
  gp_Vec Trsl = Axe.Multiplied(-(gp_Vec(O, P).Dot(Axe)));
  gp_Pnt Pp   = P.Translated(Trsl);

  double Tol2 = Tol * Tol;
  double R    = C.MajorRadius();
  double r    = C.MinorRadius();
  gp_Vec OPp(O, Pp);
  double X = OPp.Dot(gp_Vec(C.XAxis().Direction()));
  double Y = OPp.Dot(gp_Vec(C.YAxis().Direction()));

  double                     C1 = (R * R + r * r) / 4.;
  math_DirectPolynomialRoots Sol(C1, -(X * R + Y * r) / 2., 0., (X * R - Y * r) / 2., -C1);
  if (!Sol.IsDone())
  {
    return;
  }
  gp_Pnt Cu;
  double Us, Vs;
  int    NbSol = Sol.NbSolutions();
  bool   DejaEnr;
  int    NoExt;
  gp_Pnt TbExt[4];
  for (int NoSol = 1; NoSol <= NbSol; NoSol++)
  {
    Vs = Sol.Value(NoSol);
    if (Vs > 0.)
    {
      Us = std::log(Vs);
      if ((Us >= Uinf) && (Us <= Usup))
      {
        Cu      = ElCLib::Value(Us, C);
        DejaEnr = false;
        for (NoExt = 0; NoExt < myNbExt; NoExt++)
        {
          if (TbExt[NoExt].SquareDistance(Cu) < Tol2)
          {
            DejaEnr = true;
            break;
          }
        }
        if (!DejaEnr)
        {
          TbExt[myNbExt]    = Cu;
          mySqDist[myNbExt] = Cu.SquareDistance(P);
          myIsMin[myNbExt]  = mySqDist[myNbExt] < P.SquareDistance(ElCLib::Value(Us + 1, C));
          myPoint[myNbExt]  = Extrema_POnCurv(Us, Cu);
          myNbExt++;
        }
      }
    }
  }
  myDone = true;
}

Extrema_ExtPElC::Extrema_ExtPElC(const gp_Pnt&   P,
                                 const gp_Parab& C,
                                 const double    Tol,
                                 const double    Uinf,
                                 const double    Usup)
{
  Perform(P, C, Tol, Uinf, Usup);
}

void Extrema_ExtPElC::Perform(const gp_Pnt&   P,
                              const gp_Parab& C,

                              const double,
                              const double Uinf,
                              const double Usup)

{
  myDone  = false;
  myNbExt = 0;

  gp_Pnt O = C.Location();
  gp_Vec Axe(C.Axis().Direction());
  gp_Vec Trsl = Axe.Multiplied(-(gp_Vec(O, P).Dot(Axe)));
  gp_Pnt Pp   = P.Translated(Trsl);

  double                     F = C.Focal();
  gp_Vec                     OPp(O, Pp);
  double                     X = OPp.Dot(gp_Vec(C.XAxis().Direction()));
  double                     Y = OPp.Dot(gp_Vec(C.YAxis().Direction()));
  math_DirectPolynomialRoots Sol(1. / (4. * F), 0., 2. * F - X, -2. * F * Y);
  if (!Sol.IsDone())
  {
    return;
  }
  gp_Pnt Cu;
  double Us;
  int    NbSol = Sol.NbSolutions();
  bool   DejaEnr;
  int    NoExt;
  gp_Pnt TbExt[3];
  for (int NoSol = 1; NoSol <= NbSol; NoSol++)
  {
    Us = Sol.Value(NoSol);
    if ((Us >= Uinf) && (Us <= Usup))
    {
      Cu      = ElCLib::Value(Us, C);
      DejaEnr = false;
      for (NoExt = 0; NoExt < myNbExt; NoExt++)
      {
        if (TbExt[NoExt].SquareDistance(Cu) < Precision::SquareConfusion())
        {
          DejaEnr = true;
          break;
        }
      }
      if (!DejaEnr)
      {
        TbExt[myNbExt]    = Cu;
        mySqDist[myNbExt] = Cu.SquareDistance(P);
        myIsMin[myNbExt]  = mySqDist[myNbExt] < P.SquareDistance(ElCLib::Value(Us + 1, C));
        myPoint[myNbExt]  = Extrema_POnCurv(Us, Cu);
        myNbExt++;
      }
    }
  }
  myDone = true;
}

bool Extrema_ExtPElC::IsDone() const
{
  return myDone;
}

int Extrema_ExtPElC::NbExt() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myNbExt;
}

double Extrema_ExtPElC::SquareDistance(const int N) const
{
  if ((N < 1) || (N > NbExt()))
  {
    throw Standard_OutOfRange();
  }
  return mySqDist[N - 1];
}

bool Extrema_ExtPElC::IsMin(const int N) const
{
  if ((N < 1) || (N > NbExt()))
  {
    throw Standard_OutOfRange();
  }
  return myIsMin[N - 1];
}

const Extrema_POnCurv& Extrema_ExtPElC::Point(const int N) const
{
  if ((N < 1) || (N > NbExt()))
  {
    throw Standard_OutOfRange();
  }
  return myPoint[N - 1];
}
