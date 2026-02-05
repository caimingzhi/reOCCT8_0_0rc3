#include <Message_Messenger.hpp>
#include <CDM_MetaData.hpp>
#include <PCDM_ReadWriter.hpp>
#include <PCDM_RetrievalDriver.hpp>
#include <Resource_Manager.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PCDM_RetrievalDriver, PCDM_Reader)

void PCDM_RetrievalDriver::References(const TCollection_ExtendedString&     aFileName,
                                      NCollection_Sequence<PCDM_Reference>& theReferences,
                                      const occ::handle<Message_Messenger>& theMsgDriver)
{
  PCDM_ReadWriter::Reader(aFileName)->ReadReferences(aFileName, theReferences, theMsgDriver);
}

int PCDM_RetrievalDriver::DocumentVersion(const TCollection_ExtendedString&     aFileName,
                                          const occ::handle<Message_Messenger>& theMsgDriver)
{
  return PCDM_ReadWriter::Reader(aFileName)->ReadDocumentVersion(aFileName, theMsgDriver);
}

int PCDM_RetrievalDriver::ReferenceCounter(const TCollection_ExtendedString&     aFileName,
                                           const occ::handle<Message_Messenger>& theMsgDriver)
{
  return PCDM_ReadWriter::Reader(aFileName)->ReadReferenceCounter(aFileName, theMsgDriver);
}

void PCDM_RetrievalDriver::SetFormat(const TCollection_ExtendedString& aformat)
{
  myFormat = aformat;
}

TCollection_ExtendedString PCDM_RetrievalDriver::GetFormat() const
{
  return myFormat;
}
