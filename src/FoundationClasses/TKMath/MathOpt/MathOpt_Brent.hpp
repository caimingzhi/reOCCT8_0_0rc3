#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>

#include <MathUtils_Core.hpp>

#include <cmath>
#include <utility>

namespace MathUtils
{

  struct BracketResult
  {
    bool   IsValid = false;
    double A       = 0.0;
    double B       = 0.0;
    double Fa      = 0.0;
    double Fb      = 0.0;
  };

  template <typename Function>
  BracketResult BracketRoot(Function& theFunc, double theA, double theB, int theMaxIter = 50)
  {
    BracketResult aResult;
    aResult.A = theA;
    aResult.B = theB;

    if (!theFunc.Value(aResult.A, aResult.Fa))
    {
      return aResult;
    }
    if (!theFunc.Value(aResult.B, aResult.Fb))
    {
      return aResult;
    }

    for (int i = 0; i < theMaxIter; ++i)
    {
      if (aResult.Fa * aResult.Fb < 0.0)
      {
        aResult.IsValid = true;

        if (aResult.A > aResult.B)
        {
          std::swap(aResult.A, aResult.B);
          std::swap(aResult.Fa, aResult.Fb);
        }
        return aResult;
      }

      if (std::abs(aResult.Fa) < std::abs(aResult.Fb))
      {
        aResult.A += THE_GOLDEN_RATIO * (aResult.A - aResult.B);
        if (!theFunc.Value(aResult.A, aResult.Fa))
        {
          return aResult;
        }
      }
      else
      {
        aResult.B += THE_GOLDEN_RATIO * (aResult.B - aResult.A);
        if (!theFunc.Value(aResult.B, aResult.Fb))
        {
          return aResult;
        }
      }
    }

    return aResult;
  }

  struct MinBracketResult
  {
    bool   IsValid = false;
    double A       = 0.0;
    double B       = 0.0;
    double C       = 0.0;
    double Fa      = 0.0;
    double Fb      = 0.0;
    double Fc      = 0.0;
  };

  template <typename Function>
  MinBracketResult BracketMinimum(Function& theFunc, double theA, double theB, int theMaxIter = 50)
  {
    MinBracketResult aResult;
    aResult.A = theA;
    aResult.B = theB;

    if (!theFunc.Value(aResult.A, aResult.Fa))
    {
      return aResult;
    }
    if (!theFunc.Value(aResult.B, aResult.Fb))
    {
      return aResult;
    }

    if (aResult.Fb > aResult.Fa)
    {
      std::swap(aResult.A, aResult.B);
      std::swap(aResult.Fa, aResult.Fb);
    }

    aResult.C = aResult.B + THE_GOLDEN_RATIO * (aResult.B - aResult.A);
    if (!theFunc.Value(aResult.C, aResult.Fc))
    {
      return aResult;
    }

    for (int anIter = 0; anIter < theMaxIter && aResult.Fb >= aResult.Fc; ++anIter)
    {

      const double aR     = (aResult.B - aResult.A) * (aResult.Fb - aResult.Fc);
      const double aQ     = (aResult.B - aResult.C) * (aResult.Fb - aResult.Fa);
      const double aDenom = 2.0 * SignTransfer(std::max(std::abs(aQ - aR), THE_ZERO_TOL), aQ - aR);

      double aU =
        aResult.B - ((aResult.B - aResult.C) * aQ - (aResult.B - aResult.A) * aR) / aDenom;

      const double aULim = aResult.B + 100.0 * (aResult.C - aResult.B);
      double       aFu   = 0.0;

      if ((aResult.B - aU) * (aU - aResult.C) > 0.0)
      {

        if (!theFunc.Value(aU, aFu))
        {
          return aResult;
        }

        if (aFu < aResult.Fc)
        {
          aResult.A       = aResult.B;
          aResult.B       = aU;
          aResult.Fa      = aResult.Fb;
          aResult.Fb      = aFu;
          aResult.IsValid = true;
          return aResult;
        }
        else if (aFu > aResult.Fb)
        {
          aResult.C       = aU;
          aResult.Fc      = aFu;
          aResult.IsValid = true;
          return aResult;
        }

        aU = aResult.C + THE_GOLDEN_RATIO * (aResult.C - aResult.B);
        if (!theFunc.Value(aU, aFu))
        {
          return aResult;
        }
      }
      else if ((aResult.C - aU) * (aU - aULim) > 0.0)
      {

        if (!theFunc.Value(aU, aFu))
        {
          return aResult;
        }

        if (aFu < aResult.Fc)
        {
          aResult.B  = aResult.C;
          aResult.C  = aU;
          aU         = aResult.C + THE_GOLDEN_RATIO * (aResult.C - aResult.B);
          aResult.Fb = aResult.Fc;
          aResult.Fc = aFu;
          if (!theFunc.Value(aU, aFu))
          {
            return aResult;
          }
        }
      }
      else if ((aU - aULim) * (aULim - aResult.C) >= 0.0)
      {

        aU = aULim;
        if (!theFunc.Value(aU, aFu))
        {
          return aResult;
        }
      }
      else
      {

        aU = aResult.C + THE_GOLDEN_RATIO * (aResult.C - aResult.B);
        if (!theFunc.Value(aU, aFu))
        {
          return aResult;
        }
      }

      aResult.A  = aResult.B;
      aResult.B  = aResult.C;
      aResult.C  = aU;
      aResult.Fa = aResult.Fb;
      aResult.Fb = aResult.Fc;
      aResult.Fc = aFu;
    }

    aResult.IsValid = (aResult.Fb < aResult.Fa && aResult.Fb < aResult.Fc);

    if (aResult.IsValid && aResult.A > aResult.C)
    {
      std::swap(aResult.A, aResult.C);
      std::swap(aResult.Fa, aResult.Fc);
    }

    return aResult;
  }

} // namespace MathUtils

#include <cmath>

namespace MathOpt
{
  using namespace MathUtils;

  template <typename Function>
  ScalarResult Brent(Function&     theFunc,
                     double        theLower,
                     double        theUpper,
                     const Config& theConfig = Config())
  {
    ScalarResult aResult;

    double aA = theLower;
    double aB = theUpper;

    double aX = aA + MathUtils::THE_GOLDEN_SECTION * (aB - aA);
    double aW = aX;
    double aV = aX;

    double aFx = 0.0;
    if (!theFunc.Value(aX, aFx))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }
    double aFw = aFx;
    double aFv = aFx;

    double aD = 0.0;
    double aE = 0.0;

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      const double aXm   = 0.5 * (aA + aB);
      const double aTol1 = theConfig.XTolerance * std::abs(aX) + MathUtils::THE_ZERO_TOL / 10.0;
      const double aTol2 = 2.0 * aTol1;

      aResult.NbIterations = anIter + 1;

      if (std::abs(aX - aXm) <= (aTol2 - 0.5 * (aB - aA)))
      {
        aResult.Status = Status::OK;
        aResult.Root   = aX;
        aResult.Value  = aFx;
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
            aD = MathUtils::SignTransfer(aTol1, aXm - aX);
          }
          aUseParabolic = true;
        }
      }

      if (!aUseParabolic)
      {

        aE = (aX < aXm) ? (aB - aX) : (aA - aX);
        aD = MathUtils::THE_GOLDEN_SECTION * aE;
      }

      if (std::abs(aD) >= aTol1)
      {
        aU = aX + aD;
      }
      else
      {
        aU = aX + MathUtils::SignTransfer(aTol1, aD);
      }

      double aFu = 0.0;
      if (!theFunc.Value(aU, aFu))
      {
        aResult.Status = Status::NumericalError;
        aResult.Root   = aX;
        aResult.Value  = aFx;
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

    aResult.Status = Status::MaxIterations;
    aResult.Root   = aX;
    aResult.Value  = aFx;
    return aResult;
  }

  template <typename Function>
  ScalarResult Golden(Function&     theFunc,
                      double        theLower,
                      double        theUpper,
                      const Config& theConfig = Config())
  {
    ScalarResult aResult;

    constexpr double aR = 0.618033988749895;
    constexpr double aC = 1.0 - aR;

    double aA = theLower;
    double aB = theUpper;

    double aX1 = aA + aC * (aB - aA);
    double aX2 = aA + aR * (aB - aA);

    double aF1 = 0.0;
    double aF2 = 0.0;

    if (!theFunc.Value(aX1, aF1))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }
    if (!theFunc.Value(aX2, aF2))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      if ((aB - aA) < theConfig.XTolerance * (std::abs(aX1) + std::abs(aX2)))
      {
        aResult.Status = Status::OK;
        if (aF1 < aF2)
        {
          aResult.Root  = aX1;
          aResult.Value = aF1;
        }
        else
        {
          aResult.Root  = aX2;
          aResult.Value = aF2;
        }
        return aResult;
      }

      if (aF1 < aF2)
      {

        aB  = aX2;
        aX2 = aX1;
        aF2 = aF1;
        aX1 = aA + aC * (aB - aA);
        if (!theFunc.Value(aX1, aF1))
        {
          aResult.Status = Status::NumericalError;
          aResult.Root   = aX2;
          aResult.Value  = aF2;
          return aResult;
        }
      }
      else
      {

        aA  = aX1;
        aX1 = aX2;
        aF1 = aF2;
        aX2 = aA + aR * (aB - aA);
        if (!theFunc.Value(aX2, aF2))
        {
          aResult.Status = Status::NumericalError;
          aResult.Root   = aX1;
          aResult.Value  = aF1;
          return aResult;
        }
      }
    }

    aResult.Status = Status::MaxIterations;
    if (aF1 < aF2)
    {
      aResult.Root  = aX1;
      aResult.Value = aF1;
    }
    else
    {
      aResult.Root  = aX2;
      aResult.Value = aF2;
    }
    return aResult;
  }

  template <typename Function>
  ScalarResult BrentWithBracket(Function&     theFunc,
                                double        theGuess,
                                double        theStep   = 1.0,
                                const Config& theConfig = Config())
  {
    ScalarResult aResult;

    MathUtils::MinBracketResult aBracket =
      MathUtils::BracketMinimum(theFunc, theGuess, theGuess + theStep);

    if (!aBracket.IsValid)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    return Brent(theFunc, aBracket.A, aBracket.C, theConfig);
  }

} // namespace MathOpt
