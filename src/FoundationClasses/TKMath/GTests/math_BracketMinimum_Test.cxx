

#include <math_BracketMinimum.hpp>
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
      double x2 = theX * theX;
      double x3 = x2 * theX;
      double x4 = x3 * theX;
      theF      = x4 - 4.0 * x3 + 6.0 * x2 - 4.0 * theX + 5.0;
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

  class ExponentialFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = exp(theX);
      return true;
    }
  };

  class MultipleMinFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = sin(theX) + 0.1 * theX;
      return true;
    }
  };

} // namespace

TEST(MathBracketMinimumTest, QuadraticMinimumBracketing)
{

  QuadraticFunction aFunc;

  math_BracketMinimum aBracketer(aFunc, 0.0, 1.0);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should successfully bracket quadratic minimum";

  double aA, aB, aC;
  aBracketer.Values(aA, aB, aC);

  EXPECT_TRUE((aA < aB && aB < aC) || (aC < aB && aB < aA)) << "B should be between A and C";

  EXPECT_GT(aB, 1.0) << "Bracketed minimum should be greater than 1";
  EXPECT_LT(aB, 3.0) << "Bracketed minimum should be less than 3";

  double aFA, aFB, aFC;
  aBracketer.FunctionValues(aFA, aFB, aFC);

  EXPECT_LT(aFB, aFA) << "F(B) should be less than F(A)";
  EXPECT_LT(aFB, aFC) << "F(B) should be less than F(C)";
}

TEST(MathBracketMinimumTest, ConstructorWithPrecomputedValues)
{

  QuadraticFunction aFunc;

  double aA = 0.0, aB = 1.0;
  double aFA = (aA - 2.0) * (aA - 2.0) + 1.0;
  double aFB = (aB - 2.0) * (aB - 2.0) + 1.0;

  math_BracketMinimum aBracketer(aFunc, aA, aB, aFA, aFB);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should successfully bracket with precomputed values";

  double aRetA, aRetB, aRetC;
  aBracketer.Values(aRetA, aRetB, aRetC);

  EXPECT_TRUE((aRetA < aRetB && aRetB < aRetC) || (aRetC < aRetB && aRetB < aRetA));
}

TEST(MathBracketMinimumTest, ConstructorWithOnePrecomputedValue)
{

  QuadraticFunction aFunc;

  double aA = 0.0, aB = 1.0;
  double aFA = 5.0;

  math_BracketMinimum aBracketer(aFunc, aA, aB, aFA);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should successfully bracket with one precomputed value";
}

TEST(MathBracketMinimumTest, QuarticFunctionBracketing)
{

  QuarticFunction aFunc;

  math_BracketMinimum aBracketer(aFunc, 0.0, 0.5);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should bracket quartic function minimum";

  double aA, aB, aC;
  aBracketer.Values(aA, aB, aC);

  EXPECT_GT(aB, 0.5) << "Bracketed point should be greater than 0.5";
  EXPECT_LT(aB, 1.5) << "Bracketed point should be less than 1.5";
}

TEST(MathBracketMinimumTest, CosineFunction)
{

  CosineFunction aFunc;

  math_BracketMinimum aBracketer(aFunc, 2.0, 4.0);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should bracket cosine function minimum";

  double aA, aB, aC;
  aBracketer.Values(aA, aB, aC);

  EXPECT_GT(aB, 2.5) << "Bracketed point should be greater than 2.5";
  EXPECT_LT(aB, 4.5) << "Bracketed point should be less than 4.5";

  double aFA, aFB, aFC;
  aBracketer.FunctionValues(aFA, aFB, aFC);

  EXPECT_LT(aFB, aFA) << "F(B) should be less than F(A)";
  EXPECT_LT(aFB, aFC) << "F(B) should be less than F(C)";
}

TEST(MathBracketMinimumTest, SetLimits)
{

  QuadraticFunction aFunc;

  math_BracketMinimum aBracketer(0.0, 1.0);
  aBracketer.SetLimits(1.5, 3.0);
  aBracketer.Perform(aFunc);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should find minimum within limits";

  double aA, aB, aC;
  aBracketer.Values(aA, aB, aC);

  EXPECT_GE(aA, 0.5) << "A should be reasonably within limits";
  EXPECT_LE(aA, 3.5) << "A should be reasonably within limits";
  EXPECT_GE(aB, 0.5) << "B should be reasonably within limits";
  EXPECT_LE(aB, 3.5) << "B should be reasonably within limits";
  EXPECT_GE(aC, 0.5) << "C should be reasonably within limits";
  EXPECT_LE(aC, 3.5) << "C should be reasonably within limits";
}

TEST(MathBracketMinimumTest, SetPrecomputedValues)
{

  QuadraticFunction aFunc;

  math_BracketMinimum aBracketer(0.0, 1.0);
  aBracketer.SetFA(5.0);
  aBracketer.SetFB(2.0);
  aBracketer.Perform(aFunc);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should work with precomputed values";
}

TEST(MathBracketMinimumTest, NoMinimumFunction)
{

  ExponentialFunction aFunc;

  math_BracketMinimum aBracketer(aFunc, -1.0, 0.0);

  EXPECT_TRUE(true) << "Exponential function test completed without crash";
}

TEST(MathBracketMinimumTest, MultipleLocalMinima)
{

  MultipleMinFunction aFunc;

  math_BracketMinimum aBracketer(aFunc, -2.0, 0.0);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should bracket one of the minima";

  double aFA, aFB, aFC;
  aBracketer.FunctionValues(aFA, aFB, aFC);

  EXPECT_LT(aFB, aFA) << "F(B) should be less than F(A)";
  EXPECT_LT(aFB, aFC) << "F(B) should be less than F(C)";
}

TEST(MathBracketMinimumTest, UnperformedState)
{

  math_BracketMinimum aBracketer(0.0, 1.0);

  EXPECT_FALSE(aBracketer.IsDone()) << "Bracketer should not be done before Perform()";
}

TEST(MathBracketMinimumTest, VeryNarrowInitialBounds)
{

  QuadraticFunction aFunc;

  math_BracketMinimum aBracketer(aFunc, 1.99, 2.01);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should handle narrow initial bounds";

  double aA, aB, aC;
  aBracketer.Values(aA, aB, aC);

  EXPECT_GT(aA, 1.5) << "Bracketing points should be reasonable";
  EXPECT_LT(aC, 2.5) << "Bracketing points should be reasonable";
}

TEST(MathBracketMinimumTest, ReverseOrderInitialPoints)
{

  QuadraticFunction aFunc;

  math_BracketMinimum aBracketer(aFunc, 4.0, 0.0);

  EXPECT_TRUE(aBracketer.IsDone()) << "Should handle reverse order initial points";

  double aA, aB, aC;
  aBracketer.Values(aA, aB, aC);

  EXPECT_GT(aB, -1.0) << "Bracketed point should be reasonable";
  EXPECT_LT(aB, 5.0) << "Bracketed point should be reasonable";
}

TEST(MathBracketMinimumTest, RestrictiveLimits)
{

  QuadraticFunction aFunc;

  math_BracketMinimum aBracketer(0.0, 0.5);
  aBracketer.SetLimits(0.0, 1.0);
  aBracketer.Perform(aFunc);

  if (aBracketer.IsDone())
  {
    double aA, aB, aC;
    aBracketer.Values(aA, aB, aC);

    EXPECT_GE(aA, -0.1) << "A should respect lower limit";
    EXPECT_LE(aA, 1.1) << "A should respect upper limit";
    EXPECT_GE(aB, -0.1) << "B should respect lower limit";
    EXPECT_LE(aB, 1.1) << "B should respect upper limit";
    EXPECT_GE(aC, -0.1) << "C should respect lower limit";
    EXPECT_LE(aC, 1.1) << "C should respect upper limit";
  }
}
