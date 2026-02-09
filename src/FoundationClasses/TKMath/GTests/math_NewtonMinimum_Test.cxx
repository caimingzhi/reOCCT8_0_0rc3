

#include <math_NewtonMinimum.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_DimensionError.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class QuadraticBowlWithHessian : public math_MultipleVarFunctionWithHessian
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double dx = theX(1) - 1.0;
      double dy = theX(2) - 2.0;
      theF      = dx * dx + 2.0 * dy * dy;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      theG(1) = 2.0 * (theX(1) - 1.0);
      theG(2) = 4.0 * (theX(2) - 2.0);
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      Value(theX, theF);
      Gradient(theX, theG);
      return true;
    }

    bool Values(const math_Vector& theX,
                double&            theF,
                math_Vector&       theG,
                math_Matrix&       theH) override
    {
      Value(theX, theF);
      Gradient(theX, theG);

      theH(1, 1) = 2.0;
      theH(1, 2) = 0.0;
      theH(2, 1) = 0.0;
      theH(2, 2) = 4.0;
      return true;
    }
  };

  class RosenbrockWithHessian : public math_MultipleVarFunctionWithHessian
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

    bool Values(const math_Vector& theX,
                double&            theF,
                math_Vector&       theG,
                math_Matrix&       theH) override
    {
      double x = theX(1);
      double y = theX(2);

      Value(theX, theF);
      Gradient(theX, theG);

      theH(1, 1) = 2.0 + 1200.0 * x * x - 400.0 * (y - x * x);
      theH(1, 2) = -400.0 * x;
      theH(2, 1) = -400.0 * x;
      theH(2, 2) = 200.0;
      return true;
    }
  };

  class Quadratic3DWithHessian : public math_MultipleVarFunctionWithHessian
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

    bool Values(const math_Vector& theX,
                double&            theF,
                math_Vector&       theG,
                math_Matrix&       theH) override
    {
      Value(theX, theF);
      Gradient(theX, theG);

      theH.Init(0.0);
      theH(1, 1) = 2.0;
      theH(2, 2) = 4.0;
      theH(3, 3) = 6.0;
      return true;
    }
  };

  class SaddleFunction : public math_MultipleVarFunctionWithHessian
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double x = theX(1);
      double y = theX(2);
      theF     = x * x - y * y;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      theG(1) = 2.0 * theX(1);
      theG(2) = -2.0 * theX(2);
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      Value(theX, theF);
      Gradient(theX, theG);
      return true;
    }

    bool Values(const math_Vector& theX,
                double&            theF,
                math_Vector&       theG,
                math_Matrix&       theH) override
    {
      Value(theX, theF);
      Gradient(theX, theG);

      theH(1, 1) = 2.0;
      theH(1, 2) = 0.0;
      theH(2, 1) = 0.0;
      theH(2, 2) = -2.0;
      return true;
    }
  };

} // namespace

TEST(MathNewtonMinimumTest, QuadraticBowlOptimization)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for quadratic bowl function";

  const math_Vector& aLoc = aSolver.Location();
  EXPECT_NEAR(aLoc(1), 1.0, 1.0e-8) << "Minimum should be at x = 1";
  EXPECT_NEAR(aLoc(2), 2.0, 1.0e-8) << "Minimum should be at y = 2";
  EXPECT_NEAR(aSolver.Minimum(), 0.0, 1.0e-12) << "Minimum value should be 0";
  EXPECT_GT(aSolver.NbIterations(), 0) << "Should have performed some iterations";
  EXPECT_LE(aSolver.NbIterations(), 10) << "Should converge quickly for quadratic";
}

TEST(MathNewtonMinimumTest, RosenbrockOptimization)
{

  RosenbrockWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.8;
  aStartPoint(2) = 0.8;

  math_NewtonMinimum aSolver(aFunc, 1.0e-6, 100);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for Rosenbrock function";

  const math_Vector& aLoc = aSolver.Location();
  EXPECT_NEAR(aLoc(1), 1.0, 2.0e-1) << "Minimum should be near x = 1 (within tolerance)";
  EXPECT_NEAR(aLoc(2), 1.0, 2.0e-1) << "Minimum should be near y = 1 (within tolerance)";
  EXPECT_LT(aSolver.Minimum(), 2.0e-2) << "Should find a reasonably small minimum";
}

TEST(MathNewtonMinimumTest, ThreeDimensionalOptimization)
{

  Quadratic3DWithHessian aFunc;

  math_Vector aStartPoint(1, 3);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;
  aStartPoint(3) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum for 3D function";

  const math_Vector& aLoc = aSolver.Location();
  EXPECT_NEAR(aLoc(1), 1.0, 1.0e-8) << "Minimum should be at x = 1";
  EXPECT_NEAR(aLoc(2), 2.0, 1.0e-8) << "Minimum should be at y = 2";
  EXPECT_NEAR(aLoc(3), 3.0, 1.0e-8) << "Minimum should be at z = 3";
  EXPECT_NEAR(aSolver.Minimum(), 0.0, 1.0e-12) << "Minimum value should be 0";
}

TEST(MathNewtonMinimumTest, BoundedOptimization)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_Vector aLeftBound(1, 2);
  aLeftBound(1) = -0.5;
  aLeftBound(2) = -0.5;

  math_Vector aRightBound(1, 2);
  aRightBound(1) = 1.5;
  aRightBound(2) = 2.5;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10);
  aSolver.SetBoundary(aLeftBound, aRightBound);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum with bounds";

  const math_Vector& aLoc = aSolver.Location();
  EXPECT_NEAR(aLoc(1), 1.0, 1.0e-8) << "Minimum should be at x = 1";
  EXPECT_NEAR(aLoc(2), 2.0, 1.0e-8) << "Minimum should be at y = 2";
  EXPECT_GE(aLoc(1), -0.5) << "Should respect lower bound";
  EXPECT_LE(aLoc(1), 1.5) << "Should respect upper bound";
  EXPECT_GE(aLoc(2), -0.5) << "Should respect lower bound";
  EXPECT_LE(aLoc(2), 2.5) << "Should respect upper bound";
}

TEST(MathNewtonMinimumTest, CustomTolerance)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver1(aFunc, 1.0e-3);
  aSolver1.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver1.IsDone()) << "Should converge with loose tolerance";
  EXPECT_NEAR(aSolver1.Location()(1), 1.0, 1.0e-2) << "Location should be approximately correct";
  EXPECT_NEAR(aSolver1.Location()(2), 2.0, 1.0e-2) << "Location should be approximately correct";

  math_NewtonMinimum aSolver2(aFunc, 1.0e-12);
  aSolver2.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with tight tolerance";
  EXPECT_NEAR(aSolver2.Location()(1), 1.0, 1.0e-10) << "Location should be very accurate";
  EXPECT_NEAR(aSolver2.Location()(2), 2.0, 1.0e-10) << "Location should be very accurate";
}

TEST(MathNewtonMinimumTest, CustomIterationLimit)
{

  RosenbrockWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.8;
  aStartPoint(2) = 0.8;

  math_NewtonMinimum aSolver1(aFunc, 1.0e-6, 5);
  aSolver1.Perform(aFunc, aStartPoint);

  if (aSolver1.IsDone())
  {
    EXPECT_LE(aSolver1.NbIterations(), 5) << "Should respect iteration limit";
  }

  math_NewtonMinimum aSolver2(aFunc, 1.0e-8, 200);
  aSolver2.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver2.IsDone()) << "Should converge with many iterations allowed";
}

TEST(MathNewtonMinimumTest, GradientAccess)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10);
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

TEST(MathNewtonMinimumTest, LocationAccess)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum";

  math_Vector aLocOut(1, 2);
  aSolver.Location(aLocOut);
  EXPECT_NEAR(aLocOut(1), 1.0, 1.0e-8) << "Output location should match";
  EXPECT_NEAR(aLocOut(2), 2.0, 1.0e-8) << "Output location should match";
}

TEST(MathNewtonMinimumTest, CustomConvexity)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10, 40, 1.0e-8);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with custom convexity";
  EXPECT_NEAR(aSolver.Location()(1), 1.0, 1.0e-8) << "Result should be accurate";
  EXPECT_NEAR(aSolver.Location()(2), 2.0, 1.0e-8) << "Result should be accurate";
}

TEST(MathNewtonMinimumTest, WithSingularityTreatment)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10, 40, 1.0e-6, true);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should work with singularity treatment";
  EXPECT_NEAR(aSolver.Location()(1), 1.0, 1.0e-8) << "Should find correct minimum";
  EXPECT_NEAR(aSolver.Location()(2), 2.0, 1.0e-8) << "Should find correct minimum";
}

TEST(MathNewtonMinimumTest, NonConvexFunction)
{

  SaddleFunction aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.1;
  aStartPoint(2) = 0.1;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10, 40, 1.0e-6, false);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_NO_THROW(aSolver.Perform(aFunc, aStartPoint))
    << "Should handle non-convex function gracefully";
}

TEST(MathNewtonMinimumTest, UnperformedState)
{

  QuadraticBowlWithHessian aFunc;
  math_NewtonMinimum       aSolver(aFunc, 1.0e-10);

  EXPECT_FALSE(aSolver.IsDone()) << "Solver should not be done before Perform()";

  if (!aSolver.IsDone())
  {
    EXPECT_FALSE(aSolver.IsDone()) << "State should be consistent when not done";
  }
}

TEST(MathNewtonMinimumTest, DimensionCompatibility)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum";

  math_Vector aCorrectVec(1, 2);
  aSolver.Location(aCorrectVec);
  aSolver.Gradient(aCorrectVec);

  EXPECT_EQ(aCorrectVec.Length(), 2) << "Vector should have correct dimension";
}

TEST(MathNewtonMinimumTest, StartingNearMinimum)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 1.001;
  aStartPoint(2) = 1.999;

  math_NewtonMinimum aSolver(aFunc, 1.0e-12);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should succeed when starting near minimum";
  EXPECT_NEAR(aSolver.Location()(1), 1.0, 1.0e-8) << "Should find accurate minimum";
  EXPECT_NEAR(aSolver.Location()(2), 2.0, 1.0e-8) << "Should find accurate minimum";
  EXPECT_NEAR(aSolver.Minimum(), 0.0, 1.0e-12) << "Minimum value should be very small";
  EXPECT_LE(aSolver.NbIterations(), 5) << "Should converge very quickly";
}

TEST(MathNewtonMinimumTest, StatusAccess)
{

  QuadraticBowlWithHessian aFunc;

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 0.0;
  aStartPoint(2) = 0.0;

  math_NewtonMinimum aSolver(aFunc, 1.0e-10);
  aSolver.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(aSolver.IsDone()) << "Should find minimum";

  EXPECT_NO_THROW(aSolver.GetStatus()) << "Should be able to get status after completion";
}
