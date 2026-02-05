#pragma once

#include <Standard.hpp>

#include <OSD_Path.hpp>
#include <OSD_Error.hpp>

class OSD_Protection;
class Quantity_Date;

//! A class for 'File' and 'Directory' grouping common
//! methods (file/directory manipulation tools).
//! The "file oriented" name means files or directories which are
//! in fact hard coded as files.
class OSD_FileNode
{
public:
  DEFINE_STANDARD_ALLOC

  //! Gets file name and path.
  Standard_EXPORT void Path(OSD_Path& Name) const;

  //! Sets file name and path.
  //! If a name is not found, it raises a program error.
  Standard_EXPORT void SetPath(const OSD_Path& Name);

  //! Returns TRUE if <me> exists.
  Standard_EXPORT bool Exists();

  //! Erases the FileNode from directory
  Standard_EXPORT void Remove();

  //! Moves <me> into another directory
  Standard_EXPORT void Move(const OSD_Path& NewPath);

  //! Copies <me> to another FileNode
  Standard_EXPORT void Copy(const OSD_Path& ToPath);

  // None of the existing security APIs are supported in a UWP applications
  //! Returns access mode of <me>.
  Standard_EXPORT OSD_Protection Protection();

  //! Changes protection of the FileNode
  Standard_EXPORT void SetProtection(const OSD_Protection& Prot);

  //! Returns last write access.
  //! On UNIX, AccessMoment and CreationMoment return the
  //! same value.
  Standard_EXPORT Quantity_Date AccessMoment();

  //! Returns creation date.
  //! On UNIX, AccessMoment and CreationMoment return the
  //! same value.
  Standard_EXPORT Quantity_Date CreationMoment();

  //! Returns TRUE if an error occurs
  Standard_EXPORT bool Failed() const;

  //! Resets error counter to zero
  Standard_EXPORT void Reset();

  //! Raises OSD_Error
  Standard_EXPORT void Perror();

  //! Returns error number if 'Failed' is TRUE.
  Standard_EXPORT int Error() const;

protected:
  //! Creates FileNode object
  //! This is to be used with SetPath .
  //! Allocate space for the file name and initializes this
  //! name to an empty name.
  Standard_EXPORT OSD_FileNode();

  //! Instantiates the object FileNode storing its name.
  //! If a name is not found, it raises a program error.
  Standard_EXPORT OSD_FileNode(const OSD_Path& Name);

  //! Destructor is protected for safer inheritance
  ~OSD_FileNode() = default;

protected:
  OSD_Path  myPath;
  OSD_Error myError;
};
