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
#include "RWStepBasic_RWApplicationContextElement.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationContextElement.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWApplicationContextElement::RWStepBasic_RWApplicationContextElement() = default;

void RWStepBasic_RWApplicationContextElement::ReadStep(
  const occ::handle<StepData_StepReaderData>&             data,
  const int                                               num,
  occ::handle<Interface_Check>&                           ach,
  const occ::handle<StepBasic_ApplicationContextElement>& ent) const
{

  // --- Number of Parameter Control ---

  if (!data->CheckNbParams(num, 2, ach, "application_context_element"))
    return;

  // --- own field : name ---

  occ::handle<TCollection_HAsciiString> aName;
  // szv#4:S4163:12Mar99 `bool stat1 =` not needed
  data->ReadString(num, 1, "name", ach, aName);

  // --- own field : frameOfReference ---

  occ::handle<StepBasic_ApplicationContext> aFrameOfReference;
  data->ReadEntity(num,
                   2,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ApplicationContext),
                   aFrameOfReference);

  //--- Initialisation of the read entity ---

  ent->Init(aName, aFrameOfReference);
}

void RWStepBasic_RWApplicationContextElement::WriteStep(
  StepData_StepWriter&                                    SW,
  const occ::handle<StepBasic_ApplicationContextElement>& ent) const
{

  // --- own field : name ---

  SW.Send(ent->Name());

  // --- own field : frameOfReference ---

  SW.Send(ent->FrameOfReference());
}

void RWStepBasic_RWApplicationContextElement::Share(
  const occ::handle<StepBasic_ApplicationContextElement>& ent,
  Interface_EntityIterator&                               iter) const
{

  iter.GetOneItem(ent->FrameOfReference());
}
