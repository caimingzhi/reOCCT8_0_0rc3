#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>
#include <Message_ProgressRange.hpp>

class CDM_MetaData;
class CDM_Document;
class Resource_Manager;
class Message_Messenger;
class PCDM_ReaderFilter;

class CDM_Application : public Standard_Transient
{

public:
  Standard_EXPORT virtual occ::handle<Resource_Manager> Resources() = 0;

  Standard_EXPORT virtual occ::handle<Message_Messenger> MessageDriver();

  Standard_EXPORT virtual void BeginOfUpdate(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT virtual void EndOfUpdate(const occ::handle<CDM_Document>&  aDocument,
                                           const bool                        theStatus,
                                           const TCollection_ExtendedString& ErrorString);

  Standard_EXPORT void Write(const char16_t* aString);

  Standard_EXPORT virtual TCollection_ExtendedString Name() const;

  Standard_EXPORT virtual TCollection_AsciiString Version() const;

  Standard_EXPORT virtual NCollection_DataMap<TCollection_ExtendedString,
                                              occ::handle<CDM_MetaData>>&
    MetaDataLookUpTable();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class CDM_Reference;
  friend class CDM_MetaData;

  DEFINE_STANDARD_RTTIEXT(CDM_Application, Standard_Transient)

protected:
  Standard_EXPORT CDM_Application();

  Standard_EXPORT void SetDocumentVersion(const occ::handle<CDM_Document>& aDocument,
                                          const occ::handle<CDM_MetaData>& aMetaData) const;

  Standard_EXPORT void SetReferenceCounter(const occ::handle<CDM_Document>& aDocument,
                                           const int                        aReferenceCounter);

private:
  Standard_EXPORT virtual occ::handle<CDM_Document> Retrieve(
    const occ::handle<CDM_MetaData>&      aMetaData,
    const bool                            UseStorageConfiguration,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange()) = 0;

  Standard_EXPORT virtual int DocumentVersion(const occ::handle<CDM_MetaData>& aMetaData) = 0;

  occ::handle<Message_Messenger>                                             myMessenger;
  NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>> myMetaDataLookUpTable;
};
