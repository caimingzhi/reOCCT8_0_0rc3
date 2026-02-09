#pragma once

#include <NCollection_SparseArray.hpp>
#include <TDF_Label.hpp>

class Standard_GUID;

class TObj_TIntSparseArray : public TDF_Attribute
{
public:
  Standard_EXPORT TObj_TIntSparseArray();

  static Standard_EXPORT const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

  static Standard_EXPORT occ::handle<TObj_TIntSparseArray> Set(const TDF_Label& theLabel);

public:
  size_t Size() const { return myVector.Size(); }

  typedef NCollection_SparseArray<int>::ConstIterator Iterator;

  Iterator GetIterator() const { return Iterator(myVector); }

  bool HasValue(const size_t theId) const { return myVector.HasValue(theId); }

  int Value(const size_t theId) const { return myVector.Value(theId); }

  Standard_EXPORT void SetValue(const size_t theId, const int theValue);

  Standard_EXPORT void UnsetValue(const size_t theId);

  Standard_EXPORT void Clear();

public:
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theDelta) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  Standard_EXPORT void BeforeCommitTransaction() override;

  Standard_EXPORT void DeltaOnModification(
    const occ::handle<TDF_DeltaOnModification>& theDelta) override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& theDelta,
                                 const bool                             toForce) override;

public:
  void SetDoBackup(const bool toDo) { myDoBackup = toDo; }

  void ClearDelta() { myOldMap.Clear(); }

private:
  enum
  {
    AbsentValue = -1
  };

  void backupValue(const size_t theId, const int theCurrValue, const int theNewValue);

  NCollection_SparseArray<int> myVector;
  NCollection_SparseArray<int> myOldMap;
  bool                         myDoBackup;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_TIntSparseArray, TDF_Attribute)
};

#ifdef _MSC_VER
  #pragma once
#endif
