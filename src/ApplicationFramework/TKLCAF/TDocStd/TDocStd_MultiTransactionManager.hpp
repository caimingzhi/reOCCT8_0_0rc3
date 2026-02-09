#pragma once

#include <Standard.hpp>

#include <TDocStd_ApplicationDelta.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
class TCollection_ExtendedString;
class TDocStd_Document;

class TDocStd_MultiTransactionManager : public Standard_Transient
{

public:
  Standard_EXPORT TDocStd_MultiTransactionManager();

  Standard_EXPORT void SetUndoLimit(const int theLimit);

  int GetUndoLimit() const;

  Standard_EXPORT void Undo();

  Standard_EXPORT void Redo();

  const NCollection_Sequence<occ::handle<TDocStd_ApplicationDelta>>& GetAvailableUndos() const;

  const NCollection_Sequence<occ::handle<TDocStd_ApplicationDelta>>& GetAvailableRedos() const;

  Standard_EXPORT void OpenCommand();

  Standard_EXPORT void AbortCommand();

  Standard_EXPORT bool CommitCommand();

  Standard_EXPORT bool CommitCommand(const TCollection_ExtendedString& theName);

  bool HasOpenCommand() const;

  Standard_EXPORT void RemoveLastUndo();

  Standard_EXPORT void DumpTransaction(Standard_OStream& theOS) const;

  Standard_EXPORT void AddDocument(const occ::handle<TDocStd_Document>& theDoc);

  Standard_EXPORT void RemoveDocument(const occ::handle<TDocStd_Document>& theDoc);

  const NCollection_Sequence<occ::handle<TDocStd_Document>>& Documents() const;

  Standard_EXPORT void SetNestedTransactionMode(const bool isAllowed = true);

  bool IsNestedTransactionMode() const;

  Standard_EXPORT void SetModificationMode(const bool theTransactionOnly);

  bool ModificationMode() const;

  Standard_EXPORT void ClearUndos();

  Standard_EXPORT void ClearRedos();

  DEFINE_STANDARD_RTTIEXT(TDocStd_MultiTransactionManager, Standard_Transient)

private:
  NCollection_Sequence<occ::handle<TDocStd_Document>>         myDocuments;
  NCollection_Sequence<occ::handle<TDocStd_ApplicationDelta>> myUndos;
  NCollection_Sequence<occ::handle<TDocStd_ApplicationDelta>> myRedos;
  int                                                         myUndoLimit;
  bool                                                        myOpenTransaction;
  bool                                                        myIsNestedTransactionMode;
  bool                                                        myOnlyTransactionModification;
};

inline int TDocStd_MultiTransactionManager::GetUndoLimit() const
{
  return myUndoLimit;
}

inline const NCollection_Sequence<occ::handle<TDocStd_ApplicationDelta>>&
  TDocStd_MultiTransactionManager::GetAvailableUndos() const
{
  return myUndos;
}

inline const NCollection_Sequence<occ::handle<TDocStd_ApplicationDelta>>&
  TDocStd_MultiTransactionManager::GetAvailableRedos() const
{
  return myRedos;
}

inline const NCollection_Sequence<occ::handle<TDocStd_Document>>& TDocStd_MultiTransactionManager::
  Documents() const
{
  return myDocuments;
}

inline bool TDocStd_MultiTransactionManager::IsNestedTransactionMode() const
{
  return myIsNestedTransactionMode;
}

inline bool TDocStd_MultiTransactionManager::HasOpenCommand() const
{
  return myOpenTransaction;
}

inline bool TDocStd_MultiTransactionManager::ModificationMode() const
{
  return myOnlyTransactionModification;
}
