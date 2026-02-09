

#include <OSD_FileNode.hpp>

#include <OSD_Protection.hpp>
#include <Quantity_Date.hpp>
#include <Standard_ProgramError.hpp>

#ifndef _WIN32

  #include <OSD_OSDError.hpp>
  #include <OSD_Path.hpp>
  #include <OSD_WhoAmI.hpp>
  #include <Standard_NullObject.hpp>

  #include <cerrno>
  #include <fcntl.h>
  #include <cstdio>
  #include <cstdlib>
  #include <sys/stat.h>
  #include <unistd.h>

const OSD_WhoAmI Iam = OSD_WFileNode;

OSD_FileNode::OSD_FileNode() = default;

OSD_FileNode::OSD_FileNode(const OSD_Path& Name)
{
  SetPath(Name);
}

void OSD_FileNode::Path(OSD_Path& Name) const
{
  Name = myPath;
}

void OSD_FileNode::SetPath(const OSD_Path& Name)
{
  myError.Reset();
  myPath = Name;
}

bool OSD_FileNode::Exists()
{
  int status;

  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);
  status = access(aBuffer.ToCString(), F_OK);

  if (status == 0)
    return (true);
  else
    return (false);
}

void OSD_FileNode::Remove()
{

  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);

  if (access(aBuffer.ToCString(), W_OK))
  {
    myError.SetValue(errno, Iam, "Remove");
    return;
  }

  struct stat stat_buf;

  if (stat(aBuffer.ToCString(), &stat_buf))
  {
    myError.SetValue(errno, Iam, "Remove");
    return;
  }

  if (S_ISDIR(stat_buf.st_mode))
  {

    if (rmdir(aBuffer.ToCString()))
    {
      myError.SetValue(errno, Iam, "Remove");
      return;
    }
    return;
  }
  else if (S_ISREG(stat_buf.st_mode) || S_ISLNK(stat_buf.st_mode) || S_ISFIFO(stat_buf.st_mode))
  {

    if (unlink(aBuffer.ToCString()) == -1)
      myError.SetValue(errno, Iam, "Remove");
    return;
  }
  myError.SetValue(EINVAL, Iam, "Remove");
  return;
}

void OSD_FileNode::Move(const OSD_Path& NewPath)
{
  int                     status;
  TCollection_AsciiString thisPath;

  NewPath.SystemName(thisPath);
  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);
  status = rename(aBuffer.ToCString(), thisPath.ToCString());

  if (status == -1)
    myError.SetValue(errno, Iam, "Move");
}

int static copy_file(const char* src, const char* trg)
{
  int err = 0;
  errno   = 0;
  int fds = open(src, O_RDONLY);
  if (fds < 0)
    return errno;

  int fdo = open(trg, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fdo < 0)
  {
    err = errno;
    close(fds);
    return err;
  }

  const int BUFSIZE = 4096;
  char      buf[BUFSIZE];
  int       n = 0;
  while ((n = (int)read(fds, buf, BUFSIZE)) > 0)
  {
    if (write(fdo, buf, n) != n)
    {

      if (!errno)
      {
        errno = ENOSPC;
      }
      break;
    }
  }

  err = errno;
  close(fdo);
  if (!err)
    err = errno;
  close(fds);
  if (!err)
    err = errno;
  return err;
}

void OSD_FileNode::Copy(const OSD_Path& ToPath)
{
  int                     status;
  TCollection_AsciiString second_name;

  ToPath.SystemName(second_name);

  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);
  status = copy_file(aBuffer.ToCString(), second_name.ToCString());
  if (status != 0)
    myError.SetValue(-1, Iam, "Copy failed");
  #ifdef OCCT_DEBUG
  printf("Status %d : errno # %d\n", status, errno);
  #endif
}

OSD_Protection OSD_FileNode::Protection()
{
  OSD_Protection thisProt;
  struct stat    myStat;
  int            status;
  int            s, u, g, w;

  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);
  status = stat(aBuffer.ToCString(), &myStat);
  if (status == -1)
    myError.SetValue(errno, Iam, "Protection");

  u = g = w = OSD_None;

  if (myStat.st_mode & S_IRUSR)
    u |= OSD_R;
  if (myStat.st_mode & S_IWUSR)
    u |= OSD_W;
  if (myStat.st_mode & S_IXUSR)
    u |= OSD_X;

  if (myStat.st_mode & S_IRGRP)
    g |= OSD_R;
  if (myStat.st_mode & S_IWGRP)
    g |= OSD_W;
  if (myStat.st_mode & S_IXGRP)
    g |= OSD_X;

  if (myStat.st_mode & S_IROTH)
    w |= OSD_R;
  if (myStat.st_mode & S_IWOTH)
    w |= OSD_W;
  if (myStat.st_mode & S_IXOTH)
    w |= OSD_X;

  s = g;
  thisProt.SetValues((OSD_SingleProtection)s,
                     (OSD_SingleProtection)u,
                     (OSD_SingleProtection)g,
                     (OSD_SingleProtection)w);

  return (thisProt);
}

void OSD_FileNode::SetProtection(const OSD_Protection& Prot)
{
  int status;

  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);
  status = chmod(aBuffer.ToCString(), (mode_t)Prot.Internal());
  if (status == -1)
    myError.SetValue(errno, Iam, "SetProtection");
}

Quantity_Date OSD_FileNode::CreationMoment()
{

  Quantity_Date result;
  struct tm*    decode;
  struct stat   buffer;

  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);
  if (!stat(aBuffer.ToCString(), &buffer))
  {
    time_t aTime = (time_t)buffer.st_ctime;
    decode       = localtime(&aTime);
    result.SetValues(decode->tm_mon + 1,
                     decode->tm_mday,
                     decode->tm_year + 1900,
                     decode->tm_hour,
                     decode->tm_min,
                     decode->tm_sec,
                     0,
                     0);
  }
  else
    result.SetValues(1, 1, 1979, 0, 0, 0, 0, 0);
  return (result);
}

Quantity_Date OSD_FileNode::AccessMoment()
{

  Quantity_Date result;
  struct tm*    decode;
  struct stat   buffer;

  TCollection_AsciiString aBuffer;
  myPath.SystemName(aBuffer);
  if (!stat(aBuffer.ToCString(), &buffer))
  {
    time_t aTime = (time_t)buffer.st_ctime;
    decode       = localtime(&aTime);
    result.SetValues(decode->tm_mon + 1,
                     decode->tm_mday,
                     decode->tm_year + 1900,
                     decode->tm_hour,
                     decode->tm_min,
                     decode->tm_sec,
                     0,
                     0);
  }
  else
    result.SetValues(1, 1, 1979, 0, 0, 0, 0, 0);
  return (result);
}

void OSD_FileNode::Reset()
{
  myError.Reset();
}

bool OSD_FileNode::Failed() const
{
  return (myError.Failed());
}

void OSD_FileNode::Perror()
{
  myError.Perror();
}

int OSD_FileNode::Error() const
{
  return (myError.Error());
}

#else

  #ifdef NONLS
    #undef NONLS
  #endif
  #include <windows.h>

  #include <TCollection_ExtendedString.hpp>

  #include <OSD_WNT.hpp>

  #ifndef _INC_TCHAR
    #include <tchar.h>
  #endif

  #include <strsafe.h>

  #define TEST_RAISE(arg) _test_raise(fName, (arg))
  #define RAISE(arg) throw Standard_ProgramError((arg))

  #ifndef OCCT_UWP

PSECURITY_DESCRIPTOR __fastcall _osd_wnt_protection_to_sd(const OSD_Protection&,
                                                          BOOL,
                                                          const wchar_t*);
BOOL __fastcall _osd_wnt_sd_to_protection(PSECURITY_DESCRIPTOR pSD, OSD_Protection& prot, BOOL);
  #endif
int __fastcall _get_file_type(const char*, HANDLE);

void _osd_wnt_set_error(OSD_Error&, int, ...);

static BOOL __fastcall _get_file_time(const wchar_t*, LPSYSTEMTIME, BOOL);
static void __fastcall _test_raise(TCollection_AsciiString, const char*);

OSD_FileNode::OSD_FileNode() {}

OSD_FileNode::OSD_FileNode(const OSD_Path& Name)
{
  myPath = Name;
}

void OSD_FileNode::Path(OSD_Path& Name) const
{

  Name = myPath;
}

void OSD_FileNode::SetPath(const OSD_Path& Name)
{

  myPath = Name;
}

bool OSD_FileNode::Exists()
{
  myError.Reset();

  bool                    retVal = false;
  TCollection_AsciiString fName;

  myPath.SystemName(fName);

  if (fName.IsEmpty())
    return false;
  TEST_RAISE("Exists");

  TCollection_ExtendedString fNameW(fName);

  WIN32_FILE_ATTRIBUTE_DATA aFileInfo;

  if (!GetFileAttributesExW(fNameW.ToWideString(), GetFileExInfoStandard, &aFileInfo))
  {
    if (GetLastError() != ERROR_FILE_NOT_FOUND)
    {
      _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString());
    }
  }
  else
  {
    retVal = true;
  }

  return retVal;
}

void OSD_FileNode::Remove()
{

  TCollection_AsciiString fName;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  TEST_RAISE("Remove");

  switch (_get_file_type(fName.ToCString(), INVALID_HANDLE_VALUE))
  {

    case FLAG_FILE:

      if (!DeleteFileW(fNameW.ToWideString()))
        _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString());
      break;

    case FLAG_DIRECTORY:

      if (!RemoveDirectoryW(fNameW.ToWideString()))
        _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString());
      break;

    default:
      RAISE("OSD_FileNode :: Remove (): invalid file type - neither file nor directory");
  }
}

void OSD_FileNode::Move(const OSD_Path& NewPath)
{

  TCollection_AsciiString fName;
  TCollection_AsciiString fNameDst;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  TEST_RAISE("Move");

  NewPath.SystemName(fNameDst);
  TCollection_ExtendedString fNameDstW(fNameDst);

  switch (_get_file_type(fName.ToCString(), INVALID_HANDLE_VALUE))
  {

    case FLAG_FILE:

      if (!MoveFileExW(fNameW.ToWideString(),
                       fNameDstW.ToWideString(),
                       MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED))
        _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString(), fNameDstW.ToWideString());
      break;

    case FLAG_DIRECTORY:

      if (!MoveDirectory(fNameW.ToWideString(), fNameDstW.ToWideString()))
        _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString(), fNameDstW.ToWideString());
      break;

    default:
      RAISE("OSD_FileNode :: Move (): invalid file type - neither file nor directory");
  }
}

void OSD_FileNode::Copy(const OSD_Path& ToPath)
{

  TCollection_AsciiString fName;
  TCollection_AsciiString fNameDst;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  TEST_RAISE("Copy");

  ToPath.SystemName(fNameDst);
  TCollection_ExtendedString fNameDstW(fNameDst);

  switch (_get_file_type(fName.ToCString(), INVALID_HANDLE_VALUE))
  {

    case FLAG_FILE:
  #ifndef OCCT_UWP
      if (!CopyFileW(fNameW.ToWideString(), fNameDstW.ToWideString(), FALSE))
  #else
      if (CopyFile2(fNameW.ToWideString(), fNameDstW.ToWideString(), FALSE) != S_OK)
  #endif
        _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString(), fNameDstW.ToWideString());
      break;

    case FLAG_DIRECTORY:

      if (!CopyDirectory(fNameW.ToWideString(), fNameDstW.ToWideString()))
        _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString(), fNameDstW.ToWideString());

      break;

    default:
      RAISE("OSD_FileNode :: Copy (): invalid file type - neither file nor directory");
  }
}

  #ifndef OCCT_UWP

OSD_Protection OSD_FileNode::Protection()
{

  OSD_Protection          retVal;
  TCollection_AsciiString fName;
  PSECURITY_DESCRIPTOR    pSD;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  TEST_RAISE("Protection");

  if ((pSD = GetFileSecurityEx(fNameW.ToWideString(),
                               DACL_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION))
        == NULL
      || !_osd_wnt_sd_to_protection(pSD,
                                    retVal,
                                    _get_file_type(fName.ToCString(), INVALID_HANDLE_VALUE)
                                      == FLAG_DIRECTORY))

    _osd_wnt_set_error(myError, OSD_WFileNode);

  if (pSD != NULL)

    FreeFileSecurity(pSD);

  return retVal;
}

void OSD_FileNode::SetProtection(const OSD_Protection& Prot)
{

  TCollection_AsciiString fName;
  PSECURITY_DESCRIPTOR    pSD;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  TEST_RAISE("SetProtection");

  pSD = _osd_wnt_protection_to_sd(Prot,
                                  _get_file_type(fName.ToCString(), INVALID_HANDLE_VALUE)
                                    == FLAG_DIRECTORY,
                                  fNameW.ToWideString());

  if (pSD == NULL || !SetFileSecurityW(fNameW.ToWideString(), DACL_SECURITY_INFORMATION, pSD))
    _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString());

  if (pSD != NULL)

    FreeSD(pSD);
}

  #else

    #include <io.h>

OSD_Protection OSD_FileNode::Protection()
{
  TCollection_AsciiString fName;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  OSD_SingleProtection aProt = OSD_None;
  if (_waccess_s(fNameW.ToWideString(), 6))
    aProt = OSD_RW;
  else if (_waccess_s(fNameW.ToWideString(), 2))
    aProt = OSD_W;
  else if (_waccess_s(fNameW.ToWideString(), 4))
    aProt = OSD_R;

  OSD_Protection retVal(OSD_RWXD, aProt, aProt, OSD_None);
  return retVal;
}

void OSD_FileNode::SetProtection(const OSD_Protection&) {}

  #endif

Quantity_Date OSD_FileNode::AccessMoment()
{

  Quantity_Date           retVal;
  SYSTEMTIME              stAccessMoment;
  SYSTEMTIME              stAccessSystemMoment;
  TCollection_AsciiString fName;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  TEST_RAISE("AccessMoment");

  if (_get_file_time(fNameW.ToWideString(), &stAccessSystemMoment, TRUE))
  {
    SYSTEMTIME* aSysTime = &stAccessMoment;
    BOOL aFlag = SystemTimeToTzSpecificLocalTime(NULL, &stAccessSystemMoment, &stAccessMoment);
    if (aFlag == 0)
      aSysTime = &stAccessSystemMoment;
    retVal.SetValues(aSysTime->wMonth,
                     aSysTime->wDay,
                     aSysTime->wYear,
                     aSysTime->wHour,
                     aSysTime->wMinute,
                     aSysTime->wSecond,
                     aSysTime->wMilliseconds);
  }
  else
  {
    _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString());
  }

  return retVal;
}

Quantity_Date OSD_FileNode::CreationMoment()
{

  Quantity_Date           retVal;
  SYSTEMTIME              stCreationMoment;
  SYSTEMTIME              stCreationSystemMoment;
  TCollection_AsciiString fName;

  myPath.SystemName(fName);
  TCollection_ExtendedString fNameW(fName);

  TEST_RAISE("CreationMoment");

  if (_get_file_time(fNameW.ToWideString(), &stCreationSystemMoment, FALSE))
  {
    SYSTEMTIME* aSysTime = &stCreationMoment;
    BOOL aFlag = SystemTimeToTzSpecificLocalTime(NULL, &stCreationSystemMoment, &stCreationMoment);
    if (aFlag == 0)
      aSysTime = &stCreationSystemMoment;
    retVal.SetValues(aSysTime->wMonth,
                     aSysTime->wDay,
                     aSysTime->wYear,
                     aSysTime->wHour,
                     aSysTime->wMinute,
                     aSysTime->wSecond,
                     aSysTime->wMilliseconds);
  }
  else
  {
    _osd_wnt_set_error(myError, OSD_WFileNode, fNameW.ToWideString());
  }

  return retVal;
}

bool OSD_FileNode::Failed() const
{

  return myError.Failed();
}

void OSD_FileNode::Reset()
{

  myError.Reset();
}

void OSD_FileNode::Perror()
{

  myError.Perror();
}

int OSD_FileNode::Error() const
{

  return myError.Error();
}

void _osd_wnt_set_error(OSD_Error& err, int who, ...)
{

  DWORD errCode;

  wchar_t buffer[2048];

  va_list arg_ptr;

  va_start(arg_ptr, who);

  errCode = GetLastError();

  if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM,
                      0,
                      errCode,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                      buffer,
                      2048,
                      &arg_ptr))
  {
    StringCchPrintfW(buffer, _countof(buffer), L"error code %d", (int)errCode);

    SetLastError(errCode);
  }

  char aBufferA[2048];
  WideCharToMultiByte(CP_UTF8, 0, buffer, -1, aBufferA, sizeof(aBufferA), NULL, NULL);
  err.SetValue(errCode, who, aBufferA);

  va_end(arg_ptr);
}

  #if defined(__CYGWIN32__) || defined(__MINGW32__)
    #ifdef __try
      #undef __try
    #endif
    #define __try
    #define __finally
    #define __leave return retVal
  #endif

static BOOL __fastcall _get_file_time(const wchar_t* fName, LPSYSTEMTIME lpSysTime, BOOL fAccess)
{
  BOOL       retVal = FALSE;
  FILETIME   ftCreationTime;
  FILETIME   ftLastWriteTime;
  LPFILETIME lpftPtr;
  HANDLE     hFile = INVALID_HANDLE_VALUE;

  __try
  {
  #ifndef OCCT_UWP
    if ((hFile = CreateFileW(fName, 0, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL))
        == INVALID_HANDLE_VALUE)
  #else
    CREATEFILE2_EXTENDED_PARAMETERS pCreateExParams = {};
    pCreateExParams.dwSize                          = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
    pCreateExParams.dwFileAttributes                = FILE_ATTRIBUTE_NORMAL;
    pCreateExParams.lpSecurityAttributes            = NULL;
    pCreateExParams.hTemplateFile                   = NULL;
    if ((hFile = CreateFile2(fName, NULL, NULL, OPEN_EXISTING, &pCreateExParams))
        == INVALID_HANDLE_VALUE)
  #endif
      __leave;

    if (!GetFileTime(hFile, &ftCreationTime, NULL, &ftLastWriteTime))
      __leave;

    lpftPtr = fAccess ? &ftLastWriteTime : &ftCreationTime;

    if (!FileTimeToSystemTime(lpftPtr, lpSysTime))
      __leave;

    retVal = TRUE;
  }

  __finally
  {

    if (hFile != INVALID_HANDLE_VALUE)

      CloseHandle(hFile);
  }

  return retVal;
}

  #if defined(__CYGWIN32__) || defined(__MINGW32__)
    #undef __try
    #undef __finally
    #undef __leave
  #endif

static void __fastcall _test_raise(TCollection_AsciiString fName, const char* str)
{
  if (fName.IsEmpty())
  {
    TCollection_AsciiString buff = "OSD_FileNode :: ";
    buff += str;
    buff += " (): wrong access";

    throw Standard_ProgramError(buff.ToCString());
  }
}

#endif
