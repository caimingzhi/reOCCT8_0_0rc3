#include <IntTools_Range.hpp>
#include <IntTools_SurfaceRangeSample.hpp>

IntTools_SurfaceRangeSample::IntTools_SurfaceRangeSample() = default;

IntTools_SurfaceRangeSample::IntTools_SurfaceRangeSample(const int theIndexU,
                                                         const int theDepthU,
                                                         const int theIndexV,
                                                         const int theDepthV)
{
  myRangeU.SetRangeIndex(theIndexU);
  myRangeU.SetDepth(theDepthU);
  myRangeV.SetRangeIndex(theIndexV);
  myRangeV.SetDepth(theDepthV);
}

IntTools_SurfaceRangeSample::IntTools_SurfaceRangeSample(const IntTools_CurveRangeSample& theRangeU,
                                                         const IntTools_CurveRangeSample& theRangeV)
{
  myRangeU = theRangeU;
  myRangeV = theRangeV;
}

IntTools_SurfaceRangeSample::IntTools_SurfaceRangeSample(const IntTools_SurfaceRangeSample& Other)
{
  Assign(Other);
}

IntTools_SurfaceRangeSample& IntTools_SurfaceRangeSample::Assign(
  const IntTools_SurfaceRangeSample& Other)
{
  myRangeU = Other.myRangeU;
  myRangeV = Other.myRangeV;
  return (*this);
}

IntTools_Range IntTools_SurfaceRangeSample::GetRangeU(const double theFirstU,
                                                      const double theLastU,
                                                      const int    theNbSampleU) const
{
  return myRangeU.GetRange(theFirstU, theLastU, theNbSampleU);
}

IntTools_Range IntTools_SurfaceRangeSample::GetRangeV(const double theFirstV,
                                                      const double theLastV,
                                                      const int    theNbSampleV) const
{
  return myRangeV.GetRange(theFirstV, theLastV, theNbSampleV);
}
