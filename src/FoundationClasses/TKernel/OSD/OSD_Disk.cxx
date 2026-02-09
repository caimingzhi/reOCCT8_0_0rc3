

#include <OSD_Disk.hpp>

#include <OSD_Path.hpp>
#include <OSD_WhoAmI.hpp>
#include <NCollection_Array1.hpp>
#include <TCollection_ExtendedString.hpp>

#ifdef _WIN32
  #include <windows.h>

void _osd_wnt_set_error(OSD_Error&, int, ...);

static TCollection_AsciiString _osd_wnt_set_disk_name(const OSD_Path& thePath)
{
  {
    TCollection_AsciiString aDisk = thePath.Disk();
    if (aDisk.UsefullLength() != 0)
    {
      return aDisk + '/';
    }
  }

  TCollection_AsciiString aDir = thePath.Trek();
  const int               j    = aDir.UsefullLength();
  if (j < 3 || aDir.Value(1) != '|' || aDir.Value(2) != '|')
  {
    throw Standard_ProgramError("OSD_Disk: bad disk name");
  }

  aDir.SetValue(1, '\\');
  aDir.SetValue(2, '\\');
  int k = 0;
  for (int i = 3; i <= j; ++i)
  {
    if (aDir.Value(i) == '|')
    {
      if (k == 0)
      {
        aDir.SetValue(i, '\\');
        ++k;
        continue;
      }

      aDir.SetValue(i, '\\');
      break;
    }
  }

  if (k == 0)
  {
    if (thePath.Name().UsefullLength() == 0 && thePath.Extension().UsefullLength() == 0)
    {
      throw Standard_ProgramError("OSD_Disk: bad disk name");
    }
    else
    {
      aDir += '\\';
      aDir += thePath.Name();
      aDir += thePath.Extension();
    }
  }

  if (aDir.Value(aDir.UsefullLength()) != '\\')
  {
    aDir += '\\';
  }
  return aDir;
}

#else
const OSD_WhoAmI Iam = OSD_WDisk;
extern "C"
{
  #if defined(__ANDROID__)
    #include <sys/vfs.h>
    #define statvfs statfs
    #define fstatvfs fstatfs
  #else
    #include <sys/statvfs.h>
  #endif
}
  #include <cerrno>
#endif

OSD_Disk::OSD_Disk()
{
#ifdef _WIN32
  const DWORD                 aBuffLen = GetCurrentDirectoryW(0, NULL);
  NCollection_Array1<wchar_t> aBuff(0, aBuffLen);
  GetCurrentDirectoryW(aBuffLen, &aBuff.ChangeFirst());
  aBuff.ChangeValue(aBuffLen - 1) = (aBuff.Value(aBuffLen - 2) == L'\\') ? L'\0' : L'\\';
  aBuff.ChangeLast()              = L'\0';
  if (aBuffLen > 3 && aBuff.First() != L'\\')
  {
    aBuff.ChangeValue(3) = L'\0';
    myDiskName           = TCollection_AsciiString(&aBuff.ChangeFirst());
  }
#endif
}

OSD_Disk::OSD_Disk(const OSD_Path& theName)
    : myDiskName(theName.Disk())
{
#ifdef _WIN32
  myDiskName = _osd_wnt_set_disk_name(theName);
#endif
}

OSD_Disk::OSD_Disk(const char* theName)
    : myDiskName(theName)
{
#ifdef _WIN32
  OSD_Path aPath(theName);
  myDiskName = _osd_wnt_set_disk_name(aPath);
#endif
}

void OSD_Disk::SetName(const OSD_Path& theName)
{
  myDiskName = theName.Disk();
}

OSD_Path OSD_Disk::Name() const
{
#ifdef _WIN32
  return myDiskName;
#else
  OSD_Path aPath;
  aPath.SetDisk(myDiskName);
  return aPath;
#endif
}

int OSD_Disk::DiskSize()
{
#ifdef _WIN32
  ULARGE_INTEGER                   aNbFreeAvailableBytes, aNbTotalBytes, aNbTotalFreeBytes;
  const TCollection_ExtendedString aDiskNameW(myDiskName);
  if (!GetDiskFreeSpaceExW(aDiskNameW.ToWideString(),
                           &aNbFreeAvailableBytes,
                           &aNbTotalBytes,
                           &aNbTotalFreeBytes))
  {
    _osd_wnt_set_error(myError, OSD_WDisk);
    return 0;
  }

  ULONGLONG aSize = aNbTotalBytes.QuadPart / 512;
  return (int)aSize;
#else
  struct statvfs aBuffer;
  if (statvfs(myDiskName.ToCString(), &aBuffer) == 0)
  {
    unsigned long aBSize512 = aBuffer.f_frsize / 512;
    return int(aBuffer.f_blocks * aBSize512);
  }
  myError.SetValue(errno, Iam, "OSD_Disk: statvfs failed.");
  return 0;
#endif
}

int OSD_Disk::DiskFree()
{
#ifdef _WIN32
  ULARGE_INTEGER                   aNbFreeAvailableBytes, aNbTotalBytes, aNbTotalFreeBytes;
  const TCollection_ExtendedString aDiskNameW(myDiskName);
  if (!GetDiskFreeSpaceExW(aDiskNameW.ToWideString(),
                           &aNbFreeAvailableBytes,
                           &aNbTotalBytes,
                           &aNbTotalFreeBytes))
  {
    _osd_wnt_set_error(myError, OSD_WDisk);
    return 0;
  }

  ULONGLONG aSize = aNbFreeAvailableBytes.QuadPart / 512;
  return (int)aSize;
#else
  struct statvfs aBuffer;
  if (statvfs(myDiskName.ToCString(), &aBuffer) == 0)
  {
    unsigned long aBSize512 = aBuffer.f_frsize / 512;
    return int(aBuffer.f_bavail * aBSize512);
  }
  myError.SetValue(errno, Iam, "OSD_Disk: statvfs failed.");
  return 0;
#endif
}
