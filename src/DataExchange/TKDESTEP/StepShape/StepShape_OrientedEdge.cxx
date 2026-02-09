

#include <StepShape_OrientedEdge.hpp>
#include <StepShape_Vertex.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_OrientedEdge, StepShape_Edge)

StepShape_OrientedEdge::StepShape_OrientedEdge() = default;

void StepShape_OrientedEdge::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                  const occ::handle<StepShape_Edge>&           aEdgeElement,
                                  const bool                                   aOrientation)
{

  edgeElement = aEdgeElement;
  orientation = aOrientation;

  occ::handle<StepShape_Vertex> aEdgeStart;
  aEdgeStart.Nullify();
  occ::handle<StepShape_Vertex> aEdgeEnd;
  aEdgeEnd.Nullify();
  StepShape_Edge::Init(aName, aEdgeStart, aEdgeEnd);
}

void StepShape_OrientedEdge::SetEdgeElement(const occ::handle<StepShape_Edge>& aEdgeElement)
{
  edgeElement = aEdgeElement;
}

occ::handle<StepShape_Edge> StepShape_OrientedEdge::EdgeElement() const
{
  return edgeElement;
}

void StepShape_OrientedEdge::SetOrientation(const bool aOrientation)
{
  orientation = aOrientation;
}

bool StepShape_OrientedEdge::Orientation() const
{
  return orientation;
}

void StepShape_OrientedEdge::SetEdgeStart(const occ::handle<StepShape_Vertex>&)
{

  std::cout << "Field is redefined, SetUp Forbidden" << std::endl;
}

occ::handle<StepShape_Vertex> StepShape_OrientedEdge::EdgeStart() const
{

  if (edgeElement.IsNull())
    return nullptr;
  if (Orientation())
  {
    return edgeElement->EdgeStart();
  }
  else
  {
    return edgeElement->EdgeEnd();
  }
}

void StepShape_OrientedEdge::SetEdgeEnd(const occ::handle<StepShape_Vertex>&)
{

  std::cout << "Field is redefined, SetUp Forbidden" << std::endl;
}

occ::handle<StepShape_Vertex> StepShape_OrientedEdge::EdgeEnd() const
{

  if (edgeElement.IsNull())
    return nullptr;
  if (Orientation())
  {
    return edgeElement->EdgeEnd();
  }
  else
  {
    return edgeElement->EdgeStart();
  }
}
