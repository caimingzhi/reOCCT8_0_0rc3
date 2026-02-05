#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRAlgo_Interference.hpp>

#include <NCollection_List.hpp>
#include <HLRBRep_EdgeInterferenceTool.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>
class HLRAlgo_Intersection;

class HLRBRep_VertexList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_VertexList(const HLRBRep_EdgeInterferenceTool&                     T,
                                     const NCollection_List<HLRAlgo_Interference>::Iterator& I);

  //! Returns True when the curve is periodic.
  Standard_EXPORT bool IsPeriodic() const;

  //! Returns True when there are more vertices.
  Standard_EXPORT bool More() const;

  //! Proceeds to the next vertex.
  Standard_EXPORT void Next();

  //! Returns the current vertex
  Standard_EXPORT const HLRAlgo_Intersection& Current() const;

  //! Returns True if the current vertex is on the boundary of the edge.
  Standard_EXPORT bool IsBoundary() const;

  //! Returns True if the current vertex is an
  //! interference.
  Standard_EXPORT bool IsInterference() const;

  //! Returns the orientation of the current vertex if
  //! it is on the boundary of the edge.
  Standard_EXPORT TopAbs_Orientation Orientation() const;

  //! Returns the transition of the current vertex if
  //! it is an interference.
  Standard_EXPORT TopAbs_Orientation Transition() const;

  //! Returns the transition of the current vertex
  //! relative to the boundary if it is an interference.
  Standard_EXPORT TopAbs_Orientation BoundaryTransition() const;

private:
  NCollection_List<HLRAlgo_Interference>::Iterator myIterator;
  HLRBRep_EdgeInterferenceTool                     myTool;
  bool                                             fromEdge;
  bool                                             fromInterf;
};
