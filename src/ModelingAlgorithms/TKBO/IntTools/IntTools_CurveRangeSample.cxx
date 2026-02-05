#include <IntTools_CurveRangeSample.hpp>
#include <IntTools_Range.hpp>

IntTools_CurveRangeSample::IntTools_CurveRangeSample()
{
  myIndex = 0;
}

IntTools_CurveRangeSample::IntTools_CurveRangeSample(const int theIndex)
{
  myIndex = theIndex;
}

IntTools_Range IntTools_CurveRangeSample::GetRange(const double theFirst,
                                                   const double theLast,
                                                   const int    theNbSample) const
{
  double         diffC = theLast - theFirst;
  IntTools_Range aResult;

  if (GetDepth() <= 0)
  {
    aResult.SetFirst(theFirst);
    aResult.SetLast(theLast);
  }
  else
  {
    double tmp        = pow(double(theNbSample), double(GetDepth()));
    double localdiffC = diffC / double(tmp);
    double aFirstC    = theFirst + double(myIndex) * localdiffC;
    double aLastC     = aFirstC + localdiffC;
    aResult.SetFirst(aFirstC);
    aResult.SetLast(aLastC);
  }
  return aResult;
}
