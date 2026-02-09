#pragma once

#include <MathUtils_Types.hpp>
#include <MathUtils_Config.hpp>
#include <MathUtils_Core.hpp>
#include <math_BullardGenerator.hpp>

#include <NCollection_Vector.hpp>

#include <cmath>

namespace MathOpt
{
  using namespace MathUtils;

  struct PSOConfig : NDimConfig
  {
    int          NbParticles   = 40;
    double       Omega         = 0.7;
    double       PhiPersonal   = 1.5;
    double       PhiGlobal     = 1.5;
    double       VelocityClamp = 0.5;
    unsigned int Seed          = 12345;

    PSOConfig()
        : NDimConfig(1.0e-8, 100, true)
    {
    }

    PSOConfig(int theNbParticles, int theMaxIter = 100, double theTolerance = 1.0e-8)
        : NDimConfig(theTolerance, theMaxIter, true),
          NbParticles(theNbParticles)
    {
    }
  };

  template <typename Function>
  VectorResult PSO(Function&          theFunc,
                   const math_Vector& theLowerBounds,
                   const math_Vector& theUpperBounds,
                   const PSOConfig&   theConfig = PSOConfig())
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

    for (int i = aLower; i <= aUpper; ++i)
    {
      if (theLowerBounds(i) >= theUpperBounds(i))
      {
        aResult.Status = Status::InvalidInput;
        return aResult;
      }
    }

    const int aNbParticles = theConfig.NbParticles;

    struct Particle
    {
      math_Vector Position;
      math_Vector Velocity;
      math_Vector BestPosition;
      double      BestValue;
      double      CurrentValue;

      Particle(int theLower, int theUpper)
          : Position(theLower, theUpper),
            Velocity(theLower, theUpper),
            BestPosition(theLower, theUpper),
            BestValue(std::numeric_limits<double>::max()),
            CurrentValue(std::numeric_limits<double>::max())
      {
      }
    };

    NCollection_Vector<Particle> aSwarm;
    for (int p = 0; p < aNbParticles; ++p)
    {
      aSwarm.Append(Particle(aLower, aUpper));
    }

    math_BullardGenerator aRNG(theConfig.Seed);

    math_Vector aVelMax(aLower, aUpper);
    for (int i = aLower; i <= aUpper; ++i)
    {
      aVelMax(i) = theConfig.VelocityClamp * (theUpperBounds(i) - theLowerBounds(i));
    }

    math_Vector aGlobalBest(aLower, aUpper);
    double      aGlobalBestValue = std::numeric_limits<double>::max();

    for (int p = 0; p < aNbParticles; ++p)
    {
      Particle& aParticle = aSwarm.ChangeValue(p);

      for (int i = aLower; i <= aUpper; ++i)
      {
        double aRand          = aRNG.NextReal();
        aParticle.Position(i) = theLowerBounds(i) + aRand * (theUpperBounds(i) - theLowerBounds(i));

        aRand                 = 2.0 * aRNG.NextReal() - 1.0;
        aParticle.Velocity(i) = aRand * aVelMax(i);
      }

      if (!theFunc.Value(aParticle.Position, aParticle.CurrentValue))
      {
        aParticle.CurrentValue = std::numeric_limits<double>::max();
      }

      aParticle.BestPosition = aParticle.Position;
      aParticle.BestValue    = aParticle.CurrentValue;

      if (aParticle.BestValue < aGlobalBestValue)
      {
        aGlobalBestValue = aParticle.BestValue;
        aGlobalBest      = aParticle.BestPosition;
      }
    }

    double aPrevBest        = aGlobalBestValue;
    int    aStagnationCount = 0;

    for (int anIter = 0; anIter < theConfig.MaxIterations; ++anIter)
    {
      aResult.NbIterations = anIter + 1;

      for (int p = 0; p < aNbParticles; ++p)
      {
        Particle& aParticle = aSwarm.ChangeValue(p);

        for (int i = aLower; i <= aUpper; ++i)
        {
          double r1 = aRNG.NextReal();
          double r2 = aRNG.NextReal();

          double aVnew =
            theConfig.Omega * aParticle.Velocity(i)
            + theConfig.PhiPersonal * r1 * (aParticle.BestPosition(i) - aParticle.Position(i))
            + theConfig.PhiGlobal * r2 * (aGlobalBest(i) - aParticle.Position(i));

          aVnew                 = MathUtils::Clamp(aVnew, -aVelMax(i), aVelMax(i));
          aParticle.Velocity(i) = aVnew;
        }

        for (int i = aLower; i <= aUpper; ++i)
        {
          double aXnew = aParticle.Position(i) + aParticle.Velocity(i);

          if (aXnew < theLowerBounds(i))
          {
            aXnew                 = theLowerBounds(i);
            aParticle.Velocity(i) = -0.5 * aParticle.Velocity(i);
          }
          else if (aXnew > theUpperBounds(i))
          {
            aXnew                 = theUpperBounds(i);
            aParticle.Velocity(i) = -0.5 * aParticle.Velocity(i);
          }

          aParticle.Position(i) = aXnew;
        }

        if (!theFunc.Value(aParticle.Position, aParticle.CurrentValue))
        {
          aParticle.CurrentValue = std::numeric_limits<double>::max();
        }

        if (aParticle.CurrentValue < aParticle.BestValue)
        {
          aParticle.BestValue    = aParticle.CurrentValue;
          aParticle.BestPosition = aParticle.Position;
        }

        if (aParticle.BestValue < aGlobalBestValue)
        {
          aGlobalBestValue = aParticle.BestValue;
          aGlobalBest      = aParticle.BestPosition;
        }
      }

      if (std::abs(aGlobalBestValue - aPrevBest)
          < theConfig.Tolerance * (1.0 + std::abs(aGlobalBestValue)))
      {
        ++aStagnationCount;
        if (aStagnationCount > 10)
        {

          break;
        }
      }
      else
      {
        aStagnationCount = 0;
      }
      aPrevBest = aGlobalBestValue;
    }

    aResult.Status   = Status::OK;
    aResult.Solution = aGlobalBest;
    aResult.Value    = aGlobalBestValue;
    return aResult;
  }

  template <typename Function>
  VectorResult PSOMultiStart(Function&          theFunc,
                             const math_Vector& theLowerBounds,
                             const math_Vector& theUpperBounds,
                             int                theNbStarts = 5,
                             const PSOConfig&   theConfig   = PSOConfig())
  {

    PSOConfig aPSOConfig     = theConfig;
    aPSOConfig.NbParticles   = theNbStarts * 10;
    aPSOConfig.MaxIterations = theConfig.MaxIterations / 2;

    VectorResult aPSOResult = PSO(theFunc, theLowerBounds, theUpperBounds, aPSOConfig);
    return aPSOResult;
  }

} // namespace MathOpt
