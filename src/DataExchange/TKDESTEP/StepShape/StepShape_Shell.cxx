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

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_OpenShell.hpp>
#include <StepShape_Shell.hpp>

StepShape_Shell::StepShape_Shell() = default;

int StepShape_Shell::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_OpenShell)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ClosedShell)))
    return 2;
  return 0;
}

occ::handle<StepShape_OpenShell> StepShape_Shell::OpenShell() const
{
  return GetCasted(StepShape_OpenShell, Value());
}

occ::handle<StepShape_ClosedShell> StepShape_Shell::ClosedShell() const
{
  return GetCasted(StepShape_ClosedShell, Value());
}
