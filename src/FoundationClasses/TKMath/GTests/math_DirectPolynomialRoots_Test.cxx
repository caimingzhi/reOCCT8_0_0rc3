

#include <math_DirectPolynomialRoots.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <Precision.hpp>

#include <cmath>
#include <algorithm>

class math_DirectPolynomialRootsTest : public ::testing::Test
{
protected:
  void SetUp() override { myTolerance = 1.0e-10; }

  double myTolerance;

  void verifyRoot(double                     theRoot,
                  const std::vector<double>& theCoeffs,
                  int                        theSolutionIndex,
                  double                     theTolerance = 1.0e-10) const
  {
    double aResult = 0.0;
    double aPower  = 1.0;

    for (int i = static_cast<int>(theCoeffs.size()) - 1; i >= 0; i--)
    {
      aResult += theCoeffs[i] * aPower;
      aPower *= theRoot;
    }

    EXPECT_NEAR(aResult, 0.0, theTolerance)
      << "Root " << theSolutionIndex << " should satisfy polynomial equation";
  }
};

TEST_F(math_DirectPolynomialRootsTest, QuadraticRoots)
{

  math_DirectPolynomialRoots aRoots(1.0, -5.0, 6.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Quadratic root finding should succeed";
  EXPECT_EQ(aRoots.NbSolutions(), 2) << "Quadratic should have 2 roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);

  EXPECT_NEAR(aRoot1, 3.0, myTolerance) << "First root should be 3";
  EXPECT_NEAR(aRoot2, 2.0, myTolerance) << "Second root should be 2";

  verifyRoot(aRoot1, {1.0, -5.0, 6.0}, 1);
  verifyRoot(aRoot2, {1.0, -5.0, 6.0}, 2);
}

TEST_F(math_DirectPolynomialRootsTest, QuadraticNoRealRoots)
{

  math_DirectPolynomialRoots aRoots(1.0, 1.0, 1.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Should complete even with no real roots";
  EXPECT_EQ(aRoots.NbSolutions(), 0) << "Should have no real roots";
}

TEST_F(math_DirectPolynomialRootsTest, QuadraticDoubleRoot)
{

  math_DirectPolynomialRoots aRoots(1.0, -2.0, 1.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Double root case should succeed";
  EXPECT_EQ(aRoots.NbSolutions(), 2)
    << "Double root is reported as 2 solutions in the current implementation";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  EXPECT_NEAR(aRoot1, 1.0, myTolerance) << "First double root should be 1.0";
  EXPECT_NEAR(aRoot2, 1.0, myTolerance) << "Second double root should be 1.0";

  verifyRoot(aRoot1, {1.0, -2.0, 1.0}, 1);
  verifyRoot(aRoot2, {1.0, -2.0, 1.0}, 2);
}

TEST_F(math_DirectPolynomialRootsTest, CubicRoots)
{

  math_DirectPolynomialRoots aRoots(1.0, -6.0, 11.0, -6.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Cubic root finding should succeed";
  EXPECT_EQ(aRoots.NbSolutions(), 3) << "Cubic should have 3 real roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  double aRoot3 = aRoots.Value(3);

  EXPECT_NEAR(aRoot1, 3.0, myTolerance) << "First root should be 3";
  EXPECT_NEAR(aRoot2, 2.0, myTolerance) << "Second root should be 2";
  EXPECT_NEAR(aRoot3, 1.0, myTolerance) << "Third root should be 1";

  verifyRoot(aRoot1, {1.0, -6.0, 11.0, -6.0}, 1);
  verifyRoot(aRoot2, {1.0, -6.0, 11.0, -6.0}, 2);
  verifyRoot(aRoot3, {1.0, -6.0, 11.0, -6.0}, 3);
}

TEST_F(math_DirectPolynomialRootsTest, CubicOneRealRoot)
{

  math_DirectPolynomialRoots aRoots(1.0, 0.0, 1.0, 1.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Cubic with one real root should succeed";
  EXPECT_EQ(aRoots.NbSolutions(), 1) << "Should have exactly one real root";

  double aRoot = aRoots.Value(1);

  verifyRoot(aRoot, {1.0, 0.0, 1.0, 1.0}, 1);
}

TEST_F(math_DirectPolynomialRootsTest, QuarticRoots)
{

  math_DirectPolynomialRoots aRoots(1.0, 0.0, -5.0, 0.0, 4.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Quartic root finding should succeed";
  EXPECT_EQ(aRoots.NbSolutions(), 4) << "Quartic should have 4 real roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  double aRoot3 = aRoots.Value(3);
  double aRoot4 = aRoots.Value(4);

  EXPECT_NEAR(aRoot1, -2.0, myTolerance) << "First root should be -2";
  EXPECT_NEAR(aRoot2, -1.0, myTolerance) << "Second root should be -1";
  EXPECT_NEAR(aRoot3, 2.0, myTolerance) << "Third root should be 2";
  EXPECT_NEAR(aRoot4, 1.0, myTolerance) << "Fourth root should be 1";

  std::vector<double> aCoeffs = {1.0, 0.0, -5.0, 0.0, 4.0};
  verifyRoot(aRoot1, aCoeffs, 1);
  verifyRoot(aRoot2, aCoeffs, 2);
  verifyRoot(aRoot3, aCoeffs, 3);
  verifyRoot(aRoot4, aCoeffs, 4);
}

TEST_F(math_DirectPolynomialRootsTest, LinearCase)
{

  math_DirectPolynomialRoots aRoots(2.0, -6.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Linear root finding should succeed";
  EXPECT_EQ(aRoots.NbSolutions(), 1) << "Linear should have 1 root";

  double aRoot = aRoots.Value(1);
  EXPECT_NEAR(aRoot, 3.0, myTolerance) << "Linear root value";

  verifyRoot(aRoot, {2.0, -6.0}, 1);
}

TEST_F(math_DirectPolynomialRootsTest, DegenerateLinearCase)
{

  math_DirectPolynomialRoots aRoots(0.0, 5.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Degenerate linear case should complete";
  EXPECT_EQ(aRoots.NbSolutions(), 0) << "0x + 5 = 0 should have no solutions";
}

TEST_F(math_DirectPolynomialRootsTest, PolynomialEvaluation)
{

  math_DirectPolynomialRoots aRoots(1.0, -3.0, 2.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Should find roots successfully";
  EXPECT_EQ(aRoots.NbSolutions(), 2) << "Should have 2 roots";

  for (int i = 1; i <= aRoots.NbSolutions(); i++)
  {
    double aRoot = aRoots.Value(i);
    verifyRoot(aRoot, {1.0, -3.0, 2.0}, i);
  }
}

TEST_F(math_DirectPolynomialRootsTest, NearZeroCoefficients)
{

  math_DirectPolynomialRoots aRoots(1.0e-15, 1.0, -2.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Should handle near-zero leading coefficient";
  EXPECT_EQ(aRoots.NbSolutions(), 2) << "Should find 2 roots for this quadratic";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);

  bool aFoundNearTwo = (std::abs(aRoot1 - 2.0) < 1.0e-6) || (std::abs(aRoot2 - 2.0) < 1.0e-6);
  EXPECT_TRUE(aFoundNearTwo) << "Should find one root near x = 2";
}

TEST_F(math_DirectPolynomialRootsTest, BiQuadraticPolynomial)
{

  math_DirectPolynomialRoots aRoots(1.0, 0.0, -10.0, 0.0, 9.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Should solve biquadratic polynomial";
  EXPECT_EQ(aRoots.NbSolutions(), 4) << "Should find 4 real roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  double aRoot3 = aRoots.Value(3);
  double aRoot4 = aRoots.Value(4);

  EXPECT_NEAR(aRoot1, -3.0, 1.0e-8) << "First root should be -3";
  EXPECT_NEAR(aRoot2, -1.0, 1.0e-8) << "Second root should be -1";
  EXPECT_NEAR(aRoot3, 3.0, 1.0e-8) << "Third root should be 3";
  EXPECT_NEAR(aRoot4, 1.0, 1.0e-8) << "Fourth root should be 1";

  std::vector<double> aCoeffs = {1.0, 0.0, -10.0, 0.0, 9.0};
  verifyRoot(aRoot1, aCoeffs, 1, 1.0e-8);
  verifyRoot(aRoot2, aCoeffs, 2, 1.0e-8);
  verifyRoot(aRoot3, aCoeffs, 3, 1.0e-8);
  verifyRoot(aRoot4, aCoeffs, 4, 1.0e-8);
}

TEST_F(math_DirectPolynomialRootsTest, RepeatedRoots)
{

  math_DirectPolynomialRoots aRoots(1.0, -3.0, 3.0, -1.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Should handle repeated roots";
  EXPECT_EQ(aRoots.NbSolutions(), 3)
    << "Triple root is reported as 3 solutions in the current implementation";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  double aRoot3 = aRoots.Value(3);
  EXPECT_NEAR(aRoot1, 1.0, 1.0e-8) << "First triple root should be 1.0";
  EXPECT_NEAR(aRoot2, 1.0, 1.0e-8) << "Second triple root should be 1.0";
  EXPECT_NEAR(aRoot3, 1.0, 1.0e-8) << "Third triple root should be 1.0";

  verifyRoot(aRoot1, {1.0, -3.0, 3.0, -1.0}, 1, 1.0e-8);
  verifyRoot(aRoot2, {1.0, -3.0, 3.0, -1.0}, 2, 1.0e-8);
  verifyRoot(aRoot3, {1.0, -3.0, 3.0, -1.0}, 3, 1.0e-8);
}

TEST_F(math_DirectPolynomialRootsTest, ProblematicQuarticCaseDetailed)
{

  const double a = 1.0000000000000004;
  const double b = -2.2737367544323211e-13;
  const double c = -17361733.368892364;
  const double d = 28.998342463569099;
  const double e = 75357446168894.516;

  math_DirectPolynomialRoots aRoots(a, b, c, d, e);

  EXPECT_TRUE(aRoots.IsDone()) << "Problematic quartic should be solved successfully";
  EXPECT_EQ(aRoots.NbSolutions(), 4) << "Should find all 4 real roots";
  EXPECT_FALSE(aRoots.InfiniteRoots()) << "Should not report infinite roots";

  double actualRoots[4];
  for (int i = 1; i <= 4; ++i)
  {
    actualRoots[i - 1] = aRoots.Value(i);
  }

  EXPECT_NEAR(actualRoots[0], -2946.425490, 1.0e-3) << "First root";
  EXPECT_NEAR(actualRoots[1], -2946.236617, 1.0e-3) << "Second root";
  EXPECT_NEAR(actualRoots[2], 2946.394276, 1.0e-3) << "Third root";
  EXPECT_NEAR(actualRoots[3], 2946.267830, 1.0e-3) << "Fourth root";

  for (int i = 1; i <= 4; ++i)
  {
    const double root = aRoots.Value(i);
    const double residual =
      a * root * root * root * root + b * root * root * root + c * root * root + d * root + e;

    EXPECT_LT(std::abs(residual), 1.0)
      << "Root " << i << " residual should be much smaller than previous ~85000";
  }
}

TEST_F(math_DirectPolynomialRootsTest, ModernImplementationBiquadraticDetection)
{

  math_DirectPolynomialRoots aRoots(1.0, 0.0, -5.0, 0.0, 4.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Biquadratic should be solved";
  EXPECT_EQ(aRoots.NbSolutions(), 4) << "Should find 4 real roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  double aRoot3 = aRoots.Value(3);
  double aRoot4 = aRoots.Value(4);

  EXPECT_NEAR(aRoot1, -2.0, 1.0e-12) << "First root should be -2";
  EXPECT_NEAR(aRoot2, -1.0, 1.0e-12) << "Second root should be -1";
  EXPECT_NEAR(aRoot3, 2.0, 1.0e-12) << "Third root should be 2";
  EXPECT_NEAR(aRoot4, 1.0, 1.0e-12) << "Fourth root should be 1";
}

TEST_F(math_DirectPolynomialRootsTest, FullFerrariMethodRequired)
{

  math_DirectPolynomialRoots aRoots(1.0, 1.0, -4.0, -4.0, 0.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Full Ferrari method should work";
  EXPECT_EQ(aRoots.NbSolutions(), 4) << "Should find 4 real roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  double aRoot3 = aRoots.Value(3);
  double aRoot4 = aRoots.Value(4);

  EXPECT_NEAR(aRoot1, -2.0, 1.0e-10) << "First root should be -2";
  EXPECT_NEAR(aRoot2, -1.0, 1.0e-10) << "Second root should be -1";
  EXPECT_NEAR(aRoot3, 2.0, 1.0e-10) << "Third root should be 2";
  EXPECT_NEAR(aRoot4, 0.0, 1.0e-10) << "Fourth root should be 0";
}

TEST_F(math_DirectPolynomialRootsTest, AggressiveRefinementEffectiveness)
{

  const double a = 1.0;
  const double b = 0.0;
  const double c = -1000000.0;
  const double d = 0.0;
  const double e = 999999.0;

  math_DirectPolynomialRoots aRoots(a, b, c, d, e);

  EXPECT_TRUE(aRoots.IsDone()) << "Should handle large coefficients";

  for (int i = 1; i <= aRoots.NbSolutions(); ++i)
  {
    const double root = aRoots.Value(i);
    const double residual =
      a * root * root * root * root + b * root * root * root + c * root * root + d * root + e;

    EXPECT_LT(std::abs(residual), 1.0e-3)
      << "Aggressive refinement should achieve good residuals even with large coefficients";
  }
}

TEST_F(math_DirectPolynomialRootsTest, CubicWithAggressiveRefinement)
{

  math_DirectPolynomialRoots aRoots(1.0, -6.0, 11.0, -6.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Cubic with aggressive refinement should work";
  EXPECT_EQ(aRoots.NbSolutions(), 3) << "Should find 3 real roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);
  double aRoot3 = aRoots.Value(3);

  EXPECT_NEAR(aRoot1, 3.0, 1.0e-12) << "First root should be 3";
  EXPECT_NEAR(aRoot2, 2.0, 1.0e-12) << "Second root should be 2";
  EXPECT_NEAR(aRoot3, 1.0, 1.0e-12) << "Third root should be 1";

  for (int i = 1; i <= 3; ++i)
  {
    const double root     = aRoots.Value(i);
    const double residual = root * root * root - 6.0 * root * root + 11.0 * root - 6.0;
    EXPECT_LT(std::abs(residual), 1.0e-12) << "Cubic residual should be excellent";
  }
}

TEST_F(math_DirectPolynomialRootsTest, ExtremeCoefficientsStability)
{

  const double a = 1.0;
  const double b = 1.0e-15;
  const double c = -1.0e8;
  const double d = 1.0e-10;
  const double e = 1.0e15;

  math_DirectPolynomialRoots aRoots(a, b, c, d, e);

  EXPECT_TRUE(aRoots.IsDone()) << "Should handle extreme coefficient ranges";

  for (int i = 1; i <= aRoots.NbSolutions(); ++i)
  {
    const double root = aRoots.Value(i);
    const double residual =
      a * root * root * root * root + b * root * root * root + c * root * root + d * root + e;

    EXPECT_LT(std::abs(residual), 1.0e6)
      << "Even with extreme coefficients, residuals should be controlled";
  }
}

TEST_F(math_DirectPolynomialRootsTest, CloseToZeroCoefficients)
{

  const double               epsilon = 1.0e-14;
  math_DirectPolynomialRoots aRoots(1.0, epsilon, epsilon, epsilon, -16.0);

  EXPECT_TRUE(aRoots.IsDone()) << "Should handle near-zero coefficients";
  EXPECT_EQ(aRoots.NbSolutions(), 2) << "Should find 2 real roots";

  double aRoot1 = aRoots.Value(1);
  double aRoot2 = aRoots.Value(2);

  EXPECT_NEAR(aRoot1, 2.0, 1.0e-10) << "First root should be 2";
  EXPECT_NEAR(aRoot2, -2.0, 1.0e-10) << "Second root should be -2";
}
