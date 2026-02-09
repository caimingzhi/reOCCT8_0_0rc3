

#include <math_Powell.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <math_MultipleVarFunction.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class QuadraticFunction : public math_MultipleVarFunction
  {
  public:
    QuadraticFunction() = default;

    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& X, double& F) override
    {
      double x = X(1) - 1.0;
      double y = X(2) - 2.0;
      F        = x * x + y * y;
      return true;
    }
  };

  class RosenbrockFunction : public math_MultipleVarFunction
  {
  public:
    RosenbrockFunction() = default;

    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& X, double& F) override
    {
      double x     = X(1);
      double y     = X(2);
      double term1 = y - x * x;
      double term2 = 1.0 - x;
      F            = 100.0 * term1 * term1 + term2 * term2;
      return true;
    }
  };

  class Simple1DFunction : public math_MultipleVarFunction
  {
  public:
    Simple1DFunction() = default;

    int NbVariables() const override { return 1; }

    bool Value(const math_Vector& X, double& F) override
    {
      double x = X(1) - 3.0;
      F        = x * x;
      return true;
    }
  };

  class MultiDimensionalQuadratic : public math_MultipleVarFunction
  {
  private:
    int myN;

  public:
    MultiDimensionalQuadratic(int n)
        : myN(n)
    {
    }

    int NbVariables() const override { return myN; }

    bool Value(const math_Vector& X, double& F) override
    {
      F = 0.0;
      for (int i = 1; i <= myN; i++)
      {
        double diff = X(i) - static_cast<double>(i);
        F += diff * diff;
      }
      return true;
    }
  };

  TEST(MathPowellTest, SimpleQuadraticFunction)
  {
    QuadraticFunction aFunc;
    math_Powell       aPowell(aFunc, 1.0e-8, 100);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 5.0;
    aStartPoint(2) = 7.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 0.0;
    aDirections(2, 1) = 0.0;
    aDirections(2, 2) = 1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);

    EXPECT_TRUE(aPowell.IsDone()) << "Powell should converge for simple quadratic function";

    const math_Vector& aLocation = aPowell.Location();
    double             aMinimum  = aPowell.Minimum();

    EXPECT_NEAR(aLocation(1), 1.0, 1.0e-6) << "Optimal X coordinate";
    EXPECT_NEAR(aLocation(2), 2.0, 1.0e-6) << "Optimal Y coordinate";
    EXPECT_NEAR(aMinimum, 0.0, 1.0e-10) << "Minimum function value";
  }

  TEST(MathPowellTest, Simple1DOptimization)
  {
    Simple1DFunction aFunc;
    math_Powell      aPowell(aFunc, 1.0e-10, 50);

    math_Vector aStartPoint(1, 1);
    aStartPoint(1) = 10.0;

    math_Matrix aDirections(1, 1, 1, 1);
    aDirections(1, 1) = 1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);

    EXPECT_TRUE(aPowell.IsDone()) << "Powell should converge for 1D quadratic";

    const math_Vector& aLocation = aPowell.Location();
    EXPECT_NEAR(aLocation(1), 3.0, 1.0e-8) << "1D optimum should be at x=3";
    EXPECT_NEAR(aPowell.Minimum(), 0.0, 1.0e-12) << "1D minimum value should be 0";
  }

  TEST(MathPowellTest, RosenbrockFunction)
  {
    RosenbrockFunction aFunc;
    math_Powell        aPowell(aFunc, 1.0e-6, 1000);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = -1.0;
    aStartPoint(2) = 1.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 0.0;
    aDirections(2, 1) = 0.0;
    aDirections(2, 2) = 1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);

    EXPECT_TRUE(aPowell.IsDone()) << "Powell should converge for Rosenbrock function";

    const math_Vector& aLocation = aPowell.Location();

    EXPECT_NEAR(aLocation(1), 1.0, 1.0e-3) << "Rosenbrock optimal X";
    EXPECT_NEAR(aLocation(2), 1.0, 1.0e-3) << "Rosenbrock optimal Y";
    EXPECT_NEAR(aPowell.Minimum(), 0.0, 1.0e-5) << "Rosenbrock minimum value";
  }

  TEST(MathPowellTest, HigherDimensionalOptimization)
  {
    MultiDimensionalQuadratic aFunc(4);
    math_Powell               aPowell(aFunc, 1.0e-8, 200);

    math_Vector aStartPoint(1, 4);
    aStartPoint(1) = 0.0;
    aStartPoint(2) = 0.0;
    aStartPoint(3) = 0.0;
    aStartPoint(4) = 0.0;

    math_Matrix aDirections(1, 4, 1, 4);
    for (int i = 1; i <= 4; i++)
    {
      for (int j = 1; j <= 4; j++)
      {
        aDirections(i, j) = (i == j) ? 1.0 : 0.0;
      }
    }

    aPowell.Perform(aFunc, aStartPoint, aDirections);

    EXPECT_TRUE(aPowell.IsDone()) << "Powell should converge for 4D quadratic";

    const math_Vector& aLocation = aPowell.Location();

    EXPECT_NEAR(aLocation(1), 1.0, 1.0e-6) << "4D optimal X1";
    EXPECT_NEAR(aLocation(2), 2.0, 1.0e-6) << "4D optimal X2";
    EXPECT_NEAR(aLocation(3), 3.0, 1.0e-6) << "4D optimal X3";
    EXPECT_NEAR(aLocation(4), 4.0, 1.0e-6) << "4D optimal X4";
    EXPECT_NEAR(aPowell.Minimum(), 0.0, 1.0e-10) << "4D minimum value";
  }

  TEST(MathPowellTest, DifferentStartingDirections)
  {
    QuadraticFunction aFunc;
    math_Powell       aPowell(aFunc, 1.0e-8, 100);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 3.0;
    aStartPoint(2) = 5.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 1.0;
    aDirections(2, 1) = 1.0;
    aDirections(2, 2) = -1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);

    EXPECT_TRUE(aPowell.IsDone()) << "Powell should work with non-orthogonal directions";

    const math_Vector& aLocation = aPowell.Location();
    EXPECT_NEAR(aLocation(1), 1.0, 1.0e-6) << "Non-orthogonal directions X";
    EXPECT_NEAR(aLocation(2), 2.0, 1.0e-6) << "Non-orthogonal directions Y";
  }

  TEST(MathPowellTest, IterationLimit)
  {
    RosenbrockFunction aFunc;
    math_Powell        aPowell(aFunc, 1.0e-12, 5);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = -2.0;
    aStartPoint(2) = 3.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 0.0;
    aDirections(2, 1) = 0.0;
    aDirections(2, 2) = 1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);

    EXPECT_FALSE(aPowell.IsDone())
      << "Should fail to converge within 5 iterations for challenging function";
  }

  TEST(MathPowellTest, ToleranceSettings)
  {
    QuadraticFunction aFunc;

    math_Powell aPowell1(aFunc, 1.0e-2, 100);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 5.0;
    aStartPoint(2) = 7.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 0.0;
    aDirections(2, 1) = 0.0;
    aDirections(2, 2) = 1.0;

    aPowell1.Perform(aFunc, aStartPoint, aDirections);
    EXPECT_TRUE(aPowell1.IsDone()) << "Should converge with loose tolerance";

    int aIterationsLoose = aPowell1.NbIterations();

    math_Powell aPowell2(aFunc, 1.0e-10, 100);
    aPowell2.Perform(aFunc, aStartPoint, aDirections);
    EXPECT_TRUE(aPowell2.IsDone()) << "Should converge with tight tolerance";

    int aIterationsTight = aPowell2.NbIterations();

    EXPECT_GE(aIterationsTight, aIterationsLoose)
      << "Tighter tolerance should require more iterations";
  }

  TEST(MathPowellTest, LocationOutputMethod)
  {
    QuadraticFunction aFunc;
    math_Powell       aPowell(aFunc, 1.0e-8, 100);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 4.0;
    aStartPoint(2) = 6.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 0.0;
    aDirections(2, 1) = 0.0;
    aDirections(2, 2) = 1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);
    EXPECT_TRUE(aPowell.IsDone());

    math_Vector aLoc(1, 2);
    aPowell.Location(aLoc);

    EXPECT_NEAR(aLoc(1), 1.0, 1.0e-6) << "Location output method X";
    EXPECT_NEAR(aLoc(2), 2.0, 1.0e-6) << "Location output method Y";

    const math_Vector& aLocDirect = aPowell.Location();
    EXPECT_NEAR(aLoc(1), aLocDirect(1), Precision::Confusion()) << "Location methods should match";
    EXPECT_NEAR(aLoc(2), aLocDirect(2), Precision::Confusion()) << "Location methods should match";
  }

  TEST(MathPowellTest, UnperformedState)
  {
    QuadraticFunction aFunc;
    math_Powell       aPowell(aFunc, 1.0e-8, 100);

    EXPECT_FALSE(aPowell.IsDone()) << "Optimizer should not be done before Perform()";

    if (!aPowell.IsDone())
    {
      EXPECT_FALSE(aPowell.IsDone()) << "State should be consistent when not done";
    }
  }

  TEST(MathPowellTest, DimensionCompatibility)
  {
    QuadraticFunction aFunc;
    math_Powell       aPowell(aFunc, 1.0e-8, 100);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 2.0;
    aStartPoint(2) = 3.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 0.0;
    aDirections(2, 1) = 0.0;
    aDirections(2, 2) = 1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);
    EXPECT_TRUE(aPowell.IsDone());

    math_Vector aCorrectLoc(1, 2);
    aPowell.Location(aCorrectLoc);

    EXPECT_EQ(aCorrectLoc.Length(), 2) << "Location vector should have correct dimension";
  }

  TEST(MathPowellTest, AlreadyAtOptimum)
  {
    QuadraticFunction aFunc;
    math_Powell       aPowell(aFunc, 1.0e-8, 100);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 1.0;
    aStartPoint(2) = 2.0;

    math_Matrix aDirections(1, 2, 1, 2);
    aDirections(1, 1) = 1.0;
    aDirections(1, 2) = 0.0;
    aDirections(2, 1) = 0.0;
    aDirections(2, 2) = 1.0;

    aPowell.Perform(aFunc, aStartPoint, aDirections);

    EXPECT_TRUE(aPowell.IsDone()) << "Should succeed when starting at optimum";

    const math_Vector& aLocation = aPowell.Location();
    EXPECT_NEAR(aLocation(1), 1.0, 1.0e-10) << "Should stay at optimum X";
    EXPECT_NEAR(aLocation(2), 2.0, 1.0e-10) << "Should stay at optimum Y";
    EXPECT_NEAR(aPowell.Minimum(), 0.0, 1.0e-12) << "Function value should be 0";

    EXPECT_LE(aPowell.NbIterations(), 5) << "Should converge quickly when starting at optimum";
  }

} // namespace
