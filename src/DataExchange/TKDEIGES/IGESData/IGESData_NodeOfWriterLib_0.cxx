// Created on: 1992-04-06
// Created by: Christian CAILLET
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

#include <IGESData_NodeOfWriterLib.hpp>

#include <Standard_Type.hpp>

#include <IGESData_GlobalNodeOfWriterLib.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_ReadWriteModule.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_WriterLib.hpp>

IGESData_NodeOfWriterLib::IGESData_NodeOfWriterLib() = default;

void IGESData_NodeOfWriterLib::AddNode(const occ::handle<IGESData_GlobalNodeOfWriterLib>& anode)
{
  if (thenode == anode)
    return;
  if (thenext.IsNull())
  {
    if (thenode.IsNull())
      thenode = anode;
    else
    {
      thenext = new IGESData_NodeOfWriterLib;
      thenext->AddNode(anode);
    }
  }
  else
    thenext->AddNode(anode);
}

const occ::handle<IGESData_ReadWriteModule>& IGESData_NodeOfWriterLib::Module() const
{
  return thenode->Module();
}

const occ::handle<IGESData_Protocol>& IGESData_NodeOfWriterLib::Protocol() const
{
  return thenode->Protocol();
}

const occ::handle<IGESData_NodeOfWriterLib>& IGESData_NodeOfWriterLib::Next() const
{
  return thenext;
}
