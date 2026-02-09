#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_ExtendedString.hpp>
#include <PCDM_StoreStatus.hpp>
#include <CDF_StoreSetNameStatus.hpp>
#include <TCollection_HExtendedString.hpp>

#include <Message_ProgressRange.hpp>

class CDF_StoreList;
class CDM_Document;

class CDF_Store
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT CDF_Store(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT occ::handle<TCollection_HExtendedString> Folder() const;

  Standard_EXPORT occ::handle<TCollection_HExtendedString> Name() const;

  Standard_EXPORT bool IsStored() const;

  Standard_EXPORT bool IsModified() const;

  Standard_EXPORT bool CurrentIsConsistent() const;

  Standard_EXPORT bool IsConsistent() const;

  Standard_EXPORT bool HasAPreviousVersion() const;

  Standard_EXPORT occ::handle<TCollection_HExtendedString> PreviousVersion() const;

  Standard_EXPORT bool IsMainDocument() const;

  Standard_EXPORT bool SetFolder(const TCollection_ExtendedString& aFolder);

  Standard_EXPORT CDF_StoreSetNameStatus SetName(const char16_t* aName);

  Standard_EXPORT void SetComment(const char16_t* aComment);

  Standard_EXPORT occ::handle<TCollection_HExtendedString> Comment() const;

  Standard_EXPORT CDF_StoreSetNameStatus RecheckName();

  Standard_EXPORT bool SetPreviousVersion(const char16_t* aPreviousVersion);

  Standard_EXPORT void Realize(const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT const char16_t* Path() const;

  Standard_EXPORT occ::handle<TCollection_HExtendedString> MetaDataPath() const;

  Standard_EXPORT occ::handle<TCollection_HExtendedString> Description() const;

  Standard_EXPORT void SetCurrent(const char16_t* aPresentation);

  Standard_EXPORT void SetMain();

  Standard_EXPORT PCDM_StoreStatus StoreStatus() const;

  Standard_EXPORT const char16_t* AssociatedStatusText() const;

  Standard_EXPORT CDF_StoreSetNameStatus SetName(const TCollection_ExtendedString& aName);

  Standard_EXPORT bool SetFolder(const char16_t* aFolder);

private:
  Standard_EXPORT CDF_Store();

  Standard_EXPORT void FindDefault();

  Standard_EXPORT void Init();

  occ::handle<CDF_StoreList> myList;
  occ::handle<CDM_Document>  myMainDocument;
  occ::handle<CDM_Document>  myCurrentDocument;
  bool                       myHasSubComponents;
  bool                       myIsMainDocument;
  TCollection_ExtendedString myPath;
  TCollection_ExtendedString myText;
  PCDM_StoreStatus           myStatus;
};
