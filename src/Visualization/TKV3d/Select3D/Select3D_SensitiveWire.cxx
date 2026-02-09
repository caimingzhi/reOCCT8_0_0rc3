#include <Select3D_SensitiveWire.hpp>
#include <Select3D_SensitiveEntity.hpp>
#include <TopLoc_Location.hpp>

#include <Select3D_SensitiveSegment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveWire, Select3D_SensitiveSet)

Select3D_SensitiveWire::Select3D_SensitiveWire(const occ::handle<SelectMgr_EntityOwner>& theOwnerId)
    : Select3D_SensitiveSet(theOwnerId),
      myCenter(0.0, 0.0, 0.0)
{
}

void Select3D_SensitiveWire::Add(const occ::handle<Select3D_SensitiveEntity>& theSensitive)
{
  if (!theSensitive.IsNull())
    myEntities.Append(theSensitive);

  Select3D_BndBox3d aBndBox = theSensitive->BoundingBox();
  myBndBox.Combine(aBndBox);
  myCenter.ChangeCoord() += theSensitive->CenterOfGeometry().XYZ();
  if (myEntities.Length() != 1)
    myCenter.ChangeCoord().Divide(2.0);
  myEntityIndexes.Append(myEntities.Length() - 1);
}

int Select3D_SensitiveWire::NbSubElements() const
{
  return myEntities.Length();
}

int Select3D_SensitiveWire::Size() const
{
  return myEntities.Length();
}

Select3D_BndBox3d Select3D_SensitiveWire::Box(const int theIdx) const
{
  const int aSensitiveIdx = myEntityIndexes.Value(theIdx);
  return myEntities.Value(aSensitiveIdx)->BoundingBox();
}

double Select3D_SensitiveWire::Center(const int theIdx, const int theAxis) const
{
  const int     aSensitiveIdx = myEntityIndexes.Value(theIdx);
  const gp_Pnt& aCenter       = myEntities.Value(aSensitiveIdx)->CenterOfGeometry();
  double        aCenterCoord  = 0.0;
  aCenterCoord = theAxis == 0 ? aCenter.X() : (theAxis == 1 ? aCenter.Y() : aCenter.Z());

  return aCenterCoord;
}

void Select3D_SensitiveWire::Swap(const int theIdx1, const int theIdx2)
{
  const int aSensitiveIdx1             = myEntityIndexes.Value(theIdx1);
  const int aSensitiveIdx2             = myEntityIndexes.Value(theIdx2);
  myEntityIndexes.ChangeValue(theIdx1) = aSensitiveIdx2;
  myEntityIndexes.ChangeValue(theIdx2) = aSensitiveIdx1;
}

bool Select3D_SensitiveWire::overlapsElement(SelectBasics_PickResult&             thePickResult,
                                             SelectBasics_SelectingVolumeManager& theMgr,
                                             int                                  theElemIdx,
                                             bool)
{
  const int                                    aSensitiveIdx = myEntityIndexes.Value(theElemIdx);
  const occ::handle<Select3D_SensitiveEntity>& aSeg          = myEntities.Value(aSensitiveIdx);
  return aSeg->Matches(theMgr, thePickResult);
}

bool Select3D_SensitiveWire::elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                             int                                  theElemIdx,
                                             bool)
{
  SelectBasics_PickResult aMatchResult;
  return myEntities.Value(myEntityIndexes.Value(theElemIdx))->Matches(theMgr, aMatchResult);
}

double Select3D_SensitiveWire::distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr)
{
  return theMgr.DistToGeometryCenter(myCenter);
}

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveWire::GetConnected()
{
  occ::handle<Select3D_SensitiveWire> aNewEntity = new Select3D_SensitiveWire(myOwnerId);
  for (int anEntityIdx = 0; anEntityIdx < myEntities.Length(); anEntityIdx++)
    aNewEntity->Add(myEntities(anEntityIdx)->GetConnected());

  return aNewEntity;
}

const NCollection_Vector<occ::handle<Select3D_SensitiveEntity>>& Select3D_SensitiveWire::GetEdges()
{
  return myEntities;
}

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveWire::GetLastDetected() const
{
  occ::handle<Select3D_SensitiveEntity> aRes;

  if (myDetectedIdx >= 0 && myDetectedIdx < myEntities.Length())
  {
    const int aSensitiveIdx = myEntityIndexes.Value(myDetectedIdx);
    aRes                    = myEntities.Value(aSensitiveIdx);
  }

  return aRes;
}

void Select3D_SensitiveWire::Set(const occ::handle<SelectMgr_EntityOwner>& theOwnerId)
{
  Select3D_SensitiveEntity::Set(theOwnerId);

  for (int anEntityIdx = 0; anEntityIdx < myEntities.Length(); ++anEntityIdx)
  {
    myEntities.Value(anEntityIdx)->Set(theOwnerId);
  }
}

Select3D_BndBox3d Select3D_SensitiveWire::BoundingBox()
{
  if (myBndBox.IsValid())
    return myBndBox;

  for (int aSensitiveIdx = 0; aSensitiveIdx < myEntities.Length(); ++aSensitiveIdx)
  {
    myBndBox.Combine(myEntities.Value(aSensitiveIdx)->BoundingBox());
  }

  return myBndBox;
}

gp_Pnt Select3D_SensitiveWire::CenterOfGeometry() const
{
  return myCenter;
}

void Select3D_SensitiveWire::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Select3D_SensitiveSet)

  for (NCollection_Vector<occ::handle<Select3D_SensitiveEntity>>::Iterator anIterator(myEntities);
       anIterator.More();
       anIterator.Next())
  {
    const occ::handle<Select3D_SensitiveEntity>& anEntity = anIterator.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, anEntity.get())
  }
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myBndBox)
}
