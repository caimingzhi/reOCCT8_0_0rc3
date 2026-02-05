#include <StepGeom_Pcurve.hpp>
#include <StepShape_SeamEdge.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_SeamEdge, StepShape_OrientedEdge)

//=================================================================================================

StepShape_SeamEdge::StepShape_SeamEdge() = default;

//=================================================================================================

void StepShape_SeamEdge::Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                              const occ::handle<StepShape_Edge>&  aOrientedEdge_EdgeElement,
                              const bool                          aOrientedEdge_Orientation,
                              const occ::handle<StepGeom_Pcurve>& aPcurveReference)
{
  StepShape_OrientedEdge::Init(aRepresentationItem_Name,
                               aOrientedEdge_EdgeElement,
                               aOrientedEdge_Orientation);

  thePcurveReference = aPcurveReference;
}

//=================================================================================================

occ::handle<StepGeom_Pcurve> StepShape_SeamEdge::PcurveReference() const
{
  return thePcurveReference;
}

//=================================================================================================

void StepShape_SeamEdge::SetPcurveReference(const occ::handle<StepGeom_Pcurve>& aPcurveReference)
{
  thePcurveReference = aPcurveReference;
}
