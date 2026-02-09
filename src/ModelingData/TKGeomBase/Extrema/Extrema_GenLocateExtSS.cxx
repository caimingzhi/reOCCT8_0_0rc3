#include <Adaptor3d_Surface.hpp>
#include <Extrema_FuncExtSS.hpp>
#include <Extrema_GenLocateExtSS.hpp>
#include <Extrema_POnSurf.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_NewtonFunctionSetRoot.hpp>
#include <math_Vector.hpp>
#include <StdFail_NotDone.hpp>

Extrema_GenLocateExtSS::Extrema_GenLocateExtSS()
    : myDone(false),
      mySqDist(RealLast())
{
}

Extrema_GenLocateExtSS::Extrema_GenLocateExtSS(const Adaptor3d_Surface& S1,
                                               const Adaptor3d_Surface& S2,
                                               const double             U1,
                                               const double             V1,
                                               const double             U2,
                                               const double             V2,
                                               const double             Tol1,
                                               const double             Tol2)
{
  Perform(S1, S2, U1, V1, U2, V2, Tol1, Tol2);
}

void Extrema_GenLocateExtSS::Perform(const Adaptor3d_Surface& S1,
                                     const Adaptor3d_Surface& S2,
                                     const double             U1,
                                     const double             V1,
                                     const double             U2,
                                     const double             V2,
                                     const double             Tol1,
                                     const double             Tol2)
{
  myDone = false;

  double Uinf1, Usup1, Vinf1, Vsup1;
  Uinf1 = S1.FirstUParameter();
  Usup1 = S1.LastUParameter();
  Vinf1 = S1.FirstVParameter();
  Vsup1 = S1.LastVParameter();

  double Uinf2, Usup2, Vinf2, Vsup2;
  Uinf2 = S2.FirstUParameter();
  Usup2 = S2.LastUParameter();
  Vinf2 = S2.FirstVParameter();
  Vsup2 = S2.LastVParameter();

  Extrema_FuncExtSS F(S1, S2);
  math_Vector       Tol(1, 4), Start(1, 4), BInf(1, 4), BSup(1, 4);

  Tol(1) = Tol1;
  Tol(2) = Tol1;
  Tol(3) = Tol2;
  Tol(4) = Tol2;

  Start(1) = U1;
  Start(2) = V1;
  Start(3) = U2;
  Start(4) = V2;

  BInf(1) = Uinf1;
  BInf(2) = Vinf1;
  BInf(3) = Uinf2;
  BInf(4) = Vinf2;
  BSup(1) = Usup1;
  BSup(2) = Vsup1;
  BSup(3) = Usup2;
  BSup(4) = Vsup2;

  math_FunctionSetRoot SR(F, Tol);
  SR.Perform(F, Start, BInf, BSup);
  if (!SR.IsDone())
    return;

  mySqDist = F.SquareDistance(1);
  myPoint1 = F.PointOnS1(1);
  myPoint2 = F.PointOnS2(1);
  myDone   = true;
}

bool Extrema_GenLocateExtSS::IsDone() const
{
  return myDone;
}

double Extrema_GenLocateExtSS::SquareDistance() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return mySqDist;
}

const Extrema_POnSurf& Extrema_GenLocateExtSS::PointOnS1() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myPoint1;
}

const Extrema_POnSurf& Extrema_GenLocateExtSS::PointOnS2() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myPoint2;
}
