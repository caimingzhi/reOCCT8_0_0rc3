#include <CDM_Document.hpp>
#include <FSD_CmpFile.hpp>
#include <PCDM_DriverError.hpp>
#include <PCDM_ReadWriter.hpp>
#include <PCDM_StorageDriver.hpp>
#include <Resource_Manager.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>
#include <Storage_Data.hpp>
#include <Storage_OpenMode.hpp>
#include <Storage_Schema.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_Sequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PCDM_StorageDriver, PCDM_Writer)

#define STORAGE_VERSION "STORAGE_VERSION:"

void PCDM_StorageDriver::Write(const occ::handle<CDM_Document>&  aDocument,
                               const TCollection_ExtendedString& aFileName,
                               const Message_ProgressRange& /*theRange*/)
{
  occ::handle<Storage_Schema> theSchema = new Storage_Schema;

  occ::handle<Storage_Data> theData = new Storage_Data;

  bool             Failure(false);
  Standard_SStream aMsg;
  aMsg << "error during Make:";
  NCollection_Sequence<occ::handle<PCDM_Document>> thePersistentDocuments;
  {
    try
    {
      OCC_CATCH_SIGNALS
      Make(aDocument, thePersistentDocuments);
    }
    catch (Standard_Failure const& anException)
    {
      aMsg << anException << (char)0;
      Failure = true;
    }
  }

  if (Failure)
    throw PCDM_DriverError(aMsg.str().c_str());

  if (thePersistentDocuments.IsEmpty())
  {
    aMsg << "the storage driver: " << DynamicType()->Name() << "returned no documents to store"
         << (char)0;
    throw PCDM_DriverError(aMsg.str().c_str());
  }

  int i = 1;
  for (; i <= thePersistentDocuments.Length(); i++)
  {
    theData->AddRoot(thePersistentDocuments(i));
  }

  TCollection_AsciiString ligne(STORAGE_VERSION);
  ligne += PCDM_ReadWriter::Writer()->Version();
  theData->AddToUserInfo(ligne);

  PCDM_ReadWriter::WriteFileFormat(theData, aDocument);
  PCDM_ReadWriter::Writer()->WriteReferenceCounter(theData, aDocument);
  PCDM_ReadWriter::Writer()->WriteReferences(theData, aDocument, aFileName);
  PCDM_ReadWriter::Writer()->WriteExtensions(theData, aDocument);
  PCDM_ReadWriter::Writer()->WriteVersion(theData, aDocument);

  // add document comments
  NCollection_Sequence<TCollection_ExtendedString> aComments;
  aDocument->Comments(aComments);
  int aLen = aComments.Length();
  for (i = 1; i <= aLen; i++)
  {
    theData->AddToComments(aComments(i));
  }

  occ::handle<FSD_CmpFile> theFile = new FSD_CmpFile;
  PCDM_ReadWriter::Open(theFile, aFileName, Storage_VSWrite);
  theSchema->Write(theFile, theData);
  theFile->Close();

  if (theData->ErrorStatus() != Storage_VSOk)
    throw PCDM_DriverError(theData->ErrorStatusExtension().ToCString());
}

//=================================================================================================

void PCDM_StorageDriver::Write(const occ::handle<CDM_Document>& /*aDocument*/,
                               Standard_OStream& /*theOStream*/,
                               const Message_ProgressRange& /*theRange*/)
{
}

// occ::handle<PCDM_Document> PCDM_StorageDriver::Make(const occ::handle<CDM_Document>& aDocument) {
occ::handle<PCDM_Document> PCDM_StorageDriver::Make(const occ::handle<CDM_Document>&)
{
  occ::handle<PCDM_Document> voidDocument;
  Standard_SStream           aMsg;
  aMsg << "No Make method were implemented in this Driver" << DynamicType()->Name() << (char)0;
  throw Standard_NotImplemented(aMsg.str().c_str());
}

void PCDM_StorageDriver::Make(const occ::handle<CDM_Document>&                  aDocument,
                              NCollection_Sequence<occ::handle<PCDM_Document>>& Documents)
{
  Documents.Append(Make(aDocument));
}

//=================================================================================================

void PCDM_StorageDriver::SetFormat(const TCollection_ExtendedString& aformat)
{
  myFormat = aformat;
}

//=================================================================================================

TCollection_ExtendedString PCDM_StorageDriver::GetFormat() const
{
  return myFormat;
}

//=================================================================================================

bool PCDM_StorageDriver::IsError() const
{
  return myIsError;
}

//=================================================================================================

void PCDM_StorageDriver::SetIsError(const bool theIsError)
{
  myIsError = theIsError;
}

//=================================================================================================

PCDM_StoreStatus PCDM_StorageDriver::GetStoreStatus() const
{
  return myStoreStatus;
}

//=================================================================================================

void PCDM_StorageDriver::SetStoreStatus(const PCDM_StoreStatus theStoreStatus)
{
  myStoreStatus = theStoreStatus;
}
