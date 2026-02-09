#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <MathRoot_Brent.hpp>
#include <math_Vector.hpp>
#include <math_IntegerVector.hpp>

#include <NCollection_Vector.hpp>

#include <cmath>

namespace MathRoot
{
  using namespace MathUtils;

  struct MultipleResult
  {
    MathUtils::Status          Status       = MathUtils::Status::NotConverged;
    size_t                     NbIterations = 0;
    NCollection_Vector<double> Roots;
    NCollection_Vector<double> Values;
    bool                       IsAllNull = false;

    bool IsDone() const { return Status == MathUtils::Status::OK; }

    explicit operator bool() const { return IsDone(); }

    int NbRoots() const { return Roots.Length(); }

    double operator[](int theIndex) const { return Roots.Value(theIndex); }
  };

  struct MultipleConfig
  {
    int    NbSamples     = 100;
    double XTolerance    = 1e-10;
    double FTolerance    = 1e-10;
    double NullTolerance = 1e-12;
    int    MaxIterations = 100;
    double Offset        = 0.0;
  };

  template <typename Function>
  MultipleResult FindAllRoots(Function&             theFunc,
                              double                theLower,
                              double                theUpper,
                              const MultipleConfig& theConfig = MultipleConfig())
  {
    MultipleResult aResult;
    aResult.Status = MathUtils::Status::OK;

    double aLower = std::min(theLower, theUpper);
    double aUpper = std::max(theLower, theUpper);

    const int    aNbSamples = std::max(theConfig.NbSamples, 10);
    const double aDx        = (aUpper - aLower) / aNbSamples;

    const double aMinEpsX = 1e-10 * (std::abs(aLower) + std::abs(aUpper));
    const double aEpsX    = std::max(theConfig.XTolerance, aMinEpsX);

    math_Vector aSamples(0, aNbSamples);
    math_Vector aXValues(0, aNbSamples);

    bool aAllValid = true;
    for (int i = 0; i <= aNbSamples; ++i)
    {
      double aX = aLower + i * aDx;
      if (aX > aUpper)
        aX = aUpper;
      aXValues(i) = aX;

      double aF = 0.0;
      if (!theFunc.Value(aX, aF))
      {
        aAllValid = false;
        break;
      }
      aSamples(i) = aF - theConfig.Offset;
    }

    if (!aAllValid)
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }

    aResult.IsAllNull = true;
    for (int i = 0; i <= aNbSamples; ++i)
    {
      if (std::abs(aSamples(i)) > theConfig.NullTolerance)
      {
        aResult.IsAllNull = false;
        break;
      }
    }

    if (aResult.IsAllNull)
    {
      return aResult;
    }

    auto addRoot = [&](double theRoot, double theValue)
    {
      for (int k = 0; k < aResult.Roots.Length(); ++k)
      {
        if (std::abs(theRoot - aResult.Roots.Value(k)) < aEpsX)
        {
          return;
        }
      }
      aResult.Roots.Append(theRoot);
      aResult.Values.Append(theValue);
    };

    class BrentWrapper
    {
    public:
      BrentWrapper(Function& theF, double theOffset)
          : myFunc(theF),
            myOffset(theOffset)
      {
      }

      bool Value(double theX, double& theY) const
      {
        if (!myFunc.Value(theX, theY))
          return false;
        theY -= myOffset;
        return true;
      }

    private:
      Function& myFunc;
      double    myOffset;
    };

    BrentWrapper aWrapper(theFunc, theConfig.Offset);

    for (int i = 0; i < aNbSamples; ++i)
    {
      const double aF0 = aSamples(i);
      const double aF1 = aSamples(i + 1);
      const double aX0 = aXValues(i);
      const double aX1 = aXValues(i + 1);

      if (std::abs(aF0) < theConfig.FTolerance)
      {
        addRoot(aX0, aF0 + theConfig.Offset);
        continue;
      }

      if (aF0 * aF1 < 0.0)
      {
        MathUtils::Config aBrentConfig;
        aBrentConfig.XTolerance    = aEpsX;
        aBrentConfig.FTolerance    = theConfig.FTolerance;
        aBrentConfig.MaxIterations = theConfig.MaxIterations;

        auto aBrentResult = Brent(aWrapper, aX0, aX1, aBrentConfig);
        aResult.NbIterations += aBrentResult.NbIterations;

        if (aBrentResult.IsDone() && aBrentResult.Root.has_value())
        {
          double aRootValue = 0.0;
          theFunc.Value(*aBrentResult.Root, aRootValue);
          addRoot(*aBrentResult.Root, aRootValue);
        }
      }
    }

    if (std::abs(aSamples(aNbSamples)) < theConfig.FTolerance)
    {
      addRoot(aXValues(aNbSamples), aSamples(aNbSamples) + theConfig.Offset);
    }

    const int aNbRoots = aResult.Roots.Length();
    if (aNbRoots > 1)
    {
      math_IntegerVector aIndices(0, aNbRoots - 1);
      for (int i = 0; i < aNbRoots; ++i)
      {
        aIndices(i) = i;
      }

      for (int i = 1; i < aNbRoots; ++i)
      {
        int aKey = aIndices(i);
        int j    = i - 1;
        while (j >= 0 && aResult.Roots.Value(aIndices(j)) > aResult.Roots.Value(aKey))
        {
          aIndices(j + 1) = aIndices(j);
          --j;
        }
        aIndices(j + 1) = aKey;
      }

      NCollection_Vector<double> aSortedRoots, aSortedValues;
      for (int i = 0; i < aNbRoots; ++i)
      {
        aSortedRoots.Append(aResult.Roots.Value(aIndices(i)));
        aSortedValues.Append(aResult.Values.Value(aIndices(i)));
      }
      aResult.Roots  = aSortedRoots;
      aResult.Values = aSortedValues;
    }

    return aResult;
  }

  template <typename Function>
  MultipleResult FindAllRootsWithDerivative(Function&             theFunc,
                                            double                theLower,
                                            double                theUpper,
                                            const MultipleConfig& theConfig = MultipleConfig())
  {
    MultipleResult aResult;
    aResult.Status = MathUtils::Status::OK;

    double aLower = std::min(theLower, theUpper);
    double aUpper = std::max(theLower, theUpper);

    const int    aNbSamples = std::max(theConfig.NbSamples, 10);
    const double aDx        = (aUpper - aLower) / aNbSamples;

    const double aMinEpsX = 1e-10 * (std::abs(aLower) + std::abs(aUpper));
    const double aEpsX    = std::max(theConfig.XTolerance, aMinEpsX);

    math_Vector aFValues(0, aNbSamples);
    math_Vector aDFValues(0, aNbSamples);
    math_Vector aXValues(0, aNbSamples);

    bool aAllValid = true;
    for (int i = 0; i <= aNbSamples; ++i)
    {
      double aX = aLower + i * aDx;
      if (aX > aUpper)
        aX = aUpper;
      aXValues(i) = aX;

      double aF = 0.0, aDF = 0.0;
      if (!theFunc.Values(aX, aF, aDF))
      {
        aAllValid = false;
        break;
      }
      aFValues(i)  = aF - theConfig.Offset;
      aDFValues(i) = aDF;
    }

    if (!aAllValid)
    {
      aResult.Status = MathUtils::Status::NumericalError;
      return aResult;
    }

    aResult.IsAllNull = true;
    for (int i = 0; i <= aNbSamples; ++i)
    {
      if (std::abs(aFValues(i)) > theConfig.NullTolerance)
      {
        aResult.IsAllNull = false;
        break;
      }
    }

    if (aResult.IsAllNull)
    {
      return aResult;
    }

    auto addRoot = [&](double theRoot, double theValue)
    {
      for (int k = 0; k < aResult.Roots.Length(); ++k)
      {
        if (std::abs(theRoot - aResult.Roots.Value(k)) < aEpsX)
        {
          return;
        }
      }
      aResult.Roots.Append(theRoot);
      aResult.Values.Append(theValue);
    };

    class BrentWrapper
    {
    public:
      BrentWrapper(Function& theF, double theOffset)
          : myFunc(theF),
            myOffset(theOffset)
      {
      }

      bool Value(double theX, double& theY) const
      {
        double aDF = 0.0;
        if (!myFunc.Values(theX, theY, aDF))
          return false;
        theY -= myOffset;
        return true;
      }

    private:
      Function& myFunc;
      double    myOffset;
    };

    BrentWrapper aWrapper(theFunc, theConfig.Offset);

    for (int i = 0; i < aNbSamples; ++i)
    {
      const double aF0 = aFValues(i);
      const double aF1 = aFValues(i + 1);
      const double aX0 = aXValues(i);
      const double aX1 = aXValues(i + 1);

      if (std::abs(aF0) < theConfig.FTolerance)
      {
        addRoot(aX0, aF0 + theConfig.Offset);
        continue;
      }

      if (aF0 * aF1 < 0.0)
      {
        MathUtils::Config aBrentConfig;
        aBrentConfig.XTolerance    = aEpsX;
        aBrentConfig.FTolerance    = theConfig.FTolerance;
        aBrentConfig.MaxIterations = theConfig.MaxIterations;

        auto aBrentResult = Brent(aWrapper, aX0, aX1, aBrentConfig);
        aResult.NbIterations += aBrentResult.NbIterations;

        if (aBrentResult.IsDone() && aBrentResult.Root.has_value())
        {
          double aRootValue = 0.0, aDummy = 0.0;
          theFunc.Values(*aBrentResult.Root, aRootValue, aDummy);
          addRoot(*aBrentResult.Root, aRootValue);
        }
      }

      else if (aF0 > 0.0 && aF1 > 0.0)
      {

        if (aDFValues(i) < 0.0 && aDFValues(i + 1) > 0.0)
        {

          double aXL = aX0, aXR = aX1;

          for (int anIter = 0; anIter < 20; ++anIter)
          {
            double aXM = 0.5 * (aXL + aXR);
            double aFM = 0.0, aDFM = 0.0;
            if (!theFunc.Values(aXM, aFM, aDFM))
              break;
            aFM -= theConfig.Offset;

            if (aDFM < 0.0)
            {
              aXL = aXM;
            }
            else
            {
              aXR = aXM;
            }

            if (std::abs(aFM) < theConfig.FTolerance)
            {
              addRoot(aXM, aFM + theConfig.Offset);
              break;
            }
          }
        }
      }
      else if (aF0 < 0.0 && aF1 < 0.0)
      {

        if (aDFValues(i) > 0.0 && aDFValues(i + 1) < 0.0)
        {
          double aXL = aX0, aXR = aX1;

          for (int anIter = 0; anIter < 20; ++anIter)
          {
            double aXM = 0.5 * (aXL + aXR);
            double aFM = 0.0, aDFM = 0.0;
            if (!theFunc.Values(aXM, aFM, aDFM))
              break;
            aFM -= theConfig.Offset;

            if (aDFM > 0.0)
            {
              aXL = aXM;
            }
            else
            {
              aXR = aXM;
            }

            if (std::abs(aFM) < theConfig.FTolerance)
            {
              addRoot(aXM, aFM + theConfig.Offset);
              break;
            }
          }
        }
      }
    }

    if (std::abs(aFValues(aNbSamples)) < theConfig.FTolerance)
    {
      addRoot(aXValues(aNbSamples), aFValues(aNbSamples) + theConfig.Offset);
    }

    const int aNbRoots = aResult.Roots.Length();
    if (aNbRoots > 1)
    {
      math_IntegerVector aIndices(0, aNbRoots - 1);
      for (int i = 0; i < aNbRoots; ++i)
      {
        aIndices(i) = i;
      }

      for (int i = 1; i < aNbRoots; ++i)
      {
        int aKey = aIndices(i);
        int j    = i - 1;
        while (j >= 0 && aResult.Roots.Value(aIndices(j)) > aResult.Roots.Value(aKey))
        {
          aIndices(j + 1) = aIndices(j);
          --j;
        }
        aIndices(j + 1) = aKey;
      }

      NCollection_Vector<double> aSortedRoots, aSortedValues;
      for (int i = 0; i < aNbRoots; ++i)
      {
        aSortedRoots.Append(aResult.Roots.Value(aIndices(i)));
        aSortedValues.Append(aResult.Values.Value(aIndices(i)));
      }
      aResult.Roots  = aSortedRoots;
      aResult.Values = aSortedValues;
    }

    return aResult;
  }

  template <typename Function>
  MultipleResult FindAllRoots(Function& theFunc, double theLower, double theUpper, int theNbSamples)
  {
    MultipleConfig aConfig;
    aConfig.NbSamples = theNbSamples;
    return FindAllRoots(theFunc, theLower, theUpper, aConfig);
  }

} // namespace MathRoot
