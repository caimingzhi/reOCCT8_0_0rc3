#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_FunctionRoot.hpp>
#include <StdFail_NotDone.hpp>

#include <cmath>

template <typename TheCurve,
          typename TheTool,
          typename ThePOnC,
          typename ThePnt,
          typename ThePCLocF>
class Extrema_GenLocateExtPC
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_GenLocateExtPC()
      : myDone(false),
        mytolU(0.0),
        myumin(0.0),
        myusup(0.0)
  {
  }

  Extrema_GenLocateExtPC(const ThePnt&   theP,
                         const TheCurve& theC,
                         const double    theU0,
                         const double    theTolU)
  {
    Initialize(theC, TheTool::FirstParameter(theC), TheTool::LastParameter(theC), theTolU);
    Perform(theP, theU0);
  }

  Extrema_GenLocateExtPC(const ThePnt&   theP,
                         const TheCurve& theC,
                         const double    theU0,
                         const double    theUmin,
                         const double    theUsup,
                         const double    theTolU)
  {
    Initialize(theC, theUmin, theUsup, theTolU);
    Perform(theP, theU0);
  }

  void Initialize(const TheCurve& theC,
                  const double    theUmin,
                  const double    theUsup,
                  const double    theTolU)
  {
    myDone = false;
    myF.Initialize(theC);
    myumin = theUmin;
    myusup = theUsup;
    mytolU = theTolU;
  }

  void Perform(const ThePnt& theP, const double theU0)
  {
    myF.SetPoint(theP);
    math_FunctionRoot S(myF, theU0, mytolU, myumin, myusup);
    myDone = S.IsDone();
    if (myDone)
    {
      double         uu, ff;
      const ThePOnC& PP = Point();
      uu                = PP.Parameter();
      if (myF.Value(uu, ff))
      {
        if (std::abs(ff) >= 1.e-07)
          myDone = false;
      }
      else
        myDone = false;
    }
  }

  bool IsDone() const { return myDone; }

  double SquareDistance() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    return myF.SquareDistance(1);
  }

  bool IsMin() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    return myF.IsMin(1);
  }

  const ThePOnC& Point() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    return myF.Point(1);
  }

private:
  bool      myDone;
  double    mytolU;
  double    myumin;
  double    myusup;
  ThePCLocF myF;
};
