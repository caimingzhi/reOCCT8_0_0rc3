#pragma once


#include <Select3D_SensitiveEntity.hpp>

//! A framework to define selection by a sensitive sphere.
class Select3D_SensitiveSphere : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveSphere, Select3D_SensitiveEntity)
public:
  //! Constructs a sensitive sphere object defined by the owner theOwnerId,
  //! the center of the sphere and it's radius.
  Standard_EXPORT Select3D_SensitiveSphere(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                           const gp_Pnt&                             theCenter,
                                           const double                              theRadius);

  //! Returns the radius of the sphere
  double Radius() const { return myRadius; }

public:
  //! Checks whether the sphere overlaps current selecting volume
  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  //! Returns the copy of this
  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  //! Returns bounding box of the sphere.
  //! If location transformation is set, it will be applied
  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  //! Always returns false
  bool ToBuildBVH() const override { return false; }

  //! Returns the amount of points
  int NbSubElements() const override { return 1; }

  //! Returns center of the sphere with transformation applied
  gp_Pnt CenterOfGeometry() const override { return myCenter; };

  //! Returns the position of detected point on the sphere.
  const gp_Pnt& LastDetectedPoint() const { return myLastDetectedPoint; }

  //! Invalidate the position of detected point on the sphere.
  void ResetLastDetectedPoint()
  {
    myLastDetectedPoint = gp_Pnt(RealLast(), RealLast(), RealLast());
  }

protected:
  gp_Pnt myCenter;
  gp_Pnt myLastDetectedPoint;
  double myRadius;
};

