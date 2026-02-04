#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <IntTools_CurveRangeSample.hpp>
#include <NCollection_Map.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>

class IntTools_CurveRangeSample;
class Bnd_Box;

class IntTools_CurveRangeLocalizeData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_CurveRangeLocalizeData(const int theNbSample, const double theMinRange);

  int GetNbSample() const { return myNbSampleC; }

  double GetMinRange() const { return myMinRangeC; }

  Standard_EXPORT void AddOutRange(const IntTools_CurveRangeSample& theRange);

  Standard_EXPORT void AddBox(const IntTools_CurveRangeSample& theRange, const Bnd_Box& theBox);

  Standard_EXPORT bool FindBox(const IntTools_CurveRangeSample& theRange, Bnd_Box& theBox) const;

  Standard_EXPORT bool IsRangeOut(const IntTools_CurveRangeSample& theRange) const;

  Standard_EXPORT void ListRangeOut(NCollection_List<IntTools_CurveRangeSample>& theList) const;

private:
  int                                                     myNbSampleC;
  double                                                  myMinRangeC;
  NCollection_Map<IntTools_CurveRangeSample>              myMapRangeOut;
  NCollection_DataMap<IntTools_CurveRangeSample, Bnd_Box> myMapBox;
};

