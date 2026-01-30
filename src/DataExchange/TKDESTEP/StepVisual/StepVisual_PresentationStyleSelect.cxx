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
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_NullStyleMember.hpp>
#include <StepVisual_PointStyle.hpp>
#include <StepVisual_PresentationStyleSelect.hpp>
#include <StepVisual_SurfaceStyleUsage.hpp>

StepVisual_PresentationStyleSelect::StepVisual_PresentationStyleSelect() = default;

int StepVisual_PresentationStyleSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PointStyle)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_CurveStyle)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleUsage)))
    return 3;
  //	if (ent->IsKind(STANDARD_TYPE(StepVisual_SymbolStyle))) return 4;
  //	if (ent->IsKind(STANDARD_TYPE(StepVisual_FillAreaStyle))) return 5;
  //	if (ent->IsKind(STANDARD_TYPE(StepVisual_TextStyle))) return 6;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_NullStyleMember)))
    return 7;
  return 0;
}

occ::handle<StepVisual_PointStyle> StepVisual_PresentationStyleSelect::PointStyle() const
{
  return GetCasted(StepVisual_PointStyle, Value());
}

occ::handle<StepVisual_CurveStyle> StepVisual_PresentationStyleSelect::CurveStyle() const
{
  return GetCasted(StepVisual_CurveStyle, Value());
}

occ::handle<StepVisual_NullStyleMember> StepVisual_PresentationStyleSelect::NullStyle() const
{
  return GetCasted(StepVisual_NullStyleMember, Value());
}

occ::handle<StepVisual_SurfaceStyleUsage> StepVisual_PresentationStyleSelect::SurfaceStyleUsage()
  const
{
  return GetCasted(StepVisual_SurfaceStyleUsage, Value());
}
