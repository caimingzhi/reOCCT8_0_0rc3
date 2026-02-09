

#include <gtest/gtest.h>

#include <MathSys_LevenbergMarquardt.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-6;
  constexpr double THE_LOOSE_TOL = 1.0e-3;

  struct LinearSystem2D
  {
    int NbVariables() const { return 2; }

    int NbEquations() const { return 2; }

    bool Value(const math_Vector& theX, math_Vector& theF)
    {
      theF(1) = theX(1) + theX(2) - 3.0;
      theF(2) = theX(1) - theX(2) - 1.0;
      return true;
    }

    bool Derivatives(const math_Vector&, math_Matrix& theD)
    {
      theD(1, 1) = 1.0;
      theD(1, 2) = 1.0;
      theD(2, 1) = 1.0;
      theD(2, 2) = -1.0;
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD)
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

  struct CircleHyperbola
  {
    int NbVariables() const { return 2; }

    int NbEquations() const { return 2; }

    bool Value(const math_Vector& theX, math_Vector& theF)
    {
      theF(1) = theX(1) * theX(1) + theX(2) * theX(2) - 4.0;
      theF(2) = theX(1) * theX(2) - 1.0;
      return true;
    }

    bool Derivatives(const math_Vector& theX, math_Matrix& theD)
    {
      theD(1, 1) = 2.0 * theX(1);
      theD(1, 2) = 2.0 * theX(2);
      theD(2, 1) = theX(2);
      theD(2, 2) = theX(1);
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD)
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

  struct RosenbrockResidual
  {
    int NbVariables() const { return 2; }

    int NbEquations() const { return 2; }

    bool Value(const math_Vector& theX, math_Vector& theF)
    {
      theF(1) = 10.0 * (theX(2) - theX(1) * theX(1));
      theF(2) = 1.0 - theX(1);
      return true;
    }

    bool Derivatives(const math_Vector& theX, math_Matrix& theD)
    {
      theD(1, 1) = -20.0 * theX(1);
      theD(1, 2) = 10.0;
      theD(2, 1) = -1.0;
      theD(2, 2) = 0.0;
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD)
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

  struct PowellSingular
  {
    int NbVariables() const { return 4; }

    int NbEquations() const { return 4; }

    bool Value(const math_Vector& theX, math_Vector& theF)
    {
      theF(1) = theX(1) + 10.0 * theX(2);
      theF(2) = std::sqrt(5.0) * (theX(3) - theX(4));
      theF(3) = (theX(2) - 2.0 * theX(3)) * (theX(2) - 2.0 * theX(3));
      theF(4) = std::sqrt(10.0) * (theX(1) - theX(4)) * (theX(1) - theX(4));
      return true;
    }

    bool Derivatives(const math_Vector& theX, math_Matrix& theD)
    {
      theD.Init(0.0);

      theD(1, 1) = 1.0;
      theD(1, 2) = 10.0;

      theD(2, 3) = std::sqrt(5.0);
      theD(2, 4) = -std::sqrt(5.0);

      const double aT1 = theX(2) - 2.0 * theX(3);
      theD(3, 2)       = 2.0 * aT1;
      theD(3, 3)       = -4.0 * aT1;

      const double aT2 = theX(1) - theX(4);
      theD(4, 1)       = 2.0 * std::sqrt(10.0) * aT2;
      theD(4, 4)       = -2.0 * std::sqrt(10.0) * aT2;
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD)
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

  struct ExponentialFit
  {
    double myT[5] = {0.0, 1.0, 2.0, 3.0, 4.0};
    double myY[5] = {1.0, 2.7, 7.4, 20.1, 54.6};

    int NbVariables() const { return 2; }

    int NbEquations() const { return 5; }

    bool Value(const math_Vector& theX, math_Vector& theF)
    {
      for (int i = 0; i < 5; ++i)
      {
        theF(i + 1) = myY[i] - theX(1) * std::exp(theX(2) * myT[i]);
      }
      return true;
    }

    bool Derivatives(const math_Vector& theX, math_Matrix& theD)
    {
      for (int i = 0; i < 5; ++i)
      {
        const double aExp = std::exp(theX(2) * myT[i]);
        theD(i + 1, 1)    = -aExp;
        theD(i + 1, 2)    = -theX(1) * myT[i] * aExp;
      }
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD)
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

  struct OverdeterminedSystem
  {
    int NbVariables() const { return 2; }

    int NbEquations() const { return 3; }

    bool Value(const math_Vector& theX, math_Vector& theF)
    {
      theF(1) = theX(1) + theX(2) - 2.0;
      theF(2) = theX(1) - theX(2);
      theF(3) = 2.0 * theX(1) + theX(2) - 3.0;
      return true;
    }

    bool Derivatives(const math_Vector&, math_Matrix& theD)
    {
      theD(1, 1) = 1.0;
      theD(1, 2) = 1.0;
      theD(2, 1) = 1.0;
      theD(2, 2) = -1.0;
      theD(3, 1) = 2.0;
      theD(3, 2) = 1.0;
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD)
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

  class CircleHyperbolaOld : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& theX, math_Vector& theF) override
    {
      theF(1) = theX(1) * theX(1) + theX(2) * theX(2) - 4.0;
      theF(2) = theX(1) * theX(2) - 1.0;
      return true;
    }

    bool Derivatives(const math_Vector& theX, math_Matrix& theD) override
    {
      theD(1, 1) = 2.0 * theX(1);
      theD(1, 2) = 2.0 * theX(2);
      theD(2, 1) = theX(2);
      theD(2, 2) = theX(1);
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD) override
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

  class RosenbrockResidualOld : public math_FunctionSetWithDerivatives
  {
  public:
    int NbVariables() const override { return 2; }

    int NbEquations() const override { return 2; }

    bool Value(const math_Vector& theX, math_Vector& theF) override
    {
      theF(1) = 10.0 * (theX(2) - theX(1) * theX(1));
      theF(2) = 1.0 - theX(1);
      return true;
    }

    bool Derivatives(const math_Vector& theX, math_Matrix& theD) override
    {
      theD(1, 1) = -20.0 * theX(1);
      theD(1, 2) = 10.0;
      theD(2, 1) = -1.0;
      theD(2, 2) = 0.0;
      return true;
    }

    bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD) override
    {
      return Value(theX, theF) && Derivatives(theX, theD);
    }
  };

} // namespace

TEST(MathSys_LM_Test, LinearSystem2D)
{
  LinearSystem2D aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 100;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 2.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathSys_LM_Test, CircleHyperbola)
{
  CircleHyperbola aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 1.5;
  aStart(2) = 0.5;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 100;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());

  const double aX = (*aResult.Solution)(1);
  const double aY = (*aResult.Solution)(2);

  EXPECT_NEAR(aX * aX + aY * aY, 4.0, THE_TOLERANCE);
  EXPECT_NEAR(aX * aY, 1.0, THE_TOLERANCE);
}

TEST(MathSys_LM_Test, RosenbrockResidual)
{
  RosenbrockResidual aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 200;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_LOOSE_TOL);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, THE_LOOSE_TOL);
  EXPECT_LT(*aResult.Value, 0.01);
}

TEST(MathSys_LM_Test, PowellSingular)
{
  PowellSingular aFunc;

  math_Vector aStart(1, 4);
  aStart(1) = 3.0;
  aStart(2) = -1.0;
  aStart(3) = 0.0;
  aStart(4) = 1.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 500;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());

  for (int i = 1; i <= 4; ++i)
  {
    EXPECT_NEAR((*aResult.Solution)(i), 0.0, 0.1);
  }
  EXPECT_LT(*aResult.Value, 0.01);
}

TEST(MathSys_LM_Test, OverdeterminedSystem)
{
  OverdeterminedSystem aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.MaxIterations = 100;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, THE_TOLERANCE);
}

TEST(MathSys_LM_Test, ExponentialFit)
{
  ExponentialFit aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.5;
  aStart(2) = 0.5;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-8;
  aConfig.MaxIterations = 100;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());

  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 0.1);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, 0.1);
}

TEST(MathSys_LM_Test, BoundedCircleHyperbola)
{
  CircleHyperbola aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 1.0;
  aStart(2) = 1.0;

  math_Vector aLower(1, 2);
  aLower(1) = 0.0;
  aLower(2) = 0.0;

  math_Vector aUpper(1, 2);
  aUpper(1) = 5.0;
  aUpper(2) = 5.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 100;

  auto aResult = MathSys::LevenbergMarquardtBounded(aFunc, aStart, aLower, aUpper, aConfig);

  ASSERT_TRUE(aResult.IsDone());

  const double aX = (*aResult.Solution)(1);
  const double aY = (*aResult.Solution)(2);

  EXPECT_GE(aX, 0.0);
  EXPECT_LE(aX, 5.0);
  EXPECT_GE(aY, 0.0);
  EXPECT_LE(aY, 5.0);

  EXPECT_NEAR(aX * aX + aY * aY, 4.0, THE_TOLERANCE);
  EXPECT_NEAR(aX * aY, 1.0, THE_TOLERANCE);
}

TEST(MathSys_LM_Test, BoundedRosenbrock)
{
  RosenbrockResidual aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  math_Vector aLower(1, 2);
  aLower(1) = -5.0;
  aLower(2) = -5.0;

  math_Vector aUpper(1, 2);
  aUpper(1) = 5.0;
  aUpper(2) = 5.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 200;

  auto aResult = MathSys::LevenbergMarquardtBounded(aFunc, aStart, aLower, aUpper, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_LOOSE_TOL);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, THE_LOOSE_TOL);
}

TEST(MathSys_LM_Test, BoundedActiveConstraint)
{

  LinearSystem2D aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 1.0;
  aStart(2) = 1.0;

  math_Vector aLower(1, 2);
  aLower(1) = -10.0;
  aLower(2) = -10.0;

  math_Vector aUpper(1, 2);
  aUpper(1) = 1.5;
  aUpper(2) = 10.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.MaxIterations = 100;

  auto aResult = MathSys::LevenbergMarquardtBounded(aFunc, aStart, aLower, aUpper, aConfig);

  EXPECT_LE((*aResult.Solution)(1), 1.5 + THE_TOLERANCE);
}

TEST(MathSys_LM_Test, DampingParameters)
{
  CircleHyperbola aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 1.5;
  aStart(2) = 0.5;

  double aLambdas[] = {1.0e-6, 1.0e-3, 1.0, 100.0};

  for (double aLambda : aLambdas)
  {
    MathSys::LMConfig aConfig;
    aConfig.Tolerance     = 1.0e-10;
    aConfig.FTolerance    = 1.0e-10;
    aConfig.MaxIterations = 200;
    aConfig.LambdaInit    = aLambda;

    auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

    ASSERT_TRUE(aResult.IsDone()) << "Failed with lambda = " << aLambda;

    const double aX = (*aResult.Solution)(1);
    const double aY = (*aResult.Solution)(2);

    EXPECT_NEAR(aX * aX + aY * aY, 4.0, THE_TOLERANCE)
      << "Failed equation 1 with lambda = " << aLambda;
    EXPECT_NEAR(aX * aY, 1.0, THE_TOLERANCE) << "Failed equation 2 with lambda = " << aLambda;
  }
}

TEST(MathSys_LM_Test, LambdaUpdateFactors)
{
  RosenbrockResidual aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  struct
  {
    double myIncrease;
    double myDecrease;
  } aFactors[] = {{2.0, 0.5}, {5.0, 0.2}, {10.0, 0.1}, {20.0, 0.05}};

  for (const auto& aFactor : aFactors)
  {
    MathSys::LMConfig aConfig;
    aConfig.Tolerance      = 1.0e-10;
    aConfig.FTolerance     = 1.0e-10;
    aConfig.MaxIterations  = 300;
    aConfig.LambdaIncrease = aFactor.myIncrease;
    aConfig.LambdaDecrease = aFactor.myDecrease;

    auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

    ASSERT_TRUE(aResult.IsDone()) << "Failed with increase=" << aFactor.myIncrease
                                  << ", decrease=" << aFactor.myDecrease;
    EXPECT_LT(*aResult.Value, 0.1);
  }
}

TEST(MathSys_LM_Test, CompareWithOldAPI_CircleHyperbola)
{
  CircleHyperbolaOld anOldFunc;
  CircleHyperbola    aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 1.5;
  aStart(2) = 0.5;

  math_Vector aTol(1, 2, 1.0e-10);

  math_FunctionSetRoot anOldSolver(anOldFunc, aTol, 100);
  anOldSolver.Perform(anOldFunc, aStart);

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 100;
  auto aNewResult       = MathSys::LevenbergMarquardt(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  const math_Vector& anOldSol = anOldSolver.Root();
  EXPECT_NEAR(anOldSol(1) * anOldSol(1) + anOldSol(2) * anOldSol(2), 4.0, THE_LOOSE_TOL);
  EXPECT_NEAR(anOldSol(1) * anOldSol(2), 1.0, THE_LOOSE_TOL);

  const double aNewX = (*aNewResult.Solution)(1);
  const double aNewY = (*aNewResult.Solution)(2);
  EXPECT_NEAR(aNewX * aNewX + aNewY * aNewY, 4.0, THE_TOLERANCE);
  EXPECT_NEAR(aNewX * aNewY, 1.0, THE_TOLERANCE);
}

TEST(MathSys_LM_Test, CompareWithOldAPI_Rosenbrock)
{
  RosenbrockResidualOld anOldFunc;
  RosenbrockResidual    aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  math_Vector aTol(1, 2, 1.0e-10);

  math_FunctionSetRoot anOldSolver(anOldFunc, aTol, 200);
  anOldSolver.Perform(anOldFunc, aStart);

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 200;
  auto aNewResult       = MathSys::LevenbergMarquardt(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_LOOSE_TOL);
  EXPECT_NEAR((*aNewResult.Solution)(2), 1.0, THE_LOOSE_TOL);
}

TEST(MathSys_LM_Test, CompareWithOldAPI_Bounded)
{
  CircleHyperbolaOld anOldFunc;
  CircleHyperbola    aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 1.0;
  aStart(2) = 1.0;

  math_Vector aLower(1, 2);
  aLower(1) = 0.0;
  aLower(2) = 0.0;

  math_Vector aUpper(1, 2);
  aUpper(1) = 5.0;
  aUpper(2) = 5.0;

  math_Vector aTol(1, 2, 1.0e-10);

  math_FunctionSetRoot anOldSolver(anOldFunc, aTol, 100);
  anOldSolver.Perform(anOldFunc, aStart, aLower, aUpper);

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.FTolerance    = 1.0e-10;
  aConfig.MaxIterations = 100;
  auto aNewResult = MathSys::LevenbergMarquardtBounded(aNewFunc, aStart, aLower, aUpper, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  const math_Vector& anOldSol = anOldSolver.Root();
  EXPECT_GE(anOldSol(1), 0.0);
  EXPECT_LE(anOldSol(1), 5.0);
  EXPECT_GE(anOldSol(2), 0.0);
  EXPECT_LE(anOldSol(2), 5.0);

  const double aNewX = (*aNewResult.Solution)(1);
  const double aNewY = (*aNewResult.Solution)(2);
  EXPECT_GE(aNewX, 0.0);
  EXPECT_LE(aNewX, 5.0);
  EXPECT_GE(aNewY, 0.0);
  EXPECT_LE(aNewY, 5.0);
}

TEST(MathSys_LM_Test, DifferentStartingPoints)
{
  CircleHyperbola aFunc;

  double aStarts[][2] = {{1.5, 0.5}, {2.0, 0.5}, {1.0, 1.0}, {2.5, 0.5}, {0.5, 2.0}};

  for (const auto& aStartPt : aStarts)
  {
    math_Vector aStart(1, 2);
    aStart(1) = aStartPt[0];
    aStart(2) = aStartPt[1];

    MathSys::LMConfig aConfig;
    aConfig.Tolerance     = 1.0e-10;
    aConfig.FTolerance    = 1.0e-10;
    aConfig.MaxIterations = 100;

    auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

    ASSERT_TRUE(aResult.IsDone()) << "Failed with start = (" << aStartPt[0] << ", " << aStartPt[1]
                                  << ")";

    const double aX = (*aResult.Solution)(1);
    const double aY = (*aResult.Solution)(2);

    EXPECT_NEAR(aX * aX + aY * aY, 4.0, THE_TOLERANCE)
      << "Failed equation 1 with start = (" << aStartPt[0] << ", " << aStartPt[1] << ")";
    EXPECT_NEAR(aX * aY, 1.0, THE_TOLERANCE)
      << "Failed equation 2 with start = (" << aStartPt[0] << ", " << aStartPt[1] << ")";
  }
}

TEST(MathSys_LM_Test, ConvergenceIterations)
{
  LinearSystem2D aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-12;
  aConfig.FTolerance    = 1.0e-12;
  aConfig.MaxIterations = 100;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());

  EXPECT_LT(aResult.NbIterations, 20);

  EXPECT_NEAR((*aResult.Solution)(1), 2.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, THE_TOLERANCE);
}

TEST(MathSys_LM_Test, MaxIterationsReached)
{
  RosenbrockResidual aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  MathSys::LMConfig aConfig;
  aConfig.Tolerance     = 1.0e-15;
  aConfig.MaxIterations = 5;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.Solution.has_value());
}

TEST(MathSys_LM_Test, InvalidInputDimensions)
{
  LinearSystem2D aFunc;

  math_Vector aStart(1, 3);
  aStart(1) = 0.0;
  aStart(2) = 0.0;
  aStart(3) = 0.0;

  MathSys::LMConfig aConfig;

  auto aResult = MathSys::LevenbergMarquardt(aFunc, aStart, aConfig);

  EXPECT_FALSE(aResult.IsDone());
  EXPECT_EQ(aResult.Status, MathSys::Status::InvalidInput);
}

TEST(MathSys_LM_Test, BoundedInvalidDimensions)
{
  LinearSystem2D aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  math_Vector aLower(1, 3);
  aLower(1) = -10.0;
  aLower(2) = -10.0;
  aLower(3) = -10.0;

  math_Vector aUpper(1, 2);
  aUpper(1) = 10.0;
  aUpper(2) = 10.0;

  MathSys::LMConfig aConfig;

  auto aResult = MathSys::LevenbergMarquardtBounded(aFunc, aStart, aLower, aUpper, aConfig);

  EXPECT_FALSE(aResult.IsDone());
  EXPECT_EQ(aResult.Status, MathSys::Status::InvalidInput);
}
