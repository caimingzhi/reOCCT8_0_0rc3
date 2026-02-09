

#include <OSD_Directory.hpp>

#include <OSD_Path.hpp>
#include <OSD_Protection.hpp>
#include <OSD_WhoAmI.hpp>
#include <Standard_ProgramError.hpp>
#include <TCollection_ExtendedString.hpp>

#ifdef _WIN32
  #include <OSD_WNT.hpp>
  #include <stdio.h>

  #ifndef _INC_TCHAR
    #include <tchar.h>
  #endif

void _osd_wnt_set_error(OSD_Error&, int, ...);
#else
  #include <cerrno>
  #include <cstdio>
  #include <sys/stat.h>
  #include <unistd.h>

const OSD_WhoAmI Iam = OSD_WDirectory;
#endif

OSD_Directory::OSD_Directory() = default;

OSD_Directory::OSD_Directory(const OSD_Path& theName)
    : OSD_FileNode(theName)
{
}

void OSD_Directory::Build(const OSD_Protection& theProtect)
{
#ifdef _WIN32
  TCollection_AsciiString aDirName;
  myPath.SystemName(aDirName);
  if (aDirName.IsEmpty())
  {
    throw Standard_ProgramError("OSD_Directory::Build(): incorrect call - no directory name");
  }

  bool isOK = Exists();
  if (!isOK)
  {

    myError.Reset();

    TCollection_ExtendedString aDirNameW(aDirName);
    if (CreateDirectoryW(aDirNameW.ToWideString(), NULL))
    {
      isOK = true;
    }

    else if (GetLastError() == ERROR_PATH_NOT_FOUND)
    {
      OSD_Path aSupPath = myPath;
      aSupPath.UpTrek();
      aSupPath.SetName(myPath.TrekValue(myPath.TrekLength()));
      OSD_Directory aSupDir(aSupPath);
      aSupDir.Build(theProtect);
      if (aSupDir.Failed())
      {
        myError = aSupDir.myError;
        return;
      }
      isOK = (CreateDirectoryW(aDirNameW.ToWideString(), NULL) != 0);
    }
  }

  if (isOK)
  {
  #ifndef OCCT_UWP
    SetProtection(theProtect);
  #else
    (void)theProtect;
  #endif
  }
  else
  {
    _osd_wnt_set_error(myError, OSD_WDirectory);
  }
#else
  errno = 0;
  TCollection_AsciiString aBuffer;
  mode_t                  anInternalProt = (mode_t)theProtect.Internal();
  myPath.SystemName(aBuffer);
  umask(0);
  int aStatus = mkdir(aBuffer.ToCString(), anInternalProt);
  if (aStatus == -1 && errno == ENOENT)
  {
    OSD_Path aSupPath = myPath;
    aSupPath.UpTrek();
    aSupPath.SetName(myPath.TrekValue(myPath.TrekLength()));
    OSD_Directory aSupDir(aSupPath);
    aSupDir.Build(theProtect);
    if (aSupDir.Failed())
    {
      myError = aSupDir.myError;
      return;
    }
    aStatus = mkdir(aBuffer.ToCString(), anInternalProt);
  }
  if (aStatus == -1 && errno != EEXIST)
  {
    char anErrMsg[2048];
    Sprintf(anErrMsg, "OSD_Directory::Build Directory \"%.2000s\"", aBuffer.ToCString());
    myError.SetValue(errno, Iam, anErrMsg);
  }
#endif
}

OSD_Directory OSD_Directory::BuildTemporary()
{
#ifdef _WIN32
  wchar_t* aTmpNameW = _wtmpnam(NULL);
  if (aTmpNameW == NULL)
  {
    return OSD_Directory();
  }

  TCollection_AsciiString aTmpName(aTmpNameW);
  OSD_Path                aDirPath(aTmpName);
  OSD_Directory           aDir;
  aDir.SetPath(aDirPath);
  aDir.Build(OSD_Protection());
  return aDir;
#else

  char aTmpName[] = "/tmp/CSFXXXXXX";
  if (nullptr == mkdtemp(aTmpName))
  {
    return OSD_Directory();
  }

  unlink(aTmpName);
  OSD_Directory aDir;
  aDir.SetPath(TCollection_AsciiString(aTmpName));
  return aDir;
#endif
}
