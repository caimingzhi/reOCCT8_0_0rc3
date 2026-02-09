

#include <math_GaussSingleIntegration.hpp>
#include <math_KronrodSingleIntegration.hpp>
#include <math_Function.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <StdFail_NotDone.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  class ConstantFunction : public math_Function
  {
  private:
    double myValue;

  public:
    ConstantFunction(double theValue)
        : myValue(theValue)
    {
    }

    bool Value(const double, double& theF) override
    {
      theF = myValue;
      return true;
    }
  };

  class LinearFunction : public math_Function
  {
  private:
    double myA, myB;

  public:
    LinearFunction(double theA, double theB)
        : myA(theA),
          myB(theB)
    {
    }

    bool Value(const double theX, double& theF) override
    {
      theF = myA * theX + myB;
      return true;
    }
  };

  class QuadraticFunction : public math_Function
  {
  private:
    double myA, myB, myC;

  public:
    QuadraticFunction(double theA, double theB, double theC)
        : myA(theA),
          myB(theB),
          myC(theC)
    {
    }

    bool Value(const double theX, double& theF) override
    {
      theF = myA * theX * theX + myB * theX + myC;
      return true;
    }
  };

  class PowerFunction : public math_Function
  {
  private:
    int myPower;

  public:
    PowerFunction(int thePower)
        : myPower(thePower)
    {
    }

    bool Value(const double theX, double& theF) override
    {
      theF = pow(theX, myPower);
      return true;
    }
  };

  class SineFunction : public math_Function
  {
  public:
    bool Value(const double theX, double& theF) override
    {
      theF = sin(theX);
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

  TEST(MathIntegrationTest, GaussConstantFunction)
  {
    ConstantFunction aFunc(5.0);
    double           aLower  = 0.0;
    double           anUpper = 2.0;
    int              anOrder = 4;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone()) << "Gauss integration should succeed for constant function";

    double anExpected = 5.0 * (anUpper - aLower);
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-12)
      << "Constant function integration should be exact";
  }

  TEST(MathIntegrationTest, GaussLinearFunction)
  {
    LinearFunction aFunc(2.0, 3.0);
    double         aLower  = 1.0;
    double         anUpper = 4.0;
    int            anOrder = 2;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone()) << "Gauss integration should succeed for linear function";

    double anExpected = 24.0;
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-12)
      << "Linear function integration should be exact with order 2";
  }

  TEST(MathIntegrationTest, GaussQuadraticFunction)
  {
    QuadraticFunction aFunc(1.0, -2.0, 1.0);
    double            aLower  = 0.0;
    double            anUpper = 2.0;
    int               anOrder = 3;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone()) << "Gauss integration should succeed for quadratic function";

    double anExpected = 2.0 / 3.0;

    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-12)
      << "Quadratic function integration should be exact with order 3";
  }

  TEST(MathIntegrationTest, GaussSineFunction)
  {
    SineFunction aFunc;
    double       aLower  = 0.0;
    double       anUpper = M_PI;
    int          anOrder = 10;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone()) << "Gauss integration should succeed for sine function";

    double anExpected = 2.0;
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-10)
      << "Sine function integration should be accurate";
  }

  TEST(MathIntegrationTest, GaussExponentialFunction)
  {
    ExponentialFunction aFunc;
    double              aLower  = 0.0;
    double              anUpper = 1.0;
    int                 anOrder = 15;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone())
      << "Gauss integration should succeed for exponential function";

    double anExpected = exp(1.0) - 1.0;
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-8)
      << "Exponential function integration should be accurate";
  }

  TEST(MathIntegrationTest, GaussDifferentOrders)
  {
    QuadraticFunction aFunc(1.0, 0.0, 0.0);
    double            aLower  = 0.0;
    double            anUpper = 1.0;

    double anExpected = 1.0 / 3.0;

    std::vector<int> anOrders = {2, 3, 5, 10, 20};

    for (int anOrder : anOrders)
    {
      math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

      EXPECT_TRUE(anIntegrator.IsDone()) << "Integration should succeed for order " << anOrder;

      if (anOrder >= 3)
      {

        EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-12)
          << "High order integration should be exact for order " << anOrder;
      }
      else
      {

        EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-6)
          << "Low order integration should be reasonably accurate for order " << anOrder;
      }
    }
  }

  TEST(MathIntegrationTest, GaussWithTolerance)
  {
    QuadraticFunction aFunc(1.0, 0.0, 0.0);
    double            aLower     = 0.0;
    double            anUpper    = 1.0;
    int               anOrder    = 5;
    double            aTolerance = 1.0e-10;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder, aTolerance);

    EXPECT_TRUE(anIntegrator.IsDone()) << "Integration with tolerance should succeed";

    double anExpected = 1.0 / 3.0;
    EXPECT_NEAR(anIntegrator.Value(), anExpected, aTolerance * 10)
      << "Integration with tolerance should meet accuracy requirements";
  }

  TEST(MathIntegrationTest, GaussNegativeInterval)
  {
    LinearFunction aFunc(1.0, 0.0);
    double         aLower  = -2.0;
    double         anUpper = 2.0;
    int            anOrder = 3;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone()) << "Integration over symmetric interval should succeed";

    EXPECT_NEAR(anIntegrator.Value(), 0.0, 1.0e-12)
      << "Symmetric odd function integral should be zero";
  }

  TEST(MathIntegrationTest, KronrodConstantFunction)
  {
    ConstantFunction aFunc(3.0);
    double           aLower  = 1.0;
    double           anUpper = 5.0;
    int              anOrder = 15;

    math_KronrodSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone())
      << "Kronrod integration should succeed for constant function";

    double anExpected = 3.0 * (anUpper - aLower);
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-12)
      << "Constant function integration should be exact";
  }

  TEST(MathIntegrationTest, KronrodQuadraticFunction)
  {
    QuadraticFunction aFunc(2.0, -1.0, 3.0);
    double            aLower  = 0.0;
    double            anUpper = 1.0;
    int               anOrder = 15;

    math_KronrodSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone())
      << "Kronrod integration should succeed for quadratic function";

    double anExpected = 19.0 / 6.0;
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-10)
      << "Quadratic function integration should be very accurate";
  }

  TEST(MathIntegrationTest, KronrodSineFunction)
  {
    SineFunction aFunc;
    double       aLower  = 0.0;
    double       anUpper = M_PI / 2.0;
    int          anOrder = 21;

    math_KronrodSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone()) << "Kronrod integration should succeed for sine function";

    double anExpected = 1.0;
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-12)
      << "Sine function integration should be very accurate";
  }

  TEST(MathIntegrationTest, GaussVsKronrodComparison)
  {
    PowerFunction aFunc(4);
    double        aLower  = 0.0;
    double        anUpper = 2.0;

    double anExpected = 32.0 / 5.0;

    math_GaussSingleIntegration aGaussIntegrator(aFunc, aLower, anUpper, 10);
    EXPECT_TRUE(aGaussIntegrator.IsDone()) << "Gauss integration should succeed";

    math_KronrodSingleIntegration aKronrodIntegrator(aFunc, aLower, anUpper, 21);
    EXPECT_TRUE(aKronrodIntegrator.IsDone()) << "Kronrod integration should succeed";

    EXPECT_NEAR(aGaussIntegrator.Value(), anExpected, 1.0e-10)
      << "Gauss integration should be accurate for x^4";
    EXPECT_NEAR(aKronrodIntegrator.Value(), anExpected, 1.0e-10)
      << "Kronrod integration should be accurate for x^4";

    EXPECT_NEAR(aGaussIntegrator.Value(), aKronrodIntegrator.Value(), 1.0e-8)
      << "Gauss and Kronrod results should be similar";
  }

  TEST(MathIntegrationTest, DefaultConstructorAndPerform)
  {

    math_GaussSingleIntegration anIntegrator1;

    LinearFunction aFunc(1.0, 2.0);
    double         aLower  = 0.0;
    double         anUpper = 3.0;
    int            anOrder = 5;

    math_GaussSingleIntegration anIntegrator2(aFunc, aLower, anUpper, anOrder);
    EXPECT_TRUE(anIntegrator2.IsDone()) << "Integration after explicit construction should succeed";

    EXPECT_NEAR(anIntegrator2.Value(), 10.5, 1.0e-12) << "Linear function integral should be exact";
  }

  TEST(MathIntegrationTest, ZeroLengthInterval)
  {
    ConstantFunction aFunc(1.0);
    double           aLower  = 5.0;
    double           anUpper = 5.0;
    int              anOrder = 5;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    if (anIntegrator.IsDone())
    {
      EXPECT_NEAR(anIntegrator.Value(), 0.0, Precision::Confusion())
        << "Zero-length interval should give zero integral";
    }
  }

  TEST(MathIntegrationTest, ReverseInterval)
  {
    LinearFunction aFunc(1.0, 0.0);
    double         aLower  = 2.0;
    double         anUpper = 0.0;
    int            anOrder = 5;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    if (anIntegrator.IsDone())
    {

      EXPECT_NEAR(anIntegrator.Value(), -2.0, 1.0e-12)
        << "Reverse interval should give negative result";
    }
  }

  TEST(MathIntegrationTest, HighOrderIntegration)
  {
    PowerFunction aFunc(10);
    double        aLower  = 0.0;
    double        anUpper = 1.0;
    int           anOrder = 30;

    math_GaussSingleIntegration anIntegrator(aFunc, aLower, anUpper, anOrder);

    EXPECT_TRUE(anIntegrator.IsDone()) << "High order integration should succeed";

    double anExpected = 1.0 / 11.0;
    EXPECT_NEAR(anIntegrator.Value(), anExpected, 1.0e-12)
      << "High order integration of polynomial should be exact";
  }

} // namespace
