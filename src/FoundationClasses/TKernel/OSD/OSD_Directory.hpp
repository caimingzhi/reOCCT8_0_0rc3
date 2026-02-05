#pragma once

#include <OSD_FileNode.hpp>

//! Management of directories (a set of directory oriented tools)
class OSD_Directory : public OSD_FileNode
{
public:
  //! Creates a temporary Directory in current directory.
  //! This directory is automatically removed when object dies.
  Standard_EXPORT static OSD_Directory BuildTemporary();

public:
  //! Creates Directory object.
  //! It is initialized to an empty name.
  Standard_EXPORT OSD_Directory();

  //! Creates Directory object initialized with theName.
  Standard_EXPORT OSD_Directory(const OSD_Path& theName);

  //! Creates (physically) a directory.
  //! When a directory of the same name already exists, no error is
  //! returned, and only <Protect> is applied to the existing directory.
  //!
  //! If Build is used and <me> is instantiated without a name,
  //! OSDError is raised.
  Standard_EXPORT void Build(const OSD_Protection& Protect);
};
