#pragma once

#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <cmath>
#include <utility>

namespace MathUtils
{

  template <typename Lambda>
  class VectorLambda
  {
  public:
    explicit VectorLambda(Lambda theLambda)
        : myLambda(std::move(theLambda))
    {
    }

    bool Value(const math_Vector& theX, double& theY) const { return myLambda(theX, theY); }

  private:
    Lambda myLambda;
  };

  template <typename ValueLambda, typename GradLambda>
  class VectorLambdaWithGradient
  {
  public:
    VectorLambdaWithGradient(ValueLambda theValueLambda, GradLambda theGradLambda)
        : myValueLambda(std::move(theValueLambda)),
          myGradLambda(std::move(theGradLambda))
    {
    }

    bool Value(const math_Vector& theX, double& theY) const { return myValueLambda(theX, theY); }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {
      return myGradLambda(theX, theG);
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return myValueLambda(theX, theY) && myGradLambda(theX, theG);
    }

  private:
    ValueLambda myValueLambda;
    GradLambda  myGradLambda;
  };

  template <typename Lambda>
  VectorLambda<Lambda> MakeVector(Lambda theLambda)
  {
    return VectorLambda<Lambda>(std::move(theLambda));
  }

  template <typename ValueLambda, typename GradLambda>
  VectorLambdaWithGradient<ValueLambda, GradLambda> MakeVectorWithGradient(
    ValueLambda theValueLambda,
    GradLambda  theGradLambda)
  {
    return VectorLambdaWithGradient<ValueLambda, GradLambda>(std::move(theValueLambda),
                                                             std::move(theGradLambda));
  }

  class QuadraticForm
  {
  public:
    QuadraticForm(const math_Matrix& theA, const math_Vector& theB, double theC)
        : myA(theA),
          myB(theB),
          myC(theC)
    {
    }

    bool Value(const math_Vector& theX, double& theY) const
    {
      theY = myC;

      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        for (int j = theX.Lower(); j <= theX.Upper(); ++j)
        {
          theY += theX(i) * myA(i, j) * theX(j);
        }
      }

      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theY += myB(i) * theX(i);
      }
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {

      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theG(i) = myB(i);
        for (int j = theX.Lower(); j <= theX.Upper(); ++j)
        {
          theG(i) += (myA(i, j) + myA(j, i)) * theX(j);
        }
      }
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }

  private:
    math_Matrix myA;
    math_Vector myB;
    double      myC;
  };

  class Rosenbrock
  {
  public:
    Rosenbrock(double theA = 1.0, double theB = 100.0)
        : myA(theA),
          myB(theB)
    {
    }

    bool Value(const math_Vector& theX, double& theY) const
    {
      const double x  = theX(theX.Lower());
      const double y  = theX(theX.Lower() + 1);
      const double t1 = myA - x;
      const double t2 = y - x * x;
      theY            = t1 * t1 + myB * t2 * t2;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {
      const double x         = theX(theX.Lower());
      const double y         = theX(theX.Lower() + 1);
      const double t2        = y - x * x;
      theG(theG.Lower())     = -2.0 * (myA - x) - 4.0 * myB * x * t2;
      theG(theG.Lower() + 1) = 2.0 * myB * t2;
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }

  private:
    double myA;
    double myB;
  };

  class Sphere
  {
  public:
    bool Value(const math_Vector& theX, double& theY) const
    {
      theY = 0.0;
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theY += theX(i) * theX(i);
      }
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theG(i) = 2.0 * theX(i);
      }
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }
  };

  class Booth
  {
  public:
    bool Value(const math_Vector& theX, double& theY) const
    {
      const double x  = theX(theX.Lower());
      const double y  = theX(theX.Lower() + 1);
      const double t1 = x + 2.0 * y - 7.0;
      const double t2 = 2.0 * x + y - 5.0;
      theY            = t1 * t1 + t2 * t2;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {
      const double x         = theX(theX.Lower());
      const double y         = theX(theX.Lower() + 1);
      const double t1        = x + 2.0 * y - 7.0;
      const double t2        = 2.0 * x + y - 5.0;
      theG(theG.Lower())     = 2.0 * t1 + 4.0 * t2;
      theG(theG.Lower() + 1) = 4.0 * t1 + 2.0 * t2;
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }
  };

  class Beale
  {
  public:
    bool Value(const math_Vector& theX, double& theY) const
    {
      const double x  = theX(theX.Lower());
      const double y  = theX(theX.Lower() + 1);
      const double t1 = 1.5 - x + x * y;
      const double t2 = 2.25 - x + x * y * y;
      const double t3 = 2.625 - x + x * y * y * y;
      theY            = t1 * t1 + t2 * t2 + t3 * t3;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {
      const double x         = theX(theX.Lower());
      const double y         = theX(theX.Lower() + 1);
      const double y2        = y * y;
      const double y3        = y2 * y;
      const double t1        = 1.5 - x + x * y;
      const double t2        = 2.25 - x + x * y2;
      const double t3        = 2.625 - x + x * y3;
      theG(theG.Lower())     = 2.0 * ((y - 1.0) * t1 + (y2 - 1.0) * t2 + (y3 - 1.0) * t3);
      theG(theG.Lower() + 1) = 2.0 * x * (t1 + 2.0 * y * t2 + 3.0 * y2 * t3);
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }
  };

  class Himmelblau
  {
  public:
    bool Value(const math_Vector& theX, double& theY) const
    {
      const double x  = theX(theX.Lower());
      const double y  = theX(theX.Lower() + 1);
      const double t1 = x * x + y - 11.0;
      const double t2 = x + y * y - 7.0;
      theY            = t1 * t1 + t2 * t2;
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {
      const double x         = theX(theX.Lower());
      const double y         = theX(theX.Lower() + 1);
      const double t1        = x * x + y - 11.0;
      const double t2        = x + y * y - 7.0;
      theG(theG.Lower())     = 4.0 * x * t1 + 2.0 * t2;
      theG(theG.Lower() + 1) = 2.0 * t1 + 4.0 * y * t2;
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }
  };

  class Rastrigin
  {
  public:
    explicit Rastrigin(double theA = 10.0)
        : myA(theA)
    {
    }

    bool Value(const math_Vector& theX, double& theY) const
    {
      constexpr double aTwoPi = 2.0 * 3.14159265358979323846;
      const int        n      = theX.Upper() - theX.Lower() + 1;
      theY                    = myA * static_cast<double>(n);
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theY += theX(i) * theX(i) - myA * std::cos(aTwoPi * theX(i));
      }
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {
      constexpr double aTwoPi = 2.0 * 3.14159265358979323846;
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        theG(i) = 2.0 * theX(i) + myA * aTwoPi * std::sin(aTwoPi * theX(i));
      }
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }

  private:
    double myA;
  };

  class Ackley
  {
  public:
    Ackley(double theA = 20.0, double theB = 0.2, double theC = 2.0 * 3.14159265358979323846)
        : myA(theA),
          myB(theB),
          myC(theC)
    {
    }

    bool Value(const math_Vector& theX, double& theY) const
    {
      constexpr double aE      = 2.718281828459045;
      const int        n       = theX.Upper() - theX.Lower() + 1;
      double           aSumSq  = 0.0;
      double           aSumCos = 0.0;
      for (int i = theX.Lower(); i <= theX.Upper(); ++i)
      {
        aSumSq += theX(i) * theX(i);
        aSumCos += std::cos(myC * theX(i));
      }
      theY = -myA * std::exp(-myB * std::sqrt(aSumSq / n)) - std::exp(aSumCos / n) + myA + aE;
      return true;
    }

  private:
    double myA;
    double myB;
    double myC;
  };

  class LinearResidual
  {
  public:
    LinearResidual(const math_Matrix& theA, const math_Vector& theB)
        : myA(theA),
          myB(theB)
    {
    }

    bool Value(const math_Vector& theX, double& theY) const
    {
      theY = 0.0;
      for (int i = myA.LowerRow(); i <= myA.UpperRow(); ++i)
      {
        double aResidual = -myB(i);
        for (int j = myA.LowerCol(); j <= myA.UpperCol(); ++j)
        {
          aResidual += myA(i, j) * theX(j);
        }
        theY += aResidual * aResidual;
      }
      return true;
    }

    bool Gradient(const math_Vector& theX, math_Vector& theG) const
    {

      const int   m = myA.UpperRow() - myA.LowerRow() + 1;
      math_Vector aResidual(1, m);
      for (int i = myA.LowerRow(); i <= myA.UpperRow(); ++i)
      {
        aResidual(i - myA.LowerRow() + 1) = -myB(i);
        for (int j = myA.LowerCol(); j <= myA.UpperCol(); ++j)
        {
          aResidual(i - myA.LowerRow() + 1) += myA(i, j) * theX(j);
        }
      }

      for (int j = myA.LowerCol(); j <= myA.UpperCol(); ++j)
      {
        theG(j) = 0.0;
        for (int i = myA.LowerRow(); i <= myA.UpperRow(); ++i)
        {
          theG(j) += 2.0 * myA(i, j) * aResidual(i - myA.LowerRow() + 1);
        }
      }
      return true;
    }

    bool Values(const math_Vector& theX, double& theY, math_Vector& theG) const
    {
      return Value(theX, theY) && Gradient(theX, theG);
    }

  private:
    math_Matrix myA;
    math_Vector myB;
  };

  template <typename Lambda>
  class SystemLambda
  {
  public:
    SystemLambda(Lambda theLambda, int theNbEquations)
        : myLambda(std::move(theLambda)),
          myNbEquations(theNbEquations)
    {
    }

    int NbEquations() const { return myNbEquations; }

    bool Value(const math_Vector& theX, math_Vector& theF) const { return myLambda(theX, theF); }

  private:
    Lambda myLambda;
    int    myNbEquations;
  };

  template <typename Lambda>
  SystemLambda<Lambda> MakeSystem(Lambda theLambda, int theNbEquations)
  {
    return SystemLambda<Lambda>(std::move(theLambda), theNbEquations);
  }

} // namespace MathUtils
