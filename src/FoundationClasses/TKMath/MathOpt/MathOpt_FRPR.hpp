#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <MathUtils_LineSearch.hpp>
#include <MathUtils_Deriv.hpp>

#include <cmath>

namespace MathOpt
{
  using namespace MathUtils;

  enum class ConjugateGradientFormula
  {
    FletcherReeves,
    PolakRibiere,
    HestenesStiefel,
    DaiYuan
  };

  struct FRPRConfig : Config
  {
    ConjugateGradientFormula Formula         = ConjugateGradientFormula::PolakRibiere;
    int                      RestartInterval = 0;

    FRPRConfig() = default;

    explicit FRPRConfig(double theTolerance, int theMaxIter = 100)
        : Config(theTolerance, theMaxIter)
    {
    }
  };

  template <typename Function>
  VectorResult FRPR(Function&          theFunc,
                    const math_Vector& theStartingPoint,
                    const FRPRConfig&  theConfig = FRPRConfig())
  {
    VectorResult aResult;

    const int aLower = theStartingPoint.Lower();
    const int aUpper = theStartingPoint.Upper();
    const int aN     = aUpper - aLower + 1;

    const int aRestartInterval = (theConfig.RestartInterval > 0) ? theConfig.RestartInterval : aN;

    math_Vector aX(aLower, aUpper);
    aX = theStartingPoint;

    double aFx = 0.0;
    if (!theFunc.Value(aX, aFx))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    math_Vector aGrad(aLower, aUpper);
    if (!theFunc.Gradient(aX, aGrad))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    double aGradNormSq = 0.0;
    for (int i = aLower; i <= aUpper; ++i)
    {
      aGradNormSq += MathUtils::Sqr(aGrad(i));
    }

    if (std::sqrt(aGradNormSq) < theConfig.FTolerance)
    {
      aResult.Status   = Status::OK;
      aResult.Solution = aX;
      aResult.Value    = aFx;
      aResult.Gradient = aGrad;
      return aResult;
    }

    math_Vector aDir(aLower, aUpper);
    for (int i = aLower; i <= aUpper; ++i)
    {
      aDir(i) = -aGrad(i);
    }

    math_Vector aXNew(aLower, aUpper);
    math_Vector aGradNew(aLower, aUpper);
    math_Vector aGradDiff(aLower, aUpper);

    int aRestartCount = 0;

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      MathUtils::LineSearchResult aLineResult =
        MathUtils::ArmijoBacktrack(theFunc, aX, aDir, aGrad, aFx, 1.0, 1.0e-4, 0.5, 50);

      if (!aLineResult.IsValid || aLineResult.Alpha < MathUtils::THE_EPSILON)
      {

        for (int i = aLower; i <= aUpper; ++i)
        {
          aDir(i) = -aGrad(i);
        }
        aLineResult =
          MathUtils::ArmijoBacktrack(theFunc, aX, aDir, aGrad, aFx, 1.0, 1.0e-4, 0.5, 50);

        if (!aLineResult.IsValid)
        {
          aResult.Status   = Status::NotConverged;
          aResult.Solution = aX;
          aResult.Value    = aFx;
          aResult.Gradient = aGrad;
          return aResult;
        }
        aRestartCount = 0;
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aXNew(i) = aX(i) + aLineResult.Alpha * aDir(i);
      }

      double aMaxDiff = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aXNew(i) - aX(i)));
      }

      if (!theFunc.Gradient(aXNew, aGradNew))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }

      double aGradNewNormSq = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aGradNewNormSq += MathUtils::Sqr(aGradNew(i));
      }

      if (std::sqrt(aGradNewNormSq) < theConfig.FTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aLineResult.FNew;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      if (aMaxDiff < theConfig.XTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aLineResult.FNew;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aGradDiff(i) = aGradNew(i) - aGrad(i);
      }

      double aBeta = 0.0;
      ++aRestartCount;

      if (aRestartCount >= aRestartInterval)
      {

        aBeta         = 0.0;
        aRestartCount = 0;
      }
      else
      {
        switch (theConfig.Formula)
        {
          case ConjugateGradientFormula::FletcherReeves:

            if (aGradNormSq > MathUtils::THE_ZERO_TOL)
            {
              aBeta = aGradNewNormSq / aGradNormSq;
            }
            break;

          case ConjugateGradientFormula::PolakRibiere:
          {

            double aDot = 0.0;
            for (int i = aLower; i <= aUpper; ++i)
            {
              aDot += aGradNew(i) * aGradDiff(i);
            }
            if (aGradNormSq > MathUtils::THE_ZERO_TOL)
            {
              aBeta = aDot / aGradNormSq;
            }

            if (aBeta < 0.0)
            {
              aBeta         = 0.0;
              aRestartCount = 0;
            }
          }
          break;

          case ConjugateGradientFormula::HestenesStiefel:
          {

            double aNum = 0.0;
            double aDen = 0.0;
            for (int i = aLower; i <= aUpper; ++i)
            {
              aNum += aGradNew(i) * aGradDiff(i);
              aDen += aDir(i) * aGradDiff(i);
            }
            if (std::abs(aDen) > MathUtils::THE_ZERO_TOL)
            {
              aBeta = aNum / aDen;
            }
            if (aBeta < 0.0)
            {
              aBeta         = 0.0;
              aRestartCount = 0;
            }
          }
          break;

          case ConjugateGradientFormula::DaiYuan:
          {

            double aDen = 0.0;
            for (int i = aLower; i <= aUpper; ++i)
            {
              aDen += aDir(i) * aGradDiff(i);
            }
            if (std::abs(aDen) > MathUtils::THE_ZERO_TOL)
            {
              aBeta = aGradNewNormSq / aDen;
            }
          }
          break;
        }
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aDir(i) = -aGradNew(i) + aBeta * aDir(i);
      }

      double aDirDeriv = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aDirDeriv += aGradNew(i) * aDir(i);
      }

      if (aDirDeriv >= 0.0)
      {

        for (int i = aLower; i <= aUpper; ++i)
        {
          aDir(i) = -aGradNew(i);
        }
        aRestartCount = 0;
      }

      aX          = aXNew;
      aGrad       = aGradNew;
      aGradNormSq = aGradNewNormSq;
      aFx         = aLineResult.FNew;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    aResult.Gradient = aGrad;
    return aResult;
  }

  template <typename Function>
  VectorResult FRPRNumerical(Function&          theFunc,
                             const math_Vector& theStartingPoint,
                             double             theGradStep = 1.0e-8,
                             const FRPRConfig&  theConfig   = FRPRConfig())
  {

    class FuncWithGradient
    {
    public:
      FuncWithGradient(Function& theF, double theStep)
          : myFunc(theF),
            myStep(theStep)
      {
      }

      bool Value(const math_Vector& theX, double& theF) { return myFunc.Value(theX, theF); }

      bool Gradient(const math_Vector& theX, math_Vector& theGrad)
      {
        math_Vector aXMod = theX;
        return MathUtils::NumericalGradientAdaptive(myFunc, aXMod, theGrad, myStep);
      }

    private:
      Function& myFunc;
      double    myStep;
    };

    FuncWithGradient aWrapper(theFunc, theGradStep);
    return FRPR(aWrapper, theStartingPoint, theConfig);
  }

} // namespace MathOpt
