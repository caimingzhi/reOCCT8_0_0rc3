

#include <Standard_ErrorHandler.hpp>
#include <Storage_HeaderData.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <Storage_StreamExtCharParityError.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_HeaderData, Standard_Transient)

app::storage::Storage_HeaderData::Storage_HeaderData()
    : myNBObj(0),
      myErrorStatus(Storage_VSOk)
{
}

bool app::storage::Storage_HeaderData::Read(const occ::handle<app::storage::Storage_BaseDriver>& theDriver)
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

  {
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
    catch (app::storage::Storage_StreamTypeMismatchError const&)
    {
      myErrorStatus    = Storage_VSTypeMismatch;
      myErrorStatusExt = "ReadInfo";
      return false;
    }
    catch (app::storage::Storage_StreamExtCharParityError const&)
    {
      myErrorStatus    = Storage_VSExtCharParityError;
      myErrorStatusExt = "ReadInfo";
      return false;
    }
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

  {
    try
    {
      OCC_CATCH_SIGNALS
      theDriver->ReadComment(myComments);
    }
    catch (app::storage::Storage_StreamTypeMismatchError const&)
    {
      myErrorStatus    = Storage_VSTypeMismatch;
      myErrorStatusExt = "ReadComment";
      return false;
    }
    catch (app::storage::Storage_StreamExtCharParityError const&)
    {
      myErrorStatus    = Storage_VSExtCharParityError;
      myErrorStatusExt = "ReadComment";
      return false;
    }
  }

  myErrorStatus = theDriver->EndReadCommentSection();
  if (myErrorStatus != Storage_VSOk)
  {
    myErrorStatusExt = "EndReadCommentSection";
    return false;
  }

  return true;
}

TCollection_AsciiString app::storage::Storage_HeaderData::CreationDate() const
{
  return myDate;
}

void app::storage::Storage_HeaderData::SetSchemaVersion(const TCollection_AsciiString& aVersion)
{
  mySchemaVersion = aVersion;
}

TCollection_AsciiString app::storage::Storage_HeaderData::SchemaVersion() const
{
  return mySchemaVersion;
}

void app::storage::Storage_HeaderData::SetSchemaName(const TCollection_AsciiString& aSchemaName)
{
  mySchemaName = aSchemaName;
}

TCollection_AsciiString app::storage::Storage_HeaderData::SchemaName() const
{
  return mySchemaName;
}

void app::storage::Storage_HeaderData::SetApplicationVersion(const TCollection_AsciiString& aVersion)
{
  myApplicationVersion = aVersion;
}

TCollection_AsciiString app::storage::Storage_HeaderData::ApplicationVersion() const
{
  return myApplicationVersion;
}

void app::storage::Storage_HeaderData::SetApplicationName(const TCollection_ExtendedString& aName)
{
  myApplicationName = aName;
}

TCollection_ExtendedString app::storage::Storage_HeaderData::ApplicationName() const
{
  return myApplicationName;
}

void app::storage::Storage_HeaderData::SetDataType(const TCollection_ExtendedString& aName)
{
  myDataType = aName;
}

TCollection_ExtendedString app::storage::Storage_HeaderData::DataType() const
{
  return myDataType;
}

void app::storage::Storage_HeaderData::AddToUserInfo(const TCollection_AsciiString& theUserInfo)
{
  myUserInfo.Append(theUserInfo);
}

const NCollection_Sequence<TCollection_AsciiString>& app::storage::Storage_HeaderData::UserInfo() const
{
  return myUserInfo;
}

void app::storage::Storage_HeaderData::AddToComments(const TCollection_ExtendedString& aComments)
{
  myComments.Append(aComments);
}

const NCollection_Sequence<TCollection_ExtendedString>& app::storage::Storage_HeaderData::Comments() const
{
  return myComments;
}

int app::storage::Storage_HeaderData::NumberOfObjects() const
{
  return myNBObj;
}

void app::storage::Storage_HeaderData::SetNumberOfObjects(const int anObjectNumber)
{
  myNBObj = anObjectNumber;
}

void app::storage::Storage_HeaderData::SetStorageVersion(const TCollection_AsciiString& v)
{
  myStorageVersion = v;
}

void app::storage::Storage_HeaderData::SetCreationDate(const TCollection_AsciiString& d)
{
  myDate = d;
}

TCollection_AsciiString app::storage::Storage_HeaderData::StorageVersion() const
{
  return myStorageVersion;
}

Storage_Error app::storage::Storage_HeaderData::ErrorStatus() const
{
  return myErrorStatus;
}

void app::storage::Storage_HeaderData::SetErrorStatus(const Storage_Error anError)
{
  myErrorStatus = anError;
}

TCollection_AsciiString app::storage::Storage_HeaderData::ErrorStatusExtension() const
{
  return myErrorStatusExt;
}

void app::storage::Storage_HeaderData::SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt)
{
  myErrorStatusExt = anErrorExt;
}

void app::storage::Storage_HeaderData::ClearErrorStatus()
{
  myErrorStatus = Storage_VSOk;
  myErrorStatusExt.Clear();
}
