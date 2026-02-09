#pragma once

#include <limits>

namespace MathUtils
{

  struct Config
  {
    int    MaxIterations = 100;
    double Tolerance     = 1.0e-10;
    double XTolerance    = 1.0e-10;
    double FTolerance    = 1.0e-10;

    double StepMin = std::numeric_limits<double>::epsilon();

    Config() = default;

    explicit Config(double theTolerance, int theMaxIter = 100)
        : MaxIterations(theMaxIter),
          Tolerance(theTolerance),
          XTolerance(theTolerance),
          FTolerance(theTolerance)
    {
    }
  };

  struct BoundedConfig : Config
  {
    double LowerBound = -std::numeric_limits<double>::max();
    double UpperBound = std::numeric_limits<double>::max();

    BoundedConfig() = default;

    BoundedConfig(double theLower,
                  double theUpper,
                  double theTolerance = 1.0e-10,
                  int    theMaxIter   = 100)
        : Config(theTolerance, theMaxIter),
          LowerBound(theLower),
          UpperBound(theUpper)
    {
    }
  };

  struct NDimConfig : Config
  {
    bool UseBounds = false;

    NDimConfig() = default;

    explicit NDimConfig(double theTolerance, int theMaxIter = 100, bool theUseBounds = false)
        : Config(theTolerance, theMaxIter),
          UseBounds(theUseBounds)
    {
    }
  };

  struct IntegConfig
  {
    int    InitialOrder  = 15;
    int    MaxOrder      = 61;
    int    MaxIterations = 100;
    double Tolerance     = 1.0e-10;

    IntegConfig() = default;

    explicit IntegConfig(double theTolerance, int theMaxIter = 100)
        : MaxIterations(theMaxIter),
          Tolerance(theTolerance)
    {
    }
  };

  struct LinConfig
  {
    double SingularityTolerance = 1.0e-15;
    bool   UsePivoting          = true;

    LinConfig() = default;
  };

} // namespace MathUtils
