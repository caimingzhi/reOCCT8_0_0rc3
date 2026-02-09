

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCurveStyle.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_CurveStyleFontSelect.hpp>

RWStepVisual_RWCurveStyle::RWStepVisual_RWCurveStyle() = default;

void RWStepVisual_RWCurveStyle::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepVisual_CurveStyle>&   ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "curve_style"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepVisual_CurveStyleFontSelect aCurveFont;
  data->ReadEntity(num, 2, "curve_font", ach, aCurveFont);

  StepBasic_SizeSelect aCurveWidth;
  data->ReadEntity(num, 3, "curve_width", ach, aCurveWidth);

  occ::handle<StepVisual_Colour> aCurveColour;

  data->ReadEntity(num, 4, "curve_colour", ach, STANDARD_TYPE(StepVisual_Colour), aCurveColour);

  ent->Init(aName, aCurveFont, aCurveWidth, aCurveColour);
}

void RWStepVisual_RWCurveStyle::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepVisual_CurveStyle>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->CurveFont().Value());

  SW.Send(ent->CurveWidth().Value());

  SW.Send(ent->CurveColour());
}

void RWStepVisual_RWCurveStyle::Share(const occ::handle<StepVisual_CurveStyle>& ent,
                                      Interface_EntityIterator&                 iter) const
{
  iter.GetOneItem(ent->CurveFont().Value());
  iter.GetOneItem(ent->CurveColour());
}
