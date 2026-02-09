

#include <gtest/gtest.h>

#include <MathRoot_Trig.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOL = 1.0e-10;
  constexpr double THE_PI  = 3.14159265358979323846;
  constexpr double THE_2PI = 2.0 * THE_PI;

  double evaluateEquation(double theA,
                          double theB,
                          double theC,
                          double theD,
                          double theE,
                          double theX)
  {
    double aCos = std::cos(theX);
    double aSin = std::sin(theX);
    return theA * aCos * aCos + 2.0 * theB * aCos * aSin + theC * aCos + theD * aSin + theE;
  }

  void verifyRoots(const MathRoot::TrigResult& theResult,
                   double                      theA,
                   double                      theB,
                   double                      theC,
                   double                      theD,
                   double                      theE,
                   double                      theTol = 1.0e-10)
  {
    for (int i = 0; i < theResult.NbRoots; ++i)
    {
      double aVal = evaluateEquation(theA, theB, theC, theD, theE, theResult.Roots[i]);
      EXPECT_NEAR(aVal, 0.0, theTol)
        << "Root " << i << " = " << theResult.Roots[i] << " gives f(x) = " << aVal;
    }
  }

} // namespace

TEST(MathRoot_TrigTest, LinearSin_ZeroConstant)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 0.0, 1.0, 0.0);
}

TEST(MathRoot_TrigTest, LinearSin_HalfValue)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, -0.5);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 0.0, 1.0, -0.5);
}

TEST(MathRoot_TrigTest, LinearSin_NegativeHalf)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, 0.5);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 0.0, 1.0, 0.5);
}

TEST(MathRoot_TrigTest, LinearSin_NoSolution)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, -2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 0);
}

TEST(MathRoot_TrigTest, LinearSin_BoundaryValue)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, -1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 1);
  verifyRoots(aResult, 0.0, 0.0, 0.0, 1.0, -1.0);
}

TEST(MathRoot_TrigTest, LinearCos_ZeroConstant)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.0, 1.0, 0.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 1.0, 0.0, 0.0);
}

TEST(MathRoot_TrigTest, LinearCos_HalfValue)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.0, 1.0, 0.0, -0.5);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 1.0, 0.0, -0.5);
}

TEST(MathRoot_TrigTest, LinearCos_NoSolution)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.0, 1.0, 0.0, -2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 0);
}

TEST(MathRoot_TrigTest, CDE_CosPlusSin)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricCDE(1.0, 1.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 1.0, 1.0, 0.0);
}

TEST(MathRoot_TrigTest, CDE_CosPlusSinEqualsSqrt2)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricCDE(1.0, 1.0, -std::sqrt(2.0));
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 1);

  verifyRoots(aResult, 0.0, 0.0, 1.0, 1.0, -std::sqrt(2.0), 1.0e-9);
}

TEST(MathRoot_TrigTest, CDE_CosMinusSin)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricCDE(1.0, -1.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 1.0, -1.0, 0.0);
}

TEST(MathRoot_TrigTest, CDE_Harmonic)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricCDE(3.0, 4.0, -5.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 1);
  verifyRoots(aResult, 0.0, 0.0, 3.0, 4.0, -5.0);
}

TEST(MathRoot_TrigTest, CDE_NoSolution)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricCDE(1.0, 1.0, -2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 0);
}

TEST(MathRoot_TrigTest, QuadraticCos_TwoSolutions)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.0, 0.0, 0.0, -1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 2);
  verifyRoots(aResult, 1.0, 0.0, 0.0, 0.0, -1.0);
}

TEST(MathRoot_TrigTest, QuadraticCos_FourSolutions)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.0, 0.0, 0.0, -0.25);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 4);
  verifyRoots(aResult, 1.0, 0.0, 0.0, 0.0, -0.25);
}

TEST(MathRoot_TrigTest, CosSinProduct_AE_Zero)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 1.0, 0.0, 0.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 4);
  verifyRoots(aResult, 0.0, 1.0, 0.0, 0.0, 0.0);
}

TEST(MathRoot_TrigTest, Mixed_SinTimesCos)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.5, 0.0, 1.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.5, 0.0, 1.0, 0.0);
}

TEST(MathRoot_TrigTest, General_FourRoots)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.0, 1.0, 0.0, -0.5);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_GE(aResult.NbRoots, 2);
  verifyRoots(aResult, 1.0, 0.0, 1.0, 0.0, -0.5);
}

TEST(MathRoot_TrigTest, General_AllCoefficients)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.5, 0.3, 0.4, -0.2);
  ASSERT_TRUE(aResult.IsDone());

  verifyRoots(aResult, 1.0, 0.5, 0.3, 0.4, -0.2, 1.0e-8);
}

TEST(MathRoot_TrigTest, Bounds_FirstQuadrant)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, -0.5, 0.0, THE_PI / 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);
  EXPECT_GE(aResult.Roots[0], 0.0 - THE_TOL);
  EXPECT_LE(aResult.Roots[0], THE_PI / 2.0 + THE_TOL);
  verifyRoots(aResult, 0.0, 0.0, 0.0, 1.0, -0.5);
}

TEST(MathRoot_TrigTest, Bounds_SecondQuadrant)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, -0.5, THE_PI / 2.0, THE_PI);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);
  EXPECT_GE(aResult.Roots[0], THE_PI / 2.0 - THE_TOL);
  EXPECT_LE(aResult.Roots[0], THE_PI + THE_TOL);
  verifyRoots(aResult, 0.0, 0.0, 0.0, 1.0, -0.5);
}

TEST(MathRoot_TrigTest, Bounds_NarrowRange)
{

  MathRoot::TrigResult aResult =
    MathRoot::Trigonometric(0.0, 0.0, 1.0, 0.0, 0.0, THE_PI / 2.0 - 0.1, THE_PI / 2.0 + 0.1);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);
  EXPECT_NEAR(aResult.Roots[0], THE_PI / 2.0, THE_TOL);
}

TEST(MathRoot_TrigTest, Bounds_RootOutsideRange)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, -0.5, THE_PI, THE_2PI);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 0);
}

TEST(MathRoot_TrigTest, Bounds_FullCircle)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, 0.0, 0.0, THE_2PI);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
}

TEST(MathRoot_TrigTest, Bounds_MultipleCircles)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, 0.0, 0.0, 4.0 * THE_PI);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_EQ(aResult.NbRoots, 2);
}

TEST(MathRoot_TrigTest, Degenerate_AllZero)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.0, 0.0, 0.0, 0.0);
  EXPECT_TRUE(aResult.InfiniteRoots);
}

TEST(MathRoot_TrigTest, Degenerate_ConstantNonZero)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.0, 0.0, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 0);
}

TEST(MathRoot_TrigTest, Degenerate_NearZeroCoefficients)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0e-14, 1.0e-14, 1.0, 0.0, -0.5);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_EQ(aResult.NbRoots, 2);
  verifyRoots(aResult, 1.0e-14, 1.0e-14, 1.0, 0.0, -0.5, 1.0e-6);
}

TEST(MathRoot_TrigTest, SpecialCase_PiRoot)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.0, -1.0, 0.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 2);
  verifyRoots(aResult, 1.0, 0.0, -1.0, 0.0, 0.0);
}

TEST(MathRoot_TrigTest, SpecialCase_PiRootCheck)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.0, 0.0, 0.0, -1.0);
  ASSERT_TRUE(aResult.IsDone());

  bool aFoundPi = false;
  for (int i = 0; i < aResult.NbRoots; ++i)
  {
    if (std::abs(aResult.Roots[i] - THE_PI) < THE_TOL)
    {
      aFoundPi = true;
      break;
    }
  }
  EXPECT_TRUE(aFoundPi) << "PI should be a root of cos^2(x) - 1 = 0";
  verifyRoots(aResult, 1.0, 0.0, 0.0, 0.0, -1.0);
}

TEST(MathRoot_TrigTest, Stability_LargeCoefficients)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1000.0, 500.0, 300.0, 400.0, -200.0);
  ASSERT_TRUE(aResult.IsDone());
  verifyRoots(aResult, 1000.0, 500.0, 300.0, 400.0, -200.0, 1.0e-6);
}

TEST(MathRoot_TrigTest, Stability_SmallCoefficients)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0e-6, 0.5e-6, 0.3e-6, 0.4e-6, -0.2e-6);
  ASSERT_TRUE(aResult.IsDone());

  if (aResult.NbRoots > 0)
  {
    verifyRoots(aResult, 1.0e-6, 0.5e-6, 0.3e-6, 0.4e-6, -0.2e-6, 1.0e-4);
  }
}

TEST(MathRoot_TrigTest, Stability_MixedMagnitude)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.0, 1.0e6, 0.0, -0.5e6);
  ASSERT_TRUE(aResult.IsDone());
  verifyRoots(aResult, 1.0, 0.0, 1.0e6, 0.0, -0.5e6, 1.0e-4);
}

TEST(MathRoot_TrigTest, RootOrdering_Sorted)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  for (int i = 1; i < aResult.NbRoots; ++i)
  {
    EXPECT_LE(aResult.Roots[i - 1], aResult.Roots[i]) << "Roots should be in ascending order";
  }
}

TEST(MathRoot_TrigTest, RootUniqueness_NoDuplicates)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(1.0, 0.0, 0.0, 0.0, -0.25);
  ASSERT_TRUE(aResult.IsDone());
  for (int i = 0; i < aResult.NbRoots; ++i)
  {
    for (int j = i + 1; j < aResult.NbRoots; ++j)
    {
      EXPECT_GT(std::abs(aResult.Roots[i] - aResult.Roots[j]), 1.0e-10)
        << "Roots " << i << " and " << j << " are duplicates";
    }
  }
}

TEST(MathRoot_TrigTest, Wrapper_TrigonometricLinear)
{

  MathRoot::TrigResult aResult1 = MathRoot::TrigonometricLinear(2.0, -1.0);
  MathRoot::TrigResult aResult2 = MathRoot::Trigonometric(0.0, 0.0, 0.0, 2.0, -1.0);

  EXPECT_EQ(aResult1.NbRoots, aResult2.NbRoots);
  for (int i = 0; i < aResult1.NbRoots; ++i)
  {
    EXPECT_NEAR(aResult1.Roots[i], aResult2.Roots[i], THE_TOL);
  }
}

TEST(MathRoot_TrigTest, Wrapper_TrigonometricCDE)
{

  MathRoot::TrigResult aResult1 = MathRoot::TrigonometricCDE(1.0, 2.0, -0.5);
  MathRoot::TrigResult aResult2 = MathRoot::Trigonometric(0.0, 0.0, 1.0, 2.0, -0.5);

  EXPECT_EQ(aResult1.NbRoots, aResult2.NbRoots);
  for (int i = 0; i < aResult1.NbRoots; ++i)
  {
    EXPECT_NEAR(aResult1.Roots[i], aResult2.Roots[i], THE_TOL);
  }
}

TEST(MathRoot_TrigTest, Result_BoolConversion)
{
  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, 0.0);
  EXPECT_TRUE(static_cast<bool>(aResult));
  EXPECT_TRUE(aResult.IsDone());
}

TEST(MathRoot_TrigTest, Result_InfiniteRoots)
{
  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.0, 0.0, 0.0, 0.0);
  EXPECT_TRUE(aResult.InfiniteRoots);
}

TEST(MathRoot_TrigTest, Ellipse_PointOnMajorAxis)
{

  double aB2MinusA2Over2 = (100.0 - 400.0) / 2.0;
  double aAX             = 20.0 * 30.0;
  double aBY             = 0.0;

  MathRoot::TrigResult aResult =
    MathRoot::Trigonometric(0.0, aB2MinusA2Over2, -aBY, aAX, 0.0, 0.0, THE_2PI);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_GE(aResult.NbRoots, 2);

  verifyRoots(aResult, 0.0, aB2MinusA2Over2, -aBY, aAX, 0.0);
}

TEST(MathRoot_TrigTest, Ellipse_GeneralPoint)
{

  double aB2MinusA2Over2 = (100.0 - 400.0) / 2.0;
  double aAX             = 20.0 * 15.0;
  double aBY             = 10.0 * 8.0;

  MathRoot::TrigResult aResult =
    MathRoot::Trigonometric(0.0, aB2MinusA2Over2, -aBY, aAX, 0.0, 0.0, THE_2PI);
  ASSERT_TRUE(aResult.IsDone());

  verifyRoots(aResult, 0.0, aB2MinusA2Over2, -aBY, aAX, 0.0);
}

TEST(MathRoot_TrigTest, NegativeBounds_Basic)
{

  MathRoot::TrigResult aResult = MathRoot::TrigonometricLinear(1.0, 0.0, -THE_PI, 0.0);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_GE(aResult.NbRoots, 1);
  for (int i = 0; i < aResult.NbRoots; ++i)
  {
    EXPECT_GE(aResult.Roots[i], -THE_PI - THE_TOL);
    EXPECT_LE(aResult.Roots[i], THE_TOL);
  }
}

TEST(MathRoot_TrigTest, NegativeBounds_CosEquation)
{

  MathRoot::TrigResult aResult = MathRoot::Trigonometric(0.0, 0.0, 1.0, 0.0, -0.5, -THE_PI, THE_PI);
  ASSERT_TRUE(aResult.IsDone());

  EXPECT_GE(aResult.NbRoots, 2);
  verifyRoots(aResult, 0.0, 0.0, 1.0, 0.0, -0.5);
}
