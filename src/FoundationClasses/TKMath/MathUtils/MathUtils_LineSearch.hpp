#pragma once

#include <math_Vector.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>

namespace MathUtils
{

  struct LineSearchResult
  {
    bool   IsValid = false;
    double Alpha   = 0.0;
    double FNew    = 0.0;
    int    NbEvals = 0;
  };

  template <typename Function>
  LineSearchResult ArmijoBacktrack(Function&          theFunc,
                                   const math_Vector& theX,
                                   const math_Vector& theDir,
                                   const math_Vector& theGrad,
                                   double             theFx,
                                   double             theAlphaInit = 1.0,
                                   double             theC1        = 1.0e-4,
                                   double             theRho       = 0.5,
                                   int                theMaxIter   = 50)
  {
    LineSearchResult aResult;
    aResult.Alpha   = theAlphaInit;
    aResult.NbEvals = 0;

    const int aLower = theX.Lower();
    const int aUpper = theX.Upper();

    double aDirDeriv = 0.0;
    for (int i = aLower; i <= aUpper; ++i)
    {
      aDirDeriv += theGrad(i) * theDir(i);
    }

    if (aDirDeriv >= 0.0)
    {

      aResult.IsValid = false;
      return aResult;
    }

    math_Vector aXNew(aLower, aUpper);

    for (int k = 0; k < theMaxIter; ++k)
    {

      for (int i = aLower; i <= aUpper; ++i)
      {
        aXNew(i) = theX(i) + aResult.Alpha * theDir(i);
      }

      double aFNew = 0.0;
      if (!theFunc.Value(aXNew, aFNew))
      {

        aResult.Alpha *= theRho;
        ++aResult.NbEvals;
        continue;
      }
      ++aResult.NbEvals;

      if (aFNew <= theFx + theC1 * aResult.Alpha * aDirDeriv)
      {
        aResult.IsValid = true;
        aResult.FNew    = aFNew;
        return aResult;
      }

      aResult.Alpha *= theRho;

      if (aResult.Alpha < THE_EPSILON)
      {
        break;
      }
    }

    aResult.IsValid = false;
    return aResult;
  }

  template <typename Function>
  LineSearchResult WolfeSearch(Function&          theFunc,
                               const math_Vector& theX,
                               const math_Vector& theDir,
                               const math_Vector& theGrad,
                               double             theFx,
                               double             theAlphaInit = 1.0,
                               double             theC1        = 1.0e-4,
                               double             theC2        = 0.9,
                               int                theMaxIter   = 20)
  {
    LineSearchResult aResult;
    aResult.NbEvals = 0;

    const int aLower = theX.Lower();
    const int aUpper = theX.Upper();

    double aPhi0Prime = 0.0;
    for (int i = aLower; i <= aUpper; ++i)
    {
      aPhi0Prime += theGrad(i) * theDir(i);
    }

    if (aPhi0Prime >= 0.0)
    {
      aResult.IsValid = false;
      return aResult;
    }

    math_Vector aXNew(aLower, aUpper);
    math_Vector aGradNew(aLower, aUpper);

    double aAlphaLo = 0.0;
    double aAlphaHi = theAlphaInit * 2.0;
    double aAlpha   = theAlphaInit;

    double aPhiLo = theFx;

    for (int k = 0; k < theMaxIter; ++k)
    {

      for (int i = aLower; i <= aUpper; ++i)
      {
        aXNew(i) = theX(i) + aAlpha * theDir(i);
      }

      double aPhi = 0.0;
      if (!theFunc.Value(aXNew, aPhi))
      {

        aAlphaHi = aAlpha;
        aAlpha   = 0.5 * (aAlphaLo + aAlphaHi);
        ++aResult.NbEvals;
        continue;
      }
      ++aResult.NbEvals;

      if (aPhi > theFx + theC1 * aAlpha * aPhi0Prime || (k > 0 && aPhi >= aPhiLo))
      {

        aAlphaHi = aAlpha;
        break;
      }

      if (!theFunc.Gradient(aXNew, aGradNew))
      {
        aResult.IsValid = false;
        return aResult;
      }

      double aPhiPrime = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aPhiPrime += aGradNew(i) * theDir(i);
      }

      if (std::abs(aPhiPrime) <= -theC2 * aPhi0Prime)
      {
        aResult.IsValid = true;
        aResult.Alpha   = aAlpha;
        aResult.FNew    = aPhi;
        return aResult;
      }

      if (aPhiPrime >= 0.0)
      {

        aAlphaHi = aAlphaLo;
        aAlphaLo = aAlpha;
        aPhiLo   = aPhi;
        break;
      }

      aAlphaLo = aAlpha;
      aPhiLo   = aPhi;
      aAlpha   = 0.5 * (aAlpha + aAlphaHi);
    }

    for (int k = 0; k < theMaxIter; ++k)
    {

      aAlpha = 0.5 * (aAlphaLo + aAlphaHi);

      for (int i = aLower; i <= aUpper; ++i)
      {
        aXNew(i) = theX(i) + aAlpha * theDir(i);
      }

      double aPhi = 0.0;
      if (!theFunc.Value(aXNew, aPhi))
      {
        aAlphaHi = aAlpha;
        ++aResult.NbEvals;
        continue;
      }
      ++aResult.NbEvals;

      if (aPhi > theFx + theC1 * aAlpha * aPhi0Prime || aPhi >= aPhiLo)
      {
        aAlphaHi = aAlpha;
      }
      else
      {
        if (!theFunc.Gradient(aXNew, aGradNew))
        {
          break;
        }

        double aPhiPrime = 0.0;
        for (int i = aLower; i <= aUpper; ++i)
        {
          aPhiPrime += aGradNew(i) * theDir(i);
        }

        if (std::abs(aPhiPrime) <= -theC2 * aPhi0Prime)
        {
          aResult.IsValid = true;
          aResult.Alpha   = aAlpha;
          aResult.FNew    = aPhi;
          return aResult;
        }

        if (aPhiPrime * (aAlphaHi - aAlphaLo) >= 0.0)
        {
          aAlphaHi = aAlphaLo;
        }

        aAlphaLo = aAlpha;
        aPhiLo   = aPhi;
      }

      if (std::abs(aAlphaHi - aAlphaLo) < THE_EPSILON)
      {
        break;
      }
    }

    aResult.IsValid = true;
    aResult.Alpha   = aAlpha;
    aResult.FNew    = aPhiLo;
    return aResult;
  }

  template <typename Function>
  LineSearchResult ExactLineSearch(Function&          theFunc,
                                   const math_Vector& theX,
                                   const math_Vector& theDir,
                                   double             theAlphaMax  = 10.0,
                                   double             theTolerance = 1.0e-6,
                                   int                theMaxIter   = 100)
  {
    LineSearchResult aResult;
    aResult.NbEvals = 0;

    const int aLower = theX.Lower();
    const int aUpper = theX.Upper();

    math_Vector aXNew(aLower, aUpper);

    auto aEvalPhi = [&](double theAlpha, double& thePhi) -> bool
    {
      for (int i = aLower; i <= aUpper; ++i)
      {
        aXNew(i) = theX(i) + theAlpha * theDir(i);
      }
      ++aResult.NbEvals;
      return theFunc.Value(aXNew, thePhi);
    };

    double aA = -theAlphaMax;
    double aB = theAlphaMax;
    double aX = 0.0;
    double aW = aX;
    double aV = aX;

    double aFx = 0.0;
    if (!aEvalPhi(aX, aFx))
    {
      aResult.IsValid = false;
      return aResult;
    }
    double aFw = aFx;
    double aFv = aFx;

    double aD = 0.0;
    double aE = 0.0;

    for (int anIter = 0; anIter < theMaxIter; ++anIter)
    {
      const double aXm   = 0.5 * (aA + aB);
      const double aTol1 = theTolerance * std::abs(aX) + THE_ZERO_TOL / 10.0;
      const double aTol2 = 2.0 * aTol1;

      if (std::abs(aX - aXm) <= (aTol2 - 0.5 * (aB - aA)))
      {
        aResult.IsValid = true;
        aResult.Alpha   = aX;
        aResult.FNew    = aFx;
        return aResult;
      }

      double aU            = 0.0;
      bool   aUseParabolic = false;

      if (std::abs(aE) > aTol1)
      {
        const double aR = (aX - aW) * (aFx - aFv);
        double       aQ = (aX - aV) * (aFx - aFw);
        double       aP = (aX - aV) * aQ - (aX - aW) * aR;
        aQ              = 2.0 * (aQ - aR);

        if (aQ > 0.0)
        {
          aP = -aP;
        }
        else
        {
          aQ = -aQ;
        }

        const double aETmp = aE;
        aE                 = aD;

        if (std::abs(aP) < std::abs(0.5 * aQ * aETmp) && aP > aQ * (aA - aX) && aP < aQ * (aB - aX))
        {
          aD = aP / aQ;
          aU = aX + aD;
          if ((aU - aA) < aTol2 || (aB - aU) < aTol2)
          {
            aD = SignTransfer(aTol1, aXm - aX);
          }
          aUseParabolic = true;
        }
      }

      if (!aUseParabolic)
      {
        aE = (aX < aXm) ? (aB - aX) : (aA - aX);
        aD = THE_GOLDEN_SECTION * aE;
      }

      if (std::abs(aD) >= aTol1)
      {
        aU = aX + aD;
      }
      else
      {
        aU = aX + SignTransfer(aTol1, aD);
      }

      double aFu = 0.0;
      if (!aEvalPhi(aU, aFu))
      {
        aResult.IsValid = false;
        aResult.Alpha   = aX;
        aResult.FNew    = aFx;
        return aResult;
      }

      if (aFu <= aFx)
      {
        if (aU < aX)
        {
          aB = aX;
        }
        else
        {
          aA = aX;
        }

        aV  = aW;
        aW  = aX;
        aX  = aU;
        aFv = aFw;
        aFw = aFx;
        aFx = aFu;
      }
      else
      {
        if (aU < aX)
        {
          aA = aU;
        }
        else
        {
          aB = aU;
        }

        if (aFu <= aFw || aW == aX)
        {
          aV  = aW;
          aW  = aU;
          aFv = aFw;
          aFw = aFu;
        }
        else if (aFu <= aFv || aV == aX || aV == aW)
        {
          aV  = aU;
          aFv = aFu;
        }
      }
    }

    aResult.IsValid = true;
    aResult.Alpha   = aX;
    aResult.FNew    = aFx;
    return aResult;
  }

  inline double QuadraticInterpolation(double thePhi0,
                                       double thePhi0Prime,
                                       double theAlpha1,
                                       double thePhi1)
  {

    const double aNum   = thePhi0Prime * theAlpha1 * theAlpha1;
    const double aDenom = 2.0 * (thePhi1 - thePhi0 - thePhi0Prime * theAlpha1);

    if (std::abs(aDenom) < THE_ZERO_TOL)
    {
      return 0.5 * theAlpha1;
    }

    double aAlphaNew = -aNum / aDenom;

    if (aAlphaNew < 0.1 * theAlpha1)
    {
      aAlphaNew = 0.1 * theAlpha1;
    }
    else if (aAlphaNew > 0.9 * theAlpha1)
    {
      aAlphaNew = 0.5 * theAlpha1;
    }

    return aAlphaNew;
  }

} // namespace MathUtils
