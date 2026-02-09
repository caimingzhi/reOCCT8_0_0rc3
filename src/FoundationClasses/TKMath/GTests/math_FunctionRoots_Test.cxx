

#include <math_FunctionRoots.hpp>
#include <math_FunctionWithDerivative.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_RangeError.hpp>

#include <algorithm>
#include <cmath>

namespace
{

  class QuadraticWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX - 4.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 2.0 * theX;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX - 4.0;
      theD = 2.0 * theX;
      return true;
    }
  };

  class CubicWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX * theX - 6.0 * theX * theX + 11.0 * theX - 6.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 3.0 * theX * theX - 12.0 * theX + 11.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX * theX - 6.0 * theX * theX + 11.0 * theX - 6.0;
      theD = 3.0 * theX * theX - 12.0 * theX + 11.0;
      return true;
    }
  };

  class SineWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = sin(theX);
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = cos(theX);
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = sin(theX);
      theD = cos(theX);
      return true;
    }
  };

  class LinearWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = 2.0 * theX - 4.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      (void)theX;
      theD = 2.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = 2.0 * theX - 4.0;
      theD = 2.0;
      return true;
    }
  };

  class ConstantZeroFunction : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double, double& theF) override
    {
      theF = 0.0;
      return true;
    }

    bool Derivative(const double, double& theD) override
    {
      theD = 0.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      (void)theX;
      theF = 0.0;
      theD = 0.0;
      return true;
    }
  };

  class NoRootsFunction : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX + 1.0;
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {
      theD = 2.0 * theX;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      theF = theX * theX + 1.0;
      theD = 2.0 * theX;
      return true;
    }
  };

  class QuarticWithDerivative : public math_FunctionWithDerivative
  {
  public:
    bool Value(const double theX, double& theF) override
    {

      theF = (theX - 1.0) * (theX - 2.0) * (theX - 3.0) * (theX - 4.0);
      return true;
    }

    bool Derivative(const double theX, double& theD) override
    {

      theD = 4.0 * theX * theX * theX - 30.0 * theX * theX + 70.0 * theX - 50.0;
      return true;
    }

    bool Values(const double theX, double& theF, double& theD) override
    {
      Value(theX, theF);
      Derivative(theX, theD);
      return true;
    }
  };

} // namespace

TEST(MathFunctionRootsTest, QuadraticTwoRoots)
{

  QuadraticWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, -5.0, 5.0, 20, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully find roots";
  EXPECT_FALSE(aRootFinder.IsAllNull()) << "Function should not be all null";
  EXPECT_EQ(aRootFinder.NbSolutions(), 2) << "Should find exactly 2 roots";

  double aRoot1 = aRootFinder.Value(1);
  double aRoot2 = aRootFinder.Value(2);

  if (aRoot1 > aRoot2)
  {
    double aTemp = aRoot1;
    aRoot1       = aRoot2;
    aRoot2       = aTemp;
  }

  EXPECT_NEAR(aRoot1, -2.0, 1.0e-8) << "First root should be -2";
  EXPECT_NEAR(aRoot2, 2.0, 1.0e-8) << "Second root should be 2";
}

TEST(MathFunctionRootsTest, CubicThreeRoots)
{

  CubicWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, 0.0, 4.0, 30, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully find roots";
  EXPECT_FALSE(aRootFinder.IsAllNull()) << "Function should not be all null";
  EXPECT_EQ(aRootFinder.NbSolutions(), 3) << "Should find exactly 3 roots";

  std::vector<double> aRoots;
  for (int i = 1; i <= aRootFinder.NbSolutions(); ++i)
  {
    aRoots.push_back(aRootFinder.Value(i));
  }
  std::sort(aRoots.begin(), aRoots.end());

  EXPECT_NEAR(aRoots[0], 1.0, 1.0e-8) << "First root should be 1";
  EXPECT_NEAR(aRoots[1], 2.0, 1.0e-8) << "Second root should be 2";
  EXPECT_NEAR(aRoots[2], 3.0, 1.0e-8) << "Third root should be 3";
}

TEST(MathFunctionRootsTest, SineMultipleRoots)
{

  SineWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, 0.0, 2.0 * M_PI, 50, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully find roots";
  EXPECT_FALSE(aRootFinder.IsAllNull()) << "Sine function should not be all null";

  int aNbRoots = aRootFinder.NbSolutions();
  EXPECT_GE(aNbRoots, 2) << "Should find at least 2 roots (0, PI, 2PI)";
  EXPECT_LE(aNbRoots, 3) << "Should find at most 3 roots in [0, 2PI]";

  for (int i = 1; i <= aNbRoots; ++i)
  {
    double aRoot = aRootFinder.Value(i);
    double aFuncValue;
    aFunc.Value(aRoot, aFuncValue);
    EXPECT_NEAR(aFuncValue, 0.0, 1.0e-8) << "Root " << i << " should have function value near 0";
  }
}

TEST(MathFunctionRootsTest, LinearSingleRoot)
{

  LinearWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, 0.0, 4.0, 10, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully find root";
  EXPECT_FALSE(aRootFinder.IsAllNull()) << "Linear function should not be all null";
  EXPECT_EQ(aRootFinder.NbSolutions(), 1) << "Should find exactly 1 root";

  double aRoot = aRootFinder.Value(1);
  EXPECT_NEAR(aRoot, 2.0, 1.0e-10) << "Root should be x = 2";
}

TEST(MathFunctionRootsTest, ConstantZeroFunction)
{

  ConstantZeroFunction aFunc;

  math_FunctionRoots aRootFinder(aFunc, -2.0, 2.0, 10, 1.0e-10, 1.0e-10, 1.0e-6);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully process constant function";
  EXPECT_TRUE(aRootFinder.IsAllNull()) << "Constant zero function should be all null";
}

TEST(MathFunctionRootsTest, NoRootsFunction)
{

  NoRootsFunction aFunc;

  math_FunctionRoots aRootFinder(aFunc, -5.0, 5.0, 20, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully process function";
  EXPECT_FALSE(aRootFinder.IsAllNull()) << "Function is not zero everywhere";
  EXPECT_EQ(aRootFinder.NbSolutions(), 0) << "Should find no real roots";
}

TEST(MathFunctionRootsTest, QuarticFourRoots)
{

  QuarticWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, 0.0, 5.0, 40, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully find roots";
  EXPECT_FALSE(aRootFinder.IsAllNull()) << "Function should not be all null";
  EXPECT_EQ(aRootFinder.NbSolutions(), 4) << "Should find exactly 4 roots";

  std::vector<double> aRoots;
  for (int i = 1; i <= aRootFinder.NbSolutions(); ++i)
  {
    aRoots.push_back(aRootFinder.Value(i));
  }
  std::sort(aRoots.begin(), aRoots.end());

  EXPECT_NEAR(aRoots[0], 1.0, 1.0e-8) << "First root should be 1";
  EXPECT_NEAR(aRoots[1], 2.0, 1.0e-8) << "Second root should be 2";
  EXPECT_NEAR(aRoots[2], 3.0, 1.0e-8) << "Third root should be 3";
  EXPECT_NEAR(aRoots[3], 4.0, 1.0e-8) << "Fourth root should be 4";
}

TEST(MathFunctionRootsTest, CustomTolerances)
{

  QuadraticWithDerivative aFunc;

  math_FunctionRoots aRootFinder1(aFunc, -5.0, 5.0, 20, 1.0e-3, 1.0e-3);

  EXPECT_TRUE(aRootFinder1.IsDone()) << "Should work with loose tolerances";
  EXPECT_EQ(aRootFinder1.NbSolutions(), 2) << "Should still find 2 roots";

  math_FunctionRoots aRootFinder2(aFunc, -5.0, 5.0, 20, 1.0e-12, 1.0e-12);

  EXPECT_TRUE(aRootFinder2.IsDone()) << "Should work with tight tolerances";
  EXPECT_EQ(aRootFinder2.NbSolutions(), 2) << "Should still find 2 roots";
}

TEST(MathFunctionRootsTest, CustomSampleCount)
{

  CubicWithDerivative aFunc;

  math_FunctionRoots aRootFinder1(aFunc, 0.0, 4.0, 5, 1.0e-8, 1.0e-8);

  EXPECT_TRUE(aRootFinder1.IsDone()) << "Should work with few samples";
  EXPECT_GE(aRootFinder1.NbSolutions(), 1) << "Should find at least some roots";

  math_FunctionRoots aRootFinder2(aFunc, 0.0, 4.0, 100, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder2.IsDone()) << "Should work with many samples";
  EXPECT_EQ(aRootFinder2.NbSolutions(), 3) << "Should find all 3 roots with many samples";
}

TEST(MathFunctionRootsTest, StateNumberAccess)
{

  QuadraticWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, -5.0, 5.0, 20, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully find roots";
  EXPECT_EQ(aRootFinder.NbSolutions(), 2) << "Should find 2 roots";

  if (aRootFinder.NbSolutions() >= 1)
  {
    int aState1 = aRootFinder.StateNumber(1);
    EXPECT_GE(aState1, 0) << "State number should be non-negative";
  }
  if (aRootFinder.NbSolutions() >= 2)
  {
    int aState2 = aRootFinder.StateNumber(2);
    EXPECT_GE(aState2, 0) << "State number should be non-negative";
  }

  EXPECT_GE(aRootFinder.NbSolutions(), 0) << "Number of solutions should be non-negative";
}

TEST(MathFunctionRootsTest, ShiftedTarget)
{

  QuadraticWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, -2.0, 2.0, 20, 1.0e-10, 1.0e-10, 0.0, -4.0);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should successfully find shifted roots";
  EXPECT_EQ(aRootFinder.NbSolutions(), 1) << "Should find 1 root for x^2 = 0";

  double aRoot = aRootFinder.Value(1);
  EXPECT_NEAR(aRoot, 0.0, 1.0e-8) << "Root should be x = 0";
}

TEST(MathFunctionRootsTest, NotDoneExceptions)
{

  QuadraticWithDerivative aFunc;
  math_FunctionRoots      aRootFinder(aFunc, -5.0, 5.0, 20, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Root finder should be done";
  EXPECT_NO_THROW(aRootFinder.IsAllNull()) << "Should be able to check if all null";
  EXPECT_NO_THROW(aRootFinder.NbSolutions()) << "Should be able to get number of solutions";

  if (aRootFinder.NbSolutions() > 0)
  {
    EXPECT_NO_THROW(aRootFinder.Value(1)) << "Should be able to get first root";
  }
}

TEST(MathFunctionRootsTest, NarrowRange)
{

  LinearWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, 1.9, 2.1, 10, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should work in narrow range";
  EXPECT_EQ(aRootFinder.NbSolutions(), 1) << "Should find the root in narrow range";

  double aRoot = aRootFinder.Value(1);
  EXPECT_NEAR(aRoot, 2.0, 1.0e-8) << "Should find accurate root";
}

TEST(MathFunctionRootsTest, RootAtBoundary)
{

  LinearWithDerivative aFunc;

  math_FunctionRoots aRootFinder1(aFunc, 2.0, 4.0, 10, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder1.IsDone()) << "Should work with root at left boundary";
  EXPECT_EQ(aRootFinder1.NbSolutions(), 1) << "Should find root at boundary";

  math_FunctionRoots aRootFinder2(aFunc, 0.0, 2.0, 10, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder2.IsDone()) << "Should work with root at right boundary";
  EXPECT_EQ(aRootFinder2.NbSolutions(), 1) << "Should find root at boundary";
}

TEST(MathFunctionRootsTest, ReversedRange)
{

  QuadraticWithDerivative aFunc;

  math_FunctionRoots aRootFinder(aFunc, 5.0, -5.0, 20, 1.0e-10, 1.0e-10);

  EXPECT_TRUE(aRootFinder.IsDone()) << "Should handle reversed range";
  EXPECT_EQ(aRootFinder.NbSolutions(), 2) << "Should still find both roots";
}
