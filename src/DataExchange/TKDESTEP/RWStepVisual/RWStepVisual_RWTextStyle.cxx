

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWTextStyle.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_TextStyle.hpp>
#include <StepVisual_TextStyleForDefinedFont.hpp>

RWStepVisual_RWTextStyle::RWStepVisual_RWTextStyle() = default;

void RWStepVisual_RWTextStyle::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepVisual_TextStyle>&    ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "text_style has not 2 parameter(s)"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepVisual_TextStyleForDefinedFont> aCharacterAppearance;

  data->ReadEntity(num,
                   2,
                   "character_appearance",
                   ach,
                   STANDARD_TYPE(StepVisual_TextStyleForDefinedFont),
                   aCharacterAppearance);

  ent->Init(aName, aCharacterAppearance);
}

void RWStepVisual_RWTextStyle::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepVisual_TextStyle>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->CharacterAppearance());
}

void RWStepVisual_RWTextStyle::Share(const occ::handle<StepVisual_TextStyle>& ent,
                                     Interface_EntityIterator&                iter) const
{

  iter.GetOneItem(ent->CharacterAppearance());
}
