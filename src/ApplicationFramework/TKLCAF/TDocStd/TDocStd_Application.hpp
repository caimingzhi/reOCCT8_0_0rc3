#pragma once

#include <Standard.hpp>

#include <CDF_Application.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Integer.hpp>
#include <Standard_IStream.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <PCDM_ReaderStatus.hpp>
#include <PCDM_StoreStatus.hpp>
#include <TDocStd_Document.hpp>

class Resource_Manager;
class CDM_Document;
class TCollection_ExtendedString;

class TDocStd_Application : public CDF_Application
{

public:
  Standard_EXPORT TDocStd_Application();

  Standard_EXPORT bool IsDriverLoaded() const;

  Standard_EXPORT occ::handle<Resource_Manager> Resources() override;

  Standard_EXPORT virtual const char* ResourcesName();

  Standard_EXPORT void DefineFormat(const TCollection_AsciiString&           theFormat,
                                    const TCollection_AsciiString&           theDescription,
                                    const TCollection_AsciiString&           theExtension,
                                    const occ::handle<PCDM_RetrievalDriver>& theReader,
                                    const occ::handle<PCDM_StorageDriver>&   theWriter);

  Standard_EXPORT void ReadingFormats(NCollection_Sequence<TCollection_AsciiString>& theFormats);

  Standard_EXPORT void WritingFormats(NCollection_Sequence<TCollection_AsciiString>& theFormats);

  Standard_EXPORT int NbDocuments() const;

  Standard_EXPORT void GetDocument(const int index, occ::handle<TDocStd_Document>& aDoc) const;

  Standard_EXPORT void NewDocument(const TCollection_ExtendedString& format,
                                   occ::handle<CDM_Document>&        aDoc) override;

  Standard_EXPORT void NewDocument(const TCollection_ExtendedString& format,
                                   occ::handle<TDocStd_Document>&    aDoc);

  Standard_EXPORT void InitDocument(const occ::handle<CDM_Document>& aDoc) const override;

  Standard_EXPORT void Close(const occ::handle<TDocStd_Document>& aDoc);

  Standard_EXPORT int IsInSession(const TCollection_ExtendedString& path) const;

  Standard_EXPORT PCDM_ReaderStatus
    Open(const TCollection_ExtendedString&     thePath,
         occ::handle<TDocStd_Document>&        theDoc,
         const occ::handle<PCDM_ReaderFilter>& theFilter,
         const Message_ProgressRange&          theRange = Message_ProgressRange());

  PCDM_ReaderStatus Open(const TCollection_ExtendedString& thePath,
                         occ::handle<TDocStd_Document>&    theDoc,
                         const Message_ProgressRange&      theRange = Message_ProgressRange())
  {
    return Open(thePath, theDoc, occ::handle<PCDM_ReaderFilter>(), theRange);
  }

  Standard_EXPORT PCDM_ReaderStatus
    Open(Standard_IStream&                     theIStream,
         occ::handle<TDocStd_Document>&        theDoc,
         const occ::handle<PCDM_ReaderFilter>& theFilter,
         const Message_ProgressRange&          theRange = Message_ProgressRange());

  PCDM_ReaderStatus Open(Standard_IStream&              theIStream,
                         occ::handle<TDocStd_Document>& theDoc,
                         const Message_ProgressRange&   theRange = Message_ProgressRange())
  {
    return Open(theIStream, theDoc, occ::handle<PCDM_ReaderFilter>(), theRange);
  }

  Standard_EXPORT PCDM_StoreStatus
    SaveAs(const occ::handle<TDocStd_Document>& theDoc,
           const TCollection_ExtendedString&    path,
           const Message_ProgressRange&         theRange = Message_ProgressRange());

  Standard_EXPORT PCDM_StoreStatus
    SaveAs(const occ::handle<TDocStd_Document>& theDoc,
           Standard_OStream&                    theOStream,
           const Message_ProgressRange&         theRange = Message_ProgressRange());

  Standard_EXPORT PCDM_StoreStatus
    Save(const occ::handle<TDocStd_Document>& theDoc,
         const Message_ProgressRange&         theRange = Message_ProgressRange());

  Standard_EXPORT PCDM_StoreStatus
    SaveAs(const occ::handle<TDocStd_Document>& theDoc,
           const TCollection_ExtendedString&    path,
           TCollection_ExtendedString&          theStatusMessage,
           const Message_ProgressRange&         theRange = Message_ProgressRange());

  Standard_EXPORT PCDM_StoreStatus
    SaveAs(const occ::handle<TDocStd_Document>& theDoc,
           Standard_OStream&                    theOStream,
           TCollection_ExtendedString&          theStatusMessage,
           const Message_ProgressRange&         theRange = Message_ProgressRange());

  Standard_EXPORT PCDM_StoreStatus
    Save(const occ::handle<TDocStd_Document>& theDoc,
         TCollection_ExtendedString&          theStatusMessage,
         const Message_ProgressRange&         theRange = Message_ProgressRange());

  Standard_EXPORT virtual void OnOpenTransaction(const occ::handle<TDocStd_Document>& theDoc);

  Standard_EXPORT virtual void OnCommitTransaction(const occ::handle<TDocStd_Document>& theDoc);

  Standard_EXPORT virtual void OnAbortTransaction(const occ::handle<TDocStd_Document>& theDoc);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(TDocStd_Application, CDF_Application)

protected:
  occ::handle<Resource_Manager> myResources;
  bool                          myIsDriverLoaded;
};
