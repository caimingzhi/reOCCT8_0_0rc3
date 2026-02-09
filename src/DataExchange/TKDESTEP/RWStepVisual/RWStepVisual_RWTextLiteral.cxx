

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWTextLiteral.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_TextLiteral.hpp>
#include <StepVisual_TextPath.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepVisual_RWTextPath.hpp"

RWStepVisual_RWTextLiteral::RWStepVisual_RWTextLiteral() = default;

void RWStepVisual_RWTextLiteral::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepVisual_TextLiteral>&  ent) const
{

  if (!data->CheckNbParams(num, 6, ach, "text_literal has not 6 parameter(s)"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aLiteral;

  data->ReadString(num, 2, "literal", ach, aLiteral);

  StepGeom_Axis2Placement aPlacement;

  data->ReadEntity(num, 3, "placement", ach, aPlacement);

  occ::handle<TCollection_HAsciiString> aAlignment;

  data->ReadString(num, 4, "alignment", ach, aAlignment);

  StepVisual_TextPath aPath = StepVisual_tpUp;
  if (data->ParamType(num, 5) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 5);
    if (!RWStepVisual_RWTextPath::ConvertToEnum(text, aPath))
    {
      ach->AddFail("Enumeration text_path has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #5 (path) is not an enumeration");

  StepVisual_FontSelect aFont;

  data->ReadEntity(num, 6, "font", ach, aFont);

  ent->Init(aName, aLiteral, aPlacement, aAlignment, aPath, aFont);
}

void RWStepVisual_RWTextLiteral::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepVisual_TextLiteral>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Literal());

  SW.Send(ent->Placement().Value());

  SW.Send(ent->Alignment());

  SW.SendEnum(RWStepVisual_RWTextPath::ConvertToString(ent->Path()));

  SW.Send(ent->Font().Value());
}

void RWStepVisual_RWTextLiteral::Share(const occ::handle<StepVisual_TextLiteral>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->Placement().Value());

  iter.GetOneItem(ent->Font().Value());
}
