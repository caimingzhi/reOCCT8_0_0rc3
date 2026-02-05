#include <Select3D_SensitiveSphere.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveSphere, Select3D_SensitiveEntity)

//=================================================================================================

Select3D_SensitiveSphere::Select3D_SensitiveSphere(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
  const gp_Pnt&                             theCenter,
  const double                              theRadius)
    : Select3D_SensitiveEntity(theOwnerId),
      myCenter(theCenter),
      myLastDetectedPoint(RealLast(), RealLast(), RealLast()),
      myRadius(theRadius)
{
}

//=================================================================================================

bool Select3D_SensitiveSphere::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                       SelectBasics_PickResult&             thePickResult)
{
  myLastDetectedPoint = gp_Pnt(RealLast(), RealLast(), RealLast());
  if (theMgr.GetActiveSelectionType() != SelectMgr_SelectionType_Point)
  {
    if (!theMgr.IsOverlapAllowed())
    {
      bool isInside = true;
      return theMgr.OverlapsSphere(myCenter, myRadius, &isInside) && isInside;
    }
    else
    {
      return theMgr.OverlapsSphere(myCenter, myRadius, nullptr);
    }
  }
  if (!theMgr.OverlapsSphere(myCenter, myRadius, thePickResult))
  {
    return false;
  }
  myLastDetectedPoint = thePickResult.PickedPoint();
  thePickResult.SetDistToGeomCenter(theMgr.DistToGeometryCenter(myCenter));
  return true;
}

//=================================================================================================

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveSphere::GetConnected()
{
  occ::handle<Select3D_SensitiveEntity> aNewEntity =
    new Select3D_SensitiveSphere(myOwnerId, myCenter, myRadius);
  return aNewEntity;
}

//=================================================================================================

Select3D_BndBox3d Select3D_SensitiveSphere::BoundingBox()
{
  const NCollection_Vec3<double> aMinPnt = NCollection_Vec3<double>(myCenter.X() - myRadius,
                                                                    myCenter.Y() - myRadius,
                                                                    myCenter.Z() - myRadius);
  const NCollection_Vec3<double> aMaxPnt = NCollection_Vec3<double>(myCenter.X() + myRadius,
                                                                    myCenter.Y() + myRadius,
                                                                    myCenter.Z() + myRadius);
  return Select3D_BndBox3d(aMinPnt, aMaxPnt);
}
