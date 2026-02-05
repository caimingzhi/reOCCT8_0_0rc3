#include <StepShape_EdgeBasedWireframeModel.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_EdgeBasedWireframeModel, StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepShape_EdgeBasedWireframeModel::StepShape_EdgeBasedWireframeModel() = default;

//=================================================================================================

void StepShape_EdgeBasedWireframeModel::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>>& aEbwmBoundary)
{
  StepGeom_GeometricRepresentationItem::Init(aRepresentationItem_Name);

  theEbwmBoundary = aEbwmBoundary;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>>
  StepShape_EdgeBasedWireframeModel::EbwmBoundary() const
{
  return theEbwmBoundary;
}

//=================================================================================================

void StepShape_EdgeBasedWireframeModel::SetEbwmBoundary(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>>& aEbwmBoundary)
{
  theEbwmBoundary = aEbwmBoundary;
}
