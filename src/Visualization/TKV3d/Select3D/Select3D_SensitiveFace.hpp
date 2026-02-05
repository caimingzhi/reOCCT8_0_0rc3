#pragma once

#include <Select3D_TypeOfSensitivity.hpp>
#include <Select3D_SensitiveSet.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <SelectBasics_SelectingVolumeManager.hpp>

//! Sensitive Entity to make a face selectable.
//! In some cases this class can raise Standard_ConstructionError and
//! Standard_OutOfRange exceptions. For more details see Select3D_SensitivePoly.
class Select3D_SensitiveFace : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveFace, Select3D_SensitiveEntity)
public:
  //! Constructs a sensitive face object defined by the
  //! owner theOwnerId, the array of points thePoints, and
  //! the sensitivity type theType.
  //! The array of points is the outer polygon of the geometric face.
  Standard_EXPORT Select3D_SensitiveFace(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const NCollection_Array1<gp_Pnt>&         thePoints,
                                         const Select3D_TypeOfSensitivity          theType);

  //! Constructs a sensitive face object defined by the
  //! owner theOwnerId, the array of points thePoints, and
  //! the sensitivity type theType.
  //! The array of points is the outer polygon of the geometric face.
  Standard_EXPORT Select3D_SensitiveFace(const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
                                         const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints,
                                         const Select3D_TypeOfSensitivity                theType);

  //! Initializes the given array theHArrayOfPnt by 3d
  //! coordinates of vertices of the face
  Standard_EXPORT void GetPoints(occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt);

  //! Checks whether the face overlaps current selecting volume
  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  //! Returns bounding box of the face. If location transformation
  //! is set, it will be applied
  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  //! Returns center of the face. If location transformation
  //! is set, it will be applied
  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  //! Builds BVH tree for the face
  Standard_EXPORT void BVH() override;

  //! Returns TRUE if BVH tree is in invalidated state
  bool ToBuildBVH() const override { return myFacePoints->ToBuildBVH(); }

  //! Returns the amount of sub-entities (points or planar convex polygons)
  Standard_EXPORT int NbSubElements() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  Select3D_TypeOfSensitivity mySensType; //!< Type of sensitivity: interior or boundary
  // clang-format off
  occ::handle<Select3D_SensitiveSet> myFacePoints;     //!< Wrapper for overlap detection created depending on sensitivity type
  // clang-format on
};
