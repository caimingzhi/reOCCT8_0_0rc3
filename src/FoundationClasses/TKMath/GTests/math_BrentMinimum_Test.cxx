

#include <math_BrentMinimum.hpp>
#include <math_Function.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class QuadraticFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = (theX - 2.0) * (theX - 2.0) + 1.0;
      return true;
    }
  };

  class QuarticFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      double dx = theX - 1.0;
      theF      = dx * dx * dx * dx + 2.0;
      return true;
    }
  };

  class CosineFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = cos(theX);
      return true;
    }
  };

  class ShiftedExponentialFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = exp(theX - 3.0);
      return true;
    }
  };

  class RosenbrockSliceFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      double dx = 1.0 - theX;
      double dy = theX - theX * theX;
      theF      = dx * dx + 100.0 * dy * dy;
      return true;
    }
  };

} // namespace

TEST(MathBrentMinimumTest, QuadraticMinimumFinding)
{

  QuadraticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 0.0, 1.5, 4.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for quadratic function";
  EXPECT_NEAR(aSolver.Location(), 2.0, 1.0e-8) << "Minimum should be at x = 2";
  EXPECT_NEAR(aSolver.Minimum(), 1.0, 1.0e-10) << "Minimum value should be 1";
  EXPECT_GT(aSolver.NbIterations(), 0) << "Should have performed some iterations";
}

TEST(MathBrentMinimumTest, QuarticMinimumFinding)
{

  QuarticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 0.0, 0.8, 2.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for quartic function";
  EXPECT_NEAR(aSolver.Location(), 1.0, 1.0e-4) << "Minimum should be at x = 1";
  EXPECT_NEAR(aSolver.Minimum(), 2.0, 1.0e-6) << "Minimum value should be 2";
}

TEST(MathBrentMinimumTest, CosineMinimumFinding)
{

  CosineFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 2.5, 3.1, 4.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for cosine function";
  EXPECT_NEAR(aSolver.Location(), M_PI, 1.0e-8) << "Minimum should be at PI";
  EXPECT_NEAR(aSolver.Minimum(), -1.0, 1.0e-10) << "Minimum value should be -1";
}

TEST(MathBrentMinimumTest, ConstructorWithKnownValue)
{

  QuadraticFunction aFunc;
  double            Bx  = 1.5;
  double            Fbx = (Bx - 2.0) * (Bx - 2.0) + 1.0;

  math_BrentMinimum aSolver(1.0e-10, Fbx);
  aSolver.Perform(aFunc, 0.0, Bx, 4.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with precomputed F(Bx)";
  EXPECT_NEAR(aSolver.Location(), 2.0, 1.0e-8) << "Should still find correct minimum";
}

TEST(MathBrentMinimumTest, CustomTolerance)
{

  QuadraticFunction aFunc;

  math_BrentMinimum aSolver1(1.0e-3);
  aSolver1.Perform(aFunc, 0.0, 1.5, 4.0);

  EXPECT_TRUE(aSolver1.IsDone()) << "Should converge with loose tolerance";
  EXPECT_NEAR(aSolver1.Location(), 2.0, 1.0e-2) << "Location should be approximately correct";

  math_BrentMinimum aSolver2(1.0e-12);
  aSolver2.Perform(aFunc, 0.0, 1.5, 4.0);

  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with tight tolerance";
  EXPECT_NEAR(aSolver2.Location(), 2.0, 1.0e-8) << "Location should be very accurate";
}

TEST(MathBrentMinimumTest, CustomIterationLimit)
{

  RosenbrockSliceFunction aFunc;

  math_BrentMinimum aSolver1(1.0e-10, 5);
  aSolver1.Perform(aFunc, 0.0, 0.5, 2.0);

  if (aSolver1.IsDone())
  {
    EXPECT_LE(aSolver1.NbIterations(), 5) << "Should respect iteration limit";
  }

  math_BrentMinimum aSolver2(1.0e-12, 200);
  aSolver2.Perform(aFunc, 0.0, 0.5, 2.0);

  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with many iterations allowed";
}

TEST(MathBrentMinimumTest, InvalidBracketingTriplet)
{

  QuadraticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 0.0, 4.0, 1.5);

  if (aSolver.IsDone())
  {

    EXPECT_GT(aSolver.Location(), 0.0) << "Result should be reasonable if converged";
    EXPECT_LT(aSolver.Location(), 5.0) << "Result should be reasonable if converged";
  }
}

TEST(MathBrentMinimumTest, FlatFunction)
{

  QuarticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-12);
  aSolver.Perform(aFunc, 0.99, 1.0, 1.01);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle flat function";
  EXPECT_NEAR(aSolver.Location(), 1.0, 1.0e-8) << "Should find flat minimum";
}

TEST(MathBrentMinimumTest, MonotonicFunction)
{

  ShiftedExponentialFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 0.0, 1.0, 2.0);

  if (aSolver.IsDone())
  {

    EXPECT_LT(aSolver.Location(), 1.0) << "Minimum should be toward left boundary";
  }
}

TEST(MathBrentMinimumTest, CustomZEPS)
{

  QuadraticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10, 100, 1.0e-15);
  aSolver.Perform(aFunc, 0.0, 1.5, 4.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with custom ZEPS";
  EXPECT_NEAR(aSolver.Location(), 2.0, 1.0e-8) << "Result should be accurate";
}

TEST(MathBrentMinimumTest, UnperformedState)
{

  math_BrentMinimum aSolver(1.0e-10);

  EXPECT_FALSE(aSolver.IsDone()) << "Solver should not be done before Perform()";

  if (!aSolver.IsDone())
  {
    EXPECT_FALSE(aSolver.IsDone()) << "State should be consistent when not done";
  }
}

TEST(MathBrentMinimumTest, ReversedBracketOrder)
{

  QuadraticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 4.0, 1.5, 0.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle reversed bracket order";
  EXPECT_NEAR(aSolver.Location(), 2.0, 1.0e-8) << "Should still find correct minimum";
}

TEST(MathBrentMinimumTest, HighPrecisionRequirement)
{

  CosineFunction    aFunc;
  math_BrentMinimum aSolver(1.0e-15, 200);

  aSolver.Perform(aFunc, 2.5, 3.1, 4.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should converge with high precision requirement";
  EXPECT_NEAR(aSolver.Location(), M_PI, 1.0e-8) << "Location should be very accurate";
  EXPECT_GT(aSolver.NbIterations(), 10) << "Should require several iterations for high precision";
}

TEST(MathBrentMinimumTest, VeryNarrowBracket)
{

  QuadraticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 1.99, 2.0, 2.01);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle narrow bracket";
  EXPECT_NEAR(aSolver.Location(), 2.0, 1.0e-8) << "Should find accurate minimum";
}

TEST(MathBrentMinimumTest, MultipleCalls)
{

  QuadraticFunction aFunc1;
  CosineFunction    aFunc2;

  math_BrentMinimum aSolver(1.0e-10);

  aSolver.Perform(aFunc1, 0.0, 1.5, 4.0);
  EXPECT_TRUE(aSolver.IsDone()) << "First call should succeed";
  EXPECT_NEAR(aSolver.Location(), 2.0, 1.0e-8) << "First minimum should be x = 2";

  aSolver.Perform(aFunc2, 2.5, 3.1, 4.0);
  EXPECT_TRUE(aSolver.IsDone()) << "Second call should succeed";
  EXPECT_NEAR(aSolver.Location(), M_PI, 1.0e-8) << "Second minimum should be PI";
}

TEST(MathBrentMinimumTest, EdgeCaseAtBoundary)
{

  QuadraticFunction aFunc;

  math_BrentMinimum aSolver(1.0e-10);
  aSolver.Perform(aFunc, 2.0, 2.1, 3.0);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle minimum near boundary";
  EXPECT_NEAR(aSolver.Location(), 2.0, 1.0e-8) << "Should find minimum at boundary";
}
