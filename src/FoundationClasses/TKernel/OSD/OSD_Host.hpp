#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <OSD_Error.hpp>
#include <OSD_SysType.hpp>

enum OSD_OEMType
{
  OSD_Unavailable,
  OSD_SUN,
  OSD_DEC,
  OSD_SGI,
  OSD_NEC,
  OSD_MAC,
  OSD_PC,
  OSD_HP,
  OSD_IBM,
  OSD_VAX,
  OSD_LIN,
  OSD_AIX
};

class OSD_Host
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Host();

  Standard_EXPORT TCollection_AsciiString SystemVersion();

  Standard_EXPORT OSD_SysType SystemId() const;

  Standard_EXPORT TCollection_AsciiString HostName();

  Standard_EXPORT int AvailableMemory();

  Standard_EXPORT TCollection_AsciiString InternetAddress();

  Standard_EXPORT OSD_OEMType MachineType();

  Standard_EXPORT bool Failed() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Perror();

  Standard_EXPORT int Error() const;

private:
  TCollection_AsciiString myName;
  OSD_Error               myError;
};
