

#include <gtest/gtest.h>

#include <MathOpt_Brent.hpp>

#include <math_BrentMinimum.hpp>
#include <math_Function.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-7;
  constexpr double THE_PI        = 3.14159265358979323846;

  class ParabolaFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = (theX - 3.0) * (theX - 3.0) + 1.0;
      return true;
    }
  };

  class ParabolaFunc2Old : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX - 4.0 * theX + 3.0;
      return true;
    }
  };

  class CosFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::cos(theX);
      return true;
    }
  };

  class QuarticFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      const double aX2 = theX * theX;
      theF             = aX2 * aX2 - 2.0 * aX2;
      return true;
    }
  };

  class CoshLikeFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = std::exp(theX) + std::exp(-theX);
      return true;
    }
  };

  class SquareFuncOld : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = theX * theX;
      return true;
    }
  };

  struct ParabolaFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = (theX - 3.0) * (theX - 3.0) + 1.0;
      return true;
    }
  };

  struct ParabolaFunc2New
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX - 4.0 * theX + 3.0;
      return true;
    }
  };

  struct CosFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = std::cos(theX);
      return true;
    }
  };

  struct QuarticFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      const double aX2 = theX * theX;
      theF             = aX2 * aX2 - 2.0 * aX2;
      return true;
    }
  };

  struct CoshLikeFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = std::exp(theX) + std::exp(-theX);
      return true;
    }
  };

  struct SquareFuncNew
  {
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX;
      return true;
    }
  };
} // namespace

TEST(MathOpt_1D_ComparisonTest, Brent_Parabola)
{
  ParabolaFuncOld anOldFunc;
  ParabolaFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, 0.0, 3.0, 6.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, 0.0, 6.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Brent_ParabolaNegativeMinimum)
{
  ParabolaFunc2Old anOldFunc;
  ParabolaFunc2New aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, 0.0, 2.0, 5.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, 0.0, 5.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Brent_Cosine)
{
  CosFuncOld anOldFunc;
  CosFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, 2.0, THE_PI, 4.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, 2.0, 4.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, THE_PI, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Brent_QuarticRight)
{
  QuarticFuncOld anOldFunc;
  QuarticFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, 0.0, 1.0, 2.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, 0.0, 2.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, 1.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Brent_QuarticLeft)
{
  QuarticFuncOld anOldFunc;
  QuarticFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, -2.0, -1.0, 0.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, -2.0, 0.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, -1.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Brent_CoshLike)
{
  CoshLikeFuncOld anOldFunc;
  CoshLikeFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, -5.0, 0.0, 5.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, -5.0, 5.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, 0.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Brent_Square)
{
  SquareFuncOld anOldFunc;
  SquareFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, -10.0, 0.0, 10.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, -10.0, 10.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(anOldSolver.Minimum(), *aNewResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, 0.0, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Value, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, IterationCount_BrentVsGolden)
{
  ParabolaFuncNew aFunc;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;

  MathOpt::ScalarResult aBrentResult  = MathOpt::Brent(aFunc, 0.0, 10.0, aConfig);
  MathOpt::ScalarResult aGoldenResult = MathOpt::Golden(aFunc, 0.0, 10.0, aConfig);

  ASSERT_TRUE(aBrentResult.IsDone());
  ASSERT_TRUE(aGoldenResult.IsDone());

  EXPECT_NEAR(*aBrentResult.Root, *aGoldenResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aBrentResult.Value, *aGoldenResult.Value, THE_TOLERANCE);

  EXPECT_LE(aBrentResult.NbIterations, aGoldenResult.NbIterations);
}

TEST(MathOpt_1D_ComparisonTest, Accuracy_BrentVsOld)
{
  ParabolaFuncOld anOldFunc;
  ParabolaFuncNew aNewFunc;

  const double aTightTol = 1.0e-12;

  math_BrentMinimum anOldSolver(aTightTol, 200);
  anOldSolver.Perform(anOldFunc, 0.0, 3.0, 10.0);

  MathOpt::Config aConfig;
  aConfig.XTolerance               = aTightTol;
  aConfig.MaxIterations            = 200;
  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, 0.0, 10.0, aConfig);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), 3.0, 1.0e-8);
  EXPECT_NEAR(*aNewResult.Root, 3.0, 1.0e-8);
}

TEST(MathOpt_1D_ComparisonTest, WideInterval_Parabola)
{
  ParabolaFuncOld anOldFunc;
  ParabolaFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 200);
  anOldSolver.Perform(anOldFunc, -100.0, 3.0, 100.0);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, -100.0, 100.0);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, 3.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, NarrowInterval_Parabola)
{
  ParabolaFuncOld anOldFunc;
  ParabolaFuncNew aNewFunc;

  math_BrentMinimum anOldSolver(THE_TOLERANCE, 100);
  anOldSolver.Perform(anOldFunc, 2.9, 3.0, 3.1);

  MathOpt::ScalarResult aNewResult = MathOpt::Brent(aNewFunc, 2.9, 3.1);

  ASSERT_TRUE(anOldSolver.IsDone());
  ASSERT_TRUE(aNewResult.IsDone());

  EXPECT_NEAR(anOldSolver.Location(), *aNewResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aNewResult.Root, 3.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Golden_Parabola)
{
  ParabolaFuncNew aNewFunc;

  MathOpt::ScalarResult aBrentResult  = MathOpt::Brent(aNewFunc, 0.0, 10.0);
  MathOpt::ScalarResult aGoldenResult = MathOpt::Golden(aNewFunc, 0.0, 10.0);

  ASSERT_TRUE(aBrentResult.IsDone());
  ASSERT_TRUE(aGoldenResult.IsDone());

  EXPECT_NEAR(*aBrentResult.Root, *aGoldenResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aBrentResult.Value, *aGoldenResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aGoldenResult.Root, 3.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, Golden_CoshLike)
{
  CoshLikeFuncNew aNewFunc;

  MathOpt::ScalarResult aBrentResult  = MathOpt::Brent(aNewFunc, -5.0, 5.0);
  MathOpt::ScalarResult aGoldenResult = MathOpt::Golden(aNewFunc, -5.0, 5.0);

  ASSERT_TRUE(aBrentResult.IsDone());
  ASSERT_TRUE(aGoldenResult.IsDone());

  EXPECT_NEAR(*aBrentResult.Root, *aGoldenResult.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aBrentResult.Value, *aGoldenResult.Value, THE_TOLERANCE);
  EXPECT_NEAR(*aGoldenResult.Root, 0.0, THE_TOLERANCE);
}
