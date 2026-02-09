

#include <gtest/gtest.h>

#include <MathOpt_Newton.hpp>
#include <MathOpt_BFGS.hpp>
#include <math_NewtonMinimum.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>
#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-6;

  struct QuadraticFunc
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      const double aDx = theX(1) - 1.0;
      const double aDy = theX(2) - 2.0;
      theF             = aDx * aDx + aDy * aDy;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theGrad)
    {
      theGrad(1) = 2.0 * (theX(1) - 1.0);
      theGrad(2) = 2.0 * (theX(2) - 2.0);
      return true;
    }

    bool Hessian(const math_Vector&, math_Matrix& theHess)
    {
      theHess(1, 1) = 2.0;
      theHess(1, 2) = 0.0;
      theHess(2, 1) = 0.0;
      theHess(2, 2) = 2.0;
      return true;
    }
  };

  struct RosenbrockFunc
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aT1 = aY - aX * aX;
      const double aT2 = 1.0 - aX;
      theF             = 100.0 * aT1 * aT1 + aT2 * aT2;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theGrad)
    {
      const double aX = theX(1);
      const double aY = theX(2);
      theGrad(1)      = -400.0 * aX * (aY - aX * aX) - 2.0 * (1.0 - aX);
      theGrad(2)      = 200.0 * (aY - aX * aX);
      return true;
    }

    bool Hessian(const math_Vector& theX, math_Matrix& theHess)
    {
      const double aX = theX(1);
      const double aY = theX(2);
      theHess(1, 1)   = 1200.0 * aX * aX - 400.0 * aY + 2.0;
      theHess(1, 2)   = -400.0 * aX;
      theHess(2, 1)   = -400.0 * aX;
      theHess(2, 2)   = 200.0;
      return true;
    }
  };

  struct BoothFunc
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aT1 = aX + 2.0 * aY - 7.0;
      const double aT2 = 2.0 * aX + aY - 5.0;
      theF             = aT1 * aT1 + aT2 * aT2;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theGrad)
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aT1 = aX + 2.0 * aY - 7.0;
      const double aT2 = 2.0 * aX + aY - 5.0;
      theGrad(1)       = 2.0 * aT1 + 4.0 * aT2;
      theGrad(2)       = 4.0 * aT1 + 2.0 * aT2;
      return true;
    }

    bool Hessian(const math_Vector&, math_Matrix& theHess)
    {
      theHess(1, 1) = 10.0;
      theHess(1, 2) = 8.0;
      theHess(2, 1) = 8.0;
      theHess(2, 2) = 10.0;
      return true;
    }
  };

  struct SphereFunc
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      theF = 0.0;
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theF += theX(i) * theX(i);
      }
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theGrad)
    {
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theGrad(i) = 2.0 * theX(i);
      }
      return true;
    }

    bool Hessian(const math_Vector& theX, math_Matrix& theHess)
    {
      const int aLower = theX.Lower();
      const int aUpper = theX.Upper();
      for (int i = aLower; i <= aUpper; ++i)
      {
        for (int j = aLower; j <= aUpper; ++j)
        {
          theHess(i, j) = (i == j) ? 2.0 : 0.0;
        }
      }
      return true;
    }
  };

  class QuadraticFuncOld : public math_MultipleVarFunctionWithHessian
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      const double aDx = theX(1) - 1.0;
      const double aDy = theX(2) - 2.0;
      theF             = aDx * aDx + aDy * aDy;
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
      return Value(theX, theF) && Gradient(theX, theG);
    }

    bool Values(const math_Vector& theX,
                double&            theF,
                math_Vector&       theG,
                math_Matrix&       theH) override
    {
      if (!Value(theX, theF))
        return false;
      if (!Gradient(theX, theG))
        return false;
      theH(1, 1) = 2.0;
      theH(1, 2) = 0.0;
      theH(2, 1) = 0.0;
      theH(2, 2) = 2.0;
      return true;
    }
  };

  class BoothFuncOld : public math_MultipleVarFunctionWithHessian
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aT1 = aX + 2.0 * aY - 7.0;
      const double aT2 = 2.0 * aX + aY - 5.0;
      theF             = aT1 * aT1 + aT2 * aT2;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aT1 = aX + 2.0 * aY - 7.0;
      const double aT2 = 2.0 * aX + aY - 5.0;
      theG(1)          = 2.0 * aT1 + 4.0 * aT2;
      theG(2)          = 4.0 * aT1 + 2.0 * aT2;
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      return Value(theX, theF) && Gradient(theX, theG);
    }

    bool Values(const math_Vector& theX,
                double&            theF,
                math_Vector&       theG,
                math_Matrix&       theH) override
    {
      if (!Value(theX, theF))
        return false;
      if (!Gradient(theX, theG))
        return false;
      theH(1, 1) = 10.0;
      theH(1, 2) = 8.0;
      theH(2, 1) = 8.0;
      theH(2, 2) = 10.0;
      return true;
    }
  };

} // namespace

TEST(MathOpt_NewtonTest, Quadratic)
{
  QuadraticFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-10;

  auto aResult = MathOpt::Newton(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);

  EXPECT_LE(aResult.NbIterations, 5);
}

TEST(MathOpt_NewtonTest, Booth)
{
  BoothFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-10;

  auto aResult = MathOpt::Newton(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NewtonTest, Rosenbrock)
{
  RosenbrockFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.5;
  aStart(2) = 0.5;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-8;

  auto aResult = MathOpt::Newton(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-3);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, 1.0e-3);
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-4);
}

TEST(MathOpt_NewtonTest, Sphere3D)
{
  SphereFunc aFunc;

  math_Vector aStart(1, 3);
  aStart(1) = 3.0;
  aStart(2) = -2.0;
  aStart(3) = 4.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-10;

  auto aResult = MathOpt::Newton(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR((*aResult.Solution)(i), 0.0, THE_TOLERANCE);
  }
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);

  EXPECT_LE(aResult.NbIterations, 5);
}

TEST(MathOpt_NewtonTest, ModifiedNewton_Quadratic)
{
  QuadraticFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-10;

  auto aResult = MathOpt::NewtonModified(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NewtonTest, ModifiedNewton_Rosenbrock)
{
  RosenbrockFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations  = 200;
  aConfig.Tolerance      = 1.0e-6;
  aConfig.Regularization = 1.0e-4;

  auto aResult = MathOpt::NewtonModified(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-3);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, 1.0e-3);
}

TEST(MathOpt_NewtonTest, NumericalHessian_Quadratic)
{

  struct QuadraticGradOnly
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      const double aDx = theX(1) - 1.0;
      const double aDy = theX(2) - 2.0;
      theF             = aDx * aDx + aDy * aDy;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theGrad)
    {
      theGrad(1) = 2.0 * (theX(1) - 1.0);
      theGrad(2) = 2.0 * (theX(2) - 2.0);
      return true;
    }
  };

  QuadraticGradOnly aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-8;

  auto aResult = MathOpt::NewtonNumericalHessian(aFunc, aStart, 1.0e-6, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-4);
  EXPECT_NEAR((*aResult.Solution)(2), 2.0, 1.0e-4);
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-6);
}

TEST(MathOpt_NewtonTest, FullNumerical_Quadratic)
{

  struct QuadraticValueOnly
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      const double aDx = theX(1) - 1.0;
      const double aDy = theX(2) - 2.0;
      theF             = aDx * aDx + aDy * aDy;
      return true;
    }
  };

  QuadraticValueOnly aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-6;

  auto aResult = MathOpt::NewtonNumerical(aFunc, aStart, 1.0e-8, 1.0e-6, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-3);
  EXPECT_NEAR((*aResult.Solution)(2), 2.0, 1.0e-3);
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-4);
}

TEST(MathOpt_NewtonTest, CompareWithOldAPI_Quadratic)
{
  QuadraticFuncOld anOldFunc;
  QuadraticFunc    aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  math_NewtonMinimum anOldSolver(anOldFunc, 1.0e-8, 50, 1.0e-10);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-10;
  auto aNewResult       = MathOpt::Newton(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathOpt_NewtonTest, CompareWithOldAPI_Booth)
{
  BoothFuncOld anOldFunc;
  BoothFunc    aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  math_NewtonMinimum anOldSolver(anOldFunc, 1.0e-8, 50, 1.0e-10);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 50;
  aConfig.Tolerance     = 1.0e-10;
  auto aNewResult       = MathOpt::Newton(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathOpt_NewtonTest, CompareWithBFGS)
{
  QuadraticFunc aQuadFunc;

  struct QuadraticNoBFGS
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      const double aDx = theX(1) - 1.0;
      const double aDy = theX(2) - 2.0;
      theF             = aDx * aDx + aDy * aDy;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theGrad)
    {
      theGrad(1) = 2.0 * (theX(1) - 1.0);
      theGrad(2) = 2.0 * (theX(2) - 2.0);
      return true;
    }
  };

  QuadraticNoBFGS aBFGSFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::Config aBFGSConfig;
  aBFGSConfig.MaxIterations = 100;
  aBFGSConfig.XTolerance    = 1.0e-10;
  aBFGSConfig.FTolerance    = 1.0e-12;

  MathOpt::NewtonConfig aNewtonConfig;
  aNewtonConfig.MaxIterations = 50;
  aNewtonConfig.Tolerance     = 1.0e-10;

  auto aNewtonResult = MathOpt::Newton(aQuadFunc, aStart, aNewtonConfig);
  auto aBFGSResult   = MathOpt::BFGS(aBFGSFunc, aStart, aBFGSConfig);

  ASSERT_TRUE(aNewtonResult.IsDone());
  ASSERT_TRUE(aBFGSResult.IsDone());

  EXPECT_NEAR(*aNewtonResult.Value, *aBFGSResult.Value, THE_TOLERANCE);

  EXPECT_LE(aNewtonResult.NbIterations, aBFGSResult.NbIterations);
}

TEST(MathOpt_NewtonTest, QuadraticConvergence)
{
  QuadraticFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 100.0;
  aStart(2) = 100.0;

  MathOpt::NewtonConfig aConfig;
  aConfig.MaxIterations = 10;
  aConfig.Tolerance     = 1.0e-12;

  auto aResult = MathOpt::Newton(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());

  EXPECT_LE(aResult.NbIterations, 2);
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-10);
}
