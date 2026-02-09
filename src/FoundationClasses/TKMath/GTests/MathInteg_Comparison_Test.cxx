

#include <gtest/gtest.h>

#include <MathInteg_Gauss.hpp>
#include <MathInteg_Kronrod.hpp>

#include <math_Function.hpp>
#include <math_GaussSingleIntegration.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-10;
  constexpr double THE_PI        = 3.14159265358979323846;

  class SinFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::sin(theX);
      return true;
    }
  };

  class QuadraticFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX;
      return true;
    }
  };

  class ExpFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::exp(theX);
      return true;
    }
  };

  class CosFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::cos(theX);
      return true;
    }
  };

  class LogIntegrandOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = 1.0 / (1.0 + theX);
      return true;
    }
  };

  class LinearFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX;
      return true;
    }
  };

  class CubicFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX;
      return true;
    }
  };

  class ConstantFuncOld : public math_Function
  {
  public:
    bool Value(const double, double& theF) override
    {
      theF = 1.0;
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
  };

  struct QuadraticFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX;
      return true;
    }
  };

  struct ExpFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = std::exp(theX);
      return true;
    }
  };

  struct CosFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = std::cos(theX);
      return true;
    }
  };

  struct LogIntegrandNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = 1.0 / (1.0 + theX);
      return true;
    }
  };

  struct LinearFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX;
      return true;
    }
  };

  struct CubicFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX * theX;
      return true;
    }
  };

  struct ConstantFuncNew
  {
    bool Value(double, double& theF) const
    {
      theF = 1.0;
      return true;
    }
  };
} // namespace

TEST(MathInteg_ComparisonTest, Gauss_SinPi)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  const int anOrder = 15;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, THE_PI, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, THE_PI, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Gauss_Quadratic)
{
  QuadraticFuncOld anOldFunc;
  QuadraticFuncNew aNewFunc;

  const int anOrder = 7;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 1.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 1.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 1.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Gauss_Exponential)
{
  ExpFuncOld anOldFunc;
  ExpFuncNew aNewFunc;

  const int anOrder = 15;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 1.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 1.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, std::exp(1.0) - 1.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Gauss_Cosine)
{
  CosFuncOld anOldFunc;
  CosFuncNew aNewFunc;

  const int anOrder = 15;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, THE_PI / 2.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, THE_PI / 2.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 1.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Gauss_LogIntegrand)
{
  LogIntegrandOld anOldFunc;
  LogIntegrandNew aNewFunc;

  const int anOrder = 15;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 1.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 1.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, std::log(2.0), THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Gauss_Linear)
{
  LinearFuncOld anOldFunc;
  LinearFuncNew aNewFunc;

  const int anOrder = 3;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 1.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 1.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.5, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Gauss_Cubic)
{
  CubicFuncOld anOldFunc;
  CubicFuncNew aNewFunc;

  const int anOrder = 7;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 1.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 1.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.25, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Gauss_Constant)
{
  ConstantFuncOld anOldFunc;
  ConstantFuncNew aNewFunc;

  const int anOrder = 3;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 5.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 5.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 5.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Order3_Comparison)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, THE_PI, 3);
  MathInteg::IntegResult      aNewResult = MathInteg::Gauss(aNewFunc, 0.0, THE_PI, 3);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Order5_Comparison)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, THE_PI, 5);
  MathInteg::IntegResult      aNewResult = MathInteg::Gauss(aNewFunc, 0.0, THE_PI, 5);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Order7_Comparison)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, THE_PI, 7);
  MathInteg::IntegResult      aNewResult = MathInteg::Gauss(aNewFunc, 0.0, THE_PI, 7);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Order15_Comparison)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, THE_PI, 15);
  MathInteg::IntegResult      aNewResult = MathInteg::Gauss(aNewFunc, 0.0, THE_PI, 15);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, Order21_Comparison)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, THE_PI, 21);
  MathInteg::IntegResult      aNewResult = MathInteg::Gauss(aNewFunc, 0.0, THE_PI, 21);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, HigherOrderMoreAccurate)
{
  ExpFuncNew aFunc;

  const double aExact = std::exp(1.0) - 1.0;

  MathInteg::IntegResult aResult3  = MathInteg::Gauss(aFunc, 0.0, 1.0, 3);
  MathInteg::IntegResult aResult7  = MathInteg::Gauss(aFunc, 0.0, 1.0, 7);
  MathInteg::IntegResult aResult15 = MathInteg::Gauss(aFunc, 0.0, 1.0, 15);

  ASSERT_TRUE(aResult3.IsDone());
  ASSERT_TRUE(aResult7.IsDone());
  ASSERT_TRUE(aResult15.IsDone());

  const double aError3  = std::abs(*aResult3.Value - aExact);
  const double aError7  = std::abs(*aResult7.Value - aExact);
  const double aError15 = std::abs(*aResult15.Value - aExact);

  EXPECT_LE(aError7, aError3 + 1.0e-15);
  EXPECT_LE(aError15, aError7 + 1.0e-15);
}

TEST(MathInteg_ComparisonTest, NegativeBounds)
{
  QuadraticFuncOld anOldFunc;
  QuadraticFuncNew aNewFunc;

  const int anOrder = 7;

  math_GaussSingleIntegration anOldInteg(anOldFunc, -1.0, 1.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, -1.0, 1.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 2.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, ReversedBounds)
{
  SinFuncNew aFunc;

  MathInteg::IntegResult aResultNormal = MathInteg::Gauss(aFunc, 0.0, THE_PI, 15);

  MathInteg::IntegResult aResultReversed = MathInteg::Gauss(aFunc, THE_PI, 0.0, 15);

  ASSERT_TRUE(aResultNormal.IsDone());
  ASSERT_TRUE(aResultReversed.IsDone());

  EXPECT_NEAR(*aResultNormal.Value, -*aResultReversed.Value, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, PolynomialExactness_Order3)
{

  struct Poly5Func
  {
    bool Value(double theX, double& theF) const
    {
      const double aX2 = theX * theX;
      theF             = aX2 * aX2 * theX;
      return true;
    }
  };

  Poly5Func aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 1.0, 3);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0 / 6.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, PolynomialExactness_Order7)
{

  struct Poly7Func
  {
    bool Value(double theX, double& theF) const
    {
      const double aX2 = theX * theX;
      const double aX4 = aX2 * aX2;
      theF             = aX4 * aX2 * theX;
      return true;
    }
  };

  Poly7Func aFunc;

  MathInteg::IntegResult aResult = MathInteg::Gauss(aFunc, 0.0, 1.0, 7);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0 / 8.0, THE_TOLERANCE);
}

TEST(MathInteg_ComparisonTest, LargeInterval)
{
  ExpFuncOld anOldFunc;
  ExpFuncNew aNewFunc;

  const int anOrder = 21;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 10.0, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 10.0, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, 1.0e-6);
  EXPECT_NEAR(*aNewResult.Value, std::exp(10.0) - 1.0, 1.0e-6);
}

TEST(MathInteg_ComparisonTest, SmallInterval)
{
  SinFuncOld anOldFunc;
  SinFuncNew aNewFunc;

  const int anOrder = 15;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 0.001, anOrder);

  MathInteg::IntegResult aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 0.001, anOrder);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, THE_TOLERANCE);

  EXPECT_NEAR(*aNewResult.Value, 0.0000005, 1.0e-12);
}
