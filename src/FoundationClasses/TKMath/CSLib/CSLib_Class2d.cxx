#include <CSLib_Class2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>

#include <cmath>

namespace
{

  inline double transformToNormalized(const double theU,
                                      const double theUMin,
                                      const double theURange)
  {
    constexpr double THE_MIN_RANGE = 1e-10;
    if (theURange > THE_MIN_RANGE)
    {
      return (theU - theUMin) / theURange;
    }
    return theU;
  }
} // namespace

template <class TCol_Containers2d>
void CSLib_Class2d::init(const TCol_Containers2d& thePnts2d,
                         const double             theTolU,
                         const double             theTolV,
                         const double             theUMin,
                         const double             theVMin,
                         const double             theUMax,
                         const double             theVMax)
{
  myUMin = theUMin;
  myVMin = theVMin;
  myUMax = theUMax;
  myVMax = theVMax;

  if (theUMax <= theUMin || theVMax <= theVMin || thePnts2d.Length() < 3)
  {
    myPointsCount = 0;
    return;
  }

  myPointsCount = thePnts2d.Length();
  myTolU        = theTolU;
  myTolV        = theTolV;

  myPnts2dX.Resize(0, myPointsCount, false);
  myPnts2dY.Resize(0, myPointsCount, false);

  const double aDu = theUMax - theUMin;
  const double aDv = theVMax - theVMin;

  const int aLower = thePnts2d.Lower();
  for (int i = 0; i < myPointsCount; ++i)
  {
    const gp_Pnt2d& aP2D     = thePnts2d(i + aLower);
    myPnts2dX.ChangeValue(i) = transformToNormalized(aP2D.X(), theUMin, aDu);
    myPnts2dY.ChangeValue(i) = transformToNormalized(aP2D.Y(), theVMin, aDv);
  }

  myPnts2dX.ChangeLast() = myPnts2dX.First();
  myPnts2dY.ChangeLast() = myPnts2dY.First();

  constexpr double THE_MIN_RANGE = 1e-10;
  if (aDu > THE_MIN_RANGE)
  {
    myTolU /= aDu;
  }
  if (aDv > THE_MIN_RANGE)
  {
    myTolV /= aDv;
  }
}

CSLib_Class2d::CSLib_Class2d(const NCollection_Array1<gp_Pnt2d>& thePnts2d,
                             const double                        theTolU,
                             const double                        theTolV,
                             const double                        theUMin,
                             const double                        theVMin,
                             const double                        theUMax,
                             const double                        theVMax)
{
  init(thePnts2d, theTolU, theTolV, theUMin, theVMin, theUMax, theVMax);
}

CSLib_Class2d::CSLib_Class2d(const NCollection_Sequence<gp_Pnt2d>& thePnts2d,
                             const double                          theTolU,
                             const double                          theTolV,
                             const double                          theUMin,
                             const double                          theVMin,
                             const double                          theUMax,
                             const double                          theVMax)
{
  init(thePnts2d, theTolU, theTolV, theUMin, theVMin, theUMax, theVMax);
}

CSLib_Class2d::Result CSLib_Class2d::SiDans(const gp_Pnt2d& thePoint) const
{
  if (myPointsCount == 0)
  {
    return Result_Uncertain;
  }

  double aX = thePoint.X();
  double aY = thePoint.Y();

  const double aTolU = myTolU * (myUMax - myUMin);
  const double aTolV = myTolV * (myVMax - myVMin);

  if (aX < (myUMin - aTolU) || aX > (myUMax + aTolU) || aY < (myVMin - aTolV)
      || aY > (myVMax + aTolV))
  {
    return Result_Outside;
  }

  aX = transformToNormalized(aX, myUMin, myUMax - myUMin);
  aY = transformToNormalized(aY, myVMin, myVMax - myVMin);

  const Result aResult = internalSiDansOuOn(aX, aY);
  if (aResult == Result_Uncertain)
  {
    return Result_Uncertain;
  }

  if (myTolU > 0.0 || myTolV > 0.0)
  {
    const bool isInside = (aResult == Result_Inside);
    if (isInside != internalSiDans(aX - myTolU, aY - myTolV)
        || isInside != internalSiDans(aX + myTolU, aY - myTolV)
        || isInside != internalSiDans(aX - myTolU, aY + myTolV)
        || isInside != internalSiDans(aX + myTolU, aY + myTolV))
    {
      return Result_Uncertain;
    }
  }

  return aResult;
}

CSLib_Class2d::Result CSLib_Class2d::SiDans_OnMode(const gp_Pnt2d& thePoint,
                                                   const double    theTol) const
{
  if (myPointsCount == 0)
  {
    return Result_Uncertain;
  }

  double aX = thePoint.X();
  double aY = thePoint.Y();

  if (aX < (myUMin - theTol) || aX > (myUMax + theTol) || aY < (myVMin - theTol)
      || aY > (myVMax + theTol))
  {
    return Result_Outside;
  }

  aX = transformToNormalized(aX, myUMin, myUMax - myUMin);
  aY = transformToNormalized(aY, myVMin, myVMax - myVMin);

  const Result aResult = internalSiDansOuOn(aX, aY);

  if (theTol > 0.0)
  {
    const bool isInside = (aResult == Result_Inside);
    if (isInside != internalSiDans(aX - theTol, aY - theTol)
        || isInside != internalSiDans(aX + theTol, aY - theTol)
        || isInside != internalSiDans(aX - theTol, aY + theTol)
        || isInside != internalSiDans(aX + theTol, aY + theTol))
    {
      return Result_Uncertain;
    }
  }

  return aResult;
}

bool CSLib_Class2d::internalSiDans(const double thePx, const double thePy) const
{

  int aNbCrossings = 0;

  double aPrevDx          = myPnts2dX.Value(0) - thePx;
  double aPrevDy          = myPnts2dY.Value(0) - thePy;
  bool   aPrevYIsNegative = (aPrevDy < 0.0);

  for (int aNextIdx = 1; aNextIdx <= myPointsCount; ++aNextIdx)
  {
    const double aCurrDx          = myPnts2dX.Value(aNextIdx) - thePx;
    const double aCurrDy          = myPnts2dY.Value(aNextIdx) - thePy;
    const bool   aCurrYIsNegative = (aCurrDy < 0.0);

    if (aCurrYIsNegative != aPrevYIsNegative)
    {
      if (aPrevDx > 0.0 && aCurrDx > 0.0)
      {

        ++aNbCrossings;
      }
      else if (aPrevDx > 0.0 || aCurrDx > 0.0)
      {

        const double aXIntersect = aPrevDx - aPrevDy * (aCurrDx - aPrevDx) / (aCurrDy - aPrevDy);
        if (aXIntersect > 0.0)
        {
          ++aNbCrossings;
        }
      }
      aPrevYIsNegative = aCurrYIsNegative;
    }

    aPrevDx = aCurrDx;
    aPrevDy = aCurrDy;
  }

  return (aNbCrossings & 1) != 0;
}

CSLib_Class2d::Result CSLib_Class2d::internalSiDansOuOn(const double thePx,
                                                        const double thePy) const
{

  int aNbCrossings = 0;

  double aPrevDx          = myPnts2dX.Value(0) - thePx;
  double aPrevDy          = myPnts2dY.Value(0) - thePy;
  bool   aPrevYIsNegative = (aPrevDy < 0.0);

  for (int aNextIdx = 1; aNextIdx <= myPointsCount; ++aNextIdx)
  {
    const int    aPrevIdx = aNextIdx - 1;
    const double aCurrDx  = myPnts2dX.Value(aNextIdx) - thePx;
    const double aCurrDy  = myPnts2dY.Value(aNextIdx) - thePy;

    if (aCurrDx < myTolU && aCurrDx > -myTolU && aCurrDy < myTolV && aCurrDy > -myTolV)
    {
      return Result_Uncertain;
    }

    const double aEdgeDx = myPnts2dX.Value(aNextIdx) - myPnts2dX.Value(aPrevIdx);
    if ((myPnts2dX.Value(aPrevIdx) - thePx) * aCurrDx < 0.0
        && std::abs(aEdgeDx) > Precision::PConfusion())
    {
      const double aInterpY =
        myPnts2dY.Value(aNextIdx)
        - (myPnts2dY.Value(aNextIdx) - myPnts2dY.Value(aPrevIdx)) / aEdgeDx * aCurrDx;
      const double aDeltaY = aInterpY - thePy;
      if (aDeltaY >= -myTolV && aDeltaY <= myTolV)
      {
        return Result_Uncertain;
      }
    }

    const bool aCurrYIsNegative = (aCurrDy < 0.0);
    if (aCurrYIsNegative != aPrevYIsNegative)
    {
      if (aPrevDx > 0.0 && aCurrDx > 0.0)
      {
        ++aNbCrossings;
      }
      else if (aPrevDx > 0.0 || aCurrDx > 0.0)
      {
        const double aXIntersect = aPrevDx - aPrevDy * (aCurrDx - aPrevDx) / (aCurrDy - aPrevDy);
        if (aXIntersect > 0.0)
        {
          ++aNbCrossings;
        }
      }
      aPrevYIsNegative = aCurrYIsNegative;
    }

    aPrevDx = aCurrDx;
    aPrevDy = aCurrDy;
  }

  return ((aNbCrossings & 1) != 0) ? Result_Inside : Result_Outside;
}
