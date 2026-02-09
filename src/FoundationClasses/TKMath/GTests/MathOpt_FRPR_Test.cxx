

#include <gtest/gtest.h>

#include <MathOpt_FRPR.hpp>
#include <MathOpt_BFGS.hpp>
#include <math_FRPR.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>
#include <math_Vector.hpp>

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
  };

  struct BealeFunc
  {
    bool Value(const math_Vector& theX, double& theF)
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aT1 = 1.5 - aX * (1.0 - aY);
      const double aT2 = 2.25 - aX * (1.0 - aY * aY);
      const double aT3 = 2.625 - aX * (1.0 - aY * aY * aY);
      theF             = aT1 * aT1 + aT2 * aT2 + aT3 * aT3;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theGrad)
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aY2 = aY * aY;
      const double aY3 = aY2 * aY;
      const double aT1 = 1.5 - aX * (1.0 - aY);
      const double aT2 = 2.25 - aX * (1.0 - aY2);
      const double aT3 = 2.625 - aX * (1.0 - aY3);
      theGrad(1) = -2.0 * aT1 * (1.0 - aY) - 2.0 * aT2 * (1.0 - aY2) - 2.0 * aT3 * (1.0 - aY3);
      theGrad(2) = 2.0 * aT1 * aX + 2.0 * aT2 * 2.0 * aX * aY + 2.0 * aT3 * 3.0 * aX * aY2;
      return true;
    }
  };

  class QuadraticFuncOld : public math_MultipleVarFunctionWithGradient
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
  };

  class RosenbrockFuncOld : public math_MultipleVarFunctionWithGradient
  {
  public:
    int NbVariables() const override { return 2; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      const double aX  = theX(1);
      const double aY  = theX(2);
      const double aT1 = aY - aX * aX;
      const double aT2 = 1.0 - aX;
      theF             = 100.0 * aT1 * aT1 + aT2 * aT2;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      const double aX = theX(1);
      const double aY = theX(2);
      theG(1)         = -400.0 * aX * (aY - aX * aX) - 2.0 * (1.0 - aX);
      theG(2)         = 200.0 * (aY - aX * aX);
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      return Value(theX, theF) && Gradient(theX, theG);
    }
  };

} // namespace

TEST(MathOpt_FRPRTest, Quadratic_FletcherReeves)
{
  QuadraticFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-8;
  aConfig.Formula       = MathOpt::ConjugateGradientFormula::FletcherReeves;

  auto aResult = MathOpt::FRPR(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_FRPRTest, Quadratic_PolakRibiere)
{
  QuadraticFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-8;
  aConfig.Formula       = MathOpt::ConjugateGradientFormula::PolakRibiere;

  auto aResult = MathOpt::FRPR(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_FRPRTest, Booth)
{
  BoothFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-8;

  auto aResult = MathOpt::FRPR(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResult.Solution)(2), 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_FRPRTest, Rosenbrock)
{
  RosenbrockFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 2000;
  aConfig.Tolerance     = 1.0e-6;
  aConfig.Formula       = MathOpt::ConjugateGradientFormula::PolakRibiere;

  auto aResult = MathOpt::FRPR(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-3);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, 1.0e-3);
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-4);
}

TEST(MathOpt_FRPRTest, Sphere3D)
{
  SphereFunc aFunc;

  math_Vector aStart(1, 3);
  aStart(1) = 3.0;
  aStart(2) = -2.0;
  aStart(3) = 4.0;

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-8;

  auto aResult = MathOpt::FRPR(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR((*aResult.Solution)(i), 0.0, THE_TOLERANCE);
  }
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_FRPRTest, Sphere5D)
{
  SphereFunc aFunc;

  math_Vector aStart(1, 5);
  for (int i = 1; i <= 5; ++i)
  {
    aStart(i) = static_cast<double>(i);
  }

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-8;

  auto aResult = MathOpt::FRPR(aFunc, aStart, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  for (int i = 1; i <= 5; ++i)
  {
    EXPECT_NEAR((*aResult.Solution)(i), 0.0, THE_TOLERANCE);
  }
  EXPECT_NEAR(*aResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_FRPRTest, NumericalGradient_Quadratic)
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

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-6;

  auto aResult = MathOpt::FRPRNumerical(aFunc, aStart, 1.0e-8, aConfig);

  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-4);
  EXPECT_NEAR((*aResult.Solution)(2), 2.0, 1.0e-4);
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-4);
}

TEST(MathOpt_FRPRTest, CompareWithOldAPI_Quadratic)
{
  QuadraticFuncOld anOldFunc;
  QuadraticFunc    aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  math_FRPR anOldSolver(anOldFunc, 1.0e-8, 100);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 100;
  aConfig.Tolerance     = 1.0e-8;
  auto aNewResult       = MathOpt::FRPR(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
}

TEST(MathOpt_FRPRTest, CompareWithOldAPI_Rosenbrock)
{
  RosenbrockFuncOld anOldFunc;
  RosenbrockFunc    aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  math_FRPR anOldSolver(anOldFunc, 1.0e-6, 2000);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::FRPRConfig aConfig;
  aConfig.MaxIterations = 2000;
  aConfig.Tolerance     = 1.0e-6;
  auto aNewResult       = MathOpt::FRPR(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), 0.01);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), 0.01);
}

TEST(MathOpt_FRPRTest, CompareWithBFGS)
{
  QuadraticFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  MathOpt::FRPRConfig aFRPRConfig;
  aFRPRConfig.MaxIterations = 100;
  aFRPRConfig.Tolerance     = 1.0e-8;

  auto aFRPRResult = MathOpt::FRPR(aFunc, aStart, aFRPRConfig);
  auto aBFGSResult = MathOpt::BFGS(aFunc, aStart, aConfig);

  ASSERT_TRUE(aFRPRResult.IsDone());
  ASSERT_TRUE(aBFGSResult.IsDone());

  EXPECT_NEAR(*aFRPRResult.Value, *aBFGSResult.Value, THE_TOLERANCE);
  EXPECT_NEAR((*aFRPRResult.Solution)(1), (*aBFGSResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR((*aFRPRResult.Solution)(2), (*aBFGSResult.Solution)(2), THE_TOLERANCE);
}

TEST(MathOpt_FRPRTest, FormulaComparison)
{
  QuadraticFunc aFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  MathOpt::FRPRConfig aConfigFR;
  aConfigFR.MaxIterations = 100;
  aConfigFR.Tolerance     = 1.0e-8;
  aConfigFR.Formula       = MathOpt::ConjugateGradientFormula::FletcherReeves;

  MathOpt::FRPRConfig aConfigPR;
  aConfigPR.MaxIterations = 100;
  aConfigPR.Tolerance     = 1.0e-8;
  aConfigPR.Formula       = MathOpt::ConjugateGradientFormula::PolakRibiere;

  MathOpt::FRPRConfig aConfigHS;
  aConfigHS.MaxIterations = 100;
  aConfigHS.Tolerance     = 1.0e-8;
  aConfigHS.Formula       = MathOpt::ConjugateGradientFormula::HestenesStiefel;

  auto aResultFR = MathOpt::FRPR(aFunc, aStart, aConfigFR);
  auto aResultPR = MathOpt::FRPR(aFunc, aStart, aConfigPR);
  auto aResultHS = MathOpt::FRPR(aFunc, aStart, aConfigHS);

  ASSERT_TRUE(aResultFR.IsDone());
  ASSERT_TRUE(aResultPR.IsDone());
  ASSERT_TRUE(aResultHS.IsDone());

  EXPECT_NEAR(*aResultFR.Value, *aResultPR.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aResultFR.Value, *aResultHS.Value, THE_TOLERANCE);
  EXPECT_NEAR((*aResultFR.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aResultFR.Solution)(2), 2.0, THE_TOLERANCE);
}
