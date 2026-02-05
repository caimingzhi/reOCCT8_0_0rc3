#pragma once

#include <Select3D_SensitiveEntity.hpp>
#include <Standard.hpp>
#include <Standard_Type.hpp>

//! The purpose of this class is to mark sensitive entities selectable or not
//! depending on current active selection of parent object for proper BVH traverse
class SelectMgr_SensitiveEntity : public Standard_Transient
{
public:
  //! Creates new inactive for selection object with base entity theEntity
  Standard_EXPORT SelectMgr_SensitiveEntity(const occ::handle<Select3D_SensitiveEntity>& theEntity);

  ~SelectMgr_SensitiveEntity() override = default;

  //! Clears up all resources and memory
  Standard_EXPORT void Clear();

  //! Returns related instance of SelectBasics class
  const occ::handle<Select3D_SensitiveEntity>& BaseSensitive() const { return mySensitive; }

  //! Returns true if this entity belongs to the active selection
  //! mode of parent object
  bool IsActiveForSelection() const { return myIsActiveForSelection; }

  //! Marks entity as inactive for selection
  void ResetSelectionActiveStatus() const { myIsActiveForSelection = false; }

  //! Marks entity as active for selection
  void SetActiveForSelection() const { myIsActiveForSelection = true; }

  //! Dumps the content of me into the stream
  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_SensitiveEntity, Standard_Transient) // Type definition

private:
  occ::handle<Select3D_SensitiveEntity> mySensitive;            //!< Related SelectBasics entity
  mutable bool                          myIsActiveForSelection; //!< Selection activity status
};
