#pragma once

#include <SelectMgr_SensitiveEntity.hpp>
#include <SelectMgr_StateOfSelection.hpp>

enum SelectMgr_TypeOfBVHUpdate
{
  SelectMgr_TBU_Add,
  SelectMgr_TBU_Remove,
  SelectMgr_TBU_Renew,
  SelectMgr_TBU_Invalidate,
  SelectMgr_TBU_None
};

#include <SelectMgr_TypeOfUpdate.hpp>

class Select3D_SensitiveEntity;

class SelectMgr_Selection : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(SelectMgr_Selection, Standard_Transient)
public:
  Standard_EXPORT SelectMgr_Selection(const int theModeIdx = 0);

  Standard_EXPORT ~SelectMgr_Selection() override;

  Standard_EXPORT void Destroy();

  Standard_EXPORT void Add(const occ::handle<Select3D_SensitiveEntity>& theSensitive);

  Standard_EXPORT void Clear();

  bool IsEmpty() const { return myEntities.IsEmpty(); }

  int Mode() const { return myMode; }

  const NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>& Entities() const
  {
    return myEntities;
  }

  NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>& ChangeEntities()
  {
    return myEntities;
  }

  SelectMgr_TypeOfUpdate UpdateStatus() const { return myUpdateStatus; }

  void UpdateStatus(const SelectMgr_TypeOfUpdate theStatus) { myUpdateStatus = theStatus; }

  void UpdateBVHStatus(const SelectMgr_TypeOfBVHUpdate theStatus) { myBVHUpdateStatus = theStatus; }

  SelectMgr_TypeOfBVHUpdate BVHUpdateStatus() const { return myBVHUpdateStatus; }

  SelectMgr_StateOfSelection GetSelectionState() const { return mySelectionState; }

  void SetSelectionState(const SelectMgr_StateOfSelection theState) const
  {
    mySelectionState = theState;
  }

  int Sensitivity() const { return mySensFactor; }

  Standard_EXPORT void SetSensitivity(const int theNewSens);

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>> myEntities;
  int                                                        myMode;
  SelectMgr_TypeOfUpdate                                     myUpdateStatus;
  mutable SelectMgr_StateOfSelection                         mySelectionState;
  mutable SelectMgr_TypeOfBVHUpdate                          myBVHUpdateStatus;
  int                                                        mySensFactor;
  bool                                                       myIsCustomSens;
};
