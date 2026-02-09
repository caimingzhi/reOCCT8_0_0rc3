#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Storage_Error.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Storage_Root.hpp>
#include <NCollection_HSequence.hpp>
#include <TCollection_AsciiString.hpp>
class Storage_HeaderData;
class Storage_RootData;
class Storage_TypeData;
class Storage_InternalData;
class TCollection_ExtendedString;
class Standard_Persistent;
class Storage_Root;

class Storage_Data : public Standard_Transient
{

public:
  Standard_EXPORT Storage_Data();

  Standard_EXPORT Storage_Error ErrorStatus() const;

  Standard_EXPORT void ClearErrorStatus();

  Standard_EXPORT TCollection_AsciiString ErrorStatusExtension() const;

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

  Standard_EXPORT void AddToUserInfo(const TCollection_AsciiString& anInfo);

  Standard_EXPORT const NCollection_Sequence<TCollection_AsciiString>& UserInfo() const;

  Standard_EXPORT void AddToComments(const TCollection_ExtendedString& aComment);

  Standard_EXPORT const NCollection_Sequence<TCollection_ExtendedString>& Comments() const;

  Standard_EXPORT int NumberOfObjects() const;

  Standard_EXPORT int NumberOfRoots() const;

  Standard_EXPORT void AddRoot(const occ::handle<Standard_Persistent>& anObject) const;

  Standard_EXPORT void AddRoot(const TCollection_AsciiString&          aName,
                               const occ::handle<Standard_Persistent>& anObject) const;

  Standard_EXPORT void RemoveRoot(const TCollection_AsciiString& aName);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Storage_Root>>> Roots() const;

  Standard_EXPORT occ::handle<Storage_Root> Find(const TCollection_AsciiString& aName) const;

  Standard_EXPORT bool IsRoot(const TCollection_AsciiString& aName) const;

  Standard_EXPORT int NumberOfTypes() const;

  Standard_EXPORT bool IsType(const TCollection_AsciiString& aName) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_AsciiString>> Types() const;

  friend class Storage_Schema;

  DEFINE_STANDARD_RTTIEXT(Storage_Data, Standard_Transient)

  Standard_EXPORT occ::handle<Storage_HeaderData> HeaderData() const;

  Standard_EXPORT occ::handle<Storage_RootData> RootData() const;

  Standard_EXPORT occ::handle<Storage_TypeData> TypeData() const;

  Standard_EXPORT occ::handle<Storage_InternalData> InternalData() const;

  Standard_EXPORT void Clear() const;

private:
  Standard_EXPORT void SetErrorStatus(const Storage_Error anError);

  Standard_EXPORT void SetErrorStatusExtension(const TCollection_AsciiString& anErrorExt);

  occ::handle<Storage_HeaderData>   myHeaderData;
  occ::handle<Storage_RootData>     myRootData;
  occ::handle<Storage_TypeData>     myTypeData;
  occ::handle<Storage_InternalData> myInternal;
  Storage_Error                     myErrorStatus;
  TCollection_AsciiString           myErrorStatusExt;
};
