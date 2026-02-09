#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathLin_Gauss.hpp>
#include <math_FunctionSetWithDerivatives.hpp>

#include <cmath>

namespace MathSys
{
  using namespace MathUtils;

  template <typename FuncSetType>
  VectorResult Newton(FuncSetType&       theFunc,
                      const math_Vector& theStart,
                      const math_Vector& theTolX,
                      double             theTolF,
                      size_t             theMaxIter = 100)
  {
    VectorResult aResult;

    const int aN = theFunc.NbVariables();
    const int aM = theFunc.NbEquations();

    if (aN != aM || theStart.Length() != aN || theTolX.Length() != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const int aLower = theStart.Lower();
    const int aUpper = theStart.Upper();

    math_Vector aSol = theStart;
    math_Vector aF(aLower, aUpper);
    math_Vector aDeltaX(aLower, aUpper);
    math_Matrix aJacobian(aLower, aUpper, aLower, aUpper);

    for (size_t anIter = 0; anIter < theMaxIter; ++anIter)
    {

      if (!theFunc.Values(aSol, aF, aJacobian))
      {
        aResult.Status       = Status::NumericalError;
        aResult.NbIterations = anIter;
        return aResult;
      }

      math_Vector aNegF(aLower, aUpper);
      for (int i = aLower; i <= aUpper; ++i)
      {
        aNegF(i) = -aF(i);
      }

      auto aLinResult = MathLin::Solve(aJacobian, aNegF);
      if (!aLinResult.IsDone())
      {
        aResult.Status       = Status::Singular;
        aResult.NbIterations = anIter;
        return aResult;
      }

      aDeltaX = *aLinResult.Solution;

      bool aXConverged = true;
      for (int i = aLower; i <= aUpper; ++i)
      {
        if (std::abs(aDeltaX(i)) > theTolX(i))
        {
          aXConverged = false;
          break;
        }
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aSol(i) += aDeltaX(i);
      }

      if (!theFunc.Value(aSol, aF))
      {
        aResult.Status       = Status::NumericalError;
        aResult.NbIterations = anIter + 1;
        return aResult;
      }

      bool aFConverged = true;
      for (int i = aLower; i <= aUpper; ++i)
      {
        if (std::abs(aF(i)) > theTolF)
        {
          aFConverged = false;
          break;
        }
      }

      if (aXConverged && aFConverged)
      {
        aResult.Status       = Status::OK;
        aResult.NbIterations = anIter + 1;
        aResult.Solution     = aSol;
        aResult.Jacobian     = aJacobian;
        return aResult;
      }

      aResult.NbIterations = anIter + 1;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aSol;
    aResult.Jacobian = aJacobian;
    return aResult;
  }

  template <typename FuncSetType>
  VectorResult NewtonBounded(FuncSetType&       theFunc,
                             const math_Vector& theStart,
                             const math_Vector& theInfBound,
                             const math_Vector& theSupBound,
                             const math_Vector& theTolX,
                             double             theTolF,
                             size_t             theMaxIter = 100)
  {
    VectorResult aResult;

    const int aN = theFunc.NbVariables();
    const int aM = theFunc.NbEquations();

    if (aN != aM || theStart.Length() != aN || theTolX.Length() != aN || theInfBound.Length() != aN
        || theSupBound.Length() != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const int aLower = theStart.Lower();
    const int aUpper = theStart.Upper();

    math_Vector aSol = theStart;
    math_Vector aF(aLower, aUpper);
    math_Vector aDeltaX(aLower, aUpper);
    math_Matrix aJacobian(aLower, aUpper, aLower, aUpper);

    for (int i = aLower; i <= aUpper; ++i)
    {
      if (aSol(i) < theInfBound(i))
      {
        aSol(i) = theInfBound(i);
      }
      if (aSol(i) > theSupBound(i))
      {
        aSol(i) = theSupBound(i);
      }
    }

    for (size_t anIter = 0; anIter < theMaxIter; ++anIter)
    {

      if (!theFunc.Values(aSol, aF, aJacobian))
      {
        aResult.Status       = Status::NumericalError;
        aResult.NbIterations = anIter;
        return aResult;
      }

      math_Vector aNegF(aLower, aUpper);
      for (int i = aLower; i <= aUpper; ++i)
      {
        aNegF(i) = -aF(i);
      }

      auto aLinResult = MathLin::Solve(aJacobian, aNegF);
      if (!aLinResult.IsDone())
      {
        aResult.Status       = Status::Singular;
        aResult.NbIterations = anIter;
        return aResult;
      }

      aDeltaX = *aLinResult.Solution;

      bool aXConverged = true;
      for (int i = aLower; i <= aUpper; ++i)
      {
        if (std::abs(aDeltaX(i)) > theTolX(i))
        {
          aXConverged = false;
          break;
        }
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aSol(i) += aDeltaX(i);
        if (aSol(i) < theInfBound(i))
        {
          aSol(i) = theInfBound(i);
        }
        if (aSol(i) > theSupBound(i))
        {
          aSol(i) = theSupBound(i);
        }
      }

      if (!theFunc.Value(aSol, aF))
      {
        aResult.Status       = Status::NumericalError;
        aResult.NbIterations = anIter + 1;
        return aResult;
      }

      bool aFConverged = true;
      for (int i = aLower; i <= aUpper; ++i)
      {
        if (std::abs(aF(i)) > theTolF)
        {
          aFConverged = false;
          break;
        }
      }

      if (aXConverged && aFConverged)
      {
        aResult.Status       = Status::OK;
        aResult.NbIterations = anIter + 1;
        aResult.Solution     = aSol;
        aResult.Jacobian     = aJacobian;
        return aResult;
      }

      aResult.NbIterations = anIter + 1;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aSol;
    aResult.Jacobian = aJacobian;
    return aResult;
  }

  template <typename FuncSetType>
  VectorResult Newton(FuncSetType&       theFunc,
                      const math_Vector& theStart,
                      double             theTolX,
                      double             theTolF,
                      size_t             theMaxIter = 100)
  {
    math_Vector aTolXVec(theStart.Lower(), theStart.Upper(), theTolX);
    return Newton(theFunc, theStart, aTolXVec, theTolF, theMaxIter);
  }

} // namespace MathSys
