#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <MathUtils_LineSearch.hpp>
#include <MathUtils_Deriv.hpp>

#include <NCollection_Vector.hpp>

#include <cmath>

namespace MathOpt
{
  using namespace MathUtils;

  template <typename Function>
  VectorResult BFGS(Function&          theFunc,
                    const math_Vector& theStartingPoint,
                    const Config&      theConfig = Config())
  {
    VectorResult aResult;

    const int aLower = theStartingPoint.Lower();
    const int aUpper = theStartingPoint.Upper();
    const int aN     = aUpper - aLower + 1;

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

    math_Matrix aH(1, aN, 1, aN, 0.0);
    for (int i = 1; i <= aN; ++i)
    {
      aH(i, i) = 1.0;
    }

    math_Vector aDir(aLower, aUpper);
    math_Vector aXNew(aLower, aUpper);
    math_Vector aGradNew(aLower, aUpper);
    math_Vector aS(1, aN);
    math_Vector aY(1, aN);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      for (int i = 1; i <= aN; ++i)
      {
        double aSum = 0.0;
        for (int j = 1; j <= aN; ++j)
        {
          aSum += aH(i, j) * aGrad(aLower + j - 1);
        }
        aDir(aLower + i - 1) = -aSum;
      }

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

        for (int i = 1; i <= aN; ++i)
        {
          for (int j = 1; j <= aN; ++j)
          {
            aH(i, j) = (i == j) ? 1.0 : 0.0;
          }
        }
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aXNew(i) = aX(i) + aLineResult.Alpha * aDir(i);
      }

      for (int i = 1; i <= aN; ++i)
      {
        aS(i) = aXNew(aLower + i - 1) - aX(aLower + i - 1);
      }

      if (!theFunc.Gradient(aXNew, aGradNew))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aX;
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
        aResult.Value    = aLineResult.FNew;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      double aMaxDiff = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aXNew(i) - aX(i)));
      }
      if (aMaxDiff < theConfig.XTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aLineResult.FNew;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      for (int i = 1; i <= aN; ++i)
      {
        aY(i) = aGradNew(aLower + i - 1) - aGrad(aLower + i - 1);
      }

      double aSY = 0.0;
      for (int i = 1; i <= aN; ++i)
      {
        aSY += aS(i) * aY(i);
      }

      if (aSY > MathUtils::THE_ZERO_TOL)
      {

        const double aRho = 1.0 / aSY;

        math_Vector aHy(1, aN, 0.0);
        for (int i = 1; i <= aN; ++i)
        {
          for (int j = 1; j <= aN; ++j)
          {
            aHy(i) += aH(i, j) * aY(j);
          }
        }

        double aYHy = 0.0;
        for (int i = 1; i <= aN; ++i)
        {
          aYHy += aY(i) * aHy(i);
        }

        const double aFactor = 1.0 + aRho * aYHy;

        for (int i = 1; i <= aN; ++i)
        {
          for (int j = 1; j <= aN; ++j)
          {
            aH(i, j) =
              aH(i, j) - aRho * (aHy(i) * aS(j) + aS(i) * aHy(j)) + aFactor * aRho * aS(i) * aS(j);
          }
        }
      }

      aX    = aXNew;
      aGrad = aGradNew;
      aFx   = aLineResult.FNew;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    aResult.Gradient = aGrad;
    return aResult;
  }

  template <typename Function>
  VectorResult BFGSNumerical(Function&          theFunc,
                             const math_Vector& theStartingPoint,
                             double             theGradStep = 1.0e-8,
                             const Config&      theConfig   = Config())
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
    return BFGS(aWrapper, theStartingPoint, theConfig);
  }

  template <typename Function>
  VectorResult LBFGS(Function&          theFunc,
                     const math_Vector& theStartingPoint,
                     int                theMemorySize = 10,
                     const Config&      theConfig     = Config())
  {
    VectorResult aResult;

    const int aLower = theStartingPoint.Lower();
    const int aUpper = theStartingPoint.Upper();
    const int aN     = aUpper - aLower + 1;
    const int aM     = theMemorySize;

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

    NCollection_Vector<math_Vector> aSVec;
    NCollection_Vector<math_Vector> aYVec;
    math_Vector                     aRhoVec(0, aM - 1, 0.0);
    for (int i = 0; i < aM; ++i)
    {
      aSVec.Append(math_Vector(1, aN));
      aYVec.Append(math_Vector(1, aN));
    }
    int aHead  = 0;
    int aCount = 0;

    math_Vector aDir(aLower, aUpper);
    math_Vector aXNew(aLower, aUpper);
    math_Vector aGradNew(aLower, aUpper);
    math_Vector aQ(1, aN);
    math_Vector aAlphaVec(0, aM - 1);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      double aGradNorm = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aGradNorm += MathUtils::Sqr(aGrad(i));
      }
      if (std::sqrt(aGradNorm) < theConfig.FTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        aResult.Gradient = aGrad;
        return aResult;
      }

      for (int i = 1; i <= aN; ++i)
      {
        aQ(i) = aGrad(aLower + i - 1);
      }

      for (int k = aCount - 1; k >= 0; --k)
      {
        const int aIdx  = (aHead + k) % aM;
        aAlphaVec(aIdx) = aRhoVec(aIdx) * MathUtils::DotProduct(aSVec.Value(aIdx), aQ);
        for (int i = 1; i <= aN; ++i)
        {
          aQ(i) -= aAlphaVec(aIdx) * aYVec.Value(aIdx)(i);
        }
      }

      double aGamma = 1.0;
      if (aCount > 0)
      {
        const int aLastIdx = (aHead + aCount - 1) % aM;
        double    aYY      = MathUtils::DotProduct(aYVec.Value(aLastIdx), aYVec.Value(aLastIdx));
        if (aYY > MathUtils::THE_ZERO_TOL)
        {
          aGamma = 1.0 / (aRhoVec(aLastIdx) * aYY);
        }
      }

      math_Vector aR(1, aN);
      for (int i = 1; i <= aN; ++i)
      {
        aR(i) = aGamma * aQ(i);
      }

      for (int k = 0; k < aCount; ++k)
      {
        const int    aIdx  = (aHead + k) % aM;
        const double aBeta = aRhoVec(aIdx) * MathUtils::DotProduct(aYVec.Value(aIdx), aR);
        for (int i = 1; i <= aN; ++i)
        {
          aR(i) += (aAlphaVec(aIdx) - aBeta) * aSVec.Value(aIdx)(i);
        }
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aDir(i) = -aR(i - aLower + 1);
      }

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
          return aResult;
        }

        aCount = 0;
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
      if (aMaxDiff < theConfig.XTolerance)
      {
        if (!theFunc.Gradient(aXNew, aGradNew))
        {
          aGradNew = aGrad;
        }
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aLineResult.FNew;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      if (!theFunc.Gradient(aXNew, aGradNew))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }

      const int aNewIdx = (aHead + aCount) % aM;
      for (int i = 1; i <= aN; ++i)
      {
        aSVec.ChangeValue(aNewIdx)(i) = aXNew(aLower + i - 1) - aX(aLower + i - 1);
        aYVec.ChangeValue(aNewIdx)(i) = aGradNew(aLower + i - 1) - aGrad(aLower + i - 1);
      }

      double aSY = MathUtils::DotProduct(aSVec.Value(aNewIdx), aYVec.Value(aNewIdx));
      if (aSY > MathUtils::THE_ZERO_TOL)
      {
        aRhoVec(aNewIdx) = 1.0 / aSY;
        if (aCount < aM)
        {
          ++aCount;
        }
        else
        {
          aHead = (aHead + 1) % aM;
        }
      }

      aX    = aXNew;
      aGrad = aGradNew;
      aFx   = aLineResult.FNew;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    aResult.Gradient = aGrad;
    return aResult;
  }

  template <typename Function>
  VectorResult BFGSBounded(Function&          theFunc,
                           const math_Vector& theStartingPoint,
                           const math_Vector& theLowerBounds,
                           const math_Vector& theUpperBounds,
                           const Config&      theConfig = Config())
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

    math_Matrix aH(1, aN, 1, aN, 0.0);
    for (int i = 1; i <= aN; ++i)
    {
      aH(i, i) = 1.0;
    }

    math_Vector aDir(aLower, aUpper);
    math_Vector aXNew(aLower, aUpper);
    math_Vector aGradNew(aLower, aUpper);
    math_Vector aS(1, aN);
    math_Vector aY(1, aN);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      for (int i = 1; i <= aN; ++i)
      {
        double aSum = 0.0;
        for (int j = 1; j <= aN; ++j)
        {
          aSum += aH(i, j) * aGrad(aLower + j - 1);
        }
        aDir(aLower + i - 1) = -aSum;
      }

      double aAlphaMax = 1.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        const int aBndIdx = theLowerBounds.Lower() + (i - aLower);
        if (aDir(i) < -MathUtils::THE_EPSILON)
        {

          double aMaxStep = (theLowerBounds(aBndIdx) - aX(i)) / aDir(i);
          aAlphaMax       = std::min(aAlphaMax, aMaxStep);
        }
        else if (aDir(i) > MathUtils::THE_EPSILON)
        {

          double aMaxStep = (theUpperBounds(aBndIdx) - aX(i)) / aDir(i);
          aAlphaMax       = std::min(aAlphaMax, aMaxStep);
        }
      }
      aAlphaMax = std::max(aAlphaMax, MathUtils::THE_EPSILON);

      MathUtils::LineSearchResult aLineResult =
        MathUtils::ArmijoBacktrack(theFunc, aX, aDir, aGrad, aFx, aAlphaMax, 1.0e-4, 0.5, 50);

      if (!aLineResult.IsValid || aLineResult.Alpha < MathUtils::THE_EPSILON)
      {

        for (int i = aLower; i <= aUpper; ++i)
        {
          aDir(i) = -aGrad(i);
        }

        aAlphaMax = 1.0;
        for (int i = aLower; i <= aUpper; ++i)
        {
          const int aBndIdx = theLowerBounds.Lower() + (i - aLower);
          if (aDir(i) < -MathUtils::THE_EPSILON)
          {
            aAlphaMax = std::min(aAlphaMax, (theLowerBounds(aBndIdx) - aX(i)) / aDir(i));
          }
          else if (aDir(i) > MathUtils::THE_EPSILON)
          {
            aAlphaMax = std::min(aAlphaMax, (theUpperBounds(aBndIdx) - aX(i)) / aDir(i));
          }
        }
        aAlphaMax = std::max(aAlphaMax, MathUtils::THE_EPSILON);

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

        for (int i = 1; i <= aN; ++i)
        {
          for (int j = 1; j <= aN; ++j)
          {
            aH(i, j) = (i == j) ? 1.0 : 0.0;
          }
        }
      }

      for (int i = aLower; i <= aUpper; ++i)
      {
        aXNew(i) = aX(i) + aLineResult.Alpha * aDir(i);
      }
      ClampToBounds(aXNew);

      for (int i = 1; i <= aN; ++i)
      {
        aS(i) = aXNew(aLower + i - 1) - aX(aLower + i - 1);
      }

      double aFxNew = 0.0;
      if (!theFunc.Value(aXNew, aFxNew))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aX;
        aResult.Value    = aFx;
        return aResult;
      }

      if (!theFunc.Gradient(aXNew, aGradNew))
      {
        aResult.Status   = Status::NumericalError;
        aResult.Solution = aX;
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
        aResult.Value    = aFxNew;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      double aMaxDiff = 0.0;
      for (int i = aLower; i <= aUpper; ++i)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aXNew(i) - aX(i)));
      }
      if (aMaxDiff < theConfig.XTolerance)
      {
        aResult.Status   = Status::OK;
        aResult.Solution = aXNew;
        aResult.Value    = aFxNew;
        aResult.Gradient = aGradNew;
        return aResult;
      }

      for (int i = 1; i <= aN; ++i)
      {
        aY(i) = aGradNew(aLower + i - 1) - aGrad(aLower + i - 1);
      }

      double aSY = 0.0;
      for (int i = 1; i <= aN; ++i)
      {
        aSY += aS(i) * aY(i);
      }

      if (aSY > MathUtils::THE_ZERO_TOL)
      {
        const double aRho = 1.0 / aSY;

        math_Vector aHy(1, aN, 0.0);
        for (int i = 1; i <= aN; ++i)
        {
          for (int j = 1; j <= aN; ++j)
          {
            aHy(i) += aH(i, j) * aY(j);
          }
        }

        double aYHy = 0.0;
        for (int i = 1; i <= aN; ++i)
        {
          aYHy += aY(i) * aHy(i);
        }

        const double aFactor = 1.0 + aRho * aYHy;
        for (int i = 1; i <= aN; ++i)
        {
          for (int j = 1; j <= aN; ++j)
          {
            aH(i, j) =
              aH(i, j) - aRho * (aHy(i) * aS(j) + aS(i) * aHy(j)) + aFactor * aRho * aS(i) * aS(j);
          }
        }
      }

      aX    = aXNew;
      aGrad = aGradNew;
      aFx   = aFxNew;
    }

    aResult.Status   = Status::MaxIterations;
    aResult.Solution = aX;
    aResult.Value    = aFx;
    aResult.Gradient = aGrad;
    return aResult;
  }

} // namespace MathOpt
