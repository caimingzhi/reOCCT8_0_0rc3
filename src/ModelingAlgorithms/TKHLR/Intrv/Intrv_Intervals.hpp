#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intrv_Interval.hpp>
#include <NCollection_Sequence.hpp>
class Intrv_Interval;

//! The class Intervals is a sorted sequence of non
//! overlapping Real Intervals.
class Intrv_Intervals
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a void sequence of intervals.
  Standard_EXPORT Intrv_Intervals();

  //! Creates a sequence of one interval.
  Standard_EXPORT Intrv_Intervals(const Intrv_Interval& Int);

  //! Intersects the intervals with the interval <Tool>.
  Standard_EXPORT void Intersect(const Intrv_Interval& Tool);

  //! Intersects the intervals with the intervals in the
  //! sequence <Tool>.
  Standard_EXPORT void Intersect(const Intrv_Intervals& Tool);

  Standard_EXPORT void Subtract(const Intrv_Interval& Tool);

  Standard_EXPORT void Subtract(const Intrv_Intervals& Tool);

  Standard_EXPORT void Unite(const Intrv_Interval& Tool);

  Standard_EXPORT void Unite(const Intrv_Intervals& Tool);

  Standard_EXPORT void XUnite(const Intrv_Interval& Tool);

  Standard_EXPORT void XUnite(const Intrv_Intervals& Tool);

  int NbIntervals() const;

  const Intrv_Interval& Value(const int Index) const;

private:
  NCollection_Sequence<Intrv_Interval> myInter;
};

#include <Intrv_Interval.hpp>
#include <NCollection_Sequence.hpp>

//=======================================================================
// function : NbIntervals
// purpose  : returns the number of Intervals
//=======================================================================

inline int Intrv_Intervals::NbIntervals() const
{
  return myInter.Length();
}

//=======================================================================
// function : Value
// purpose  : returns the Interval of rank Index
//=======================================================================

inline const Intrv_Interval& Intrv_Intervals::Value(const int Index) const
{
  return myInter(Index);
}
