

#include <NCollection_Handle.hpp>
#include <NCollection_Array1.hpp>
#include <PCDM.hpp>
#include <PCDM_ReadWriter.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_NullObject.hpp>
#include <StdObjMgt_Persistent.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>
#include <StdStorage.hpp>
#include <StdStorage_Data.hpp>
#include <StdStorage_HeaderData.hpp>
#include <StdStorage_TypeData.hpp>
#include <StdStorage_RootData.hpp>
#include <StdStorage_Root.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <StdStorage_BacketOfPersistent.hpp>
#include <Storage.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <Storage_StreamFormatError.hpp>
#include <Storage_StreamWriteError.hpp>

#include <cstdio>

TCollection_AsciiString StdStorage::Version()
{
  TCollection_AsciiString v("1.3");
  return v;
}

Storage_Error StdStorage::Read(const TCollection_AsciiString& theFileName,
                               occ::handle<StdStorage_Data>&  theData)
{

  occ::handle<Storage_BaseDriver> aDriver;
  if (PCDM::FileDriverType(theFileName, aDriver) == PCDM_TOFD_Unknown)
    return Storage_VSWrongFileDriver;

  try
  {
    OCC_CATCH_SIGNALS
    PCDM_ReadWriter::Open(aDriver, theFileName, Storage_VSRead);
  }
  catch (Standard_Failure const&)
  {
    return Storage_VSOpenError;
  }

  return Read(aDriver, theData);
}

Storage_Error StdStorage::Read(const occ::handle<Storage_BaseDriver>& theDriver,
                               occ::handle<StdStorage_Data>&          theData)
{
  if (theData.IsNull())
    theData = new StdStorage_Data;
  else
    theData->Clear();

  occ::handle<StdStorage_HeaderData> aHeaderData = theData->HeaderData();
  occ::handle<StdStorage_TypeData>   aTypeData   = theData->TypeData();
  occ::handle<StdStorage_RootData>   aRootData   = theData->RootData();

  if (!aHeaderData->Read(theDriver))
    return aHeaderData->ErrorStatus();

  if (!aTypeData->Read(theDriver))
    return aTypeData->ErrorStatus();

  NCollection_Array1<StdObjMgt_Persistent::Instantiator> anInstantiators(
    1,
    aTypeData->NumberOfTypes());
  for (int i = 1; i <= aTypeData->NumberOfTypes(); i++)
  {
    StdObjMgt_Persistent::Instantiator anInstantiator = aTypeData->Instantiator(i);
    if (anInstantiator)
      anInstantiators(i) = anInstantiator;
    else
      return Storage_VSUnknownType;
  }

  if (!aRootData->Read(theDriver))
    return aRootData->ErrorStatus();

  Storage_Error anError;

  StdObjMgt_ReadData aReadData(theDriver, aHeaderData->NumberOfObjects());

  anError = theDriver->BeginReadRefSection();
  if (anError != Storage_VSOk)
    return anError;

  int aNbRefs = theDriver->RefSectionSize();
  for (int i = 1; i <= aNbRefs; i++)
  {
    int aRef = 0, aType = 0;
    try
    {
      OCC_CATCH_SIGNALS
      theDriver->ReadReferenceType(aRef, aType);
      anError = Storage_VSOk;
    }
    catch (Storage_StreamTypeMismatchError const&)
    {
      anError = Storage_VSTypeMismatch;
    }

    if (anError != Storage_VSOk)
      return anError;

    aReadData.CreatePersistentObject(aRef, anInstantiators(aType));
  }

  anError = theDriver->EndReadRefSection();
  if (anError != Storage_VSOk)
    return anError;

  anError = theDriver->BeginReadDataSection();
  if (anError != Storage_VSOk)
    return anError;

  for (int i = 1; i <= aHeaderData->NumberOfObjects(); i++)
  {
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

    if (anError != Storage_VSOk)
      return anError;
  }

  anError = theDriver->EndReadDataSection();
  if (anError != Storage_VSOk)
    return anError;

  occ::handle<NCollection_HSequence<occ::handle<StdStorage_Root>>> aRoots = aRootData->Roots();
  if (!aRoots.IsNull())
  {
    for (NCollection_HSequence<occ::handle<StdStorage_Root>>::Iterator anIt(*aRoots); anIt.More();
         anIt.Next())
    {
      occ::handle<StdStorage_Root>& aRoot = anIt.ChangeValue();
      aRoot->SetObject(aReadData.PersistentObject(aRoot->Reference()));
    }
  }

  return Storage_VSOk;
}

static TCollection_AsciiString currentDate()
{
#define SLENGTH 80

  char       nowstr[SLENGTH];
  time_t     nowbin;
  struct tm* nowstruct;
  if (time(&nowbin) != (time_t)-1)
  {
    nowstruct = localtime(&nowbin);
    strftime(nowstr, SLENGTH, "%m/%d/%Y", nowstruct);
  }
  TCollection_AsciiString t(nowstr);
  return t;

#undef SLENGTH
}

Storage_Error StdStorage::Write(const occ::handle<Storage_BaseDriver>& theDriver,
                                const occ::handle<StdStorage_Data>&    theData)
{
  Standard_NullObject_Raise_if(theData.IsNull(), "Null storage data");

  occ::handle<StdStorage_HeaderData> aHeaderData = theData->HeaderData();
  occ::handle<StdStorage_TypeData>   aTypeData   = theData->TypeData();
  occ::handle<StdStorage_RootData>   aRootData   = theData->RootData();

  aHeaderData->SetCreationDate(currentDate());

  occ::handle<NCollection_HSequence<occ::handle<StdStorage_Root>>> aRoots = aRootData->Roots();

  StdStorage_BucketOfPersistent aPObjs;

  if (!aRoots.IsNull())
  {
    StdObjMgt_Persistent::SequenceOfPersistent aPQueue;
    for (NCollection_HSequence<occ::handle<StdStorage_Root>>::Iterator anIt(*aRoots); anIt.More();
         anIt.Next())
    {
      occ::handle<StdStorage_Root>      aRoot = anIt.ChangeValue();
      occ::handle<StdObjMgt_Persistent> aPObj = aRoot->Object();
      if (!aPObj.IsNull())
      {
        aPQueue.Append(aPObj);
      }
    }
    while (!aPQueue.IsEmpty())
    {
      StdObjMgt_Persistent::SequenceOfPersistent aPQueue1;
      for (StdObjMgt_Persistent::SequenceOfPersistent::Iterator anIt(aPQueue); anIt.More();
           anIt.Next())
      {
        occ::handle<StdObjMgt_Persistent>& aPObj = anIt.ChangeValue();
        if (!aPObj.IsNull())
        {
          if (aPObj->TypeNum() == 0 && aPObj->RefNum() == 0)
          {
            aPObj->TypeNum(aTypeData->AddType(aPObj));
            int anPObjId = aPObjs.Length() + 1;
            aPObj->RefNum(anPObjId);
            aPObjs.Append(aPObj);
            aPObj->PChildren(aPQueue1);
          }
        }
      }
      aPQueue.Assign(aPQueue1);
    }
  }

  aHeaderData->SetStorageVersion(StdStorage::Version());
  aHeaderData->SetNumberOfObjects(aPObjs.Length());

  try
  {

    if (!aHeaderData->Write(theDriver))
      return aHeaderData->ErrorStatus();

    if (!aTypeData->Write(theDriver))
      return aTypeData->ErrorStatus();

    if (!aRootData->Write(theDriver))
      return aRootData->ErrorStatus();

    Storage_Error anError;

    anError = theDriver->BeginWriteRefSection();
    if (anError != Storage_VSOk)
      return anError;

    theDriver->SetRefSectionSize(aPObjs.Length());
    for (StdStorage_BucketIterator anIt(&aPObjs); anIt.More(); anIt.Next())
    {
      occ::handle<StdObjMgt_Persistent> aPObj = anIt.Value();
      if (!aPObj.IsNull())
        theDriver->WriteReferenceType(aPObj->RefNum(), aPObj->TypeNum());
    }

    anError = theDriver->EndWriteRefSection();
    if (anError != Storage_VSOk)
      return anError;

    anError = theDriver->BeginWriteDataSection();
    if (anError != Storage_VSOk)
      return anError;

    StdObjMgt_WriteData aWriteData(theDriver);
    for (StdStorage_BucketIterator anIt(&aPObjs); anIt.More(); anIt.Next())
    {
      occ::handle<StdObjMgt_Persistent> aPObj = anIt.Value();
      if (!aPObj.IsNull())
        aWriteData.WritePersistentObject(aPObj);
    }

    anError = theDriver->EndWriteDataSection();
    if (anError != Storage_VSOk)
      return anError;
  }
  catch (Storage_StreamWriteError const&)
  {
    return Storage_VSWriteError;
  }

  return Storage_VSOk;
}
