#pragma once

#include <OSD_FileNode.hpp>

class OSD_Directory : public OSD_FileNode
{
public:
  Standard_EXPORT static OSD_Directory BuildTemporary();

public:
  Standard_EXPORT OSD_Directory();

  Standard_EXPORT OSD_Directory(const OSD_Path& theName);

  Standard_EXPORT void Build(const OSD_Protection& Protect);
};
