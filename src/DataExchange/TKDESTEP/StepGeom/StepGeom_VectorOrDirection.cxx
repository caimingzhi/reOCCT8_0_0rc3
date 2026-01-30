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
#include <StepGeom_Direction.hpp>
#include <StepGeom_Vector.hpp>
#include <StepGeom_VectorOrDirection.hpp>

StepGeom_VectorOrDirection::StepGeom_VectorOrDirection() = default;

int StepGeom_VectorOrDirection::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Vector)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_Direction)))
    return 2;
  return 0;
}

occ::handle<StepGeom_Vector> StepGeom_VectorOrDirection::Vector() const
{
  return GetCasted(StepGeom_Vector, Value());
}

occ::handle<StepGeom_Direction> StepGeom_VectorOrDirection::Direction() const
{
  return GetCasted(StepGeom_Direction, Value());
}
