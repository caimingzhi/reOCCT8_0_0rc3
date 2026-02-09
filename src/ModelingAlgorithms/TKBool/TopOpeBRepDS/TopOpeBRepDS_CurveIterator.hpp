#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_InterferenceIterator.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepDS_Interference;
class Geom2d_Curve;

class TopOpeBRepDS_CurveIterator : public TopOpeBRepDS_InterferenceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_CurveIterator(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  Standard_EXPORT bool MatchInterference(
    const occ::handle<TopOpeBRepDS_Interference>& I) const override;

  Standard_EXPORT int Current() const;

  Standard_EXPORT TopAbs_Orientation Orientation(const TopAbs_State S) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve() const;
};
