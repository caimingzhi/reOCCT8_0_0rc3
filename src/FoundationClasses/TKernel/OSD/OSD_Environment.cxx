

#include <OSD_Environment.hpp>

#include <OSD_OSDError.hpp>
#include <OSD_WhoAmI.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Failure.hpp>
#include <Standard_NullObject.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_UtfString.hpp>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>

#ifndef _WIN32

static const OSD_WhoAmI Iam = OSD_WEnvironment;

OSD_Environment::OSD_Environment() = default;

OSD_Environment::OSD_Environment(const TCollection_AsciiString& Name)
{

  if (!Name.IsAscii() || Name.Search("$") != -1)
    throw Standard_ConstructionError("OSD_Environment::OSD_Environment: bad argument");

  myName = Name;
}

OSD_Environment::OSD_Environment(const TCollection_AsciiString& Name,
                                 const TCollection_AsciiString& Value)
{

  if (!Name.IsAscii() || !Value.IsAscii() ||

      Name.Search("$") != -1)
    throw Standard_ConstructionError("OSD_Environment::OSD_Environment: bad argument");

  myName  = Name;
  myValue = Value;
}

TCollection_AsciiString OSD_Environment::Name() const
{
  return myName;
}

void OSD_Environment::SetName(const TCollection_AsciiString& Name)
{
  myError.Reset();
  if (!Name.IsAscii() || Name.Search("$") != -1)
    throw Standard_ConstructionError("OSD_Environment::SetName: bad argument");

  myName = Name;
}

void OSD_Environment::SetValue(const TCollection_AsciiString& Value)
{
  if (!Value.IsAscii() || Value.Search("$") != -1)
    throw Standard_ConstructionError("OSD_Environment::Change: bad argument");

  myValue = Value;
}

TCollection_AsciiString OSD_Environment::Value()
{
  char* result = getenv(myName.ToCString());
  if (result == nullptr)
    myValue.Clear();
  else
    myValue = result;
  return myValue;
}

void OSD_Environment::Build()
{

  static char** buffer  = nullptr;
  static int    Ibuffer = 0;

  static std::mutex           aMutex;
  std::lock_guard<std::mutex> aLock(aMutex);

  int index = -1, len = myName.Length();
  for (int i = 0; i < Ibuffer; i++)
  {
    if (!strncmp(buffer[i], myName.ToCString(), len) && buffer[i][len] == '=')
    {
      index = i;
      break;
    }
  }

  char* old_value = nullptr;
  if (index >= 0)
  {
    old_value = buffer[index];
  }
  else
  {

    index = Ibuffer++;
    char** aTmp;
    aTmp = (char**)realloc(buffer, Ibuffer * sizeof(char*));
    if (aTmp)
    {
      buffer = aTmp;
    }
    else
    {
      myError.SetValue(errno, Iam, "Memory realloc failure");
      return;
    }
  }

  buffer[index] = (char*)malloc(len + myValue.Length() + 2);
  Sprintf(buffer[index], "%s=%s", myName.ToCString(), myValue.ToCString());
  putenv(buffer[index]);

  if (old_value)
    free(old_value);

  char* result = getenv(myName.ToCString());
  if (result == nullptr)
    myError.SetValue(errno, Iam, "Set Environment");
}

void OSD_Environment::Remove()
{
  myValue.Clear();
  Build();
}

void OSD_Environment::Reset()
{
  myError.Reset();
}

bool OSD_Environment::Failed() const
{
  return myError.Failed();
}

void OSD_Environment::Perror()
{
  myError.Perror();
}

int OSD_Environment::Error() const
{
  return myError.Error();
}

#else

  #include <windows.h>

  #include <NCollection_DataMap.hpp>

  #ifdef OCCT_UWP
namespace
{

  static std::mutex                                                            THE_ENV_LOCK;
  static NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString> THE_ENV_MAP;
} // namespace
  #else
static void __fastcall _set_error(OSD_Error&, DWORD);
  #endif

OSD_Environment ::OSD_Environment() {}

OSD_Environment ::OSD_Environment(const TCollection_AsciiString& Name)
{

  myName = Name;
}

OSD_Environment ::OSD_Environment(const TCollection_AsciiString& Name,
                                  const TCollection_AsciiString& Value)
{

  myName  = Name;
  myValue = Value;
}

void OSD_Environment ::SetValue(const TCollection_AsciiString& Value)
{

  myValue = Value;
}

TCollection_AsciiString OSD_Environment::Value()
{
  myValue.Clear();
  #ifdef OCCT_UWP
  std::lock_guard<std::mutex> aLock(THE_ENV_LOCK);
  THE_ENV_MAP.Find(myName, myValue);
  #else

  SetLastError(ERROR_SUCCESS);
  NCollection_UtfString<wchar_t> aNameWide(myName.ToCString());
  DWORD                          aSize = GetEnvironmentVariableW(aNameWide.ToCString(), NULL, 0);
  if (aSize == 0 && GetLastError() != ERROR_SUCCESS)
  {
    _set_error(myError, ERROR_ENVVAR_NOT_FOUND);
    return myValue;
  }

  NCollection_UtfString<char> aValue;
  aSize += 1;
  wchar_t* aBuff = new wchar_t[aSize];
  GetEnvironmentVariableW(aNameWide.ToCString(), aBuff, aSize);
  aBuff[aSize - 1] = L'\0';
  aValue.FromUnicode(aBuff);
  delete[] aBuff;
  Reset();

  myValue = aValue.ToCString();
  #endif
  return myValue;
}

void OSD_Environment ::SetName(const TCollection_AsciiString& name)
{

  myName = name;
}

TCollection_AsciiString OSD_Environment ::Name() const
{

  return myName;
}

void OSD_Environment::Build()
{
  #ifdef OCCT_UWP
  std::lock_guard<std::mutex> aLock(THE_ENV_LOCK);
  THE_ENV_MAP.Bind(myName, myValue);
  #else
  NCollection_UtfString<char> aSetVariable =
    NCollection_UtfString<char>(myName.ToCString()) + "=" + myValue.ToCString();
  _wputenv(aSetVariable.ToUtfWide().ToCString());
  #endif
}

void OSD_Environment::Remove()
{
  #ifdef OCCT_UWP
  std::lock_guard<std::mutex> aLock(THE_ENV_LOCK);
  THE_ENV_MAP.UnBind(myName);
  #else
  NCollection_UtfString<char> aSetVariable = NCollection_UtfString<char>(myName.ToCString()) + "=";
  _wputenv(aSetVariable.ToUtfWide().ToCString());
  #endif
}

bool OSD_Environment ::Failed() const
{

  return myError.Failed();
}

void OSD_Environment ::Reset()
{

  myError.Reset();
}

void OSD_Environment ::Perror()
{
  myError.Perror();
}

int OSD_Environment ::Error() const
{

  return myError.Error();
}

  #ifndef OCCT_UWP
static void __fastcall _set_error(OSD_Error& theErr, DWORD theCode)
{
  wchar_t     aBuffer[2048];
  const DWORD anErrCode = theCode != 0 ? theCode : GetLastError();
  if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                      0,
                      anErrCode,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                      aBuffer,
                      2048,
                      NULL))
  {
    theErr.SetValue(anErrCode,
                    OSD_WEnvironment,
                    TCollection_AsciiString("error code ") + (int)anErrCode);
    SetLastError(anErrCode);
  }
  else
  {
    theErr.SetValue(anErrCode, OSD_WEnvironment, TCollection_AsciiString(aBuffer));
  }
}
  #endif

#endif
