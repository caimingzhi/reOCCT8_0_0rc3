#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Core.hpp>
#include <MathUtils_Poly.hpp>
#include <MathPoly_Quadratic.hpp>
#include <MathPoly_Cubic.hpp>

#include <cmath>

namespace MathPoly
{
  using namespace MathUtils;

  inline MathUtils::PolyResult Quartic(double theA,
                                       double theB,
                                       double theC,
                                       double theD,
                                       double theE)
  {
    MathUtils::PolyResult aResult;

    if (MathUtils::IsZero(theA))
    {
      return Cubic(theB, theC, theD, theE);
    }

    const double aScale =
      std::max({std::abs(theA), std::abs(theB), std::abs(theC), std::abs(theD), std::abs(theE)});
    if (aScale < MathUtils::THE_ZERO_TOL)
    {
      aResult.Status = MathUtils::Status::InfiniteSolutions;
      return aResult;
    }

    const double a = theB / theA;
    const double b = theC / theA;
    const double c = theD / theA;
    const double d = theE / theA;

    const double aShift = a / 4.0;
    const double a2     = a * a;
    const double a3     = a2 * a;
    const double a4     = a2 * a2;

    const double p = b - 3.0 * a2 / 8.0;
    const double q = c - a * b / 2.0 + a3 / 8.0;
    const double r = d - a * c / 4.0 + a2 * b / 16.0 - 3.0 * a4 / 256.0;

    const double aCoeffs[5] = {theE, theD, theC, theB, theA};

    if (MathUtils::IsZero(q))
    {

      MathUtils::PolyResult aQuadResult = Quadratic(1.0, p, r);

      if (!aQuadResult.IsDone())
      {
        aResult.Status = aQuadResult.Status;
        return aResult;
      }

      aResult.Status  = MathUtils::Status::OK;
      aResult.NbRoots = 0;

      for (size_t i = 0; i < aQuadResult.NbRoots; ++i)
      {
        const double u = aQuadResult.Roots[i];
        if (u >= -MathUtils::THE_ZERO_TOL)
        {
          if (u <= MathUtils::THE_ZERO_TOL)
          {

            aResult.Roots[aResult.NbRoots++] = -aShift;
          }
          else
          {

            const double aSqrtU              = std::sqrt(u);
            aResult.Roots[aResult.NbRoots++] = aSqrtU - aShift;
            aResult.Roots[aResult.NbRoots++] = -aSqrtU - aShift;
          }
        }
      }

      for (size_t i = 0; i < aResult.NbRoots; ++i)
      {
        aResult.Roots[i] = MathUtils::RefinePolyRoot(aCoeffs, 4, aResult.Roots[i]);
      }
      MathUtils::SortRoots(aResult.Roots.data(), aResult.NbRoots);
      aResult.NbRoots = MathUtils::RemoveDuplicateRoots(aResult.Roots.data(), aResult.NbRoots);

      return aResult;
    }

    MathUtils::PolyResult aCubicResult = Cubic(1.0, 2.0 * p, p * p - 4.0 * r, -q * q);

    if (!aCubicResult.IsDone() || aCubicResult.NbRoots == 0)
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }

    double z = aCubicResult.Roots[aCubicResult.NbRoots - 1];

    if (z < -MathUtils::THE_ZERO_TOL)
    {

      for (size_t i = 0; i < aCubicResult.NbRoots; ++i)
      {
        if (aCubicResult.Roots[i] >= -MathUtils::THE_ZERO_TOL)
        {
          z = std::max(0.0, aCubicResult.Roots[i]);
          break;
        }
      }
    }
    z = std::max(0.0, z);

    const double s = std::sqrt(z);
    double       u, v;

    if (MathUtils::IsZero(s))
    {

      MathUtils::PolyResult aUVResult = Quadratic(1.0, p, r);
      if (!aUVResult.IsDone() || aUVResult.NbRoots < 2)
      {

        u = p / 2.0;
        v = p / 2.0;
      }
      else
      {
        u = aUVResult.Roots[0];
        v = aUVResult.Roots[1];
      }

      aResult.Status  = MathUtils::Status::OK;
      aResult.NbRoots = 0;

      if (u <= MathUtils::THE_ZERO_TOL)
      {
        const double aSqrt               = std::sqrt(std::max(0.0, -u));
        aResult.Roots[aResult.NbRoots++] = aSqrt - aShift;
        if (aSqrt > MathUtils::THE_ZERO_TOL)
        {
          aResult.Roots[aResult.NbRoots++] = -aSqrt - aShift;
        }
      }

      if (v <= MathUtils::THE_ZERO_TOL)
      {
        const double aSqrt               = std::sqrt(std::max(0.0, -v));
        aResult.Roots[aResult.NbRoots++] = aSqrt - aShift;
        if (aSqrt > MathUtils::THE_ZERO_TOL)
        {
          aResult.Roots[aResult.NbRoots++] = -aSqrt - aShift;
        }
      }
    }
    else
    {

      const double aHalfPPlusZ = (p + z) / 2.0;
      const double aQOver2S    = q / (2.0 * s);

      u = aHalfPPlusZ - aQOver2S;
      v = aHalfPPlusZ + aQOver2S;

      MathUtils::PolyResult aQuad1 = Quadratic(1.0, s, u);

      MathUtils::PolyResult aQuad2 = Quadratic(1.0, -s, v);

      aResult.Status  = MathUtils::Status::OK;
      aResult.NbRoots = 0;

      if (aQuad1.IsDone())
      {
        for (size_t i = 0; i < aQuad1.NbRoots; ++i)
        {
          aResult.Roots[aResult.NbRoots++] = aQuad1.Roots[i] - aShift;
        }
      }

      if (aQuad2.IsDone())
      {
        for (size_t i = 0; i < aQuad2.NbRoots; ++i)
        {
          aResult.Roots[aResult.NbRoots++] = aQuad2.Roots[i] - aShift;
        }
      }
    }

    for (size_t i = 0; i < aResult.NbRoots; ++i)
    {
      aResult.Roots[i] = MathUtils::RefinePolyRoot(aCoeffs, 4, aResult.Roots[i]);
    }

    MathUtils::SortRoots(aResult.Roots.data(), aResult.NbRoots);
    aResult.NbRoots = MathUtils::RemoveDuplicateRoots(aResult.Roots.data(), aResult.NbRoots);

    return aResult;
  }

} // namespace MathPoly
