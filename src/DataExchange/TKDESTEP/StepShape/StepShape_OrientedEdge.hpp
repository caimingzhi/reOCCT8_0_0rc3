#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepShape_Edge.hpp>
class TCollection_HAsciiString;
class StepShape_Vertex;

class StepShape_OrientedEdge : public StepShape_Edge
{

public:
  Standard_EXPORT StepShape_OrientedEdge();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_Edge>&           aEdgeElement,
                            const bool                                   aOrientation);

  Standard_EXPORT void SetEdgeElement(const occ::handle<StepShape_Edge>& aEdgeElement);

  Standard_EXPORT occ::handle<StepShape_Edge> EdgeElement() const;

  Standard_EXPORT void SetOrientation(const bool aOrientation);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetEdgeStart(const occ::handle<StepShape_Vertex>& aEdgeStart) override;

  Standard_EXPORT occ::handle<StepShape_Vertex> EdgeStart() const override;

  Standard_EXPORT void SetEdgeEnd(const occ::handle<StepShape_Vertex>& aEdgeEnd) override;

  Standard_EXPORT occ::handle<StepShape_Vertex> EdgeEnd() const override;

  DEFINE_STANDARD_RTTIEXT(StepShape_OrientedEdge, StepShape_Edge)

private:
  occ::handle<StepShape_Edge> edgeElement;
  bool                        orientation;
};
