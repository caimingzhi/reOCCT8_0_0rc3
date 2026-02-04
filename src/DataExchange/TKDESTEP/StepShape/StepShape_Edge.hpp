#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Vertex.hpp>

class TCollection_HAsciiString;

class StepShape_Edge : public StepShape_TopologicalRepresentationItem
{

public:
  //! Returns a Edge
  Standard_EXPORT StepShape_Edge();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_Vertex>&         aEdgeStart,
                            const occ::handle<StepShape_Vertex>&         aEdgeEnd);

  Standard_EXPORT virtual void SetEdgeStart(const occ::handle<StepShape_Vertex>& aEdgeStart);

  Standard_EXPORT virtual occ::handle<StepShape_Vertex> EdgeStart() const;

  Standard_EXPORT virtual void SetEdgeEnd(const occ::handle<StepShape_Vertex>& aEdgeEnd);

  Standard_EXPORT virtual occ::handle<StepShape_Vertex> EdgeEnd() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_Edge, StepShape_TopologicalRepresentationItem)

private:
  occ::handle<StepShape_Vertex> edgeStart;
  occ::handle<StepShape_Vertex> edgeEnd;
};

