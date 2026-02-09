

#include <gtest/gtest.h>

#include <MathOpt_Powell.hpp>
#include <MathOpt_BFGS.hpp>

#include <cmath>

class RosenbrockFunction
{
public:
  bool Value(const math_Vector& theX, double& theF)
  {
    const double aX = theX(1);
    const double aY = theX(2);
    theF            = (1.0 - aX) * (1.0 - aX) + 100.0 * (aY - aX * aX) * (aY - aX * aX);
    return true;
  }

  bool Gradient(const math_Vector& theX, math_Vector& theGrad)
  {
    const double aX = theX(1);
    const double aY = theX(2);
    theGrad(1)      = -2.0 * (1.0 - aX) - 400.0 * aX * (aY - aX * aX);
    theGrad(2)      = 200.0 * (aY - aX * aX);
    return true;
  }
};

class SimpleQuadratic
{
public:
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

class SphereFunction
{
public:
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

class BoothFunction
{
public:
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

class BealeFunction
{
public:
  bool Value(const math_Vector& theX, double& theF)
  {
    const double aX  = theX(1);
    const double aY  = theX(2);
    const double aT1 = 1.5 - aX + aX * aY;
    const double aT2 = 2.25 - aX + aX * aY * aY;
    const double aT3 = 2.625 - aX + aX * aY * aY * aY;
    theF             = aT1 * aT1 + aT2 * aT2 + aT3 * aT3;
    return true;
  }

  bool Gradient(const math_Vector& theX, math_Vector& theGrad)
  {
    const double aX  = theX(1);
    const double aY  = theX(2);
    const double aY2 = aY * aY;
    const double aY3 = aY2 * aY;
    const double aT1 = 1.5 - aX + aX * aY;
    const double aT2 = 2.25 - aX + aX * aY2;
    const double aT3 = 2.625 - aX + aX * aY3;
    theGrad(1) = 2.0 * aT1 * (-1.0 + aY) + 2.0 * aT2 * (-1.0 + aY2) + 2.0 * aT3 * (-1.0 + aY3);
    theGrad(2) = 2.0 * aT1 * aX + 2.0 * aT2 * (2.0 * aX * aY) + 2.0 * aT3 * (3.0 * aX * aY2);
    return true;
  }
};

TEST(MathOpt_PowellTest, SimpleQuadratic)
{
  SimpleQuadratic aFunc;
  math_Vector     aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 5.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aResult = MathOpt::Powell(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-6);
  EXPECT_NEAR((*aResult.Solution)(1), 0.0, 1.0e-4);
  EXPECT_NEAR((*aResult.Solution)(2), 0.0, 1.0e-4);
}

TEST(MathOpt_PowellTest, BoothFunction)
{
  BoothFunction aFunc;
  math_Vector   aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aResult = MathOpt::Powell(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-6);
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-4);
  EXPECT_NEAR((*aResult.Solution)(2), 3.0, 1.0e-4);
}

TEST(MathOpt_PowellTest, SphereFunction3D)
{
  SphereFunction aFunc;
  math_Vector    aStart(1, 3);
  aStart(1) = 3.0;
  aStart(2) = -2.0;
  aStart(3) = 4.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aResult = MathOpt::Powell(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-6);
  for (int i = 1; i <= 3; ++i)
  {
    EXPECT_NEAR((*aResult.Solution)(i), 0.0, 1.0e-4);
  }
}

TEST(MathOpt_BFGSTest, SimpleQuadratic)
{
  SimpleQuadratic aFunc;
  math_Vector     aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 5.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-10;
  aConfig.FTolerance    = 1.0e-12;

  auto aResult = MathOpt::BFGS(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
  EXPECT_NEAR((*aResult.Solution)(1), 0.0, 1.0e-6);
  EXPECT_NEAR((*aResult.Solution)(2), 0.0, 1.0e-6);
  EXPECT_LT(aResult.NbIterations, 20);
}

TEST(MathOpt_BFGSTest, BoothFunction)
{
  BoothFunction aFunc;
  math_Vector   aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-10;
  aConfig.FTolerance    = 1.0e-12;

  auto aResult = MathOpt::BFGS(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-6);
  EXPECT_NEAR((*aResult.Solution)(2), 3.0, 1.0e-6);
}

TEST(MathOpt_BFGSTest, RosenbrockFunction)
{
  RosenbrockFunction aFunc;
  math_Vector        aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 500;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aResult = MathOpt::BFGS(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-4);
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-3);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, 1.0e-3);
}

TEST(MathOpt_BFGSTest, BealeFunction)
{
  BealeFunction aFunc;
  math_Vector   aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 200;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aResult = MathOpt::BFGS(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-4);
  EXPECT_NEAR((*aResult.Solution)(1), 3.0, 1.0e-3);
  EXPECT_NEAR((*aResult.Solution)(2), 0.5, 1.0e-3);
}

TEST(MathOpt_BFGSTest, SphereFunction5D)
{
  SphereFunction aFunc;
  math_Vector    aStart(1, 5);
  for (int i = 1; i <= 5; ++i)
  {
    aStart(i) = static_cast<double>(i);
  }

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-10;
  aConfig.FTolerance    = 1.0e-12;

  auto aResult = MathOpt::BFGS(aFunc, aStart, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
  for (int i = 1; i <= 5; ++i)
  {
    EXPECT_NEAR((*aResult.Solution)(i), 0.0, 1.0e-6);
  }
  EXPECT_LT(aResult.NbIterations, 20);
}

TEST(MathOpt_BFGSNumericalTest, SimpleQuadratic)
{

  class QuadraticNoGrad
  {
  public:
    bool Value(const math_Vector& theX, double& theF)
    {
      theF = 0.0;
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theF += theX(i) * theX(i);
      }
      return true;
    }
  };

  QuadraticNoGrad aFunc;
  math_Vector     aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 5.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aResult = MathOpt::BFGSNumerical(aFunc, aStart, 1.0e-7, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-6);
  EXPECT_NEAR((*aResult.Solution)(1), 0.0, 1.0e-4);
  EXPECT_NEAR((*aResult.Solution)(2), 0.0, 1.0e-4);
}

TEST(MathOpt_LBFGSTest, SimpleQuadratic)
{
  SimpleQuadratic aFunc;
  math_Vector     aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 5.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-10;
  aConfig.FTolerance    = 1.0e-12;

  auto aResult = MathOpt::LBFGS(aFunc, aStart, 10, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
  EXPECT_NEAR((*aResult.Solution)(1), 0.0, 1.0e-6);
  EXPECT_NEAR((*aResult.Solution)(2), 0.0, 1.0e-6);
}

TEST(MathOpt_LBFGSTest, BoothFunction)
{
  BoothFunction aFunc;
  math_Vector   aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-10;
  aConfig.FTolerance    = 1.0e-12;

  auto aResult = MathOpt::LBFGS(aFunc, aStart, 10, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1.0e-6);
  EXPECT_NEAR((*aResult.Solution)(2), 3.0, 1.0e-6);
}

TEST(MathOpt_LBFGSTest, SphereFunction10D)
{
  SphereFunction aFunc;
  math_Vector    aStart(1, 10);
  for (int i = 1; i <= 10; ++i)
  {
    aStart(i) = static_cast<double>(i);
  }

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 100;
  aConfig.XTolerance    = 1.0e-10;
  aConfig.FTolerance    = 1.0e-12;

  auto aResult = MathOpt::LBFGS(aFunc, aStart, 5, aConfig);

  EXPECT_TRUE(aResult.IsDone());
  ASSERT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR(*aResult.Value, 0.0, 1.0e-8);
  for (int i = 1; i <= 10; ++i)
  {
    EXPECT_NEAR((*aResult.Solution)(i), 0.0, 1.0e-6);
  }
}

TEST(MathOpt_ComparisonTest, BFGSFasterThanPowellOnQuadratic)
{
  SimpleQuadratic aFunc;
  math_Vector     aStart(1, 2);
  aStart(1) = 10.0;
  aStart(2) = 10.0;

  MathOpt::Config aConfig;
  aConfig.MaxIterations = 500;
  aConfig.XTolerance    = 1.0e-8;
  aConfig.FTolerance    = 1.0e-10;

  auto aPowellResult = MathOpt::Powell(aFunc, aStart, aConfig);
  auto aBFGSResult   = MathOpt::BFGS(aFunc, aStart, aConfig);

  EXPECT_TRUE(aPowellResult.IsDone());
  EXPECT_TRUE(aBFGSResult.IsDone());

  EXPECT_NEAR(*aPowellResult.Value, *aBFGSResult.Value, 1.0e-4);

  EXPECT_LT(aBFGSResult.NbIterations, aPowellResult.NbIterations);
}
