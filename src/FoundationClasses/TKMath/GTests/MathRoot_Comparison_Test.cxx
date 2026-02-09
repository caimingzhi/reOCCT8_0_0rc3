

#include <gtest/gtest.h>

#include <MathRoot_Newton.hpp>
#include <MathRoot_Brent.hpp>
#include <MathRoot_Bisection.hpp>
#include <MathRoot_Secant.hpp>

#include <math_BissecNewton.hpp>
#include <math_BracketedRoot.hpp>
#include <math_FunctionRoot.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <math_NewtonFunctionRoot.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-9;
  constexpr double THE_PI        = 3.14159265358979323846;

  class SqrtTwoFuncOld : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX - 2.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 2.0 * theX;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX - 2.0;
      theD = 2.0 * theX;
      return true;
    }
  };

  class CosMinusXFuncOld : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::cos(theX) - theX;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = -std::sin(theX) - 1.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = std::cos(theX) - theX;
      theD = -std::sin(theX) - 1.0;
      return true;
    }
  };

  class SinFuncOld : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::sin(theX);
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = std::cos(theX);
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = std::sin(theX);
      theD = std::cos(theX);
      return true;
    }
  };

  class CubicFuncOld : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX - theX - 2.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 3.0 * theX * theX - 1.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX * theX - theX - 2.0;
      theD = 3.0 * theX * theX - 1.0;
      return true;
    }
  };

  class ExpMinusThreeFuncOld : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::exp(theX) - 3.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = std::exp(theX);
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = std::exp(theX) - 3.0;
      theD = std::exp(theX);
      return true;
    }
  };

  struct SqrtTwoFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX - 2.0;
      return true;
    }

    bool Values(double theX, double& theF, double& theDf) const
    {
      theF  = theX * theX - 2.0;
      theDf = 2.0 * theX;
      return true;
    }
  };

  struct CosMinusXFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = std::cos(theX) - theX;
      return true;
    }

    bool Values(double theX, double& theF, double& theDf) const
    {
      theF  = std::cos(theX) - theX;
      theDf = -std::sin(theX) - 1.0;
      return true;
    }
  };

  struct SinFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = std::sin(theX);
      return true;
    }

    bool Values(double theX, double& theF, double& theDf) const
    {
      theF  = std::sin(theX);
      theDf = std::cos(theX);
      return true;
    }
  };

  struct CubicFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX * theX - theX - 2.0;
      return true;
    }

    bool Values(double theX, double& theF, double& theDf) const
    {
      theF  = theX * theX * theX - theX - 2.0;
      theDf = 3.0 * theX * theX - 1.0;
      return true;
    }
  };

  struct ExpMinusThreeFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = std::exp(theX) - 3.0;
      return true;
    }

    bool Values(double theX, double& theF, double& theDf) const
    {
      theF  = std::exp(theX) - 3.0;
      theDf = std::exp(theX);
      return true;
    }
  };
} // namespace

TEST(MathRoot_ComparisonTest, BisectionNewton_SqrtTwo)
{
  SqrtTwoFuncOld anOldFunc;
  SqrtTwoFuncNew aNewFunc;

  math_BissecNewton anOldSolver(THE_TOLERANCE);
  anOldSolver.Perform(anOldFunc, 1.0, 2.0, 100);

  MathRoot::ScalarResult aNewResult = MathRoot::BisectionNewton(aNewFunc, 1.0, 2.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Root(), std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, BisectionNewton_CosMinusX)
{
  CosMinusXFuncOld anOldFunc;
  CosMinusXFuncNew aNewFunc;

  math_BissecNewton anOldSolver(THE_TOLERANCE);
  anOldSolver.Perform(anOldFunc, 0.0, 1.0, 100);

  MathRoot::ScalarResult aNewResult = MathRoot::BisectionNewton(aNewFunc, 0.0, 1.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);

  double aFx = std::cos(*aNewResult.Root) - *aNewResult.Root;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, BisectionNewton_SinPi)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_BissecNewton anOldSolver(THE_TOLERANCE);
  anOldSolver.Perform(anOldFunc, 2.0, 4.0, 100);

  MathRoot::ScalarResult aNewResult = MathRoot::BisectionNewton(aNewFunc, 2.0, 4.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, BisectionNewton_Cubic)
{
  CubicFuncOld anOldFunc;
  CubicFuncNew aNewFunc;

  math_BissecNewton anOldSolver(THE_TOLERANCE);
  anOldSolver.Perform(anOldFunc, 1.0, 2.0, 100);

  MathRoot::ScalarResult aNewResult = MathRoot::BisectionNewton(aNewFunc, 1.0, 2.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, Newton_SqrtTwo)
{
  SqrtTwoFuncOld anOldFunc;
  SqrtTwoFuncNew aNewFunc;

  math_NewtonFunctionRoot anOldSolver(anOldFunc, 1.5, THE_TOLERANCE, THE_TOLERANCE, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  aConfig.FTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::Newton(aNewFunc, 1.5, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, Newton_ExpMinusThree)
{
  ExpMinusThreeFuncOld anOldFunc;
  ExpMinusThreeFuncNew aNewFunc;

  math_NewtonFunctionRoot anOldSolver(anOldFunc, 1.0, THE_TOLERANCE, THE_TOLERANCE, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  aConfig.FTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::Newton(aNewFunc, 1.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, std::log(3.0), THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, Newton_CosMinusX)
{
  CosMinusXFuncOld anOldFunc;
  CosMinusXFuncNew aNewFunc;

  math_NewtonFunctionRoot anOldSolver(anOldFunc, 0.5, THE_TOLERANCE, THE_TOLERANCE, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  aConfig.FTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::Newton(aNewFunc, 0.5, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, Brent_SqrtTwo)
{
  SqrtTwoFuncOld anOldFunc;
  SqrtTwoFuncNew aNewFunc;

  math_BracketedRoot anOldSolver(anOldFunc, 1.0, 2.0, THE_TOLERANCE, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::Brent(aNewFunc, 1.0, 2.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, Brent_CosMinusX)
{
  CosMinusXFuncOld anOldFunc;
  CosMinusXFuncNew aNewFunc;

  math_BracketedRoot anOldSolver(anOldFunc, 0.0, 1.0, THE_TOLERANCE, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::Brent(aNewFunc, 0.0, 1.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, Brent_SinPi)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_BracketedRoot anOldSolver(anOldFunc, 2.0, 4.0, THE_TOLERANCE, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::Brent(aNewFunc, 2.0, 4.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, Brent_ExpMinusThree)
{
  ExpMinusThreeFuncOld anOldFunc;
  ExpMinusThreeFuncNew aNewFunc;

  math_BracketedRoot anOldSolver(anOldFunc, 0.0, 2.0, THE_TOLERANCE, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::Brent(aNewFunc, 0.0, 2.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, std::log(3.0), THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, FunctionRoot_SqrtTwo)
{
  SqrtTwoFuncOld anOldFunc;
  SqrtTwoFuncNew aNewFunc;

  math_FunctionRoot anOldSolver(anOldFunc, 1.5, THE_TOLERANCE, 1.0, 2.0, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::NewtonBounded(aNewFunc, 1.5, 1.0, 2.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, FunctionRoot_SinPi)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_FunctionRoot anOldSolver(anOldFunc, 3.0, THE_TOLERANCE, 2.0, 4.0, 100);

  MathRoot::Config aConfig;
  aConfig.XTolerance                = THE_TOLERANCE;
  MathRoot::ScalarResult aNewResult = MathRoot::NewtonBounded(aNewFunc, 3.0, 2.0, 4.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, IterationCount_NewtonVsBrent)
{
  SqrtTwoFuncNew aFunc;

  MathRoot::Config aConfig;
  aConfig.MaxIterations = 100;

  MathRoot::ScalarResult aNewtonResult = MathRoot::Newton(aFunc, 1.5, aConfig);
  MathRoot::ScalarResult aBrentResult  = MathRoot::Brent(aFunc, 1.0, 2.0, aConfig);

  ASSERT_TRUE(aNewtonResult.IsDone());
  ASSERT_TRUE(aBrentResult.IsDone());

  EXPECT_LE(aNewtonResult.NbIterations, aBrentResult.NbIterations);

  EXPECT_NEAR(*aNewtonResult.Root, *aBrentResult.Root, THE_TOLERANCE);
}

TEST(MathRoot_ComparisonTest, ChallengingCase_CloseToZeroDerivative)
{

  struct CubicNearZeroOld : public math_FunctionWithDerivative
  {
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX - 0.001;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 3.0 * theX * theX;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      Value(theX, theF);
      Derivative(theX, theD);
      return true;
    }
  };

  struct CubicNearZeroNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX * theX - 0.001;
      return true;
    }

    bool Values(double theX, double& theF, double& theDf) const
    {
      theF  = theX * theX * theX - 0.001;
      theDf = 3.0 * theX * theX;
      return true;
    }
  };

  CubicNearZeroOld anOldFunc;
  CubicNearZeroNew aNewFunc;

  math_BracketedRoot anOldSolver(anOldFunc, 0.0, 1.0, THE_TOLERANCE, 100);

  MathRoot::ScalarResult aNewResult = MathRoot::Brent(aNewFunc, 0.0, 1.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Root(), 0.1, 1.0e-6);
  EXPECT_NEAR(*aNewResult.Root, 0.1, 1.0e-6);
  EXPECT_NEAR(anOldSolver.Root(), *aNewResult.Root, THE_TOLERANCE);
}
