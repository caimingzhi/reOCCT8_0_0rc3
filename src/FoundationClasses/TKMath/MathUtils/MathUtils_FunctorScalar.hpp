#pragma once

#include <math_Vector.hpp>

#include <cmath>
#include <initializer_list>
#include <utility>

namespace MathUtils
{

  template <typename Lambda>
  class ScalarLambda
  {
  public:
    explicit ScalarLambda(Lambda theLambda)
        : myLambda(std::move(theLambda))
    {
    }

    bool Value(double theX, double& theY) const { return myLambda(theX, theY); }

  private:
    Lambda myLambda;
  };

  template <typename Lambda>
  class ScalarLambdaWithDerivative
  {
  public:
    explicit ScalarLambdaWithDerivative(Lambda theLambda)
        : myLambda(std::move(theLambda))
    {
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      return myLambda(theX, theY, theDY);
    }

    bool Value(double theX, double& theY) const
    {
      double aDummy = 0.0;
      return myLambda(theX, theY, aDummy);
    }

  private:
    Lambda myLambda;
  };

  template <typename Lambda>
  ScalarLambda<Lambda> MakeScalar(Lambda theLambda)
  {
    return ScalarLambda<Lambda>(std::move(theLambda));
  }

  template <typename Lambda>
  ScalarLambdaWithDerivative<Lambda> MakeScalarWithDerivative(Lambda theLambda)
  {
    return ScalarLambdaWithDerivative<Lambda>(std::move(theLambda));
  }

  class Polynomial
  {
  public:
    Polynomial(std::initializer_list<double> theCoeffs)
        : myCoeffs(0, static_cast<int>(theCoeffs.size()) - 1)
    {
      int anIdx = 0;
      for (double aCoeff : theCoeffs)
      {
        myCoeffs(anIdx++) = aCoeff;
      }
    }

    explicit Polynomial(const math_Vector& theCoeffs)
        : myCoeffs(theCoeffs)
    {
    }

    bool Value(double theX, double& theY) const
    {
      if (myCoeffs.Length() <= 0)
      {
        theY = 0.0;
        return true;
      }

      const int aLast = myCoeffs.Upper();
      theY            = myCoeffs(aLast);
      for (int i = aLast - 1; i >= myCoeffs.Lower(); --i)
      {
        theY = theY * theX + myCoeffs(i);
      }
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      if (myCoeffs.Length() <= 0)
      {
        theY  = 0.0;
        theDY = 0.0;
        return true;
      }

      const int n = myCoeffs.Length();
      if (n == 1)
      {
        theY  = myCoeffs(myCoeffs.Lower());
        theDY = 0.0;
        return true;
      }

      const int aLower = myCoeffs.Lower();
      const int aLast  = myCoeffs.Upper();
      theY             = myCoeffs(aLast);
      theDY            = 0.0;
      for (int i = aLast - 1; i >= aLower; --i)
      {
        theDY = theDY * theX + theY;
        theY  = theY * theX + myCoeffs(i);
      }
      return true;
    }

    int Degree() const { return myCoeffs.Length() <= 0 ? 0 : myCoeffs.Length() - 1; }

    double Coefficient(int theIndex) const
    {
      const int aIdx = myCoeffs.Lower() + theIndex;
      return (aIdx >= myCoeffs.Lower() && aIdx <= myCoeffs.Upper()) ? myCoeffs(aIdx) : 0.0;
    }

  private:
    math_Vector myCoeffs;
  };

  class Rational
  {
  public:
    Rational(const math_Vector& theNum, const math_Vector& theDenom)
        : myNum(theNum),
          myDenom(theDenom)
    {
    }

    Rational(std::initializer_list<double> theNum, std::initializer_list<double> theDenom)
        : myNum(0, static_cast<int>(theNum.size()) - 1),
          myDenom(0, static_cast<int>(theDenom.size()) - 1)
    {
      int anIdx = 0;
      for (double aCoeff : theNum)
      {
        myNum(anIdx++) = aCoeff;
      }
      anIdx = 0;
      for (double aCoeff : theDenom)
      {
        myDenom(anIdx++) = aCoeff;
      }
    }

    bool Value(double theX, double& theY) const
    {
      double aNum   = 0.0;
      double aDenom = 0.0;

      if (myNum.Length() > 0)
      {
        const int aLast = myNum.Upper();
        aNum            = myNum(aLast);
        for (int i = aLast - 1; i >= myNum.Lower(); --i)
        {
          aNum = aNum * theX + myNum(i);
        }
      }

      if (myDenom.Length() > 0)
      {
        const int aLast = myDenom.Upper();
        aDenom          = myDenom(aLast);
        for (int i = aLast - 1; i >= myDenom.Lower(); --i)
        {
          aDenom = aDenom * theX + myDenom(i);
        }
      }

      if (std::abs(aDenom) < 1e-15)
      {
        return false;
      }

      theY = aNum / aDenom;
      return true;
    }

  private:
    math_Vector myNum;
    math_Vector myDenom;
  };

  template <typename Outer, typename Inner>
  class Composite
  {
  public:
    Composite(Outer theOuter, Inner theInner)
        : myOuter(std::move(theOuter)),
          myInner(std::move(theInner))
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aInner = 0.0;
      if (!myInner.Value(theX, aInner))
      {
        return false;
      }
      return myOuter.Value(aInner, theY);
    }

  private:
    Outer myOuter;
    Inner myInner;
  };

  template <typename Outer, typename Inner>
  Composite<Outer, Inner> MakeComposite(Outer theOuter, Inner theInner)
  {
    return Composite<Outer, Inner>(std::move(theOuter), std::move(theInner));
  }

  template <typename F, typename G>
  class Sum
  {
  public:
    Sum(F theF, G theG)
        : myF(std::move(theF)),
          myG(std::move(theG))
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aF = 0.0;
      double aG = 0.0;
      if (!myF.Value(theX, aF))
      {
        return false;
      }
      if (!myG.Value(theX, aG))
      {
        return false;
      }
      theY = aF + aG;
      return true;
    }

  private:
    F myF;
    G myG;
  };

  template <typename F, typename G>
  Sum<F, G> MakeSum(F theF, G theG)
  {
    return Sum<F, G>(std::move(theF), std::move(theG));
  }

  template <typename F, typename G>
  class Difference
  {
  public:
    Difference(F theF, G theG)
        : myF(std::move(theF)),
          myG(std::move(theG))
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aF = 0.0;
      double aG = 0.0;
      if (!myF.Value(theX, aF))
      {
        return false;
      }
      if (!myG.Value(theX, aG))
      {
        return false;
      }
      theY = aF - aG;
      return true;
    }

  private:
    F myF;
    G myG;
  };

  template <typename F, typename G>
  Difference<F, G> MakeDifference(F theF, G theG)
  {
    return Difference<F, G>(std::move(theF), std::move(theG));
  }

  template <typename F, typename G>
  class Product
  {
  public:
    Product(F theF, G theG)
        : myF(std::move(theF)),
          myG(std::move(theG))
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aF = 0.0;
      double aG = 0.0;
      if (!myF.Value(theX, aF))
      {
        return false;
      }
      if (!myG.Value(theX, aG))
      {
        return false;
      }
      theY = aF * aG;
      return true;
    }

  private:
    F myF;
    G myG;
  };

  template <typename F, typename G>
  Product<F, G> MakeProduct(F theF, G theG)
  {
    return Product<F, G>(std::move(theF), std::move(theG));
  }

  template <typename F, typename G>
  class Quotient
  {
  public:
    Quotient(F theF, G theG)
        : myF(std::move(theF)),
          myG(std::move(theG))
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aF = 0.0;
      double aG = 0.0;
      if (!myF.Value(theX, aF))
      {
        return false;
      }
      if (!myG.Value(theX, aG))
      {
        return false;
      }
      if (std::abs(aG) < 1e-15)
      {
        return false;
      }
      theY = aF / aG;
      return true;
    }

  private:
    F myF;
    G myG;
  };

  template <typename F, typename G>
  Quotient<F, G> MakeQuotient(F theF, G theG)
  {
    return Quotient<F, G>(std::move(theF), std::move(theG));
  }

  template <typename F>
  class Scaled
  {
  public:
    Scaled(F theF, double theScale)
        : myF(std::move(theF)),
          myScale(theScale)
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aF = 0.0;
      if (!myF.Value(theX, aF))
      {
        return false;
      }
      theY = myScale * aF;
      return true;
    }

  private:
    F      myF;
    double myScale;
  };

  template <typename F>
  Scaled<F> MakeScaled(F theF, double theScale)
  {
    return Scaled<F>(std::move(theF), theScale);
  }

  template <typename F>
  class Shifted
  {
  public:
    Shifted(F theF, double theShift)
        : myF(std::move(theF)),
          myShift(theShift)
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aF = 0.0;
      if (!myF.Value(theX, aF))
      {
        return false;
      }
      theY = aF + myShift;
      return true;
    }

  private:
    F      myF;
    double myShift;
  };

  template <typename F>
  Shifted<F> MakeShifted(F theF, double theShift)
  {
    return Shifted<F>(std::move(theF), theShift);
  }

  template <typename F>
  class Negated
  {
  public:
    explicit Negated(F theF)
        : myF(std::move(theF))
    {
    }

    bool Value(double theX, double& theY) const
    {
      double aF = 0.0;
      if (!myF.Value(theX, aF))
      {
        return false;
      }
      theY = -aF;
      return true;
    }

  private:
    F myF;
  };

  template <typename F>
  Negated<F> MakeNegated(F theF)
  {
    return Negated<F>(std::move(theF));
  }

  class Constant
  {
  public:
    explicit Constant(double theValue)
        : myValue(theValue)
    {
    }

    bool Value(double, double& theY) const
    {
      theY = myValue;
      return true;
    }

    bool Values(double, double& theY, double& theDY) const
    {
      theY  = myValue;
      theDY = 0.0;
      return true;
    }

  private:
    double myValue;
  };

  class Linear
  {
  public:
    Linear(double theSlope, double theIntercept)
        : mySlope(theSlope),
          myIntercept(theIntercept)
    {
    }

    bool Value(double theX, double& theY) const
    {
      theY = mySlope * theX + myIntercept;
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      theY  = mySlope * theX + myIntercept;
      theDY = mySlope;
      return true;
    }

  private:
    double mySlope;
    double myIntercept;
  };

  class Sine
  {
  public:
    Sine(double theAmplitude = 1.0,
         double theFrequency = 1.0,
         double thePhase     = 0.0,
         double theOffset    = 0.0)
        : myAmplitude(theAmplitude),
          myFrequency(theFrequency),
          myPhase(thePhase),
          myOffset(theOffset)
    {
    }

    bool Value(double theX, double& theY) const
    {
      theY = myAmplitude * std::sin(myFrequency * theX + myPhase) + myOffset;
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      const double anArg = myFrequency * theX + myPhase;
      theY               = myAmplitude * std::sin(anArg) + myOffset;
      theDY              = myAmplitude * myFrequency * std::cos(anArg);
      return true;
    }

  private:
    double myAmplitude;
    double myFrequency;
    double myPhase;
    double myOffset;
  };

  class Cosine
  {
  public:
    Cosine(double theAmplitude = 1.0,
           double theFrequency = 1.0,
           double thePhase     = 0.0,
           double theOffset    = 0.0)
        : myAmplitude(theAmplitude),
          myFrequency(theFrequency),
          myPhase(thePhase),
          myOffset(theOffset)
    {
    }

    bool Value(double theX, double& theY) const
    {
      theY = myAmplitude * std::cos(myFrequency * theX + myPhase) + myOffset;
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      const double anArg = myFrequency * theX + myPhase;
      theY               = myAmplitude * std::cos(anArg) + myOffset;
      theDY              = -myAmplitude * myFrequency * std::sin(anArg);
      return true;
    }

  private:
    double myAmplitude;
    double myFrequency;
    double myPhase;
    double myOffset;
  };

  class Exponential
  {
  public:
    Exponential(double theScale = 1.0, double theRate = 1.0, double theOffset = 0.0)
        : myScale(theScale),
          myRate(theRate),
          myOffset(theOffset)
    {
    }

    bool Value(double theX, double& theY) const
    {
      theY = myScale * std::exp(myRate * theX) + myOffset;
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      const double anExp = std::exp(myRate * theX);
      theY               = myScale * anExp + myOffset;
      theDY              = myScale * myRate * anExp;
      return true;
    }

  private:
    double myScale;
    double myRate;
    double myOffset;
  };

  class Power
  {
  public:
    Power(double theExponent, double theScale = 1.0, double theOffset = 0.0)
        : myExponent(theExponent),
          myScale(theScale),
          myOffset(theOffset)
    {
    }

    bool Value(double theX, double& theY) const
    {
      if (theX < 0.0 && myExponent != std::floor(myExponent))
      {
        return false;
      }
      theY = myScale * std::pow(theX, myExponent) + myOffset;
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      if (theX < 0.0 && myExponent != std::floor(myExponent))
      {
        return false;
      }
      const double aPow = std::pow(theX, myExponent);
      theY              = myScale * aPow + myOffset;
      if (std::abs(theX) < 1e-15)
      {
        theDY = (myExponent == 1.0) ? myScale : 0.0;
      }
      else
      {
        theDY = myScale * myExponent * aPow / theX;
      }
      return true;
    }

  private:
    double myExponent;
    double myScale;
    double myOffset;
  };

  class Gaussian
  {
  public:
    Gaussian(double theAmplitude = 1.0, double theMean = 0.0, double theSigma = 1.0)
        : myAmplitude(theAmplitude),
          myMean(theMean),
          mySigma(theSigma)
    {
    }

    bool Value(double theX, double& theY) const
    {
      if (std::abs(mySigma) < 1e-15)
      {
        return false;
      }
      const double aZ = (theX - myMean) / mySigma;
      theY            = myAmplitude * std::exp(-0.5 * aZ * aZ);
      return true;
    }

    bool Values(double theX, double& theY, double& theDY) const
    {
      if (std::abs(mySigma) < 1e-15)
      {
        return false;
      }
      const double aZ   = (theX - myMean) / mySigma;
      const double aExp = std::exp(-0.5 * aZ * aZ);
      theY              = myAmplitude * aExp;
      theDY             = -myAmplitude * aZ * aExp / mySigma;
      return true;
    }

  private:
    double myAmplitude;
    double myMean;
    double mySigma;
  };

} // namespace MathUtils
