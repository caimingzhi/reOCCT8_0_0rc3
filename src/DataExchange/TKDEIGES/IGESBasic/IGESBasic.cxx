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

#include <IGESBasic.hpp>
#include <IGESBasic_GeneralModule.hpp>
#include <IGESBasic_Protocol.hpp>
#include <IGESBasic_ReadWriteModule.hpp>
#include <IGESBasic_SpecificModule.hpp>
#include <IGESData.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

//  Ancillary data to work on a Package of IGES Entities with a Protocol
//  (Modules are created and loaded in appropriate libraries, once by Init)
static occ::handle<IGESBasic_Protocol> protocol;

void IGESBasic::Init()
{
  IGESData::Init(); // useful for Undefined Type or Erroneous Entities
  if (protocol.IsNull())
  {
    protocol = new IGESBasic_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESBasic_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESBasic_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESBasic_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESBasic_SpecificModule, protocol);
  }
}

occ::handle<IGESBasic_Protocol> IGESBasic::Protocol()
{
  return protocol;
}
