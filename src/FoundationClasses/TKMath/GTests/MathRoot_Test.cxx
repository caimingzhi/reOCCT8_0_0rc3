

#include <gtest/gtest.h>

#include <MathRoot_Newton.hpp>
#include <MathRoot_Brent.hpp>
#include <MathRoot_Bisection.hpp>
#include <MathRoot_Secant.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-10;
  constexpr double THE_PI        = 3.14159265358979323846;

  class SqrtTwoFunc
  {
  public:
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

  class CosMinusXFunc
  {
  public:
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

  class CubicFunc
  {
  public:
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

  class SinFunc
  {
  public:
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

  class ExpMinusThreeFunc
  {
  public:
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

  class LinearFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = 2.0 * theX - 4.0;
      return true;
    }

    bool Values(double theX, double& theF, double& theDf) const
    {
      theF  = 2.0 * theX - 4.0;
      theDf = 2.0;
      return true;
    }
  };
} // namespace

TEST(MathRoot_NewtonTest, SqrtTwo)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_NewtonTest, CosMinusX)
{
  CosMinusXFunc          aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 0.5);
  ASSERT_TRUE(aResult.IsDone());

  double aFx = std::cos(*aResult.Root) - *aResult.Root;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_NewtonTest, CubicEquation)
{
  CubicFunc              aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 1.5);
  ASSERT_TRUE(aResult.IsDone());

  double aFx = *aResult.Root * *aResult.Root * *aResult.Root - *aResult.Root - 2.0;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_NewtonTest, LinearFunction)
{
  LinearFunc             aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 2.0, THE_TOLERANCE);
}

TEST(MathRoot_NewtonTest, ExpFunction)
{
  ExpMinusThreeFunc      aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::log(3.0), THE_TOLERANCE);
}

TEST(MathRoot_NewtonTest, CustomTolerance)
{
  SqrtTwoFunc      aFunc;
  MathRoot::Config aConfig;
  aConfig.XTolerance    = 1.0e-14;
  aConfig.FTolerance    = 1.0e-14;
  aConfig.MaxIterations = 100;

  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 1.0, aConfig);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), 1.0e-14);
}

TEST(MathRoot_NewtonBoundedTest, SqrtTwoWithBounds)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::NewtonBounded(aFunc, 1.5, 1.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_NewtonBoundedTest, SinWithBounds)
{
  SinFunc                aFunc;
  MathRoot::ScalarResult aResult = MathRoot::NewtonBounded(aFunc, 3.0, 2.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_SecantTest, SqrtTwo)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Secant(aFunc, 1.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_SecantTest, CosMinusX)
{
  CosMinusXFunc          aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Secant(aFunc, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  double aFx = std::cos(*aResult.Root) - *aResult.Root;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_SecantTest, ExpFunction)
{
  ExpMinusThreeFunc      aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Secant(aFunc, 0.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::log(3.0), THE_TOLERANCE);
}

TEST(MathRoot_BrentTest, SqrtTwo)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 1.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_BrentTest, CosMinusX)
{
  CosMinusXFunc          aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  double aFx = std::cos(*aResult.Root) - *aResult.Root;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_BrentTest, CubicEquation)
{
  CubicFunc              aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 1.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  double aFx = *aResult.Root * *aResult.Root * *aResult.Root - *aResult.Root - 2.0;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_BrentTest, SinPi)
{
  SinFunc                aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 2.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_BrentTest, ExpFunction)
{
  ExpMinusThreeFunc      aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 0.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::log(3.0), THE_TOLERANCE);
}

TEST(MathRoot_BrentTest, InvalidBracket)
{
  SqrtTwoFunc aFunc;

  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 2.0, 3.0);
  EXPECT_EQ(aResult.Status, MathRoot::Status::InvalidInput);
}

TEST(MathRoot_BrentTest, ReversedBracket)
{
  SqrtTwoFunc aFunc;

  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 2.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_BisectionTest, SqrtTwo)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Bisection(aFunc, 1.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_BisectionTest, CosMinusX)
{
  CosMinusXFunc          aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Bisection(aFunc, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  double aFx = std::cos(*aResult.Root) - *aResult.Root;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_BisectionTest, SinPi)
{
  SinFunc                aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Bisection(aFunc, 2.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_BisectionTest, InvalidBracket)
{
  SqrtTwoFunc aFunc;

  MathRoot::ScalarResult aResult = MathRoot::Bisection(aFunc, 2.0, 3.0);
  EXPECT_EQ(aResult.Status, MathRoot::Status::InvalidInput);
}

TEST(MathRoot_BisectionNewtonTest, SqrtTwo)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::BisectionNewton(aFunc, 1.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), THE_TOLERANCE);
}

TEST(MathRoot_BisectionNewtonTest, CosMinusX)
{
  CosMinusXFunc          aFunc;
  MathRoot::ScalarResult aResult = MathRoot::BisectionNewton(aFunc, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  double aFx = std::cos(*aResult.Root) - *aResult.Root;
  EXPECT_NEAR(aFx, 0.0, THE_TOLERANCE);
}

TEST(MathRoot_BisectionNewtonTest, FasterThanPureBisection)
{
  SqrtTwoFunc      aFunc;
  MathRoot::Config aConfig;
  aConfig.MaxIterations = 100;

  MathRoot::ScalarResult aBisec  = MathRoot::Bisection(aFunc, 1.0, 2.0, aConfig);
  MathRoot::ScalarResult aHybrid = MathRoot::BisectionNewton(aFunc, 1.0, 2.0, aConfig);

  ASSERT_TRUE(aBisec.IsDone());
  ASSERT_TRUE(aHybrid.IsDone());

  EXPECT_LE(aHybrid.NbIterations, aBisec.NbIterations);
}

TEST(MathRoot_ConvergenceTest, NewtonIterationCount)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 1.0);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_LT(aResult.NbIterations, 15);
}

TEST(MathRoot_ConvergenceTest, BrentIterationCount)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 1.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_LT(aResult.NbIterations, 50);
}

TEST(MathRoot_BoolConversionTest, SuccessfulResultIsTrue)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Newton(aFunc, 1.0);
  EXPECT_TRUE(static_cast<bool>(aResult));
}

TEST(MathRoot_BoolConversionTest, InvalidInputIsFalse)
{
  SqrtTwoFunc            aFunc;
  MathRoot::ScalarResult aResult = MathRoot::Brent(aFunc, 2.0, 3.0);
  EXPECT_FALSE(static_cast<bool>(aResult));
}
