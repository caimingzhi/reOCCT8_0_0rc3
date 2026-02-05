#include <SelectMgr_SensitiveEntity.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_SensitiveEntity, Standard_Transient)

//=======================================================================
// function : SelectMgr_SensitiveEntity
// purpose  : Creates new inactive for selection object with base entity
//            theEntity
//=======================================================================
SelectMgr_SensitiveEntity::SelectMgr_SensitiveEntity(
  const occ::handle<Select3D_SensitiveEntity>& theEntity)
    : mySensitive(theEntity),
      myIsActiveForSelection(false)
{
}

//=======================================================================
// function : Clear
// purpose  : Clears up all the resources and memory
//=======================================================================
void SelectMgr_SensitiveEntity::Clear()
{
  mySensitive->Clear();
  mySensitive.Nullify();
}

//=================================================================================================

void SelectMgr_SensitiveEntity::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, mySensitive.get())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsActiveForSelection)
}
