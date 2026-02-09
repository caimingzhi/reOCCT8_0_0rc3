

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWFillAreaStyleColour.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_FillAreaStyleColour.hpp>

RWStepVisual_RWFillAreaStyleColour::RWStepVisual_RWFillAreaStyleColour() = default;

void RWStepVisual_RWFillAreaStyleColour::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepVisual_FillAreaStyleColour>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "fill_area_style_colour"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepVisual_Colour> aFillColour;

  data->ReadEntity(num, 2, "fill_colour", ach, STANDARD_TYPE(StepVisual_Colour), aFillColour);

  ent->Init(aName, aFillColour);
}

void RWStepVisual_RWFillAreaStyleColour::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepVisual_FillAreaStyleColour>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->FillColour());
}

void RWStepVisual_RWFillAreaStyleColour::Share(
  const occ::handle<StepVisual_FillAreaStyleColour>& ent,
  Interface_EntityIterator&                          iter) const
{

  iter.GetOneItem(ent->FillColour());
}
