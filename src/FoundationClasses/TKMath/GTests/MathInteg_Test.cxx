

#include <gtest/gtest.h>

#include <MathInteg_Gauss.hpp>
#include <MathInteg_Kronrod.hpp>
#include <MathInteg_DoubleExp.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-10;
  constexpr double THE_PI        = 3.14159265358979323846;

  class ConstantFunc
  {
  public:
    bool Value(double, double& theF) const
    {
      theF = 5.0;
      return true;
    }
  };

  class LinearFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = 2.0 * theX + 1.0;
      return true;
    }
  };

  class QuadraticFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX;
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
  };

  class CosFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::cos(theX);
      return true;
    }
  };

  class ExpFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::exp(theX);
      return true;
    }
  };

  class PolynomialFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      const double aX2 = theX * theX;
      const double aX3 = aX2 * theX;
      theF             = aX2 * aX3 - 3.0 * aX3 + 2.0 * theX;
      return true;
    }
  };

  class GaussianFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::exp(-theX * theX);
      return true;
    }
  };

  class ReciprocalFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = 1.0 / theX;
      return true;
    }
  };

  class OscillatoryFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::sin(10.0 * theX);
      return true;
    }
  };

  class SqrtFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::sqrt(theX);
      return true;
    }
  };
} // namespace

TEST(MathInteg_GaussTest, ConstantFunction)
{
  ConstantFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 2.0, 3);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 10.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, LinearFunction)
{
  LinearFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 3.0, 3);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 12.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, QuadraticFunction)
{
  QuadraticFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 1.0, 3);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, SineFunction)
{
  SinFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, THE_PI, 15);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, CosineFunction)
{
  CosFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, THE_PI / 2.0, 15);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, ExponentialFunction)
{
  ExpFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 1.0, 15);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, std::exp(1.0) - 1.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, ReciprocalFunction)
{
  ReciprocalFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 1.0, std::exp(1.0), 15);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, Order3)
{
  QuadraticFunc          aFunc;
  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 1.0, 3);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbPoints, 3);
  EXPECT_NEAR(*aResult.Value, 1.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, Order5)
{
  QuadraticFunc          aFunc;
  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 1.0, 5);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbPoints, 5);
  EXPECT_NEAR(*aResult.Value, 1.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, Order7)
{
  QuadraticFunc          aFunc;
  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 1.0, 7);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbPoints, 7);
  EXPECT_NEAR(*aResult.Value, 1.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, Order15)
{
  SinFunc                aFunc;
  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, THE_PI, 15);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbPoints, 15);
  EXPECT_NEAR(*aResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, Order21)
{
  SinFunc                aFunc;
  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, THE_PI, 21);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbPoints, 21);
  EXPECT_NEAR(*aResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, InvalidOrder)
{
  SinFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, THE_PI, 9);
  EXPECT_EQ(aResult.Status, MathInteg::Status::InvalidInput);
}

TEST(MathInteg_GaussTest, PolynomialExactness_Order3)
{

  PolynomialFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, -1.0, 1.0, 3);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussTest, PolynomialExactness_Order7)
{

  PolynomialFunc         aFunc;
  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, -1.0, 1.0, 7);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathInteg_GaussAdaptiveTest, SineFunction)
{
  SinFunc                aFunc;
  MathInteg::IntegConfig aConfig;
  aConfig.Tolerance = 1.0e-12;

  MathInteg::IntegResult aResult = MathInteg::GaussAdaptive(aFunc, 0.0, THE_PI, aConfig);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, 1.0e-11);
}

TEST(MathInteg_GaussAdaptiveTest, ExponentialFunction)
{
  ExpFunc                aFunc;
  MathInteg::IntegConfig aConfig;
  aConfig.Tolerance = 1.0e-12;

  MathInteg::IntegResult aResult = MathInteg::GaussAdaptive(aFunc, 0.0, 1.0, aConfig);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, std::exp(1.0) - 1.0, 1.0e-11);
}

TEST(MathInteg_GaussAdaptiveTest, OscillatoryFunction)
{
  OscillatoryFunc        aFunc;
  MathInteg::IntegConfig aConfig;
  aConfig.Tolerance     = 1.0e-8;
  aConfig.MaxIterations = 20;

  MathInteg::IntegResult aResult = MathInteg::GaussAdaptive(aFunc, 0.0, THE_PI, aConfig);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-6);
}

TEST(MathInteg_GaussAdaptiveTest, ProvidesErrorEstimate)
{
  SinFunc                aFunc;
  MathInteg::IntegConfig aConfig;
  aConfig.Tolerance = 1.0e-8;

  MathInteg::IntegResult aResult = MathInteg::GaussAdaptive(aFunc, 0.0, THE_PI, aConfig);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GT(aResult.AbsoluteError, 0.0);
  EXPECT_LT(aResult.AbsoluteError, 1.0e-6);
}

TEST(MathInteg_GaussCompositeTest, SineFunction)
{
  SinFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::GaussComposite(aFunc, 0.0, THE_PI, 10, 7);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, THE_TOLERANCE);
  EXPECT_EQ(aResult.NbPoints, 70);
}

TEST(MathInteg_GaussCompositeTest, OscillatoryFunction)
{
  OscillatoryFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::GaussComposite(aFunc, 0.0, THE_PI, 50, 7);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
}

TEST(MathInteg_GaussCompositeTest, GaussianFunction)
{
  GaussianFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::GaussComposite(aFunc, -3.0, 3.0, 50, 15);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_NEAR(*aResult.Value, std::sqrt(THE_PI), 1.0e-4);
}

TEST(MathInteg_GaussCompositeTest, InvalidSubintervals)
{
  SinFunc                aFunc;
  MathInteg::IntegResult aResult = MathInteg::GaussComposite(aFunc, 0.0, THE_PI, 0, 7);
  EXPECT_EQ(aResult.Status, MathInteg::Status::InvalidInput);
}

TEST(MathInteg_BoundsTest, ReversedBounds)
{
  SinFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, THE_PI, 0.0, 15);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, -2.0, THE_TOLERANCE);
}

TEST(MathInteg_BoundsTest, NegativeBounds)
{
  QuadraticFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, -1.0, 1.0, 7);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_BoundsTest, SmallInterval)
{
  SinFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 0.001, 15);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_NEAR(*aResult.Value, 0.0000005, 1.0e-10);
}

TEST(MathInteg_BoundsTest, LargeInterval)
{

  class LorentzianFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = 1.0 / (1.0 + theX * theX);
      return true;
    }
  };

  LorentzianFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::GaussComposite(aFunc, -100.0, 100.0, 200, 15);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, THE_PI, 0.05);
}

TEST(MathInteg_SpecialTest, SqrtFunction)
{
  SqrtFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::GaussComposite(aFunc, 0.001, 1.0, 20, 15);
  ASSERT_TRUE(aResult.IsDone());

  const double aExpected = (2.0 / 3.0) * (1.0 - std::pow(0.001, 1.5));
  EXPECT_NEAR(*aResult.Value, aExpected, 1.0e-6);
}

TEST(MathInteg_BoolConversionTest, SuccessfulResultIsTrue)
{
  SinFunc                aFunc;
  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, THE_PI, 15);
  EXPECT_TRUE(static_cast<bool>(aResult));
}

TEST(MathInteg_BoolConversionTest, InvalidInputIsFalse)
{
  SinFunc aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, THE_PI, 9);
  EXPECT_FALSE(static_cast<bool>(aResult));
}

TEST(MathInteg_AccuracyTest, HigherOrderMoreAccurate)
{
  SinFunc      aFunc;
  const double aExact = 2.0;

  MathInteg::IntegResult aResult3  = MathInteg::Gauss(aFunc, 0.0, THE_PI, 3);
  MathInteg::IntegResult aResult7  = MathInteg::Gauss(aFunc, 0.0, THE_PI, 7);
  MathInteg::IntegResult aResult15 = MathInteg::Gauss(aFunc, 0.0, THE_PI, 15);

  ASSERT_TRUE(aResult3.IsDone());
  ASSERT_TRUE(aResult7.IsDone());
  ASSERT_TRUE(aResult15.IsDone());

  double aError3  = std::abs(*aResult3.Value - aExact);
  double aError7  = std::abs(*aResult7.Value - aExact);
  double aError15 = std::abs(*aResult15.Value - aExact);

  EXPECT_GT(aError3, aError7);
  EXPECT_GT(aError7, aError15);
}
