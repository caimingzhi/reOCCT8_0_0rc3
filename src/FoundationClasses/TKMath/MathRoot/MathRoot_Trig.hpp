#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <MathPoly_Quadratic.hpp>
#include <MathPoly_Quartic.hpp>

#include <cmath>
#include <algorithm>

namespace MathRoot
{
  using namespace MathUtils;

  struct TrigResult
  {
    MathUtils::Status     Status        = MathUtils::Status::NotConverged;
    std::array<double, 4> Roots         = {0.0, 0.0, 0.0, 0.0};
    int                   NbRoots       = 0;
    bool                  InfiniteRoots = false;

    bool IsDone() const { return Status == MathUtils::Status::OK; }

    explicit operator bool() const { return IsDone(); }
  };

  inline TrigResult Trigonometric(double theA,
                                  double theB,
                                  double theC,
                                  double theD,
                                  double theE,
                                  double theInfBound = 0.0,
                                  double theSupBound = THE_2PI,
                                  double theEps      = 1.5e-12)
  {
    TrigResult aResult;
    aResult.Status = MathUtils::Status::OK;

    double aMyBorneInf, aDelta, aMod;
    if (theInfBound <= std::numeric_limits<double>::lowest() / 2.0
        && theSupBound >= std::numeric_limits<double>::max() / 2.0)
    {
      aMyBorneInf = 0.0;
      aDelta      = THE_2PI;
      aMod        = 0.0;
    }
    else if (theSupBound >= std::numeric_limits<double>::max() / 2.0)
    {
      aMyBorneInf = theInfBound;
      aDelta      = THE_2PI;
      aMod        = aMyBorneInf / THE_2PI;
    }
    else if (theInfBound <= std::numeric_limits<double>::lowest() / 2.0)
    {
      aMyBorneInf = theSupBound - THE_2PI;
      aDelta      = THE_2PI;
      aMod        = aMyBorneInf / THE_2PI;
    }
    else
    {
      aMyBorneInf = theInfBound;
      aDelta      = theSupBound - theInfBound;
      aMod        = theInfBound / THE_2PI;
      if (aDelta > THE_2PI)
      {
        aDelta = THE_2PI;
      }
    }

    std::array<double, 4> aZer       = {0.0, 0.0, 0.0, 0.0};
    size_t                aNZer      = 0;
    const double          aDelta_Eps = std::numeric_limits<double>::epsilon() * std::abs(aDelta);

    if (std::abs(theA) <= theEps && std::abs(theB) <= theEps)
    {
      if (std::abs(theC) <= theEps)
      {
        if (std::abs(theD) <= theEps)
        {
          if (std::abs(theE) <= theEps)
          {
            aResult.InfiniteRoots = true;
            return aResult;
          }
          else
          {
            aResult.NbRoots = 0;
            return aResult;
          }
        }
        else
        {

          double aVal = -theE / theD;
          if (std::abs(aVal) > 1.0)
          {
            aResult.NbRoots = 0;
            return aResult;
          }

          aZer[0] = std::asin(aVal);
          aZer[1] = THE_PI - aZer[0];
          aNZer   = 2;

          for (size_t i = 0; i < aNZer; ++i)
          {
            if (aZer[i] <= -theEps)
            {
              aZer[i] = THE_2PI - std::abs(aZer[i]);
            }
            aZer[i] += std::trunc(aMod) * THE_2PI;
            double aX = aZer[i] - aMyBorneInf;
            if (aX >= -aDelta_Eps && aX <= aDelta + aDelta_Eps)
            {
              aResult.Roots[aResult.NbRoots++] = aZer[i];
            }
          }
          return aResult;
        }
      }
      else if (std::abs(theD) <= theEps)
      {

        double aVal = -theE / theC;
        if (std::abs(aVal) > 1.0)
        {
          aResult.NbRoots = 0;
          return aResult;
        }

        double aPrincipal = std::acos(aVal);
        aZer[0]           = aPrincipal;
        aZer[1]           = -aPrincipal;
        aNZer             = 2;

        for (size_t i = 0; i < aNZer; ++i)
        {
          double aAngle = aZer[i];

          double aK = std::floor((theInfBound - aAngle) / THE_2PI);
          aAngle += (aK + 1) * THE_2PI;

          for (int aPeriod = 0; aPeriod < 2; ++aPeriod)
          {
            double aTestAngle = aAngle + aPeriod * THE_2PI;
            if (aTestAngle >= theInfBound - aDelta_Eps && aTestAngle <= theSupBound + aDelta_Eps)
            {

              bool aDup = false;
              for (int k = 0; k < aResult.NbRoots; ++k)
              {
                if (std::abs(aTestAngle - aResult.Roots[k]) < theEps)
                {
                  aDup = true;
                  break;
                }
              }
              if (!aDup && aResult.NbRoots < 4)
              {
                aResult.Roots[aResult.NbRoots++] = aTestAngle;
              }
            }
          }
        }
        return aResult;
      }
      else
      {

        double aAA = theE - theC;
        double aBB = 2.0 * theD;
        double aCC = theE + theC;

        MathPoly::PolyResult aPoly = MathPoly::Quadratic(aAA, aBB, aCC);
        if (!aPoly.IsDone())
        {
          aResult.Status = aPoly.Status;
          return aResult;
        }
        if (aPoly.Status == MathUtils::Status::InfiniteSolutions)
        {
          aResult.InfiniteRoots = true;
          return aResult;
        }

        aNZer = aPoly.NbRoots;
        for (size_t i = 0; i < aNZer; ++i)
        {
          aZer[i] = aPoly.Roots[i];
        }
      }
    }
    else
    {

      if (std::abs(theA) <= theEps && std::abs(theE) <= theEps)
      {
        if (std::abs(theC) <= theEps)
        {

          aZer[0] = 0.0;
          aZer[1] = THE_PI;
          aNZer   = 2;

          double aVal = -theD / (theB * 2.0);
          if (std::abs(aVal) <= 1.0 + 1.0e-10)
          {
            if (aVal >= 1.0)
            {
              aZer[2] = 0.0;
              aZer[3] = 0.0;
            }
            else if (aVal <= -1.0)
            {
              aZer[2] = THE_PI;
              aZer[3] = THE_PI;
            }
            else
            {
              aZer[2] = std::acos(aVal);
              aZer[3] = THE_2PI - aZer[2];
            }
            aNZer = 4;
          }

          for (size_t i = 0; i < aNZer; ++i)
          {
            if (aZer[i] <= aMyBorneInf - theEps)
            {
              aZer[i] += THE_2PI;
            }
            aZer[i] += std::trunc(aMod) * THE_2PI;
            double aX = aZer[i] - aMyBorneInf;
            if (aX >= -1.0e-10 && aX <= aDelta + 1.0e-10)
            {
              aZer[i] = std::max(theInfBound, std::min(theSupBound, aZer[i]));
              aResult.Roots[aResult.NbRoots++] = aZer[i];
            }
          }
          return aResult;
        }
        if (std::abs(theD) <= theEps)
        {

          aZer[0] = THE_PI / 2.0;
          aZer[1] = THE_PI * 3.0 / 2.0;
          aNZer   = 2;

          double aVal = -theC / (theB * 2.0);
          if (std::abs(aVal) <= 1.0 + 1.0e-10)
          {
            if (aVal >= 1.0)
            {
              aZer[2] = THE_PI / 2.0;
              aZer[3] = THE_PI / 2.0;
            }
            else if (aVal <= -1.0)
            {
              aZer[2] = THE_PI * 3.0 / 2.0;
              aZer[3] = THE_PI * 3.0 / 2.0;
            }
            else
            {
              aZer[2] = std::asin(aVal);
              aZer[3] = THE_PI - aZer[2];
            }
            aNZer = 4;
          }

          for (size_t i = 0; i < aNZer; ++i)
          {
            if (aZer[i] <= aMyBorneInf - theEps)
            {
              aZer[i] += THE_2PI;
            }
            aZer[i] += std::trunc(aMod) * THE_2PI;
            double aX = aZer[i] - aMyBorneInf;
            if (aX >= -1.0e-10 && aX <= aDelta + 1.0e-10)
            {
              aZer[i] = std::max(theInfBound, std::min(theSupBound, aZer[i]));
              aResult.Roots[aResult.NbRoots++] = aZer[i];
            }
          }
          return aResult;
        }
      }

      double ko0 = theA - theC + theE;
      double ko1 = 2.0 * theD - 4.0 * theB;
      double ko2 = 2.0 * theE - 2.0 * theA;
      double ko3 = 4.0 * theB + 2.0 * theD;
      double ko4 = theA + theC + theE;

      MathPoly::PolyResult aPoly = MathPoly::Quartic(ko0, ko1, ko2, ko3, ko4);
      if (!aPoly.IsDone())
      {
        if (aPoly.Status == MathUtils::Status::InfiniteSolutions)
        {
          aResult.InfiniteRoots = true;
        }
        else
        {
          aResult.Status = aPoly.Status;
        }
        return aResult;
      }

      aNZer = aPoly.NbRoots;
      for (size_t i = 0; i < aNZer; ++i)
      {
        aZer[i] = aPoly.Roots[i];
      }

      std::sort(aZer.begin(), aZer.begin() + aNZer);
    }

    for (size_t i = 0; i < aNZer; ++i)
    {
      double aTeta = 2.0 * std::atan(aZer[i]);
      if (aZer[i] <= -theEps)
      {
        aTeta = THE_2PI - std::abs(aTeta);
      }
      aTeta += std::trunc(aMod) * THE_2PI;
      if (aTeta - aMyBorneInf < 0.0)
      {
        aTeta += THE_2PI;
      }

      double aX = aTeta - aMyBorneInf;
      if (aX >= -aDelta_Eps && aX <= aDelta + aDelta_Eps)
      {

        auto aRefineRoot = [&](double theX) -> double
        {
          constexpr int    THE_MAX_ITER = 20;
          constexpr double THE_TOL      = 1.0e-14;

          for (int anIter = 0; anIter < THE_MAX_ITER; ++anIter)
          {
            double aCos  = std::cos(theX);
            double aSin  = std::sin(theX);
            double aCos2 = aCos * aCos;
            double aSin2 = aSin * aSin;
            double aCS   = aCos * aSin;

            double aF = theA * aCos2 + 2.0 * theB * aCS + theC * aCos + theD * aSin + theE;
            double aDF =
              -2.0 * theA * aCS + 2.0 * theB * (aCos2 - aSin2) - theC * aSin + theD * aCos;

            if (std::abs(aF) < 1.0e-15)
            {
              break;
            }

            double aDelta;
            if (std::abs(aDF) < 1.0e-10 * (std::abs(aF) + 1.0))
            {

              double aD2F =
                -2.0 * theA * (aCos2 - aSin2) - 4.0 * theB * aCS - theC * aCos - theD * aSin;
              double aDenom = 2.0 * aDF * aDF - aF * aD2F;
              if (std::abs(aDenom) < 1.0e-30)
              {

                break;
              }
              aDelta = 2.0 * aF * aDF / aDenom;
            }
            else
            {

              aDelta = aF / aDF;
            }

            constexpr double THE_MAX_STEP = 0.5;
            if (std::abs(aDelta) > THE_MAX_STEP)
            {
              aDelta = (aDelta > 0) ? THE_MAX_STEP : -THE_MAX_STEP;
            }

            theX -= aDelta;

            if (std::abs(aDelta) < THE_TOL)
            {
              break;
            }
          }
          return theX;
        };

        double aTetaRefined = aRefineRoot(aTeta);

        double aDeltaNewton = std::abs(aTetaRefined - aTeta);
        double aSupmInfs100 = (theSupBound - theInfBound) * 0.01;
        if (aDeltaNewton <= aSupmInfs100)
        {
          aTeta = aTetaRefined;
        }

        bool aFound = false;
        for (int k = 0; k < aResult.NbRoots; ++k)
        {
          if (std::abs(aTeta - aResult.Roots[k]) < theEps)
          {
            aFound = true;
            break;
          }
        }

        if (!aFound && aResult.NbRoots < 4)
        {

          int aPos = aResult.NbRoots;
          for (int k = 0; k < aResult.NbRoots; ++k)
          {
            if (aTeta < aResult.Roots[k])
            {
              aPos = k;
              break;
            }
          }
          for (int k = aResult.NbRoots; k > aPos; --k)
          {
            aResult.Roots[k] = aResult.Roots[k - 1];
          }
          aResult.Roots[aPos] = aTeta;
          aResult.NbRoots++;
        }
      }
    }

    if (aResult.NbRoots < 4 && std::abs(theA - theC + theE) <= theEps)
    {
      double aTeta = THE_PI + std::trunc(aMod) * THE_2PI;
      double aX    = aTeta - aMyBorneInf;
      if (aX >= -aDelta_Eps && aX <= aDelta + aDelta_Eps)
      {
        bool aFound = false;
        for (int k = 0; k < aResult.NbRoots; ++k)
        {
          if (std::abs(aTeta - aResult.Roots[k]) <= theEps)
          {
            aFound = true;
            break;
          }
        }
        if (!aFound)
        {
          int aPos = aResult.NbRoots;
          for (int k = 0; k < aResult.NbRoots; ++k)
          {
            if (aTeta < aResult.Roots[k])
            {
              aPos = k;
              break;
            }
          }
          for (int k = aResult.NbRoots; k > aPos; --k)
          {
            aResult.Roots[k] = aResult.Roots[k - 1];
          }
          aResult.Roots[aPos] = aTeta;
          aResult.NbRoots++;
        }
      }
    }

    return aResult;
  }

  inline TrigResult TrigonometricLinear(double theD,
                                        double theE,
                                        double theInfBound = 0.0,
                                        double theSupBound = THE_2PI)
  {
    return Trigonometric(0.0, 0.0, 0.0, theD, theE, theInfBound, theSupBound);
  }

  inline TrigResult TrigonometricCDE(double theC,
                                     double theD,
                                     double theE,
                                     double theInfBound = 0.0,
                                     double theSupBound = THE_2PI)
  {
    return Trigonometric(0.0, 0.0, theC, theD, theE, theInfBound, theSupBound);
  }

} // namespace MathRoot
