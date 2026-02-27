

#include <Standard_Persistent.hpp>
#include <Standard_Type.hpp>
#include <Storage_Data.hpp>
#include <Storage_HeaderData.hpp>
#include <Storage_Root.hpp>
#include <Storage_RootData.hpp>
#include <Storage_Schema.hpp>
#include <Storage_TypeData.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_Data, Standard_Transient)

app::storage::Storage_Data::Storage_Data()
{
  myRootData   = new app::storage::Storage_RootData;
  myTypeData   = new app::storage::Storage_TypeData;
  myInternal   = new app::storage::Storage_InternalData;
  myHeaderData = new app::storage::Storage_HeaderData;
}

void app::storage::Storage_Data::AddRoot(const occ::handle<Standard_Persistent>& anObject) const
{
  occ::handle<app::storage::Storage_Root> aRoot =
    new app::storage::Storage_Root(TCollection_AsciiString(myRootData->NumberOfRoots() + 1), anObject);
  myRootData->AddRoot(aRoot);
}

void app::storage::Storage_Data::AddRoot(const TCollection_AsciiString&          aName,
                           const occ::handle<Standard_Persistent>& anObject) const
{
  occ::handle<app::storage::Storage_Root> aRoot = new app::storage::Storage_Root(aName, anObject);
  myRootData->AddRoot(aRoot);
}

void app::storage::Storage_Data::RemoveRoot(const TCollection_AsciiString& anObject)
{
  myRootData->RemoveRoot(anObject);
}

occ::handle<app::storage::Storage_Root> app::storage::Storage_Data::Find(const TCollection_AsciiString& aName) const
{
  return myRootData->Find(aName);
}

int app::storage::Storage_Data::NumberOfRoots() const
{
  return myRootData->NumberOfRoots();
}

bool app::storage::Storage_Data::IsRoot(const TCollection_AsciiString& aName) const
{
  return myRootData->IsRoot(aName);
}

occ::handle<NCollection_HSequence<occ::handle<app::storage::Storage_Root>>> app::storage::Storage_Data::Roots() const
{
  return myRootData->Roots();
}

int app::storage::Storage_Data::NumberOfTypes() const
{
  return myTypeData->NumberOfTypes();
}

bool app::storage::Storage_Data::IsType(const TCollection_AsciiString& aName) const
{
  return myTypeData->IsType(aName);
}

occ::handle<NCollection_HSequence<TCollection_AsciiString>> app::storage::Storage_Data::Types() const
{
  return myTypeData->Types();
}

occ::handle<app::storage::Storage_RootData> app::storage::Storage_Data::RootData() const
{
  return myRootData;
}

occ::handle<app::storage::Storage_TypeData> app::storage::Storage_Data::TypeData() const
{
  return myTypeData;
}

occ::handle<app::storage::Storage_InternalData> app::storage::Storage_Data::InternalData() const
{
  return myInternal;
}

occ::handle<app::storage::Storage_HeaderData> app::storage::Storage_Data::HeaderData() const
{
  return myHeaderData;
}

void app::storage::Storage_Data::Clear() const
{
  myInternal->Clear();
  myTypeData->Clear();
}

TCollection_AsciiString app::storage::Storage_Data::CreationDate() const
{
  return myHeaderData->CreationDate();
}

TCollection_AsciiString app::storage::Storage_Data::SchemaVersion() const
{
  return myHeaderData->SchemaVersion();
}

TCollection_AsciiString app::storage::Storage_Data::SchemaName() const
{
  return myHeaderData->SchemaName();
}

void app::storage::Storage_Data::SetApplicationVersion(const TCollection_AsciiString& aVersion)
{
  myHeaderData->SetApplicationVersion(aVersion);
}

TCollection_AsciiString app::storage::Storage_Data::ApplicationVersion() const
{
  return myHeaderData->ApplicationVersion();
}

void app::storage::Storage_Data::SetApplicationName(const TCollection_ExtendedString& aName)
{
  myHeaderData->SetApplicationName(aName);
}

TCollection_ExtendedString app::storage::Storage_Data::ApplicationName() const
{
  return myHeaderData->ApplicationName();
}

void app::storage::Storage_Data::AddToUserInfo(const TCollection_AsciiString& theUserInfo)
{
  myHeaderData->AddToUserInfo(theUserInfo);
}

const NCollection_Sequence<TCollection_AsciiString>& app::storage::Storage_Data::UserInfo() const
{
  return myHeaderData->UserInfo();
}

void app::storage::Storage_Data::AddToComments(const TCollection_ExtendedString& theUserInfo)
{
  myHeaderData->AddToComments(theUserInfo);
}

const NCollection_Sequence<TCollection_ExtendedString>& app::storage::Storage_Data::Comments() const
{
  return myHeaderData->Comments();
}

int app::storage::Storage_Data::NumberOfObjects() const
{
  return myHeaderData->NumberOfObjects();
}

TCollection_AsciiString app::storage::Storage_Data::StorageVersion() const
{
  return myHeaderData->StorageVersion();
}

Storage_Error app::storage::Storage_Data::ErrorStatus() const
{
  return myErrorStatus;
}

void app::storage::Storage_Data::SetErrorStatus(const Storage_Error anError)
{
  myErrorStatus = anError;
}

void app::storage::Storage_Data::ClearErrorStatus()
{
  myErrorStatus = Storage_VSOk;
  myErrorStatusExt.Clear();
  myHeaderData->ClearErrorStatus();
  myRootData->ClearErrorStatus();
  myTypeData->ClearErrorStatus();
}

void app::storage::Storage_Data::SetDataType(const TCollection_ExtendedString& aName)
{
  myHeaderData->SetDataType(aName);
}

TCollection_ExtendedString app::storage::Storage_Data::DataType() const
{
  return myHeaderData->DataType();
}

TCollection_AsciiString app::storage::Storage_Data::ErrorStatusExtension() const
{
  return myErrorStatusExt;
}

void app::storage::Storage_Data::SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt)
{
  myErrorStatusExt = anErrorExt;
}
