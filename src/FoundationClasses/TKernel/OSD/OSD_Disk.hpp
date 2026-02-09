#pragma once

#include <TCollection_AsciiString.hpp>
#include <OSD_Error.hpp>
#include <OSD_Path.hpp>

class OSD_Disk
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Disk();

  Standard_EXPORT OSD_Disk(const OSD_Path& Name);

  Standard_EXPORT OSD_Disk(const char* PathName);

  Standard_EXPORT OSD_Path Name() const;

  Standard_EXPORT void SetName(const OSD_Path& Name);

  Standard_EXPORT int DiskSize();

  Standard_EXPORT int DiskFree();

  bool Failed() const { return myError.Failed(); }

  void Reset() { myError.Reset(); }

  void Perror() { myError.Perror(); }

  int Error() const { return myError.Error(); }

private:
  TCollection_AsciiString myDiskName;
  OSD_Error               myError;
};
