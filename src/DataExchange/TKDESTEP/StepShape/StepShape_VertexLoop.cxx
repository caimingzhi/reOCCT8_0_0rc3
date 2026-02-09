

#include <StepShape_Vertex.hpp>
#include <StepShape_VertexLoop.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_VertexLoop, StepShape_Loop)

StepShape_VertexLoop::StepShape_VertexLoop() = default;

void StepShape_VertexLoop::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                const occ::handle<StepShape_Vertex>&         aLoopVertex)
{

  loopVertex = aLoopVertex;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_VertexLoop::SetLoopVertex(const occ::handle<StepShape_Vertex>& aLoopVertex)
{
  loopVertex = aLoopVertex;
}

occ::handle<StepShape_Vertex> StepShape_VertexLoop::LoopVertex() const
{
  return loopVertex;
}
