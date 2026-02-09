#pragma once

#include <Standard.hpp>

#include <OSD_Path.hpp>
#include <OSD_Error.hpp>

class OSD_Protection;
class Quantity_Date;

class OSD_FileNode
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void Path(OSD_Path& Name) const;

  Standard_EXPORT void SetPath(const OSD_Path& Name);

  Standard_EXPORT bool Exists();

  Standard_EXPORT void Remove();

  Standard_EXPORT void Move(const OSD_Path& NewPath);

  Standard_EXPORT void Copy(const OSD_Path& ToPath);

  Standard_EXPORT OSD_Protection Protection();

  Standard_EXPORT void SetProtection(const OSD_Protection& Prot);

  Standard_EXPORT Quantity_Date AccessMoment();

  Standard_EXPORT Quantity_Date CreationMoment();

  Standard_EXPORT bool Failed() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Perror();

  Standard_EXPORT int Error() const;

protected:
  Standard_EXPORT OSD_FileNode();

  Standard_EXPORT OSD_FileNode(const OSD_Path& Name);

  ~OSD_FileNode() = default;

protected:
  OSD_Path  myPath;
  OSD_Error myError;
};
