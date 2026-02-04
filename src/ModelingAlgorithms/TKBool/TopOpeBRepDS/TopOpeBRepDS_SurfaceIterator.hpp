#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_InterferenceIterator.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>

class TopOpeBRepDS_SurfaceIterator : public TopOpeBRepDS_InterferenceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an iterator on the Surfaces on solid
  //! described by the interferences in <L>.
  Standard_EXPORT TopOpeBRepDS_SurfaceIterator(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  //! Index of the surface in the data structure.
  Standard_EXPORT int Current() const;

  Standard_EXPORT TopAbs_Orientation Orientation(const TopAbs_State S) const;
};

