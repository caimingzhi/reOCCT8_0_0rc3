#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathLin_Gauss.hpp>
#include <MathUtils_Core.hpp>
#include <MathUtils_LineSearch.hpp>
#include <MathUtils_Deriv.hpp>

#include <cmath>

namespace MathOpt
{
  using namespace MathUtils;

  struct NewtonConfig : Config
  {
    double Regularization = 1.0e-8;
    bool   UseLineSearch  = true;

    NewtonConfig() = default;

    explicit NewtonConfig(double theTolerance, int theMaxIter = 100)
        : Config(theTolerance, theMaxIter)
    {
    }
  };

  template <typename Function>
  VectorResult Newton(Function&           theFunc,
                      const math_Vector&  theStartingPoint,
                      const NewtonConfig& theConfig = NewtonConfig())
  {
    VectorResult aResult;

    const int aLower = theStartingPoint.Lower();
    const int aUpper = theStartingPoint.Upper();

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

    double aGradNorm = 0.0;
    for (int i = aLower; i <= aUpper; ++i)
    {
      aGradNorm += MathUtils::Sqr(aGrad(i));
    }
    aGradNorm = std::sqrt(aGradNorm);

    if (aGradNorm < theConfig.FTolerance)
    {
      aResult.Status   = Status::OK;
      aResult.Solution = aX;
      aResult.Value    = aFx;
      aResult.Gradient = aGrad;
      return aResult;
    }

    math_Vector aDir(aLower, aUpper);
    math_Vector aXNew(aLower, aUpper);
    math_Vector aGradNew(aLower, aUpper);
    math_Matrix aHessian(aLower, aUpper, aLower, aUpper);
    math_Vector aNegGrad(aLower, aUpper);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      if (!theFunc.Hessian(aX, aHessian))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aNegGrad(i) = -aGrad(i);
      }

      auto aLinResult = MathLin::Solve(aHessian, aNegGrad);

      if (!aLinResult.IsDone())
      {

        double aLambda = theConfig.Regularization;
        bool   aSolved = false;

        for (int k = 0; k < 10 && !aSolved; ++k)
        {
          math_Matrix aRegHessian = aHessian;
          for (int i = aLower; i <= aUpper; ++i)
          {
            aRegHessian(i, i) += aLambda;
          }

          aLinResult = MathLin::Solve(aRegHessian, aNegGrad);
          if (aLinResult.IsDone())
          {
            aSolved = true;
          }
          else
          {
            aLambda *= 10.0;
          }
        }

        if (!aSolved)
        {

          for (int i = aLower; i <= aUpper; ++i)
          {
            aDir(i) = -aGrad(i);
          }
          goto perform_line_search;
        }
      }

      aDir = *aLinResult.Solution;

      {
        double aDirDeriv = 0.0;
        for (int i = aLower; i <= aUpper; ++i)
        {
          aDirDeriv += aGrad(i) * aDir(i);
        }

        if (aDirDeriv >= 0.0)
        {

          for (int i = aLower; i <= aUpper; ++i)
          {
            aDir(i) = -aGrad(i);
          }
        }
      }

    perform_line_search:
      if (theConfig.UseLineSearch)
      {

        MathUtils::LineSearchResult aLineResult =
          MathUtils::ArmijoBacktrack(theFunc, aX, aDir, aGrad, aFx, 1.0, 1.0e-4, 0.5, 50);

        if (!aLineResult.IsValid)
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
        }

        for (int i = aLower; i <= aUpper; ++i)
        {
          aXNew(i) = aX(i) + aLineResult.Alpha * aDir(i);
        }
        aFx = aLineResult.FNew;
      }
      else
      {

        for (int i = aLower; i <= aUpper; ++i)
        {
          aXNew(i) = aX(i) + aDir(i);
        }

        if (!theFunc.Value(aXNew, aFx))
        {
          aResult.Status   = Status::NumericalError;
          aResult.Solution = aX;
          return aResult;
        }
      }

      double aMaxDiff = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aXNew(i) - aX(i)));
      }

      if (!theFunc.Gradient(aXNew, aGradNew))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aXNew;
        aResult.Value    = aFx;
        return aResult;
      }

      aGradNorm = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aGradNorm += MathUtils::Sqr(aGradNew(i));
      }
      aGradNorm = std::sqrt(aGradNorm);

      if (aGradNorm < theConfig.FTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aFx;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      if (aMaxDiff < theConfig.XTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aFx;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      aX    = aXNew;
      aGrad = aGradNew;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    aResult.Gradient = aGrad;
    return aResult;
  }

  template <typename Function>
  VectorResult NewtonModified(Function&           theFunc,
                              const math_Vector&  theStartingPoint,
                              const NewtonConfig& theConfig = NewtonConfig())
  {
    return Newton(theFunc, theStartingPoint, theConfig);
  }

  template <typename Function>
  VectorResult NewtonNumericalHessian(Function&           theFunc,
                                      const math_Vector&  theStartingPoint,
                                      double              theHessStep = 1.0e-6,
                                      const NewtonConfig& theConfig   = NewtonConfig())
  {

    class FuncWithHessian
    {
    public:
      FuncWithHessian(Function& theF, double theStep)
          : myFunc(theF),
            myStep(theStep)
      {
      }

      bool Value(const math_Vector& theX, double& theF) { return myFunc.Value(theX, theF); }

      bool Gradient(const math_Vector& theX, math_Vector& theGrad)
      {
        return myFunc.Gradient(theX, theGrad);
      }

      bool Hessian(const math_Vector& theX, math_Matrix& theHess)
      {
        math_Vector aXMod = theX;
        return MathUtils::NumericalHessian(myFunc, aXMod, theHess, myStep);
      }

    private:
      Function& myFunc;
      double    myStep;
    };

    FuncWithHessian aWrapper(theFunc, theHessStep);
    return Newton(aWrapper, theStartingPoint, theConfig);
  }

  template <typename Function>
  VectorResult NewtonNumerical(Function&           theFunc,
                               const math_Vector&  theStartingPoint,
                               double              theGradStep = 1.0e-8,
                               double              theHessStep = 1.0e-6,
                               const NewtonConfig& theConfig   = NewtonConfig())
  {

    class FuncWithDerivatives
    {
    public:
      FuncWithDerivatives(Function& theF, double theGStep, double theHStep)
          : myFunc(theF),
            myGradStep(theGStep),
            myHessStep(theHStep)
      {
      }

      bool Value(const math_Vector& theX, double& theF) { return myFunc.Value(theX, theF); }

      bool Gradient(const math_Vector& theX, math_Vector& theGrad)
      {
        math_Vector aXMod = theX;
        return MathUtils::NumericalGradientAdaptive(myFunc, aXMod, theGrad, myGradStep);
      }

      bool Hessian(const math_Vector& theX, math_Matrix& theHess)
      {

        const int aLower = theX.Lower();
        const int aUpper = theX.Upper();

        math_Vector aXMod = theX;
        math_Vector aGradPlus(aLower, aUpper);
        math_Vector aGradMinus(aLower, aUpper);

        for (int j = aLower; j <= aUpper; ++j)
        {
          const double aXj = aXMod(j);

          aXMod(j) = aXj + myHessStep;
          if (!MathUtils::NumericalGradientAdaptive(myFunc, aXMod, aGradPlus, myGradStep))
          {
            aXMod(j) = aXj;
            return false;
          }

          aXMod(j) = aXj - myHessStep;
          if (!MathUtils::NumericalGradientAdaptive(myFunc, aXMod, aGradMinus, myGradStep))
          {
            aXMod(j) = aXj;
            return false;
          }

          aXMod(j) = aXj;

          for (int i = aLower; i <= aUpper; ++i)
          {
            theHess(i, j) = (aGradPlus(i) - aGradMinus(i)) / (2.0 * myHessStep);
          }
        }

        for (int i = aLower; i <= aUpper; ++i)
        {
          for (int j = i + 1; j <= aUpper; ++j)
          {
            double aAvg   = 0.5 * (theHess(i, j) + theHess(j, i));
            theHess(i, j) = aAvg;
            theHess(j, i) = aAvg;
          }
        }

        return true;
      }

    private:
      Function& myFunc;
      double    myGradStep;
      double    myHessStep;
    };

    FuncWithDerivatives aWrapper(theFunc, theGradStep, theHessStep);
    return Newton(aWrapper, theStartingPoint, theConfig);
  }

  template <typename Function>
  VectorResult NewtonBounded(Function&           theFunc,
                             const math_Vector&  theStartingPoint,
                             const math_Vector&  theLowerBounds,
                             const math_Vector&  theUpperBounds,
                             const NewtonConfig& theConfig = NewtonConfig())
  {
    VectorResult aResult;

    const int aLower = theStartingPoint.Lower();
    const int aUpper = theStartingPoint.Upper();
    const int aN     = aUpper - aLower + 1;

    if (theLowerBounds.Length() != aN || theUpperBounds.Length() != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    auto ClampToBounds = [&](math_Vector& theX)
    {
      for (int i = aLower; i <= aUpper; ++i)
      {
        const int aBndIdx = theLowerBounds.Lower() + (i - aLower);
        if (theX(i) < theLowerBounds(aBndIdx))
        {
          theX(i) = theLowerBounds(aBndIdx);
        }
        if (theX(i) > theUpperBounds(aBndIdx))
        {
          theX(i) = theUpperBounds(aBndIdx);
        }
      }
    };

    auto ProjectGradient = [&](const math_Vector& theX, math_Vector& theGrad)
    {
      for (int i = aLower; i <= aUpper; ++i)
      {
        const int    aBndIdx = theLowerBounds.Lower() + (i - aLower);
        const double aTol    = MathUtils::THE_EPSILON * std::max(1.0, std::abs(theX(i)));

        if (theX(i) - theLowerBounds(aBndIdx) < aTol && theGrad(i) > 0.0)
        {
          theGrad(i) = 0.0;
        }
        if (theUpperBounds(aBndIdx) - theX(i) < aTol && theGrad(i) < 0.0)
        {
          theGrad(i) = 0.0;
        }
      }
    };

    auto ComputeAlphaMax = [&](const math_Vector& theX, const math_Vector& theDir) -> double
    {
      double aAlphaMax = 1.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        const int aBndIdx = theLowerBounds.Lower() + (i - aLower);
        if (theDir(i) < -MathUtils::THE_EPSILON)
        {
          double aMaxStep = (theLowerBounds(aBndIdx) - theX(i)) / theDir(i);
          aAlphaMax       = std::min(aAlphaMax, aMaxStep);
        }
        else if (theDir(i) > MathUtils::THE_EPSILON)
        {
          double aMaxStep = (theUpperBounds(aBndIdx) - theX(i)) / theDir(i);
          aAlphaMax       = std::min(aAlphaMax, aMaxStep);
        }
      }
      return std::max(aAlphaMax, MathUtils::THE_EPSILON);
    };

    math_Vector aX(aLower, aUpper);
    aX = theStartingPoint;
    ClampToBounds(aX);

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
    ProjectGradient(aX, aGrad);

    double aGradNorm = 0.0;
    for (int i = aLower; i <= aUpper; ++i)
    {
      aGradNorm += MathUtils::Sqr(aGrad(i));
    }
    aGradNorm = std::sqrt(aGradNorm);

    if (aGradNorm < theConfig.FTolerance)
    {
      aResult.Status   = Status::OK;
      aResult.Solution = aX;
      aResult.Value    = aFx;
      aResult.Gradient = aGrad;
      return aResult;
    }

    math_Vector aDir(aLower, aUpper);
    math_Vector aXNew(aLower, aUpper);
    math_Vector aGradNew(aLower, aUpper);
    math_Matrix aHessian(aLower, aUpper, aLower, aUpper);
    math_Vector aNegGrad(aLower, aUpper);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      if (!theFunc.Hessian(aX, aHessian))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aNegGrad(i) = -aGrad(i);
      }

      auto aLinResult = MathLin::Solve(aHessian, aNegGrad);

      if (!aLinResult.IsDone())
      {

        double aLambda = theConfig.Regularization;
        bool   aSolved = false;

        for (int k = 0; k < 10 && !aSolved; ++k)
        {
          math_Matrix aRegHessian = aHessian;
          for (int i = aLower; i <= aUpper; ++i)
          {
            aRegHessian(i, i) += aLambda;
          }

          aLinResult = MathLin::Solve(aRegHessian, aNegGrad);
          if (aLinResult.IsDone())
          {
            aSolved = true;
          }
          else
          {
            aLambda *= 10.0;
          }
        }

        if (!aSolved)
        {

          for (int i = aLower; i <= aUpper; ++i)
          {
            aDir(i) = -aGrad(i);
          }
          goto perform_bounded_line_search;
        }
      }

      aDir = *aLinResult.Solution;

      {
        double aDirDeriv = 0.0;
        for (int i = aLower; i <= aUpper; ++i)
        {
          aDirDeriv += aGrad(i) * aDir(i);
        }

        if (aDirDeriv >= 0.0)
        {
          for (int i = aLower; i <= aUpper; ++i)
          {
            aDir(i) = -aGrad(i);
          }
        }
      }

    perform_bounded_line_search:
      if (theConfig.UseLineSearch)
      {
        double aAlphaMax = ComputeAlphaMax(aX, aDir);

        MathUtils::LineSearchResult aLineResult =
          MathUtils::ArmijoBacktrack(theFunc, aX, aDir, aGrad, aFx, aAlphaMax, 1.0e-4, 0.5, 50);

        if (!aLineResult.IsValid)
        {

          for (int i = aLower; i <= aUpper; ++i)
          {
            aDir(i) = -aGrad(i);
          }
          aAlphaMax = ComputeAlphaMax(aX, aDir);
          aLineResult =
            MathUtils::ArmijoBacktrack(theFunc, aX, aDir, aGrad, aFx, aAlphaMax, 1.0e-4, 0.5, 50);

          if (!aLineResult.IsValid)
          {
            aResult.Status   = Status::NotConverged;
            aResult.Solution = aX;
            aResult.Value    = aFx;
            aResult.Gradient = aGrad;
            return aResult;
          }
        }

        for (int i = aLower; i <= aUpper; ++i)
        {
          aXNew(i) = aX(i) + aLineResult.Alpha * aDir(i);
        }
        ClampToBounds(aXNew);

        if (!theFunc.Value(aXNew, aFx))
        {
          aResult.Status   = Status::NumericalError;
          aResult.Solution = aX;
          return aResult;
        }
      }
      else
      {
        for (int i = aLower; i <= aUpper; ++i)
        {
          aXNew(i) = aX(i) + aDir(i);
        }
        ClampToBounds(aXNew);

        if (!theFunc.Value(aXNew, aFx))
        {
          aResult.Status   = Status::NumericalError;
          aResult.Solution = aX;
          return aResult;
        }
      }

      double aMaxDiff = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aXNew(i) - aX(i)));
      }

      if (!theFunc.Gradient(aXNew, aGradNew))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aXNew;
        aResult.Value    = aFx;
        return aResult;
      }
      ProjectGradient(aXNew, aGradNew);

      aGradNorm = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aGradNorm += MathUtils::Sqr(aGradNew(i));
      }
      aGradNorm = std::sqrt(aGradNorm);

      if (aGradNorm < theConfig.FTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aFx;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      if (aMaxDiff < theConfig.XTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aFx;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      aX    = aXNew;
      aGrad = aGradNew;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    aResult.Gradient = aGrad;
    return aResult;
  }

} // namespace MathOpt
