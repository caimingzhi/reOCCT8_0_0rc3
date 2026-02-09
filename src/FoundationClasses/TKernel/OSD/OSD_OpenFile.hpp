#pragma once

#include <Standard_Macro.hpp>

#if defined(__cplusplus)

  #include <fstream>
  #include <TCollection_ExtendedString.hpp>
  #include <NCollection_UtfString.hpp>

  #if defined(_WIN32) && defined(__GLIBCXX__)
    #include <ext/stdio_filebuf.h>
  #endif

Standard_EXPORT FILE* OSD_OpenFile(const TCollection_ExtendedString& theName, const char* theMode);

Standard_EXPORT std::time_t OSD_FileStatCTime(const char* theName);

Standard_EXPORT int OSD_OpenFileDescriptor(const TCollection_ExtendedString& theName,
                                           ::std::ios_base::openmode         theMode);

inline bool OSD_OpenStream(::std::filebuf&                   theFileBuf,
                           const TCollection_ExtendedString& theName,
                           const std::ios_base::openmode     theMode)
{
  #if defined(_WIN32)
    #if defined(__GLIBCXX__)

  if (theFileBuf.is_open())
    return false;

  const int aFileDesc = OSD_OpenFileDescriptor(theName.ToWideString(), theMode);
  __gnu_cxx::stdio_filebuf<char> aGccBuf(aFileDesc, theMode);
  if (aGccBuf.is_open())
  {
    theFileBuf.swap(aGccBuf);
    return true;
  }
  return false;
    #else
  return theFileBuf.open(theName.ToWideString(), theMode) != 0;
    #endif
  #else

  NCollection_UtfString<char> aString(theName.ToExtString());
  return theFileBuf.open(aString.ToCString(), theMode) != nullptr;
  #endif
}

template <typename T>
inline void OSD_OpenStream(T&                                theStream,
                           const TCollection_ExtendedString& theName,
                           const std::ios_base::openmode     theMode)
{
  #if defined(_WIN32)
    #if defined(__GLIBCXX__)

  if (!OSD_OpenStream(*theStream.rdbuf(), theName, theMode))
  {
    theStream.setstate(std::ios_base::failbit);
  }
  else
  {
    theStream.clear();
  }
    #else
  theStream.open(theName.ToWideString(), theMode);
    #endif
  #else

  NCollection_UtfString<char> aString(theName.ToExtString());
  theStream.open(aString.ToCString(), theMode);
  #endif
}

template <typename T>
inline void OSD_OpenStream(T& theStream, const char* theName, const std::ios_base::openmode theMode)
{
  #if defined(_WIN32)

  const TCollection_ExtendedString aFileNameW(theName, true);
  OSD_OpenStream(theStream, aFileNameW, theMode);
  #else
  theStream.open(theName, theMode);
  #endif
}

extern "C"
{
#endif

  Standard_EXPORT FILE* OSD_OpenFile(const char* theName, const char* theMode);

#if defined(__cplusplus)
}
#endif
