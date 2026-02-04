#pragma once


#include <PCDM_RetrievalDriver.hpp>
#include <Storage_Error.hpp>

class StdObjMgt_MapOfInstantiators;
class StdObjMgt_Persistent;

//! retrieval driver of a Part document
class StdLDrivers_DocumentRetrievalDriver : public PCDM_RetrievalDriver
{
public:
  //! Retrieve the content of a file into a new document.
  Standard_EXPORT void Read(
    const TCollection_ExtendedString&     theFileName,
    const occ::handle<CDM_Document>&      theNewDocument,
    const occ::handle<CDM_Application>&   theApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange()) override;

  //! Override pure virtual method (raises exception Standard_NotImplemented)
  Standard_EXPORT void Read(
    Standard_IStream&                     theIStream,
    const occ::handle<Storage_Data>&      theStorageData,
    const occ::handle<CDM_Document>&      theDoc,
    const occ::handle<CDM_Application>&   theApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(StdLDrivers_DocumentRetrievalDriver, PCDM_RetrievalDriver)

protected:
  //! Register types.
  Standard_EXPORT virtual void bindTypes(StdObjMgt_MapOfInstantiators& theMap);

private:
  //! Read persistent document from a file.
  occ::handle<StdObjMgt_Persistent> read(const TCollection_ExtendedString& theFileName,
                                         Storage_HeaderData&               theHeaderData);

  //! Update the reader status and raise an exception appropriate for the given storage error.
  Standard_EXPORT void raiseOnStorageError(Storage_Error theError);
};

