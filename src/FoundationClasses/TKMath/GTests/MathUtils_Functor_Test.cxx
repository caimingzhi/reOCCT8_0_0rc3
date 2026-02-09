

#include <gtest/gtest.h>

#include <MathUtils_FunctorScalar.hpp>
#include <MathUtils_FunctorVector.hpp>
#include <MathRoot_Brent.hpp>
#include <MathRoot_Newton.hpp>
#include <MathOpt_Powell.hpp>
#include <MathOpt_BFGS.hpp>

#include <cmath>

namespace
{
  constexpr double THE_TOLERANCE = 1e-10;
  constexpr double THE_PI        = 3.14159265358979323846;
} // namespace

TEST(MathUtils_Functor_Scalar, ScalarLambda_Value)
{
  auto aFunc = MathUtils::MakeScalar(
    [](double x, double& y)
    {
      y = x * x - 2.0;
      return true;
    });

  double aValue = 0.0;
  EXPECT_TRUE(aFunc.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 2.0, THE_TOLERANCE);

  EXPECT_TRUE(aFunc.Value(std::sqrt(2.0), aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, ScalarLambdaWithDerivative_Values)
{
  auto aFunc = MathUtils::MakeScalarWithDerivative(
    [](double x, double& y, double& dy)
    {
      y  = x * x - 2.0;
      dy = 2.0 * x;
      return true;
    });

  double aValue = 0.0;
  double aDeriv = 0.0;
  EXPECT_TRUE(aFunc.Values(3.0, aValue, aDeriv));
  EXPECT_NEAR(aValue, 7.0, THE_TOLERANCE);
  EXPECT_NEAR(aDeriv, 6.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Polynomial_Value)
{

  MathUtils::Polynomial aPoly({1.0, 2.0, 3.0});

  double aValue = 0.0;
  EXPECT_TRUE(aPoly.Value(0.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);

  EXPECT_TRUE(aPoly.Value(1.0, aValue));
  EXPECT_NEAR(aValue, 6.0, THE_TOLERANCE);

  EXPECT_TRUE(aPoly.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 17.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Polynomial_Values)
{

  MathUtils::Polynomial aPoly({-2.0, 0.0, 1.0});

  double aValue = 0.0;
  double aDeriv = 0.0;
  EXPECT_TRUE(aPoly.Values(3.0, aValue, aDeriv));
  EXPECT_NEAR(aValue, 7.0, THE_TOLERANCE);
  EXPECT_NEAR(aDeriv, 6.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Polynomial_WithRoots)
{

  MathUtils::Polynomial aPoly({-2.0, 0.0, 1.0});

  auto aResult = MathRoot::Brent(aPoly, 0.0, 2.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Root.has_value());
  EXPECT_NEAR(*aResult.Root, std::sqrt(2.0), 1e-9);
}

TEST(MathUtils_Functor_Scalar, Polynomial_WithNewton)
{

  MathUtils::Polynomial aPoly({-5.0, -2.0, 0.0, 1.0});

  auto aResult = MathRoot::Newton(aPoly, 2.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Root.has_value());

  EXPECT_NEAR(*aResult.Root, 2.0945514815, 1e-8);
}

TEST(MathUtils_Functor_Scalar, Rational_Value)
{

  MathUtils::Rational aRat({1.0, 1.0}, {1.0, 0.0, 1.0});

  double aValue = 0.0;
  EXPECT_TRUE(aRat.Value(0.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);

  EXPECT_TRUE(aRat.Value(1.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);

  EXPECT_TRUE(aRat.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 0.6, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Rational_DivisionByZero)
{

  MathUtils::Rational aRat({0.0, 1.0}, {-1.0, 1.0});

  double aValue = 0.0;
  EXPECT_FALSE(aRat.Value(1.0, aValue));
}

TEST(MathUtils_Functor_Scalar, Composite_Value)
{

  MathUtils::Polynomial aOuter({0.0, 0.0, 1.0});
  MathUtils::Polynomial aInner({1.0, 1.0});
  auto                  aComposite = MathUtils::MakeComposite(aOuter, aInner);

  double aValue = 0.0;
  EXPECT_TRUE(aComposite.Value(0.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);

  EXPECT_TRUE(aComposite.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 9.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Sum_Value)
{

  MathUtils::Polynomial aF({0.0, 0.0, 1.0});
  MathUtils::Polynomial aG({1.0, 2.0});
  auto                  aSum = MathUtils::MakeSum(aF, aG);

  double aValue = 0.0;
  EXPECT_TRUE(aSum.Value(1.0, aValue));
  EXPECT_NEAR(aValue, 4.0, THE_TOLERANCE);

  EXPECT_TRUE(aSum.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 9.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Difference_Value)
{

  MathUtils::Polynomial aF({0.0, 0.0, 1.0});
  MathUtils::Polynomial aG({0.0, 1.0});
  auto                  aDiff = MathUtils::MakeDifference(aF, aG);

  double aValue = 0.0;
  EXPECT_TRUE(aDiff.Value(3.0, aValue));
  EXPECT_NEAR(aValue, 6.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Product_Value)
{

  MathUtils::Polynomial aF({0.0, 1.0});
  MathUtils::Polynomial aG({1.0, 1.0});
  auto                  aProd = MathUtils::MakeProduct(aF, aG);

  double aValue = 0.0;
  EXPECT_TRUE(aProd.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 6.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Quotient_Value)
{

  MathUtils::Polynomial aF({0.0, 0.0, 1.0});
  MathUtils::Polynomial aG({0.0, 1.0});
  auto                  aQuot = MathUtils::MakeQuotient(aF, aG);

  double aValue = 0.0;
  EXPECT_TRUE(aQuot.Value(5.0, aValue));
  EXPECT_NEAR(aValue, 5.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Scaled_Value)
{

  MathUtils::Polynomial aF({0.0, 0.0, 1.0});
  auto                  aScaled = MathUtils::MakeScaled(aF, 3.0);

  double aValue = 0.0;
  EXPECT_TRUE(aScaled.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 12.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Shifted_Value)
{

  MathUtils::Polynomial aF({0.0, 0.0, 1.0});
  auto                  aShifted = MathUtils::MakeShifted(aF, 5.0);

  double aValue = 0.0;
  EXPECT_TRUE(aShifted.Value(2.0, aValue));
  EXPECT_NEAR(aValue, 9.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Negated_Value)
{

  MathUtils::Polynomial aF({0.0, 0.0, 1.0});
  auto                  aNegated = MathUtils::MakeNegated(aF);

  double aValue = 0.0;
  EXPECT_TRUE(aNegated.Value(3.0, aValue));
  EXPECT_NEAR(aValue, -9.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Constant_Value)
{
  MathUtils::Constant aConst(42.0);

  double aValue = 0.0;
  double aDeriv = 0.0;
  EXPECT_TRUE(aConst.Value(123.456, aValue));
  EXPECT_NEAR(aValue, 42.0, THE_TOLERANCE);

  EXPECT_TRUE(aConst.Values(789.0, aValue, aDeriv));
  EXPECT_NEAR(aValue, 42.0, THE_TOLERANCE);
  EXPECT_NEAR(aDeriv, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Linear_Value)
{

  MathUtils::Linear aLinear(2.0, 3.0);

  double aValue = 0.0;
  double aDeriv = 0.0;
  EXPECT_TRUE(aLinear.Value(5.0, aValue));
  EXPECT_NEAR(aValue, 13.0, THE_TOLERANCE);

  EXPECT_TRUE(aLinear.Values(5.0, aValue, aDeriv));
  EXPECT_NEAR(aValue, 13.0, THE_TOLERANCE);
  EXPECT_NEAR(aDeriv, 2.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Sine_Value)
{
  MathUtils::Sine aSine(1.0, 1.0, 0.0, 0.0);

  double aValue = 0.0;
  EXPECT_TRUE(aSine.Value(0.0, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);

  EXPECT_TRUE(aSine.Value(THE_PI / 2.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Sine_Values)
{
  MathUtils::Sine aSine(2.0, 1.0, 0.0, 0.0);

  double aValue = 0.0;
  double aDeriv = 0.0;
  EXPECT_TRUE(aSine.Values(0.0, aValue, aDeriv));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
  EXPECT_NEAR(aDeriv, 2.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Cosine_Value)
{
  MathUtils::Cosine aCosine(1.0, 1.0, 0.0, 0.0);

  double aValue = 0.0;
  EXPECT_TRUE(aCosine.Value(0.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);

  EXPECT_TRUE(aCosine.Value(THE_PI, aValue));
  EXPECT_NEAR(aValue, -1.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Exponential_Value)
{
  MathUtils::Exponential aExp(1.0, 1.0, 0.0);

  double aValue = 0.0;
  EXPECT_TRUE(aExp.Value(0.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);

  EXPECT_TRUE(aExp.Value(1.0, aValue));
  EXPECT_NEAR(aValue, std::exp(1.0), THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Power_Value)
{
  MathUtils::Power aPower(2.0, 1.0, 0.0);

  double aValue = 0.0;
  EXPECT_TRUE(aPower.Value(3.0, aValue));
  EXPECT_NEAR(aValue, 9.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Scalar, Power_NonInteger)
{
  MathUtils::Power aPower(0.5, 1.0, 0.0);

  double aValue = 0.0;
  EXPECT_TRUE(aPower.Value(4.0, aValue));
  EXPECT_NEAR(aValue, 2.0, THE_TOLERANCE);

  EXPECT_FALSE(aPower.Value(-4.0, aValue));
}

TEST(MathUtils_Functor_Scalar, Gaussian_Value)
{
  MathUtils::Gaussian aGauss(1.0, 0.0, 1.0);

  double aValue = 0.0;
  EXPECT_TRUE(aGauss.Value(0.0, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);

  EXPECT_TRUE(aGauss.Value(1.0, aValue));
  EXPECT_NEAR(aValue, std::exp(-0.5), THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, VectorLambda_Value)
{
  auto aFunc = MathUtils::MakeVector(
    [](const math_Vector& x, double& y)
    {
      y = x(1) * x(1) + x(2) * x(2);
      return true;
    });

  math_Vector aX(1, 2);
  aX(1) = 3.0;
  aX(2) = 4.0;

  double aValue = 0.0;
  EXPECT_TRUE(aFunc.Value(aX, aValue));
  EXPECT_NEAR(aValue, 25.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, VectorLambdaWithGradient_Values)
{
  auto aFunc = MathUtils::MakeVectorWithGradient(
    [](const math_Vector& x, double& y)
    {
      y = x(1) * x(1) + x(2) * x(2);
      return true;
    },
    [](const math_Vector& x, math_Vector& g)
    {
      g(1) = 2.0 * x(1);
      g(2) = 2.0 * x(2);
      return true;
    });

  math_Vector aX(1, 2);
  aX(1) = 3.0;
  aX(2) = 4.0;

  double      aValue = 0.0;
  math_Vector aGrad(1, 2);
  EXPECT_TRUE(aFunc.Values(aX, aValue, aGrad));
  EXPECT_NEAR(aValue, 25.0, THE_TOLERANCE);
  EXPECT_NEAR(aGrad(1), 6.0, THE_TOLERANCE);
  EXPECT_NEAR(aGrad(2), 8.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Rosenbrock_Value)
{
  MathUtils::Rosenbrock aRosen;

  math_Vector aX(1, 2);
  aX(1) = 1.0;
  aX(2) = 1.0;

  double aValue = 0.0;
  EXPECT_TRUE(aRosen.Value(aX, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Rosenbrock_AwayFromMinimum)
{
  MathUtils::Rosenbrock aRosen;

  math_Vector aX(1, 2);
  aX(1) = 0.0;
  aX(2) = 0.0;

  double aValue = 0.0;
  EXPECT_TRUE(aRosen.Value(aX, aValue));
  EXPECT_NEAR(aValue, 1.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Rosenbrock_Gradient)
{
  MathUtils::Rosenbrock aRosen;

  math_Vector aX(1, 2);
  aX(1) = 1.0;
  aX(2) = 1.0;

  math_Vector aGrad(1, 2);
  EXPECT_TRUE(aRosen.Gradient(aX, aGrad));
  EXPECT_NEAR(aGrad(1), 0.0, THE_TOLERANCE);
  EXPECT_NEAR(aGrad(2), 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Sphere_Value)
{
  MathUtils::Sphere aSphere;

  math_Vector aX(1, 3);
  aX(1) = 1.0;
  aX(2) = 2.0;
  aX(3) = 3.0;

  double aValue = 0.0;
  EXPECT_TRUE(aSphere.Value(aX, aValue));
  EXPECT_NEAR(aValue, 14.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Sphere_Gradient)
{
  MathUtils::Sphere aSphere;

  math_Vector aX(1, 3);
  aX(1) = 1.0;
  aX(2) = 2.0;
  aX(3) = 3.0;

  math_Vector aGrad(1, 3);
  EXPECT_TRUE(aSphere.Gradient(aX, aGrad));
  EXPECT_NEAR(aGrad(1), 2.0, THE_TOLERANCE);
  EXPECT_NEAR(aGrad(2), 4.0, THE_TOLERANCE);
  EXPECT_NEAR(aGrad(3), 6.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Booth_Value)
{
  MathUtils::Booth aBooth;

  math_Vector aX(1, 2);
  aX(1) = 1.0;
  aX(2) = 3.0;

  double aValue = 0.0;
  EXPECT_TRUE(aBooth.Value(aX, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Beale_Value)
{
  MathUtils::Beale aBeale;

  math_Vector aX(1, 2);
  aX(1) = 3.0;
  aX(2) = 0.5;

  double aValue = 0.0;
  EXPECT_TRUE(aBeale.Value(aX, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Himmelblau_Value)
{
  MathUtils::Himmelblau aHimmel;

  math_Vector aX(1, 2);
  aX(1) = 3.0;
  aX(2) = 2.0;

  double aValue = 0.0;
  EXPECT_TRUE(aHimmel.Value(aX, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Rastrigin_Value)
{
  MathUtils::Rastrigin aRast;

  math_Vector aX(1, 2);
  aX(1) = 0.0;
  aX(2) = 0.0;

  double aValue = 0.0;
  EXPECT_TRUE(aRast.Value(aX, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, Ackley_Value)
{
  MathUtils::Ackley aAckley;

  math_Vector aX(1, 2);
  aX(1) = 0.0;
  aX(2) = 0.0;

  double aValue = 0.0;
  EXPECT_TRUE(aAckley.Value(aX, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, QuadraticForm_Value)
{

  math_Matrix aA(1, 2, 1, 2, 0.0);
  aA(1, 1) = 1.0;
  aA(2, 2) = 1.0;

  math_Vector aB(1, 2, 0.0);
  double      aC = 0.0;

  MathUtils::QuadraticForm aQuad(aA, aB, aC);

  math_Vector aX(1, 2);
  aX(1) = 3.0;
  aX(2) = 4.0;

  double aValue = 0.0;
  EXPECT_TRUE(aQuad.Value(aX, aValue));
  EXPECT_NEAR(aValue, 25.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, QuadraticForm_Gradient)
{

  math_Matrix aA(1, 2, 1, 2, 0.0);
  aA(1, 1) = 1.0;
  aA(2, 2) = 1.0;

  math_Vector aB(1, 2, 0.0);
  double      aC = 0.0;

  MathUtils::QuadraticForm aQuad(aA, aB, aC);

  math_Vector aX(1, 2);
  aX(1) = 3.0;
  aX(2) = 4.0;

  math_Vector aGrad(1, 2);
  EXPECT_TRUE(aQuad.Gradient(aX, aGrad));
  EXPECT_NEAR(aGrad(1), 6.0, THE_TOLERANCE);
  EXPECT_NEAR(aGrad(2), 8.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, LinearResidual_Value)
{

  math_Matrix aA(1, 2, 1, 2, 0.0);
  aA(1, 1) = 1.0;
  aA(2, 2) = 1.0;

  math_Vector aB(1, 2);
  aB(1) = 3.0;
  aB(2) = 4.0;

  MathUtils::LinearResidual aRes(aA, aB);

  math_Vector aX(1, 2);
  aX(1) = 3.0;
  aX(2) = 4.0;

  double aValue = 0.0;
  EXPECT_TRUE(aRes.Value(aX, aValue));
  EXPECT_NEAR(aValue, 0.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Vector, LinearResidual_NonZero)
{
  math_Matrix aA(1, 2, 1, 2, 0.0);
  aA(1, 1) = 1.0;
  aA(2, 2) = 1.0;

  math_Vector aB(1, 2);
  aB(1) = 3.0;
  aB(2) = 4.0;

  MathUtils::LinearResidual aRes(aA, aB);

  math_Vector aX(1, 2);
  aX(1) = 0.0;
  aX(2) = 0.0;

  double aValue = 0.0;
  EXPECT_TRUE(aRes.Value(aX, aValue));
  EXPECT_NEAR(aValue, 25.0, THE_TOLERANCE);
}

TEST(MathUtils_Functor_Integration, Polynomial_WithBrent)
{

  MathUtils::Polynomial aPoly({-2.0, -1.0, 0.0, 1.0});

  auto aResult = MathRoot::Brent(aPoly, 1.0, 2.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Root.has_value());

  double aValue = 0.0;
  aPoly.Value(*aResult.Root, aValue);
  EXPECT_NEAR(aValue, 0.0, 1e-10);
}

TEST(MathUtils_Functor_Integration, Sine_RootFinding)
{

  MathUtils::Sine aSine;

  auto aResult = MathRoot::Brent(aSine, 2.0, 4.0);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Root.has_value());
  EXPECT_NEAR(*aResult.Root, THE_PI, 1e-10);
}

TEST(MathUtils_Functor_Integration, Sphere_WithPowell)
{

  MathUtils::Sphere aSphere;

  math_Vector aStart(1, 2);
  aStart(1) = 5.0;
  aStart(2) = 5.0;

  auto aResult = MathOpt::Powell(aSphere, aStart);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR((*aResult.Solution)(1), 0.0, 1e-5);
  EXPECT_NEAR((*aResult.Solution)(2), 0.0, 1e-5);
}

TEST(MathUtils_Functor_Integration, Booth_WithBFGS)
{

  MathUtils::Booth aBooth;

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  auto aResult = MathOpt::BFGS(aBooth, aStart);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1e-5);
  EXPECT_NEAR((*aResult.Solution)(2), 3.0, 1e-5);
}

TEST(MathUtils_Functor_Integration, Rosenbrock_WithBFGS)
{

  MathUtils::Rosenbrock aRosen;

  math_Vector aStart(1, 2);
  aStart(1) = -1.0;
  aStart(2) = 1.0;

  MathUtils::NDimConfig aConfig;
  aConfig.MaxIterations = 500;
  aConfig.FTolerance    = 1e-10;
  aConfig.XTolerance    = 1e-10;

  auto aResult = MathOpt::BFGS(aRosen, aStart, aConfig);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1e-4);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, 1e-4);
}

TEST(MathUtils_Functor_Integration, Quadratic_WithNewton)
{

  math_Matrix aA(1, 2, 1, 2, 0.0);
  aA(1, 1) = 2.0;
  aA(2, 2) = 4.0;

  math_Vector aB(1, 2);
  aB(1) = -4.0;
  aB(2) = -8.0;

  MathUtils::QuadraticForm aQuad(aA, aB, 10.0);

  math_Vector aStart(1, 2);
  aStart(1) = 0.0;
  aStart(2) = 0.0;

  auto aResult = MathOpt::BFGS(aQuad, aStart);
  EXPECT_TRUE(aResult.IsDone());
  EXPECT_TRUE(aResult.Solution.has_value());
  EXPECT_NEAR((*aResult.Solution)(1), 1.0, 1e-5);
  EXPECT_NEAR((*aResult.Solution)(2), 1.0, 1e-5);
}
