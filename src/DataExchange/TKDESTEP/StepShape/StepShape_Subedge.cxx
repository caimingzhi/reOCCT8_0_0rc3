#include <StepShape_Subedge.hpp>
#include <StepShape_Vertex.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Subedge, StepShape_Edge)

StepShape_Subedge::StepShape_Subedge() = default;

void StepShape_Subedge::Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                             const occ::handle<StepShape_Vertex>&         aEdge_EdgeStart,
                             const occ::handle<StepShape_Vertex>&         aEdge_EdgeEnd,
                             const occ::handle<StepShape_Edge>&           aParentEdge)
{
  StepShape_Edge::Init(aRepresentationItem_Name, aEdge_EdgeStart, aEdge_EdgeEnd);

  theParentEdge = aParentEdge;
}

occ::handle<StepShape_Edge> StepShape_Subedge::ParentEdge() const
{
  return theParentEdge;
}

void StepShape_Subedge::SetParentEdge(const occ::handle<StepShape_Edge>& aParentEdge)
{
  theParentEdge = aParentEdge;
}
