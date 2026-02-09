

#ifndef _WIN32

  #include <OSD_Host.hpp>
  #include <OSD_OSDError.hpp>
  #include <OSD_WhoAmI.hpp>
  #include <Standard_ConstructionError.hpp>
  #include <Standard_NullObject.hpp>
  #include <TCollection_AsciiString.hpp>

const OSD_WhoAmI Iam = OSD_WHost;

  #include <cerrno>

  #include <sys/utsname.h>
  #include <netdb.h>
  #include <unistd.h>
  #include <cstdio>

  #if defined(__osf__) || defined(DECOSF1)
    #include <sys/types.h>
    #include <sys/sysinfo.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <net/if.h>
extern "C"
{
  int gethostname(char* address, int len);
}
  #endif

extern "C"
{
  int sysinfo(int, char*, long);
}

OSD_Host::OSD_Host() = default;

TCollection_AsciiString OSD_Host::SystemVersion()
{
  struct utsname          info;
  TCollection_AsciiString result;

  uname(&info);
  result = info.sysname;
  result += " ";
  result += info.release;
  return (result);
}

OSD_SysType OSD_Host::SystemId() const
{
  struct utsname info;

  uname(&info);

  if (!strcmp(info.sysname, "SunOS"))
    return (OSD_UnixBSD);
  if (!strcmp(info.sysname, "ULTRIX"))
    return (OSD_UnixBSD);
  if (!strcmp(info.sysname, "FreeBSD"))
    return (OSD_UnixBSD);
  if (!strncmp(info.sysname, "Linux", 5))
    return (OSD_LinuxREDHAT);
  if (!strncmp(info.sysname, "IRIX", 4))
    return (OSD_UnixSystemV);
  if (!strncmp(info.sysname, "OSF", 3))
    return (OSD_OSF);
  if (!strcmp(info.sysname, "AIX"))
    return (OSD_Aix);
  if (!strcmp(info.sysname, "UNIX_System_V"))
    return (OSD_UnixSystemV);
  if (!strcmp(info.sysname, "VMS_POSIX"))
    return (OSD_VMS);
  if (!strcmp(info.sysname, "Darwin"))
    return (OSD_MacOs);
  return (OSD_Unknown);
}

TCollection_AsciiString OSD_Host::HostName()
{
  TCollection_AsciiString result;
  char                    value[65];
  int                     status;

  status = gethostname(value, 64);
  if (status == -1)
    myError.SetValue(errno, Iam, "Host Name");

  result = value;
  return (result);
}

int OSD_Host::AvailableMemory()
{
  int result;

  #if defined(__osf__) || defined(DECOSF1)
  char buffer[16];

  if (result != -1)
    result *= 1024;
  #else
  result = 0;

  #endif
  return (result);
}

TCollection_AsciiString OSD_Host::InternetAddress()
{
  struct hostent          internet_address;
  int                     a, b, c, d;
  char                    buffer[16];
  TCollection_AsciiString result, host;

  host                    = HostName();
  const auto* aHostByName = gethostbyname(host.ToCString());
  if (aHostByName == nullptr)
  {
    aHostByName = gethostbyname("localhost");
  }
  memcpy(&internet_address, aHostByName, sizeof(struct hostent));

  a = (unsigned char)internet_address.h_addr_list[0][0];
  b = (unsigned char)internet_address.h_addr_list[0][1];
  c = (unsigned char)internet_address.h_addr_list[0][2];
  d = (unsigned char)internet_address.h_addr_list[0][3];
  Sprintf(buffer, "%d.%d.%d.%d", a, b, c, d);
  result = buffer;
  return (result);
}

OSD_OEMType OSD_Host::MachineType()
{
  struct utsname info;

  uname(&info);

  if (!strcmp(info.sysname, "SunOS"))
    return (OSD_SUN);
  if (!strcmp(info.sysname, "ULTRIX"))
    return (OSD_DEC);
  if (!strncmp(info.sysname, "IRIX", 4))
    return (OSD_SGI);
  if (!strcmp(info.sysname, "HP-UX"))
    return (OSD_HP);
  if (!strcmp(info.sysname, "UNIX_System_V"))
    return (OSD_NEC);
  if (!strcmp(info.sysname, "VMS_POSIX"))
    return (OSD_VAX);
  if (!strncmp(info.sysname, "OSF", 3))
    return (OSD_DEC);
  if (!strncmp(info.sysname, "Linux", 5))
    return (OSD_LIN);
  if (!strcmp(info.sysname, "FreeBSD"))
    return (OSD_LIN);
  if (!strncmp(info.sysname, "AIX", 3))
    return (OSD_AIX);
  if (!strcmp(info.sysname, "Darwin"))
    return (OSD_MAC);
  return (OSD_Unavailable);
}

void OSD_Host::Reset()
{
  myError.Reset();
}

bool OSD_Host::Failed() const
{
  return (myError.Failed());
}

void OSD_Host::Perror()
{
  myError.Perror();
}

int OSD_Host::Error() const
{
  return (myError.Error());
}

#else

  #include <windows.h>

  #include <OSD_Host.hpp>

void _osd_wnt_set_error(OSD_Error&, int, ...);

static BOOL                    fInit = FALSE;
static TCollection_AsciiString hostName;
static TCollection_AsciiString version;
static TCollection_AsciiString interAddr;
static int                     memSize;

OSD_Host ::OSD_Host()
{
  #ifndef OCCT_UWP
  DWORD          nSize;
  char           szHostName[MAX_COMPUTERNAME_LENGTH + 1];
  char*          hostAddr = 0;
  MEMORYSTATUS   ms;
  WSADATA        wd;
  PHOSTENT       phe;
  IN_ADDR        inAddr;
  OSVERSIONINFOW osVerInfo;

  if (!fInit)
  {

    nSize = MAX_COMPUTERNAME_LENGTH + 1;
    ZeroMemory(&osVerInfo, sizeof(OSVERSIONINFOW));
    osVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);

    ZeroMemory(&ms, sizeof(ms));
    ZeroMemory(szHostName, sizeof(char) * (MAX_COMPUTERNAME_LENGTH + 1));

    Standard_DISABLE_DEPRECATION_WARNINGS if (!GetVersionExW(&osVerInfo))
    {
      _osd_wnt_set_error(myError, OSD_WHost);
    }
    else if (!GetComputerNameA(szHostName, &nSize))
    {
      _osd_wnt_set_error(myError, OSD_WHost);
    }
    else
    {
      ms.dwLength = sizeof(MEMORYSTATUS);
      GlobalMemoryStatus(&ms);
    }
    Standard_ENABLE_DEPRECATION_WARNINGS

      if (!Failed())
    {

      memSize = (int)ms.dwAvailPageFile;

      if (WSAStartup(MAKEWORD(1, 1), &wd))
      {

        _osd_wnt_set_error(myError, OSD_WHost);
      }
      else if ((phe = gethostbyname(szHostName)) == NULL)
      {

        _osd_wnt_set_error(myError, OSD_WHost);
      }
      else
      {

        CopyMemory(&inAddr, *phe->h_addr_list, sizeof(IN_ADDR));
        hostAddr = inet_ntoa(inAddr);
      }
    }

    if (!Failed())
    {

      hostName                         = szHostName;
      interAddr                        = static_cast<const char*>(hostAddr);
      TCollection_AsciiString aVersion = TCollection_AsciiString("Windows NT Version ")
                                         + (int)osVerInfo.dwMajorVersion + "."
                                         + (int)osVerInfo.dwMinorVersion;
      if (*osVerInfo.szCSDVersion != L'\0')
      {
        aVersion += TCollection_AsciiString(" ") + TCollection_AsciiString(osVerInfo.szCSDVersion);
      }
      version = aVersion;

      fInit = TRUE;
    }
  }

  if (fInit)

    myName = hostName;
  #endif
}

TCollection_AsciiString OSD_Host ::SystemVersion()
{

  return version;
}

OSD_SysType OSD_Host ::SystemId() const
{

  return OSD_WindowsNT;
}

TCollection_AsciiString OSD_Host ::HostName()
{

  return hostName;
}

int OSD_Host ::AvailableMemory()
{

  return memSize;
}

TCollection_AsciiString OSD_Host ::InternetAddress()
{

  return interAddr;
}

OSD_OEMType OSD_Host ::MachineType()
{

  return OSD_PC;
}

bool OSD_Host ::Failed() const
{

  return myError.Failed();
}

void OSD_Host ::Reset()
{

  myError.Reset();
}

void OSD_Host ::Perror()
{

  myError.Perror();
}

int OSD_Host ::Error() const
{

  return myError.Error();
}

#endif
