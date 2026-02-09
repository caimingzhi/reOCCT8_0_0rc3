

#ifdef _WIN32

  #ifdef NOUSER
    #undef NOUSER
  #endif
  #include <windows.h>
#endif

#include <OSD_Process.hpp>

#include <NCollection_Array1.hpp>
#include <OSD_Environment.hpp>
#include <OSD_OSDError.hpp>
#include <OSD_Path.hpp>
#include <OSD_WhoAmI.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Quantity_Date.hpp>

#ifdef _WIN32
  #include <OSD_WNT.hpp>
  #include <lmcons.h>
#else
const OSD_WhoAmI Iam = OSD_WProcess;
  #include <cerrno>
  #include <cstdlib>
  #include <sys/param.h>
  #include <sys/time.h>
  #if !defined(__EMSCRIPTEN__)
    #include <pwd.h>
  #endif
  #include <unistd.h>
#endif

#if defined(__APPLE__)
  #include <mach-o/dyld.h>
#endif

#ifndef _WIN32

OSD_Process::OSD_Process() = default;

void OSD_Process::TerminalType(TCollection_AsciiString& Name)
{
  TCollection_AsciiString which = "TERM";
  OSD_Environment         term(which, "");

  term.Value();
  which = term.Value();
  Name  = term.Name();
}

Quantity_Date OSD_Process::SystemDate()
{
  Quantity_Date   result;
  int             month = 0, day = 0, year = 0, hh = 0, mn = 0, ss = 0;
  struct tm       transfert;
  struct timeval  tval;
  struct timezone tzone;
  int             status;

  status = gettimeofday(&tval, &tzone);
  if (status == -1)
    myError.SetValue(errno, Iam, "GetSystem");
  else
  {
    memcpy(&transfert, localtime((time_t*)&tval.tv_sec), sizeof(struct tm));
    month = transfert.tm_mon + 1;
    day   = transfert.tm_mday;
    year  = transfert.tm_year;
    hh    = transfert.tm_hour;
    mn    = transfert.tm_min;
    ss    = transfert.tm_sec;
  }

  result.SetValues(month, day, year + 1900, hh, mn, ss);
  return (result);
}

int OSD_Process::ProcessId()
{
  return (getpid());
}

TCollection_AsciiString OSD_Process::UserName()
{
  #if defined(__EMSCRIPTEN__)

  return TCollection_AsciiString();
  #else
  struct passwd* anInfos = getpwuid(getuid());
  return TCollection_AsciiString(anInfos ? anInfos->pw_name : "");
  #endif
}

bool OSD_Process::IsSuperUser()
{
  return getuid() == 0;
}

OSD_Path OSD_Process::CurrentDirectory()
{
  char                    cwd[MAXPATHLEN + 1];
  OSD_Path                result;
  TCollection_AsciiString Name;

  if (!getcwd(cwd, MAXPATHLEN + 1))
    myError.SetValue(errno, Iam, "Where");
  else
  {
    Name = cwd;

  #if defined(vax) || defined(__vms)
    int iDisk = Name.Search(":");
    if (iDisk)
    {
      TCollection_AsciiString Disk;
      TCollection_AsciiString Directory;
      Disk      = Name.SubString(1, iDisk - 1);
      Directory = Name.SubString(iDisk + 1, Name.Length());
      result.SetValues("", "", "", Disk, Directory, "", "");
    }
  #else
    Name += TCollection_AsciiString("/");
    result = OSD_Path(Name);

  #endif
  }
  return (result);
}

void OSD_Process::SetCurrentDirectory(const OSD_Path& where)
{
  TCollection_AsciiString Name;
  int                     status;

  where.SystemName(Name);

  status = chdir(Name.ToCString());
  if (status == -1)
    myError.SetValue(errno, Iam, "Move to directory");
}

void OSD_Process::Reset()
{
  myError.Reset();
}

bool OSD_Process::Failed() const
{
  return (myError.Failed());
}

void OSD_Process::Perror()
{
  myError.Perror();
}

int OSD_Process::Error() const
{
  return (myError.Error());
}

#else

void _osd_wnt_set_error(OSD_Error&, int, ...);

OSD_Process::OSD_Process() {}

void OSD_Process ::TerminalType(TCollection_AsciiString& Name)
{

  Name = "WIN32 console";
}

Quantity_Date OSD_Process ::SystemDate()
{

  Quantity_Date retVal;
  SYSTEMTIME    st;

  GetLocalTime(&st);

  retVal
    .SetValues(st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

  return retVal;
}

TCollection_AsciiString OSD_Process::UserName()
{
  #ifndef OCCT_UWP
  wchar_t                 aUserName[UNLEN + 1];
  DWORD                   aNameSize = UNLEN + 1;
  TCollection_AsciiString retVal;
  if (!GetUserNameW(aUserName, &aNameSize))
  {
    _osd_wnt_set_error(myError, OSD_WProcess);
    return TCollection_AsciiString();
  }
  return TCollection_AsciiString(aUserName);
  #else
  return TCollection_AsciiString();
  #endif
}

bool OSD_Process ::IsSuperUser()
{
  #ifndef OCCT_UWP
  bool          retVal = FALSE;
  PSID          pSIDadmin;
  HANDLE        hProcessToken = INVALID_HANDLE_VALUE;
  PTOKEN_GROUPS pTKgroups     = NULL;

  if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hProcessToken)
      || (pTKgroups = (PTOKEN_GROUPS)GetTokenInformationEx(hProcessToken, TokenGroups)) == NULL)

    _osd_wnt_set_error(myError, OSD_WProcess);

  else
  {

    pSIDadmin = AdminSid();

    for (int i = 0; i < (int)pTKgroups->GroupCount; ++i)

      if (EqualSid(pTKgroups->Groups[i].Sid, pSIDadmin))
      {

        retVal = TRUE;
        break;
      }
  }

  if (hProcessToken != INVALID_HANDLE_VALUE)
    CloseHandle(hProcessToken);
  if (pTKgroups != NULL)
    FreeTokenInformation(pTKgroups);

  return retVal;
  #else
  return FALSE;
  #endif
}

int OSD_Process::ProcessId()
{
  return (int)GetCurrentProcessId();
}

OSD_Path OSD_Process::CurrentDirectory()
{
  OSD_Path anCurrentDirectory;
  #ifndef OCCT_UWP
  const DWORD aBuffLen = GetCurrentDirectoryW(0, NULL);
  if (aBuffLen > 0)
  {
    wchar_t* aBuff = new wchar_t[aBuffLen + 1];
    GetCurrentDirectoryW(aBuffLen, aBuff);
    aBuff[aBuffLen] = L'\0';
    const TCollection_AsciiString aPath(aBuff);
    delete[] aBuff;

    anCurrentDirectory = OSD_Path(aPath);
  }
  else
  {
    _osd_wnt_set_error(myError, OSD_WProcess);
  }
  #endif
  return anCurrentDirectory;
}

void OSD_Process ::SetCurrentDirectory(const OSD_Path& where)
{

  TCollection_AsciiString path;

  where.SystemName(path);
  TCollection_ExtendedString pathW(path);

  if (!::SetCurrentDirectoryW(pathW.ToWideString()))

    _osd_wnt_set_error(myError, OSD_WProcess);
}

bool OSD_Process ::Failed() const
{

  return myError.Failed();
}

void OSD_Process ::Reset()
{

  myError.Reset();
}

void OSD_Process ::Perror()
{

  myError.Perror();
}

int OSD_Process ::Error() const
{

  return myError.Error();
}

#endif

TCollection_AsciiString OSD_Process::ExecutablePath()
{
#ifdef _WIN32
  wchar_t aBuff[MAX_PATH + 2];
  DWORD   aLenFilled  = GetModuleFileNameW(0, aBuff, MAX_PATH + 1);
  aBuff[MAX_PATH + 1] = 0;
  if (aLenFilled == 0)
  {
    return TCollection_AsciiString();
  }
  else if (aLenFilled <= MAX_PATH)
  {
    return TCollection_AsciiString(aBuff);
  }

  wchar_t* aBuffDyn = NULL;
  for (int anIter = 2;; ++anIter)
  {
    size_t aBuffLen = MAX_PATH * anIter;
    aBuffDyn = reinterpret_cast<wchar_t*>(realloc(aBuffDyn, sizeof(wchar_t) * (aBuffLen + 1)));
    if (aBuffDyn == NULL)
    {
      return TCollection_AsciiString();
    }

    aLenFilled = GetModuleFileNameW(NULL, aBuffDyn, DWORD(aBuffLen));
    if (aLenFilled != aBuffLen)
    {
      aBuffDyn[aBuffLen] = L'\0';
      TCollection_AsciiString aRes(aBuffDyn);
      free(aBuffDyn);
      return aRes;
    }
  }
#elif defined(__APPLE__)

  uint32_t aNbBytes = 0;
  _NSGetExecutablePath(nullptr, &aNbBytes);
  if (aNbBytes == 0)
  {
    return TCollection_AsciiString();
  }

  NCollection_Array1<char> aBuff(0, aNbBytes);
  _NSGetExecutablePath(&aBuff.ChangeFirst(), &aNbBytes);
  aBuff[aNbBytes] = '\0';

  char* aResultBuf = realpath(&aBuff.First(), nullptr);
  if (aResultBuf == nullptr)
  {
    return TCollection_AsciiString();
  }

  TCollection_AsciiString aProcessPath(aResultBuf);
  free(aResultBuf);
  return aProcessPath;
#elif defined(__linux__)

  TCollection_AsciiString aSimLink =
    TCollection_AsciiString("/proc/") + TCollection_AsciiString(getpid()) + "/exe";
  char    aBuff[4096];
  ssize_t aBytes = readlink(aSimLink.ToCString(), aBuff, 4096);
  if (aBytes > 0)
  {
    aBuff[aBytes] = '\0';
    return TCollection_AsciiString(aBuff);
  }
  return TCollection_AsciiString();
#else

  return TCollection_AsciiString();
#endif
}

TCollection_AsciiString OSD_Process::ExecutableFolder()
{
  TCollection_AsciiString aFullPath  = ExecutablePath();
  int                     aLastSplit = -1;
#ifdef _WIN32
  const char THE_FILE_SEPARATOR = '\\';
#else
  const char THE_FILE_SEPARATOR = '/';
#endif
  for (int anIter = 1; anIter <= aFullPath.Length(); ++anIter)
  {
    if (aFullPath.Value(anIter) == THE_FILE_SEPARATOR)
    {
      aLastSplit = anIter;
    }
  }

  if (aLastSplit != -1)
  {
    return aFullPath.SubString(1, aLastSplit);
  }
  return TCollection_AsciiString();
}
