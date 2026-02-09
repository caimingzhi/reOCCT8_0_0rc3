

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_DirectPolynomialRoots.hpp>
#include <StdFail_InfiniteSolutions.hpp>

#include <algorithm>
#include <array>
#include <cmath>

namespace
{

  const double ZERO_THRESHOLD = 1.0e-30;

  const double MACHINE_EPSILON = RealEpsilon();

  const double FLOATING_RADIX = 2.0;

  const double INV_LOG_RADIX = 1.0 / std::log(2.0);

  constexpr int MAX_NEWTON_ITERATIONS = 10;

  constexpr double OVERFLOW_LIMIT = 1.0e+80;

  double EvaluatePolynomial(const int theN, const double* thePoly, const double theX)
  {
    double aResult = thePoly[0];
    for (int i = 1; i < theN; ++i)
    {
      aResult = aResult * theX + thePoly[i];
    }
    return aResult;
  }

  void EvaluatePolynomialWithDerivative(const int     theN,
                                        const double* thePoly,
                                        const double  theX,
                                        double&       theValue,
                                        double&       theDerivative)
  {
    theValue      = thePoly[0] * theX + thePoly[1];
    theDerivative = thePoly[0];

    for (int i = 2; i < theN; ++i)
    {
      theDerivative = theDerivative * theX + theValue;
      theValue      = theValue * theX + thePoly[i];
    }
  }

  double RefineRoot(const int theN, const double* thePoly, const double theInitialGuess)
  {
    double       aValue        = 0.0;
    double       aDerivative   = 0.0;
    double       aSolution     = theInitialGuess;
    const double aInitialValue = EvaluatePolynomial(theN, thePoly, theInitialGuess);

    for (int iter = 1; iter < MAX_NEWTON_ITERATIONS; ++iter)
    {
      EvaluatePolynomialWithDerivative(theN, thePoly, aSolution, aValue, aDerivative);

      if (std::abs(aDerivative) <= ZERO_THRESHOLD)
      {
        break;
      }

      const double aDelta = -aValue / aDerivative;

      if (std::abs(aDelta) <= MACHINE_EPSILON * std::abs(aSolution))
      {
        break;
      }

      aSolution += aDelta;
    }

    return (std::abs(aValue) <= std::abs(aInitialValue)) ? aSolution : theInitialGuess;
  }

  template <typename... Coeffs>
  inline double RefinePolynomialRoot(const double theInitialGuess, Coeffs... theCoeffs)
  {
    const double aCoeffs[] = {theCoeffs...};
    const size_t N         = sizeof...(Coeffs);
    return RefineRoot(N, aCoeffs, theInitialGuess);
  }

  template <typename... Args>
  inline void ScaleAndRefineAllRoots(double*      theRoots,
                                     const int    theNbRoots,
                                     const double theScaleFactor,
                                     Args... theCoeffs)
  {
    for (int i = 0; i < theNbRoots; ++i)
    {
      theRoots[i] *= theScaleFactor;
      theRoots[i] = RefinePolynomialRoot(theRoots[i], theCoeffs...);
    }
  }

  int ComputeBaseExponent(const double theValue)
  {
    if (theValue > 1.0)
    {
      return static_cast<int>(std::log(theValue) * INV_LOG_RADIX);
    }
    else if (theValue < -1.0)
    {
      return static_cast<int>(-std::log(-theValue) * INV_LOG_RADIX);
    }
    return 0;
  }

  struct ScaledCoefficients
  {

    double A, B, C, D, E;

    double ScaleFactor;

    void ScaleQuartic(double theA, double theB, double theC, double theD, double theE)
    {
      const int aExp             = ComputeBaseExponent(theE) / 4;
      ScaleFactor                = std::pow(FLOATING_RADIX, aExp);
      const double aScaleFactor2 = ScaleFactor * ScaleFactor;

      A = theA / ScaleFactor;
      B = theB / aScaleFactor2;
      C = theC / (aScaleFactor2 * ScaleFactor);
      D = theD / (aScaleFactor2 * aScaleFactor2);
      E = theE / (aScaleFactor2 * aScaleFactor2);
    }

    void ScaleCubic(double theA, double theB, double theC, double theD)
    {
      const int aExp             = ComputeBaseExponent(theD) / 3;
      ScaleFactor                = std::pow(FLOATING_RADIX, aExp);
      const double aScaleFactor2 = ScaleFactor * ScaleFactor;

      A = theA / ScaleFactor;
      B = theB / aScaleFactor2;
      C = theC / (aScaleFactor2 * ScaleFactor);
      D = theD;
    }
  };

  double ComputeSpecialDiscriminant(const double theBeta,
                                    const double theGamma,
                                    const double theDel,
                                    const double theA1)
  {
    const double aSigma = theBeta * theGamma / 3.0 - 2.0 * theBeta * theBeta * theBeta / 27.0;
    const double aPsi   = theGamma * theGamma * (4.0 * theGamma - theBeta * theBeta) / 27.0;

    double aD1;
    if (aSigma >= 0.0)
    {
      aD1 = aSigma + 2.0 * std::sqrt(-theA1);
    }
    else
    {
      aD1 = aSigma - 2.0 * std::sqrt(-theA1);
    }

    const double aD2 = aPsi / aD1;

    if (std::abs(theDel - aD1) >= 18.0 * MACHINE_EPSILON * (std::abs(theDel) + std::abs(aD1))
        && std::abs(theDel - aD2) >= 24.0 * MACHINE_EPSILON * (std::abs(theDel) + std::abs(aD2)))
    {
      return (theDel - aD1) * (theDel - aD2) / 4.0;
    }

    return 0.0;
  }

  void SolveCubicThreeRealRoots(const double theBeta,
                                const double theGamma,
                                const double theDel,
                                const double theP,
                                const double theQ,
                                const double theDiscr,
                                double*      theRoots)
  {
    if (theBeta == 0.0 && theQ == 0.0)
    {

      theRoots[0] = std::sqrt(-theP);
      theRoots[1] = -theRoots[0];
      theRoots[2] = 0.0;
    }
    else
    {
      const double aSb    = (theBeta >= 0.0) ? 1.0 : -1.0;
      const double aOmega = std::atan(0.5 * theQ / std::sqrt(-theDiscr));
      const double aSp3   = std::sqrt(-theP / 3.0);
      const double aY1    = -2.0 * aSb * aSp3 * std::cos(M_PI / 6.0 - aSb * aOmega / 3.0);

      theRoots[0] = -theBeta / 3.0 + aY1;

      if (theBeta * theQ <= 0.0)
      {
        theRoots[1] = -theBeta / 3.0 + 2.0 * aSp3 * std::sin(aOmega / 3.0);
      }
      else
      {

        const double aDbg  = theDel - theBeta * theGamma;
        const double aSdbg = (aDbg >= 0.0) ? 1.0 : -1.0;
        const double aDen1 =
          8.0 * theBeta * theBeta / 9.0 - 4.0 * theBeta * aY1 / 3.0 - 2.0 * theQ / aY1;
        const double aDen2 = 2.0 * aY1 * aY1 - theQ / aY1;
        theRoots[1]        = aDbg / aDen1 + aSdbg * std::sqrt(-27.0 * theDiscr) / aDen2;
      }

      theRoots[2] = -theDel / (theRoots[0] * theRoots[1]);
    }
  }

  void SolveCubicOneRealRoot(const double theBeta,
                             const double theDel,
                             const double theP,
                             const double theQ,
                             const double theDiscr,
                             double*      theRoots)
  {
    double aU = std::sqrt(theDiscr) + std::abs(theQ / 2.0);
    aU        = (aU >= 0.0) ? std::pow(aU, 1.0 / 3.0) : -std::pow(std::abs(aU), 1.0 / 3.0);

    double aH;
    if (theP >= 0.0)
    {
      aH = aU * aU + theP / 3.0 + (theP / aU) * (theP / aU) / 9.0;
    }
    else
    {
      aH = aU * std::abs(theQ) / (aU * aU - theP / 3.0);
    }

    if (theBeta * theQ >= 0.0)
    {
      if (std::abs(aH) <= RealSmall() && std::abs(theQ) <= RealSmall())
      {
        theRoots[0] = -theBeta / 3.0 - aU + theP / (3.0 * aU);
      }
      else
      {
        theRoots[0] = -theBeta / 3.0 - theQ / aH;
      }
    }
    else
    {
      theRoots[0] = -theDel / (theBeta * theBeta / 9.0 + aH - theBeta * theQ / (3.0 * aH));
    }
  }

  void SolveCubicMultipleRoots(const double theBeta,
                               const double theGamma,
                               const double theDel,
                               const double theP,
                               const double theQ,
                               double*      theRoots,
                               int&         theNbRoots)
  {
    theNbRoots        = 3;
    const double aSq  = (theQ >= 0.0) ? 1.0 : -1.0;
    const double aSp3 = std::sqrt(-theP / 3.0);

    if (theBeta * theQ <= 0.0)
    {
      theRoots[0] = -theBeta / 3.0 + aSq * aSp3;
      theRoots[1] = theRoots[0];

      if (theBeta * theQ == 0.0)
      {
        theRoots[2] = -theBeta / 3.0 - 2.0 * aSq * aSp3;
      }
      else
      {
        theRoots[2] = -theDel / (theRoots[0] * theRoots[1]);
      }
    }
    else
    {
      theRoots[0] = -theGamma / (theBeta + 3.0 * aSq * aSp3);
      theRoots[1] = theRoots[0];
      theRoots[2] = -theBeta / 3.0 - 2.0 * aSq * aSp3;
    }
  }

  bool ShouldReduceDegreeQuartic(const double theA,
                                 const double theB,
                                 const double theC,
                                 const double theD,
                                 const double theE)
  {
    if (std::abs(theA) <= ZERO_THRESHOLD)
    {
      return true;
    }

    double aMaxCoeff = ZERO_THRESHOLD;
    aMaxCoeff        = std::max(aMaxCoeff, std::abs(theB));
    aMaxCoeff        = std::max(aMaxCoeff, std::abs(theC));
    aMaxCoeff        = std::max(aMaxCoeff, std::abs(theD));
    aMaxCoeff        = std::max(aMaxCoeff, std::abs(theE));

    if (aMaxCoeff > ZERO_THRESHOLD)
    {
      aMaxCoeff = Epsilon(100.0 * aMaxCoeff);
    }

    if (std::abs(theA) <= aMaxCoeff)
    {
      const double aMaxCoeff1000 = 1000.0 * aMaxCoeff;
      bool         aWithA        = false;

      if (std::abs(theB) > ZERO_THRESHOLD && std::abs(theB) <= aMaxCoeff1000)
        aWithA = true;
      if (std::abs(theC) > ZERO_THRESHOLD && std::abs(theC) <= aMaxCoeff1000)
        aWithA = true;
      if (std::abs(theD) > ZERO_THRESHOLD && std::abs(theD) <= aMaxCoeff1000)
        aWithA = true;
      if (std::abs(theE) > ZERO_THRESHOLD && std::abs(theE) <= aMaxCoeff1000)
        aWithA = true;

      return !aWithA;
    }

    return false;
  }

  double SolveFerrariResolvent(const double theA,
                               const double theB,
                               const double theC,
                               const double theD,
                               bool&        theSuccess)
  {

    const double aR3 = -theB;
    const double aS3 = theA * theC - 4.0 * theD;
    const double aT3 = theD * (4.0 * theB - theA * theA) - theC * theC;

    math_DirectPolynomialRoots aCubicSolver(1.0, aR3, aS3, aT3);

    if (!aCubicSolver.IsDone())
    {
      theSuccess = false;
      return 0.0;
    }

    theSuccess = true;

    double aY0 = aCubicSolver.Value(1);
    for (int i = 2; i <= aCubicSolver.NbSolutions(); ++i)
    {
      if (aCubicSolver.Value(i) > aY0)
      {
        aY0 = aCubicSolver.Value(i);
      }
    }

    return aY0;
  }

  struct QuarticFactorization
  {

    double P1;

    double Q1;

    double P2;

    double Q2;
  };

  QuarticFactorization FactorQuarticViaFerrari(const double theA,
                                               const double theB,
                                               const double theC,
                                               const double theD,
                                               const double theY0)
  {
    QuarticFactorization aFactors;

    const double aDiscr  = theA * theY0 * 0.5 - theC;
    const double aSdiscr = (aDiscr >= 0.0) ? 1.0 : -1.0;

    double aP0 = theA * theA * 0.25 - theB + theY0;
    aP0        = (aP0 < 0.0) ? 0.0 : std::sqrt(aP0);

    double aQ0 = theY0 * theY0 * 0.25 - theD;

    if (std::abs(aQ0) < 10 * MACHINE_EPSILON)
    {
      aQ0 = 0.0;
    }
    else
    {
      aQ0 = (aQ0 < 0.0) ? 0.0 : std::sqrt(aQ0);
    }

    const double aAdemi    = theA * 0.5;
    const double aYdemi    = theY0 * 0.5;
    const double aSdiscrQ0 = aSdiscr * aQ0;

    aFactors.P1 = aAdemi + aP0;
    aFactors.Q1 = aYdemi + aSdiscrQ0;
    aFactors.P2 = aAdemi - aP0;
    aFactors.Q2 = aYdemi - aSdiscrQ0;

    const double anEps = 100.0 * MACHINE_EPSILON;

    if (std::abs(aFactors.P1) <= anEps)
      aFactors.P1 = 0.0;
    if (std::abs(aFactors.P2) <= anEps)
      aFactors.P2 = 0.0;
    if (std::abs(aFactors.Q1) <= anEps)
      aFactors.Q1 = 0.0;
    if (std::abs(aFactors.Q2) <= anEps)
      aFactors.Q2 = 0.0;

    return aFactors;
  }

} // namespace

math_DirectPolynomialRoots::math_DirectPolynomialRoots(const double theA,
                                                       const double theB,
                                                       const double theC,
                                                       const double theD,
                                                       const double theE)
{
  myInfiniteStatus = false;
  myDone           = true;
  Solve(theA, theB, theC, theD, theE);
}

math_DirectPolynomialRoots::math_DirectPolynomialRoots(const double theA,
                                                       const double theB,
                                                       const double theC,
                                                       const double theD)
{
  myDone           = true;
  myInfiniteStatus = false;
  Solve(theA, theB, theC, theD);
}

math_DirectPolynomialRoots::math_DirectPolynomialRoots(const double theA,
                                                       const double theB,
                                                       const double theC)
{
  myDone           = true;
  myInfiniteStatus = false;
  Solve(theA, theB, theC);
}

math_DirectPolynomialRoots::math_DirectPolynomialRoots(const double theA, const double theB)
{
  myDone           = true;
  myInfiniteStatus = false;
  Solve(theA, theB);
}

void math_DirectPolynomialRoots::Solve(const double theA,
                                       const double theB,
                                       const double theC,
                                       const double theD,
                                       const double theE)
{

  if (ShouldReduceDegreeQuartic(theA, theB, theC, theD, theE))
  {
    Solve(theB, theC, theD, theE);
    return;
  }

  const double A = theB / theA;
  const double B = theC / theA;
  const double C = theD / theA;
  const double D = theE / theA;

  ScaledCoefficients aScaled;
  aScaled.ScaleQuartic(A, B, C, D, D);

  bool         aSuccess = false;
  const double aY0 = SolveFerrariResolvent(aScaled.A, aScaled.B, aScaled.C, aScaled.D, aSuccess);

  if (!aSuccess)
  {
    myDone = false;
    return;
  }

  const QuarticFactorization aFactors =
    FactorQuarticViaFerrari(aScaled.A, aScaled.B, aScaled.C, aScaled.D, aY0);

  math_DirectPolynomialRoots aQuadratic1(1.0, aFactors.P1, aFactors.Q1);
  if (!aQuadratic1.IsDone())
  {
    myDone = false;
    return;
  }

  math_DirectPolynomialRoots aQuadratic2(1.0, aFactors.P2, aFactors.Q2);
  if (!aQuadratic2.IsDone())
  {
    myDone = false;
    return;
  }

  myNbSol    = aQuadratic1.NbSolutions() + aQuadratic2.NbSolutions();
  int aIndex = 0;

  for (int i = 0; i < aQuadratic1.NbSolutions(); ++i)
  {
    myRoots[aIndex++] = aQuadratic1.myRoots[i];
  }

  for (int i = 0; i < aQuadratic2.NbSolutions(); ++i)
  {
    myRoots[aIndex++] = aQuadratic2.myRoots[i];
  }

  ScaleAndRefineAllRoots(myRoots, myNbSol, aScaled.ScaleFactor, theA, theB, theC, theD, theE);
}

void math_DirectPolynomialRoots::Solve(const double theA,
                                       const double theB,
                                       const double theC,
                                       const double theD)
{

  if (std::abs(theA) <= ZERO_THRESHOLD)
  {
    Solve(theB, theC, theD);
    return;
  }

  const double aBeta  = theB / theA;
  const double aGamma = theC / theA;
  const double aDel   = theD / theA;

  ScaledCoefficients aScaled;
  aScaled.ScaleCubic(aBeta, aGamma, aDel, aDel);

  const double aP1 = aScaled.B;
  const double aP2 = -(aScaled.A * aScaled.A) / 3.0;
  double       aP  = aP1 + aP2;
  const double aEp = 5.0 * MACHINE_EPSILON * (std::abs(aP1) + std::abs(aP2));
  if (std::abs(aP) <= aEp)
    aP = 0.0;

  const double aQ1 = aScaled.C;
  const double aQ2 = -aScaled.A * aScaled.B / 3.0;
  const double aQ3 = 2.0 * (aScaled.A * aScaled.A * aScaled.A) / 27.0;
  double       aQ  = aQ1 + aQ2 + aQ3;
  const double aEq = 10.0 * MACHINE_EPSILON * (std::abs(aQ1) + std::abs(aQ2) + std::abs(aQ3));
  if (std::abs(aQ) <= aEq)
    aQ = 0.0;

  if (std::abs(aP) > OVERFLOW_LIMIT)
  {
    myDone = false;
    return;
  }

  const double aA1    = (aP * aP * aP) / 27.0;
  const double aA2    = (aQ * aQ) / 4.0;
  double       aDiscr = aA1 + aA2;

  if (aP < 0.0)
  {
    aDiscr = ComputeSpecialDiscriminant(aScaled.A, aScaled.B, aScaled.C, aA1);
  }

  if (aDiscr < 0.0)
  {

    myNbSol = 3;
    SolveCubicThreeRealRoots(aScaled.A, aScaled.B, aScaled.C, aP, aQ, aDiscr, myRoots);
  }
  else if (aDiscr > 0.0)
  {

    myNbSol = 1;
    SolveCubicOneRealRoot(aScaled.A, aScaled.C, aP, aQ, aDiscr, myRoots);
  }
  else
  {

    SolveCubicMultipleRoots(aScaled.A, aScaled.B, aScaled.C, aP, aQ, myRoots, myNbSol);
  }

  ScaleAndRefineAllRoots(myRoots, myNbSol, aScaled.ScaleFactor, theA, theB, theC, theD);
}

void math_DirectPolynomialRoots::Solve(const double theA, const double theB, const double theC)
{

  if (std::abs(theA) <= ZERO_THRESHOLD)
  {
    Solve(theB, theC);
    return;
  }

  const double P = theB / theA;
  const double Q = theC / theA;

  const double aEpsD    = 3.0 * MACHINE_EPSILON * (P * P + std::abs(4.0 * Q));
  double       aDiscrim = P * P - 4.0 * Q;

  if (std::abs(aDiscrim) <= aEpsD)
  {
    aDiscrim = 0.0;
  }

  if (aDiscrim < 0.0)
  {

    myNbSol = 0;
  }
  else if (aDiscrim == 0.0)
  {

    myNbSol    = 2;
    myRoots[0] = -0.5 * P;
    myRoots[0] = RefinePolynomialRoot(myRoots[0], 1.0, P, Q);
    myRoots[1] = myRoots[0];
  }
  else
  {

    myNbSol = 2;
    if (P > 0.0)
    {
      myRoots[0] = -(P + std::sqrt(aDiscrim)) / 2.0;
    }
    else
    {
      myRoots[0] = -(P - std::sqrt(aDiscrim)) / 2.0;
    }
    myRoots[0] = RefinePolynomialRoot(myRoots[0], 1.0, P, Q);
    myRoots[1] = Q / myRoots[0];
    myRoots[1] = RefinePolynomialRoot(myRoots[1], 1.0, P, Q);
  }
}

void math_DirectPolynomialRoots::Solve(const double theA, const double theB)
{
  if (std::abs(theA) <= ZERO_THRESHOLD)
  {
    if (std::abs(theB) <= ZERO_THRESHOLD)
    {

      myInfiniteStatus = true;
      return;
    }

    myNbSol = 0;
    return;
  }

  myNbSol    = 1;
  myRoots[0] = -theB / theA;
}

void math_DirectPolynomialRoots::Dump(Standard_OStream& theStream) const
{
  theStream << "math_DirectPolynomialRoots ";

  if (!myDone)
  {
    theStream << " Not Done \n";
  }
  else if (myInfiniteStatus)
  {
    theStream << " Status = Infinity Roots \n";
  }
  else
  {
    theStream << " Status = Not Infinity Roots \n";
    theStream << " Number of solutions = " << myNbSol << "\n";
    for (int i = 1; i <= myNbSol; i++)
    {
      theStream << " Solution number " << i << " = " << myRoots[i - 1] << "\n";
    }
  }
}
