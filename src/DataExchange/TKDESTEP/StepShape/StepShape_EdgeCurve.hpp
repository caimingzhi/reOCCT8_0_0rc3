#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Edge.hpp>
class StepGeom_Curve;
class TCollection_HAsciiString;
class StepShape_Vertex;

class StepShape_EdgeCurve : public StepShape_Edge
{

public:
  //! Returns a EdgeCurve
  Standard_EXPORT StepShape_EdgeCurve();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_Vertex>&         aEdgeStart,
                            const occ::handle<StepShape_Vertex>&         aEdgeEnd,
                            const occ::handle<StepGeom_Curve>&           aEdgeGeometry,
                            const bool                                   aSameSense);

  Standard_EXPORT void SetEdgeGeometry(const occ::handle<StepGeom_Curve>& aEdgeGeometry);

  Standard_EXPORT occ::handle<StepGeom_Curve> EdgeGeometry() const;

  Standard_EXPORT void SetSameSense(const bool aSameSense);

  Standard_EXPORT bool SameSense() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_EdgeCurve, StepShape_Edge)

private:
  occ::handle<StepGeom_Curve> edgeGeometry;
  bool                        sameSense;
};

