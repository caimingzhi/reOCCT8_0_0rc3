#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <TCollection_AsciiString.hpp>
#include <OSD_SysType.hpp>

class OSD_Path
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Path();

  Standard_EXPORT OSD_Path(const TCollection_AsciiString& aDependentName,
                           const OSD_SysType              aSysType = OSD_Default);

  Standard_EXPORT OSD_Path(const TCollection_AsciiString& aNode,
                           const TCollection_AsciiString& aUsername,
                           const TCollection_AsciiString& aPassword,
                           const TCollection_AsciiString& aDisk,
                           const TCollection_AsciiString& aTrek,
                           const TCollection_AsciiString& aName,
                           const TCollection_AsciiString& anExtension);

  Standard_EXPORT void Values(TCollection_AsciiString& aNode,
                              TCollection_AsciiString& aUsername,
                              TCollection_AsciiString& aPassword,
                              TCollection_AsciiString& aDisk,
                              TCollection_AsciiString& aTrek,
                              TCollection_AsciiString& aName,
                              TCollection_AsciiString& anExtension) const;

  Standard_EXPORT void SetValues(const TCollection_AsciiString& aNode,
                                 const TCollection_AsciiString& aUsername,
                                 const TCollection_AsciiString& aPassword,
                                 const TCollection_AsciiString& aDisk,
                                 const TCollection_AsciiString& aTrek,
                                 const TCollection_AsciiString& aName,
                                 const TCollection_AsciiString& anExtension);

  Standard_EXPORT void SystemName(TCollection_AsciiString& FullName,
                                  const OSD_SysType        aType = OSD_Default) const;

  Standard_EXPORT void ExpandedName(TCollection_AsciiString& aName);

  Standard_EXPORT static bool IsValid(const TCollection_AsciiString& theDependentName,
                                      const OSD_SysType              theSysType = OSD_Default);

  Standard_EXPORT void UpTrek();

  Standard_EXPORT void DownTrek(const TCollection_AsciiString& aName);

  Standard_EXPORT int TrekLength() const;

  Standard_EXPORT void RemoveATrek(const int where);

  Standard_EXPORT void RemoveATrek(const TCollection_AsciiString& aName);

  Standard_EXPORT TCollection_AsciiString TrekValue(const int where) const;

  Standard_EXPORT void InsertATrek(const TCollection_AsciiString& aName, const int where);

  Standard_EXPORT TCollection_AsciiString Node() const;

  Standard_EXPORT TCollection_AsciiString UserName() const;

  Standard_EXPORT TCollection_AsciiString Password() const;

  Standard_EXPORT TCollection_AsciiString Disk() const;

  Standard_EXPORT TCollection_AsciiString Trek() const;

  Standard_EXPORT TCollection_AsciiString Name() const;

  Standard_EXPORT TCollection_AsciiString Extension() const;

  Standard_EXPORT void SetNode(const TCollection_AsciiString& aName);

  Standard_EXPORT void SetUserName(const TCollection_AsciiString& aName);

  Standard_EXPORT void SetPassword(const TCollection_AsciiString& aName);

  Standard_EXPORT void SetDisk(const TCollection_AsciiString& aName);

  Standard_EXPORT void SetTrek(const TCollection_AsciiString& aName);

  Standard_EXPORT void SetName(const TCollection_AsciiString& aName);

  Standard_EXPORT void SetExtension(const TCollection_AsciiString& aName);

  Standard_EXPORT bool LocateExecFile(OSD_Path& aPath);

public:
  Standard_EXPORT static TCollection_AsciiString RelativePath(
    const TCollection_AsciiString& DirPath,
    const TCollection_AsciiString& AbsFilePath);

  Standard_EXPORT static TCollection_AsciiString AbsolutePath(
    const TCollection_AsciiString& DirPath,
    const TCollection_AsciiString& RelFilePath);

  Standard_EXPORT static void FolderAndFileFromPath(const TCollection_AsciiString& theFilePath,
                                                    TCollection_AsciiString&       theFolder,
                                                    TCollection_AsciiString&       theFileName);

  Standard_EXPORT static void FileNameAndExtension(const TCollection_AsciiString& theFilePath,
                                                   TCollection_AsciiString&       theName,
                                                   TCollection_AsciiString&       theExtension);

  static bool IsDosPath(const char* thePath) { return thePath[0] != '\0' && thePath[1] == ':'; }

  static bool IsNtExtendedPath(const char* thePath)
  {
    return ::strncmp(thePath, "\\\\?\\", 4) == 0;
  }

  static bool IsUncPath(const char* thePath)
  {
    if (::strncmp(thePath, "\\\\", 2) == 0)
    {
      return thePath[2] != '?' || IsUncExtendedPath(thePath);
    }
    return ::strncmp(thePath, "//", 2) == 0;
  }

  static bool IsUncExtendedPath(const char* thePath)
  {
    return ::strncmp(thePath, "\\\\?\\UNC\\", 8) == 0;
  }

  static bool IsUnixPath(const char* thePath) { return thePath[0] == '/' && thePath[1] != '/'; }

  static bool IsContentProtocolPath(const char* thePath)
  {
    return ::strncmp(thePath, "content://", 10) == 0;
  }

  static bool IsRemoteProtocolPath(const char* thePath)
  {
    const char* anIter = thePath;
    if (*anIter == ':')
    {
      return false;
    }
    for (; *anIter != '\0'; ++anIter)
    {
      if (*anIter == ':')
      {
        return *(++anIter) == '/' && *(++anIter) == '/';
      }
    }
    return false;
  }

  static bool IsRelativePath(const char* thePath)
  {
    return !IsUncPath(thePath) && !IsDosPath(thePath) && !IsNtExtendedPath(thePath)
           && !IsUnixPath(thePath) && !IsRemoteProtocolPath(thePath);
  }

  static bool IsAbsolutePath(const char* thePath) { return !IsRelativePath(thePath); }

private:
  TCollection_AsciiString myNode;
  TCollection_AsciiString myUserName;
  TCollection_AsciiString myPassword;
  TCollection_AsciiString myDisk;
  TCollection_AsciiString myTrek;
  TCollection_AsciiString myName;
  TCollection_AsciiString myExtension;
  bool                    myUNCFlag;
  OSD_SysType             mySysDep;
};
