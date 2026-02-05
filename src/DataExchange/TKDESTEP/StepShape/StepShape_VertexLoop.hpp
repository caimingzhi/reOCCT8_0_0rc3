#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Loop.hpp>
class StepShape_Vertex;
class TCollection_HAsciiString;

class StepShape_VertexLoop : public StepShape_Loop
{

public:
  //! Returns a VertexLoop
  Standard_EXPORT StepShape_VertexLoop();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_Vertex>&         aLoopVertex);

  Standard_EXPORT void SetLoopVertex(const occ::handle<StepShape_Vertex>& aLoopVertex);

  Standard_EXPORT occ::handle<StepShape_Vertex> LoopVertex() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_VertexLoop, StepShape_Loop)

private:
  occ::handle<StepShape_Vertex> loopVertex;
};
