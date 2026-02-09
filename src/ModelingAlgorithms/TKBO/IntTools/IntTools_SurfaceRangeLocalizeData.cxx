#include <Bnd_Box.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_List.hpp>
#include <IntTools_SurfaceRangeLocalizeData.hpp>
#include <IntTools_SurfaceRangeSample.hpp>
#include <Precision.hpp>

IntTools_SurfaceRangeLocalizeData::IntTools_SurfaceRangeLocalizeData()
{
  myNbSampleU = 1;
  myNbSampleV = 1;
  myMinRangeU = 0.;
  myMinRangeV = 0.;

  myDeflection = 0.;
  myUIndMin    = 0;
  myUIndMax    = 0;
  myVIndMin    = 0;
  myVIndMax    = 0;
}

IntTools_SurfaceRangeLocalizeData::IntTools_SurfaceRangeLocalizeData(const int    theNbSampleU,
                                                                     const int    theNbSampleV,
                                                                     const double theMinRangeU,
                                                                     const double theMinRangeV)
{
  myNbSampleU = theNbSampleU;
  myNbSampleV = theNbSampleV;
  myMinRangeU = theMinRangeU;
  myMinRangeV = theMinRangeV;

  myDeflection = 0.;
  myUIndMin    = 0;
  myUIndMax    = 0;
  myVIndMin    = 0;
  myVIndMax    = 0;
}

IntTools_SurfaceRangeLocalizeData::IntTools_SurfaceRangeLocalizeData(
  const IntTools_SurfaceRangeLocalizeData& Other)
{
  Assign(Other);
}

IntTools_SurfaceRangeLocalizeData& IntTools_SurfaceRangeLocalizeData::Assign(
  const IntTools_SurfaceRangeLocalizeData& Other)
{
  myNbSampleU = Other.myNbSampleU;
  myNbSampleV = Other.myNbSampleV;
  myMinRangeU = Other.myMinRangeU;
  myMinRangeV = Other.myMinRangeV;
  myMapRangeOut.Clear();
  myMapRangeOut = Other.myMapRangeOut;
  myMapBox.Clear();
  myMapBox = Other.myMapBox;

  myDeflection = Other.myDeflection;
  myUIndMin    = Other.myUIndMin;
  myUIndMax    = Other.myUIndMax;
  myVIndMin    = Other.myVIndMin;
  myVIndMax    = Other.myVIndMax;

  if (!Other.myUParams.IsNull())
    myUParams = Other.myUParams;

  if (!Other.myVParams.IsNull())
    myVParams = Other.myVParams;

  if (!Other.myGridPoints.IsNull())
    myGridPoints = Other.myGridPoints;

  return *(this);
}

void IntTools_SurfaceRangeLocalizeData::AddOutRange(const IntTools_SurfaceRangeSample& theRange)
{
  myMapRangeOut.Add(theRange);
}

void IntTools_SurfaceRangeLocalizeData::AddBox(const IntTools_SurfaceRangeSample& theRange,
                                               const Bnd_Box&                     theBox)
{
  myMapBox.Bind(theRange, theBox);
}

bool IntTools_SurfaceRangeLocalizeData::FindBox(const IntTools_SurfaceRangeSample& theRange,
                                                Bnd_Box&                           theBox) const
{
  const Bnd_Box* aBoxPtr = myMapBox.Seek(theRange);
  if (aBoxPtr)
  {
    theBox = *aBoxPtr;
    return true;
  }
  return false;
}

bool IntTools_SurfaceRangeLocalizeData::IsRangeOut(
  const IntTools_SurfaceRangeSample& theRange) const
{
  return myMapRangeOut.Contains(theRange);
}

void IntTools_SurfaceRangeLocalizeData::ListRangeOut(
  NCollection_List<IntTools_SurfaceRangeSample>& theList) const
{
  NCollection_Map<IntTools_SurfaceRangeSample>::Iterator anIt(myMapRangeOut);

  for (; anIt.More(); anIt.Next())
    theList.Append(anIt.Key());
}

void IntTools_SurfaceRangeLocalizeData::RemoveRangeOutAll()
{
  myMapRangeOut.Clear();
}

void IntTools_SurfaceRangeLocalizeData::SetRangeUGrid(const int theNbUGrid)
{
  myUIndMin = 0;
  myUIndMax = 0;
  myVIndMin = 0;
  myVIndMax = 0;

  if (myUParams.IsNull() || theNbUGrid != myUParams->Length())
  {
    myUParams = new NCollection_HArray1<double>(1, theNbUGrid);

    if (!myVParams.IsNull())
    {
      myGridPoints = new NCollection_HArray2<gp_Pnt>(1, theNbUGrid, 1, myVParams->Length());
    }
  }
}

void IntTools_SurfaceRangeLocalizeData::SetRangeVGrid(const int theNbVGrid)
{
  myUIndMin = 0;
  myUIndMax = 0;
  myVIndMin = 0;
  myVIndMax = 0;

  if (myVParams.IsNull() || theNbVGrid != myVParams->Length())
  {
    myVParams = new NCollection_HArray1<double>(1, theNbVGrid);

    if (!myUParams.IsNull())
    {
      myGridPoints = new NCollection_HArray2<gp_Pnt>(1, myUParams->Length(), 1, theNbVGrid);
    }
  }
}

void IntTools_SurfaceRangeLocalizeData::SetFrame(const double theUMin,
                                                 const double theUMax,
                                                 const double theVMin,
                                                 const double theVMax)
{
  myUIndMin = 0;
  myUIndMax = 0;
  myVIndMin = 0;
  myVIndMax = 0;

  if (myUParams.IsNull() || myVParams.IsNull())
  {
    return;
  }

  int i;
  int aLmI;
  int aLen = myUParams->Length();

  for (i = 1; i <= aLen; i++)
  {
    if (myUIndMin == 0 && theUMin < myUParams->Value(i))
      myUIndMin = i;

    aLmI = aLen - i + 1;

    if (myUIndMax == 0 && theUMax > myUParams->Value(aLmI))
      myUIndMax = aLmI;
  }

  if (myUIndMin == 0)
    myUIndMin = aLen + 1;

  aLen = myVParams->Length();

  for (i = 1; i <= aLen; i++)
  {
    if (myVIndMin == 0 && theVMin < myVParams->Value(i))
      myVIndMin = i;

    aLmI = aLen - i + 1;

    if (myVIndMax == 0 && theVMax > myVParams->Value(aLmI))
      myVIndMax = aLmI;
  }

  if (myVIndMin == 0)
    myVIndMin = aLen + 1;
}

const gp_Pnt& IntTools_SurfaceRangeLocalizeData::GetPointInFrame(const int theUIndex,
                                                                 const int theVIndex) const
{
  int aFrmUInd = theUIndex + myUIndMin - 1;
  int aFrmVInd = theVIndex + myVIndMin - 1;

  if (myGridPoints.IsNull() || aFrmUInd > myUIndMax || aFrmVInd > myVIndMax)
    return gp::Origin();

  return myGridPoints->Value(aFrmUInd, aFrmVInd);
}

double IntTools_SurfaceRangeLocalizeData::GetUParamInFrame(const int theIndex) const
{
  int aFrmInd = theIndex + myUIndMin - 1;

  if (myUParams.IsNull() || aFrmInd > myUIndMax)
    return Precision::Infinite();

  return myUParams->Value(aFrmInd);
}

double IntTools_SurfaceRangeLocalizeData::GetVParamInFrame(const int theIndex) const
{
  int aFrmInd = theIndex + myVIndMin - 1;

  if (myVParams.IsNull() || aFrmInd > myVIndMax)
    return Precision::Infinite();

  return myVParams->Value(aFrmInd);
}

void IntTools_SurfaceRangeLocalizeData::ClearGrid()
{
  myDeflection = 0.;
  myUIndMin    = 0;
  myUIndMax    = 0;
  myVIndMin    = 0;
  myVIndMax    = 0;

  if (!myUParams.IsNull())
    myUParams.Nullify();

  if (!myVParams.IsNull())
    myVParams.Nullify();

  if (!myGridPoints.IsNull())
    myGridPoints.Nullify();
}
