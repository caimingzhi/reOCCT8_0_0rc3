#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntTools_BaseRangeSample.hpp>
#include <Standard_HashUtils.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

class IntTools_Range;

//! class for range index management of curve
class IntTools_CurveRangeSample : public IntTools_BaseRangeSample
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_CurveRangeSample();

  Standard_EXPORT IntTools_CurveRangeSample(const int theIndex);

  void SetRangeIndex(const int theIndex) { myIndex = theIndex; }

  int GetRangeIndex() const { return myIndex; }

  bool IsEqual(const IntTools_CurveRangeSample& Other) const
  {
    return ((myIndex == Other.myIndex) && (GetDepth() == Other.GetDepth()));
  }

  bool operator==(const IntTools_CurveRangeSample& Other) const { return IsEqual(Other); }

  Standard_EXPORT IntTools_Range GetRange(const double theFirst,
                                          const double theLast,
                                          const int    theNbSample) const;

  int GetRangeIndexDeeper(const int theNbSample) const { return myIndex * theNbSample; }

private:
  int myIndex;
};

namespace std
{
  template <>
  struct hash<IntTools_CurveRangeSample>
  {
    size_t operator()(const IntTools_CurveRangeSample& theCurveRangeSample) const noexcept
    {
      // Combine two int values into a single hash value.
      int aCombination[2]{theCurveRangeSample.GetDepth(), theCurveRangeSample.GetRangeIndex()};
      return opencascade::hashBytes(aCombination, sizeof(aCombination));
    }
  };
} // namespace std
