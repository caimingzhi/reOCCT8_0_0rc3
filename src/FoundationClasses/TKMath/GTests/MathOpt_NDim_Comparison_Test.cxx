

#include <gtest/gtest.h>

#include <MathOpt_Powell.hpp>
#include <MathOpt_BFGS.hpp>

#include <math_Powell.hpp>
#include <math_BFGS.hpp>
#include <math_MultipleVarFunction.hpp>
#include <math_MultipleVarFunctionWithGradient.hpp>
#include <math_Matrix.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-6;

  class QuadraticFuncOld : public math_MultipleVarFunction
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
  };

  class RosenbrockFuncOld : public math_MultipleVarFunction
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
  };

  class BoothFuncOld : public math_MultipleVarFunction
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
  };

  class SphereFuncOld : public math_MultipleVarFunction
  {
  private:
    int myN;

  public:
    SphereFuncOld(int theN)
        : myN(theN)
    {
    }

    int NbVariables() const override { return myN; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      theF = 0.0;
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theF += theX(i) * theX(i);
      }
      return true;
    }
  };

  class QuadraticFuncGradOld : public math_MultipleVarFunctionWithGradient
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

  class RosenbrockFuncGradOld : public math_MultipleVarFunctionWithGradient
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

  class BoothFuncGradOld : public math_MultipleVarFunctionWithGradient
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
  };

  class SphereFuncGradOld : public math_MultipleVarFunctionWithGradient
  {
  private:
    int myN;

  public:
    SphereFuncGradOld(int theN)
        : myN(theN)
    {
    }

    int NbVariables() const override { return myN; }

    bool Value(const math_Vector& theX, double& theF) override
    {
      theF = 0.0;
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theF += theX(i) * theX(i);
      }
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) override
    {
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theG(i) = 2.0 * theX(i);
      }
      return true;
    }

    bool Values(const math_Vector& theX, double& theF, math_Vector& theG) override
    {
      return Value(theX, theF) && Gradient(theX, theG);
    }
  };

  struct QuadraticFuncNew
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

  struct RosenbrockFuncNew
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

  struct BoothFuncNew
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

  struct SphereFuncNew
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

  math_Matrix CreateIdentityMatrix(int theN)
  {
    math_Matrix aMat(1, theN, 1, theN, 0.0);
    for (int i = 1; i <= theN; ++i)
    {
      aMat(i, i) = 1.0;
    }
    return aMat;
  }

} // namespace

TEST(MathOpt_NDim_ComparisonTest, Powell_Quadratic)
{
  QuadraticFuncOld anOldFunc;
  QuadraticFuncNew aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  math_Powell anOldSolver(anOldFunc, 1.0e-8, 200);
  math_Matrix aDirections = CreateIdentityMatrix(2);
  anOldSolver.Perform(anOldFunc, aStart, aDirections);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;
  auto aNewResult       = MathOpt::Powell(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NDim_ComparisonTest, Powell_Booth)
{
  BoothFuncOld anOldFunc;
  BoothFuncNew aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  math_Powell anOldSolver(anOldFunc, 1.0e-8, 200);
  math_Matrix aDirections = CreateIdentityMatrix(2);
  anOldSolver.Perform(anOldFunc, aStart, aDirections);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;
  auto aNewResult       = MathOpt::Powell(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NDim_ComparisonTest, Powell_Rosenbrock)
{
  RosenbrockFuncOld anOldFunc;
  RosenbrockFuncNew aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  math_Powell anOldSolver(anOldFunc, 1.0e-6, 1000);
  math_Matrix aDirections = CreateIdentityMatrix(2);
  anOldSolver.Perform(anOldFunc, aStart, aDirections);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 1000;
  aConfig.XTolerance    = 1.0e-6;
  aConfig.FTolerance    = 1.0e-8;
  auto aNewResult       = MathOpt::Powell(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), 1.0e-3);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), 1.0e-3);

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, 1.0e-3);
  EXPECT_NEAR((*aNewResult.Solution)(2), 1.0, 1.0e-3);
}

TEST(MathOpt_NDim_ComparisonTest, Powell_Sphere3D)
{
  SphereFuncOld anOldFunc(3);
  SphereFuncNew aNewFunc;

  math_Vector aStart(1, 3);
  aStart(1) = 3.0;
  aStart(2) = -2.0;
  aStart(3) = 4.0;

  math_Powell anOldSolver(anOldFunc, 1.0e-8, 200);
  math_Matrix aDirections = CreateIdentityMatrix(3);
  anOldSolver.Perform(anOldFunc, aStart, aDirections);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;
  auto aNewResult       = MathOpt::Powell(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR(anOldSolver.Location()(i), (*aNewResult.Solution)(i), THE_TOLERANCE);
    EXPECT_NEAR((*aNewResult.Solution)(i), 0.0, THE_TOLERANCE);
  }
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NDim_ComparisonTest, BFGS_Quadratic)
{
  QuadraticFuncGradOld anOldFunc;
  QuadraticFuncNew     aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  math_BFGS anOldSolver(2, 1.0e-8, 100);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;
  auto aNewResult       = MathOpt::BFGS(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NDim_ComparisonTest, BFGS_Booth)
{
  BoothFuncGradOld anOldFunc;
  BoothFuncNew     aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  math_BFGS anOldSolver(2, 1.0e-8, 100);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;
  auto aNewResult       = MathOpt::BFGS(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_TOLERANCE);
  EXPECT_NEAR((*aNewResult.Solution)(2), 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NDim_ComparisonTest, BFGS_Rosenbrock)
{
  RosenbrockFuncGradOld anOldFunc;
  RosenbrockFuncNew     aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  math_BFGS anOldSolver(2, 1.0e-6, 1000);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 1000;
  aConfig.XTolerance    = 1.0e-6;
  aConfig.FTolerance    = 1.0e-8;
  auto aNewResult       = MathOpt::BFGS(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), 1.0e-3);
  EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), 1.0e-3);

  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, 1.0e-3);
  EXPECT_NEAR((*aNewResult.Solution)(2), 1.0, 1.0e-3);
}

TEST(MathOpt_NDim_ComparisonTest, BFGS_Sphere3D)
{
  SphereFuncGradOld anOldFunc(3);
  SphereFuncNew     aNewFunc;

  math_Vector aStart(1, 3);
  aStart(1) = 3.0;
  aStart(2) = -2.0;
  aStart(3) = 4.0;

  math_BFGS anOldSolver(3, 1.0e-8, 100);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;
  auto aNewResult       = MathOpt::BFGS(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR(anOldSolver.Location()(i), (*aNewResult.Solution)(i), THE_TOLERANCE);
    EXPECT_NEAR((*aNewResult.Solution)(i), 0.0, THE_TOLERANCE);
  }
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_NDim_ComparisonTest, IterationCount_BFGSVsPowell)
{
  QuadraticFuncNew aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 10.0;
  aStart(2) = 10.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 500;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aPowellResult = MathOpt::Powell(aNewFunc, aStart, aConfig);
  auto aBFGSResult   = MathOpt::BFGS(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(aPowellResult.IsDone());
  ASSERT_TRUE(aBFGSResult.IsDone());

  EXPECT_NEAR(*aPowellResult.Value, *aBFGSResult.Value, THE_TOLERANCE);

  EXPECT_LT(aBFGSResult.NbIterations, aPowellResult.NbIterations);
}

TEST(MathOpt_NDim_ComparisonTest, IterationCount_LBFGSVsBFGS)
{
  SphereFuncNew aNewFunc;

  math_Vector aStart(1, 5);
  for (int i = 1; i <= 5; ++i)
  {
    aStart(i) = static_cast<double>(i);
  }

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aBFGSResult  = MathOpt::BFGS(aNewFunc, aStart, aConfig);
  auto aLBFGSResult = MathOpt::LBFGS(aNewFunc, aStart, 10, aConfig);

  ASSERT_TRUE(aBFGSResult.IsDone());
  ASSERT_TRUE(aLBFGSResult.IsDone());

  EXPECT_NEAR(*aBFGSResult.Value, *aLBFGSResult.Value, THE_TOLERANCE);

  for (int i = 1; i <= 5; ++i)
  {
    EXPECT_NEAR((*aBFGSResult.Solution)(i), 0.0, THE_TOLERANCE);
    EXPECT_NEAR((*aLBFGSResult.Solution)(i), 0.0, THE_TOLERANCE);
  }
}

TEST(MathOpt_NDim_ComparisonTest, Accuracy_BFGSVsOld)
{
  QuadraticFuncGradOld anOldFunc;
  QuadraticFuncNew     aNewFunc;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 7.0;

  const double aTightTol = 1.0e-12;

  math_BFGS anOldSolver(2, aTightTol, 200);
  anOldSolver.Perform(anOldFunc, aStart);

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = aTightTol;
  aConfig.FTolerance    = 1.0e-14;
  auto aNewResult       = MathOpt::BFGS(aNewFunc, aStart, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location()(1), 1.0, 1.0e-8);
  EXPECT_NEAR(anOldSolver.Location()(2), 2.0, 1.0e-8);
  EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, 1.0e-8);
  EXPECT_NEAR((*aNewResult.Solution)(2), 2.0, 1.0e-8);
}

TEST(MathOpt_NDim_ComparisonTest, DifferentStartingPoints)
{
  QuadraticFuncGradOld anOldFunc;
  QuadraticFuncNew     aNewFunc;

  std::vector<std::pair<double, double>> aStartPoints = {{0.0, 0.0},
                                                         {10.0, 10.0},
                                                         {-5.0, 5.0},
                                                         {100.0, -50.0}};

  for (const auto& aPoint : aStartPoints)
  {
    math_Vector aStart(1, 2);
    aStart(1) = aPoint.first;
    aStart(2) = aPoint.second;

    math_BFGS anOldSolver(2, 1.0e-8, 200);
    anOldSolver.Perform(anOldFunc, aStart);

    MathOpt::Config aConfig;
    aConfig.MaxIterations = 200;
    aConfig.XTolerance    = 1.0e-8;
    aConfig.FTolerance    = 1.0e-10;
    auto aNewResult       = MathOpt::BFGS(aNewFunc, aStart, aConfig);

    ASSERT_TRUE(anOldSolver.IsDone())
      << "Old API failed for start point (" << aPoint.first << ", " << aPoint.second << ")";
    ASSERT_TRUE(aNewResult.IsDone())
      << "New API failed for start point (" << aPoint.first << ", " << aPoint.second << ")";

    EXPECT_NEAR(anOldSolver.Location()(1), (*aNewResult.Solution)(1), THE_TOLERANCE);
    EXPECT_NEAR(anOldSolver.Location()(2), (*aNewResult.Solution)(2), THE_TOLERANCE);
    EXPECT_NEAR((*aNewResult.Solution)(1), 1.0, THE_TOLERANCE);
    EXPECT_NEAR((*aNewResult.Solution)(2), 2.0, THE_TOLERANCE);
  }
}
