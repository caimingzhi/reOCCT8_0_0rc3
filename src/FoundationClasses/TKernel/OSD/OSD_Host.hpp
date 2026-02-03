// Created on: 2018-03-15
// Created by: Stephan GARNAUD (ARM)
// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _OSD_Host_HeaderFile
#define _OSD_Host_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <OSD_Error.hpp>
#include <OSD_SysType.hpp>
// Copyright (c) 1992-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _OSD_OEMType_HeaderFile
#define _OSD_OEMType_HeaderFile

//! This is set of possible machine types
//! used in OSD_Host::MachineType
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

#endif // _OSD_OEMType_HeaderFile


//! Carries information about a Host
//! System version ,host name, nodename ...
class OSD_Host
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initializes current host by default.
  Standard_EXPORT OSD_Host();

  //! Returns system name and version
  Standard_EXPORT TCollection_AsciiString SystemVersion();

  //! Returns the system type (UNIX System V, UNIX BSD, MS-DOS...)
  Standard_EXPORT OSD_SysType SystemId() const;

  //! Returns host name.
  Standard_EXPORT TCollection_AsciiString HostName();

  //! Returns available memory in Kilobytes.
  Standard_EXPORT int AvailableMemory();

  //! Returns Internet address of current host.
  Standard_EXPORT TCollection_AsciiString InternetAddress();

  //! Returns type of current machine.
  Standard_EXPORT OSD_OEMType MachineType();

  //! Returns TRUE if an error occurs
  Standard_EXPORT bool Failed() const;

  //! Resets error counter to zero
  Standard_EXPORT void Reset();

  //! Raises OSD_Error
  Standard_EXPORT void Perror();

  //! Returns error number if 'Failed' is TRUE.
  Standard_EXPORT int Error() const;

private:
  TCollection_AsciiString myName;
  OSD_Error               myError;
};

#endif // _OSD_Host_HeaderFile
