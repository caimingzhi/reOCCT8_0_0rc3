#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>

namespace MathPoly
{
  using namespace MathUtils;

  inline MathUtils::PolyResult Linear(double theA, double theB)
  {
    MathUtils::PolyResult aResult;

    if (MathUtils::IsZero(theA))
    {
      if (MathUtils::IsZero(theB))
      {
        aResult.Status = MathUtils::Status::InfiniteSolutions;
      }
      else
      {
        aResult.Status = MathUtils::Status::NoSolution;
      }
      return aResult;
    }

    aResult.Status   = MathUtils::Status::OK;
    aResult.NbRoots  = 1;
    aResult.Roots[0] = -theB / theA;
    return aResult;
  }

  inline MathUtils::PolyResult Quadratic(double theA, double theB, double theC)
  {
    MathUtils::PolyResult aResult;

    if (MathUtils::IsZero(theA))
    {
      return Linear(theB, theC);
    }

    const double aScale = std::max({std::abs(theA), std::abs(theB), std::abs(theC)});
    if (aScale < MathUtils::THE_ZERO_TOL)
    {
      aResult.Status = MathUtils::Status::InfiniteSolutions;
      return aResult;
    }

    const double aA = theA / aScale;
    const double aB = theB / aScale;
    const double aC = theC / aScale;

    const double aDisc = aB * aB - 4.0 * aA * aC;

    const double aDiscTol = MathUtils::THE_ZERO_TOL * (aB * aB + std::abs(4.0 * aA * aC));

    if (aDisc < -aDiscTol)
    {

      aResult.Status  = MathUtils::Status::OK;
      aResult.NbRoots = 0;
      return aResult;
    }

    if (std::abs(aDisc) <= aDiscTol)
    {

      aResult.Status   = MathUtils::Status::OK;
      aResult.NbRoots  = 1;
      aResult.Roots[0] = -aB / (2.0 * aA);
      return aResult;
    }

    const double aSqrtDisc = std::sqrt(aDisc);

    const double aQ = -0.5 * (aB + MathUtils::SignTransfer(aSqrtDisc, aB));

    aResult.Status   = MathUtils::Status::OK;
    aResult.NbRoots  = 2;
    aResult.Roots[0] = aQ / aA;
    aResult.Roots[1] = aC / aQ;

    if (aResult.Roots[0] > aResult.Roots[1])
    {
      std::swap(aResult.Roots[0], aResult.Roots[1]);
    }

    return aResult;
  }

} // namespace MathPoly
