#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathOpt_PSO.hpp>
#include <MathOpt_BFGS.hpp>
#include <MathOpt_Powell.hpp>
#include <MathUtils_Core.hpp>
#include <math_BullardGenerator.hpp>

#include <NCollection_Vector.hpp>

#include <cmath>

namespace MathOpt
{
  using namespace MathUtils;

  enum class GlobalStrategy
  {
    PSO,
    MultiStart,
    PSOHybrid,
    DifferentialEvolution
  };

  struct GlobalConfig : NDimConfig
  {
    GlobalStrategy Strategy      = GlobalStrategy::PSOHybrid;
    int            NbPopulation  = 40;
    int            NbStarts      = 10;
    double         MutationScale = 0.8;
    double         CrossoverProb = 0.9;
    unsigned int   Seed          = 12345;

    GlobalConfig()
        : NDimConfig(1.0e-8, 200, true)
    {
    }

    GlobalConfig(GlobalStrategy theStrategy, int theMaxIter = 200)
        : NDimConfig(1.0e-8, theMaxIter, true),
          Strategy(theStrategy)
    {
    }
  };

  template <typename Function>
  VectorResult DifferentialEvolution(Function&           theFunc,
                                     const math_Vector&  theLowerBounds,
                                     const math_Vector&  theUpperBounds,
                                     const GlobalConfig& theConfig = GlobalConfig())
  {
    VectorResult aResult;

    const int aLower = theLowerBounds.Lower();
    const int aUpper = theLowerBounds.Upper();
    const int aN     = aUpper - aLower + 1;

    if (theUpperBounds.Length() != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    const int    aNP = theConfig.NbPopulation;
    const double aF  = theConfig.MutationScale;
    const double aCR = theConfig.CrossoverProb;

    math_BullardGenerator aRNG(theConfig.Seed);

    NCollection_Vector<math_Vector> aPopulation;
    math_Vector                     aFitness(0, aNP - 1);

    for (int i = 0; i < aNP; ++i)
    {
      aPopulation.Append(math_Vector(aLower, aUpper));
      for (int j = aLower; j <= aUpper; ++j)
      {
        double r = aRNG.NextReal();
        aPopulation.ChangeValue(i)(j) =
          theLowerBounds(j) + r * (theUpperBounds(j) - theLowerBounds(j));
      }

      double aFit;
      if (!theFunc.Value(aPopulation.Value(i), aFit))
      {
        aFit = std::numeric_limits<double>::max();
      }
      aFitness(i) = aFit;
    }

    int    aBestIdx   = 0;
    double aBestValue = aFitness(0);
    for (int i = 1; i < aNP; ++i)
    {
      if (aFitness(i) < aBestValue)
      {
        aBestValue = aFitness(i);
        aBestIdx   = i;
      }
    }

    math_Vector aTrial(aLower, aUpper);

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      for (int i = 0; i < aNP; ++i)
      {

        int a, b, c;
        do
        {
          a = static_cast<int>(aRNG.NextReal() * aNP);
        } while (a == i);
        do
        {
          b = static_cast<int>(aRNG.NextReal() * aNP);
        } while (b == i || b == a);
        do
        {
          c = static_cast<int>(aRNG.NextReal() * aNP);
        } while (c == i || c == a || c == b);

        int jRand = aLower + static_cast<int>(aRNG.NextReal() * aN);

        for (int j = aLower; j <= aUpper; ++j)
        {
          if (aRNG.NextReal() < aCR || j == jRand)
          {

            double aVal =
              aPopulation.Value(a)(j) + aF * (aPopulation.Value(b)(j) - aPopulation.Value(c)(j));

            aTrial(j) = MathUtils::Clamp(aVal, theLowerBounds(j), theUpperBounds(j));
          }
          else
          {
            aTrial(j) = aPopulation.Value(i)(j);
          }
        }

        double aTrialFitness;
        if (!theFunc.Value(aTrial, aTrialFitness))
        {
          aTrialFitness = std::numeric_limits<double>::max();
        }

        if (aTrialFitness <= aFitness(i))
        {
          aPopulation.ChangeValue(i) = aTrial;
          aFitness(i)                = aTrialFitness;

          if (aTrialFitness < aBestValue)
          {
            aBestValue = aTrialFitness;
            aBestIdx   = i;
          }
        }
      }

      double aMaxDiff = 0.0;
      for (int i = 0; i < aNP; ++i)
      {
        aMaxDiff = std::max(aMaxDiff, std::abs(aFitness(i) - aBestValue));
      }

      if (aMaxDiff < theConfig.Tolerance)
      {
        break;
      }
    }

    aResult.Status   = Status::OK;
    aResult.Solution = aPopulation.Value(aBestIdx);
    aResult.Value    = aBestValue;
    return aResult;
  }

  template <typename Function>
  VectorResult MultiStart(Function&           theFunc,
                          const math_Vector&  theLowerBounds,
                          const math_Vector&  theUpperBounds,
                          const GlobalConfig& theConfig = GlobalConfig())
  {
    VectorResult aResult;

    const int aLower = theLowerBounds.Lower();
    const int aUpper = theLowerBounds.Upper();
    const int aN     = aUpper - aLower + 1;

    if (theUpperBounds.Length() != aN)
    {
      aResult.Status = Status::InvalidInput;
      return aResult;
    }

    math_BullardGenerator aRNG(theConfig.Seed);

    math_Vector aBestSolution(aLower, aUpper);
    double      aBestValue = std::numeric_limits<double>::max();
    bool        aFound     = false;

    Config aPowellConfig;
    aPowellConfig.Tolerance     = theConfig.Tolerance;
    aPowellConfig.XTolerance    = theConfig.Tolerance;
    aPowellConfig.FTolerance    = theConfig.Tolerance;
    aPowellConfig.MaxIterations = theConfig.MaxIterations / theConfig.NbStarts;
    if (aPowellConfig.MaxIterations < 10)
    {
      aPowellConfig.MaxIterations = 10;
    }

    for (int s = 0; s < theConfig.NbStarts; ++s)
    {

      math_Vector aStart(aLower, aUpper);
      for (int i = aLower; i <= aUpper; ++i)
      {
        double r  = aRNG.NextReal();
        aStart(i) = theLowerBounds(i) + r * (theUpperBounds(i) - theLowerBounds(i));
      }

      VectorResult aLocalResult = Powell(theFunc, aStart, aPowellConfig);

      if (aLocalResult.IsDone() && aLocalResult.Value)
      {

        math_Vector aSol = *aLocalResult.Solution;
        for (int i = aLower; i <= aUpper; ++i)
        {
          aSol(i) = MathUtils::Clamp(aSol(i), theLowerBounds(i), theUpperBounds(i));
        }

        double aValue;
        if (theFunc.Value(aSol, aValue) && aValue < aBestValue)
        {
          aBestValue    = aValue;
          aBestSolution = aSol;
          aFound        = true;
        }
      }
      else
      {

        double aValue;
        if (theFunc.Value(aStart, aValue) && aValue < aBestValue)
        {
          aBestValue    = aValue;
          aBestSolution = aStart;
          aFound        = true;
        }
      }
    }

    if (!aFound)
    {
      aResult.Status = Status::NumericalError;
      return aResult;
    }

    aResult.Status   = Status::OK;
    aResult.Solution = aBestSolution;
    aResult.Value    = aBestValue;
    return aResult;
  }

  template <typename Function>
  VectorResult GlobalMinimum(Function&           theFunc,
                             const math_Vector&  theLowerBounds,
                             const math_Vector&  theUpperBounds,
                             const GlobalConfig& theConfig = GlobalConfig())
  {
    switch (theConfig.Strategy)
    {
      case GlobalStrategy::PSO:
      {
        PSOConfig aPSOConfig;
        aPSOConfig.NbParticles   = theConfig.NbPopulation;
        aPSOConfig.MaxIterations = theConfig.MaxIterations;
        aPSOConfig.Tolerance     = theConfig.Tolerance;
        aPSOConfig.Seed          = theConfig.Seed;
        return PSO(theFunc, theLowerBounds, theUpperBounds, aPSOConfig);
      }

      case GlobalStrategy::MultiStart:
        return MultiStart(theFunc, theLowerBounds, theUpperBounds, theConfig);

      case GlobalStrategy::PSOHybrid:
      {

        PSOConfig aPSOConfig;
        aPSOConfig.NbParticles   = theConfig.NbPopulation;
        aPSOConfig.MaxIterations = theConfig.MaxIterations / 2;
        aPSOConfig.Tolerance     = theConfig.Tolerance * 10.0;
        aPSOConfig.Seed          = theConfig.Seed;

        VectorResult aPSOResult = PSO(theFunc, theLowerBounds, theUpperBounds, aPSOConfig);

        if (!aPSOResult.IsDone() || !aPSOResult.Solution)
        {
          return aPSOResult;
        }

        Config aPowellConfig;
        aPowellConfig.Tolerance     = theConfig.Tolerance;
        aPowellConfig.XTolerance    = theConfig.Tolerance;
        aPowellConfig.FTolerance    = theConfig.Tolerance;
        aPowellConfig.MaxIterations = theConfig.MaxIterations / 2;

        VectorResult aLocalResult = Powell(theFunc, *aPSOResult.Solution, aPowellConfig);

        if (aLocalResult.IsDone() && aLocalResult.Value && aPSOResult.Value
            && *aLocalResult.Value < *aPSOResult.Value)
        {

          const int   aLower = theLowerBounds.Lower();
          const int   aUpper = theLowerBounds.Upper();
          math_Vector aSol   = *aLocalResult.Solution;
          for (int i = aLower; i <= aUpper; ++i)
          {
            aSol(i) = MathUtils::Clamp(aSol(i), theLowerBounds(i), theUpperBounds(i));
          }
          aLocalResult.Solution = aSol;

          double aValue;
          if (theFunc.Value(aSol, aValue))
          {
            aLocalResult.Value = aValue;
          }
          return aLocalResult;
        }

        return aPSOResult;
      }

      case GlobalStrategy::DifferentialEvolution:
        return DifferentialEvolution(theFunc, theLowerBounds, theUpperBounds, theConfig);

      default:
        VectorResult aResult;
        aResult.Status = Status::InvalidInput;
        return aResult;
    }
  }

} // namespace MathOpt
