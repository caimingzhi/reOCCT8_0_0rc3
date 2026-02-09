#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class TCollection_AsciiString;
class TCollection_ExtendedString;

class Message_MsgFile
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool Load(const char* theDirName, const char* theFileName);

  Standard_EXPORT static bool LoadFile(const char* theFName);

  Standard_EXPORT static bool LoadFromEnv(const char* theEnvName,
                                          const char* theFileName,
                                          const char* theLangExt = "");

  Standard_EXPORT static bool LoadFromString(const char* theContent, const int theLength = -1);

  Standard_EXPORT static bool AddMsg(const TCollection_AsciiString&    key,
                                     const TCollection_ExtendedString& text);

  Standard_EXPORT static bool HasMsg(const TCollection_AsciiString& key);

  Standard_EXPORT static const TCollection_ExtendedString& Msg(const char* key);

  Standard_EXPORT static const TCollection_ExtendedString& Msg(const TCollection_AsciiString& key);
};
