#include <Select3D_SensitiveCylinder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveCylinder, Select3D_SensitiveEntity)

Select3D_SensitiveCylinder::Select3D_SensitiveCylinder(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
  const double                              theBottomRad,
  const double                              theTopRad,
  const double                              theHeight,
  const gp_Trsf&                            theTrsf,
  const bool                                theIsHollow)
    : Select3D_SensitiveEntity(theOwnerId),
      myTrsf(theTrsf),
      myBottomRadius(theBottomRad),
      myTopRadius(theTopRad),
      myHeight(theHeight),
      myIsHollow(theIsHollow)
{
}

bool Select3D_SensitiveCylinder::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                         SelectBasics_PickResult&             thePickResult)
{
  if (theMgr.GetActiveSelectionType() != SelectMgr_SelectionType_Point)
  {
    if (!theMgr.IsOverlapAllowed())
    {
      bool isInside = true;
      return theMgr.OverlapsCylinder(myBottomRadius,
                                     myTopRadius,
                                     myHeight,
                                     myTrsf,
                                     myIsHollow,
                                     &isInside)
             && isInside;
    }
    else
    {
      return theMgr
        .OverlapsCylinder(myBottomRadius, myTopRadius, myHeight, myTrsf, myIsHollow, nullptr);
    }
  }
  if (!theMgr.OverlapsCylinder(myBottomRadius,
                               myTopRadius,
                               myHeight,
                               myTrsf,
                               myIsHollow,
                               thePickResult))
  {
    return false;
  }

  thePickResult.SetDistToGeomCenter(theMgr.DistToGeometryCenter(CenterOfGeometry()));
  return true;
}

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveCylinder::GetConnected()
{
  occ::handle<Select3D_SensitiveEntity> aNewEntity =
    new Select3D_SensitiveCylinder(myOwnerId, myBottomRadius, myTopRadius, myHeight, myTrsf);
  return aNewEntity;
}

Select3D_BndBox3d Select3D_SensitiveCylinder::BoundingBox()
{
  double                   aMaxRad = std::max(myBottomRadius, myTopRadius);
  NCollection_Mat4<double> aTrsf;
  myTrsf.GetMat4(aTrsf);

  Select3D_BndBox3d aBox(NCollection_Vec3<double>(-aMaxRad, -aMaxRad, 0),
                         NCollection_Vec3<double>(aMaxRad, aMaxRad, myHeight));
  aBox.Transform(aTrsf);

  return aBox;
}

gp_Pnt Select3D_SensitiveCylinder::CenterOfGeometry() const
{
  return gp_Pnt(0, 0, myHeight / 2).Transformed(myTrsf);
}
