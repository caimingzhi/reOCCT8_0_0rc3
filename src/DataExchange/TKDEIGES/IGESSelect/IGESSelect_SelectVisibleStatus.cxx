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

#include <IGESData_IGESEntity.hpp>
#include <IGESSelect_SelectVisibleStatus.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectVisibleStatus, IFSelect_SelectExtract)

IGESSelect_SelectVisibleStatus::IGESSelect_SelectVisibleStatus() = default;

bool IGESSelect_SelectVisibleStatus::Sort(
  const int /*rank*/,
  const occ::handle<Standard_Transient>& ent,
  const occ::handle<Interface_InterfaceModel>& /*model*/) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return false;
  return (igesent->BlankStatus() == 0);
}

TCollection_AsciiString IGESSelect_SelectVisibleStatus::ExtractLabel() const
{
  return TCollection_AsciiString("IGES Entity, Status Visible");
}
