#include <math_GlobOptMin.hpp>

#include <math_BFGS.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>
#include <math_NewtonMinimum.hpp>
#include <math_Powell.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Precision.hpp>

#ifndef M_SQRT2
  #define M_SQRT2 1.41421356237309504880168872420969808
#endif

static double DistanceToBorder(const math_Vector& theX,
                               const math_Vector& theMin,
                               const math_Vector& theMax)
{
  double aDist = RealLast();

  for (int anIdx = theMin.Lower(); anIdx <= theMin.Upper(); ++anIdx)
  {
    const double aDist1 = std::abs(theX(anIdx) - theMin(anIdx));
    const double aDist2 = std::abs(theX(anIdx) - theMax(anIdx));

    aDist = std::min(aDist, std::min(aDist1, aDist2));
  }

  return aDist;
}

math_GlobOptMin::math_GlobOptMin(math_MultipleVarFunction* theFunc,
                                 const math_Vector&        theA,
                                 const math_Vector&        theB,
                                 const double              theC,
                                 const double              theDiscretizationTol,
                                 const double              theSameTol)
    : myN(theFunc->NbVariables()),
      myA(1, myN),
      myB(1, myN),
      myGlobA(1, myN),
      myGlobB(1, myN),
      myIsConstLocked(false),
      myX(1, myN),
      myTmp(1, myN),
      myV(1, myN),
      myMaxV(1, myN),
      myCellSize(0, myN - 1),
      myFilter(theFunc->NbVariables()),
      myCont(2),
      myF(Precision::Infinite())
{
  int i;

  myFunc                   = theFunc;
  myC                      = theC;
  myInitC                  = theC;
  myIsFindSingleSolution   = false;
  myFunctionalMinimalValue = -Precision::Infinite();
  myZ                      = -1;
  mySolCount               = 0;

  for (i = 1; i <= myN; i++)
  {
    myGlobA(i) = theA(i);
    myGlobB(i) = theB(i);

    myA(i) = theA(i);
    myB(i) = theB(i);
  }

  for (i = 1; i <= myN; i++)
  {
    myMaxV(i) = (myB(i) - myA(i)) / 3.0;
  }

  myTol     = theDiscretizationTol;
  mySameTol = theSameTol;

  const int aMaxSquareSearchSol = 200;
  int       aSolNb              = int(std::pow(3.0, double(myN)));
  myMinCellFilterSol            = std::max(2 * aSolNb, aMaxSquareSearchSol);
  initCellSize();
  ComputeInitSol();

  myDone = false;
}

void math_GlobOptMin::SetGlobalParams(math_MultipleVarFunction* theFunc,
                                      const math_Vector&        theA,
                                      const math_Vector&        theB,
                                      const double              theC,
                                      const double              theDiscretizationTol,
                                      const double              theSameTol)
{
  int i;

  myFunc     = theFunc;
  myC        = theC;
  myInitC    = theC;
  myZ        = -1;
  mySolCount = 0;

  for (i = 1; i <= myN; i++)
  {
    myGlobA(i) = theA(i);
    myGlobB(i) = theB(i);

    myA(i) = theA(i);
    myB(i) = theB(i);
  }

  for (i = 1; i <= myN; i++)
  {
    myMaxV(i) = (myB(i) - myA(i)) / 3.0;
  }

  myTol     = theDiscretizationTol;
  mySameTol = theSameTol;

  initCellSize();
  ComputeInitSol();

  myDone = false;
}

void math_GlobOptMin::SetLocalParams(const math_Vector& theLocalA, const math_Vector& theLocalB)
{
  int i;

  myZ = -1;
  for (i = 1; i <= myN; i++)
  {
    myA(i) = theLocalA(i);
    myB(i) = theLocalB(i);
  }

  for (i = 1; i <= myN; i++)
  {
    myMaxV(i) = (myB(i) - myA(i)) / 3.0;
  }

  myDone = false;
}

void math_GlobOptMin::SetTol(const double theDiscretizationTol, const double theSameTol)
{
  myTol     = theDiscretizationTol;
  mySameTol = theSameTol;
}

void math_GlobOptMin::GetTol(double& theDiscretizationTol, double& theSameTol)
{
  theDiscretizationTol = myTol;
  theSameTol           = mySameTol;
}

void math_GlobOptMin::Perform(const bool isFindSingleSolution)
{
  myDone = false;

  double minLength = RealLast();
  double maxLength = RealFirst();
  for (int i = 1; i <= myN; i++)
  {
    double currentLength = myB(i) - myA(i);
    if (currentLength < minLength)
      minLength = currentLength;
    if (currentLength > maxLength)
      maxLength = currentLength;

    myV(i) = 0.0;
  }

  if (minLength < Precision::PConfusion())
  {
#ifdef OCCT_DEBUG
    std::cout << "math_GlobOptMin::Perform(): Degenerated parameters space" << std::endl;
#endif

    return;
  }

  if (!myIsConstLocked)
  {

    computeInitialValues();
  }

  myE1 = minLength * myTol;
  myE2 = maxLength * myTol;

  myIsFindSingleSolution = isFindSingleSolution;
  if (isFindSingleSolution)
  {

    myE3 = 0.0;
  }
  else
  {
    if (myC > 1.0)
      myE3 = -maxLength * myTol / 4.0;
    else
      myE3 = -maxLength * myTol * myC / 4.0;
  }

  if (CheckFunctionalStopCriteria())
  {
    myDone = true;
    return;
  }

  myLastStep              = 0.0;
  isFirstCellFilterInvoke = true;
  computeGlobalExtremum(myN);

  myDone = true;
}

bool math_GlobOptMin::computeLocalExtremum(const math_Vector& thePnt,
                                           double&            theVal,
                                           math_Vector&       theOutPnt)
{
  int i;

  if (myCont >= 2 && dynamic_cast<math_MultipleVarFunctionWithHessian*>(myFunc))
  {
    math_MultipleVarFunctionWithHessian* aTmp =
      dynamic_cast<math_MultipleVarFunctionWithHessian*>(myFunc);
    math_NewtonMinimum newtonMinimum(*aTmp);
    newtonMinimum.SetBoundary(myGlobA, myGlobB);
    newtonMinimum.Perform(*aTmp, thePnt);

    if (newtonMinimum.IsDone())
    {
      newtonMinimum.Location(theOutPnt);
      theVal = newtonMinimum.Minimum();

      if (isInside(theOutPnt))
        return true;
    }
  }

  if (myCont >= 1 && dynamic_cast<math_MultipleVarFunctionWithGradient*>(myFunc))
  {
    math_MultipleVarFunctionWithGradient* aTmp =
      dynamic_cast<math_MultipleVarFunctionWithGradient*>(myFunc);
    math_BFGS bfgs(aTmp->NbVariables());
    bfgs.SetBoundary(myGlobA, myGlobB);
    bfgs.Perform(*aTmp, thePnt);

    if (bfgs.IsDone())
    {
      bfgs.Location(theOutPnt);
      theVal = bfgs.Minimum();

      if (isInside(theOutPnt))
        return true;
    }
  }

  if (dynamic_cast<math_MultipleVarFunction*>(myFunc))
  {
    math_Matrix m(1, myN, 1, myN, 0.0);
    for (i = 1; i <= myN; i++)
      m(i, i) = 1.0;

    math_Powell powell(*myFunc, 1e-10);
    powell.Perform(*myFunc, thePnt, m);

    if (powell.IsDone())
    {
      powell.Location(theOutPnt);
      theVal = powell.Minimum();

      if (isInside(theOutPnt))
        return true;
    }
  }

  return false;
}

void math_GlobOptMin::computeInitialValues()
{
  const double aMinLC  = 0.01;
  const double aMaxLC  = 1000.;
  const double aMinEps = 0.1;
  const double aMaxEps = 100.;
  int          i;
  math_Vector  aCurrPnt(1, myN);
  math_Vector  aBestPnt(1, myN);
  math_Vector  aParamStep(1, myN);
  double       aCurrVal = RealLast();

  double aLipConst = 0.0, aPrevValDiag, aPrevValProj;
  int    aPntNb    = 13;
  myFunc->Value(myA, aPrevValDiag);
  aPrevValProj = aPrevValDiag;
  double aStep = (myB - myA).Norm() / aPntNb;
  aParamStep   = (myB - myA) / aPntNb;
  for (i = 1; i <= aPntNb; i++)
  {
    aCurrPnt = myA + aParamStep * i;

    myFunc->Value(aCurrPnt, aCurrVal);
    aLipConst    = std::max(std::abs(aCurrVal - aPrevValDiag), aLipConst);
    aPrevValDiag = aCurrVal;

    aCurrPnt(1) = myA(1);
    myFunc->Value(aCurrPnt, aCurrVal);
    aLipConst    = std::max(std::abs(aCurrVal - aPrevValProj), aLipConst);
    aPrevValProj = aCurrVal;
  }

  myC = myInitC;
  aLipConst *= std::sqrt(myN) / aStep;
  if (aLipConst < myC * aMinEps)
    myC = std::max(aLipConst * aMinEps, aMinLC);
  else if (aLipConst > myC * aMaxEps)
    myC = std::min(myC * aMaxEps, aMaxLC);
}

void math_GlobOptMin::computeGlobalExtremum(int j)
{
  int         i;
  double      d              = RealLast(), aPrevVal;
  double      val            = RealLast();
  double      aStepBestValue = RealLast();
  math_Vector aStepBestPoint(1, myN);
  bool        isInside = false, isReached = false;

  double r1, r2, r;

  for (myX(j) = myA(j) + myE1; !isReached; myX(j) += myV(j))
  {
    if (myX(j) > myB(j))
    {
      myX(j)    = myB(j);
      isReached = true;
    }

    if (CheckFunctionalStopCriteria())
      return;

    if (j == 1)
    {
      isInside = false;
      aPrevVal = d;
      myFunc->Value(myX, d);
      r1 = (d + myZ * myC * myLastStep - myF) * myZ;

      r2 = ((d + aPrevVal - myC * myLastStep) * 0.5 - myF) * myZ;

      r = std::min(r1, r2);
      if (r > myE3)
      {
        double aSaveParam = myX(1);

        double aParam = (2 * myX(1) - myV(1)) * 0.5 + (aPrevVal - d) * 0.5 / myC;
        if (Precision::IsInfinite(aPrevVal))
          aParam = myX(1) - myV(1) * 0.5;

        myX(1)      = aParam;
        double aVal = 0;
        myFunc->Value(myX, aVal);
        myX(1) = aSaveParam;

        if ((aVal < d && aVal < aPrevVal) || DistanceToBorder(myX, myA, myB) < myE1)
        {
          isInside = computeLocalExtremum(myX, val, myTmp);
        }
      }
      aStepBestValue = (isInside && (val < d)) ? val : d;
      aStepBestPoint = (isInside && (val < d)) ? myTmp : myX;

      checkAddCandidate(aStepBestPoint, aStepBestValue);

      if (CheckFunctionalStopCriteria())
        return;

      myV(1)     = std::min(myE2 + std::abs(myF - d) / myC, myMaxV(1));
      myLastStep = myV(1);
    }
    else
    {
      myV(j) = RealLast() / 2.0;
      computeGlobalExtremum(j - 1);

      for (i = 1; i < j; i++)
        myV(i) = 0.0;
    }
    if (j < myN)
    {
      double aUpperDimStep = std::max(myV(j), myE2);
      if (myV(j + 1) > aUpperDimStep)
      {
        if (aUpperDimStep > myMaxV(j + 1))
          myV(j + 1) = myMaxV(j + 1);
        else
          myV(j + 1) = aUpperDimStep;
      }
    }
  }
}

bool math_GlobOptMin::isInside(const math_Vector& thePnt)
{
  int i;

  for (i = 1; i <= myN; i++)
  {
    if (thePnt(i) < myGlobA(i) || thePnt(i) > myGlobB(i))
      return false;
  }

  return true;
}

bool math_GlobOptMin::isStored(const math_Vector& thePnt)
{
  int         i, j;
  bool        isSame = true;
  math_Vector aTol(1, myN);
  aTol = (myB - myA) * mySameTol;

  if (mySolCount < myMinCellFilterSol)
  {
    for (i = 0; i < mySolCount; i++)
    {
      isSame = true;
      for (j = 1; j <= myN; j++)
      {
        if ((std::abs(thePnt(j) - myY(i * myN + j))) > aTol(j))
        {
          isSame = false;
          break;
        }
      }
      if (isSame)
        return true;
    }
  }
  else
  {
    NCollection_CellFilter_Inspector anInspector(myN, Precision::PConfusion());
    if (isFirstCellFilterInvoke)
    {
      myFilter.Reset(myCellSize);

      for (int aSolIdx = 0; aSolIdx < mySolCount; aSolIdx++)
      {
        math_Vector aVec(1, myN);
        for (int aSolDim = 1; aSolDim <= myN; aSolDim++)
          aVec(aSolDim) = myY(aSolIdx * myN + aSolDim);

        myFilter.Add(aVec, aVec);
      }
    }

    isFirstCellFilterInvoke = false;

    math_Vector aLow(1, myN), anUp(1, myN);
    anInspector.Shift(thePnt, myCellSize, aLow, anUp);

    anInspector.ClearFind();
    anInspector.SetCurrent(thePnt);
    myFilter.Inspect(aLow, anUp, anInspector);
    if (!anInspector.isFind())
    {

      myFilter.Add(thePnt, thePnt);
    }
  }
  return false;
}

void math_GlobOptMin::Points(const int theIndex, math_Vector& theSol)
{
  int j;

  for (j = 1; j <= myN; j++)
    theSol(j) = myY((theIndex - 1) * myN + j);
}

void math_GlobOptMin::initCellSize()
{
  for (int anIdx = 1; anIdx <= myN; anIdx++)
  {
    myCellSize(anIdx - 1) =
      (myGlobB(anIdx) - myGlobA(anIdx)) * Precision::PConfusion() / (2.0 * M_SQRT2);
  }
}

bool math_GlobOptMin::CheckFunctionalStopCriteria()
{

  return myIsFindSingleSolution && std::abs(myF - myFunctionalMinimalValue) < mySameTol * 0.01;
}

void math_GlobOptMin::ComputeInitSol()
{
  double      aVal;
  math_Vector aPnt(1, myN);

  aPnt = (myGlobA + myGlobB) * 0.5;
  myFunc->Value(aPnt, aVal);
  checkAddCandidate(aPnt, aVal);

  for (int i = 1; i <= 3; i++)
  {
    aPnt = myA + (myB - myA) * (i - 1) / 2.0;

    if (computeLocalExtremum(aPnt, aVal, aPnt))
      checkAddCandidate(aPnt, aVal);
  }
}

void math_GlobOptMin::checkAddCandidate(const math_Vector& thePnt, const double theValue)
{
  if (std::abs(theValue - myF) < mySameTol * 0.01 && !myIsFindSingleSolution)
  {
    if (!isStored(thePnt))
    {
      if ((theValue - myF) * myZ > 0.0)
        myF = theValue;
      for (int j = 1; j <= myN; j++)
        myY.Append(thePnt(j));
      mySolCount++;
    }
  }

  double aDelta = (theValue - myF) * myZ;
  if (aDelta > mySameTol * 0.01 || (aDelta > 0.0 && myIsFindSingleSolution))
  {
    myF = theValue;
    myY.Clear();
    for (int j = 1; j <= myN; j++)
      myY.Append(thePnt(j));
    mySolCount = 1;

    isFirstCellFilterInvoke = true;
  }
}
