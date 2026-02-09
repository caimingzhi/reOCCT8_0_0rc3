#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <OSD_Directory.hpp>
#include <TCollection_AsciiString.hpp>
#include <OSD_Error.hpp>
#include <Standard_Boolean.hpp>
class OSD_Path;

class OSD_DirectoryIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_DirectoryIterator();

  Standard_EXPORT OSD_DirectoryIterator(const OSD_Path& where, const TCollection_AsciiString& Mask);

  Standard_EXPORT void Destroy();

  ~OSD_DirectoryIterator() { Destroy(); }

  Standard_EXPORT void Initialize(const OSD_Path& where, const TCollection_AsciiString& Mask);

  Standard_EXPORT bool More();

  Standard_EXPORT void Next();

  Standard_EXPORT OSD_Directory Values();

  Standard_EXPORT bool Failed() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Perror();

  Standard_EXPORT int Error() const;

private:
  OSD_Directory           TheIterator;
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
