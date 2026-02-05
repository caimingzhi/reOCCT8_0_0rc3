#include <Select3D_SensitiveEntity.hpp>

#include <SelectMgr_EntityOwner.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveEntity, Standard_Transient)

//=================================================================================================

Select3D_SensitiveEntity::Select3D_SensitiveEntity(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId)
    : myOwnerId(theOwnerId),
      mySFactor(2)
{
}

//=================================================================================================

void Select3D_SensitiveEntity::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myOwnerId.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myTrsfPers.get())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySFactor)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, NbSubElements());

  gp_Pnt aCenterOfGeometry = CenterOfGeometry();
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &aCenterOfGeometry)

  bool aHasInitLocation = HasInitLocation();
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, aHasInitLocation)

  gp_GTrsf anInvInitLocation = InvInitLocation();
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &anInvInitLocation)
}
