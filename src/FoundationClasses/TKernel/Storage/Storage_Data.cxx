

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

IMPLEMENT_STANDARD_RTTIEXT(Storage_Data, Standard_Transient)

Storage_Data::Storage_Data()
{
  myRootData   = new Storage_RootData;
  myTypeData   = new Storage_TypeData;
  myInternal   = new Storage_InternalData;
  myHeaderData = new Storage_HeaderData;
}

void Storage_Data::AddRoot(const occ::handle<Standard_Persistent>& anObject) const
{
  occ::handle<Storage_Root> aRoot =
    new Storage_Root(TCollection_AsciiString(myRootData->NumberOfRoots() + 1), anObject);
  myRootData->AddRoot(aRoot);
}

void Storage_Data::AddRoot(const TCollection_AsciiString&          aName,
                           const occ::handle<Standard_Persistent>& anObject) const
{
  occ::handle<Storage_Root> aRoot = new Storage_Root(aName, anObject);
  myRootData->AddRoot(aRoot);
}

void Storage_Data::RemoveRoot(const TCollection_AsciiString& anObject)
{
  myRootData->RemoveRoot(anObject);
}

occ::handle<Storage_Root> Storage_Data::Find(const TCollection_AsciiString& aName) const
{
  return myRootData->Find(aName);
}

int Storage_Data::NumberOfRoots() const
{
  return myRootData->NumberOfRoots();
}

bool Storage_Data::IsRoot(const TCollection_AsciiString& aName) const
{
  return myRootData->IsRoot(aName);
}

occ::handle<NCollection_HSequence<occ::handle<Storage_Root>>> Storage_Data::Roots() const
{
  return myRootData->Roots();
}

int Storage_Data::NumberOfTypes() const
{
  return myTypeData->NumberOfTypes();
}

bool Storage_Data::IsType(const TCollection_AsciiString& aName) const
{
  return myTypeData->IsType(aName);
}

occ::handle<NCollection_HSequence<TCollection_AsciiString>> Storage_Data::Types() const
{
  return myTypeData->Types();
}

occ::handle<Storage_RootData> Storage_Data::RootData() const
{
  return myRootData;
}

occ::handle<Storage_TypeData> Storage_Data::TypeData() const
{
  return myTypeData;
}

occ::handle<Storage_InternalData> Storage_Data::InternalData() const
{
  return myInternal;
}

occ::handle<Storage_HeaderData> Storage_Data::HeaderData() const
{
  return myHeaderData;
}

void Storage_Data::Clear() const
{
  myInternal->Clear();
  myTypeData->Clear();
}

TCollection_AsciiString Storage_Data::CreationDate() const
{
  return myHeaderData->CreationDate();
}

TCollection_AsciiString Storage_Data::SchemaVersion() const
{
  return myHeaderData->SchemaVersion();
}

TCollection_AsciiString Storage_Data::SchemaName() const
{
  return myHeaderData->SchemaName();
}

void Storage_Data::SetApplicationVersion(const TCollection_AsciiString& aVersion)
{
  myHeaderData->SetApplicationVersion(aVersion);
}

TCollection_AsciiString Storage_Data::ApplicationVersion() const
{
  return myHeaderData->ApplicationVersion();
}

void Storage_Data::SetApplicationName(const TCollection_ExtendedString& aName)
{
  myHeaderData->SetApplicationName(aName);
}

TCollection_ExtendedString Storage_Data::ApplicationName() const
{
  return myHeaderData->ApplicationName();
}

void Storage_Data::AddToUserInfo(const TCollection_AsciiString& theUserInfo)
{
  myHeaderData->AddToUserInfo(theUserInfo);
}

const NCollection_Sequence<TCollection_AsciiString>& Storage_Data::UserInfo() const
{
  return myHeaderData->UserInfo();
}

void Storage_Data::AddToComments(const TCollection_ExtendedString& theUserInfo)
{
  myHeaderData->AddToComments(theUserInfo);
}

const NCollection_Sequence<TCollection_ExtendedString>& Storage_Data::Comments() const
{
  return myHeaderData->Comments();
}

int Storage_Data::NumberOfObjects() const
{
  return myHeaderData->NumberOfObjects();
}

TCollection_AsciiString Storage_Data::StorageVersion() const
{
  return myHeaderData->StorageVersion();
}

Storage_Error Storage_Data::ErrorStatus() const
{
  return myErrorStatus;
}

void Storage_Data::SetErrorStatus(const Storage_Error anError)
{
  myErrorStatus = anError;
}

void Storage_Data::ClearErrorStatus()
{
  myErrorStatus = Storage_VSOk;
  myErrorStatusExt.Clear();
  myHeaderData->ClearErrorStatus();
  myRootData->ClearErrorStatus();
  myTypeData->ClearErrorStatus();
}

void Storage_Data::SetDataType(const TCollection_ExtendedString& aName)
{
  myHeaderData->SetDataType(aName);
}

TCollection_ExtendedString Storage_Data::DataType() const
{
  return myHeaderData->DataType();
}

TCollection_AsciiString Storage_Data::ErrorStatusExtension() const
{
  return myErrorStatusExt;
}

void Storage_Data::SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt)
{
  myErrorStatusExt = anErrorExt;
}
