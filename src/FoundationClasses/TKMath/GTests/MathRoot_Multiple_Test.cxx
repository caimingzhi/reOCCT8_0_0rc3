

#include <gtest/gtest.h>

#include <MathRoot_Multiple.hpp>
#include <MathUtils_FunctorScalar.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1e-8;
  constexpr double THE_PI        = 3.14159265358979323846;
} // namespace

TEST(MathRoot_Multiple, FindAllRoots_NoRoots)
{

  MathUtils::Polynomial aFunc({1.0, 0.0, 1.0});

  auto aResult = MathRoot::FindAllRoots(aFunc, -10.0, 10.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 0u);
}

TEST(MathRoot_Multiple, FindAllRoots_SingleRoot)
{

  MathUtils::Polynomial aFunc({-2.0, 1.0});

  auto aResult = MathRoot::FindAllRoots(aFunc, 0.0, 5.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 1u);
  EXPECT_NEAR(aResult.Roots[0], 2.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRoots_TwoRoots)
{

  MathUtils::Polynomial aFunc({-4.0, 0.0, 1.0});

  auto aResult = MathRoot::FindAllRoots(aFunc, -5.0, 5.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 2u);
  EXPECT_NEAR(aResult.Roots[0], -2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRoots_ThreeRoots)
{

  MathUtils::Polynomial aFunc({-6.0, 11.0, -6.0, 1.0});

  auto aResult = MathRoot::FindAllRoots(aFunc, 0.0, 4.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 3u);
  EXPECT_NEAR(aResult.Roots[0], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 3.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRoots_SineFunction)
{

  MathUtils::Sine aSine;

  MathRoot::MultipleConfig aConfig;
  aConfig.NbSamples  = 200;
  aConfig.FTolerance = 1e-10;

  auto aResult = MathRoot::FindAllRoots(aSine, 0.0, 10.0, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 4u);

  EXPECT_NEAR(aResult.Roots[0], 0.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], THE_PI, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 2.0 * THE_PI, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[3], 3.0 * THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRoots_WithOffset)
{

  MathUtils::Polynomial aFunc({0.0, 0.0, 1.0});

  MathRoot::MultipleConfig aConfig;
  aConfig.Offset = 4.0;

  auto aResult = MathRoot::FindAllRoots(aFunc, -5.0, 5.0, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 2u);
  EXPECT_NEAR(aResult.Roots[0], -2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRoots_CloseRoots)
{

  MathUtils::Polynomial aFunc({1.01, -2.01, 1.0});

  MathRoot::MultipleConfig aConfig;
  aConfig.NbSamples  = 500;
  aConfig.XTolerance = 1e-4;

  auto aResult = MathRoot::FindAllRoots(aFunc, 0.0, 2.0, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 2u);
  EXPECT_NEAR(aResult.Roots[0], 1.0, 1e-3);
  EXPECT_NEAR(aResult.Roots[1], 1.01, 1e-3);
}

TEST(MathRoot_Multiple, FindAllRoots_NullFunction)
{

  MathUtils::Constant aFunc(0.0);

  MathRoot::MultipleConfig aConfig;
  aConfig.NullTolerance = 1e-10;

  auto aResult = MathRoot::FindAllRoots(aFunc, -1.0, 1.0, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.IsAllNull);
}

TEST(MathRoot_Multiple, FindAllRoots_LambdaFunction)
{

  auto aFunc = MathUtils::MakeScalar(
    [](double x, double& y)
    {
      y = std::cos(x) - 0.5;
      return true;
    });

  MathRoot::MultipleConfig aConfig;
  aConfig.NbSamples = 100;

  auto aResult = MathRoot::FindAllRoots(aFunc, 0.0, 2.0 * THE_PI, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 2u);

  EXPECT_NEAR(aResult.Roots[0], THE_PI / 3.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 5.0 * THE_PI / 3.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRootsWithDerivative_ThreeRoots)
{

  MathUtils::Polynomial aFunc({-6.0, 11.0, -6.0, 1.0});

  auto aResult = MathRoot::FindAllRootsWithDerivative(aFunc, 0.0, 4.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 3u);
  EXPECT_NEAR(aResult.Roots[0], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 3.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRootsWithDerivative_DoubleRoot)
{

  MathUtils::Polynomial aFunc({4.0, -4.0, 1.0});

  MathRoot::MultipleConfig aConfig;
  aConfig.NbSamples  = 100;
  aConfig.FTolerance = 1e-8;

  auto aResult = MathRoot::FindAllRootsWithDerivative(aFunc, 0.0, 4.0, aConfig);
  EXPECT_TRUE(aResult.IsDone());

  EXPECT_GE(aResult.NbRoots(), 1u);
  if (aResult.NbRoots() > 0)
  {
    EXPECT_NEAR(aResult.Roots[0], 2.0, 1e-4);
  }
}

TEST(MathRoot_Multiple, FindAllRootsWithDerivative_SineFunction)
{

  class SineWithDerivative
  {
  public:
    bool Value(double theX, double& theY) const
    {
      theY = std::sin(theX);
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      theY  = std::sin(theX);
      theDY = std::cos(theX);
      return true;
    }
  };

  SineWithDerivative aSine;

  MathRoot::MultipleConfig aConfig;
  aConfig.NbSamples = 200;

  auto aResult = MathRoot::FindAllRootsWithDerivative(aSine, 0.0, 7.0, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 3u);

  EXPECT_NEAR(aResult.Roots[0], 0.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], THE_PI, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 2.0 * THE_PI, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, CompareWithLegacy_Polynomial)
{

  MathUtils::Polynomial aFunc({-6.0, 11.0, -6.0, 1.0});

  MathRoot::MultipleConfig aConfig;
  aConfig.NbSamples  = 50;
  aConfig.XTolerance = 1e-10;
  aConfig.FTolerance = 1e-10;

  auto aResult = MathRoot::FindAllRoots(aFunc, 0.5, 3.5, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 3u);

  for (int i = 0; i < aResult.NbRoots(); ++i)
  {
    double aValue = 0.0;
    aFunc.Value(aResult.Roots[i], aValue);
    EXPECT_NEAR(aValue, 0.0, 1e-9);
  }
}

TEST(MathRoot_Multiple, CompareWithLegacy_HigherDegree)
{

  MathUtils::Polynomial aFunc({9.0, 0.0, -10.0, 0.0, 1.0});

  MathRoot::MultipleConfig aConfig;
  aConfig.NbSamples = 100;

  auto aResult = MathRoot::FindAllRoots(aFunc, -5.0, 5.0, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 4u);

  EXPECT_NEAR(aResult.Roots[0], -3.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], -1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[3], 3.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRoots_ConvenienceOverload)
{

  MathUtils::Polynomial aFunc({-4.0, 0.0, 1.0});

  auto aResult = MathRoot::FindAllRoots(aFunc, -5.0, 5.0, 50);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 2u);
  EXPECT_NEAR(aResult.Roots[0], -2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
}

TEST(MathRoot_Multiple, FindAllRoots_Exponential)
{

  auto aFunc = MathUtils::MakeScalar(
    [](double x, double& y)
    {
      y = std::exp(x) - 2.0;
      return true;
    });

  auto aResult = MathRoot::FindAllRoots(aFunc, -1.0, 2.0, 50);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots(), 1u);
  EXPECT_NEAR(aResult.Roots[0], std::log(2.0), THE_TOLERANCE);
}
