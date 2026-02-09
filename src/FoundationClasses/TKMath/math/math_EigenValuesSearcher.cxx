#include <math_EigenValuesSearcher.hpp>

#include <StdFail_NotDone.hpp>

namespace
{

  const int MAX_ITERATIONS = 30;

  double computeHypotenuseLength(const double theX, const double theY)
  {
    return std::sqrt(theX * theX + theY * theY);
  }

  void shiftSubdiagonalElements(NCollection_Array1<double>& theSubdiagWork, const int theSize)
  {
    for (int anIdx = 2; anIdx <= theSize; anIdx++)
      theSubdiagWork(anIdx - 1) = theSubdiagWork(anIdx);
    theSubdiagWork(theSize) = 0.0;
  }

  int findSubmatrixEnd(const NCollection_Array1<double>& theDiagWork,
                       const NCollection_Array1<double>& theSubdiagWork,
                       const int                         theStart,
                       const int                         theSize)
  {
    int aSubmatrixEnd;
    for (aSubmatrixEnd = theStart; aSubmatrixEnd <= theSize - 1; aSubmatrixEnd++)
    {
      const double aDiagSum =
        std::abs(theDiagWork(aSubmatrixEnd)) + std::abs(theDiagWork(aSubmatrixEnd + 1));

      if (std::abs(theSubdiagWork(aSubmatrixEnd)) + aDiagSum == aDiagSum)
        break;
    }
    return aSubmatrixEnd;
  }

  double computeWilkinsonShift(const NCollection_Array1<double>& theDiagWork,
                               const NCollection_Array1<double>& theSubdiagWork,
                               const int                         theStart,
                               const int                         theEnd)
  {
    double aShift =
      (theDiagWork(theStart + 1) - theDiagWork(theStart)) / (2.0 * theSubdiagWork(theStart));
    const double aRadius = computeHypotenuseLength(1.0, aShift);

    if (aShift < 0.0)
      aShift =
        theDiagWork(theEnd) - theDiagWork(theStart) + theSubdiagWork(theStart) / (aShift - aRadius);
    else
      aShift =
        theDiagWork(theEnd) - theDiagWork(theStart) + theSubdiagWork(theStart) / (aShift + aRadius);

    return aShift;
  }

  bool performQLStep(NCollection_Array1<double>& theDiagWork,
                     NCollection_Array1<double>& theSubdiagWork,
                     NCollection_Array2<double>& theEigenVecWork,
                     const int                   theStart,
                     const int                   theEnd,
                     const double                theShift,
                     const int                   theSize)
  {
    double aSine     = 1.0;
    double aCosine   = 1.0;
    double aPrevDiag = 0.0;
    double aShift    = theShift;
    double aRadius   = 0.0;

    int aRowIdx;
    for (aRowIdx = theEnd - 1; aRowIdx >= theStart; aRowIdx--)
    {
      const double aTempVal       = aSine * theSubdiagWork(aRowIdx);
      const double aSubdiagTemp   = aCosine * theSubdiagWork(aRowIdx);
      aRadius                     = computeHypotenuseLength(aTempVal, aShift);
      theSubdiagWork(aRowIdx + 1) = aRadius;

      if (aRadius == 0.0)
      {
        theDiagWork(aRowIdx + 1) -= aPrevDiag;
        theSubdiagWork(theEnd) = 0.0;
        break;
      }

      aSine   = aTempVal / aRadius;
      aCosine = aShift / aRadius;
      aShift  = theDiagWork(aRowIdx + 1) - aPrevDiag;
      const double aRadiusTemp =
        (theDiagWork(aRowIdx) - aShift) * aSine + 2.0 * aCosine * aSubdiagTemp;
      aPrevDiag                = aSine * aRadiusTemp;
      theDiagWork(aRowIdx + 1) = aShift + aPrevDiag;
      aShift                   = aCosine * aRadiusTemp - aSubdiagTemp;

      for (int aVecIdx = 1; aVecIdx <= theSize; aVecIdx++)
      {
        const double aTempVec = theEigenVecWork(aVecIdx, aRowIdx + 1);
        theEigenVecWork(aVecIdx, aRowIdx + 1) =
          aSine * theEigenVecWork(aVecIdx, aRowIdx) + aCosine * aTempVec;
        theEigenVecWork(aVecIdx, aRowIdx) =
          aCosine * theEigenVecWork(aVecIdx, aRowIdx) - aSine * aTempVec;
      }
    }

    if (aRadius == 0.0 && aRowIdx >= 1)
      return true;

    theDiagWork(theStart) -= aPrevDiag;
    theSubdiagWork(theStart) = aShift;
    theSubdiagWork(theEnd)   = 0.0;

    return true;
  }

  bool performQLAlgorithm(NCollection_Array1<double>& theDiagWork,
                          NCollection_Array1<double>& theSubdiagWork,
                          NCollection_Array2<double>& theEigenVecWork,
                          const int                   theSize)
  {
    for (int aSubmatrixStart = 1; aSubmatrixStart <= theSize; aSubmatrixStart++)
    {
      int aIterCount = 0;
      int aSubmatrixEnd;

      do
      {
        aSubmatrixEnd = findSubmatrixEnd(theDiagWork, theSubdiagWork, aSubmatrixStart, theSize);

        if (aSubmatrixEnd != aSubmatrixStart)
        {
          if (aIterCount++ == MAX_ITERATIONS)
            return false;

          const double aShift =
            computeWilkinsonShift(theDiagWork, theSubdiagWork, aSubmatrixStart, aSubmatrixEnd);

          if (!performQLStep(theDiagWork,
                             theSubdiagWork,
                             theEigenVecWork,
                             aSubmatrixStart,
                             aSubmatrixEnd,
                             aShift,
                             theSize))
            return false;
        }
      } while (aSubmatrixEnd != aSubmatrixStart);
    }

    return true;
  }

} // namespace

math_EigenValuesSearcher::math_EigenValuesSearcher(const NCollection_Array1<double>& theDiagonal,
                                                   const NCollection_Array1<double>& theSubdiagonal)
    : myDiagonal(theDiagonal),
      mySubdiagonal(theSubdiagonal),
      myIsDone(false),
      myN(theDiagonal.Length()),
      myEigenValues(1, theDiagonal.Length()),
      myEigenVectors(1, theDiagonal.Length(), 1, theDiagonal.Length())
{
  if (theSubdiagonal.Length() != myN)
  {
    return;
  }

  myDiagonal.UpdateLowerBound(1);
  mySubdiagonal.UpdateLowerBound(1);

  shiftSubdiagonalElements(mySubdiagonal, myN);

  for (int aRowIdx = 1; aRowIdx <= myN; aRowIdx++)
    for (int aColIdx = 1; aColIdx <= myN; aColIdx++)
      myEigenVectors(aRowIdx, aColIdx) = (aRowIdx == aColIdx) ? 1.0 : 0.0;

  bool isConverged = true;

  if (myN != 1)
  {
    isConverged = performQLAlgorithm(myDiagonal, mySubdiagonal, myEigenVectors, myN);
  }

  if (isConverged)
  {
    for (int anIdx = 1; anIdx <= myN; anIdx++)
      myEigenValues(anIdx) = myDiagonal(anIdx);
  }

  myIsDone = isConverged;
}

bool math_EigenValuesSearcher::IsDone() const
{
  return myIsDone;
}

int math_EigenValuesSearcher::Dimension() const
{
  return myN;
}

double math_EigenValuesSearcher::EigenValue(const int theIndex) const
{
  return myEigenValues(theIndex);
}

math_Vector math_EigenValuesSearcher::EigenVector(const int theIndex) const
{
  math_Vector aVector(1, myN);

  for (int anIdx = 1; anIdx <= myN; anIdx++)
    aVector(anIdx) = myEigenVectors(anIdx, theIndex);

  return aVector;
}
