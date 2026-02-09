

#ifndef _WIN32

  #include <OSD_Function.hpp>
  #include <OSD_LoadMode.hpp>
  #include <OSD_SharedLibrary.hpp>

  #include <cstdio>
  #include <cstring>

  #ifdef __some_crappy_system__

    #define RTLD_LAZY 1
    #define RTLD_NOW 2

    #define _LIBDL_RLD_DLOPEN 1
    #define _LIBDL_RLD_DLCLOSE 2
    #define _LIBDL_RLD_DLSYM 3
    #define _LIBDL_RLD_DLERROR 4
extern "C"
{
  void* dlopen(char* path, int mode);
}
extern "C"
{
  void* dlsym(void* handle, char* name);
}
extern "C"
{
  int dlclose(void* handle);
}
extern "C"
{
  void* dlerror(void);
}
  #endif

  #include <dlfcn.h>

  #define BAD(X) ((X) == NULL)

OSD_SharedLibrary::OSD_SharedLibrary()
    : myHandle(nullptr),
      myName(nullptr)
{
}

OSD_SharedLibrary::OSD_SharedLibrary(const char* aName)
    : myHandle(nullptr)
{
  if (aName != nullptr)
  {
    myName = new char[(strlen(aName) + 1)];
    strcpy(myName, aName);
  }
}

const char* OSD_SharedLibrary::Name() const
{
  return myName;
}

void OSD_SharedLibrary::SetName(const char* aName)
{
  if (aName != nullptr)
  {
    myName = new char[(strlen(aName) + 1)];
    strcpy(myName, aName);
  }
}

bool OSD_SharedLibrary::DlOpen(const OSD_LoadMode aMode)
{
  if (aMode == OSD_RTLD_LAZY)
  {
    myHandle = dlopen(myName, RTLD_LAZY);
  }
  else if (aMode == OSD_RTLD_NOW)
  {
    myHandle = dlopen(myName, RTLD_NOW);
  }

  return !BAD(myHandle);
}

OSD_Function OSD_SharedLibrary::DlSymb(const char* aName) const
{
  void (*fp)();
  fp = (void (*)())dlsym(myHandle, aName);
  if (!BAD(fp))
  {
    return (OSD_Function)fp;
  }
  else
  {
    return (OSD_Function) nullptr;
  }
}

void OSD_SharedLibrary::DlClose() const
{
  dlclose(myHandle);
}

const char* OSD_SharedLibrary::DlError() const
{
  return (char*)dlerror();
}

void OSD_SharedLibrary::Destroy()
{
  if (myName != nullptr)
  {
    delete[] myName;
    myName   = nullptr;
    myHandle = nullptr;
  }
}

#else

  #ifndef STRICT
    #define STRICT
  #endif
  #include <windows.h>

  #include <OSD_Path.hpp>
  #include <OSD_SharedLibrary.hpp>
  #include <TCollection_AsciiString.hpp>
  #include <TCollection_ExtendedString.hpp>

  #include <Standard_WarningDisableFunctionCast.hpp>

static DWORD lastDLLError;

static wchar_t errMsg[1024];
static char    errMsgA[1024];

OSD_SharedLibrary ::OSD_SharedLibrary()
{

  myHandle = NULL;
  myName   = NULL;
}

OSD_SharedLibrary ::OSD_SharedLibrary(const char* aFilename)
{

  myHandle = NULL;
  myName   = NULL;

  SetName(aFilename);
}

void OSD_SharedLibrary ::SetName(const char* aName)
{

  OSD_Path                path(aName);
  TCollection_AsciiString name(aName);

  if (myName != NULL)

    delete[] myName;

  myName = new char[strlen(aName) + 1];

  strcpy(myName, aName);

  name = path.Name();
  name.AssignCat(path.Extension());

  TCollection_ExtendedString nameW(name);
  #ifndef OCCT_UWP
  myHandle = GetModuleHandleW(nameW.ToWideString());
  #else
  myHandle = LoadPackagedLibrary(nameW.ToWideString(), NULL);
  FreeLibrary((HMODULE)myHandle);
  #endif
}

const char* OSD_SharedLibrary ::Name() const
{

  return myName;
}

bool OSD_SharedLibrary ::DlOpen(const OSD_LoadMode)
{

  bool retVal = true;

  if (myHandle == NULL)
  {
    TCollection_ExtendedString myNameW(myName);
  #ifndef OCCT_UWP
    myHandle =
      (HINSTANCE)LoadLibraryExW(myNameW.ToWideString(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
  #else
    myHandle = (HINSTANCE)LoadPackagedLibrary(myNameW.ToWideString(), NULL);
  #endif
    if (myHandle == NULL)
    {
      lastDLLError = GetLastError();
      retVal       = false;
    }
  }

  return retVal;
}

OSD_Function OSD_SharedLibrary ::DlSymb(const char* Name) const
{

  OSD_Function func = (OSD_Function)GetProcAddress((HMODULE)myHandle, Name);

  if (func == NULL)

    lastDLLError = GetLastError();

  return func;
}

void OSD_SharedLibrary ::DlClose() const
{

  FreeLibrary((HMODULE)myHandle);
}

const char* OSD_SharedLibrary ::DlError() const
{

  FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                 0,
                 lastDLLError,
                 MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                 errMsg,
                 1024,
                 (va_list*)&myName);

  WideCharToMultiByte(CP_UTF8, 0, errMsg, -1, errMsgA, sizeof(errMsgA), NULL, NULL);
  return errMsgA;
}

void OSD_SharedLibrary ::Destroy()
{

  if (myName != NULL)
    delete[] myName;
}

#endif
