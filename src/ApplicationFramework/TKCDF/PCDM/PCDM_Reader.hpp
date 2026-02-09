#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <PCDM_ReaderStatus.hpp>
#include <Standard_Transient.hpp>
#include <Standard_IStream.hpp>
#include <Storage_Data.hpp>
#include <Message_ProgressRange.hpp>

class CDM_Document;
class TCollection_ExtendedString;
class CDM_Application;
class PCDM_ReaderFilter;

class PCDM_Reader : public Standard_Transient
{

public:
  Standard_EXPORT virtual void Read(
    const TCollection_ExtendedString&     aFileName,
    const occ::handle<CDM_Document>&      aNewDocument,
    const occ::handle<CDM_Application>&   anApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter   = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theProgress = Message_ProgressRange()) = 0;

  Standard_EXPORT virtual void Read(
    Standard_IStream&                     theIStream,
    const occ::handle<Storage_Data>&      theStorageData,
    const occ::handle<CDM_Document>&      theDoc,
    const occ::handle<CDM_Application>&   theApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter   = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theProgress = Message_ProgressRange()) = 0;

  PCDM_ReaderStatus GetStatus() const;

  DEFINE_STANDARD_RTTIEXT(PCDM_Reader, Standard_Transient)

protected:
  PCDM_ReaderStatus myReaderStatus;
};

inline PCDM_ReaderStatus PCDM_Reader::GetStatus() const
{
  return myReaderStatus;
}
