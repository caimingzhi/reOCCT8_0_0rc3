#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <Storage_Error.hpp>
#include <Storage_OpenMode.hpp>
#include <Standard_Integer.hpp>
class TCollection_ExtendedString;
class Storage_BaseDriver;
class Storage_Data;
class OSD_Path;
class OSD_FileIterator;
class TCollection_AsciiString;
class Standard_GUID;
class Resource_Manager;

class UTL
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TCollection_ExtendedString xgetenv(const char* aCString);

  Standard_EXPORT static Storage_Error OpenFile(const occ::handle<Storage_BaseDriver>& aFile,
                                                const TCollection_ExtendedString&      aName,
                                                const Storage_OpenMode                 aMode);

  Standard_EXPORT static void AddToUserInfo(const occ::handle<Storage_Data>&  aData,
                                            const TCollection_ExtendedString& anInfo);

  Standard_EXPORT static OSD_Path Path(const TCollection_ExtendedString& aFileName);

  Standard_EXPORT static TCollection_ExtendedString Disk(const OSD_Path& aPath);

  Standard_EXPORT static TCollection_ExtendedString Trek(const OSD_Path& aPath);

  Standard_EXPORT static TCollection_ExtendedString Name(const OSD_Path& aPath);

  Standard_EXPORT static TCollection_ExtendedString Extension(const OSD_Path& aPath);

  Standard_EXPORT static OSD_FileIterator FileIterator(const OSD_Path&                   aPath,
                                                       const TCollection_ExtendedString& aMask);

  Standard_EXPORT static TCollection_ExtendedString Extension(
    const TCollection_ExtendedString& aFileName);

  Standard_EXPORT static TCollection_ExtendedString LocalHost();

  Standard_EXPORT static TCollection_ExtendedString ExtendedString(
    const TCollection_AsciiString& anAsciiString);

  Standard_EXPORT static Standard_GUID GUID(const TCollection_ExtendedString& anXString);

  Standard_EXPORT static bool Find(const occ::handle<Resource_Manager>& aResourceManager,
                                   const TCollection_ExtendedString&    aResourceName);

  Standard_EXPORT static TCollection_ExtendedString Value(
    const occ::handle<Resource_Manager>& aResourceManager,
    const TCollection_ExtendedString&    aResourceName);

  Standard_EXPORT static int IntegerValue(const TCollection_ExtendedString& anExtendedString);

  Standard_EXPORT static const char* CString(const TCollection_ExtendedString& anExtendedString);

  Standard_EXPORT static bool IsReadOnly(const TCollection_ExtendedString& aFileName);
};
