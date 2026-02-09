#pragma once

#include <Select3D_SensitiveEntity.hpp>
#include <Standard.hpp>
#include <Standard_Type.hpp>

class SelectMgr_SensitiveEntity : public Standard_Transient
{
public:
  Standard_EXPORT SelectMgr_SensitiveEntity(const occ::handle<Select3D_SensitiveEntity>& theEntity);

  ~SelectMgr_SensitiveEntity() override = default;

  Standard_EXPORT void Clear();

  const occ::handle<Select3D_SensitiveEntity>& BaseSensitive() const { return mySensitive; }

  bool IsActiveForSelection() const { return myIsActiveForSelection; }

  void ResetSelectionActiveStatus() const { myIsActiveForSelection = false; }

  void SetActiveForSelection() const { myIsActiveForSelection = true; }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_SensitiveEntity, Standard_Transient)

private:
  occ::handle<Select3D_SensitiveEntity> mySensitive;
  mutable bool                          myIsActiveForSelection;
};
