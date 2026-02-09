#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>
#include <vector>

namespace MathInteg
{
  using namespace MathUtils;

  struct DoubleExpConfig : IntegConfig
  {
    int    NbLevels   = 6;
    double StepFactor = 0.5;

    DoubleExpConfig() = default;

    explicit DoubleExpConfig(double theTolerance, int theMaxIter = 100)
        : IntegConfig(theTolerance, theMaxIter)
    {
    }
  };

  template <typename Function>
  IntegResult TanhSinh(Function&              theFunc,
                       double                 theLower,
                       double                 theUpper,
                       const DoubleExpConfig& theConfig = DoubleExpConfig())
  {
    IntegResult aResult;

    if (theLower >= theUpper)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const double aHalfPi = M_PI / 2.0;
    const double aMid    = 0.5 * (theUpper + theLower);
    const double aHalf   = 0.5 * (theUpper - theLower);

    double aH = 1.0;

    double aPrevSum     = 0.0;
    size_t aTotalPoints = 0;

    for (int aLevel = 0; aLevel < theConfig.NbLevels; ++aLevel)
    {
      double aSum      = 0.0;
      int    aNbPoints = 0;

      int aStart = (aLevel == 0) ? 0 : 1;
      int aStep  = (aLevel == 0) ? 1 : 2;

      for (int k = aStart;; k += aStep)
      {
        double aT = k * aH;

        double aSinhT = std::sinh(aT);
        double aCoshT = std::cosh(aT);

        double aU = aHalfPi * aSinhT;

        if (std::abs(aU) > 700.0)
        {
          break;
        }

        double aTanhU  = std::tanh(aU);
        double aCoshU  = std::cosh(aU);
        double aSech2U = 1.0 / (aCoshU * aCoshU);

        double aX = aMid + aHalf * aTanhU;

        if (aX <= theLower + MathUtils::THE_ZERO_TOL || aX >= theUpper - MathUtils::THE_ZERO_TOL)
        {
          break;
        }

        double aWeight = aHalf * aHalfPi * aCoshT * aSech2U;

        if (aWeight < MathUtils::THE_ZERO_TOL)
        {
          break;
        }

        double aF = 0.0;
        if (!theFunc.Value(aX, aF))
        {

          continue;
        }

        if (!std::isfinite(aF))
        {
          continue;
        }

        aSum += aWeight * aF;
        ++aNbPoints;

        if (aNbPoints > 10000)
        {
          break;
        }
      }

      int aNegStart = (aLevel == 0) ? 1 : aStart;
      for (int k = aNegStart;; k += aStep)
      {
        double aT = -k * aH;

        double aSinhT = std::sinh(aT);
        double aCoshT = std::cosh(aT);
        double aU     = aHalfPi * aSinhT;

        if (std::abs(aU) > 700.0)
        {
          break;
        }

        double aTanhU  = std::tanh(aU);
        double aCoshU  = std::cosh(aU);
        double aSech2U = 1.0 / (aCoshU * aCoshU);

        double aX = aMid + aHalf * aTanhU;

        if (aX <= theLower + MathUtils::THE_ZERO_TOL || aX >= theUpper - MathUtils::THE_ZERO_TOL)
        {
          break;
        }

        double aWeight = aHalf * aHalfPi * aCoshT * aSech2U;

        if (aWeight < MathUtils::THE_ZERO_TOL)
        {
          break;
        }

        double aF = 0.0;
        if (!theFunc.Value(aX, aF))
        {
          continue;
        }

        if (!std::isfinite(aF))
        {
          continue;
        }

        aSum += aWeight * aF;
        ++aNbPoints;

        if (aNbPoints > 10000)
        {
          break;
        }
      }

      double aLevelSum = aH * aSum;
      aTotalPoints += static_cast<size_t>(aNbPoints);

      double aNewSum = (aLevel == 0) ? aLevelSum : 0.5 * aPrevSum + aLevelSum;

      if (aLevel > 0)
      {
        double aAbsError = std::abs(aNewSum - aPrevSum);
        double aRelError = aAbsError / std::max(std::abs(aNewSum), 1.0e-15);

        if (aRelError < theConfig.Tolerance)
        {
          aResult.Status        = Status::OK;
          aResult.Value         = aNewSum;
          aResult.AbsoluteError = aAbsError;
          aResult.RelativeError = aRelError;
          aResult.NbPoints      = aTotalPoints;
          aResult.NbIterations  = static_cast<size_t>(aLevel + 1);
          return aResult;
        }
      }

      aPrevSum = aNewSum;
      aH *= 0.5;
    }

    aResult.Status       = Status::OK;
    aResult.Value        = aPrevSum;
    aResult.NbPoints     = aTotalPoints;
    aResult.NbIterations = static_cast<size_t>(theConfig.NbLevels);
    return aResult;
  }

  template <typename Function>
  IntegResult ExpSinh(Function&              theFunc,
                      double                 theLower,
                      const DoubleExpConfig& theConfig = DoubleExpConfig())
  {
    IntegResult aResult;

    const double aHalfPi      = M_PI / 2.0;
    double       aH           = 1.0;
    double       aPrevSum     = 0.0;
    size_t       aTotalPoints = 0;

    for (int aLevel = 0; aLevel < theConfig.NbLevels; ++aLevel)
    {
      double aSum      = 0.0;
      int    aNbPoints = 0;

      int aStart = (aLevel == 0) ? 0 : 1;
      int aStep  = (aLevel == 0) ? 1 : 2;

      for (int aSign = -1; aSign <= 1; aSign += 2)
      {
        for (int k = (aSign < 0 && aLevel == 0) ? 1 : aStart;; k += aStep)
        {
          if (aSign < 0 && k == 0)
          {
            continue;
          }

          double aT = aSign * k * aH;

          double aSinhT = std::sinh(aT);
          double aCoshT = std::cosh(aT);
          double aU     = aHalfPi * aSinhT;

          if (aU > 700.0)
          {
            break;
          }

          double aExpU = std::exp(aU);

          double aX = theLower + aExpU;

          double aWeight = aHalfPi * aCoshT * aExpU;

          if (aWeight < MathUtils::THE_ZERO_TOL || !std::isfinite(aWeight))
          {
            break;
          }

          if (aU < -30.0)
          {
            break;
          }

          double aF = 0.0;
          if (!theFunc.Value(aX, aF))
          {
            continue;
          }

          if (!std::isfinite(aF))
          {
            continue;
          }

          aSum += aWeight * aF;
          ++aNbPoints;

          if (aNbPoints > 10000)
          {
            break;
          }
        }
      }

      double aLevelSum = aH * aSum;
      aTotalPoints += static_cast<size_t>(aNbPoints);

      double aNewSum = (aLevel == 0) ? aLevelSum : 0.5 * aPrevSum + aLevelSum;

      if (aLevel > 0)
      {
        double aAbsError = std::abs(aNewSum - aPrevSum);
        double aRelError = aAbsError / std::max(std::abs(aNewSum), 1.0e-15);

        if (aRelError < theConfig.Tolerance)
        {
          aResult.Status        = Status::OK;
          aResult.Value         = aNewSum;
          aResult.AbsoluteError = aAbsError;
          aResult.RelativeError = aRelError;
          aResult.NbPoints      = aTotalPoints;
          aResult.NbIterations  = static_cast<size_t>(aLevel + 1);
          return aResult;
        }
      }

      aPrevSum = aNewSum;
      aH *= 0.5;
    }

    aResult.Status       = Status::OK;
    aResult.Value        = aPrevSum;
    aResult.NbPoints     = aTotalPoints;
    aResult.NbIterations = static_cast<size_t>(theConfig.NbLevels);
    return aResult;
  }

  template <typename Function>
  IntegResult SinhSinh(Function& theFunc, const DoubleExpConfig& theConfig = DoubleExpConfig())
  {
    IntegResult aResult;

    const double aHalfPi      = M_PI / 2.0;
    double       aH           = 1.0;
    double       aPrevSum     = 0.0;
    size_t       aTotalPoints = 0;

    for (int aLevel = 0; aLevel < theConfig.NbLevels; ++aLevel)
    {
      double aSum      = 0.0;
      int    aNbPoints = 0;

      int aStart = (aLevel == 0) ? 0 : 1;
      int aStep  = (aLevel == 0) ? 1 : 2;

      for (int aSign = -1; aSign <= 1; aSign += 2)
      {
        for (int k = (aSign < 0 && aLevel == 0) ? 1 : aStart;; k += aStep)
        {
          if (aSign < 0 && k == 0)
          {
            continue;
          }

          double aT = aSign * k * aH;

          double aSinhT = std::sinh(aT);
          double aCoshT = std::cosh(aT);
          double aU     = aHalfPi * aSinhT;

          if (std::abs(aU) > 700.0)
          {
            break;
          }

          double aSinhU = std::sinh(aU);
          double aCoshU = std::cosh(aU);

          double aX = aSinhU;

          double aWeight = aHalfPi * aCoshT * aCoshU;

          if (aWeight < MathUtils::THE_ZERO_TOL || !std::isfinite(aWeight))
          {
            break;
          }

          double aF = 0.0;
          if (!theFunc.Value(aX, aF))
          {
            continue;
          }

          if (!std::isfinite(aF))
          {
            continue;
          }

          aSum += aWeight * aF;
          ++aNbPoints;

          if (aNbPoints > 10000)
          {
            break;
          }
        }
      }

      double aLevelSum = aH * aSum;
      aTotalPoints += static_cast<size_t>(aNbPoints);

      double aNewSum = (aLevel == 0) ? aLevelSum : 0.5 * aPrevSum + aLevelSum;

      if (aLevel > 0)
      {
        double aAbsError = std::abs(aNewSum - aPrevSum);
        double aRelError = aAbsError / std::max(std::abs(aNewSum), 1.0e-15);

        if (aRelError < theConfig.Tolerance)
        {
          aResult.Status        = Status::OK;
          aResult.Value         = aNewSum;
          aResult.AbsoluteError = aAbsError;
          aResult.RelativeError = aRelError;
          aResult.NbPoints      = aTotalPoints;
          aResult.NbIterations  = static_cast<size_t>(aLevel + 1);
          return aResult;
        }
      }

      aPrevSum = aNewSum;
      aH *= 0.5;
    }

    aResult.Status       = Status::OK;
    aResult.Value        = aPrevSum;
    aResult.NbPoints     = aTotalPoints;
    aResult.NbIterations = static_cast<size_t>(theConfig.NbLevels);
    return aResult;
  }

  template <typename Function>
  IntegResult DoubleExponential(Function&              theFunc,
                                double                 theLower,
                                double                 theUpper,
                                const DoubleExpConfig& theConfig = DoubleExpConfig())
  {
    const double aHuge = 1.0e300;

    bool aIsLowerInf = (theLower < -aHuge);
    bool aIsUpperInf = (theUpper > aHuge);

    if (aIsLowerInf && aIsUpperInf)
    {

      return SinhSinh(theFunc, theConfig);
    }
    else if (aIsUpperInf)
    {

      return ExpSinh(theFunc, theLower, theConfig);
    }
    else if (aIsLowerInf)
    {

      class NegatedFunc
      {
      public:
        NegatedFunc(Function& theF)
            : myFunc(theF)
        {
        }

        bool Value(double theX, double& theF) { return myFunc.Value(-theX, theF); }

      private:
        Function& myFunc;
      };

      NegatedFunc aNegated(theFunc);
      return ExpSinh(aNegated, -theUpper, theConfig);
    }
    else
    {

      return TanhSinh(theFunc, theLower, theUpper, theConfig);
    }
  }

  template <typename Function>
  IntegResult TanhSinhSingular(Function& theFunc,
                               double    theLower,
                               double    theUpper,
                               double    theTolerance = 1.0e-10)
  {
    DoubleExpConfig aConfig;
    aConfig.Tolerance = theTolerance;
    aConfig.NbLevels  = 8;

    return TanhSinh(theFunc, theLower, theUpper, aConfig);
  }

  template <typename Function>
  IntegResult TanhSinhWithSingularity(Function&              theFunc,
                                      double                 theLower,
                                      double                 theUpper,
                                      double                 theSingularity,
                                      const DoubleExpConfig& theConfig = DoubleExpConfig())
  {
    IntegResult aResult;

    if (theSingularity <= theLower || theSingularity >= theUpper)
    {

      return TanhSinh(theFunc, theLower, theUpper, theConfig);
    }

    IntegResult aLeft = TanhSinh(theFunc, theLower, theSingularity, theConfig);
    if (!aLeft.IsDone())
    {
      return aLeft;
    }

    IntegResult aRight = TanhSinh(theFunc, theSingularity, theUpper, theConfig);
    if (!aRight.IsDone())
    {
      return aRight;
    }

    aResult.Status       = Status::OK;
    aResult.Value        = *aLeft.Value + *aRight.Value;
    aResult.NbPoints     = aLeft.NbPoints + aRight.NbPoints;
    aResult.NbIterations = std::max(aLeft.NbIterations, aRight.NbIterations);

    if (aLeft.AbsoluteError && aRight.AbsoluteError)
    {
      aResult.AbsoluteError = *aLeft.AbsoluteError + *aRight.AbsoluteError;
      aResult.RelativeError = *aResult.AbsoluteError / std::max(std::abs(*aResult.Value), 1.0e-15);
    }

    return aResult;
  }

} // namespace MathInteg
