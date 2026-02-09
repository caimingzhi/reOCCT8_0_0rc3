#pragma once

#include <MathUtils_GaussKronrodWeights.hpp>

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>

#include <NCollection_Vector.hpp>

#include <cmath>

namespace MathInteg
{
  using namespace MathUtils;

  struct KronrodConfig : IntegConfig
  {
    int  NbGaussPoints = 7;
    bool Adaptive      = true;

    KronrodConfig() = default;

    explicit KronrodConfig(double theTolerance, int theMaxIter = 100)
        : IntegConfig(theTolerance, theMaxIter)
    {
    }
  };

  template <typename Function>
  IntegResult KronrodRule(Function& theFunc, double theLower, double theUpper, int theNbGauss = 7)
  {
    IntegResult aResult;

    const int aNbKronrod = 2 * theNbGauss + 1;

    math_Vector aGaussP(1, theNbGauss);
    math_Vector aGaussW(1, theNbGauss);
    math_Vector aKronrodP(1, aNbKronrod);
    math_Vector aKronrodW(1, aNbKronrod);

    if (!GetKronrodPointsAndWeights(aNbKronrod, aKronrodP, aKronrodW)
        || !GetOrderedGaussPointsAndWeights(theNbGauss, aGaussP, aGaussW))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    const double aHalfLen = 0.5 * (theUpper - theLower);
    const double aMid     = 0.5 * (theUpper + theLower);

    const int aNPnt2 = (aNbKronrod + 1) / 2;

    double aGaussVal   = 0.0;
    double aKronrodVal = 0.0;

    math_Vector aF1(0, aNPnt2 - 1);
    math_Vector aF2(0, aNPnt2 - 1);

    for (int i = 2; i < aNPnt2; i += 2)
    {
      const double aDx   = aHalfLen * aKronrodP(i);
      double       aVal1 = 0.0, aVal2 = 0.0;

      if (!theFunc.Value(aMid + aDx, aVal1) || !theFunc.Value(aMid - aDx, aVal2))
      {
        aResult.Status = Status::NumericalError;
        return aResult;
      }

      aF1(i) = aVal1;
      aF2(i) = aVal2;
      aGaussVal += (aVal1 + aVal2) * aGaussW(i / 2);
      aKronrodVal += (aVal1 + aVal2) * aKronrodW(i);
    }

    double aFc = 0.0;
    if (!theFunc.Value(aMid, aFc))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    aKronrodVal += aFc * aKronrodW(aNPnt2);

    if (aNPnt2 % 2 == 0)
    {
      aGaussVal += aFc * aGaussW(aNPnt2 / 2);
    }

    for (int i = 1; i < aNPnt2; i += 2)
    {
      const double aDx   = aHalfLen * aKronrodP(i);
      double       aVal1 = 0.0, aVal2 = 0.0;

      if (!theFunc.Value(aMid + aDx, aVal1) || !theFunc.Value(aMid - aDx, aVal2))
      {
        aResult.Status = Status::NumericalError;
        return aResult;
      }

      aF1(i) = aVal1;
      aF2(i) = aVal2;
      aKronrodVal += (aVal1 + aVal2) * aKronrodW(i);
    }

    const double aMean = 0.5 * aKronrodVal;
    double       aAsc  = std::abs(aFc - aMean) * aKronrodW(aNPnt2);
    for (int i = 1; i < aNPnt2; ++i)
    {
      aAsc += aKronrodW(i) * (std::abs(aF1(i) - aMean) + std::abs(aF2(i) - aMean));
    }

    aAsc *= aHalfLen;
    aKronrodVal *= aHalfLen;
    aGaussVal *= aHalfLen;

    double aAbsError = std::abs(aKronrodVal - aGaussVal);

    if (aAsc != 0.0 && aAbsError != 0.0)
    {
      const double aScale = std::pow(200.0 * aAbsError / aAsc, 1.5);
      if (aScale < 1.0)
      {
        aAbsError = std::min(aAbsError, aAsc * aScale);
      }
    }

    aResult.Status        = Status::OK;
    aResult.Value         = aKronrodVal;
    aResult.AbsoluteError = aAbsError;
    aResult.RelativeError = aAbsError / std::max(std::abs(aKronrodVal), 1.0e-15);
    aResult.NbPoints      = static_cast<size_t>(aNbKronrod);
    aResult.NbIterations  = 1;
    return aResult;
  }

  template <typename Function>
  IntegResult Kronrod(Function&            theFunc,
                      double               theLower,
                      double               theUpper,
                      const KronrodConfig& theConfig = KronrodConfig())
  {
    IntegResult aResult;

    if (!theConfig.Adaptive)
    {

      return KronrodRule(theFunc, theLower, theUpper, theConfig.NbGaussPoints);
    }

    struct Interval
    {
      double Lower;
      double Upper;
      double Value;
      double Error;
    };

    IntegResult anInitResult = KronrodRule(theFunc, theLower, theUpper, theConfig.NbGaussPoints);
    if (!anInitResult.IsDone())
    {
      return anInitResult;
    }

    NCollection_Vector<Interval> aHeap;
    aHeap.Append({theLower, theUpper, *anInitResult.Value, *anInitResult.AbsoluteError});

    double aTotalValue  = *anInitResult.Value;
    double aTotalError  = *anInitResult.AbsoluteError;
    size_t aTotalPoints = anInitResult.NbPoints;
    int    aIterations  = 1;

    while (aIterations < theConfig.MaxIterations)
    {

      if (aTotalError < theConfig.Tolerance * std::max(std::abs(aTotalValue), 1.0e-15))
      {
        break;
      }

      int    aMaxIdx   = 0;
      double aMaxError = 0.0;
      for (int i = 0; i < aHeap.Length(); ++i)
      {
        if (aHeap.Value(i).Error > aMaxError)
        {
          aMaxError = aHeap.Value(i).Error;
          aMaxIdx   = i;
        }
      }

      if (aMaxError < MathUtils::THE_ZERO_TOL)
      {
        break;
      }

      const Interval aWorst  = aHeap.Value(aMaxIdx);
      const double   aBisMid = 0.5 * (aWorst.Lower + aWorst.Upper);

      IntegResult aLeftResult =
        KronrodRule(theFunc, aWorst.Lower, aBisMid, theConfig.NbGaussPoints);
      IntegResult aRightResult =
        KronrodRule(theFunc, aBisMid, aWorst.Upper, theConfig.NbGaussPoints);

      if (!aLeftResult.IsDone() || !aRightResult.IsDone())
      {
        aResult.Status        = Status::NumericalError;
        aResult.Value         = aTotalValue;
        aResult.AbsoluteError = aTotalError;
        aResult.NbPoints      = aTotalPoints;
        aResult.NbIterations  = static_cast<size_t>(aIterations);
        return aResult;
      }

      aTotalValue -= aWorst.Value;
      aTotalError -= aWorst.Error;
      aTotalValue += *aLeftResult.Value + *aRightResult.Value;
      aTotalError += *aLeftResult.AbsoluteError + *aRightResult.AbsoluteError;
      aTotalPoints += aLeftResult.NbPoints + aRightResult.NbPoints;
      ++aIterations;

      aHeap.ChangeValue(
        aMaxIdx) = {aWorst.Lower, aBisMid, *aLeftResult.Value, *aLeftResult.AbsoluteError};
      aHeap.Append({aBisMid, aWorst.Upper, *aRightResult.Value, *aRightResult.AbsoluteError});
    }

    aResult.Status        = Status::OK;
    aResult.Value         = aTotalValue;
    aResult.AbsoluteError = aTotalError;
    aResult.RelativeError = aTotalError / std::max(std::abs(aTotalValue), 1.0e-15);
    aResult.NbPoints      = aTotalPoints;
    aResult.NbIterations  = static_cast<size_t>(aIterations);
    return aResult;
  }

  template <typename Function>
  IntegResult KronrodAuto(Function& theFunc,
                          double    theLower,
                          double    theUpper,
                          double    theTolerance = 1.0e-10,
                          int       theMaxOrder  = 30)
  {
    IntegResult aBestResult;
    aBestResult.Status = Status::NotConverged;

    for (int aOrder = 7; aOrder <= theMaxOrder; aOrder += 4)
    {
      IntegResult aResult = KronrodRule(theFunc, theLower, theUpper, aOrder);
      if (!aResult.IsDone())
      {
        continue;
      }

      aBestResult = aResult;

      if (aResult.RelativeError && *aResult.RelativeError < theTolerance)
      {
        return aResult;
      }
    }

    KronrodConfig aConfig;
    aConfig.Tolerance     = theTolerance;
    aConfig.NbGaussPoints = 7;
    aConfig.Adaptive      = true;
    aConfig.MaxIterations = 50;

    return Kronrod(theFunc, theLower, theUpper, aConfig);
  }

  template <typename Function>
  IntegResult KronrodSemiInfinite(Function&            theFunc,
                                  double               theLower,
                                  const KronrodConfig& theConfig = KronrodConfig())
  {
    class TransformedFunc
    {
    public:
      TransformedFunc(Function& theF, double theA)
          : myFunc(theF),
            myA(theA)
      {
      }

      bool Value(double theT, double& theF)
      {
        if (theT >= 1.0)
        {
          theF = 0.0;
          return true;
        }

        const double aX     = myA + theT / (1.0 - theT);
        const double aJacob = 1.0 / MathUtils::Sqr(1.0 - theT);

        double aFx = 0.0;
        if (!myFunc.Value(aX, aFx))
        {
          return false;
        }

        theF = aFx * aJacob;
        return true;
      }

    private:
      Function& myFunc;
      double    myA;
    };

    TransformedFunc aTransformed(theFunc, theLower);
    return Kronrod(aTransformed, 0.0, 1.0, theConfig);
  }

  template <typename Function>
  IntegResult KronrodInfinite(Function& theFunc, const KronrodConfig& theConfig = KronrodConfig())
  {
    class TransformedFunc
    {
    public:
      TransformedFunc(Function& theF)
          : myFunc(theF)
      {
      }

      bool Value(double theT, double& theF)
      {
        if (std::abs(theT) >= 1.0)
        {
          theF = 0.0;
          return true;
        }

        const double aT2    = theT * theT;
        const double aX     = theT / (1.0 - aT2);
        const double aJacob = (1.0 + aT2) / MathUtils::Sqr(1.0 - aT2);

        double aFx = 0.0;
        if (!myFunc.Value(aX, aFx))
        {
          return false;
        }

        theF = aFx * aJacob;
        return true;
      }

    private:
      Function& myFunc;
    };

    TransformedFunc aTransformed(theFunc);
    return Kronrod(aTransformed, -1.0, 1.0, theConfig);
  }

} // namespace MathInteg
