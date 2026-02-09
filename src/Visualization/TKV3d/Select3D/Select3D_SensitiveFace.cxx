#include <Select3D_SensitiveFace.hpp>

#include <Select3D_InteriorSensitivePointSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveFace, Select3D_SensitiveEntity)

Select3D_SensitiveFace::Select3D_SensitiveFace(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                               const NCollection_Array1<gp_Pnt>&         thePoints,
                                               const Select3D_TypeOfSensitivity          theType)
    : Select3D_SensitiveEntity(theOwnerId),
      mySensType(theType)
{
  if (mySensType == Select3D_TOS_INTERIOR)
  {
    myFacePoints = new Select3D_InteriorSensitivePointSet(theOwnerId, thePoints);
  }
  else
  {
    myFacePoints = new Select3D_SensitivePoly(theOwnerId, thePoints, true);
  }
}

Select3D_SensitiveFace::Select3D_SensitiveFace(
  const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
  const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints,
  const Select3D_TypeOfSensitivity                theType)
    : Select3D_SensitiveEntity(theOwnerId),
      mySensType(theType)
{
  if (mySensType == Select3D_TOS_INTERIOR)
  {
    myFacePoints = new Select3D_InteriorSensitivePointSet(theOwnerId, thePoints->Array1());
  }
  else
  {
    myFacePoints = new Select3D_SensitivePoly(theOwnerId, thePoints->Array1(), true);
  }
}

void Select3D_SensitiveFace::GetPoints(occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt)
{
  if (myFacePoints->IsKind(STANDARD_TYPE(Select3D_SensitivePoly)))
  {
    occ::down_cast<Select3D_SensitivePoly>(myFacePoints)->Points3D(theHArrayOfPnt);
  }
  else
  {
    occ::down_cast<Select3D_InteriorSensitivePointSet>(myFacePoints)->GetPoints(theHArrayOfPnt);
  }
}

void Select3D_SensitiveFace::BVH()
{
  myFacePoints->BVH();
}

bool Select3D_SensitiveFace::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                     SelectBasics_PickResult&             thePickResult)
{
  return myFacePoints->Matches(theMgr, thePickResult);
}

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveFace::GetConnected()
{

  occ::handle<NCollection_HArray1<gp_Pnt>> aPoints;
  GetPoints(aPoints);

  occ::handle<Select3D_SensitiveEntity> aNewEntity =
    new Select3D_SensitiveFace(myOwnerId, aPoints, mySensType);

  return aNewEntity;
}

Select3D_BndBox3d Select3D_SensitiveFace::BoundingBox()
{
  return myFacePoints->BoundingBox();
}

gp_Pnt Select3D_SensitiveFace::CenterOfGeometry() const
{
  return myFacePoints->CenterOfGeometry();
}

int Select3D_SensitiveFace::NbSubElements() const
{
  return myFacePoints->NbSubElements();
}

void Select3D_SensitiveFace::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Select3D_SensitiveEntity)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySensType)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myFacePoints.get())
}
