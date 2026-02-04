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

class TopOpeBRepDS_PointIterator : public TopOpeBRepDS_InterferenceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an iterator on the points on curves
  //! described by the interferences in <L>.
  Standard_EXPORT TopOpeBRepDS_PointIterator(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  //! Returns True if the Interference <I> has a
  //! GeometryType() TopOpeBRepDS_POINT or TopOpeBRepDS_VERTEX
  //! returns False else.
  Standard_EXPORT bool MatchInterference(
    const occ::handle<TopOpeBRepDS_Interference>& I) const override;

  //! Index of the point in the data structure.
  Standard_EXPORT int Current() const;

  Standard_EXPORT TopAbs_Orientation Orientation(const TopAbs_State S) const;

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT bool IsVertex() const;

  Standard_EXPORT bool IsPoint() const;

  Standard_EXPORT bool DiffOriented() const;

  Standard_EXPORT bool SameOriented() const;

  Standard_EXPORT int Support() const;
};

