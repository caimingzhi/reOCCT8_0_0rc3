#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Vertex.hpp>
class StepGeom_Point;
class TCollection_HAsciiString;

class StepShape_VertexPoint : public StepShape_Vertex
{

public:
  //! Returns a VertexPoint
  Standard_EXPORT StepShape_VertexPoint();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Point>&           aVertexGeometry);

  Standard_EXPORT void SetVertexGeometry(const occ::handle<StepGeom_Point>& aVertexGeometry);

  Standard_EXPORT occ::handle<StepGeom_Point> VertexGeometry() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_VertexPoint, StepShape_Vertex)

private:
  occ::handle<StepGeom_Point> vertexGeometry;
};

