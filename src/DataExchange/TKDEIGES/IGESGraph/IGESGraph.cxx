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

#include <IGESGraph.hpp>

#include <IGESBasic.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESGraph_GeneralModule.hpp>
#include <IGESGraph_Protocol.hpp>
#include <IGESGraph_ReadWriteModule.hpp>
#include <IGESGraph_SpecificModule.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

//  Ancillary data to work on a Package of IGES Entities with a Protocol
//  (Modules are created and loaded in appropriate libraries, once by Init)
static occ::handle<IGESGraph_Protocol> protocol;

void IGESGraph::Init()
{
  IGESBasic::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESGraph_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESGraph_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESGraph_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESGraph_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESGraph_SpecificModule, protocol);
  }
}

occ::handle<IGESGraph_Protocol> IGESGraph::Protocol()
{
  return protocol;
}
