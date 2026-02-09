

#include <gtest/gtest.h>

#include <MathPoly_Quadratic.hpp>
#include <MathPoly_Cubic.hpp>
#include <MathPoly_Quartic.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-10;

  double EvalCubic(double theA, double theB, double theC, double theD, double theX)
  {
    return theA * theX * theX * theX + theB * theX * theX + theC * theX + theD;
  }

  double EvalQuartic(double theA, double theB, double theC, double theD, double theE, double theX)
  {
    const double aX2 = theX * theX;
    return theA * aX2 * aX2 + theB * aX2 * theX + theC * aX2 + theD * theX + theE;
  }
} // namespace

TEST(MathPoly_LinearTest, SimpleLinear)
{

  MathUtils::PolyResult aResult = MathPoly::Linear(2.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);
  EXPECT_NEAR(aResult.Roots[0], -2.0, THE_TOLERANCE);
}

TEST(MathPoly_LinearTest, ZeroCoefficient_InfiniteSolutions)
{

  MathUtils::PolyResult aResult = MathPoly::Linear(0.0, 0.0);
  EXPECT_EQ(aResult.Status, MathUtils::Status::InfiniteSolutions);
}

TEST(MathPoly_LinearTest, ZeroCoefficient_NoSolution)
{

  MathUtils::PolyResult aResult = MathPoly::Linear(0.0, 5.0);
  EXPECT_EQ(aResult.Status, MathUtils::Status::NoSolution);
}

TEST(MathPoly_QuadraticTest, TwoDistinctRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0, -5.0, 6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  EXPECT_NEAR(aResult.Roots[0], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 3.0, THE_TOLERANCE);
}

TEST(MathPoly_QuadraticTest, DoubleRoot)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0, -4.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);
  EXPECT_NEAR(aResult.Roots[0], 2.0, THE_TOLERANCE);
}

TEST(MathPoly_QuadraticTest, NoRealRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 0);
}

TEST(MathPoly_QuadraticTest, NegativeRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0, 5.0, 6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  EXPECT_NEAR(aResult.Roots[0], -3.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], -2.0, THE_TOLERANCE);
}

TEST(MathPoly_QuadraticTest, MixedSignRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0, 0.0, -1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  EXPECT_NEAR(aResult.Roots[0], -1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 1.0, THE_TOLERANCE);
}

TEST(MathPoly_QuadraticTest, ReducesToLinear)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(0.0, 2.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);
  EXPECT_NEAR(aResult.Roots[0], -2.0, THE_TOLERANCE);
}

TEST(MathPoly_QuadraticTest, LargeCoefficients)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0e6, -2.0e6, 1.0e6);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);
  EXPECT_NEAR(aResult.Roots[0], 1.0, THE_TOLERANCE);
}

TEST(MathPoly_QuadraticTest, SmallCoefficients)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0e-6, -5.0e-6, 6.0e-6);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  EXPECT_NEAR(aResult.Roots[0], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 3.0, THE_TOLERANCE);
}

TEST(MathPoly_QuadraticTest, RootsAreSorted)
{

  MathUtils::PolyResult aResult = MathPoly::Quadratic(2.0, 3.0, -2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  EXPECT_LT(aResult.Roots[0], aResult.Roots[1]);
}

TEST(MathPoly_CubicTest, ThreeDistinctRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Cubic(1.0, -6.0, 11.0, -6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 3);
  EXPECT_NEAR(aResult.Roots[0], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 3.0, THE_TOLERANCE);
}

TEST(MathPoly_CubicTest, OneRealRoot)
{

  MathUtils::PolyResult aResult = MathPoly::Cubic(1.0, 0.0, 1.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 1);

  double aValue = EvalCubic(1.0, 0.0, 1.0, 1.0, aResult.Roots[0]);
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathPoly_CubicTest, TripleRoot)
{

  MathUtils::PolyResult aResult = MathPoly::Cubic(1.0, -3.0, 3.0, -1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 1);
  EXPECT_NEAR(aResult.Roots[0], 1.0, THE_TOLERANCE);
}

TEST(MathPoly_CubicTest, OneSimpleOneDouble)
{

  MathUtils::PolyResult aResult = MathPoly::Cubic(1.0, -5.0, 8.0, -4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 2);

  for (size_t i = 0; i < aResult.NbRoots; ++i)
  {
    double aValue = EvalCubic(1.0, -5.0, 8.0, -4.0, aResult.Roots[i]);
    EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
  }
}

TEST(MathPoly_CubicTest, ReducesToQuadratic)
{

  MathUtils::PolyResult aResult = MathPoly::Cubic(0.0, 1.0, -5.0, 6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 2);
  EXPECT_NEAR(aResult.Roots[0], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 3.0, THE_TOLERANCE);
}

TEST(MathPoly_CubicTest, NegativeRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Cubic(1.0, 6.0, 11.0, 6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 3);
  EXPECT_NEAR(aResult.Roots[0], -3.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], -2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], -1.0, THE_TOLERANCE);
}

TEST(MathPoly_CubicTest, DepressedCubic)
{

  MathUtils::PolyResult aResult = MathPoly::Cubic(1.0, 0.0, -7.0, 6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 3);
  EXPECT_NEAR(aResult.Roots[0], -3.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 2.0, THE_TOLERANCE);
}

TEST(MathPoly_CubicTest, RootsAreSorted)
{
  MathUtils::PolyResult aResult = MathPoly::Cubic(1.0, -6.0, 11.0, -6.0);
  ASSERT_TRUE(aResult.IsDone());
  for (size_t i = 1; i < aResult.NbRoots; ++i)
  {
    EXPECT_LE(aResult.Roots[i - 1], aResult.Roots[i]);
  }
}

TEST(MathPoly_QuarticTest, FourDistinctRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, -10.0, 35.0, -50.0, 24.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 4);
  EXPECT_NEAR(aResult.Roots[0], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 3.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[3], 4.0, THE_TOLERANCE);
}

TEST(MathPoly_QuarticTest, TwoRealRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, 0.0, -5.0, 0.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 4);
  EXPECT_NEAR(aResult.Roots[0], -2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], -1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[3], 2.0, THE_TOLERANCE);
}

TEST(MathPoly_QuarticTest, NoRealRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, 0.0, 0.0, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 0);
}

TEST(MathPoly_QuarticTest, Biquadratic)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, 0.0, -5.0, 0.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 4);
  for (size_t i = 0; i < aResult.NbRoots; ++i)
  {
    double aValue = EvalQuartic(1.0, 0.0, -5.0, 0.0, 4.0, aResult.Roots[i]);
    EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
  }
}

TEST(MathPoly_QuarticTest, ReducesToCubic)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(0.0, 1.0, -6.0, 11.0, -6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult.NbRoots, 3);
  EXPECT_NEAR(aResult.Roots[0], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[1], 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aResult.Roots[2], 3.0, THE_TOLERANCE);
}

TEST(MathPoly_QuarticTest, QuadrupleRoot)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, -8.0, 24.0, -32.0, 16.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 1);
  EXPECT_NEAR(aResult.Roots[0], 2.0, THE_TOLERANCE);
}

TEST(MathPoly_QuarticTest, TwoDoubleRoots)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, -8.0, 22.0, -24.0, 9.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_GE(aResult.NbRoots, 2);

  for (size_t i = 0; i < aResult.NbRoots; ++i)
  {
    double aValue = EvalQuartic(1.0, -8.0, 22.0, -24.0, 9.0, aResult.Roots[i]);
    EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
  }
}

TEST(MathPoly_QuarticTest, RootsAreSorted)
{
  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, -10.0, 35.0, -50.0, 24.0);
  ASSERT_TRUE(aResult.IsDone());
  for (size_t i = 1; i < aResult.NbRoots; ++i)
  {
    EXPECT_LE(aResult.Roots[i - 1], aResult.Roots[i]);
  }
}

TEST(MathPoly_QuarticTest, VerifyRootsSatisfyEquation)
{

  MathUtils::PolyResult aResult = MathPoly::Quartic(1.0, -10.0, 35.0, -50.0, 24.0);
  ASSERT_TRUE(aResult.IsDone());
  for (size_t i = 0; i < aResult.NbRoots; ++i)
  {
    double aValue = EvalQuartic(1.0, -10.0, 35.0, -50.0, 24.0, aResult.Roots[i]);
    EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
  }
}

TEST(MathPoly_BoolConversionTest, SuccessfulResultIsTrue)
{
  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0, -5.0, 6.0);
  EXPECT_TRUE(static_cast<bool>(aResult));
}

TEST(MathPoly_BoolConversionTest, NoSolutionResultIsFalse)
{
  MathUtils::PolyResult aResult = MathPoly::Linear(0.0, 5.0);
  EXPECT_FALSE(static_cast<bool>(aResult));
}

TEST(MathPoly_IndexingTest, BracketOperator)
{
  MathUtils::PolyResult aResult = MathPoly::Quadratic(1.0, -5.0, 6.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_EQ(aResult[0], aResult.Roots[0]);
  EXPECT_EQ(aResult[1], aResult.Roots[1]);
}
