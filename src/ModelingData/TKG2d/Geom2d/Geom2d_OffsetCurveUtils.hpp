#pragma once

#include <gp.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_XY.hpp>

#include <cmath>

namespace Geom2d_OffsetCurveUtils
{

  inline bool CalculateD0(gp_Pnt2d& theValue, const gp_Vec2d& theD1, double theOffset)
  {
    if (theD1.SquareMagnitude() <= gp::Resolution())
    {
      return false;
    }

    gp_Dir2d aNormal(theD1.Y(), -theD1.X());
    theValue.ChangeCoord().Add(aNormal.XY() * theOffset);
    return true;
  }

  inline bool CalculateD1(gp_Pnt2d&       theValue,
                          gp_Vec2d&       theD1,
                          const gp_Vec2d& theD2,
                          double          theOffset)
  {

    gp_XY  Ndir(theD1.Y(), -theD1.X());
    gp_XY  DNdir(theD2.Y(), -theD2.X());
    double R2 = Ndir.SquareModulus();
    double R  = std::sqrt(R2);
    double R3 = R * R2;
    double Dr = Ndir.Dot(DNdir);
    if (R3 <= gp::Resolution())
    {
      if (R2 <= gp::Resolution())
      {
        return false;
      }

      DNdir.Multiply(R);
      DNdir.Subtract(Ndir.Multiplied(Dr / R));
      DNdir.Multiply(theOffset / R2);
    }
    else
    {

      DNdir.Multiply(theOffset / R);
      DNdir.Subtract(Ndir.Multiplied(theOffset * Dr / R3));
    }

    Ndir.Multiply(theOffset / R);

    theValue.ChangeCoord().Add(Ndir);

    theD1.Add(gp_Vec2d(DNdir));
    return true;
  }

  inline bool CalculateD2(gp_Pnt2d&       theValue,
                          gp_Vec2d&       theD1,
                          gp_Vec2d&       theD2,
                          const gp_Vec2d& theD3,
                          bool            theIsDirChange,
                          double          theOffset)
  {

    gp_XY  Ndir(theD1.Y(), -theD1.X());
    gp_XY  DNdir(theD2.Y(), -theD2.X());
    gp_XY  D2Ndir(theD3.Y(), -theD3.X());
    double R2  = Ndir.SquareModulus();
    double R   = std::sqrt(R2);
    double R3  = R2 * R;
    double R4  = R2 * R2;
    double R5  = R3 * R2;
    double Dr  = Ndir.Dot(DNdir);
    double D2r = Ndir.Dot(D2Ndir) + DNdir.Dot(DNdir);
    if (R5 <= gp::Resolution())
    {
      if (R4 <= gp::Resolution())
      {
        return false;
      }

      D2Ndir.Subtract(DNdir.Multiplied(2.0 * Dr / R2));
      D2Ndir.Add(Ndir.Multiplied(((3.0 * Dr * Dr) / R4) - (D2r / R2)));
      D2Ndir.Multiply(theOffset / R);

      DNdir.Multiply(R);
      DNdir.Subtract(Ndir.Multiplied(Dr / R));
      DNdir.Multiply(theOffset / R2);
    }
    else
    {

      D2Ndir.Multiply(theOffset / R);
      D2Ndir.Subtract(DNdir.Multiplied(2.0 * theOffset * Dr / R3));
      D2Ndir.Add(Ndir.Multiplied(theOffset * (((3.0 * Dr * Dr) / R5) - (D2r / R3))));

      DNdir.Multiply(theOffset / R);
      DNdir.Subtract(Ndir.Multiplied(theOffset * Dr / R3));
    }

    Ndir.Multiply(theOffset / R);

    theValue.ChangeCoord().Add(Ndir);

    theD1.Add(gp_Vec2d(DNdir));

    if (theIsDirChange)
    {
      theD2.Reverse();
    }
    theD2.Add(gp_Vec2d(D2Ndir));
    return true;
  }

  inline bool CalculateD3(gp_Pnt2d&       theValue,
                          gp_Vec2d&       theD1,
                          gp_Vec2d&       theD2,
                          gp_Vec2d&       theD3,
                          const gp_Vec2d& theD4,
                          bool            theIsDirChange,
                          double          theOffset)
  {

    gp_XY  Ndir(theD1.Y(), -theD1.X());
    gp_XY  DNdir(theD2.Y(), -theD2.X());
    gp_XY  D2Ndir(theD3.Y(), -theD3.X());
    gp_XY  D3Ndir(theD4.Y(), -theD4.X());
    double R2  = Ndir.SquareModulus();
    double R   = std::sqrt(R2);
    double R3  = R2 * R;
    double R4  = R2 * R2;
    double R5  = R3 * R2;
    double R6  = R3 * R3;
    double R7  = R5 * R2;
    double Dr  = Ndir.Dot(DNdir);
    double D2r = Ndir.Dot(D2Ndir) + DNdir.Dot(DNdir);
    double D3r = Ndir.Dot(D3Ndir) + 3.0 * DNdir.Dot(D2Ndir);

    if (R7 <= gp::Resolution())
    {
      if (R6 <= gp::Resolution())
      {
        return false;
      }

      D3Ndir.Subtract(D2Ndir.Multiplied(3.0 * Dr / R2));
      D3Ndir.Subtract(DNdir.Multiplied(3.0 * ((D2r / R2) + (Dr * Dr / R4))));
      D3Ndir.Add(
        Ndir.Multiplied(6.0 * Dr * Dr / R4 + 6.0 * Dr * D2r / R4 - 15.0 * Dr * Dr * Dr / R6 - D3r));
      D3Ndir.Multiply(theOffset / R);

      R4 = R2 * R2;
      D2Ndir.Subtract(DNdir.Multiplied(2.0 * Dr / R2));
      D2Ndir.Subtract(Ndir.Multiplied((3.0 * Dr * Dr / R4) - (D2r / R2)));
      D2Ndir.Multiply(theOffset / R);

      DNdir.Multiply(R);
      DNdir.Subtract(Ndir.Multiplied(Dr / R));
      DNdir.Multiply(theOffset / R2);
    }
    else
    {

      D3Ndir.Multiply(theOffset / R);
      D3Ndir.Subtract(D2Ndir.Multiplied(3.0 * theOffset * Dr / R3));
      D3Ndir.Subtract(DNdir.Multiplied(((3.0 * theOffset) * ((D2r / R3) + (Dr * Dr) / R5))));
      D3Ndir.Add(Ndir.Multiplied(
        (theOffset * (6.0 * Dr * Dr / R5 + 6.0 * Dr * D2r / R5 - 15.0 * Dr * Dr * Dr / R7 - D3r))));

      D2Ndir.Multiply(theOffset / R);
      D2Ndir.Subtract(DNdir.Multiplied(2.0 * theOffset * Dr / R3));
      D2Ndir.Subtract(Ndir.Multiplied(theOffset * (((3.0 * Dr * Dr) / R5) - (D2r / R3))));

      DNdir.Multiply(theOffset / R);
      DNdir.Subtract(Ndir.Multiplied(theOffset * Dr / R3));
    }

    Ndir.Multiply(theOffset / R);

    theValue.ChangeCoord().Add(Ndir);

    theD1.Add(gp_Vec2d(DNdir));

    theD2.Add(gp_Vec2d(D2Ndir));

    if (theIsDirChange)
    {
      theD3.Reverse();
    }
    theD3.Add(gp_Vec2d(D3Ndir));
    return true;
  }

  template <typename CurveType>
  bool AdjustDerivative(const CurveType& theCurve,
                        int              theMaxDerivative,
                        double           theU,
                        gp_Vec2d&        theD1,
                        gp_Vec2d&        theD2,
                        gp_Vec2d&        theD3,
                        gp_Vec2d&        theD4)
  {
    static const double aTol           = gp::Resolution();
    static const double aMinStep       = 1e-7;
    static const int    aMaxDerivOrder = 3;

    bool         isDirectionChange = false;
    const double anUinfium         = theCurve.FirstParameter();
    const double anUsupremum       = theCurve.LastParameter();

    static const double DivisionFactor = 1.e-3;
    double              du;
    if ((anUsupremum >= RealLast()) || (anUinfium <= RealFirst()))
    {
      du = 0.0;
    }
    else
    {
      du = anUsupremum - anUinfium;
    }

    const double aDelta = std::max(du * DivisionFactor, aMinStep);

    int      anIndex = 1;
    gp_Vec2d V;

    do
    {
      V = theCurve.DN(theU, ++anIndex);
    } while ((V.SquareMagnitude() <= aTol) && anIndex < aMaxDerivOrder);

    double u;

    if (theU - anUinfium < aDelta)
    {
      u = theU + aDelta;
    }
    else
    {
      u = theU - aDelta;
    }

    gp_Pnt2d P1, P2;
    theCurve.D0(std::min(theU, u), P1);
    theCurve.D0(std::max(theU, u), P2);

    gp_Vec2d V1(P1, P2);
    isDirectionChange  = V.Dot(V1) < 0.0;
    const double aSign = isDirectionChange ? -1.0 : 1.0;

    theD1               = V * aSign;
    gp_Vec2d* aDeriv[3] = {&theD2, &theD3, &theD4};
    for (int i = 1; i < theMaxDerivative; i++)
    {
      *(aDeriv[i - 1]) = theCurve.DN(theU, anIndex + i) * aSign;
    }

    return isDirectionChange;
  }

  template <typename BasisCurveType>
  bool EvaluateD0(double                theU,
                  const BasisCurveType& theBasisCurve,
                  double                theOffset,
                  gp_Pnt2d&             theValue)
  {
    gp_Vec2d aD1;
    theBasisCurve->D1(theU, theValue, aD1);
    return CalculateD0(theValue, aD1, theOffset);
  }

  template <typename BasisCurveType>
  bool EvaluateD1(double                theU,
                  const BasisCurveType& theBasisCurve,
                  double                theOffset,
                  gp_Pnt2d&             theValue,
                  gp_Vec2d&             theD1)
  {
    gp_Vec2d aD2;
    theBasisCurve->D2(theU, theValue, theD1, aD2);
    return CalculateD1(theValue, theD1, aD2, theOffset);
  }

  template <typename BasisCurveType>
  bool EvaluateD2(double                theU,
                  const BasisCurveType& theBasisCurve,
                  double                theOffset,
                  gp_Pnt2d&             theValue,
                  gp_Vec2d&             theD1,
                  gp_Vec2d&             theD2)
  {
    gp_Vec2d aD3;
    theBasisCurve->D3(theU, theValue, theD1, theD2, aD3);

    bool isDirectionChange = false;
    if (theD1.SquareMagnitude() <= gp::Resolution())
    {
      gp_Vec2d aDummyD4;
      isDirectionChange = AdjustDerivative(*theBasisCurve, 3, theU, theD1, theD2, aD3, aDummyD4);
    }

    return CalculateD2(theValue, theD1, theD2, aD3, isDirectionChange, theOffset);
  }

  template <typename BasisCurveType>
  bool EvaluateD3(double                theU,
                  const BasisCurveType& theBasisCurve,
                  double                theOffset,
                  gp_Pnt2d&             theValue,
                  gp_Vec2d&             theD1,
                  gp_Vec2d&             theD2,
                  gp_Vec2d&             theD3)
  {
    theBasisCurve->D3(theU, theValue, theD1, theD2, theD3);
    gp_Vec2d aD4 = theBasisCurve->DN(theU, 4);

    bool isDirectionChange = false;
    if (theD1.SquareMagnitude() <= gp::Resolution())
    {
      isDirectionChange = AdjustDerivative(*theBasisCurve, 4, theU, theD1, theD2, theD3, aD4);
    }

    return CalculateD3(theValue, theD1, theD2, theD3, aD4, isDirectionChange, theOffset);
  }

  template <typename BasisCurveType>
  bool EvaluateDN(double                theU,
                  const BasisCurveType& theBasisCurve,
                  double                theOffset,
                  int                   theN,
                  gp_Vec2d&             theDN)
  {
    gp_Pnt2d aPnt;
    gp_Vec2d aDummy;
    switch (theN)
    {
      case 1:
        return EvaluateD1(theU, theBasisCurve, theOffset, aPnt, theDN);
      case 2:
        return EvaluateD2(theU, theBasisCurve, theOffset, aPnt, aDummy, theDN);
      case 3:
        return EvaluateD3(theU, theBasisCurve, theOffset, aPnt, aDummy, aDummy, theDN);
      default:

        theDN = theBasisCurve->DN(theU, theN);
        return true;
    }
  }

} // namespace Geom2d_OffsetCurveUtils
