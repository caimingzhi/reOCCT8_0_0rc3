

#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_Face.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ConnectedFaceSet, StepShape_TopologicalRepresentationItem)

StepShape_ConnectedFaceSet::StepShape_ConnectedFaceSet() = default;

void StepShape_ConnectedFaceSet::Init(
  const occ::handle<TCollection_HAsciiString>&                         aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aCfsFaces)
{

  cfsFaces = aCfsFaces;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_ConnectedFaceSet::SetCfsFaces(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aCfsFaces)
{
  cfsFaces = aCfsFaces;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> StepShape_ConnectedFaceSet::CfsFaces()
  const
{
  return cfsFaces;
}

occ::handle<StepShape_Face> StepShape_ConnectedFaceSet::CfsFacesValue(const int num) const
{
  return cfsFaces->Value(num);
}

int StepShape_ConnectedFaceSet::NbCfsFaces() const
{
  if (cfsFaces.IsNull())
    return 0;
  return cfsFaces->Length();
}
