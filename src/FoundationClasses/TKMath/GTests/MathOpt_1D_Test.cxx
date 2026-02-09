

#include <gtest/gtest.h>

#include <MathOpt_Brent.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1.0e-7;
  constexpr double THE_PI        = 3.14159265358979323846;

  class ParabolaFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = (theX - 3.0) * (theX - 3.0) + 1.0;
      return true;
    }
  };

  class ParabolaFunc2
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX - 4.0 * theX + 3.0;
      return true;
    }
  };

  class CosFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::cos(theX);
      return true;
    }
  };

  class QuarticFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      const double aX2 = theX * theX;
      theF             = aX2 * aX2 - 2.0 * aX2;
      return true;
    }
  };

  class CoshLikeFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::exp(theX) + std::exp(-theX);
      return true;
    }
  };

  class Rosenbrock1DFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      const double a = 1.0 - theX;
      const double b = theX * theX - theX;
      theF           = a * a + 100.0 * b * b;
      return true;
    }
  };

  class AbsShiftedFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::abs(theX - 2.0) + 1.0;
      return true;
    }
  };

  class SinWithHarmonicFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = std::sin(theX) + 0.5 * std::sin(3.0 * theX);
      return true;
    }
  };
} // namespace

TEST(MathOpt_1D_BrentTest, SimpleParabola)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 10.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, ParabolaWithNegativeMinimum)
{
  ParabolaFunc2         aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 5.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 2.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, CosineMinimum)
{
  CosFunc               aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 2.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, THE_PI, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, QuarticMinimumRight)
{
  QuarticFunc aFunc;

  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 1.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, QuarticMinimumLeft)
{
  QuarticFunc aFunc;

  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, -2.0, 0.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, -1.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, CoshLikeMinimum)
{
  CoshLikeFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, -5.0, 5.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 0.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, NarrowInterval)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 2.9, 3.1);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 3.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, WideInterval)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, -100.0, 100.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 3.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentTest, CustomTolerance)
{
  ParabolaFunc    aFunc;
  MathOpt::Config aConfig;
  aConfig.XTolerance    = 1.0e-10;
  aConfig.MaxIterations = 200;

  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 10.0, aConfig);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 3.0, 1.0e-9);
}

TEST(MathOpt_1D_BrentTest, NonSmoothFunction)
{
  AbsShiftedFunc        aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 5.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 2.0, 1.0e-6);
  EXPECT_NEAR(*aResult.Value, 1.0, 1.0e-6);
}

TEST(MathOpt_1D_GoldenTest, SimpleParabola)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Golden(aFunc, 0.0, 10.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_GoldenTest, CosineMinimum)
{
  CosFunc               aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Golden(aFunc, 2.0, 4.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, THE_PI, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_GoldenTest, QuarticMinimum)
{
  QuarticFunc           aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Golden(aFunc, 0.0, 2.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 1.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, -1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_GoldenTest, CoshLikeMinimum)
{
  CoshLikeFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Golden(aFunc, -5.0, 5.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 0.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 2.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentWithBracketTest, SimpleParabola)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::BrentWithBracket(aFunc, 0.0, 1.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 3.0, THE_TOLERANCE);
  EXPECT_NEAR(*aResult.Value, 1.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentWithBracketTest, StartNearMinimum)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::BrentWithBracket(aFunc, 2.5, 0.5);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 3.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_BrentWithBracketTest, CoshLike)
{
  CoshLikeFunc aFunc;

  MathOpt::ScalarResult aResult = MathOpt::BrentWithBracket(aFunc, 0.1, 0.2);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, BrentVsGoldenSameResult)
{
  ParabolaFunc aFunc;

  MathOpt::ScalarResult aBrent  = MathOpt::Brent(aFunc, 0.0, 10.0);
  MathOpt::ScalarResult aGolden = MathOpt::Golden(aFunc, 0.0, 10.0);

  ASSERT_TRUE(aBrent.IsDone());
  ASSERT_TRUE(aGolden.IsDone());

  EXPECT_NEAR(*aBrent.Root, *aGolden.Root, THE_TOLERANCE);
  EXPECT_NEAR(*aBrent.Value, *aGolden.Value, THE_TOLERANCE);
}

TEST(MathOpt_1D_ComparisonTest, BrentFasterThanGolden)
{
  ParabolaFunc    aFunc;
  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;

  MathOpt::ScalarResult aBrent  = MathOpt::Brent(aFunc, 0.0, 10.0, aConfig);
  MathOpt::ScalarResult aGolden = MathOpt::Golden(aFunc, 0.0, 10.0, aConfig);

  ASSERT_TRUE(aBrent.IsDone());
  ASSERT_TRUE(aGolden.IsDone());

  EXPECT_LE(aBrent.NbIterations, aGolden.NbIterations);
}

TEST(MathOpt_1D_RobustnessTest, MinimumAtLeftBoundary)
{

  class SquareFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = theX * theX;
      return true;
    }
  };

  SquareFunc            aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 10.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 0.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_RobustnessTest, MinimumAtRightBoundary)
{

  class ShiftedSquareFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      theF = (10.0 - theX) * (10.0 - theX);
      return true;
    }
  };

  ShiftedSquareFunc     aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 10.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 10.0, THE_TOLERANCE);
}

TEST(MathOpt_1D_RobustnessTest, VeryFlatFunction)
{

  class FlatQuarticFunc
  {
  public:
    bool Value(double theX, double& theF) const
    {
      const double aDiff = theX - 5.0;
      theF               = aDiff * aDiff * aDiff * aDiff;
      return true;
    }
  };

  FlatQuarticFunc       aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 10.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_NEAR(*aResult.Root, 5.0, 1.0e-5);
}

TEST(MathOpt_1D_BoolConversionTest, SuccessfulResultIsTrue)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 10.0);
  EXPECT_TRUE(static_cast<bool>(aResult));
}

TEST(MathOpt_1D_IterationTest, BrentConvergesQuickly)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Brent(aFunc, 0.0, 10.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_LT(aResult.NbIterations, 50);
}

TEST(MathOpt_1D_IterationTest, GoldenConverges)
{
  ParabolaFunc          aFunc;
  MathOpt::ScalarResult aResult = MathOpt::Golden(aFunc, 0.0, 10.0);
  ASSERT_TRUE(aResult.IsDone());
  EXPECT_LT(aResult.NbIterations, 100);
}
