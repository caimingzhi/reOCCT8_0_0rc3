

#include <StdLDrivers_DocumentRetrievalDriver.hpp>
#include <StdLDrivers.hpp>

#include <StdObjMgt_MapOfInstantiators.hpp>
#include <StdObjMgt_ReadData.hpp>

#include <Storage_HeaderData.hpp>
#include <Storage_TypeData.hpp>
#include <Storage_RootData.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <Storage_StreamFormatError.hpp>
#include <Storage_StreamReadError.hpp>

#include <PCDM.hpp>
#include <PCDM_ReadWriter.hpp>

#include <Standard_ErrorHandler.hpp>
#include <Standard_NotImplemented.hpp>
#include <NCollection_Array1.hpp>
#include <TDocStd_Document.hpp>
#include <Storage_Schema.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdLDrivers_DocumentRetrievalDriver, PCDM_RetrievalDriver)

void StdLDrivers_DocumentRetrievalDriver::Read(const TCollection_ExtendedString& theFileName,
                                               const occ::handle<CDM_Document>&  theNewDocument,
                                               const occ::handle<CDM_Application>&,
                                               const occ::handle<PCDM_ReaderFilter>&,
                                               const Message_ProgressRange&)
{

  Storage_HeaderData                aHeaderData;
  occ::handle<StdObjMgt_Persistent> aPDocument = read(theFileName, aHeaderData);
  if (aPDocument.IsNull())
    return;

  aPDocument->ImportDocument(occ::down_cast<TDocStd_Document>(theNewDocument));

  theNewDocument->SetComments(aHeaderData.Comments());
}

occ::handle<StdObjMgt_Persistent> StdLDrivers_DocumentRetrievalDriver::read(
  const TCollection_ExtendedString& theFileName,
  Storage_HeaderData&               theHeaderData)
{
  int i;

  occ::handle<Storage_BaseDriver> aFileDriver;
  if (PCDM::FileDriverType(TCollection_AsciiString(theFileName), aFileDriver) == PCDM_TOFD_Unknown)
  {
    myReaderStatus = PCDM_RS_UnknownFileDriver;
    return nullptr;
  }

  try
  {
    OCC_CATCH_SIGNALS
    PCDM_ReadWriter::Open(aFileDriver, theFileName, Storage_VSRead);
    myReaderStatus = PCDM_RS_OK;
  }
  catch (Standard_Failure const& anException)
  {
    myReaderStatus = PCDM_RS_OpenError;

    Standard_SStream aMsg;
    aMsg << anException << std::endl;
    throw Standard_Failure(aMsg.str().c_str());
  }

  if (!theHeaderData.Read(aFileDriver))
    raiseOnStorageError(theHeaderData.ErrorStatus());

  Storage_TypeData aTypeData;
  if (!aTypeData.Read(aFileDriver))
    raiseOnStorageError(aTypeData.ErrorStatus());

  Storage_RootData aRootData;
  if (!aRootData.Read(aFileDriver))
    raiseOnStorageError(aRootData.ErrorStatus());

  if (aRootData.NumberOfRoots() < 1)
  {
    myReaderStatus = PCDM_RS_NoDocument;

    Standard_SStream aMsg;
    aMsg << "could not find any document in this file" << std::endl;
    throw Standard_Failure(aMsg.str().c_str());
  }

  NCollection_Array1<StdObjMgt_Persistent::Instantiator> anInstantiators(1,
                                                                         aTypeData.NumberOfTypes());
  {
    StdObjMgt_MapOfInstantiators aMapOfInst;
    bindTypes(aMapOfInst);

    NCollection_Sequence<TCollection_AsciiString> anUnknownTypes;
    int                                           aCurTypeNum;
    TCollection_AsciiString                       aCurTypeName;

    for (i = 1; i <= aTypeData.NumberOfTypes(); i++)
    {
      aCurTypeName = aTypeData.Type(i);
      aCurTypeNum  = aTypeData.Type(aCurTypeName);

      TCollection_AsciiString newName;
      if (Storage_Schema::CheckTypeMigration(aCurTypeName, newName))
      {
#ifdef OCCT_DEBUG
        std::cout << "CheckTypeMigration:OldType = " << aCurTypeName << " Len = " << aCurTypeNum
                  << std::endl;
        std::cout << "CheckTypeMigration:NewType = " << newName << " Len = " << newName.Length()
                  << std::endl;
#endif
        aCurTypeName = newName;
      }
      StdObjMgt_Persistent::Instantiator anInstantiator;
      if (aMapOfInst.Find(aCurTypeName, anInstantiator))
        anInstantiators(aCurTypeNum) = anInstantiator;
      else
        anUnknownTypes.Append(aCurTypeName);
    }

    if (!anUnknownTypes.IsEmpty())
    {
      myReaderStatus = PCDM_RS_TypeNotFoundInSchema;

      Standard_SStream aMsg;
      aMsg << "cannot read: `" << theFileName
           << "' because it contains the following unknown types: ";
      for (i = 1; i <= anUnknownTypes.Length(); i++)
      {
        aMsg << anUnknownTypes(i);
        if (i < anUnknownTypes.Length())
          aMsg << ",";
        else
          aMsg << std::endl;
      }

      throw Standard_Failure(aMsg.str().c_str());
    }
  }

  StdObjMgt_ReadData aReadData(aFileDriver, theHeaderData.NumberOfObjects());

  raiseOnStorageError(aFileDriver->BeginReadRefSection());

  int len = aFileDriver->RefSectionSize();
  for (i = 1; i <= len; i++)
  {
    int           aRef = 0, aType = 0;
    Storage_Error anError;
    try
    {
      OCC_CATCH_SIGNALS
      aFileDriver->ReadReferenceType(aRef, aType);
      anError = Storage_VSOk;
    }
    catch (Storage_StreamTypeMismatchError const&)
    {
      anError = Storage_VSTypeMismatch;
    }

    raiseOnStorageError(anError);

    aReadData.CreatePersistentObject(aRef, anInstantiators(aType));
  }

  raiseOnStorageError(aFileDriver->EndReadRefSection());

  raiseOnStorageError(aFileDriver->BeginReadDataSection());

  for (i = 1; i <= theHeaderData.NumberOfObjects(); i++)
  {
    Storage_Error anError;
    try
    {
      OCC_CATCH_SIGNALS
      aReadData.ReadPersistentObject(i);
      anError = Storage_VSOk;
    }
    catch (Storage_StreamTypeMismatchError const&)
    {
      anError = Storage_VSTypeMismatch;
    }
    catch (Storage_StreamFormatError const&)
    {
      anError = Storage_VSFormatError;
    }
    catch (Storage_StreamReadError const&)
    {
      anError = Storage_VSFormatError;
    }

    raiseOnStorageError(anError);
  }

  raiseOnStorageError(aFileDriver->EndReadDataSection());

  return aReadData.PersistentObject(aRootData.Roots()->First()->Reference());
}

void StdLDrivers_DocumentRetrievalDriver::Read(Standard_IStream&,
                                               const occ::handle<Storage_Data>&,
                                               const occ::handle<CDM_Document>&,
                                               const occ::handle<CDM_Application>&,
                                               const occ::handle<PCDM_ReaderFilter>&,
                                               const Message_ProgressRange&)
{
  throw Standard_NotImplemented(
    "Reading from stream is not supported by StdLDrivers_DocumentRetrievalDriver");
}

void StdLDrivers_DocumentRetrievalDriver::raiseOnStorageError(Storage_Error theError)
{
  Standard_SStream aMsg;

  switch (theError)
  {
    case Storage_VSOk:
      break;

    case Storage_VSOpenError:
    case Storage_VSNotOpen:
    case Storage_VSAlreadyOpen:
      myReaderStatus = PCDM_RS_OpenError;
      aMsg << "Stream Open Error" << std::endl;
      throw Standard_Failure(aMsg.str().c_str());

    case Storage_VSModeError:
      myReaderStatus = PCDM_RS_WrongStreamMode;
      aMsg << "Stream is opened with a wrong mode for operation" << std::endl;
      throw Standard_Failure(aMsg.str().c_str());

    case Storage_VSSectionNotFound:
      myReaderStatus = PCDM_RS_FormatFailure;
      aMsg << "Section is not found" << std::endl;
      throw Standard_Failure(aMsg.str().c_str());

    case Storage_VSFormatError:
      myReaderStatus = PCDM_RS_FormatFailure;
      aMsg << "Wrong format error" << std::endl;
      throw Standard_Failure(aMsg.str().c_str());

    case Storage_VSUnknownType:
      myReaderStatus = PCDM_RS_TypeFailure;
      aMsg << "Try to read an unknown type" << std::endl;
      throw Standard_Failure(aMsg.str().c_str());

    case Storage_VSTypeMismatch:
      myReaderStatus = PCDM_RS_TypeFailure;
      aMsg << "Try to read a wrong primitive type" << std::endl;
      throw Standard_Failure(aMsg.str().c_str());

    default:
      myReaderStatus = PCDM_RS_DriverFailure;
      aMsg << "Retrieval Driver Failure" << std::endl;
      throw Standard_Failure(aMsg.str().c_str());
  }
}

void StdLDrivers_DocumentRetrievalDriver::bindTypes(StdObjMgt_MapOfInstantiators& theMap)
{
  StdLDrivers::BindTypes(theMap);
}
