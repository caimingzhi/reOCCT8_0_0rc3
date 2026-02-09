#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_State.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
class HLRBRep_AreaLimit;
class HLRBRep_VertexList;
class HLRAlgo_Intersection;

class HLRBRep_EdgeBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_EdgeBuilder(HLRBRep_VertexList& VList);

  Standard_EXPORT void InitAreas();

  Standard_EXPORT void NextArea();

  Standard_EXPORT void PreviousArea();

  Standard_EXPORT bool HasArea() const;

  Standard_EXPORT TopAbs_State AreaState() const;

  Standard_EXPORT TopAbs_State AreaEdgeState() const;

  Standard_EXPORT occ::handle<HLRBRep_AreaLimit> LeftLimit() const;

  Standard_EXPORT occ::handle<HLRBRep_AreaLimit> RightLimit() const;

  Standard_EXPORT void Builds(const TopAbs_State ToBuild);

  Standard_EXPORT bool MoreEdges() const;

  Standard_EXPORT void NextEdge();

  Standard_EXPORT bool MoreVertices() const;

  Standard_EXPORT void NextVertex();

  Standard_EXPORT const HLRAlgo_Intersection& Current() const;

  Standard_EXPORT bool IsBoundary() const;

  Standard_EXPORT bool IsInterference() const;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

  Standard_EXPORT void Destroy();

  ~HLRBRep_EdgeBuilder() { Destroy(); }

private:
  TopAbs_State                   toBuild;
  occ::handle<HLRBRep_AreaLimit> myLimits;
  occ::handle<HLRBRep_AreaLimit> left;
  occ::handle<HLRBRep_AreaLimit> right;
  int                            current;
};
