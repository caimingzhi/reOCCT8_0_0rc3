

#include <gtest/gtest.h>

#include <MathPoly_Quadratic.hpp>
#include <MathPoly_Cubic.hpp>
#include <MathPoly_Quartic.hpp>

#include <math_DirectPolynomialRoots.hpp>

#include <algorithm>
#include <cmath>
#include <vector>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-9;

  std::vector<double> SortRoots(const std::vector<double>& theRoots)
  {
    std::vector<double> aSorted = theRoots;
    std::sort(aSorted.begin(), aSorted.end());
    return aSorted;
  }

  std::vector<double> GetOldRoots(const math_DirectPolynomialRoots& theSolver)
  {
    std::vector<double> aRoots;
    if (theSolver.IsDone())
    {
      for (int i = 1; i <= theSolver.NbSolutions(); ++i)
      {
        aRoots.push_back(theSolver.Value(i));
      }
    }
    return SortRoots(aRoots);
  }

  std::vector<double> GetNewRoots(const MathUtils::PolyResult& theResult)
  {
    std::vector<double> aRoots;
    if (theResult.IsDone())
    {
      for (size_t i = 0; i < theResult.NbRoots; ++i)
      {
        aRoots.push_back(theResult.Roots[i]);
      }
    }
    return SortRoots(aRoots);
  }

  void CompareRoots(const std::vector<double>& theOld,
                    const std::vector<double>& theNew,
                    double                     theTolerance = THE_TOLERANCE)
  {
    ASSERT_EQ(theOld.size(), theNew.size()) << "Different number of roots";
    for (size_t i = 0; i < theOld.size(); ++i)
    {
      EXPECT_NEAR(theOld[i], theNew[i], theTolerance)
        << "Root " << i << " differs: old=" << theOld[i] << " new=" << theNew[i];
    }
  }
} // namespace

TEST(MathPoly_ComparisonTest, Quadratic_TwoDistinctRoots)
{

  const double aA = 1.0, aB = -5.0, aC = 6.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC);
  MathUtils::PolyResult      aNewResult = MathPoly::Quadratic(aA, aB, aC);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Quadratic_DoubleRoot)
{

  const double aA = 1.0, aB = -4.0, aC = 4.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC);
  MathUtils::PolyResult      aNewResult = MathPoly::Quadratic(aA, aB, aC);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  auto aOldRoots = GetOldRoots(anOldSolver);
  auto aNewRoots = GetNewRoots(aNewResult);

  for (double aRoot : aOldRoots)
  {
    EXPECT_NEAR(aRoot, 2.0, THE_TOLERANCE);
  }
  for (double aRoot : aNewRoots)
  {
    EXPECT_NEAR(aRoot, 2.0, THE_TOLERANCE);
  }
}

TEST(MathPoly_ComparisonTest, Quadratic_NoRealRoots)
{

  const double aA = 1.0, aB = 0.0, aC = 1.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC);
  MathUtils::PolyResult      aNewResult = MathPoly::Quadratic(aA, aB, aC);

  EXPECT_EQ(anOldSolver.NbSolutions(), 0);
  EXPECT_EQ(aNewResult.NbRoots, 0);
}

TEST(MathPoly_ComparisonTest, Quadratic_NegativeRoots)
{

  const double aA = 1.0, aB = 5.0, aC = 6.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC);
  MathUtils::PolyResult      aNewResult = MathPoly::Quadratic(aA, aB, aC);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Quadratic_LargeCoefficients)
{

  const double aA = 1000.0, aB = -3000.0, aC = 2000.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC);
  MathUtils::PolyResult      aNewResult = MathPoly::Quadratic(aA, aB, aC);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Cubic_ThreeDistinctRoots)
{

  const double aA = 1.0, aB = -6.0, aC = 11.0, aD = -6.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD);
  MathUtils::PolyResult      aNewResult = MathPoly::Cubic(aA, aB, aC, aD);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Cubic_OneRealRoot)
{

  const double aA = 1.0, aB = 0.0, aC = 1.0, aD = 2.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD);
  MathUtils::PolyResult      aNewResult = MathPoly::Cubic(aA, aB, aC, aD);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_EQ(anOldSolver.NbSolutions(), aNewResult.NbRoots);

  if (anOldSolver.NbSolutions() > 0 && aNewResult.NbRoots > 0)
  {
    CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
  }
}

TEST(MathPoly_ComparisonTest, Cubic_TripleRoot)
{

  const double aA = 1.0, aB = -3.0, aC = 3.0, aD = -1.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD);
  MathUtils::PolyResult      aNewResult = MathPoly::Cubic(aA, aB, aC, aD);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  auto aOldRoots = GetOldRoots(anOldSolver);
  auto aNewRoots = GetNewRoots(aNewResult);

  for (double aRoot : aOldRoots)
  {
    EXPECT_NEAR(aRoot, 1.0, 1.0e-6);
  }
  for (double aRoot : aNewRoots)
  {
    EXPECT_NEAR(aRoot, 1.0, 1.0e-6);
  }
}

TEST(MathPoly_ComparisonTest, Cubic_NegativeLeadingCoeff)
{

  const double aA = -1.0, aB = 6.0, aC = -11.0, aD = 6.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD);
  MathUtils::PolyResult      aNewResult = MathPoly::Cubic(aA, aB, aC, aD);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Quartic_FourDistinctRoots)
{

  const double aA = 1.0, aB = -10.0, aC = 35.0, aD = -50.0, aE = 24.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD, aE);
  MathUtils::PolyResult      aNewResult = MathPoly::Quartic(aA, aB, aC, aD, aE);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Quartic_TwoRealRoots)
{

  const double aA = 1.0, aB = 0.0, aC = 0.0, aD = 0.0, aE = -1.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD, aE);
  MathUtils::PolyResult      aNewResult = MathPoly::Quartic(aA, aB, aC, aD, aE);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_EQ(anOldSolver.NbSolutions(), 2);
  EXPECT_EQ(aNewResult.NbRoots, 2);

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Quartic_Biquadratic)
{

  const double aA = 1.0, aB = 0.0, aC = -5.0, aD = 0.0, aE = 4.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD, aE);
  MathUtils::PolyResult      aNewResult = MathPoly::Quartic(aA, aB, aC, aD, aE);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));
}

TEST(MathPoly_ComparisonTest, Quartic_NoRealRoots)
{

  const double aA = 1.0, aB = 0.0, aC = 0.0, aD = 0.0, aE = 1.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD, aE);
  MathUtils::PolyResult      aNewResult = MathPoly::Quartic(aA, aB, aC, aD, aE);

  EXPECT_EQ(anOldSolver.NbSolutions(), 0);
  EXPECT_EQ(aNewResult.NbRoots, 0);
}

TEST(MathPoly_ComparisonTest, Quartic_QuadrupleRoot)
{

  const double aA = 1.0, aB = -8.0, aC = 24.0, aD = -32.0, aE = 16.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD, aE);
  MathUtils::PolyResult      aNewResult = MathPoly::Quartic(aA, aB, aC, aD, aE);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  auto aOldRoots = GetOldRoots(anOldSolver);
  auto aNewRoots = GetNewRoots(aNewResult);

  for (double aRoot : aOldRoots)
  {
    EXPECT_NEAR(aRoot, 2.0, 1.0e-5);
  }
  for (double aRoot : aNewRoots)
  {
    EXPECT_NEAR(aRoot, 2.0, 1.0e-5);
  }
}

TEST(MathPoly_ComparisonTest, Quadratic_SmallDiscriminant)
{

  const double aA = 1.0, aB = -2.0, aC = 0.9999;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC);
  MathUtils::PolyResult      aNewResult = MathPoly::Quadratic(aA, aB, aC);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_EQ(anOldSolver.NbSolutions(), 2);
  EXPECT_EQ(aNewResult.NbRoots, 2);

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult), 1.0e-4);
}

TEST(MathPoly_ComparisonTest, Cubic_SmallCoefficients)
{

  const double aA = 0.001, aB = -0.006, aC = 0.011, aD = -0.006;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD);
  MathUtils::PolyResult      aNewResult = MathPoly::Cubic(aA, aB, aC, aD);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult), 1.0e-6);
}

TEST(MathPoly_ComparisonTest, Quadratic_NumericallyChallengingCase)
{

  const double aA = 1.0, aB = -1.0e8, aC = 1.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC);
  MathUtils::PolyResult      aNewResult = MathPoly::Quadratic(aA, aB, aC);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_EQ(anOldSolver.NbSolutions(), 2);
  EXPECT_EQ(aNewResult.NbRoots, 2);

  auto aOldRoots = GetOldRoots(anOldSolver);
  auto aNewRoots = GetNewRoots(aNewResult);

  EXPECT_NEAR(aOldRoots[0], aNewRoots[0], 1.0e-14);

  EXPECT_NEAR(aOldRoots[1] / aNewRoots[1], 1.0, 1.0e-8);
}

TEST(MathPoly_ComparisonTest, Quartic_SymmetricRoots)
{

  const double aA = 1.0, aB = 0.0, aC = -5.0, aD = 0.0, aE = 4.0;

  math_DirectPolynomialRoots anOldSolver(aA, aB, aC, aD, aE);
  MathUtils::PolyResult      aNewResult = MathPoly::Quartic(aA, aB, aC, aD, aE);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  CompareRoots(GetOldRoots(anOldSolver), GetNewRoots(aNewResult));

  auto aNewRoots = GetNewRoots(aNewResult);
  ASSERT_EQ(aNewRoots.size(), 4u);
  EXPECT_NEAR(aNewRoots[0], -2.0, THE_TOLERANCE);
  EXPECT_NEAR(aNewRoots[1], -1.0, THE_TOLERANCE);
  EXPECT_NEAR(aNewRoots[2], 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aNewRoots[3], 2.0, THE_TOLERANCE);
}
