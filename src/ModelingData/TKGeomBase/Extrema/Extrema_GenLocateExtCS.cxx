#include <Adaptor3d_Surface.hpp>
#include <Extrema_FuncExtCS.hpp>
#include <Extrema_GenLocateExtCS.hpp>
#include <Extrema_POnCurv.hpp>
#include <Extrema_POnSurf.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_NewtonFunctionSetRoot.hpp>
#include <math_Vector.hpp>
#include <StdFail_NotDone.hpp>

Extrema_GenLocateExtCS::Extrema_GenLocateExtCS()
    : myDone(false),
      mySqDist(RealLast())
{
}

Extrema_GenLocateExtCS::Extrema_GenLocateExtCS(const Adaptor3d_Curve&   C,
                                               const Adaptor3d_Surface& S,
                                               const double             T,
                                               const double             U,
                                               const double             V,
                                               const double             Tol1,
                                               const double             Tol2)
{
  Perform(C, S, T, U, V, Tol1, Tol2);
}

void Extrema_GenLocateExtCS::Perform(const Adaptor3d_Curve&   C,
                                     const Adaptor3d_Surface& S,
                                     const double             T,
                                     const double             U,
                                     const double             V,
                                     const double             Tol1,
                                     const double             Tol2)
{
  myDone = false;

  double Tinf, Tsup;
  Tinf = C.FirstParameter();
  Tsup = C.LastParameter();

  double Uinf, Usup, Vinf, Vsup;
  Uinf = S.FirstUParameter();
  Usup = S.LastUParameter();
  Vinf = S.FirstVParameter();
  Vsup = S.LastVParameter();

  Extrema_FuncExtCS F(C, S);
  math_Vector       Tol(1, 3), Start(1, 3), BInf(1, 3), BSup(1, 3);
  Tol(1) = Tol1;
  Tol(2) = Tol2;
  Tol(3) = Tol2;

  Start(1) = T;
  Start(2) = U;
  Start(3) = V;

  BInf(1) = Tinf;
  BInf(2) = Uinf;
  BInf(3) = Vinf;

  BSup(1) = Tsup;
  BSup(2) = Usup;
  BSup(3) = Vsup;

  math_FunctionSetRoot SR(F, Tol);
  SR.Perform(F, Start, BInf, BSup);
  if (!SR.IsDone())
    return;

  mySqDist = F.SquareDistance(1);
  myPoint1 = F.PointOnCurve(1);
  myPoint2 = F.PointOnSurface(1);
  myDone   = true;
}

bool Extrema_GenLocateExtCS::IsDone() const
{
  return myDone;
}

double Extrema_GenLocateExtCS::SquareDistance() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return mySqDist;
}

const Extrema_POnCurv& Extrema_GenLocateExtCS::PointOnCurve() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myPoint1;
}

const Extrema_POnSurf& Extrema_GenLocateExtCS::PointOnSurface() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myPoint2;
}
