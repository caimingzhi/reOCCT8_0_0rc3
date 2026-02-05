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

  //! Creates an EdgeBuilder algorithm. <VList>
  //! describes the edge and the interferences.
  //! AreaLimits are created from the vertices.
  //! Builds(IN) is automatically called.
  Standard_EXPORT HLRBRep_EdgeBuilder(HLRBRep_VertexList& VList);

  //! Initialize an iteration on the areas.
  Standard_EXPORT void InitAreas();

  //! Set the current area to the next area.
  Standard_EXPORT void NextArea();

  //! Set the current area to the previous area.
  Standard_EXPORT void PreviousArea();

  //! Returns True if there is a current area.
  Standard_EXPORT bool HasArea() const;

  //! Returns the state of the current area.
  Standard_EXPORT TopAbs_State AreaState() const;

  //! Returns the edge state of the current area.
  Standard_EXPORT TopAbs_State AreaEdgeState() const;

  //! Returns the AreaLimit beginning the current area.
  //! This is a NULL handle when the area is infinite on
  //! the left.
  Standard_EXPORT occ::handle<HLRBRep_AreaLimit> LeftLimit() const;

  //! Returns the AreaLimit ending the current area.
  //! This is a NULL handle when the area is infinite on
  //! the right.
  Standard_EXPORT occ::handle<HLRBRep_AreaLimit> RightLimit() const;

  //! Reinitialize the results iteration to the parts
  //! with State <ToBuild>. If this method is not called
  //! after construction the default is <ToBuild> = IN.
  Standard_EXPORT void Builds(const TopAbs_State ToBuild);

  //! Returns True if there are more new edges to build.
  Standard_EXPORT bool MoreEdges() const;

  //! Proceeds to the next edge to build. Skip all
  //! remaining vertices on the current edge.
  Standard_EXPORT void NextEdge();

  //! True if there are more vertices in the current new
  //! edge.
  Standard_EXPORT bool MoreVertices() const;

  //! Proceeds to the next vertex of the current edge.
  Standard_EXPORT void NextVertex();

  //! Returns the current vertex of the current edge.
  Standard_EXPORT const HLRAlgo_Intersection& Current() const;

  //! Returns True if the current vertex comes from the
  //! boundary of the edge.
  Standard_EXPORT bool IsBoundary() const;

  //! Returns True if the current vertex was an
  //! interference.
  Standard_EXPORT bool IsInterference() const;

  //! Returns the new orientation of the current vertex.
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
