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
#include <IGESSelect_IGESName.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_IGESName, IFSelect_Signature)

static char falsetype[] = "?";
static char voidlabel[] = "";

IGESSelect_IGESName::IGESSelect_IGESName()
    : IFSelect_Signature("IGES Name (Short Label)")
{
}

const char* IGESSelect_IGESName::Value(const occ::handle<Standard_Transient>& ent,
                                       const occ::handle<Interface_InterfaceModel>& /*model*/) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return &falsetype[0];
  occ::handle<TCollection_HAsciiString> label = igesent->ShortLabel();
  if (label.IsNull())
    return &voidlabel[0];
  return label->ToCString();
}
