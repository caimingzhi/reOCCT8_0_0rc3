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

//! Storage header data section that contains some
//! auxiliary information (application name, schema version,
//! creation date, comments and so on...)
class StdStorage_HeaderData : public Standard_Transient
{
  friend class StdStorage_Data;

public:
  DEFINE_STANDARD_RTTIEXT(StdStorage_HeaderData, Standard_Transient)

  //! Reads the header data section from the container defined by theDriver.
  //! Returns true in case of success. Otherwise, one need to get
  //! an error code and description using ErrorStatus and ErrorStatusExtension
  //! functions correspondingly.
  Standard_EXPORT bool Read(const occ::handle<Storage_BaseDriver>& theDriver);

  //! Writes the header data section to the container defined by theDriver.
  //! Returns true in case of success. Otherwise, one need to get
  //! an error code and description using ErrorStatus and ErrorStatusExtension
  //! functions correspondingly.
  Standard_EXPORT bool Write(const occ::handle<Storage_BaseDriver>& theDriver);

  //! Return the creation date
  Standard_EXPORT TCollection_AsciiString CreationDate() const;

  //! Return the Storage package version
  Standard_EXPORT TCollection_AsciiString StorageVersion() const;

  //! Get the version of the schema
  Standard_EXPORT TCollection_AsciiString SchemaVersion() const;

  //! Set the version of the application
  Standard_EXPORT void SetApplicationVersion(const TCollection_AsciiString& aVersion);

  //! Get the version of the application
  Standard_EXPORT TCollection_AsciiString ApplicationVersion() const;

  //! Set the name of the application
  Standard_EXPORT void SetApplicationName(const TCollection_ExtendedString& aName);

  //! Get the name of the application
  Standard_EXPORT TCollection_ExtendedString ApplicationName() const;

  //! Set the data type
  Standard_EXPORT void SetDataType(const TCollection_ExtendedString& aType);

  //! Returns data type
  Standard_EXPORT TCollection_ExtendedString DataType() const;

  //! Add <theUserInfo> to the user information
  Standard_EXPORT void AddToUserInfo(const TCollection_AsciiString& theUserInfo);

  //! Return the user information
  Standard_EXPORT const NCollection_Sequence<TCollection_AsciiString>& UserInfo() const;

  //! Add <theUserInfo> to the user information
  Standard_EXPORT void AddToComments(const TCollection_ExtendedString& aComment);

  //! Return the user information
  Standard_EXPORT const NCollection_Sequence<TCollection_ExtendedString>& Comments() const;

  //! Returns the number of persistent objects
  Standard_EXPORT int NumberOfObjects() const;

  //! Returns a status of the latest call to Read / Write functions
  Standard_EXPORT Storage_Error ErrorStatus() const;

  //! Returns an error message if any of the latest call to Read / Write functions
  Standard_EXPORT TCollection_AsciiString ErrorStatusExtension() const;

  //! Clears error status
  Standard_EXPORT void ClearErrorStatus();

  Standard_EXPORT void SetNumberOfObjects(const int anObjectNumber);

  Standard_EXPORT void SetStorageVersion(const TCollection_AsciiString& aVersion);

  Standard_EXPORT void SetCreationDate(const TCollection_AsciiString& aDate);

  Standard_EXPORT void SetSchemaVersion(const TCollection_AsciiString& aVersion);

  Standard_EXPORT void SetSchemaName(const TCollection_AsciiString& aName);

private:
  Standard_EXPORT StdStorage_HeaderData();

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
