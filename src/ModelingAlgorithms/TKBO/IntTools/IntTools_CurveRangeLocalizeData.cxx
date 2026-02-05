#include <IntTools_CurveRangeLocalizeData.hpp>
#include <IntTools_CurveRangeSample.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>

IntTools_CurveRangeLocalizeData::IntTools_CurveRangeLocalizeData(const int    theNbSample,
                                                                 const double theMinRange)
{
  myNbSampleC = theNbSample;
  myMinRangeC = theMinRange;
}

void IntTools_CurveRangeLocalizeData::AddOutRange(const IntTools_CurveRangeSample& theRange)
{
  myMapRangeOut.Add(theRange);
  myMapBox.UnBind(theRange);
}

void IntTools_CurveRangeLocalizeData::AddBox(const IntTools_CurveRangeSample& theRange,
                                             const Bnd_Box&                   theBox)
{
  myMapBox.Bind(theRange, theBox);
}

bool IntTools_CurveRangeLocalizeData::FindBox(const IntTools_CurveRangeSample& theRange,
                                              Bnd_Box&                         theBox) const
{
  if (myMapBox.IsBound(theRange))
  {
    theBox = myMapBox(theRange);
    return true;
  }
  return false;
}

bool IntTools_CurveRangeLocalizeData::IsRangeOut(const IntTools_CurveRangeSample& theRange) const
{
  return myMapRangeOut.Contains(theRange);
}

void IntTools_CurveRangeLocalizeData::ListRangeOut(
  NCollection_List<IntTools_CurveRangeSample>& theList) const
{
  NCollection_Map<IntTools_CurveRangeSample>::Iterator anIt(myMapRangeOut);

  for (; anIt.More(); anIt.Next())
    theList.Append(anIt.Key());
}
