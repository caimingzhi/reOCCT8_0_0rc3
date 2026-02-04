#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ConnectedFaceSet.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity FaceBasedSurfaceModel
class StepShape_FaceBasedSurfaceModel : public StepGeom_GeometricRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_FaceBasedSurfaceModel();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>& aFbsmFaces);

  //! Returns field FbsmFaces
  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>
                  FbsmFaces() const;

  //! Set field FbsmFaces
  Standard_EXPORT void SetFbsmFaces(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>>& FbsmFaces);

  DEFINE_STANDARD_RTTIEXT(StepShape_FaceBasedSurfaceModel, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>> theFbsmFaces;
};

