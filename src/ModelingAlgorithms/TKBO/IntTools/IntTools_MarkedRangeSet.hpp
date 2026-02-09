#pragma once

#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

class IntTools_Range;

class IntTools_MarkedRangeSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_MarkedRangeSet();

  Standard_EXPORT IntTools_MarkedRangeSet(const double theFirstBoundary,
                                          const double theLastBoundary,
                                          const int    theInitFlag);

  Standard_EXPORT IntTools_MarkedRangeSet(const NCollection_Array1<double>& theSortedArray,
                                          const int                         theInitFlag);

  Standard_EXPORT void SetBoundaries(const double theFirstBoundary,
                                     const double theLastBoundary,
                                     const int    theInitFlag);

  Standard_EXPORT void SetRanges(const NCollection_Array1<double>& theSortedArray,
                                 const int                         theInitFlag);

  Standard_EXPORT bool InsertRange(const double theFirstBoundary,
                                   const double theLastBoundary,
                                   const int    theFlag);

  Standard_EXPORT bool InsertRange(const IntTools_Range& theRange, const int theFlag);

  Standard_EXPORT bool InsertRange(const double theFirstBoundary,
                                   const double theLastBoundary,
                                   const int    theFlag,
                                   const int    theIndex);

  Standard_EXPORT bool InsertRange(const IntTools_Range& theRange,
                                   const int             theFlag,
                                   const int             theIndex);

  Standard_EXPORT void SetFlag(const int theIndex, const int theFlag);

  Standard_EXPORT int Flag(const int theIndex) const;

  Standard_EXPORT int GetIndex(const double theValue) const;

  Standard_EXPORT const NCollection_Sequence<int>& GetIndices(const double theValue);

  Standard_EXPORT int GetIndex(const double theValue, const bool UseLower) const;

  int Length() const { return myRangeNumber; }

  Standard_EXPORT IntTools_Range Range(const int theIndex) const;

private:
  NCollection_Sequence<double> myRangeSetStorer;
  int                          myRangeNumber;
  NCollection_Sequence<int>    myFlags;
  NCollection_Sequence<int>    myFoundIndices;
};
