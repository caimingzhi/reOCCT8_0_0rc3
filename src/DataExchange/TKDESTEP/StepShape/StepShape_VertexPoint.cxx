

#include <StepGeom_Point.hpp>
#include <StepShape_VertexPoint.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_VertexPoint, StepShape_Vertex)

StepShape_VertexPoint::StepShape_VertexPoint() = default;

void StepShape_VertexPoint::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                 const occ::handle<StepGeom_Point>&           aVertexGeometry)
{

  vertexGeometry = aVertexGeometry;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_VertexPoint::SetVertexGeometry(const occ::handle<StepGeom_Point>& aVertexGeometry)
{
  vertexGeometry = aVertexGeometry;
}

occ::handle<StepGeom_Point> StepShape_VertexPoint::VertexGeometry() const
{
  return vertexGeometry;
}
