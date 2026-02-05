#include <StepShape_ConnectedFaceSubSet.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ConnectedFaceSubSet, StepShape_ConnectedFaceSet)

//=================================================================================================

StepShape_ConnectedFaceSubSet::StepShape_ConnectedFaceSubSet() = default;

//=================================================================================================

void StepShape_ConnectedFaceSubSet::Init(
  const occ::handle<TCollection_HAsciiString>&                         aRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aConnectedFaceSet_CfsFaces,
  const occ::handle<StepShape_ConnectedFaceSet>&                       aParentFaceSet)
{
  StepShape_ConnectedFaceSet::Init(aRepresentationItem_Name, aConnectedFaceSet_CfsFaces);

  theParentFaceSet = aParentFaceSet;
}

//=================================================================================================

occ::handle<StepShape_ConnectedFaceSet> StepShape_ConnectedFaceSubSet::ParentFaceSet() const
{
  return theParentFaceSet;
}

//=================================================================================================

void StepShape_ConnectedFaceSubSet::SetParentFaceSet(
  const occ::handle<StepShape_ConnectedFaceSet>& aParentFaceSet)
{
  theParentFaceSet = aParentFaceSet;
}
