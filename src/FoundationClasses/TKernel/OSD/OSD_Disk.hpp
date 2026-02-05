#pragma once

#include <TCollection_AsciiString.hpp>
#include <OSD_Error.hpp>
#include <OSD_Path.hpp>

//! Disk management (a set of disk oriented tools)
class OSD_Disk
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a disk object.
  //! This is used only when a class contains a Disk field.
  //! By default, its name is initialized to current working disk.
  Standard_EXPORT OSD_Disk();

  //! Initializes the object Disk with the disk name
  //! associated to the OSD_Path.
  Standard_EXPORT OSD_Disk(const OSD_Path& Name);

  //! Initializes the object Disk with <PathName>.
  //! <PathName> specifies any file within the mounted
  //! file system.
  //! Example : OSD_Disk myDisk ("/tmp")
  //! Initializes a disk object with the mounted
  //! file associated to /tmp.
  Standard_EXPORT OSD_Disk(const char* PathName);

  //! Returns disk name of <me>.
  Standard_EXPORT OSD_Path Name() const;

  //! Instantiates <me> with <Name>.
  Standard_EXPORT void SetName(const OSD_Path& Name);

  //! Returns total disk capacity in 512 bytes blocks.
  Standard_EXPORT int DiskSize();

  //! Returns free available 512 bytes blocks on disk.
  Standard_EXPORT int DiskFree();

  //! Returns TRUE if an error occurs
  bool Failed() const { return myError.Failed(); }

  //! Resets error counter to zero
  void Reset() { myError.Reset(); }

  //! Raises OSD_Error
  void Perror() { myError.Perror(); }

  //! Returns error number if 'Failed' is TRUE.
  int Error() const { return myError.Error(); }

private:
  TCollection_AsciiString myDiskName;
  OSD_Error               myError;
};
