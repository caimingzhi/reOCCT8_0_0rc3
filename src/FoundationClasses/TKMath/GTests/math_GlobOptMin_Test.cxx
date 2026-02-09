

#include <math_GlobOptMin.hpp>
#include <math_MultipleVarFunction.hpp>
#include <math_Vector.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class QuadraticFunction : public math_MultipleVarFunction
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
  };

  class MultiModalFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double x = theX(1);
      double y = theX(2);
      theF     = sin(x) + sin(y) + 0.1 * (x * x + y * y);
      return true;
    }
  };

  class MultiModal1DFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 1; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      double x = theX(1);
      theF     = sin(x) + 0.5 * sin(3.0 * x);
      return true;
    }
  };

  class RosenbrockFunction : public math_MultipleVarFunction
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
  };

  class LinearFunction : public math_MultipleVarFunction
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      theF = theX(1) + theX(2);
      return true;
    }
  };

} // namespace

TEST(MathGlobOptMinTest, QuadraticFunctionOptimization)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 3.0;
  aUpperBorder(2) = 4.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should successfully optimize quadratic function";
  EXPECT_GT(aSolver.NbExtrema(), 0) << "Should find at least one extremum";

  math_Vector aSol(1, 2);
  aSolver.Points(1, aSol);

  EXPECT_NEAR(aSol(1), 1.0, 1.0e-1) << "Should find minimum near x = 1";
  EXPECT_NEAR(aSol(2), 2.0, 1.0e-1) << "Should find minimum near y = 2";
  EXPECT_NEAR(aSolver.GetF(), 0.0, 1.0e-2) << "Function value at minimum should be near 0";
}

TEST(MathGlobOptMinTest, MultiModalFunctionOptimization)
{

  MultiModalFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -5.0;
  aLowerBorder(2) = -5.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 5.0;
  aUpperBorder(2) = 5.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);
  aSolver.Perform(false);

  EXPECT_TRUE(aSolver.isDone()) << "Should successfully optimize multi-modal function";
  EXPECT_GE(aSolver.NbExtrema(), 1) << "Should find at least one extremum for multi-modal function";

  math_Vector aSol(1, 2);
  aSolver.Points(1, aSol);
  EXPECT_TRUE(aSol(1) >= -5.0 && aSol(1) <= 5.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSol(2) >= -5.0 && aSol(2) <= 5.0) << "Solution should be within bounds";
}

TEST(MathGlobOptMinTest, OneDimensionalOptimization)
{

  MultiModal1DFunction aFunc;

  math_Vector aLowerBorder(1, 1);
  aLowerBorder(1) = 0.0;

  math_Vector aUpperBorder(1, 1);
  aUpperBorder(1) = 2.0 * M_PI;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);
  aSolver.Perform(false);

  EXPECT_TRUE(aSolver.isDone()) << "Should successfully optimize 1D function";
  EXPECT_GT(aSolver.NbExtrema(), 0) << "Should find at least one extremum";

  math_Vector aSol(1, 1);
  aSolver.Points(1, aSol);
  EXPECT_TRUE(aSol(1) >= 0.0 && aSol(1) <= 2.0 * M_PI) << "Solution should be within bounds";
}

TEST(MathGlobOptMinTest, SingleSolutionSearch)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 3.0;
  aUpperBorder(2) = 4.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should find single solution";
  EXPECT_EQ(aSolver.NbExtrema(), 1) << "Should find exactly one extremum";
}

TEST(MathGlobOptMinTest, AllSolutionsSearch)
{

  MultiModalFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -3.0;
  aLowerBorder(2) = -3.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 3.0;
  aUpperBorder(2) = 3.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);
  aSolver.Perform(false);

  EXPECT_TRUE(aSolver.isDone()) << "Should find all solutions";
  EXPECT_GE(aSolver.NbExtrema(), 1) << "Should find at least one extremum";
}

TEST(MathGlobOptMinTest, CustomTolerances)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 3.0;
  aUpperBorder(2) = 4.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder, 9, 1.0e-3, 1.0e-8);

  double aDiscTol, aSameTol;
  aSolver.GetTol(aDiscTol, aSameTol);
  EXPECT_NEAR(aDiscTol, 1.0e-3, 1.0e-12) << "Discretization tolerance should match";
  EXPECT_NEAR(aSameTol, 1.0e-8, 1.0e-12) << "Same tolerance should match";

  aSolver.SetTol(1.0e-2, 1.0e-6);
  aSolver.GetTol(aDiscTol, aSameTol);
  EXPECT_NEAR(aDiscTol, 1.0e-2, 1.0e-12) << "Updated discretization tolerance should match";
  EXPECT_NEAR(aSameTol, 1.0e-6, 1.0e-12) << "Updated same tolerance should match";

  aSolver.Perform(true);
  EXPECT_TRUE(aSolver.isDone()) << "Should work with custom tolerances";
}

TEST(MathGlobOptMinTest, LocalParamsReduction)
{

  QuadraticFunction aFunc;

  math_Vector aGlobalLower(1, 2);
  aGlobalLower(1) = -5.0;
  aGlobalLower(2) = -5.0;

  math_Vector aGlobalUpper(1, 2);
  aGlobalUpper(1) = 5.0;
  aGlobalUpper(2) = 5.0;

  math_GlobOptMin aSolver(&aFunc, aGlobalLower, aGlobalUpper);

  math_Vector aLocalLower(1, 2);
  aLocalLower(1) = 0.0;
  aLocalLower(2) = 1.0;

  math_Vector aLocalUpper(1, 2);
  aLocalUpper(1) = 2.0;
  aLocalUpper(2) = 3.0;

  aSolver.SetLocalParams(aLocalLower, aLocalUpper);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should work with local parameters";

  math_Vector aSol(1, 2);
  aSolver.Points(1, aSol);
  EXPECT_TRUE(aSol(1) >= 0.0 && aSol(1) <= 2.0) << "Solution should be within local bounds";
  EXPECT_TRUE(aSol(2) >= 1.0 && aSol(2) <= 3.0) << "Solution should be within local bounds";
}

TEST(MathGlobOptMinTest, ContinuitySettings)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 3.0;
  aUpperBorder(2) = 4.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);

  int aDefaultCont = aSolver.GetContinuity();
  EXPECT_GE(aDefaultCont, 0) << "Default continuity should be non-negative";

  aSolver.SetContinuity(1);
  EXPECT_EQ(aSolver.GetContinuity(), 1) << "Continuity should be set to 1";

  aSolver.SetContinuity(2);
  EXPECT_EQ(aSolver.GetContinuity(), 2) << "Continuity should be set to 2";

  aSolver.Perform(true);
  EXPECT_TRUE(aSolver.isDone()) << "Should work with different continuity settings";
}

TEST(MathGlobOptMinTest, FunctionalMinimalValue)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 3.0;
  aUpperBorder(2) = 4.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);

  double aDefaultMin = aSolver.GetFunctionalMinimalValue();
  EXPECT_EQ(aDefaultMin, -Precision::Infinite()) << "Default should be negative infinity";

  aSolver.SetFunctionalMinimalValue(-1.0);
  EXPECT_NEAR(aSolver.GetFunctionalMinimalValue(), -1.0, 1.0e-12)
    << "Functional minimal value should be set";

  aSolver.Perform(true);
  EXPECT_TRUE(aSolver.isDone()) << "Should work with functional minimal value";
}

TEST(MathGlobOptMinTest, LipschitzConstantState)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 3.0;
  aUpperBorder(2) = 4.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);

  bool aDefaultState = aSolver.GetLipConstState();
  EXPECT_FALSE(aDefaultState) << "Default Lipschitz constant should be unlocked";

  aSolver.SetLipConstState(true);
  EXPECT_TRUE(aSolver.GetLipConstState()) << "Lipschitz constant should be locked";

  aSolver.SetLipConstState(false);
  EXPECT_FALSE(aSolver.GetLipConstState()) << "Lipschitz constant should be unlocked";

  aSolver.Perform(true);
  EXPECT_TRUE(aSolver.isDone()) << "Should work with Lipschitz constant state management";
}

TEST(MathGlobOptMinTest, RosenbrockOptimization)
{

  RosenbrockFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -1.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 2.0;
  aUpperBorder(2) = 3.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder, 50, 1.0e-2, 1.0e-6);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should handle Rosenbrock function";
  EXPECT_GT(aSolver.NbExtrema(), 0) << "Should find at least one extremum";

  math_Vector aSol(1, 2);
  aSolver.Points(1, aSol);

  EXPECT_TRUE(aSol(1) >= -2.0 && aSol(1) <= 2.0) << "Solution should be within bounds";
  EXPECT_TRUE(aSol(2) >= -1.0 && aSol(2) <= 3.0) << "Solution should be within bounds";
}

TEST(MathGlobOptMinTest, LinearFunctionOptimization)
{

  LinearFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = 0.0;
  aLowerBorder(2) = 0.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 2.0;
  aUpperBorder(2) = 2.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should handle linear function";
  EXPECT_GT(aSolver.NbExtrema(), 0) << "Should find at least one extremum";

  math_Vector aSol(1, 2);
  aSolver.Points(1, aSol);

  EXPECT_NEAR(aSol(1), 0.0, 1.0e-1) << "Linear function minimum should be near lower bound";
  EXPECT_NEAR(aSol(2), 0.0, 1.0e-1) << "Linear function minimum should be near lower bound";
}

TEST(MathGlobOptMinTest, SetGlobalParamsMethod)
{

  QuadraticFunction aFunc1;
  LinearFunction    aFunc2;

  math_Vector aLowerBorder1(1, 2);
  aLowerBorder1(1) = -2.0;
  aLowerBorder1(2) = -1.0;

  math_Vector aUpperBorder1(1, 2);
  aUpperBorder1(1) = 3.0;
  aUpperBorder1(2) = 4.0;

  math_GlobOptMin aSolver(&aFunc1, aLowerBorder1, aUpperBorder1);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should work with first function";

  math_Vector aLowerBorder2(1, 2);
  aLowerBorder2(1) = 0.0;
  aLowerBorder2(2) = 0.0;

  math_Vector aUpperBorder2(1, 2);
  aUpperBorder2(1) = 1.0;
  aUpperBorder2(2) = 1.0;

  aSolver.SetGlobalParams(&aFunc2, aLowerBorder2, aUpperBorder2);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should work after changing global params";
}

TEST(MathGlobOptMinTest, MultipleExtremaAccess)
{

  MultiModalFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = -2.0;
  aLowerBorder(2) = -2.0;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 2.0;
  aUpperBorder(2) = 2.0;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder);
  aSolver.Perform(false);

  EXPECT_TRUE(aSolver.isDone()) << "Should find multiple solutions";
  int aNbSol = aSolver.NbExtrema();
  EXPECT_GT(aNbSol, 0) << "Should have at least one solution";

  for (int i = 1; i <= aNbSol; ++i)
  {
    math_Vector aSol(1, 2);
    EXPECT_NO_THROW(aSolver.Points(i, aSol)) << "Should be able to access solution " << i;
    EXPECT_TRUE(aSol(1) >= -2.0 && aSol(1) <= 2.0)
      << "Solution " << i << " should be within bounds";
    EXPECT_TRUE(aSol(2) >= -2.0 && aSol(2) <= 2.0)
      << "Solution " << i << " should be within bounds";
  }
}

TEST(MathGlobOptMinTest, SmallSearchSpace)
{

  QuadraticFunction aFunc;

  math_Vector aLowerBorder(1, 2);
  aLowerBorder(1) = 0.99;
  aLowerBorder(2) = 1.99;

  math_Vector aUpperBorder(1, 2);
  aUpperBorder(1) = 1.01;
  aUpperBorder(2) = 2.01;

  math_GlobOptMin aSolver(&aFunc, aLowerBorder, aUpperBorder, 9, 1.0e-3, 1.0e-8);
  aSolver.Perform(true);

  EXPECT_TRUE(aSolver.isDone()) << "Should handle small search space";

  math_Vector aSol(1, 2);
  aSolver.Points(1, aSol);
  EXPECT_NEAR(aSol(1), 1.0, 0.02) << "Should find solution close to global minimum";
  EXPECT_NEAR(aSol(2), 2.0, 0.02) << "Should find solution close to global minimum";
}
