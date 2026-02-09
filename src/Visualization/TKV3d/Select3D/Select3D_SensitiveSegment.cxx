#include <Select3D_SensitiveSegment.hpp>
#include <gp_Vec.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveSegment, Select3D_SensitiveEntity)

Select3D_SensitiveSegment::Select3D_SensitiveSegment(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
  const gp_Pnt&                             theFirstPnt,
  const gp_Pnt&                             theLastPnt)
    : Select3D_SensitiveEntity(theOwnerId)
{
  mySFactor = 3;
  myStart   = theFirstPnt;
  myEnd     = theLastPnt;
}

bool Select3D_SensitiveSegment::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                        SelectBasics_PickResult&             thePickResult)
{
  if (!theMgr.IsOverlapAllowed())
  {
    if (theMgr.GetActiveSelectionType() == SelectMgr_SelectionType_Polyline)
    {
      return theMgr.OverlapsSegment(myStart, myEnd, thePickResult);
    }
    return theMgr.OverlapsPoint(myStart, thePickResult)
           && theMgr.OverlapsPoint(myEnd, thePickResult);
  }

  if (!theMgr.OverlapsSegment(myStart, myEnd, thePickResult))
  {
    return false;
  }

  thePickResult.SetDistToGeomCenter(theMgr.DistToGeometryCenter(CenterOfGeometry()));
  return true;
}

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveSegment::GetConnected()
{
  occ::handle<Select3D_SensitiveSegment> aNewEntity =
    new Select3D_SensitiveSegment(myOwnerId, myStart, myEnd);

  return aNewEntity;
}

gp_Pnt Select3D_SensitiveSegment::CenterOfGeometry() const
{
  return (myStart.XYZ() + myEnd.XYZ()) * 0.5;
}

Select3D_BndBox3d Select3D_SensitiveSegment::BoundingBox()
{
  const NCollection_Vec3<double> aMinPnt(std::min(myStart.X(), myEnd.X()),
                                         std::min(myStart.Y(), myEnd.Y()),
                                         std::min(myStart.Z(), myEnd.Z()));
  const NCollection_Vec3<double> aMaxPnt(std::max(myStart.X(), myEnd.X()),
                                         std::max(myStart.Y(), myEnd.Y()),
                                         std::max(myStart.Z(), myEnd.Z()));
  return Select3D_BndBox3d(aMinPnt, aMaxPnt);
}

int Select3D_SensitiveSegment::NbSubElements() const
{
  return 2;
}

void Select3D_SensitiveSegment::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Select3D_SensitiveEntity)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myStart)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myEnd)

  Select3D_BndBox3d aBoundingBox = ((Select3D_SensitiveSegment*)this)->BoundingBox();
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &aBoundingBox)
}
