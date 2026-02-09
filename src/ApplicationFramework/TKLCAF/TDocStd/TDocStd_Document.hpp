#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TDF_Transaction.hpp>
#include <TDF_Delta.hpp>
#include <NCollection_List.hpp>
#include <CDM_Document.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TDocStd_FormatVersion.hpp>
class TDF_Data;
class TDF_Delta;
class TDF_Label;
class TCollection_AsciiString;
class TDocStd_CompoundDelta;

class TDocStd_Document : public CDM_Document
{

public:
  Standard_EXPORT static occ::handle<TDocStd_Document> Get(const TDF_Label& L);

  Standard_EXPORT TDocStd_Document(const TCollection_ExtendedString& astorageformat);

  Standard_EXPORT bool IsSaved() const;

  bool IsChanged() const;

  void SetSaved();

  void SetSavedTime(const int theTime);

  int GetSavedTime() const;

  Standard_EXPORT TCollection_ExtendedString GetName() const;

  Standard_EXPORT TCollection_ExtendedString GetPath() const;

  Standard_EXPORT void SetData(const occ::handle<TDF_Data>& data);

  Standard_EXPORT occ::handle<TDF_Data> GetData() const;

  Standard_EXPORT TDF_Label Main() const;

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT bool IsValid() const;

  Standard_EXPORT void SetModified(const TDF_Label& L);

  Standard_EXPORT void PurgeModified();

  Standard_EXPORT const NCollection_Map<TDF_Label>& GetModified() const;

  Standard_EXPORT void NewCommand();

  Standard_EXPORT bool HasOpenCommand() const;

  Standard_EXPORT void OpenCommand();

  Standard_EXPORT bool CommitCommand();

  Standard_EXPORT void AbortCommand();

  Standard_EXPORT int GetUndoLimit() const;

  Standard_EXPORT void SetUndoLimit(const int L);

  Standard_EXPORT void ClearUndos();

  Standard_EXPORT void ClearRedos();

  Standard_EXPORT int GetAvailableUndos() const;

  Standard_EXPORT bool Undo();

  Standard_EXPORT int GetAvailableRedos() const;

  Standard_EXPORT bool Redo();

  Standard_EXPORT const NCollection_List<occ::handle<TDF_Delta>>& GetUndos() const;

  Standard_EXPORT const NCollection_List<occ::handle<TDF_Delta>>& GetRedos() const;

  Standard_EXPORT void RemoveFirstUndo();

  Standard_EXPORT bool InitDeltaCompaction();

  Standard_EXPORT bool PerformDeltaCompaction();

  Standard_EXPORT void UpdateReferences(const TCollection_AsciiString& aDocEntry);

  Standard_EXPORT void Recompute();

  Standard_EXPORT void Update(const occ::handle<CDM_Document>& aToDocument,
                              const int                        aReferenceIdentifier,
                              void* const                      aModifContext) override;

  Standard_EXPORT TCollection_ExtendedString StorageFormat() const override;

  void SetEmptyLabelsSavingMode(const bool isAllowed);

  bool EmptyLabelsSavingMode() const;

  Standard_EXPORT virtual void ChangeStorageFormat(
    const TCollection_ExtendedString& newStorageFormat);

  void SetNestedTransactionMode(const bool isAllowed = true);

  bool IsNestedTransactionMode() const;

  void SetModificationMode(const bool theTransactionOnly);

  bool ModificationMode() const;

  Standard_EXPORT virtual void BeforeClose();

  Standard_EXPORT TDocStd_FormatVersion StorageFormatVersion() const;

  Standard_EXPORT void ChangeStorageFormatVersion(const TDocStd_FormatVersion theVersion);

  Standard_EXPORT static TDocStd_FormatVersion CurrentStorageFormatVersion();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(TDocStd_Document, CDM_Document)

protected:
  Standard_EXPORT virtual bool CommitTransaction();

  Standard_EXPORT virtual void AbortTransaction();

  Standard_EXPORT virtual void OpenTransaction();

  TCollection_ExtendedString               myStorageFormat;
  NCollection_List<occ::handle<TDF_Delta>> myUndos;
  NCollection_List<occ::handle<TDF_Delta>> myRedos;

private:
  Standard_EXPORT static void AppendDeltaToTheFirst(
    const occ::handle<TDocStd_CompoundDelta>& theDelta1,
    const occ::handle<TDF_Delta>&             theDelta2);

  occ::handle<TDF_Data>                    myData;
  int                                      myUndoLimit;
  TDF_Transaction                          myUndoTransaction;
  occ::handle<TDF_Delta>                   myFromUndo;
  occ::handle<TDF_Delta>                   myFromRedo;
  int                                      mySaveTime;
  bool                                     myIsNestedTransactionMode;
  NCollection_List<occ::handle<TDF_Delta>> myUndoFILO;
  bool                                     myOnlyTransactionModification;
  bool                                     mySaveEmptyLabels;
  TDocStd_FormatVersion                    myStorageFormatVersion;
};

#include <TDF_Data.hpp>

inline void TDocStd_Document::SetNestedTransactionMode(const bool isAllowed)
{
  myIsNestedTransactionMode = isAllowed;
}

inline bool TDocStd_Document::IsNestedTransactionMode() const
{
  return myIsNestedTransactionMode;
}

inline bool TDocStd_Document::IsChanged() const
{
  return myData->Time() != mySaveTime;
}

inline void TDocStd_Document::SetSaved()
{
  mySaveTime = myData->Time();
}

inline void TDocStd_Document::SetModificationMode(const bool theTransactionOnly)
{
  myOnlyTransactionModification = theTransactionOnly;

  if (myOnlyTransactionModification)
  {
    myData->AllowModification(myUndoTransaction.IsOpen());
  }
  else
  {
    myData->AllowModification(true);
  }
}

inline bool TDocStd_Document::ModificationMode() const
{
  return myOnlyTransactionModification;
}

inline void TDocStd_Document::SetSavedTime(const int theTime)
{
  mySaveTime = theTime;
}

inline int TDocStd_Document::GetSavedTime() const
{
  return mySaveTime;
}

inline void TDocStd_Document::SetEmptyLabelsSavingMode(const bool isAllowed)
{
  mySaveEmptyLabels = isAllowed;
}

inline bool TDocStd_Document::EmptyLabelsSavingMode() const
{
  return mySaveEmptyLabels;
}
