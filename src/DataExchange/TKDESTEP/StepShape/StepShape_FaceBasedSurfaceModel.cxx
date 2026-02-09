#include <StepShape_FaceBasedSurfaceModel.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_FaceBasedSurfaceModel, StepGeom_GeometricRepresentationItem)

StepShape_FaceBasedSurfaceModel::StepShape_FaceBasedSurfaceModel() = default;

void StepShape_FaceBasedSurfaceModel::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>& aFbsmFaces)
{
  StepGeom_GeometricRepresentationItem::Init(aRepresentationItem_Name);

  theFbsmFaces = aFbsmFaces;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>
  StepShape_FaceBasedSurfaceModel::FbsmFaces() const
{
  return theFbsmFaces;
}

void StepShape_FaceBasedSurfaceModel::SetFbsmFaces(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>& aFbsmFaces)
{
  theFbsmFaces = aFbsmFaces;
}
