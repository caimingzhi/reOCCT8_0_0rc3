# Source files for PCDM package
set(OCCT_PCDM_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_PCDM_FILES
  PCDM.cxx
  PCDM.hpp
  
  PCDM_Document.cxx
  PCDM_Document.hpp
  PCDM_DOMHeaderParser.cxx
  PCDM_DOMHeaderParser.hpp
  PCDM_DriverError.hpp
  PCDM_Reader.cxx
  PCDM_Reader.hpp
  PCDM_Reader_1.hpp
  PCDM_ReaderFilter.cxx
  PCDM_ReaderFilter.hpp
  PCDM_ReaderStatus.hpp
  PCDM_ReadWriter.cxx
  PCDM_ReadWriter.hpp
  PCDM_ReadWriter_1.cxx
  PCDM_ReadWriter_1.hpp
  PCDM_Reference.cxx
  PCDM_Reference.hpp
  PCDM_ReferenceIterator.cxx
  PCDM_ReferenceIterator.hpp
  PCDM_RetrievalDriver.cxx
  PCDM_RetrievalDriver.hpp

  PCDM_StorageDriver.cxx
  PCDM_StorageDriver.hpp
  PCDM_StoreStatus.hpp
  PCDM_TypeOfFileDriver.hpp
  PCDM_Writer.cxx
  PCDM_Writer.hpp
)
