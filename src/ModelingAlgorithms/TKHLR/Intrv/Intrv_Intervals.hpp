#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intrv_Interval.hpp>
#include <NCollection_Sequence.hpp>
class Intrv_Interval;

class Intrv_Intervals
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Intrv_Intervals();

  Standard_EXPORT Intrv_Intervals(const Intrv_Interval& Int);

  Standard_EXPORT void Intersect(const Intrv_Interval& Tool);

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

inline int Intrv_Intervals::NbIntervals() const
{
  return myInter.Length();
}

inline const Intrv_Interval& Intrv_Intervals::Value(const int Index) const
{
  return myInter(Index);
}
