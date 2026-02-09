#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathLin_Gauss.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>

namespace MathSys
{
  using namespace MathUtils;

  struct LMConfig : Config
  {
    double LambdaInit     = 1.0e-3;
    double LambdaIncrease = 10.0;
    double LambdaDecrease = 0.1;
    double LambdaMax      = 1.0e10;
    double LambdaMin      = 1.0e-12;

    LMConfig() = default;

    explicit LMConfig(double theTolerance, int theMaxIter = 100)
        : Config(theTolerance, theMaxIter)
    {
    }
  };

  template <typename FuncSetType>
  VectorResult LevenbergMarquardt(FuncSetType&       theFunc,
                                  const math_Vector& theStart,
                                  const LMConfig&    theConfig = LMConfig())
  {
    VectorResult aResult;

    const int aNbVars = theFunc.NbVariables();
    const int aNbEqs  = theFunc.NbEquations();

    if (theStart.Length() != aNbVars)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const int aVarLower = theStart.Lower();
    const int aVarUpper = theStart.Upper();

    math_Vector aSol = theStart;
    math_Vector aF(1, aNbEqs);
    math_Vector aFNew(1, aNbEqs);
    math_Vector aDeltaX(aVarLower, aVarUpper);
    math_Vector aGrad(aVarLower, aVarUpper);
    math_Matrix aJac(1, aNbEqs, aVarLower, aVarUpper);
    math_Matrix aJtJ(aVarLower, aVarUpper, aVarLower, aVarUpper);
    math_Vector aJtF(aVarLower, aVarUpper);

    double aLambda = theConfig.LambdaInit;

    if (!theFunc.Value(aSol, aF))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    double aChi2 = 0.0;
    for (int i = 1; i <= aNbEqs; ++i)
    {
      aChi2 += aF(i) * aF(i);
    }

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      bool aFConverged = true;
      for (int i = 1; i <= aNbEqs; ++i)
      {
        if (std::abs(aF(i)) > theConfig.FTolerance)
        {
          aFConverged = false;
          break;
        }
      }

      if (aFConverged)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aSol;
        aResult.Value    = aChi2;
        return aResult;
      }

      if (!theFunc.Derivatives(aSol, aJac))
      {
        aResult.Status = Status::NumericalError;
        return aResult;
      }

      for (int i = aVarLower; i <= aVarUpper; ++i)
      {
        for (int j = aVarLower; j <= aVarUpper; ++j)
        {
          double aSum = 0.0;
          for (int k = 1; k <= aNbEqs; ++k)
          {
            aSum += aJac(k, i) * aJac(k, j);
          }
          aJtJ(i, j) = aSum;
        }
      }

      for (int i = aVarLower; i <= aVarUpper; ++i)
      {
        double aSum = 0.0;
        for (int k = 1; k <= aNbEqs; ++k)
        {
          aSum += aJac(k, i) * aF(k);
        }
        aJtF(i)  = aSum;
        aGrad(i) = 2.0 * aSum;
      }

      double aGradNorm = 0.0;
      for (int i = aVarLower; i <= aVarUpper; ++i)
      {
        aGradNorm += aGrad(i) * aGrad(i);
      }
      aGradNorm = std::sqrt(aGradNorm);

      if (aGradNorm < theConfig.Tolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aSol;
        aResult.Value    = aChi2;
        aResult.Gradient = aGrad;
        return aResult;
      }

      bool aStepAccepted = false;
      for (int aLamIter = 0; aLamIter < 20 && !aStepAccepted; ++aLamIter)
      {

        math_Matrix aDamped = aJtJ;
        for (int i = aVarLower; i <= aVarUpper; ++i)
        {
          aDamped(i, i) += aLambda;
        }

        math_Vector aNegJtF(aVarLower, aVarUpper);
        for (int i = aVarLower; i <= aVarUpper; ++i)
        {
          aNegJtF(i) = -aJtF(i);
        }

        auto aLinResult = MathLin::Solve(aDamped, aNegJtF);
        if (!aLinResult.IsDone())
        {

          aLambda *= theConfig.LambdaIncrease;
          if (aLambda > theConfig.LambdaMax)
          {
            aResult.Status   = Status::Singular;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
          continue;
        }

        aDeltaX = *aLinResult.Solution;

        math_Vector aSolNew(aVarLower, aVarUpper);
        for (int i = aVarLower; i <= aVarUpper; ++i)
        {
          aSolNew(i) = aSol(i) + aDeltaX(i);
        }

        if (!theFunc.Value(aSolNew, aFNew))
        {

          aLambda *= theConfig.LambdaIncrease;
          if (aLambda > theConfig.LambdaMax)
          {
            aResult.Status   = Status::NumericalError;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
          continue;
        }

        double aChi2New = 0.0;
        for (int i = 1; i <= aNbEqs; ++i)
        {
          aChi2New += aFNew(i) * aFNew(i);
        }

        if (aChi2New < aChi2)
        {

          aSol  = aSolNew;
          aF    = aFNew;
          aChi2 = aChi2New;
          aLambda *= theConfig.LambdaDecrease;
          if (aLambda < theConfig.LambdaMin)
          {
            aLambda = theConfig.LambdaMin;
          }
          aStepAccepted = true;

          bool aXConverged = true;
          for (int i = aVarLower; i <= aVarUpper; ++i)
          {
            if (std::abs(aDeltaX(i)) > theConfig.XTolerance * (1.0 + std::abs(aSol(i))))
            {
              aXConverged = false;
              break;
            }
          }

          if (aXConverged)
          {
            aResult.Status   = Status::OK;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
        }
        else
        {

          aLambda *= theConfig.LambdaIncrease;
          if (aLambda > theConfig.LambdaMax)
          {
            aResult.Status   = Status::NotConverged;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
        }
      }

      if (!aStepAccepted)
      {

        aResult.Status   = Status::NotConverged;
        aResult.Solution = aSol;
        aResult.Value    = aChi2;
        return aResult;
      }
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aSol;
    aResult.Value    = aChi2;
    return aResult;
  }

  template <typename FuncSetType>
  VectorResult LevenbergMarquardtBounded(FuncSetType&       theFunc,
                                         const math_Vector& theStart,
                                         const math_Vector& theInfBound,
                                         const math_Vector& theSupBound,
                                         const LMConfig&    theConfig = LMConfig())
  {
    VectorResult aResult;

    const int aNbVars = theFunc.NbVariables();
    const int aNbEqs  = theFunc.NbEquations();

    if (theStart.Length() != aNbVars || theInfBound.Length() != aNbVars
        || theSupBound.Length() != aNbVars)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const int aVarLower = theStart.Lower();
    const int aVarUpper = theStart.Upper();

    math_Vector aSol = theStart;
    math_Vector aF(1, aNbEqs);
    math_Vector aFNew(1, aNbEqs);
    math_Vector aDeltaX(aVarLower, aVarUpper);
    math_Vector aGrad(aVarLower, aVarUpper);
    math_Matrix aJac(1, aNbEqs, aVarLower, aVarUpper);
    math_Matrix aJtJ(aVarLower, aVarUpper, aVarLower, aVarUpper);
    math_Vector aJtF(aVarLower, aVarUpper);

    for (int i = aVarLower; i <= aVarUpper; ++i)
    {
      aSol(i) = MathUtils::Clamp(aSol(i), theInfBound(i), theSupBound(i));
    }

    double aLambda = theConfig.LambdaInit;

    if (!theFunc.Value(aSol, aF))
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    double aChi2 = 0.0;
    for (int i = 1; i <= aNbEqs; ++i)
    {
      aChi2 += aF(i) * aF(i);
    }

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      bool aFConverged = true;
      for (int i = 1; i <= aNbEqs; ++i)
      {
        if (std::abs(aF(i)) > theConfig.FTolerance)
        {
          aFConverged = false;
          break;
        }
      }

      if (aFConverged)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aSol;
        aResult.Value    = aChi2;
        return aResult;
      }

      if (!theFunc.Derivatives(aSol, aJac))
      {
        aResult.Status = Status::NumericalError;
        return aResult;
      }

      for (int i = aVarLower; i <= aVarUpper; ++i)
      {
        for (int j = aVarLower; j <= aVarUpper; ++j)
        {
          double aSum = 0.0;
          for (int k = 1; k <= aNbEqs; ++k)
          {
            aSum += aJac(k, i) * aJac(k, j);
          }
          aJtJ(i, j) = aSum;
        }
      }

      for (int i = aVarLower; i <= aVarUpper; ++i)
      {
        double aSum = 0.0;
        for (int k = 1; k <= aNbEqs; ++k)
        {
          aSum += aJac(k, i) * aF(k);
        }
        aJtF(i)  = aSum;
        aGrad(i) = 2.0 * aSum;
      }

      double aGradNorm = 0.0;
      for (int i = aVarLower; i <= aVarUpper; ++i)
      {
        aGradNorm += aGrad(i) * aGrad(i);
      }
      aGradNorm = std::sqrt(aGradNorm);

      if (aGradNorm < theConfig.Tolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aSol;
        aResult.Value    = aChi2;
        aResult.Gradient = aGrad;
        return aResult;
      }

      bool aStepAccepted = false;
      for (int aLamIter = 0; aLamIter < 20 && !aStepAccepted; ++aLamIter)
      {

        math_Matrix aDamped = aJtJ;
        for (int i = aVarLower; i <= aVarUpper; ++i)
        {
          aDamped(i, i) += aLambda;
        }

        math_Vector aNegJtF(aVarLower, aVarUpper);
        for (int i = aVarLower; i <= aVarUpper; ++i)
        {
          aNegJtF(i) = -aJtF(i);
        }

        auto aLinResult = MathLin::Solve(aDamped, aNegJtF);
        if (!aLinResult.IsDone())
        {
          aLambda *= theConfig.LambdaIncrease;
          if (aLambda > theConfig.LambdaMax)
          {
            aResult.Status   = Status::Singular;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
          continue;
        }

        aDeltaX = *aLinResult.Solution;

        math_Vector aSolNew(aVarLower, aVarUpper);
        for (int i = aVarLower; i <= aVarUpper; ++i)
        {
          aSolNew(i) = MathUtils::Clamp(aSol(i) + aDeltaX(i), theInfBound(i), theSupBound(i));
        }

        if (!theFunc.Value(aSolNew, aFNew))
        {
          aLambda *= theConfig.LambdaIncrease;
          if (aLambda > theConfig.LambdaMax)
          {
            aResult.Status   = Status::NumericalError;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
          continue;
        }

        double aChi2New = 0.0;
        for (int i = 1; i <= aNbEqs; ++i)
        {
          aChi2New += aFNew(i) * aFNew(i);
        }

        if (aChi2New < aChi2)
        {
          aSol  = aSolNew;
          aF    = aFNew;
          aChi2 = aChi2New;
          aLambda *= theConfig.LambdaDecrease;
          if (aLambda < theConfig.LambdaMin)
          {
            aLambda = theConfig.LambdaMin;
          }
          aStepAccepted = true;

          bool aXConverged = true;
          for (int i = aVarLower; i <= aVarUpper; ++i)
          {
            if (std::abs(aDeltaX(i)) > theConfig.XTolerance * (1.0 + std::abs(aSol(i))))
            {
              aXConverged = false;
              break;
            }
          }

          if (aXConverged)
          {
            aResult.Status   = Status::OK;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
        }
        else
        {
          aLambda *= theConfig.LambdaIncrease;
          if (aLambda > theConfig.LambdaMax)
          {
            aResult.Status   = Status::NotConverged;
            aResult.Solution = aSol;
            aResult.Value    = aChi2;
            return aResult;
          }
        }
      }

      if (!aStepAccepted)
      {
        aResult.Status   = Status::NotConverged;
        aResult.Solution = aSol;
        aResult.Value    = aChi2;
        return aResult;
      }
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aSol;
    aResult.Value    = aChi2;
    return aResult;
  }

} // namespace MathSys
