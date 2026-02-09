#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_FunctionRoots.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>

template <typename TheCurve, typename TheTool, typename ThePOnC, typename ThePoint, typename ThePCF>
class Extrema_GGenExtPC
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_GGenExtPC()
      : myDone(false),
        myInit(false),
        mynbsample(0),
        myumin(0.0),
        myusup(0.0),
        mytolu(0.0),
        mytolF(0.0)
  {
  }

  Extrema_GGenExtPC(const ThePoint& theP,
                    const TheCurve& theC,
                    const int       theNbSample,
                    const double    theTolU,
                    const double    theTolF)
      : myF(theP, theC)
  {
    Initialize(theC, theNbSample, theTolU, theTolF);
    Perform(theP);
  }

  Extrema_GGenExtPC(const ThePoint& theP,
                    const TheCurve& theC,
                    const int       theNbSample,
                    const double    theUmin,
                    const double    theUsup,
                    const double    theTolU,
                    const double    theTolF)
      : myF(theP, theC)
  {
    Initialize(theC, theNbSample, theUmin, theUsup, theTolU, theTolF);
    Perform(theP);
  }

  void Initialize(const TheCurve& theC,
                  const int       theNbU,
                  const double    theTolU,
                  const double    theTolF)
  {
    myInit     = true;
    mynbsample = theNbU;
    mytolu     = theTolU;
    mytolF     = theTolF;
    myF.Initialize(theC);
    myumin = TheTool::FirstParameter(theC);
    myusup = TheTool::LastParameter(theC);
  }

  void Initialize(const TheCurve& theC,
                  const int       theNbU,
                  const double    theUmin,
                  const double    theUsup,
                  const double    theTolU,
                  const double    theTolF)
  {
    myInit     = true;
    mynbsample = theNbU;
    mytolu     = theTolU;
    mytolF     = theTolF;
    myF.Initialize(theC);
    myumin = theUmin;
    myusup = theUsup;
  }

  void Initialize(const int    theNbU,
                  const double theUmin,
                  const double theUsup,
                  const double theTolU,
                  const double theTolF)
  {
    mynbsample = theNbU;
    mytolu     = theTolU;
    mytolF     = theTolF;
    myumin     = theUmin;
    myusup     = theUsup;
  }

  void Initialize(const TheCurve& theC) { myF.Initialize(theC); }

  void Perform(const ThePoint& theP)
  {
    myF.SetPoint(theP);
    myF.SubIntervalInitialize(myumin, myusup);
    myDone = false;

    math_FunctionRoots S(myF, myumin, myusup, mynbsample, mytolu, mytolF, mytolF);
    if (!S.IsDone() || S.IsAllNull())
    {
      return;
    }

    myDone = true;
  }

  bool IsDone() const { return myDone; }

  int NbExt() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    return myF.NbExt();
  }

  double SquareDistance(const int theN) const
  {
    if ((theN < 1) || (theN > NbExt()))
    {
      throw Standard_OutOfRange();
    }
    return myF.SquareDistance(theN);
  }

  bool IsMin(const int theN) const
  {
    if ((theN < 1) || (theN > NbExt()))
    {
      throw Standard_OutOfRange();
    }
    return myF.IsMin(theN);
  }

  const ThePOnC& Point(const int theN) const
  {
    if ((theN < 1) || (theN > NbExt()))
    {
      throw Standard_OutOfRange();
    }
    return myF.Point(theN);
  }

private:
  bool   myDone;
  bool   myInit;
  int    mynbsample;
  double myumin;
  double myusup;
  double mytolu;
  double mytolF;
  ThePCF myF;
};
