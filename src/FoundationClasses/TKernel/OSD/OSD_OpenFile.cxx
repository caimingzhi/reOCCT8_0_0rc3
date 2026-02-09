

#ifdef _WIN32
  #include <windows.h>
  #include <share.h>
#endif

#include <OSD_OpenFile.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int OSD_OpenFile_iosMode2FileFlags(::std::ios_base::openmode theMode)
{
  int aFlags = 0;
  if (theMode & ::std::ios_base::in)
  {
    aFlags |= O_RDONLY;
  }
  if (theMode & ::std::ios_base::out)
  {
    aFlags |= O_WRONLY;
    aFlags |= O_CREAT;
    aFlags |= O_TRUNC;

    if (theMode & ::std::ios_base::app)
    {
      aFlags |= O_APPEND;
    }
  }
#ifdef _WIN32
  if (theMode & ::std::ios_base::binary)
  {
    aFlags |= O_BINARY;
  }
  else
  {
    aFlags |= O_TEXT;
  }
#endif
  return aFlags;
}

int OSD_OpenFileDescriptor(const TCollection_ExtendedString& theName,
                           ::std::ios_base::openmode         theMode)
{
  int       aFileDesc = -1;
  const int aFlags    = OSD_OpenFile_iosMode2FileFlags(theMode);
#if defined(_WIN32)
  const errno_t anErrCode =
    _wsopen_s(&aFileDesc, theName.ToWideString(), aFlags, _SH_DENYNO, _S_IREAD | _S_IWRITE);
  if (anErrCode != 0)
  {
    return -1;
  }
#else
  NCollection_UtfString<char> aString(theName.ToExtString());

  aFileDesc = open(aString.ToCString(), aFlags, S_IRUSR | S_IWUSR);
#endif
  return aFileDesc;
}

FILE* OSD_OpenFile(const char* theName, const char* theMode)
{
  FILE* aFile = nullptr;
#if defined(_WIN32)

  const TCollection_ExtendedString aFileNameW(theName, true);
  const TCollection_ExtendedString aFileModeW(theMode, true);
  aFile = ::_wfopen(aFileNameW.ToWideString(), aFileModeW.ToWideString());
#else
  aFile = ::fopen(theName, theMode);
#endif
  return aFile;
}

FILE* OSD_OpenFile(const TCollection_ExtendedString& theName, const char* theMode)
{
  FILE* aFile = nullptr;
#if defined(_WIN32)
  const TCollection_ExtendedString aFileModeW(theMode, true);
  aFile = ::_wfopen(theName.ToWideString(), aFileModeW.ToWideString());
#else

  NCollection_UtfString<char> aString(theName.ToExtString());
  aFile = ::fopen(aString.ToCString(), theMode);
#endif
  return aFile;
}

std::time_t OSD_FileStatCTime(const char* theName)
{
  std::time_t aTime = 0;
#if defined(_WIN32)

  const TCollection_ExtendedString aFileNameW(theName, true);
  struct __stat64                  aStat;
  if (_wstat64(aFileNameW.ToWideString(), &aStat) == 0)
  {
    aTime = (std::time_t)aStat.st_ctime;
  }
#else
  struct stat aStat;
  if (stat(theName, &aStat) == 0)
  {
    aTime = (std::time_t)aStat.st_ctime;
  }
#endif
  return aTime;
}
