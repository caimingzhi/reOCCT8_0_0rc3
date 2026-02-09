#pragma once

#include <Storage_BaseDriver.hpp>
#include <Storage_InternalData.hpp>
#include <TCollection_AsciiString.hpp>
#include <Storage_TypedCallBack.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class Storage_CallBack;

class Storage_Schema : public Standard_Transient
{

public:
  Standard_EXPORT Storage_Schema();

  Standard_EXPORT void SetVersion(const TCollection_AsciiString& aVersion);

  Standard_EXPORT TCollection_AsciiString Version() const;

  Standard_EXPORT void SetName(const TCollection_AsciiString& aSchemaName);

  Standard_EXPORT TCollection_AsciiString Name() const;

  Standard_EXPORT void Write(const occ::handle<Storage_BaseDriver>& s,
                             const occ::handle<Storage_Data>&       aData) const;

  Standard_EXPORT static TCollection_AsciiString ICreationDate();

  Standard_EXPORT static bool CheckTypeMigration(const TCollection_AsciiString& theTypeName,
                                                 TCollection_AsciiString&       theNewName);

  Standard_EXPORT void AddReadUnknownTypeCallBack(const TCollection_AsciiString&       aTypeName,
                                                  const occ::handle<Storage_CallBack>& aCallBack);

  Standard_EXPORT void RemoveReadUnknownTypeCallBack(const TCollection_AsciiString& aTypeName);

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>>
                  InstalledCallBackList() const;

  Standard_EXPORT void ClearCallBackList();

  Standard_EXPORT void UseDefaultCallBack();

  Standard_EXPORT void DontUseDefaultCallBack();

  Standard_EXPORT bool IsUsingDefaultCallBack() const;

  Standard_EXPORT void SetDefaultCallBack(const occ::handle<Storage_CallBack>& f);

  Standard_EXPORT void ResetDefaultCallBack();

  Standard_EXPORT occ::handle<Storage_CallBack> DefaultCallBack() const;

  void WritePersistentObjectHeader(const occ::handle<Standard_Persistent>& sp,
                                   const occ::handle<Storage_BaseDriver>&  theDriver)
  {
    theDriver->WritePersistentObjectHeader(sp->_refnum, sp->_typenum);
  }

  void WritePersistentReference(const occ::handle<Standard_Persistent>& sp,
                                const occ::handle<Storage_BaseDriver>&  theDriver)
  {
    theDriver->PutReference(sp.IsNull() ? 0 : sp->_refnum);
  }

  Standard_EXPORT bool AddPersistent(const occ::handle<Standard_Persistent>& sp,
                                     const char*                             tName) const;

  Standard_EXPORT bool PersistentToAdd(const occ::handle<Standard_Persistent>& sp) const;

  DEFINE_STANDARD_RTTIEXT(Storage_Schema, Standard_Transient)

protected:
  bool HasTypeBinding(const TCollection_AsciiString& aTypeName) const
  {
    return Storage_Schema::ICurrentData()->InternalData()->myTypeBinding.IsBound(aTypeName);
  }

  Standard_EXPORT void BindType(const TCollection_AsciiString&       aTypeName,
                                const occ::handle<Storage_CallBack>& aCallBack) const;

  Standard_EXPORT occ::handle<Storage_CallBack> TypeBinding(
    const TCollection_AsciiString& aTypeName) const;

private:
  Standard_EXPORT void Clear() const;

  Standard_EXPORT static void ISetCurrentData(const occ::handle<Storage_Data>& dData);

  Standard_EXPORT static occ::handle<Storage_Data>& ICurrentData();

  NCollection_DataMap<TCollection_AsciiString, occ::handle<Storage_TypedCallBack>> myCallBack;
  bool                                                                             myCallBackState;
  occ::handle<Storage_CallBack> myDefaultCallBack;
  TCollection_AsciiString       myName;
  TCollection_AsciiString       myVersion;
};
