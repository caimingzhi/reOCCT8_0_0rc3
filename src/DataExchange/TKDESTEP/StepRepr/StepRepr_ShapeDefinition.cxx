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
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>
#include <StepRepr_ShapeDefinition.hpp>

StepRepr_ShapeDefinition::StepRepr_ShapeDefinition() = default;

int StepRepr_ShapeDefinition::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ProductDefinitionShape)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship)))
    return 3;
  return 0;
}

occ::handle<StepRepr_ProductDefinitionShape> StepRepr_ShapeDefinition::ProductDefinitionShape()
  const
{
  return GetCasted(StepRepr_ProductDefinitionShape, Value());
}

occ::handle<StepRepr_ShapeAspect> StepRepr_ShapeDefinition::ShapeAspect() const
{
  return GetCasted(StepRepr_ShapeAspect, Value());
}

occ::handle<StepRepr_ShapeAspectRelationship> StepRepr_ShapeDefinition::ShapeAspectRelationship()
  const
{
  return GetCasted(StepRepr_ShapeAspectRelationship, Value());
}
