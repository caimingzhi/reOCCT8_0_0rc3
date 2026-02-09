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

  Standard_EXPORT bool IsPeriodic() const;

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const HLRAlgo_Intersection& Current() const;

  Standard_EXPORT bool IsBoundary() const;

  Standard_EXPORT bool IsInterference() const;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

  Standard_EXPORT TopAbs_Orientation Transition() const;

  Standard_EXPORT TopAbs_Orientation BoundaryTransition() const;

private:
  NCollection_List<HLRAlgo_Interference>::Iterator myIterator;
  HLRBRep_EdgeInterferenceTool                     myTool;
  bool                                             fromEdge;
  bool                                             fromInterf;
};
