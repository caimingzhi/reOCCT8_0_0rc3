

#include <StepGeom_Curve.hpp>
#include <StepShape_EdgeCurve.hpp>
#include <StepShape_Vertex.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_EdgeCurve, StepShape_Edge)

StepShape_EdgeCurve::StepShape_EdgeCurve() = default;

void StepShape_EdgeCurve::Init(const occ::handle<TCollection_HAsciiString>& aName,
                               const occ::handle<StepShape_Vertex>&         aEdgeStart,
                               const occ::handle<StepShape_Vertex>&         aEdgeEnd,
                               const occ::handle<StepGeom_Curve>&           aEdgeGeometry,
                               const bool                                   aSameSense)
{

  edgeGeometry = aEdgeGeometry;
  sameSense    = aSameSense;

  StepShape_Edge::Init(aName, aEdgeStart, aEdgeEnd);
}

void StepShape_EdgeCurve::SetEdgeGeometry(const occ::handle<StepGeom_Curve>& aEdgeGeometry)
{
  edgeGeometry = aEdgeGeometry;
}

occ::handle<StepGeom_Curve> StepShape_EdgeCurve::EdgeGeometry() const
{
  return edgeGeometry;
}

void StepShape_EdgeCurve::SetSameSense(const bool aSameSense)
{
  sameSense = aSameSense;
}

bool StepShape_EdgeCurve::SameSense() const
{
  return sameSense;
}
