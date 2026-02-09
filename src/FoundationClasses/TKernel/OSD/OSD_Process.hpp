#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <OSD_Error.hpp>
#include <TCollection_AsciiString.hpp>

class Quantity_Date;
class OSD_Path;

#ifdef SetCurrentDirectory
  #undef SetCurrentDirectory
#endif

class OSD_Process
{
public:
  Standard_EXPORT static TCollection_AsciiString ExecutablePath();

  Standard_EXPORT static TCollection_AsciiString ExecutableFolder();

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT OSD_Process();

  Standard_EXPORT void TerminalType(TCollection_AsciiString& Name);

  Standard_EXPORT Quantity_Date SystemDate();

  Standard_EXPORT TCollection_AsciiString UserName();

  Standard_EXPORT bool IsSuperUser();

  Standard_EXPORT int ProcessId();

  Standard_EXPORT OSD_Path CurrentDirectory();

  Standard_EXPORT void SetCurrentDirectory(const OSD_Path& where);

  Standard_EXPORT bool Failed() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Perror();

  Standard_EXPORT int Error() const;

private:
  OSD_Error myError;
};
