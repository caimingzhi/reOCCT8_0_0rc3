

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWTextStyleForDefinedFont.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_TextStyleForDefinedFont.hpp>

RWStepVisual_RWTextStyleForDefinedFont::RWStepVisual_RWTextStyleForDefinedFont() = default;

void RWStepVisual_RWTextStyleForDefinedFont::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepVisual_TextStyleForDefinedFont>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "text_style_for_defined_font has not 1 parameter(s)"))
    return;

  occ::handle<StepVisual_Colour> aTextColour;

  data->ReadEntity(num, 1, "text_colour", ach, STANDARD_TYPE(StepVisual_Colour), aTextColour);

  ent->Init(aTextColour);
}

void RWStepVisual_RWTextStyleForDefinedFont::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepVisual_TextStyleForDefinedFont>& ent) const
{

  SW.Send(ent->TextColour());
}

void RWStepVisual_RWTextStyleForDefinedFont::Share(
  const occ::handle<StepVisual_TextStyleForDefinedFont>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->TextColour());
}
