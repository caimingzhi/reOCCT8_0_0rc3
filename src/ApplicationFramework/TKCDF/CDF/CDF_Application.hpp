#pragma once

#include <TCollection_ExtendedString.hpp>
#include <PCDM_ReaderStatus.hpp>

enum CDF_TypeOfActivation
{
  CDF_TOA_New,
  CDF_TOA_Modified,
  CDF_TOA_Unchanged
};

#include <CDF_MetaDataDriver.hpp>
#include <CDM_Application.hpp>
#include <CDM_CanCloseStatus.hpp>
#include <Standard_IStream.hpp>
#include <NCollection_IndexedDataMap.hpp>

class Standard_GUID;
class CDM_Document;
class PCDM_Reader;
class CDM_MetaData;
class PCDM_RetrievalDriver;
class PCDM_StorageDriver;
class CDF_Directory;

class CDF_Application : public CDM_Application
{

public:
  Standard_EXPORT static occ::handle<CDF_Application> Load(const Standard_GUID& aGUID);

  Standard_EXPORT virtual void NewDocument(const TCollection_ExtendedString& theFormat,
                                           occ::handle<CDM_Document>&        theDoc);

  Standard_EXPORT virtual void InitDocument(const occ::handle<CDM_Document>& theDoc) const;

  Standard_EXPORT void Open(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT CDM_CanCloseStatus CanClose(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT void Close(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT occ::handle<CDM_Document> Retrieve(
    const TCollection_ExtendedString&     aFolder,
    const TCollection_ExtendedString&     aName,
    const bool                            UseStorageConfiguration = true,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange());

  Standard_EXPORT occ::handle<CDM_Document> Retrieve(
    const TCollection_ExtendedString&     aFolder,
    const TCollection_ExtendedString&     aName,
    const TCollection_ExtendedString&     aVersion,
    const bool                            UseStorageConfiguration = true,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange());

  Standard_EXPORT PCDM_ReaderStatus CanRetrieve(const TCollection_ExtendedString& theFolder,
                                                const TCollection_ExtendedString& theName,
                                                const bool                        theAppendMode);

  Standard_EXPORT PCDM_ReaderStatus CanRetrieve(const TCollection_ExtendedString& theFolder,
                                                const TCollection_ExtendedString& theName,
                                                const TCollection_ExtendedString& theVersion,
                                                const bool                        theAppendMode);

  PCDM_ReaderStatus GetRetrieveStatus() const { return myRetrievableStatus; }

  Standard_EXPORT void Read(
    Standard_IStream&                     theIStream,
    occ::handle<CDM_Document>&            theDocument,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange());

  Standard_EXPORT virtual occ::handle<PCDM_Reader> ReaderFromFormat(
    const TCollection_ExtendedString& aFormat);

  Standard_EXPORT virtual occ::handle<PCDM_StorageDriver> WriterFromFormat(
    const TCollection_ExtendedString& aFormat);

  Standard_EXPORT bool Format(const TCollection_ExtendedString& aFileName,
                              TCollection_ExtendedString&       theFormat);

  Standard_EXPORT const char16_t* DefaultFolder();

  Standard_EXPORT bool SetDefaultFolder(const char16_t* aFolder);

  Standard_EXPORT occ::handle<CDF_MetaDataDriver> MetaDataDriver() const;

  DEFINE_STANDARD_RTTIEXT(CDF_Application, CDM_Application)

  occ::handle<CDF_MetaDataDriver> myMetaDataDriver;
  occ::handle<CDF_Directory>      myDirectory;

private:
  Standard_EXPORT virtual void Activate(const occ::handle<CDM_Document>& aDocument,
                                        const CDF_TypeOfActivation       aTypeOfActivation);

  Standard_EXPORT occ::handle<CDM_Document> Retrieve(
    const occ::handle<CDM_MetaData>&      aMetaData,
    const bool                            UseStorageConfiguration,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange()) override;

  Standard_EXPORT occ::handle<CDM_Document> Retrieve(
    const occ::handle<CDM_MetaData>&      aMetaData,
    const bool                            UseStorageConfiguration,
    const bool                            IsComponent,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange());

  Standard_EXPORT int DocumentVersion(const occ::handle<CDM_MetaData>& theMetaData) override;

  Standard_EXPORT CDF_TypeOfActivation TypeOfActivation(const occ::handle<CDM_MetaData>& aMetaData);

  Standard_EXPORT PCDM_ReaderStatus CanRetrieve(const occ::handle<CDM_MetaData>& aMetaData,
                                                const bool                       theAppendMode);

protected:
  Standard_EXPORT CDF_Application();

  PCDM_ReaderStatus myRetrievableStatus;
  NCollection_IndexedDataMap<TCollection_ExtendedString, occ::handle<PCDM_RetrievalDriver>>
                                                                                          myReaders;
  NCollection_IndexedDataMap<TCollection_ExtendedString, occ::handle<PCDM_StorageDriver>> myWriters;

private:
  TCollection_ExtendedString myDefaultFolder;
};
