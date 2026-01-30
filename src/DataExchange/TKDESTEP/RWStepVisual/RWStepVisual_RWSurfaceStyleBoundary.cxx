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

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleBoundary.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_SurfaceStyleBoundary.hpp>

RWStepVisual_RWSurfaceStyleBoundary::RWStepVisual_RWSurfaceStyleBoundary() = default;

void RWStepVisual_RWSurfaceStyleBoundary::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepVisual_SurfaceStyleBoundary>& ent) const
{

  // --- Number of Parameter Control ---

  if (!data->CheckNbParams(num, 1, ach, "surface_style_boundary"))
    return;

  // --- own field : styleOfBoundary ---

  occ::handle<StepVisual_CurveStyle> aStyleOfBoundary;
  // szv#4:S4163:12Mar99 `bool stat1 =` not needed
  data->ReadEntity(num,
                   1,
                   "style_of_boundary",
                   ach,
                   STANDARD_TYPE(StepVisual_CurveStyle),
                   aStyleOfBoundary);

  //--- Initialisation of the read entity ---

  ent->Init(aStyleOfBoundary);
}

void RWStepVisual_RWSurfaceStyleBoundary::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepVisual_SurfaceStyleBoundary>& ent) const
{

  // --- own field : styleOfBoundary ---

  SW.Send(ent->StyleOfBoundary());
}

void RWStepVisual_RWSurfaceStyleBoundary::Share(
  const occ::handle<StepVisual_SurfaceStyleBoundary>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.GetOneItem(ent->StyleOfBoundary());
}
