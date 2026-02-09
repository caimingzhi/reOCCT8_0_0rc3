#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GeomAbs_CurveType.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <Precision.hpp>
#include <Standard_TypeMismatch.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>

#include <cmath>

template <typename TheCurve,
          typename TheCurveTool,
          typename ThePOnC,
          typename ThePoint,
          typename TheVector,
          typename TheSeqPOnC>
class Extrema_GFuncExtPC : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Extrema_GFuncExtPC()
      : myC(nullptr),
        myU(0.0),
        myD1f(0.0),
        myPinit(false),
        myCinit(false),
        myD1Init(false),
        myTol(MinTol),
        myMaxDerivOrder(0),
        myUinfium(0.0),
        myUsupremum(0.0)
  {
  }

  Extrema_GFuncExtPC(const ThePoint& theP, const TheCurve& theC)
      : myP(theP),
        myC(const_cast<TheCurve*>(&theC)),
        myU(0.0),
        myD1f(0.0),
        myPinit(true),
        myCinit(true),
        myD1Init(false)
  {
    SubIntervalInitialize(TheCurveTool::FirstParameter(theC), TheCurveTool::LastParameter(theC));

    switch (TheCurveTool::GetType(theC))
    {
      case GeomAbs_BezierCurve:
      case GeomAbs_BSplineCurve:
      case GeomAbs_OffsetCurve:
      case GeomAbs_OtherCurve:
        myMaxDerivOrder = MaxOrder;
        myTol           = SearchOfTolerance();
        break;
      default:
        myMaxDerivOrder = 0;
        myTol           = MinTol;
        break;
    }
  }

  void Initialize(const TheCurve& theC)
  {
    myC     = const_cast<TheCurve*>(&theC);
    myCinit = true;
    myPoint.Clear();
    mySqDist.Clear();
    myIsMin.Clear();

    SubIntervalInitialize(TheCurveTool::FirstParameter(theC), TheCurveTool::LastParameter(theC));

    switch (TheCurveTool::GetType(theC))
    {
      case GeomAbs_BezierCurve:
      case GeomAbs_BSplineCurve:
      case GeomAbs_OffsetCurve:
      case GeomAbs_OtherCurve:
        myMaxDerivOrder = MaxOrder;
        myTol           = SearchOfTolerance();
        break;
      default:
        myMaxDerivOrder = 0;
        myTol           = MinTol;
        break;
    }
  }

  void SetPoint(const ThePoint& theP)
  {
    myP     = theP;
    myPinit = true;
    myPoint.Clear();
    mySqDist.Clear();
    myIsMin.Clear();
  }

  bool Value(const double theU, double& theF) override
  {
    if (!myPinit || !myCinit)
    {
      throw Standard_TypeMismatch("No init");
    }

    myU = theU;
    TheVector D1c;
    TheCurveTool::D1(*myC, myU, myPc, D1c);

    if (Precision::IsInfinite(D1c.X()) || Precision::IsInfinite(D1c.Y()))
    {
      theF = Precision::Infinite();
      return false;
    }

    double Ndu = D1c.Magnitude();

    if (myMaxDerivOrder != 0)
    {
      if (Ndu <= myTol)
      {
        const double DivisionFactor = 1.e-3;
        double       du;
        if ((myUsupremum >= RealLast()) || (myUinfium <= RealFirst()))
          du = 0.0;
        else
          du = myUsupremum - myUinfium;

        const double aDelta = std::max(du * DivisionFactor, MinStep);

        int       n = 1;
        TheVector V;
        bool      IsDeriveFound;

        do
        {
          V             = TheCurveTool::DN(*myC, myU, ++n);
          Ndu           = V.Magnitude();
          IsDeriveFound = (Ndu > myTol);
        } while (!IsDeriveFound && n < myMaxDerivOrder);

        if (IsDeriveFound)
        {
          double u;

          if (myU - myUinfium < aDelta)
            u = myU + aDelta;
          else
            u = myU - aDelta;

          ThePoint P1, P2;
          TheCurveTool::D0(*myC, std::min(myU, u), P1);
          TheCurveTool::D0(*myC, std::max(myU, u), P2);

          TheVector V1(P1, P2);
          double    aDirFactor = V.Dot(V1);

          if (aDirFactor < 0.0)
            D1c = -V;
          else
            D1c = V;
        }
        else
        {

          ThePoint Ptemp;
          ThePoint P1, P2, P3;
          bool     IsParameterGrown;

          if (myU - myUinfium < 2 * aDelta)
          {
            TheCurveTool::D0(*myC, myU, P1);
            TheCurveTool::D0(*myC, myU + aDelta, P2);
            TheCurveTool::D0(*myC, myU + 2 * aDelta, P3);
            IsParameterGrown = true;
          }
          else
          {
            TheCurveTool::D0(*myC, myU - 2 * aDelta, P1);
            TheCurveTool::D0(*myC, myU - aDelta, P2);
            TheCurveTool::D0(*myC, myU, P3);
            IsParameterGrown = false;
          }

          TheVector V1(Ptemp, P1), V2(Ptemp, P2), V3(Ptemp, P3);

          if (IsParameterGrown)
            D1c = -3 * V1 + 4 * V2 - V3;
          else
            D1c = V1 - 4 * V2 + 3 * V3;
        }
        Ndu = D1c.Magnitude();
      }
    }

    if (Ndu <= MinTol)
    {

      return false;
    }

    TheVector PPc(myP, myPc);
    theF = PPc.Dot(D1c) / Ndu;
    return true;
  }

  bool Derivative(const double theU, double& theDF) override
  {
    if (!myPinit || !myCinit)
    {
      throw Standard_TypeMismatch();
    }
    double F;
    return Values(theU, F, theDF);
  }

  bool Values(const double theU, double& theF, double& theDF) override
  {
    if (!myPinit || !myCinit)
    {
      throw Standard_TypeMismatch("No init");
    }

    ThePoint myPc_old = myPc, myP_old = myP;

    if (Value(theU, theF) == false)
    {
      myD1Init = false;
      return false;
    }

    myU  = theU;
    myPc = myPc_old;
    myP  = myP_old;

    TheVector D1c, D2c;
    TheCurveTool::D2(*myC, myU, myPc, D1c, D2c);

    double Ndu = D1c.Magnitude();
    if (Ndu <= myTol)
    {

      const double DivisionFactor = 0.01;
      double       du;
      if ((myUsupremum >= RealLast()) || (myUinfium <= RealFirst()))
        du = 0.0;
      else
        du = myUsupremum - myUinfium;

      const double aDelta = std::max(du * DivisionFactor, MinStep);

      double F1, F2, F3;

      if (myU - myUinfium < 2 * aDelta)
      {
        F1              = theF;
        const double U2 = myU + aDelta;
        const double U3 = myU + aDelta * 2.0;

        if (!((Value(U2, F2)) && (Value(U3, F3))))
        {
          myD1Init = false;
          return false;
        }

        theDF = (-3 * F1 + 4 * F2 - F3) / (2.0 * aDelta);
      }
      else
      {
        F3              = theF;
        const double U1 = myU - aDelta * 2.0;
        const double U2 = myU - aDelta;

        if (!((Value(U2, F2)) && (Value(U1, F1))))
        {
          myD1Init = false;
          return false;
        }

        theDF = (F1 - 4 * F2 + 3 * F3) / (2.0 * aDelta);
      }
      myU  = theU;
      myPc = myPc_old;
      myP  = myP_old;
    }
    else
    {
      TheVector PPc(myP, myPc);
      theDF = Ndu + (PPc.Dot(D2c) / Ndu) - theF * (D1c.Dot(D2c)) / (Ndu * Ndu);
    }

    myD1f = theDF;

    myD1Init = true;
    return true;
  }

  int GetStateNumber() override
  {
    if (!myPinit || !myCinit)
    {
      throw Standard_TypeMismatch();
    }
    mySqDist.Append(myPc.SquareDistance(myP));

    myD1Init = true;
    double FF, DD;
    Values(myU, FF, DD);

    int IntVal = 0;
    if (myD1f > 0.0)
    {
      IntVal = 1;
    }

    myIsMin.Append(IntVal);
    myPoint.Append(ThePOnC(myU, myPc));
    return 0;
  }

  int NbExt() const { return mySqDist.Length(); }

  double SquareDistance(const int theN) const
  {
    if (!myPinit || !myCinit)
    {
      throw Standard_TypeMismatch();
    }
    return mySqDist.Value(theN);
  }

  bool IsMin(const int theN) const
  {
    if (!myPinit || !myCinit)
    {
      throw Standard_TypeMismatch();
    }
    return (myIsMin.Value(theN) == 1);
  }

  const ThePOnC& Point(const int theN) const
  {
    if (!myPinit || !myCinit)
    {
      throw Standard_TypeMismatch();
    }
    return myPoint.Value(theN);
  }

  void SubIntervalInitialize(const double theUfirst, const double theUlast)
  {
    myUinfium   = theUfirst;
    myUsupremum = theUlast;
  }

  double SearchOfTolerance()
  {
    const int    NPoint = 10;
    const double aStep  = (myUsupremum - myUinfium) / static_cast<double>(NPoint);

    int    aNum = 0;
    double aMax = -Precision::Infinite();

    do
    {
      double u = myUinfium + aNum * aStep;
      if (u > myUsupremum)
        u = myUsupremum;

      ThePoint  Ptemp;
      TheVector VDer;
      TheCurveTool::D1(*myC, u, Ptemp, VDer);

      if (Precision::IsInfinite(VDer.X()) || Precision::IsInfinite(VDer.Y()))
      {
        continue;
      }

      double vm = VDer.Magnitude();
      if (vm > aMax)
        aMax = vm;
    } while (++aNum < NPoint + 1);

    return std::max(aMax * TolFactor, MinTol);
  }

private:
  static constexpr double TolFactor = 1.e-12;
  static constexpr double MinTol    = 1.e-20;
  static constexpr double MinStep   = 1.e-7;
  static constexpr int    MaxOrder  = 3;

  ThePoint                     myP;
  TheCurve*                    myC;
  double                       myU;
  ThePoint                     myPc;
  double                       myD1f;
  NCollection_Sequence<double> mySqDist;
  NCollection_Sequence<int>    myIsMin;
  TheSeqPOnC                   myPoint;
  bool                         myPinit;
  bool                         myCinit;
  bool                         myD1Init;
  double                       myTol;
  int                          myMaxDerivOrder;
  double                       myUinfium;
  double                       myUsupremum;
};
