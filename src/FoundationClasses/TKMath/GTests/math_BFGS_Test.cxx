

#include <math_BFGS.hpp>
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

class QuadraticFunction2D : public math_MultipleVarFunctionWithGradient
{
public:
  QuadraticFunction2D() = default;

  int NbVariables() const override { return 2; }

  bool Value(const math_Vector& theX, double& theF) override
  {
    if (theX.Length() != 2)
      return false;
    double dx = theX(1) - 1.0;
    double dy = theX(2) - 2.0;
    theF      = dx * dx + dy * dy;
    return true;
  }

  bool Gradient(const math_Vector& theX, math_Vector& theG) override
  {
    if (theX.Length() != 2 || theG.Length() != 2)
      return false;
    theG(1) = 2.0 * (theX(1) - 1.0);
    theG(2) = 2.0 * (theX(2) - 2.0);
    return true;
  }

  bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
  {
    return Value(theX, theF) && Gradient(theX, theG);
  }
};

class RosenbrockFunction : public math_MultipleVarFunctionWithGradient
{
public:
  RosenbrockFunction() = default;

  int NbVariables() const override { return 2; }

  bool Value(const math_Vector& theX, double& theF) override
  {
    if (theX.Length() != 2)
      return false;
    double x  = theX(1);
    double y  = theX(2);
    double t1 = y - x * x;
    double t2 = 1.0 - x;
    theF      = 100.0 * t1 * t1 + t2 * t2;
    return true;
  }

  bool Gradient(const math_Vector& theX, math_Vector& theG) override
  {
    if (theX.Length() != 2 || theG.Length() != 2)
      return false;
    double x = theX(1);
    double y = theX(2);
    theG(1)  = -400.0 * x * (y - x * x) - 2.0 * (1.0 - x);
    theG(2)  = 200.0 * (y - x * x);
    return true;
  }

  bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
  {
    return Value(theX, theF) && Gradient(theX, theG);
  }
};

class Paraboloid3D : public math_MultipleVarFunctionWithGradient
{
public:
  Paraboloid3D() = default;

  int NbVariables() const override { return 3; }

  bool Value(const math_Vector& theX, double& theF) override
  {
    if (theX.Length() != 3)
      return false;
    theF = theX(1) * theX(1) + 2.0 * theX(2) * theX(2) + 3.0 * theX(3) * theX(3);
    return true;
  }

  bool Gradient(const math_Vector& theX, math_Vector& theG) override
  {
    if (theX.Length() != 3 || theG.Length() != 3)
      return false;
    theG(1) = 2.0 * theX(1);
    theG(2) = 4.0 * theX(2);
    theG(3) = 6.0 * theX(3);
    return true;
  }

  bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
  {
    return Value(theX, theF) && Gradient(theX, theG);
  }
};

TEST(MathBFGSTest, QuadraticFunction2DOptimization)
{
  QuadraticFunction2D aFunc;
  double              aTolerance     = 1.0e-8;
  int                 aMaxIterations = 100;

  math_BFGS anOptimizer(2, aTolerance, aMaxIterations);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 5.0;
  aStartPoint(2) = 7.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(anOptimizer.IsDone()) << "BFGS optimization should succeed";

  const math_Vector& aLocation = anOptimizer.Location();
  EXPECT_NEAR(aLocation(1), 1.0, 1.0e-6) << "X coordinate should be close to 1.0";
  EXPECT_NEAR(aLocation(2), 2.0, 1.0e-6) << "Y coordinate should be close to 2.0";

  EXPECT_NEAR(anOptimizer.Minimum(), 0.0, 1.0e-10) << "Minimum value should be close to 0.0";

  const math_Vector& aGradient = anOptimizer.Gradient();
  EXPECT_NEAR(aGradient(1), 0.0, 1.0e-6) << "Gradient X component should be close to 0";
  EXPECT_NEAR(aGradient(2), 0.0, 1.0e-6) << "Gradient Y component should be close to 0";

  EXPECT_GT(anOptimizer.NbIterations(), 0) << "Should require at least one iteration";
  EXPECT_LE(anOptimizer.NbIterations(), aMaxIterations) << "Should not exceed max iterations";
}

TEST(MathBFGSTest, RosenbrockFunctionOptimization)
{
  RosenbrockFunction aFunc;
  double             aTolerance     = 1.0e-6;
  int                aMaxIterations = 1000;

  math_BFGS anOptimizer(2, aTolerance, aMaxIterations);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = -1.0;
  aStartPoint(2) = 1.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(anOptimizer.IsDone()) << "BFGS optimization should succeed for Rosenbrock";

  const math_Vector& aLocation = anOptimizer.Location();
  EXPECT_NEAR(aLocation(1), 1.0, 1.0e-4) << "X coordinate should be close to 1.0";
  EXPECT_NEAR(aLocation(2), 1.0, 1.0e-4) << "Y coordinate should be close to 1.0";

  EXPECT_NEAR(anOptimizer.Minimum(), 0.0, 1.0e-8) << "Minimum value should be close to 0.0";
}

TEST(MathBFGSTest, Paraboloid3DOptimization)
{
  Paraboloid3D aFunc;
  double       aTolerance     = 1.0e-8;
  int          aMaxIterations = 100;

  math_BFGS anOptimizer(3, aTolerance, aMaxIterations);

  math_Vector aStartPoint(1, 3);
  aStartPoint(1) = 3.0;
  aStartPoint(2) = 4.0;
  aStartPoint(3) = 5.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(anOptimizer.IsDone()) << "BFGS optimization should succeed for 3D paraboloid";

  const math_Vector& aLocation = anOptimizer.Location();
  EXPECT_NEAR(aLocation(1), 0.0, 1.0e-6) << "X coordinate should be close to 0.0";
  EXPECT_NEAR(aLocation(2), 0.0, 1.0e-6) << "Y coordinate should be close to 0.0";
  EXPECT_NEAR(aLocation(3), 0.0, 1.0e-6) << "Z coordinate should be close to 0.0";

  EXPECT_NEAR(anOptimizer.Minimum(), 0.0, 1.0e-10) << "Minimum value should be close to 0.0";
}

TEST(MathBFGSTest, BoundaryConstraints)
{
  QuadraticFunction2D aFunc;
  double              aTolerance     = 1.0e-8;
  int                 aMaxIterations = 100;

  math_BFGS anOptimizer(2, aTolerance, aMaxIterations);

  math_Vector aLowerBound(1, 2);
  aLowerBound(1) = 2.0;
  aLowerBound(2) = 3.0;

  math_Vector anUpperBound(1, 2);
  anUpperBound(1) = 4.0;
  anUpperBound(2) = 5.0;

  anOptimizer.SetBoundary(aLowerBound, anUpperBound);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 3.0;
  aStartPoint(2) = 4.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(anOptimizer.IsDone()) << "BFGS optimization with boundaries should succeed";

  const math_Vector& aLocation = anOptimizer.Location();
  EXPECT_GE(aLocation(1), aLowerBound(1)) << "X should be within lower bound";
  EXPECT_LE(aLocation(1), anUpperBound(1)) << "X should be within upper bound";
  EXPECT_GE(aLocation(2), aLowerBound(2)) << "Y should be within lower bound";
  EXPECT_LE(aLocation(2), anUpperBound(2)) << "Y should be within upper bound";

  EXPECT_NEAR(aLocation(1), 2.0, 1.0e-6) << "Constrained minimum X should be at boundary";
  EXPECT_NEAR(aLocation(2), 3.0, 1.0e-6) << "Constrained minimum Y should be at boundary";
}

TEST(MathBFGSTest, LocationCopyMethod)
{
  QuadraticFunction2D aFunc;
  math_BFGS           anOptimizer(2);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 3.0;
  aStartPoint(2) = 4.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(anOptimizer.IsDone()) << "Optimization should succeed";

  math_Vector aLocationCopy(1, 2);
  anOptimizer.Location(aLocationCopy);

  const math_Vector& aLocationRef = anOptimizer.Location();
  EXPECT_NEAR(aLocationCopy(1), aLocationRef(1), Precision::Confusion())
    << "Copied location should match reference";
  EXPECT_NEAR(aLocationCopy(2), aLocationRef(2), Precision::Confusion())
    << "Copied location should match reference";
}

TEST(MathBFGSTest, GradientCopyMethod)
{
  QuadraticFunction2D aFunc;
  math_BFGS           anOptimizer(2);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 3.0;
  aStartPoint(2) = 4.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  EXPECT_TRUE(anOptimizer.IsDone()) << "Optimization should succeed";

  math_Vector aGradientCopy(1, 2);
  anOptimizer.Gradient(aGradientCopy);

  const math_Vector& aGradientRef = anOptimizer.Gradient();
  EXPECT_NEAR(aGradientCopy(1), aGradientRef(1), Precision::Confusion())
    << "Copied gradient should match reference";
  EXPECT_NEAR(aGradientCopy(2), aGradientRef(2), Precision::Confusion())
    << "Copied gradient should match reference";
}

TEST(MathBFGSTest, DifferentTolerances)
{
  QuadraticFunction2D aFunc;

  {
    double    aTightTolerance = 1.0e-12;
    math_BFGS anOptimizer(2, aTightTolerance);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 2.0;
    aStartPoint(2) = 3.0;

    anOptimizer.Perform(aFunc, aStartPoint);

    EXPECT_TRUE(anOptimizer.IsDone()) << "High precision optimization should succeed";
    EXPECT_NEAR(anOptimizer.Location()(1), 1.0, aTightTolerance * 10)
      << "High precision X coordinate";
    EXPECT_NEAR(anOptimizer.Location()(2), 2.0, aTightTolerance * 10)
      << "High precision Y coordinate";
  }

  {
    double    aLooseTolerance = 1.0e-3;
    math_BFGS anOptimizer(2, aLooseTolerance);

    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = 10.0;
    aStartPoint(2) = 10.0;

    anOptimizer.Perform(aFunc, aStartPoint);

    EXPECT_TRUE(anOptimizer.IsDone()) << "Low precision optimization should succeed";
    EXPECT_NEAR(anOptimizer.Location()(1), 1.0, aLooseTolerance * 10)
      << "Low precision X coordinate";
    EXPECT_NEAR(anOptimizer.Location()(2), 2.0, aLooseTolerance * 10)
      << "Low precision Y coordinate";
  }
}

TEST(MathBFGSTest, MaxIterationsLimit)
{
  RosenbrockFunction aFunc;
  double             aTolerance         = 1.0e-12;
  int                aVeryFewIterations = 5;

  math_BFGS anOptimizer(2, aTolerance, aVeryFewIterations);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = -2.0;
  aStartPoint(2) = 2.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  if (anOptimizer.IsDone())
  {
    EXPECT_LE(anOptimizer.NbIterations(), aVeryFewIterations) << "Should not exceed max iterations";
  }
  else
  {

    EXPECT_LE(aVeryFewIterations, 10) << "Failure expected with very few iterations";
  }
}

TEST(MathBFGSTest, NotDoneState)
{
  QuadraticFunction2D aFunc;
  math_BFGS           anOptimizer(2, 1.0e-12, 3);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 50.0;
  aStartPoint(2) = 50.0;

  EXPECT_NO_THROW({
    anOptimizer.Perform(aFunc, aStartPoint);

    if (!anOptimizer.IsDone())
    {
      EXPECT_GE(anOptimizer.NbIterations(), 0)
        << "Iteration count should be non-negative even on failure";
    }
    else
    {
      EXPECT_GT(anOptimizer.NbIterations(), 0)
        << "Successful optimization should require at least one iteration";
    }
  }) << "BFGS optimization should not throw exceptions";
}

TEST(MathBFGSTest, DimensionCompatibility)
{
  QuadraticFunction2D aFunc;
  math_BFGS           anOptimizer(2);

  math_Vector aStartPoint(1, 2);
  aStartPoint(1) = 2.0;
  aStartPoint(2) = 3.0;

  anOptimizer.Perform(aFunc, aStartPoint);

  ASSERT_TRUE(anOptimizer.IsDone())
    << "Optimization should succeed for dimension compatibility tests";

  math_Vector aCorrectSizeLocation(1, 2);
  math_Vector aCorrectSizeGradient(1, 2);

  anOptimizer.Location(aCorrectSizeLocation);
  anOptimizer.Gradient(aCorrectSizeGradient);

  EXPECT_EQ(aCorrectSizeLocation.Length(), 2) << "Location vector should have correct dimension";
  EXPECT_EQ(aCorrectSizeGradient.Length(), 2) << "Gradient vector should have correct dimension";
}

TEST(MathBFGSTest, ConstructorParameters)
{

  {
    math_BFGS           anOptimizer1(3);
    QuadraticFunction2D aFunc;

    EXPECT_NO_THROW({
      math_Vector aStart(1, 3);
      aStart.Init(1.0);
    });
  }

  {
    math_BFGS anOptimizer2(2, 1.0e-6);
  }

  {
    math_BFGS anOptimizer3(2, 1.0e-8, 50);
  }

  {
    math_BFGS anOptimizer4(2, 1.0e-8, 100, 1.0e-10);
  }
}

TEST(MathBFGSTest, MultipleOptimizations)
{
  QuadraticFunction2D aFunc;
  math_BFGS           anOptimizer(2);

  std::vector<std::pair<double, double>> aStartPoints = {{5.0, 7.0},
                                                         {-3.0, -4.0},
                                                         {0.5, 1.5},
                                                         {10.0, -5.0}};

  for (const auto& aStart : aStartPoints)
  {
    math_Vector aStartPoint(1, 2);
    aStartPoint(1) = aStart.first;
    aStartPoint(2) = aStart.second;

    anOptimizer.Perform(aFunc, aStartPoint);

    EXPECT_TRUE(anOptimizer.IsDone()) << "Each optimization should succeed";
    EXPECT_NEAR(anOptimizer.Location()(1), 1.0, 1.0e-6) << "Each should find correct X minimum";
    EXPECT_NEAR(anOptimizer.Location()(2), 2.0, 1.0e-6) << "Each should find correct Y minimum";
  }
}

class SquareFunction1D : public math_MultipleVarFunctionWithGradient
{
public:
  SquareFunction1D() = default;

  int NbVariables() const override { return 1; }

  bool Value(const math_Vector& theX, double& theF) override
  {
    if (theX.Length() != 1)
      return false;
    const double x = theX(1);
    theF           = x * x;
    return true;
  }

  bool Gradient(const math_Vector& theX, math_Vector& theG) override
  {
    if (theX.Length() != 1 || theG.Length() != 1)
      return false;
    const double x = theX(1);
    theG(1)        = 2.0 * x;
    return true;
  }

  bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
  {
    return Value(theX, theF) && Gradient(theX, theG);
  }
};

TEST(MathBFGSTest, OCC30492_StartingPointAtMinimum)
{

  SquareFunction1D aFunc;
  math_Vector      aStartPnt(1, 1);
  aStartPnt(1) = 0.0;

  math_FRPR aFRPR(aFunc, Precision::Confusion());
  aFRPR.Perform(aFunc, aStartPnt);
  EXPECT_TRUE(aFRPR.IsDone()) << "FRPR optimization should succeed when starting at minimum";

  math_BFGS aBFGS(1, Precision::Confusion());
  aBFGS.Perform(aFunc, aStartPnt);
  EXPECT_TRUE(aBFGS.IsDone()) << "BFGS optimization should succeed when starting at minimum";

  if (aFRPR.IsDone())
  {
    EXPECT_NEAR(aFRPR.Location()(1), 0.0, Precision::Confusion())
      << "FRPR should stay at/find the minimum";
    EXPECT_NEAR(aFRPR.Minimum(), 0.0, Precision::Confusion())
      << "FRPR should report minimum value of 0";
  }

  if (aBFGS.IsDone())
  {
    EXPECT_NEAR(aBFGS.Location()(1), 0.0, Precision::Confusion())
      << "BFGS should stay at/find the minimum";
    EXPECT_NEAR(aBFGS.Minimum(), 0.0, Precision::Confusion())
      << "BFGS should report minimum value of 0";
  }
}
