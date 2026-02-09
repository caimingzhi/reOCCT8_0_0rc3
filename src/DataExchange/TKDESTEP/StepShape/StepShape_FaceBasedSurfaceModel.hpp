#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ConnectedFaceSet.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepShape_FaceBasedSurfaceModel : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepShape_FaceBasedSurfaceModel();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>& aFbsmFaces);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>
                  FbsmFaces() const;

  Standard_EXPORT void SetFbsmFaces(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>& FbsmFaces);

  DEFINE_STANDARD_RTTIEXT(StepShape_FaceBasedSurfaceModel, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>> theFbsmFaces;
};
