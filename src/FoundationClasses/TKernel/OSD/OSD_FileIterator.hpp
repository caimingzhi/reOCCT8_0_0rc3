#pragma once

#include <OSD_File.hpp>
#include <OSD_Error.hpp>
#include <TCollection_AsciiString.hpp>

class OSD_Path;

class OSD_FileIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_FileIterator();

  Standard_EXPORT OSD_FileIterator(const OSD_Path& where, const TCollection_AsciiString& Mask);

  Standard_EXPORT void Destroy();

  ~OSD_FileIterator() { Destroy(); }

  Standard_EXPORT void Initialize(const OSD_Path& where, const TCollection_AsciiString& Mask);

  Standard_EXPORT bool More();

  Standard_EXPORT void Next();

  Standard_EXPORT OSD_File Values();

  Standard_EXPORT bool Failed() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Perror();

  Standard_EXPORT int Error() const;

private:
  OSD_File                TheIterator;
  bool                    myFlag;
  TCollection_AsciiString myMask;
  TCollection_AsciiString myPlace;
  OSD_Error               myError;

#ifdef _WIN32
  void* myHandle;
  void* myData;
  bool  myFirstCall;
#else
  void* myDescr;
  void* myEntry;
  int   myInit;
#endif
};
