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

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPresentationLayerUsage.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_PresentationLayerUsage.hpp>
#include <StepVisual_PresentationRepresentation.hpp>

RWStepVisual_RWPresentationLayerUsage::RWStepVisual_RWPresentationLayerUsage() = default;

void RWStepVisual_RWPresentationLayerUsage::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepVisual_PresentationLayerUsage>& ent) const
{

  // --- Number of Parameter Control ---

  if (!data->CheckNbParams(num, 2, ach, "presentation_layer_usage"))
    return;

  // --- own fields
  occ::handle<StepVisual_PresentationLayerAssignment> pla;
  occ::handle<StepVisual_PresentationRepresentation>  pr;

  // szv#4:S4163:12Mar99 `bool stat1 =` not needed
  data->ReadEntity(num,
                   1,
                   "assignment",
                   ach,
                   STANDARD_TYPE(StepVisual_PresentationLayerAssignment),
                   pla);
  // szv#4:S4163:12Mar99 `stat1 =` not needed
  data->ReadEntity(num,
                   2,
                   "presentation",
                   ach,
                   STANDARD_TYPE(StepVisual_PresentationRepresentation),
                   pr);

  //--- Initialisation of the read entity ---

  ent->Init(pla, pr);
}

void RWStepVisual_RWPresentationLayerUsage::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepVisual_PresentationLayerUsage>& ent) const
{

  // --- own field : dimensions ---

  SW.Send(ent->Assignment());
  SW.Send(ent->Presentation());
}

void RWStepVisual_RWPresentationLayerUsage::Share(
  const occ::handle<StepVisual_PresentationLayerUsage>& ent,
  Interface_EntityIterator&                             iter) const
{
  iter.AddItem(ent->Assignment());
  iter.AddItem(ent->Presentation());
}
