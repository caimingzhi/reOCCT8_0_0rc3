#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <CDM_Reference.hpp>
#include <NCollection_List.hpp>
#include <CDM_CanCloseStatus.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_OStream.hpp>

class CDM_MetaData;
class CDM_Application;
class CDM_Reference;
class Resource_Manager;

class CDM_Document : public Standard_Transient
{

public:
  Standard_EXPORT virtual void Update(const occ::handle<CDM_Document>& aToDocument,
                                      const int                        aReferenceIdentifier,
                                      void* const                      aModifContext);

  Standard_EXPORT virtual bool Update(TCollection_ExtendedString& ErrorString);

  Standard_EXPORT virtual TCollection_ExtendedString StorageFormat() const = 0;

  Standard_EXPORT virtual void Extensions(
    NCollection_Sequence<TCollection_ExtendedString>& Extensions) const;

  Standard_EXPORT virtual bool GetAlternativeDocument(
    const TCollection_ExtendedString& aFormat,
    occ::handle<CDM_Document>&        anAlternativeDocument);

  Standard_EXPORT int CreateReference(const occ::handle<CDM_Document>& anOtherDocument);

  Standard_EXPORT void RemoveReference(const int aReferenceIdentifier);

  Standard_EXPORT void RemoveAllReferences();

  Standard_EXPORT occ::handle<CDM_Document> Document(const int aReferenceIdentifier) const;

  Standard_EXPORT bool IsInSession(const int aReferenceIdentifier) const;

  Standard_EXPORT bool IsStored(const int aReferenceIdentifier) const;

  Standard_EXPORT TCollection_ExtendedString Name(const int aReferenceIdentifier) const;

  Standard_EXPORT void UpdateFromDocuments(void* const aModifContext) const;

  Standard_EXPORT int ToReferencesNumber() const;

  Standard_EXPORT int FromReferencesNumber() const;

  Standard_EXPORT bool ShallowReferences(const occ::handle<CDM_Document>& aDocument) const;

  Standard_EXPORT bool DeepReferences(const occ::handle<CDM_Document>& aDocument) const;

  Standard_EXPORT int CopyReference(const occ::handle<CDM_Document>& aFromDocument,
                                    const int                        aReferenceIdentifier);

  Standard_EXPORT bool IsReadOnly() const;

  Standard_EXPORT bool IsReadOnly(const int aReferenceIdentifier) const;

  Standard_EXPORT void SetIsReadOnly();

  Standard_EXPORT void UnsetIsReadOnly();

  Standard_EXPORT void Modify();

  Standard_EXPORT int Modifications() const;

  Standard_EXPORT void UnModify();

  Standard_EXPORT bool IsUpToDate(const int aReferenceIdentifier) const;

  Standard_EXPORT void SetIsUpToDate(const int aReferenceIdentifier);

  Standard_EXPORT void SetComment(const TCollection_ExtendedString& aComment);

  Standard_EXPORT void AddComment(const TCollection_ExtendedString& aComment);

  Standard_EXPORT void SetComments(
    const NCollection_Sequence<TCollection_ExtendedString>& aComments);

  Standard_EXPORT void Comments(NCollection_Sequence<TCollection_ExtendedString>& aComments) const;

  Standard_EXPORT const char16_t* Comment() const;

  Standard_EXPORT bool IsStored() const;

  Standard_EXPORT int StorageVersion() const;

  Standard_EXPORT void SetMetaData(const occ::handle<CDM_MetaData>& aMetaData);

  Standard_EXPORT void UnsetIsStored();

  Standard_EXPORT occ::handle<CDM_MetaData> MetaData() const;

  Standard_EXPORT TCollection_ExtendedString Folder() const;

  Standard_EXPORT void SetRequestedFolder(const TCollection_ExtendedString& aFolder);

  Standard_EXPORT TCollection_ExtendedString RequestedFolder() const;

  Standard_EXPORT bool HasRequestedFolder() const;

  Standard_EXPORT void SetRequestedName(const TCollection_ExtendedString& aName);

  Standard_EXPORT TCollection_ExtendedString RequestedName();

  Standard_EXPORT void SetRequestedPreviousVersion(
    const TCollection_ExtendedString& aPreviousVersion);

  Standard_EXPORT void UnsetRequestedPreviousVersion();

  Standard_EXPORT bool HasRequestedPreviousVersion() const;

  Standard_EXPORT TCollection_ExtendedString RequestedPreviousVersion() const;

  Standard_EXPORT void SetRequestedComment(const TCollection_ExtendedString& aComment);

  Standard_EXPORT TCollection_ExtendedString RequestedComment() const;

  Standard_EXPORT void LoadResources();

  Standard_EXPORT bool FindFileExtension();

  Standard_EXPORT TCollection_ExtendedString FileExtension();

  Standard_EXPORT bool FindDescription();

  Standard_EXPORT TCollection_ExtendedString Description();

  Standard_EXPORT bool IsModified() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;
  Standard_OStream&                 operator<<(Standard_OStream& anOStream);

  Standard_EXPORT bool IsOpened() const;

  Standard_EXPORT void Open(const occ::handle<CDM_Application>& anApplication);

  Standard_EXPORT CDM_CanCloseStatus CanClose() const;

  Standard_EXPORT void Close();

  Standard_EXPORT const occ::handle<CDM_Application>& Application() const;

  Standard_EXPORT virtual bool CanCloseReference(const occ::handle<CDM_Document>& aDocument,
                                                 const int aReferenceIdentifier) const;

  Standard_EXPORT virtual void CloseReference(const occ::handle<CDM_Document>& aDocument,
                                              const int aReferenceIdentifier);

  Standard_EXPORT bool IsOpened(const int aReferenceIdentifier) const;

  Standard_EXPORT void CreateReference(const occ::handle<CDM_MetaData>&    aMetaData,
                                       const int                           aReferenceIdentifier,
                                       const occ::handle<CDM_Application>& anApplication,
                                       const int                           aToDocumentVersion,
                                       const bool                          UseStorageConfiguration);

  Standard_EXPORT int CreateReference(const occ::handle<CDM_MetaData>&    aMetaData,
                                      const occ::handle<CDM_Application>& anApplication,
                                      const int                           aDocumentVersion,
                                      const bool                          UseStorageConfiguration);

  Standard_EXPORT int ReferenceCounter() const;

  Standard_EXPORT virtual void Update();

  Standard_EXPORT occ::handle<CDM_Reference> Reference(const int aReferenceIdentifier) const;

  Standard_EXPORT void SetModifications(const int Modifications);

  Standard_EXPORT void SetReferenceCounter(const int aReferenceCounter);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class CDM_Reference;
  friend class CDM_ReferenceIterator;
  friend class CDM_Application;

  DEFINE_STANDARD_RTTIEXT(CDM_Document, Standard_Transient)

protected:
  Standard_EXPORT CDM_Document();

  Standard_EXPORT ~CDM_Document() override;

  bool myResourcesAreLoaded;

private:
  Standard_EXPORT occ::handle<Resource_Manager> StorageResource();

  Standard_EXPORT void AddToReference(const occ::handle<CDM_Reference>& aReference);

  Standard_EXPORT void AddFromReference(const occ::handle<CDM_Reference>& aReference);

  Standard_EXPORT void RemoveFromReference(const int aReferenceIdentifier);

  NCollection_Sequence<TCollection_ExtendedString> myComments;
  NCollection_List<occ::handle<CDM_Reference>>     myFromReferences;
  NCollection_List<occ::handle<CDM_Reference>>     myToReferences;
  int                                              myVersion;
  int                                              myActualReferenceIdentifier;
  int                                              myStorageVersion;
  occ::handle<CDM_MetaData>                        myMetaData;
  TCollection_ExtendedString                       myRequestedComment;
  TCollection_ExtendedString                       myRequestedFolder;
  bool                                             myRequestedFolderIsDefined;
  TCollection_ExtendedString                       myRequestedName;
  bool                                             myRequestedNameIsDefined;
  bool                                             myRequestedPreviousVersionIsDefined;
  TCollection_ExtendedString                       myRequestedPreviousVersion;
  TCollection_ExtendedString                       myFileExtension;
  TCollection_ExtendedString                       myDescription;
  bool                                             myFileExtensionWasFound;
  bool                                             myDescriptionWasFound;
  occ::handle<CDM_Application>                     myApplication;
};
