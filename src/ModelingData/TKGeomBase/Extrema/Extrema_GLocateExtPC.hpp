#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GeomAbs_CurveType.hpp>
#include <Precision.hpp>
#include <Standard_DomainError.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>

#include <cmath>

template <typename TheCurve,
          typename TheCurveTool,
          typename ThePoint,
          typename TheVector,
          typename ThePOnC,
          typename TheELPC,
          typename TheLocEPC>
class Extrema_GLocateExtPC
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_GLocateExtPC()
      : myC(nullptr),
        mydist2(0.0),
        myismin(false),
        myDone(false),
        myumin(0.0),
        myusup(0.0),
        mytol(0.0),
        type(GeomAbs_OtherCurve),
        numberext(0)
  {
  }

  Extrema_GLocateExtPC(const ThePoint& theP,
                       const TheCurve& theC,
                       const double    theU0,
                       const double    theTolF)
  {
    Initialize(theC,
               TheCurveTool::FirstParameter(theC),
               TheCurveTool::LastParameter(theC),
               theTolF);
    Perform(theP, theU0);
  }

  Extrema_GLocateExtPC(const ThePoint& theP,
                       const TheCurve& theC,
                       const double    theU0,
                       const double    theUmin,
                       const double    theUsup,
                       const double    theTolF)
  {
    Initialize(theC, theUmin, theUsup, theTolF);
    Perform(theP, theU0);
  }

  void Initialize(const TheCurve& theC,
                  const double    theUmin,
                  const double    theUsup,
                  const double    theTolF)
  {
    myC         = const_cast<TheCurve*>(&theC);
    mytol       = theTolF;
    myumin      = theUmin;
    myusup      = theUsup;
    type        = TheCurveTool::GetType(theC);
    double tolu = TheCurveTool::Resolution(theC, Precision::Confusion());
    if ((type == GeomAbs_BSplineCurve) || (type == GeomAbs_BezierCurve)
        || (type == GeomAbs_OffsetCurve) || (type == GeomAbs_OtherCurve))
    {
      myLocExtPC.Initialize(theC, theUmin, theUsup, tolu);
    }
    else
    {
      myExtremPC.Initialize(theC, theUmin, theUsup, tolu);
    }
  }

  void Perform(const ThePoint& theP, const double theU0)
  {
    int    i, i1, i2, inter;
    double Par, valU, valU2 = RealLast(), local_u0;
    double myintuinf = 0, myintusup = 0;
    local_u0 = theU0;
    switch (type)
    {
      case GeomAbs_OtherCurve:
      case GeomAbs_OffsetCurve:
      case GeomAbs_BSplineCurve:
      {

        int                        n = TheCurveTool::NbIntervals(*myC, GeomAbs_C2);
        NCollection_Array1<double> theInter(1, n + 1);
        TheCurveTool::Intervals(*myC, theInter, GeomAbs_C2);

        if (local_u0 < myumin)
        {
          local_u0 = myumin;
        }
        else if (local_u0 > myusup)
        {
          local_u0 = myusup;
        }

        bool found = false;
        inter      = 1;
        while (!found && inter <= n)
        {
          myintuinf = std::max(theInter(inter), myumin);
          myintusup = std::min(theInter(inter + 1), myusup);
          if ((local_u0 >= myintuinf) && (local_u0 < myintusup))
            found = true;
          inter++;
        }

        if (found)
          inter--;

        myLocExtPC.Initialize(*myC, myintuinf, myintusup, mytol);
        myLocExtPC.Perform(theP, local_u0);
        myDone = myLocExtPC.IsDone();
        if (myDone)
        {
          mypp    = myLocExtPC.Point();
          myismin = myLocExtPC.IsMin();
          mydist2 = myLocExtPC.SquareDistance();
        }
        else
        {
          int k = 1;

          i1 = inter;
          i2 = inter;
          double    s1inf, s2inf, s1sup, s2sup;
          ThePoint  P1;
          TheVector V1;
          TheCurveTool::D1(*myC, myintuinf, P1, V1);
          s2inf = (TheVector(theP, P1) * V1);
          TheCurveTool::D1(*myC, myintusup, P1, V1);
          s1sup = (TheVector(theP, P1) * V1);

          while (!myDone && (i2 > 0) && (i1 <= n))
          {
            i1 = inter + k;
            i2 = inter - k;
            if (i1 <= n)
            {
              myintuinf = std::max(theInter(i1), myumin);
              myintusup = std::min(theInter(i1 + 1), myusup);
              if (myintuinf < myintusup)
              {
                TheCurveTool::D1(*myC, myintuinf, P1, V1);
                s2sup = (TheVector(theP, P1) * V1);
                if (Precision::IsInfinite(s2sup) || Precision::IsInfinite(s1sup))
                {
                  break;
                }
                if (s1sup * s2sup <= RealEpsilon())
                {

                  myDone = true;
                  mypp.SetValues(myintuinf, P1);
                  myismin = (s1sup <= 0.0);
                  mydist2 = theP.SquareDistance(P1);
                  break;
                }

                TheCurveTool::D1(*myC, myintusup, P1, V1);
                s1sup = (TheVector(theP, P1) * V1);
                myLocExtPC.Initialize(*myC, myintuinf, myintusup, mytol);
                myLocExtPC.Perform(theP, (myintuinf + myintusup) * 0.5);
                myDone = myLocExtPC.IsDone();
                if (myDone)
                {
                  mypp    = myLocExtPC.Point();
                  myismin = myLocExtPC.IsMin();
                  mydist2 = myLocExtPC.SquareDistance();
                  break;
                }
              }
            }

            if (i2 > 0)
            {
              myintuinf = std::max(theInter(i2), myumin);
              myintusup = std::min(theInter(i2 + 1), myusup);
              if (myintuinf < myintusup)
              {
                TheCurveTool::D1(*myC, myintusup, P1, V1);
                s1inf = (TheVector(theP, P1) * V1);
                if (Precision::IsInfinite(s2inf) || Precision::IsInfinite(s1inf))
                {
                  break;
                }
                if (s1inf * s2inf <= RealEpsilon())
                {

                  myDone = true;
                  mypp.SetValues(myintusup, P1);
                  myismin = (s1inf <= 0.0);
                  mydist2 = theP.SquareDistance(P1);
                  break;
                }

                TheCurveTool::D1(*myC, myintuinf, P1, V1);
                s2inf = (TheVector(theP, P1) * V1);
                myLocExtPC.Initialize(*myC, myintuinf, myintusup, mytol);
                myLocExtPC.Perform(theP, (myintuinf + myintusup) * 0.5);
                myDone = myLocExtPC.IsDone();

                if (myDone)
                {
                  mypp    = myLocExtPC.Point();
                  myismin = myLocExtPC.IsMin();
                  mydist2 = myLocExtPC.SquareDistance();
                  break;
                }
              }
            }

            k++;
          }
        }
      }

      break;

      case GeomAbs_BezierCurve:
      {
        myLocExtPC.Perform(theP, theU0);
        myDone = myLocExtPC.IsDone();
      }

      break;
      default:
      {
        myExtremPC.Perform(theP);
        numberext = 0;
        if (myExtremPC.IsDone())
        {
          for (i = 1; i <= myExtremPC.NbExt(); i++)
          {
            Par  = myExtremPC.Point(i).Parameter();
            valU = std::abs(Par - theU0);
            if (valU <= valU2)
            {
              valU2     = valU;
              numberext = i;
              myDone    = true;
            }
          }
        }

        if (numberext == 0)
          myDone = false;

        break;
      }
    }
  }

  bool IsDone() const { return myDone; }

  double SquareDistance() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    double d = 0;
    if ((type == GeomAbs_BezierCurve))
    {
      d = myLocExtPC.SquareDistance();
    }
    else if (type == GeomAbs_BSplineCurve || type == GeomAbs_OffsetCurve
             || type == GeomAbs_OtherCurve)
    {
      d = mydist2;
    }
    else
    {
      if (numberext != 0)
      {
        d = myExtremPC.SquareDistance(numberext);
      }
    }
    return d;
  }

  bool IsMin() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    bool b = false;
    if ((type == GeomAbs_BezierCurve))
    {
      b = myLocExtPC.IsMin();
    }
    else if (type == GeomAbs_BSplineCurve || type == GeomAbs_OffsetCurve
             || type == GeomAbs_OtherCurve)
    {
      b = myismin;
    }
    else
    {
      if (numberext != 0)
      {
        b = myExtremPC.IsMin(numberext);
      }
    }
    return b;
  }

  const ThePOnC& Point() const
  {
    if (!IsDone())
    {
      throw StdFail_NotDone();
    }
    if (type == GeomAbs_BezierCurve)
    {
      return myLocExtPC.Point();
    }
    else if (type == GeomAbs_BSplineCurve || type == GeomAbs_OffsetCurve
             || type == GeomAbs_OtherCurve)
    {
      return mypp;
    }
    return myExtremPC.Point(numberext);
  }

private:
  ThePOnC           mypp;
  TheCurve*         myC;
  double            mydist2;
  bool              myismin;
  bool              myDone;
  double            myumin;
  double            myusup;
  double            mytol;
  TheLocEPC         myLocExtPC;
  TheELPC           myExtremPC;
  GeomAbs_CurveType type;
  int               numberext;
};
