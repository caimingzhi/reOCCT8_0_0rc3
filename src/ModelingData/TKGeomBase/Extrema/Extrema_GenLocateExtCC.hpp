#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_FunctionSetRoot.hpp>
#include <math_Vector.hpp>
#include <StdFail_NotDone.hpp>

template <typename TheCurve, typename TheTool, typename ThePOnC, typename TheCCLocF>
class Extrema_GenLocateExtCC
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_GenLocateExtCC(const TheCurve& theC1,
                         const TheCurve& theC2,
                         const double    theU0,
                         const double    theV0,
                         const double    theTolU,
                         const double    theTolV)
  {
    myDone   = false;
    mySqDist = RealLast();

    double Uinf = TheTool::FirstParameter(theC1);
    double Usup = TheTool::LastParameter(theC1);
    double Uu;
    if (Uinf > Usup)
    {
      Uu   = Uinf;
      Uinf = Usup;
      Usup = Uu;
    }

    double Vinf = TheTool::FirstParameter(theC2);
    double Vsup = TheTool::LastParameter(theC2);
    if (Vinf > Vsup)
    {
      Uu   = Vinf;
      Vinf = Vsup;
      Vsup = Uu;
    }

    TheCCLocF   F(theC1, theC2);
    math_Vector Tol(1, 2);
    Tol(1)      = theTolU;
    Tol(2)      = theTolV;
    double Tolf = 1.e-10;

    math_Vector Start(1, 2);
    math_Vector Uuinf(1, 2);
    math_Vector Uusup(1, 2);

    Start(1) = theU0;
    Start(2) = theV0;

    Uuinf(1) = Uinf;
    Uuinf(2) = Vinf;
    Uusup(1) = Usup;
    Uusup(2) = Vsup;

    math_FunctionSetRoot S(F, Tol);
    S.Perform(F, Start, Uuinf, Uusup);

    if (S.IsDone() && F.NbExt() > 0)
    {
      mySqDist = F.SquareDistance(1);
      F.Points(1, myPoint1, myPoint2);
      Start(1) = myPoint1.Parameter();
      Start(2) = myPoint2.Parameter();
      math_Vector Ff(1, 2);
      F.Value(Start, Ff);
      if ((Ff(1) < Tolf) && (Ff(2) < Tolf))
        myDone = true;
    }
  }

  bool IsDone() const { return myDone; }

  double SquareDistance() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    return mySqDist;
  }

  void Point(ThePOnC& theP1, ThePOnC& theP2) const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    theP1 = myPoint1;
    theP2 = myPoint2;
  }

private:
  bool    myDone;
  double  mySqDist;
  ThePOnC myPoint1;
  ThePOnC myPoint2;
};
