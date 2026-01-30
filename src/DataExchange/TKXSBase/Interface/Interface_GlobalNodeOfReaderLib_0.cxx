// Created on: 1992-02-03
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

#include <Interface_GlobalNodeOfReaderLib.hpp>

#include <Standard_Type.hpp>

#include <Interface_ReaderModule.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ReaderLib.hpp>
#include <Interface_NodeOfReaderLib.hpp>

Interface_GlobalNodeOfReaderLib::Interface_GlobalNodeOfReaderLib() = default;

void Interface_GlobalNodeOfReaderLib::Add(const occ::handle<Interface_ReaderModule>& amodule,
                                          const occ::handle<Interface_Protocol>&     aprotocol)
{
  if (themod == amodule)
    return;
  if (theprot == aprotocol)
    themod = amodule;
  else if (thenext.IsNull())
  {
    if (themod.IsNull())
    {
      themod  = amodule;
      theprot = aprotocol;
    }
    else
    {
      thenext = new Interface_GlobalNodeOfReaderLib;
      thenext->Add(amodule, aprotocol);
    }
  }
  else
    thenext->Add(amodule, aprotocol);
}

const occ::handle<Interface_ReaderModule>& Interface_GlobalNodeOfReaderLib::Module() const
{
  return themod;
}

const occ::handle<Interface_Protocol>& Interface_GlobalNodeOfReaderLib::Protocol() const
{
  return theprot;
}

const occ::handle<Interface_GlobalNodeOfReaderLib>& Interface_GlobalNodeOfReaderLib::Next() const
{
  return thenext;
}
