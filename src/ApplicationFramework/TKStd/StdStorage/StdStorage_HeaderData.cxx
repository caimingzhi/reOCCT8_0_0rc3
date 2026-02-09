

#include <Standard_ErrorHandler.hpp>
#include <StdStorage_HeaderData.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <Storage_StreamExtCharParityError.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdStorage_HeaderData, Standard_Transient)

StdStorage_HeaderData::StdStorage_HeaderData()
    : myNBObj(0),
      myErrorStatus(Storage_VSOk)
{
}

bool StdStorage_HeaderData::Read(const occ::handle<Storage_BaseDriver>& theDriver)
{

  if (theDriver->OpenMode() != Storage_VSRead && theDriver->OpenMode() != Storage_VSReadWrite)
  {
    myErrorStatus    = Storage_VSModeError;
    myErrorStatusExt = "OpenMode";
    return false;
  }

  myErrorStatus = theDriver->BeginReadInfoSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "BeginReadInfoSection";
    return false;
  }

  try
  {
    OCC_CATCH_SIGNALS
    theDriver->ReadInfo(myNBObj,
                        myStorageVersion,
                        myDate,
                        mySchemaName,
                        mySchemaVersion,
                        myApplicationName,
                        myApplicationVersion,
                        myDataType,
                        myUserInfo);
  }
  catch (Storage_StreamTypeMismatchError const&)
  {
    myErrorStatus    = Storage_VSTypeMismatch;
    myErrorStatusExt = "ReadInfo";
    return false;
  }
  catch (Storage_StreamExtCharParityError const&)
  {
    myErrorStatus    = Storage_VSExtCharParityError;
    myErrorStatusExt = "ReadInfo";
    return false;
  }

  myErrorStatus = theDriver->EndReadInfoSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "EndReadInfoSection";
    return false;
  }

  myErrorStatus = theDriver->BeginReadCommentSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "BeginReadCommentSection";
    return false;
  }

  try
  {
    OCC_CATCH_SIGNALS
    theDriver->ReadComment(myComments);
  }
  catch (Storage_StreamTypeMismatchError const&)
  {
    myErrorStatus    = Storage_VSTypeMismatch;
    myErrorStatusExt = "ReadComment";
    return false;
  }
  catch (Storage_StreamExtCharParityError const&)
  {
    myErrorStatus    = Storage_VSExtCharParityError;
    myErrorStatusExt = "ReadComment";
    return false;
  }

  myErrorStatus = theDriver->EndReadCommentSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "EndReadCommentSection";
    return false;
  }

  return true;
}

bool StdStorage_HeaderData::Write(const occ::handle<Storage_BaseDriver>& theDriver)
{

  if (theDriver->OpenMode() != Storage_VSWrite && theDriver->OpenMode() != Storage_VSReadWrite)
  {
    myErrorStatus    = Storage_VSModeError;
    myErrorStatusExt = "OpenMode";
    return false;
  }

  myErrorStatus = theDriver->BeginWriteInfoSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "BeginWriteInfoSection";
    return false;
  }

  try
  {
    OCC_CATCH_SIGNALS
    theDriver->WriteInfo(myNBObj,
                         myStorageVersion,
                         myDate,
                         mySchemaName,
                         mySchemaVersion,
                         myApplicationName,
                         myApplicationVersion,
                         myDataType,
                         myUserInfo);
  }
  catch (Storage_StreamTypeMismatchError const&)
  {
    myErrorStatus    = Storage_VSTypeMismatch;
    myErrorStatusExt = "WriteInfo";
    return false;
  }
  catch (Storage_StreamExtCharParityError const&)
  {
    myErrorStatus    = Storage_VSExtCharParityError;
    myErrorStatusExt = "WriteInfo";
    return false;
  }

  myErrorStatus = theDriver->EndWriteInfoSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "EndWriteInfoSection";
    return false;
  }

  myErrorStatus = theDriver->BeginWriteCommentSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "BeginWriteCommentSection";
    return false;
  }

  try
  {
    OCC_CATCH_SIGNALS
    theDriver->WriteComment(myComments);
  }
  catch (Storage_StreamTypeMismatchError const&)
  {
    myErrorStatus    = Storage_VSTypeMismatch;
    myErrorStatusExt = "WriteComment";
    return false;
  }
  catch (Storage_StreamExtCharParityError const&)
  {
    myErrorStatus    = Storage_VSExtCharParityError;
    myErrorStatusExt = "WriteComment";
    return false;
  }

  myErrorStatus = theDriver->EndWriteCommentSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "EndWriteCommentSection";
    return false;
  }

  return true;
}

TCollection_AsciiString StdStorage_HeaderData::CreationDate() const
{
  return myDate;
}

void StdStorage_HeaderData::SetSchemaVersion(const TCollection_AsciiString& aVersion)
{
  mySchemaVersion = aVersion;
}

TCollection_AsciiString StdStorage_HeaderData::SchemaVersion() const
{
  return mySchemaVersion;
}

void StdStorage_HeaderData::SetSchemaName(const TCollection_AsciiString& aSchemaName)
{
  mySchemaName = aSchemaName;
}

void StdStorage_HeaderData::SetApplicationVersion(const TCollection_AsciiString& aVersion)
{
  myApplicationVersion = aVersion;
}

TCollection_AsciiString StdStorage_HeaderData::ApplicationVersion() const
{
  return myApplicationVersion;
}

void StdStorage_HeaderData::SetApplicationName(const TCollection_ExtendedString& aName)
{
  myApplicationName = aName;
}

TCollection_ExtendedString StdStorage_HeaderData::ApplicationName() const
{
  return myApplicationName;
}

void StdStorage_HeaderData::SetDataType(const TCollection_ExtendedString& aName)
{
  myDataType = aName;
}

TCollection_ExtendedString StdStorage_HeaderData::DataType() const
{
  return myDataType;
}

void StdStorage_HeaderData::AddToUserInfo(const TCollection_AsciiString& theUserInfo)
{
  myUserInfo.Append(theUserInfo);
}

const NCollection_Sequence<TCollection_AsciiString>& StdStorage_HeaderData::UserInfo() const
{
  return myUserInfo;
}

void StdStorage_HeaderData::AddToComments(const TCollection_ExtendedString& aComments)
{
  myComments.Append(aComments);
}

const NCollection_Sequence<TCollection_ExtendedString>& StdStorage_HeaderData::Comments() const
{
  return myComments;
}

int StdStorage_HeaderData::NumberOfObjects() const
{
  return myNBObj;
}

void StdStorage_HeaderData::SetNumberOfObjects(const int anObjectNumber)
{
  myNBObj = anObjectNumber;
}

void StdStorage_HeaderData::SetStorageVersion(const TCollection_AsciiString& v)
{
  myStorageVersion = v;
}

void StdStorage_HeaderData::SetCreationDate(const TCollection_AsciiString& d)
{
  myDate = d;
}

TCollection_AsciiString StdStorage_HeaderData::StorageVersion() const
{
  return myStorageVersion;
}

Storage_Error StdStorage_HeaderData::ErrorStatus() const
{
  return myErrorStatus;
}

void StdStorage_HeaderData::SetErrorStatus(const Storage_Error anError)
{
  myErrorStatus = anError;
}

TCollection_AsciiString StdStorage_HeaderData::ErrorStatusExtension() const
{
  return myErrorStatusExt;
}

void StdStorage_HeaderData::SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt)
{
  myErrorStatusExt = anErrorExt;
}

void StdStorage_HeaderData::ClearErrorStatus()
{
  myErrorStatus = Storage_VSOk;
  myErrorStatusExt.Clear();
}
