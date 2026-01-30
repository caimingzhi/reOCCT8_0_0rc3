// Created on: 1999-09-08
// Created by: Andrey BETENEV
// Copyright (c) 1999-1999 Matra Datavision
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
#include <Interface_MSG.hpp>
#include "RWStepRepr_RWMeasureRepresentationItem.hpp"
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>

//=================================================================================================

RWStepRepr_RWMeasureRepresentationItem::RWStepRepr_RWMeasureRepresentationItem() = default;

//=================================================================================================

void RWStepRepr_RWMeasureRepresentationItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepRepr_MeasureRepresentationItem>& ent) const
{
  // --- Number of Parameter Control ---

  if (!data->CheckNbParams(num, 3, ach, "measure_representation_item"))
    return;

  // --- inherited from representation_item : name ---
  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  // --- inherited from measure_with_unit : value_component ---
  occ::handle<StepBasic_MeasureValueMember> mvc = new StepBasic_MeasureValueMember;
  data->ReadMember(num, 2, "value_component", ach, mvc);

  // --- inherited from measure_with_unit : unit_component ---
  StepBasic_Unit aUnitComponent;
  data->ReadEntity(num, 3, "unit_component", ach, aUnitComponent);

  //--- Initialisation of the read entity ---

  ent->Init(aName, mvc, aUnitComponent);
}

//=================================================================================================

void RWStepRepr_RWMeasureRepresentationItem::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepRepr_MeasureRepresentationItem>& ent) const
{
  // --- inherited from representation_item : name ---
  SW.Send(ent->Name());

  // --- inherited from measure_with_unit : value_component ---
  SW.Send(ent->Measure()->ValueComponentMember());

  // --- inherited from measure_with_unit : unit_component ---
  SW.Send(ent->Measure()->UnitComponent().Value());
}

//=================================================================================================

void RWStepRepr_RWMeasureRepresentationItem::Share(
  const occ::handle<StepRepr_MeasureRepresentationItem>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->Measure()->UnitComponent().Value());
}
