

#include <gtest/gtest.h>

#include <MathInteg_Kronrod.hpp>
#include <MathInteg_DoubleExp.hpp>
#include <MathInteg_Gauss.hpp>
#include <math_KronrodSingleIntegration.hpp>
#include <math_GaussSingleIntegration.hpp>
#include <math_Function.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-8;

  struct PolynomialFunc
  {
    bool Value(double theX, double& theF)
    {
      theF = theX * theX;
      return true;
    }
  };

  struct SineFunc
  {
    bool Value(double theX, double& theF)
    {
      theF = std::sin(theX);
      return true;
    }
  };

  struct GaussianFunc
  {
    bool Value(double theX, double& theF)
    {
      theF = std::exp(-theX * theX);
      return true;
    }
  };

  struct OscillatoryFunc
  {
    bool Value(double theX, double& theF)
    {
      theF = std::cos(10.0 * theX);
      return true;
    }
  };

  struct SqrtSingularityFunc
  {
    bool Value(double theX, double& theF)
    {
      if (theX <= 0.0)
      {
        return false;
      }
      theF = 1.0 / std::sqrt(theX);
      return true;
    }
  };

  struct LogSingularityFunc
  {
    bool Value(double theX, double& theF)
    {
      if (theX <= 0.0)
      {
        return false;
      }
      theF = -std::log(theX);
      return true;
    }
  };

  struct ExponentialDecayFunc
  {
    bool Value(double theX, double& theF)
    {
      theF = std::exp(-theX);
      return true;
    }
  };

  struct InfiniteGaussianFunc
  {
    bool Value(double theX, double& theF)
    {
      theF = std::exp(-theX * theX);
      return true;
    }
  };

  class SineFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::sin(theX);
      return true;
    }
  };

  class PolynomialFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX;
      return true;
    }
  };

} // namespace

TEST(MathInteg_Kronrod_NewTest, KronrodRule_Polynomial)
{
  PolynomialFunc aFunc;

  auto aResult = MathInteg::KronrodRule(aFunc, 0.0, 1.0, 7);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0 / 3.0, THE_TOLERANCE);
}

TEST(MathInteg_Kronrod_NewTest, KronrodRule_Sine)
{
  SineFunc aFunc;

  auto aResult = MathInteg::KronrodRule(aFunc, 0.0, M_PI, 7);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathInteg_Kronrod_NewTest, AdaptiveKronrod_Oscillatory)
{
  OscillatoryFunc aFunc;

  MathInteg::KronrodConfig aConfig;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.NbGaussPoints = 7;
  aConfig.Adaptive      = true;
  aConfig.MaxIterations = 100;

  auto aResult = MathInteg::Kronrod(aFunc, 0.0, M_PI, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-6);
}

TEST(MathInteg_Kronrod_NewTest, AdaptiveKronrod_Gaussian)
{
  GaussianFunc aFunc;

  MathInteg::DoubleExpConfig aConfig;
  aConfig.Tolerance = 1.0e-10;

  auto aResult = MathInteg::SinhSinh(aFunc, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, std::sqrt(M_PI), 1.0e-6);
}

TEST(MathInteg_Kronrod_NewTest, KronrodAuto)
{
  SineFunc aFunc;

  auto aResult = MathInteg::KronrodAuto(aFunc, 0.0, 2.0 * M_PI);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
}

TEST(MathInteg_Kronrod_NewTest, DifferentOrders)
{
  PolynomialFunc aFunc;

  int aOrders[] = {3, 5, 7, 10, 15};

  for (int aOrder : aOrders)
  {
    auto aResult = MathInteg::KronrodRule(aFunc, 0.0, 1.0, aOrder);

    ASSERT_TRUE(aResult.IsDone()) << "Failed with order " << aOrder;
    EXPECT_NEAR(*aResult.Value, 1.0 / 3.0, 1.0e-8) << "Failed with order " << aOrder;
  }
}

TEST(MathInteg_DoubleExp_NewTest, TanhSinh_Polynomial)
{
  PolynomialFunc aFunc;

  auto aResult = MathInteg::TanhSinh(aFunc, 0.0, 1.0);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0 / 3.0, 1.0e-6);
}

TEST(MathInteg_DoubleExp_NewTest, TanhSinh_Sine)
{
  SineFunc aFunc;

  auto aResult = MathInteg::TanhSinh(aFunc, 0.0, M_PI);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, 1.0e-6);
}

TEST(MathInteg_DoubleExp_NewTest, TanhSinh_SqrtSingularity)
{
  SqrtSingularityFunc aFunc;

  MathInteg::DoubleExpConfig aConfig;
  aConfig.NbLevels = 8;

  auto aResult = MathInteg::TanhSinh(aFunc, 0.0, 1.0, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, 1.0e-4);
}

TEST(MathInteg_DoubleExp_NewTest, TanhSinh_LogSingularity)
{
  LogSingularityFunc aFunc;

  MathInteg::DoubleExpConfig aConfig;
  aConfig.NbLevels = 8;

  auto aResult = MathInteg::TanhSinh(aFunc, 0.0, 1.0, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0, 1.0e-4);
}

TEST(MathInteg_DoubleExp_NewTest, TanhSinhSingular)
{
  SqrtSingularityFunc aFunc;

  auto aResult = MathInteg::TanhSinhSingular(aFunc, 0.0, 1.0, 1.0e-6);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, 1.0e-3);
}

TEST(MathInteg_DoubleExp_NewTest, ExpSinh_SemiInfinite)
{
  ExponentialDecayFunc aFunc;

  auto aResult = MathInteg::ExpSinh(aFunc, 0.0);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0, 1.0e-4);
}

TEST(MathInteg_DoubleExp_NewTest, SinhSinh_Infinite)
{
  InfiniteGaussianFunc aFunc;

  auto aResult = MathInteg::SinhSinh(aFunc);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, std::sqrt(M_PI), 1.0e-4);
}

TEST(MathInteg_DoubleExp_NewTest, DoubleExponential_Auto)
{
  SineFunc aFunc;

  auto aResult = MathInteg::DoubleExponential(aFunc, 0.0, M_PI);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 2.0, 1.0e-6);
}

TEST(MathInteg_DoubleExp_NewTest, WithSingularity)
{

  struct SingularFunc
  {
    bool Value(double theX, double& theF)
    {
      const double aDist = std::abs(theX - 0.5);
      if (aDist < 1.0e-10)
      {
        return false;
      }
      theF = 1.0 / std::sqrt(aDist);
      return true;
    }
  };

  SingularFunc aFunc;

  auto aResult = MathInteg::TanhSinhWithSingularity(aFunc, 0.0, 1.0, 0.5);

  ASSERT_TRUE(aResult.IsDone());

  EXPECT_GT(*aResult.Value, 0.0);
}

TEST(MathInteg_NewTest, KronrodVsGauss_Polynomial)
{
  PolynomialFunc aFunc;

  auto aKronrodResult = MathInteg::KronrodRule(aFunc, 0.0, 1.0, 7);
  auto aGaussResult   = MathInteg::Gauss(aFunc, 0.0, 1.0, 15);

  ASSERT_TRUE(aKronrodResult.IsDone());
  ASSERT_TRUE(aGaussResult.IsDone());

  EXPECT_NEAR(*aKronrodResult.Value, *aGaussResult.Value, 1.0e-10);
}

TEST(MathInteg_NewTest, KronrodVsGauss_Sine)
{
  SineFunc aFunc;

  auto aKronrodResult = MathInteg::KronrodRule(aFunc, 0.0, M_PI, 7);
  auto aGaussResult   = MathInteg::Gauss(aFunc, 0.0, M_PI, 15);

  ASSERT_TRUE(aKronrodResult.IsDone());
  ASSERT_TRUE(aGaussResult.IsDone());

  EXPECT_NEAR(*aKronrodResult.Value, *aGaussResult.Value, 1.0e-10);
}

TEST(MathInteg_NewTest, TanhSinhVsKronrod_Polynomial)
{
  PolynomialFunc aFunc;

  auto aTanhSinhResult = MathInteg::TanhSinh(aFunc, 0.0, 1.0);
  auto aKronrodResult  = MathInteg::KronrodRule(aFunc, 0.0, 1.0, 7);

  ASSERT_TRUE(aTanhSinhResult.IsDone());
  ASSERT_TRUE(aKronrodResult.IsDone());

  EXPECT_NEAR(*aTanhSinhResult.Value, *aKronrodResult.Value, 1.0e-6);
}

TEST(MathInteg_NewTest, CompareWithOldAPI_Kronrod)
{
  SineFuncOld anOldFunc;
  SineFunc    aNewFunc;

  math_KronrodSingleIntegration anOldInteg(anOldFunc, 0.0, M_PI, 15, 1.0e-10, 100);

  MathInteg::KronrodConfig aConfig;
  aConfig.NbGaussPoints = 7;
  aConfig.Tolerance     = 1.0e-10;
  aConfig.Adaptive      = true;
  auto aNewResult       = MathInteg::Kronrod(aNewFunc, 0.0, M_PI, aConfig);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, 1.0e-8);
  EXPECT_NEAR(*aNewResult.Value, 2.0, 1.0e-8);
}

TEST(MathInteg_NewTest, CompareWithOldAPI_Gauss)
{
  PolynomialFuncOld anOldFunc;
  PolynomialFunc    aNewFunc;

  math_GaussSingleIntegration anOldInteg(anOldFunc, 0.0, 1.0, 15);

  auto aNewResult = MathInteg::Gauss(aNewFunc, 0.0, 1.0, 15);

  ASSERT_TRUE(anOldInteg.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldInteg.Value(), *aNewResult.Value, 1.0e-10);
}

TEST(MathInteg_NewTest, ErrorEstimation_Kronrod)
{
  SineFunc aFunc;

  auto aResult = MathInteg::KronrodRule(aFunc, 0.0, M_PI, 7);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.AbsoluteError.has_value());
  EXPECT_TRUE(aResult.RelativeError.has_value());

  EXPECT_LT(*aResult.AbsoluteError, 1.0e-10);
}

TEST(MathInteg_NewTest, ErrorEstimation_TanhSinh)
{
  SineFunc aFunc;

  auto aResult = MathInteg::TanhSinh(aFunc, 0.0, M_PI);

  ASSERT_TRUE(aResult.IsDone());
}

TEST(MathInteg_Kronrod_NewTest, InfiniteInterval)
{
  InfiniteGaussianFunc aFunc;

  auto aResult = MathInteg::SinhSinh(aFunc);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, std::sqrt(M_PI), 1.0e-4);
}

TEST(MathInteg_Kronrod_NewTest, SemiInfiniteInterval)
{
  ExponentialDecayFunc aFunc;

  auto aResult = MathInteg::ExpSinh(aFunc, 0.0);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Value, 1.0, 1.0e-4);
}
