

#include <math_FRPR.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>
#include <math_Vector.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class QuadraticBowlFunction : public math_MultipleVarFunctionWithGradient
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double dx = theX(1) - 1.0;
      double dy = theX(2) - 2.0;
      theF      = dx * dx + dy * dy;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      theG(1) = 2.0 * (theX(1) - 1.0);
      theG(2) = 2.0 * (theX(2) - 2.0);
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      Value(theX, theF);
      Gradient(theX, theG);
      return true;
    }
  };

  class RosenbrockFunction : public math_MultipleVarFunctionWithGradient
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double x  = theX(1);
      double y  = theX(2);
      double dx = 1.0 - x;
      double dy = y - x * x;
      theF      = dx * dx + 100.0 * dy * dy;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      double x = theX(1);
      double y = theX(2);
      theG(1)  = -2.0 * (1.0 - x) + 200.0 * (y - x * x) * (-2.0 * x);
      theG(2)  = 200.0 * (y - x * x);
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      Value(theX, theF);
      Gradient(theX, theG);
      return true;
    }
  };

  class Quadratic3DFunction : public math_MultipleVarFunctionWithGradient
  {
  public:
    int NbVariables() const override { return 3; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double dx = theX(1) - 1.0;
      double dy = theX(2) - 2.0;
      double dz = theX(3) - 3.0;
      theF      = dx * dx + 2.0 * dy * dy + 3.0 * dz * dz;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      theG(1) = 2.0 * (theX(1) - 1.0);
      theG(2) = 4.0 * (theX(2) - 2.0);
      theG(3) = 6.0 * (theX(3) - 3.0);
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      Value(theX, theF);
      Gradient(theX, theG);
      return true;
    }
  };

  class LinearFunction : public math_MultipleVarFunctionWithGradient
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      theF = 2.0 * theX(1) + 3.0 * theX(2);
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      (void)theX;
      theG(1) = 2.0;
      theG(2) = 3.0;
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      Value(theX, theF);
      Gradient(theX, theG);
      return true;
    }
  };

  class QuarticFunction : public math_MultipleVarFunctionWithGradient
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double dx = theX(1) - 1.0;
      double dy = theX(2) - 2.0;
      theF      = dx * dx * dx * dx + dy * dy * dy * dy;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      double dx = theX(1) - 1.0;
      double dy = theX(2) - 2.0;
      theG(1)   = 4.0 * dx * dx * dx;
      theG(2)   = 4.0 * dy * dy * dy;
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      Value(theX, theF);
      Gradient(theX, theG);
      return true;
    }
  };

} // namespace

TEST(MathFRPRTest, QuadraticBowlOptimization)
{

  QuadraticBowlFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for quadratic bowl function";

  const math_Vector& aLoc = aSolver.Location();
  EXPECT_NEAR(aLoc(1), 1.0, 1.0e-6) << "Minimum should be at x = 1";
  EXPECT_NEAR(aLoc(2), 2.0, 1.0e-6) << "Minimum should be at y = 2";
  EXPECT_NEAR(aSolver.Minimum(), 0.0, 1.0e-10) << "Minimum value should be 0";
  EXPECT_GT(aSolver.NbIterations(), 0) << "Should have performed some iterations";
}

TEST(MathFRPRTest, RosenbrockOptimization)
{

  RosenbrockFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-8, 500);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for Rosenbrock function";

  const math_Vector& aLoc = aSolver.Location();
  EXPECT_NEAR(aLoc(1), 1.0, 1.0e-3) << "Minimum should be near x = 1";
  EXPECT_NEAR(aLoc(2), 1.0, 1.0e-3) << "Minimum should be near y = 1";
  EXPECT_LT(aSolver.Minimum(), 1.0e-4) << "Should find a very small minimum";
}

TEST(MathFRPRTest, ThreeDimensionalOptimization)
{

  Quadratic3DFunction aFunc;

  math_Vector aStartPoint(1, 3);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;
  aStartPoint(3) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for 3D function";

  const math_Vector& aLoc = aSolver.Location();
  EXPECT_NEAR(aLoc(1), 1.0, 1.0e-6) << "Minimum should be at x = 1";
  EXPECT_NEAR(aLoc(2), 2.0, 1.0e-6) << "Minimum should be at y = 2";
  EXPECT_NEAR(aLoc(3), 3.0, 1.0e-6) << "Minimum should be at z = 3";
  EXPECT_NEAR(aSolver.Minimum(), 0.0, 1.0e-10) << "Minimum value should be 0";
}

TEST(MathFRPRTest, CustomTolerance)
{

  QuadraticBowlFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver1(aFunc, 1.0e-3);
  aSolver1.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver1.IsDone()) << "Should converge with loose tolerance";
  EXPECT_NEAR(aSolver1.Location()(1), 1.0, 1.0e-2) << "Location should be approximately correct";
  EXPECT_NEAR(aSolver1.Location()(2), 2.0, 1.0e-2) << "Location should be approximately correct";

  math_FRPR aSolver2(aFunc, 1.0e-12);
  aSolver2.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with tight tolerance";
  EXPECT_NEAR(aSolver2.Location()(1), 1.0, 1.0e-8) << "Location should be very accurate";
  EXPECT_NEAR(aSolver2.Location()(2), 2.0, 1.0e-8) << "Location should be very accurate";
}

TEST(MathFRPRTest, CustomIterationLimit)
{

  RosenbrockFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver1(aFunc, 1.0e-10, 10);
  aSolver1.Perform(aFunc, aStartPoint);

  if (aSolver1.IsDone())
  {
    EXPECT_LE(aSolver1.NbIterations(), 10) << "Should respect iteration limit";
  }

  math_FRPR aSolver2(aFunc, 1.0e-10, 1000);
  aSolver2.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with many iterations allowed";
}

TEST(MathFRPRTest, GradientAccess)
{

  QuadraticBowlFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum";

  const math_Vector& aGrad = aSolver.Gradient();
  EXPECT_NEAR(aGrad(1), 0.0, 1.0e-8) << "Gradient should be near zero at minimum";
  EXPECT_NEAR(aGrad(2), 0.0, 1.0e-8) << "Gradient should be near zero at minimum";

  math_Vector aGradOut(1, 2);
  aSolver.Gradient(aGradOut);
  EXPECT_NEAR(aGradOut(1), 0.0, 1.0e-8) << "Output gradient should match";
  EXPECT_NEAR(aGradOut(2), 0.0, 1.0e-8) << "Output gradient should match";
}

TEST(MathFRPRTest, LocationAccess)
{

  QuadraticBowlFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum";

  math_Vector aLocOut(1, 2);
  aSolver.Location(aLocOut);
  EXPECT_NEAR(aLocOut(1), 1.0, 1.0e-6) << "Output location should match";
  EXPECT_NEAR(aLocOut(2), 2.0, 1.0e-6) << "Output location should match";
}

TEST(MathFRPRTest, CustomZEPS)
{

  QuadraticBowlFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-10, 200, 1.0e-15);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with custom ZEPS";
  EXPECT_NEAR(aSolver.Location()(1), 1.0, 1.0e-6) << "Result should be accurate";
  EXPECT_NEAR(aSolver.Location()(2), 2.0, 1.0e-6) << "Result should be accurate";
}

TEST(MathFRPRTest, UnperformedState)
{

  QuadraticBowlFunction aFunc;
  math_FRPR             aSolver(aFunc, 1.0e-10);

  EXPECT_FALSE(aSolver.IsDone()) << "Solver should not be done before Perform()";

  if (!aSolver.IsDone())
  {
    EXPECT_FALSE(aSolver.IsDone()) << "State should be consistent when not done";
  }
}

TEST(MathFRPRTest, DimensionCompatibility)
{

  QuadraticBowlFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum";

  math_Vector aCorrectVec(1, 2);
  aSolver.Location(aCorrectVec);
  aSolver.Gradient(aCorrectVec);

  EXPECT_EQ(aCorrectVec.Length(), 2) << "Vector should have correct dimension";
}

TEST(MathFRPRTest, StartingNearMinimum)
{

  QuadraticBowlFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 1.001;
  aStartPoint(2) = 1.999;

  math_FRPR aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should succeed when starting near minimum";
  EXPECT_NEAR(aSolver.Location()(1), 1.0, 1.0e-6) << "Should find accurate minimum";
  EXPECT_NEAR(aSolver.Location()(2), 2.0, 1.0e-6) << "Should find accurate minimum";
  EXPECT_NEAR(aSolver.Minimum(), 0.0, 1.0e-10) << "Minimum value should be very small";
}

TEST(MathFRPRTest, QuarticFlatMinimum)
{

  QuarticFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-8);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should handle quartic function with flat minimum";
  EXPECT_NEAR(aSolver.Location()(1), 1.0, 1.0e-4) << "Should find minimum location";
  EXPECT_NEAR(aSolver.Location()(2), 2.0, 1.0e-4) << "Should find minimum location";
}

TEST(MathFRPRTest, LinearFunctionUnbounded)
{

  LinearFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_FRPR aSolver(aFunc, 1.0e-10, 50);
  aSolver.Perform(aFunc, aStartPoint);

  if (aSolver.IsDone())
  {

    EXPECT_GT(aSolver.NbIterations(), 0) << "Should have performed some iterations";
  }
}

TEST(MathFRPRTest, MultipleCalls)
{

  QuadraticBowlFunction aFunc1;
  Quadratic3DFunction   aFunc2;

  math_Vector aStartPoint2D(1, 2);
  aStartPoint2D(1) = 0.0;
  aStartPoint2D(2) = 0.0;

  math_Vector aStartPoint3D(1, 3);
  aStartPoint3D(1) = 0.0;
  aStartPoint3D(2) = 0.0;
  aStartPoint3D(3) = 0.0;

  math_FRPR aSolver(aFunc1, 1.0e-10);

  aSolver.Perform(aFunc1, aStartPoint2D);
  EXPECT_TRUE(aSolver.IsDone()) << "First call should succeed";
  EXPECT_NEAR(aSolver.Location()(1), 1.0, 1.0e-6) << "First minimum should be correct";

  math_FRPR aSolver2(aFunc2, 1.0e-10);
  aSolver2.Perform(aFunc2, aStartPoint3D);
  EXPECT_TRUE(aSolver2.IsDone()) << "Second call should succeed";
  EXPECT_NEAR(aSolver2.Location()(1), 1.0, 1.0e-6) << "Second minimum should be correct";
}
