#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Core.hpp>
#include <MathUtils_Poly.hpp>
#include <MathPoly_Quadratic.hpp>

#include <cmath>

namespace MathPoly
{
  using namespace MathUtils;

  inline MathUtils::PolyResult Cubic(double theA, double theB, double theC, double theD)
  {
    MathUtils::PolyResult aResult;

    if (MathUtils::IsZero(theA))
    {
      return Quadratic(theB, theC, theD);
    }

    const double aScale =
      std::max({std::abs(theA), std::abs(theB), std::abs(theC), std::abs(theD)});
    if (aScale < MathUtils::THE_ZERO_TOL)
    {
      aResult.Status = MathUtils::Status::InfiniteSolutions;
      return aResult;
    }

    const double aP = theB / theA;
    const double aQ = theC / theA;
    const double aR = theD / theA;

    const double aP3    = aP / 3.0;
    const double aP3_sq = aP3 * aP3;
    const double a      = aQ - 3.0 * aP3_sq;
    const double b      = aR - aP3 * aQ + 2.0 * aP3_sq * aP3;

    const double aHalfB  = b / 2.0;
    const double aThirdA = a / 3.0;
    const double aDisc   = aHalfB * aHalfB + aThirdA * aThirdA * aThirdA;

    const double aDiscTol =
      MathUtils::THE_ZERO_TOL * std::max(aHalfB * aHalfB, std::abs(aThirdA * aThirdA * aThirdA));

    const double aCoeffs[4] = {theD, theC, theB, theA};

    if (aDisc > aDiscTol)
    {

      const double aSqrtDisc = std::sqrt(aDisc);
      const double aU        = MathUtils::CubeRoot(-aHalfB + aSqrtDisc);
      const double aV        = MathUtils::CubeRoot(-aHalfB - aSqrtDisc);

      aResult.Status   = MathUtils::Status::OK;
      aResult.NbRoots  = 1;
      aResult.Roots[0] = aU + aV - aP3;

      aResult.Roots[0] = MathUtils::RefinePolyRoot(aCoeffs, 3, aResult.Roots[0]);
    }
    else if (aDisc < -aDiscTol)
    {

      const double aR_val        = std::sqrt(-aThirdA * aThirdA * aThirdA);
      const double aCosArg       = MathUtils::Clamp(-aHalfB / aR_val, -1.0, 1.0);
      const double aTheta        = std::acos(aCosArg);
      const double aTwoSqrtNegA3 = 2.0 * std::sqrt(-aThirdA);

      aResult.Status   = MathUtils::Status::OK;
      aResult.NbRoots  = 3;
      aResult.Roots[0] = aTwoSqrtNegA3 * std::cos(aTheta / 3.0) - aP3;
      aResult.Roots[1] = aTwoSqrtNegA3 * std::cos((aTheta + 2.0 * MathUtils::THE_PI) / 3.0) - aP3;
      aResult.Roots[2] = aTwoSqrtNegA3 * std::cos((aTheta + 4.0 * MathUtils::THE_PI) / 3.0) - aP3;

      for (int i = 0; i < 3; ++i)
      {
        aResult.Roots[i] = MathUtils::RefinePolyRoot(aCoeffs, 3, aResult.Roots[i]);
      }

      MathUtils::SortRoots(aResult.Roots.data(), 3);
    }
    else
    {

      const double aU = MathUtils::CubeRoot(-aHalfB);

      aResult.Status = MathUtils::Status::OK;

      if (MathUtils::IsZero(aU))
      {

        aResult.NbRoots  = 1;
        aResult.Roots[0] = -aP3;
      }
      else
      {

        aResult.NbRoots  = 2;
        aResult.Roots[0] = 2.0 * aU - aP3;
        aResult.Roots[1] = -aU - aP3;

        aResult.Roots[0] = MathUtils::RefinePolyRoot(aCoeffs, 3, aResult.Roots[0]);
        aResult.Roots[1] = MathUtils::RefinePolyRoot(aCoeffs, 3, aResult.Roots[1]);

        if (aResult.Roots[0] > aResult.Roots[1])
        {
          std::swap(aResult.Roots[0], aResult.Roots[1]);
        }
      }
    }

    return aResult;
  }

} // namespace MathPoly
