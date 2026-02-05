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

  //! return the creation date
  Standard_EXPORT TCollection_AsciiString CreationDate() const;

  //! return the Storage package version
  Standard_EXPORT TCollection_AsciiString StorageVersion() const;

  //! get the version of the schema
  Standard_EXPORT TCollection_AsciiString SchemaVersion() const;

  //! get the schema's name
  Standard_EXPORT TCollection_AsciiString SchemaName() const;

  //! set the version of the application
  Standard_EXPORT void SetApplicationVersion(const TCollection_AsciiString& aVersion);

  //! get the version of the application
  Standard_EXPORT TCollection_AsciiString ApplicationVersion() const;

  //! set the name of the application
  Standard_EXPORT void SetApplicationName(const TCollection_ExtendedString& aName);

  //! get the name of the application
  Standard_EXPORT TCollection_ExtendedString ApplicationName() const;

  //! set the data type
  Standard_EXPORT void SetDataType(const TCollection_ExtendedString& aType);

  //! returns data type
  Standard_EXPORT TCollection_ExtendedString DataType() const;

  //! add <theUserInfo> to the user information
  Standard_EXPORT void AddToUserInfo(const TCollection_AsciiString& theUserInfo);

  //! return the user information
  Standard_EXPORT const NCollection_Sequence<TCollection_AsciiString>& UserInfo() const;

  //! add <theUserInfo> to the user information
  Standard_EXPORT void AddToComments(const TCollection_ExtendedString& aComment);

  //! return the user information
  Standard_EXPORT const NCollection_Sequence<TCollection_ExtendedString>& Comments() const;

  //! the number of persistent objects
  //! Return:
  //! the number of persistent objects readed
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
