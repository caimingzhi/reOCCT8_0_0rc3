#pragma once


#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
// Copyright (c) 2025 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


#include <MathUtils_Core.hpp>

#include <cmath>
#include <utility>

//! Modern math solver utilities.
namespace MathUtils
{

//! Result of root bracketing operation.
struct BracketResult
{
  bool   IsValid = false; //!< True if valid bracket found
  double A       = 0.0;   //!< Lower bound
  double B       = 0.0;   //!< Upper bound
  double Fa      = 0.0;   //!< Function value at A
  double Fb      = 0.0;   //!< Function value at B
};

//! Bracket a root by expanding interval until sign change is found.
//! Starting from [theA, theB], expands outward using golden ratio.
//! @tparam Function type with Value(double theX, double& theF) method
//! @param theFunc function to bracket
//! @param theA initial lower bound
//! @param theB initial upper bound
//! @param theMaxIter maximum expansion iterations
//! @return bracketing result
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
      // Ensure A < B
      if (aResult.A > aResult.B)
      {
        std::swap(aResult.A, aResult.B);
        std::swap(aResult.Fa, aResult.Fb);
      }
      return aResult;
    }

    // Expand the interval using golden ratio
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

//! Result of minimum bracketing operation.
struct MinBracketResult
{
  bool   IsValid = false; //!< True if valid bracket found (Fb < Fa and Fb < Fc)
  double A       = 0.0;   //!< Left bound
  double B       = 0.0;   //!< Middle point (minimum location estimate)
  double C       = 0.0;   //!< Right bound
  double Fa      = 0.0;   //!< Function value at A
  double Fb      = 0.0;   //!< Function value at B
  double Fc      = 0.0;   //!< Function value at C
};

//! Bracket a minimum by finding three points a < b < c with f(b) < f(a) and f(b) < f(c).
//! Uses golden section expansion with parabolic interpolation.
//! @tparam Function type with Value(double theX, double& theF) method
//! @param theFunc function to bracket
//! @param theA initial point A
//! @param theB initial point B (should be to the right of A in descent direction)
//! @param theMaxIter maximum iterations
//! @return bracketing result
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

  // Ensure we go downhill from A to B
  if (aResult.Fb > aResult.Fa)
  {
    std::swap(aResult.A, aResult.B);
    std::swap(aResult.Fa, aResult.Fb);
  }

  // Initial guess for C using golden ratio
  aResult.C = aResult.B + THE_GOLDEN_RATIO * (aResult.B - aResult.A);
  if (!theFunc.Value(aResult.C, aResult.Fc))
  {
    return aResult;
  }

  // Keep expanding until we bracket a minimum
  for (int anIter = 0; anIter < theMaxIter && aResult.Fb >= aResult.Fc; ++anIter)
  {
    // Parabolic extrapolation
    const double aR     = (aResult.B - aResult.A) * (aResult.Fb - aResult.Fc);
    const double aQ     = (aResult.B - aResult.C) * (aResult.Fb - aResult.Fa);
    const double aDenom = 2.0 * SignTransfer(std::max(std::abs(aQ - aR), THE_ZERO_TOL), aQ - aR);

    double aU = aResult.B - ((aResult.B - aResult.C) * aQ - (aResult.B - aResult.A) * aR) / aDenom;

    const double aULim = aResult.B + 100.0 * (aResult.C - aResult.B);
    double       aFu   = 0.0;

    if ((aResult.B - aU) * (aU - aResult.C) > 0.0)
    {
      // U is between B and C
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

      // Parabolic step didn't help, use golden section
      aU = aResult.C + THE_GOLDEN_RATIO * (aResult.C - aResult.B);
      if (!theFunc.Value(aU, aFu))
      {
        return aResult;
      }
    }
    else if ((aResult.C - aU) * (aU - aULim) > 0.0)
    {
      // U is between C and limit
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
      // U is beyond limit
      aU = aULim;
      if (!theFunc.Value(aU, aFu))
      {
        return aResult;
      }
    }
    else
    {
      // Default golden section step
      aU = aResult.C + THE_GOLDEN_RATIO * (aResult.C - aResult.B);
      if (!theFunc.Value(aU, aFu))
      {
        return aResult;
      }
    }

    // Shift points
    aResult.A  = aResult.B;
    aResult.B  = aResult.C;
    aResult.C  = aU;
    aResult.Fa = aResult.Fb;
    aResult.Fb = aResult.Fc;
    aResult.Fc = aFu;
  }

  aResult.IsValid = (aResult.Fb < aResult.Fa && aResult.Fb < aResult.Fc);

  // Ensure A < B < C ordering
  if (aResult.IsValid && aResult.A > aResult.C)
  {
    std::swap(aResult.A, aResult.C);
    std::swap(aResult.Fa, aResult.Fc);
  }

  return aResult;
}

} // namespace MathUtils



#include <cmath>

//! Optimization algorithms for scalar and vector functions.
namespace MathOpt
{
using namespace MathUtils;

//! Brent's method for 1D minimization.
//! Combines golden section search with parabolic interpolation.
//! Guaranteed to converge for unimodal functions within the given interval.
//!
//! Algorithm:
//! 1. Maintain bracket [a, b] with interior point x where f(x) < f(a), f(x) < f(b)
//! 2. Try parabolic interpolation using three points
//! 3. If parabolic step is rejected, use golden section step
//! 4. Update bracket and repeat until convergence
//!
//! @tparam Function type with Value(double theX, double& theF) method
//! @param theFunc function to minimize
//! @param theLower lower bound of search interval
//! @param theUpper upper bound of search interval
//! @param theConfig solver configuration
//! @return result containing minimum location and value
template <typename Function>
ScalarResult Brent(Function&     theFunc,
                   double        theLower,
                   double        theUpper,
                   const Config& theConfig = Config())
{
  ScalarResult aResult;

  double aA = theLower;
  double aB = theUpper;

  // Initial point using golden section
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

  double aD = 0.0; // Current step
  double aE = 0.0; // Previous step

  for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
  {
    const double aXm   = 0.5 * (aA + aB);
    const double aTol1 = theConfig.XTolerance * std::abs(aX) + MathUtils::THE_ZERO_TOL / 10.0;
    const double aTol2 = 2.0 * aTol1;

    aResult.NbIterations = anIter + 1;

    // Check convergence
    if (std::abs(aX - aXm) <= (aTol2 - 0.5 * (aB - aA)))
    {
      aResult.Status = Status::OK;
      aResult.Root   = aX;
      aResult.Value  = aFx;
      return aResult;
    }

    double aU            = 0.0;
    bool   aUseParabolic = false;

    // Try parabolic interpolation if step is large enough
    if (std::abs(aE) > aTol1)
    {
      // Parabolic fit through x, w, v
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

      // Check if parabolic step is acceptable
      if (std::abs(aP) < std::abs(0.5 * aQ * aETmp) && aP > aQ * (aA - aX) && aP < aQ * (aB - aX))
      {
        aD = aP / aQ;
        aU = aX + aD;

        // Don't evaluate too close to bounds
        if ((aU - aA) < aTol2 || (aB - aU) < aTol2)
        {
          aD = MathUtils::SignTransfer(aTol1, aXm - aX);
        }
        aUseParabolic = true;
      }
    }

    if (!aUseParabolic)
    {
      // Golden section step
      aE = (aX < aXm) ? (aB - aX) : (aA - aX);
      aD = MathUtils::THE_GOLDEN_SECTION * aE;
    }

    // Ensure step is at least aTol1
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

    // Update bracket and best points
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

  // Maximum iterations reached
  aResult.Status = Status::MaxIterations;
  aResult.Root   = aX;
  aResult.Value  = aFx;
  return aResult;
}

//! Golden section search for 1D minimization.
//! Simpler than Brent but with guaranteed linear convergence.
//! Does not attempt parabolic interpolation.
//!
//! @tparam Function type with Value(double theX, double& theF) method
//! @param theFunc function to minimize
//! @param theLower lower bound of search interval
//! @param theUpper upper bound of search interval
//! @param theConfig solver configuration
//! @return result containing minimum location and value
template <typename Function>
ScalarResult Golden(Function&     theFunc,
                    double        theLower,
                    double        theUpper,
                    const Config& theConfig = Config())
{
  ScalarResult aResult;

  constexpr double aR = 0.618033988749895; // (sqrt(5) - 1) / 2
  constexpr double aC = 1.0 - aR;

  double aA = theLower;
  double aB = theUpper;

  // Initialize interior points
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

    // Check convergence
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
      // Minimum is in [a, x2]
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
      // Minimum is in [x1, b]
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

  // Maximum iterations reached
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

//! Brent's method with automatic bracket search.
//! First attempts to bracket a minimum, then applies Brent's method.
//!
//! @tparam Function type with Value(double theX, double& theF) method
//! @param theFunc function to minimize
//! @param theGuess initial guess
//! @param theStep initial step size for bracket search
//! @param theConfig solver configuration
//! @return result containing minimum location and value
template <typename Function>
ScalarResult BrentWithBracket(Function&     theFunc,
                              double        theGuess,
                              double        theStep   = 1.0,
                              const Config& theConfig = Config())
{
  ScalarResult aResult;

  // Try to bracket minimum
  MathUtils::MinBracketResult aBracket =
    MathUtils::BracketMinimum(theFunc, theGuess, theGuess + theStep);

  if (!aBracket.IsValid)
  {
    aResult.Status = Status::InvalidInput;
    return aResult;
  }

  // Apply Brent's method on the bracket
  return Brent(theFunc, aBracket.A, aBracket.C, theConfig);
}

} // namespace MathOpt

