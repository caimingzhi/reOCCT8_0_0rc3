

#include <StepShape_Edge.hpp>
#include <StepShape_Vertex.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_Edge, StepShape_TopologicalRepresentationItem)

StepShape_Edge::StepShape_Edge() = default;

void StepShape_Edge::Init(const occ::handle<TCollection_HAsciiString>& aName,
                          const occ::handle<StepShape_Vertex>&         aEdgeStart,
                          const occ::handle<StepShape_Vertex>&         aEdgeEnd)
{

  edgeStart = aEdgeStart;
  edgeEnd   = aEdgeEnd;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_Edge::SetEdgeStart(const occ::handle<StepShape_Vertex>& aEdgeStart)
{
  edgeStart = aEdgeStart;
}

occ::handle<StepShape_Vertex> StepShape_Edge::EdgeStart() const
{
  return edgeStart;
}

void StepShape_Edge::SetEdgeEnd(const occ::handle<StepShape_Vertex>& aEdgeEnd)
{
  edgeEnd = aEdgeEnd;
}

occ::handle<StepShape_Vertex> StepShape_Edge::EdgeEnd() const
{
  return edgeEnd;
}
