#pragma once

#include <Select3D_SensitiveEntity.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>

//! A framework to define sensitive 3D points.
class Select3D_SensitivePoint : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitivePoint, Select3D_SensitiveEntity)
public:
  //! Constructs a sensitive point object defined by the
  //! owner OwnerId and the point Point.
  Standard_EXPORT Select3D_SensitivePoint(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                          const gp_Pnt&                             thePoint);

  //! Returns the amount of sub-entities in sensitive
  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  //! Checks whether the point overlaps current selecting volume
  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  //! Returns the point used at the time of construction.
  const gp_Pnt& Point() const { return myPoint; }

  //! Returns center of point. If location transformation
  //! is set, it will be applied
  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  //! Returns bounding box of the point. If location
  //! transformation is set, it will be applied
  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  //! Returns TRUE if BVH tree is in invalidated state
  bool ToBuildBVH() const override { return false; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  gp_Pnt myPoint; //!< 3d coordinates of the point
};
