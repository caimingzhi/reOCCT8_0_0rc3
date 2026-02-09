#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Storage_Error.hpp>
#include <Standard_Transient.hpp>
class Storage_BaseDriver;

class Storage_HeaderData : public Standard_Transient
{

public:
  Standard_EXPORT Storage_HeaderData();

  Standard_EXPORT bool Read(const occ::handle<Storage_BaseDriver>& theDriver);

  Standard_EXPORT TCollection_AsciiString CreationDate() const;

  Standard_EXPORT TCollection_AsciiString StorageVersion() const;

  Standard_EXPORT TCollection_AsciiString SchemaVersion() const;

  Standard_EXPORT TCollection_AsciiString SchemaName() const;

  Standard_EXPORT void SetApplicationVersion(const TCollection_AsciiString& aVersion);

  Standard_EXPORT TCollection_AsciiString ApplicationVersion() const;

  Standard_EXPORT void SetApplicationName(const TCollection_ExtendedString& aName);

  Standard_EXPORT TCollection_ExtendedString ApplicationName() const;

  Standard_EXPORT void SetDataType(const TCollection_ExtendedString& aType);

  Standard_EXPORT TCollection_ExtendedString DataType() const;

  Standard_EXPORT void AddToUserInfo(const TCollection_AsciiString& theUserInfo);

  Standard_EXPORT const NCollection_Sequence<TCollection_AsciiString>& UserInfo() const;

  Standard_EXPORT void AddToComments(const TCollection_ExtendedString& aComment);

  Standard_EXPORT const NCollection_Sequence<TCollection_ExtendedString>& Comments() const;

  Standard_EXPORT int NumberOfObjects() const;

  Standard_EXPORT Storage_Error ErrorStatus() const;

  Standard_EXPORT TCollection_AsciiString ErrorStatusExtension() const;

  Standard_EXPORT void ClearErrorStatus();

  friend class Storage_Schema;

  DEFINE_STANDARD_RTTIEXT(Storage_HeaderData, Standard_Transient)

public:
  Standard_EXPORT void SetNumberOfObjects(const int anObjectNumber);

  Standard_EXPORT void SetStorageVersion(const TCollection_AsciiString& aVersion);

  void SetStorageVersion(const int theVersion)
  {
    SetStorageVersion(TCollection_AsciiString(theVersion));
  }

  Standard_EXPORT void SetCreationDate(const TCollection_AsciiString& aDate);

  Standard_EXPORT void SetSchemaVersion(const TCollection_AsciiString& aVersion);

  Standard_EXPORT void SetSchemaName(const TCollection_AsciiString& aName);

private:
  Standard_EXPORT void SetErrorStatus(const Storage_Error anError);

  Standard_EXPORT void SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt);

  int                                              myNBObj;
  TCollection_AsciiString                          myStorageVersion;
  TCollection_AsciiString                          mySchemaVersion;
  TCollection_AsciiString                          mySchemaName;
  TCollection_AsciiString                          myApplicationVersion;
  TCollection_ExtendedString                       myApplicationName;
  TCollection_ExtendedString                       myDataType;
  TCollection_AsciiString                          myDate;
  NCollection_Sequence<TCollection_AsciiString>    myUserInfo;
  NCollection_Sequence<TCollection_ExtendedString> myComments;
  Storage_Error                                    myErrorStatus;
  TCollection_AsciiString                          myErrorStatusExt;
};
