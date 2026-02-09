#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <OSD_SingleProtection.hpp>

class OSD_Protection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Protection();

  Standard_EXPORT OSD_Protection(const OSD_SingleProtection System,
                                 const OSD_SingleProtection User,
                                 const OSD_SingleProtection Group,
                                 const OSD_SingleProtection World);

  Standard_EXPORT void Values(OSD_SingleProtection& System,
                              OSD_SingleProtection& User,
                              OSD_SingleProtection& Group,
                              OSD_SingleProtection& World);

  Standard_EXPORT void SetValues(const OSD_SingleProtection System,
                                 const OSD_SingleProtection User,
                                 const OSD_SingleProtection Group,
                                 const OSD_SingleProtection World);

  Standard_EXPORT void SetSystem(const OSD_SingleProtection priv);

  Standard_EXPORT void SetUser(const OSD_SingleProtection priv);

  Standard_EXPORT void SetGroup(const OSD_SingleProtection priv);

  Standard_EXPORT void SetWorld(const OSD_SingleProtection priv);

  Standard_EXPORT OSD_SingleProtection System() const;

  Standard_EXPORT OSD_SingleProtection User() const;

  Standard_EXPORT OSD_SingleProtection Group() const;

  Standard_EXPORT OSD_SingleProtection World() const;

  Standard_EXPORT void Add(OSD_SingleProtection& aProt, const OSD_SingleProtection aRight);

  Standard_EXPORT void Sub(OSD_SingleProtection& aProt, const OSD_SingleProtection aRight);

  friend class OSD_FileNode;
  friend class OSD_File;
  friend class OSD_Directory;

private:
  Standard_EXPORT int Internal() const;

  OSD_SingleProtection s;
  OSD_SingleProtection u;
  OSD_SingleProtection g;
  OSD_SingleProtection w;
};
