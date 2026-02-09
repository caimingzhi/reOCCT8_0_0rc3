#pragma once

#include <gp.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Standard_NullValue.hpp>

#include <cmath>

namespace Geom_OffsetCurveUtils
{

  inline bool CalculateD0(gp_Pnt&       theValue,
                          const gp_Vec& theD1,
                          const gp_XYZ& theDirXYZ,
                          double        theOffset,
                          double        theTolerance = gp::Resolution())
  {
    gp_XYZ Ndir = (theD1.XYZ()).Crossed(theDirXYZ);
    double R    = Ndir.Modulus();
    if (R <= theTolerance)
    {
      return false;
    }

    Ndir.Multiply(theOffset / R);
    theValue.ChangeCoord().Add(Ndir);
    return true;
  }

  inline bool CalculateD1(gp_Pnt&       theValue,
                          gp_Vec&       theD1,
                          const gp_Vec& theD2,
                          const gp_XYZ& theDirXYZ,
                          double        theOffset,
                          double        theTolerance = gp::Resolution())
  {

    gp_XYZ Ndir  = (theD1.XYZ()).Crossed(theDirXYZ);
    gp_XYZ DNdir = (theD2.XYZ()).Crossed(theDirXYZ);
    double R2    = Ndir.SquareModulus();
    double R     = std::sqrt(R2);
    double R3    = R * R2;
    double Dr    = Ndir.Dot(DNdir);
    if (R3 <= theTolerance)
    {
      if (R2 <= theTolerance)
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

    theD1.Add(gp_Vec(DNdir));
    return true;
  }

  inline bool CalculateD2(gp_Pnt&       theValue,
                          gp_Vec&       theD1,
                          gp_Vec&       theD2,
                          const gp_Vec& theD3,
                          const gp_XYZ& theDirXYZ,
                          double        theOffset,
                          bool          theIsDirChange,
                          double        theTolerance = gp::Resolution())
  {

    gp_XYZ Ndir   = (theD1.XYZ()).Crossed(theDirXYZ);
    gp_XYZ DNdir  = (theD2.XYZ()).Crossed(theDirXYZ);
    gp_XYZ D2Ndir = (theD3.XYZ()).Crossed(theDirXYZ);
    double R2     = Ndir.SquareModulus();
    double R      = std::sqrt(R2);
    double R3     = R2 * R;
    double R4     = R2 * R2;
    double R5     = R3 * R2;
    double Dr     = Ndir.Dot(DNdir);
    double D2r    = Ndir.Dot(D2Ndir) + DNdir.Dot(DNdir);

    if (R5 <= theTolerance)
    {
      if (R4 <= theTolerance)
      {
        return false;
      }

      R4 = R2 * R2;
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

    theD1.Add(gp_Vec(DNdir));

    if (theIsDirChange)
    {
      theD2.Reverse();
    }
    theD2.Add(gp_Vec(D2Ndir));
    return true;
  }

  inline bool CalculateD3(gp_Pnt&       theValue,
                          gp_Vec&       theD1,
                          gp_Vec&       theD2,
                          gp_Vec&       theD3,
                          const gp_Vec& theD4,
                          const gp_XYZ& theDirXYZ,
                          double        theOffset,
                          bool          theIsDirChange,
                          double        theTolerance = gp::Resolution())
  {

    gp_XYZ       Ndir   = (theD1.XYZ()).Crossed(theDirXYZ);
    gp_XYZ       DNdir  = (theD2.XYZ()).Crossed(theDirXYZ);
    gp_XYZ       D2Ndir = (theD3.XYZ()).Crossed(theDirXYZ);
    gp_XYZ       D3Ndir = (theD4.XYZ()).Crossed(theDirXYZ);
    const double R2     = Ndir.SquareModulus();
    const double R      = std::sqrt(R2);
    const double R3     = R2 * R;
    double       R4     = R2 * R2;
    const double R5     = R3 * R2;
    const double R6     = R3 * R3;
    const double R7     = R5 * R2;
    const double Dr     = Ndir.Dot(DNdir);
    const double D2r    = Ndir.Dot(D2Ndir) + DNdir.Dot(DNdir);
    const double D3r    = Ndir.Dot(D3Ndir) + 3.0 * DNdir.Dot(D2Ndir);
    if (R7 <= theTolerance)
    {
      if (R6 <= theTolerance)
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

      D3Ndir.Divide(R);
      D3Ndir.Subtract(D2Ndir.Multiplied(3.0 * Dr / R3));
      D3Ndir.Subtract(DNdir.Multiplied((3.0 * ((D2r / R3) + (Dr * Dr) / R5))));
      D3Ndir.Add(
        Ndir.Multiplied(6.0 * Dr * Dr / R5 + 6.0 * Dr * D2r / R5 - 15.0 * Dr * Dr * Dr / R7 - D3r));
      D3Ndir.Multiply(theOffset);

      D2Ndir.Divide(R);
      D2Ndir.Subtract(DNdir.Multiplied(2.0 * Dr / R3));
      D2Ndir.Subtract(Ndir.Multiplied((3.0 * Dr * Dr / R5) - (D2r / R3)));
      D2Ndir.Multiply(theOffset);

      DNdir.Multiply(theOffset / R);
      DNdir.Subtract(Ndir.Multiplied(theOffset * Dr / R3));
    }

    Ndir.Multiply(theOffset / R);

    theValue.ChangeCoord().Add(Ndir);

    theD1.Add(gp_Vec(DNdir));

    theD2.Add(gp_Vec(D2Ndir));

    if (theIsDirChange)
    {
      theD3.Reverse();
    }
    theD3.Add(gp_Vec(D3Ndir));
    return true;
  }

  template <typename CurveType>
  bool AdjustDerivative(const CurveType& theCurve,
                        int              theMaxDerivative,
                        double           theU,
                        gp_Vec&          theD1,
                        gp_Vec&          theD2,
                        gp_Vec&          theD3,
                        gp_Vec&          theD4)
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

    int    anIndex = 1;
    gp_Vec V;

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

    gp_Pnt P1, P2;
    theCurve.D0(std::min(theU, u), P1);
    theCurve.D0(std::max(theU, u), P2);

    gp_Vec V1(P1, P2);
    isDirectionChange  = V.Dot(V1) < 0.0;
    const double aSign = isDirectionChange ? -1.0 : 1.0;

    theD1             = V * aSign;
    gp_Vec* aDeriv[3] = {&theD2, &theD3, &theD4};
    for (int i = 1; i < theMaxDerivative; i++)
    {
      *(aDeriv[i - 1]) = theCurve.DN(theU, anIndex + i) * aSign;
    }

    return isDirectionChange;
  }

  template <typename BasisCurveType>
  bool EvaluateD0(double                theU,
                  const BasisCurveType& theBasisCurve,
                  const gp_Dir&         theDir,
                  double                theOffset,
                  gp_Pnt&               theValue)
  {
    gp_Vec aD1;
    theBasisCurve->D1(theU, theValue, aD1);
    return CalculateD0(theValue, aD1, theDir.XYZ(), theOffset);
  }

  template <typename BasisCurveType>
  bool EvaluateD1(double                theU,
                  const BasisCurveType& theBasisCurve,
                  const gp_Dir&         theDir,
                  double                theOffset,
                  gp_Pnt&               theValue,
                  gp_Vec&               theD1)
  {
    gp_Vec aD2;
    theBasisCurve->D2(theU, theValue, theD1, aD2);
    return CalculateD1(theValue, theD1, aD2, theDir.XYZ(), theOffset);
  }

  template <typename BasisCurveType>
  bool EvaluateD2(double                theU,
                  const BasisCurveType& theBasisCurve,
                  const gp_Dir&         theDir,
                  double                theOffset,
                  gp_Pnt&               theValue,
                  gp_Vec&               theD1,
                  gp_Vec&               theD2)
  {
    gp_Vec aD3;
    theBasisCurve->D3(theU, theValue, theD1, theD2, aD3);

    bool isDirectionChange = false;
    if (theD1.SquareMagnitude() <= gp::Resolution())
    {
      gp_Vec aDummyD4;
      isDirectionChange = AdjustDerivative(*theBasisCurve, 3, theU, theD1, theD2, aD3, aDummyD4);
    }

    return CalculateD2(theValue, theD1, theD2, aD3, theDir.XYZ(), theOffset, isDirectionChange);
  }

  template <typename BasisCurveType>
  bool EvaluateD3(double                theU,
                  const BasisCurveType& theBasisCurve,
                  const gp_Dir&         theDir,
                  double                theOffset,
                  gp_Pnt&               theValue,
                  gp_Vec&               theD1,
                  gp_Vec&               theD2,
                  gp_Vec&               theD3)
  {
    theBasisCurve->D3(theU, theValue, theD1, theD2, theD3);
    gp_Vec aD4 = theBasisCurve->DN(theU, 4);

    bool isDirectionChange = false;
    if (theD1.SquareMagnitude() <= gp::Resolution())
    {
      isDirectionChange = AdjustDerivative(*theBasisCurve, 4, theU, theD1, theD2, theD3, aD4);
    }

    return CalculateD3(theValue,
                       theD1,
                       theD2,
                       theD3,
                       aD4,
                       theDir.XYZ(),
                       theOffset,
                       isDirectionChange);
  }

  template <typename BasisCurveType>
  bool EvaluateDN(double                theU,
                  const BasisCurveType& theBasisCurve,
                  const gp_Dir&         theDir,
                  double                theOffset,
                  int                   theN,
                  gp_Vec&               theDN)
  {
    gp_Pnt aPnt;
    gp_Vec aDummy;
    switch (theN)
    {
      case 1:
        return EvaluateD1(theU, theBasisCurve, theDir, theOffset, aPnt, theDN);
      case 2:
        return EvaluateD2(theU, theBasisCurve, theDir, theOffset, aPnt, aDummy, theDN);
      case 3:
        return EvaluateD3(theU, theBasisCurve, theDir, theOffset, aPnt, aDummy, aDummy, theDN);
      default:

        theDN = theBasisCurve->DN(theU, theN);
        return true;
    }
  }

} // namespace Geom_OffsetCurveUtils
