#include <Select3D_SensitivePoint.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitivePoint, Select3D_SensitiveEntity)

Select3D_SensitivePoint::Select3D_SensitivePoint(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                                 const gp_Pnt&                             thePoint)
    : Select3D_SensitiveEntity(theOwner)
{
  SetSensitivityFactor(12);
  myPoint = thePoint;
}

bool Select3D_SensitivePoint::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                      SelectBasics_PickResult&             thePickResult)
{
  if (!theMgr.OverlapsPoint(myPoint, thePickResult))
  {
    return false;
  }

  thePickResult.SetDistToGeomCenter(thePickResult.Depth());
  return true;
}

occ::handle<Select3D_SensitiveEntity> Select3D_SensitivePoint::GetConnected()
{
  occ::handle<Select3D_SensitivePoint> aNewEntity = new Select3D_SensitivePoint(myOwnerId, myPoint);
  return aNewEntity;
}

gp_Pnt Select3D_SensitivePoint::CenterOfGeometry() const
{
  return myPoint;
}

Select3D_BndBox3d Select3D_SensitivePoint::BoundingBox()
{
  return Select3D_BndBox3d(NCollection_Vec3<double>(myPoint.X(), myPoint.Y(), myPoint.Z()),
                           NCollection_Vec3<double>(myPoint.X(), myPoint.Y(), myPoint.Z()));
}

int Select3D_SensitivePoint::NbSubElements() const
{
  return 1;
}

void Select3D_SensitivePoint::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Select3D_SensitiveEntity)
}
