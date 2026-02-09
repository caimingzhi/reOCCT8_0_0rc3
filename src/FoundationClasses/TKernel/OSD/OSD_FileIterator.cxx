

#include <OSD_FileIterator.hpp>

#include <OSD_Path.hpp>
#include <TCollection_AsciiString.hpp>

#ifndef _WIN32

  #include <OSD_File.hpp>
  #include <OSD_OSDError.hpp>
  #include <OSD_WhoAmI.hpp>

  #include <dirent.h>
  #include <cstdio>
  #include <sys/stat.h>
  #include <sys/types.h>
  #define NAMLEN(dirent) strlen((dirent)->d_name)
  #ifdef VMS
extern char* vmsify PARAMS((char* name, int type));
  #endif

  #ifdef _D_NAMLEN
    #undef NAMLEN
    #define NAMLEN(d) _D_NAMLEN(d)
  #endif

  #if (defined(POSIX) || defined(VMS) || defined(WINDOWS32)) && !defined(__GNU_LIBRARY__)

    #define REAL_DIR_ENTRY(dp) 1
    #define FAKE_DIR_ENTRY(dp)
  #else
    #define REAL_DIR_ENTRY(dp) (dp->d_ino != 0)
    #define FAKE_DIR_ENTRY(dp) (dp->d_ino = 1)
  #endif

OSD_FileIterator::OSD_FileIterator()
    : myFlag(false),
      myDescr(nullptr),
      myEntry(nullptr),
      myInit(0)
{
}

OSD_FileIterator::OSD_FileIterator(const OSD_Path& where, const TCollection_AsciiString& Mask)
    : myFlag(false),
      myDescr(nullptr),
      myEntry(nullptr),
      myInit(0)
{
  Initialize(where, Mask);
}

void OSD_FileIterator ::Destroy() {}

void OSD_FileIterator::Initialize(const OSD_Path& where, const TCollection_AsciiString& Mask)
{
  myFlag = false;
  where.SystemName(myPlace);
  if (myPlace.Length() == 0)
    myPlace = ".";
  myMask = Mask;
  if (myDescr)
  {
    closedir((DIR*)myDescr);
    myDescr = nullptr;
  }
  myInit = 1;
}

bool OSD_FileIterator::More()
{
  if (myInit)
  {
    myInit  = 0;
    myDescr = (void*)opendir(myPlace.ToCString());
    if (myDescr)
    {
      myFlag = true;
      myInit = 0;
      Next();
    }
  }
  return myFlag;
}

static int strcmp_joker(const char* Mask, const char* Name)
{
  const char *p, *s;

  for (p = Mask, s = Name; *p && *p != '*'; p++, s++)
    if (*p != *s)
      return 0;

  if (!*p)
    return !(*s);
  while (*p == '*')
    p++;
  if (!*p)
    return 1;
  for (; *s; s++)
    if (strcmp_joker(p, s))
      return 1;
  return 0;
}

void OSD_FileIterator::Next()
{
  int         again = 1;
  struct stat stat_buf;
  myFlag = false;

  do
  {
    myEntry = readdir((DIR*)myDescr);

    if (!myEntry)
    {
      myEntry = nullptr;
      myFlag  = false;
      closedir((DIR*)myDescr);
      myDescr = nullptr;
      again   = 0;
    }
    else
    {
      if (!strcmp(((struct dirent*)myEntry)->d_name, "."))
        continue;
      if (!strcmp(((struct dirent*)myEntry)->d_name, ".."))
        continue;

      const TCollection_AsciiString aFullName = myPlace + "/" + ((struct dirent*)myEntry)->d_name;
      stat(aFullName.ToCString(), &stat_buf);
      if (S_ISREG(stat_buf.st_mode))
        if (strcmp_joker(myMask.ToCString(), ((struct dirent*)myEntry)->d_name))
        {

          myFlag = true;
          again  = 0;
        }
    }

  } while (again);
}

OSD_File OSD_FileIterator::Values()
{
  OSD_Path                thisvalue;
  TCollection_AsciiString Name;
  TCollection_AsciiString Ext;
  int                     position;

  if (myEntry)
    Name = ((struct dirent*)myEntry)->d_name;

  position = Name.Search(".");

  if (position != -1)
  {
    Ext = Name;
    Ext.Remove(1, position - 1);
    Name.Remove(position, Ext.Length());
  }

  thisvalue.SetValues("", "", "", "", "", Name, Ext);
  TheIterator.SetPath(thisvalue);

  return (TheIterator);
}

void OSD_FileIterator::Reset()
{
  myError.Reset();
}

bool OSD_FileIterator::Failed() const
{
  return (myError.Failed());
}

void OSD_FileIterator::Perror()
{
  myError.Perror();
}

int OSD_FileIterator::Error() const
{
  return (myError.Error());
}

#else

  #include <windows.h>

  #include <TCollection_ExtendedString.hpp>

  #define _FD ((PWIN32_FIND_DATAW)myData)

void _osd_wnt_set_error(OSD_Error&, int, ...);

OSD_FileIterator ::OSD_FileIterator(const OSD_Path& where, const TCollection_AsciiString& Mask)
{

  myFlag   = false;
  myHandle = INVALID_HANDLE_VALUE;

  where.SystemName(myPlace);

  if (myPlace.Length() == 0)
    myPlace = ".";

  myMask = Mask;
  myData = NULL;
}

void OSD_FileIterator ::Destroy()
{

  if (myData != NULL)
    HeapFree(GetProcessHeap(), 0, myData);

  if (myHandle != INVALID_HANDLE_VALUE)

    FindClose((HANDLE)myHandle);
}

bool OSD_FileIterator ::More()
{

  if (myHandle == INVALID_HANDLE_VALUE)
  {

    TCollection_AsciiString wc = myPlace + "/" + myMask;

    myData = HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, sizeof(WIN32_FIND_DATAW));

    TCollection_ExtendedString wcW(wc);
    myHandle = FindFirstFileExW(wcW.ToWideString(),
                                FindExInfoStandard,
                                (PWIN32_FIND_DATAW)myData,
                                FindExSearchNameMatch,
                                NULL,
                                0);

    if (myHandle == INVALID_HANDLE_VALUE)

      _osd_wnt_set_error(myError, OSD_WDirectoryIterator);

    else
    {

      myFlag      = true;
      myFirstCall = true;

      Next();
    }
  }
  else if (!myFlag)
  {

    FindClose((HANDLE)myHandle);
    myHandle = INVALID_HANDLE_VALUE;
  }

  return myFlag;
}

void OSD_FileIterator ::Next()
{

  if (!myFirstCall || (_FD->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
  {

    do
    {

      if (!FindNextFileW((HANDLE)myHandle, _FD))
      {

        myFlag = false;

        break;
      }

    } while ((_FD->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
  }

  myFirstCall = false;
}

OSD_File OSD_FileIterator ::Values()
{

  TCollection_AsciiString aFileName(TCollection_ExtendedString((const char16_t*)_FD->cFileName));
  TheIterator.SetPath(OSD_Path(aFileName));

  return TheIterator;
}

bool OSD_FileIterator ::Failed() const
{

  return myError.Failed();
}

void OSD_FileIterator ::Reset()
{

  myError.Reset();
}

void OSD_FileIterator ::Perror()
{

  myError.Perror();
}

int OSD_FileIterator ::Error() const
{

  return myError.Error();
}

OSD_FileIterator::OSD_FileIterator()
    : myFlag(false),
      myHandle(0),
      myData(0),
      myFirstCall(false)
{
}

void OSD_FileIterator::Initialize(const OSD_Path&, const TCollection_AsciiString&) {}

#endif
