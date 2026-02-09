#include <StepShape_ConnectedEdgeSet.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ConnectedEdgeSet, StepShape_TopologicalRepresentationItem)

StepShape_ConnectedEdgeSet::StepShape_ConnectedEdgeSet() = default;

void StepShape_ConnectedEdgeSet::Init(
  const occ::handle<TCollection_HAsciiString>&                         aRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_Edge>>>& aCesEdges)
{
  StepShape_TopologicalRepresentationItem::Init(aRepresentationItem_Name);

  theCesEdges = aCesEdges;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_Edge>>> StepShape_ConnectedEdgeSet::CesEdges()
  const
{
  return theCesEdges;
}

void StepShape_ConnectedEdgeSet::SetCesEdges(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_Edge>>>& aCesEdges)
{
  theCesEdges = aCesEdges;
}
