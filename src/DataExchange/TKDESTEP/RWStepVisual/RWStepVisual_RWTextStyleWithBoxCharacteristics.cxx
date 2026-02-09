

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWTextStyleWithBoxCharacteristics.hpp"
#include <Standard_Real.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_TextStyleForDefinedFont.hpp>
#include <StepVisual_TextStyleWithBoxCharacteristics.hpp>

RWStepVisual_RWTextStyleWithBoxCharacteristics::RWStepVisual_RWTextStyleWithBoxCharacteristics() =
  default;

void RWStepVisual_RWTextStyleWithBoxCharacteristics::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepVisual_TextStyleWithBoxCharacteristics>& ent) const
{

  if (!data->CheckNbParams(num,
                           3,
                           ach,
                           "text_style_with_box_characteristics has not 3 parameter(s)"))
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

  int                     numr, numpr;
  TCollection_AsciiString TypeHeigth("BOX_HEIGHT");
  TCollection_AsciiString TypeWidth("BOX_WIDTH");
  TCollection_AsciiString TypeSlant("BOX_SLANT_ANGLE");
  TCollection_AsciiString TypeRotate("BOX_ROTATE_ANGLE");
  TCollection_AsciiString TrueType;

  occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>> aCharacteristics;
  double                                                               aCharacteristicsItem;
  StepVisual_BoxCharacteristicSelect                                   aBoxCharacteristicSelect;

  int nsub3;
  nsub3 = data->SubListNumber(num, 3, false);
  if (nsub3 != 0)
  {
    int nb3          = data->NbParams(nsub3);
    aCharacteristics = new NCollection_HArray1<StepVisual_BoxCharacteristicSelect>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadTypedParam(nsub3, i3, true, "characteristics", ach, numr, numpr, TrueType))
      {

        if (data->ReadReal(numr, numpr, "characteristics", ach, aCharacteristicsItem))
        {
          aBoxCharacteristicSelect.SetRealValue(aCharacteristicsItem);
          if (TrueType == TypeHeigth)
            aBoxCharacteristicSelect.SetTypeOfContent(1);
          else if (TrueType == TypeWidth)
            aBoxCharacteristicSelect.SetTypeOfContent(2);
          else if (TrueType == TypeSlant)
            aBoxCharacteristicSelect.SetTypeOfContent(3);
          else if (TrueType == TypeRotate)
            aBoxCharacteristicSelect.SetTypeOfContent(4);
          else
          {
            ach->AddFail("Parameter #3 (characteristics) item has illegal TYPE");
          }
          aCharacteristics->SetValue(i3, aBoxCharacteristicSelect);
        }
        else
        {
          ach->AddFail("Parameter #3 (characteristics) item is not a REAL");
        }
      }
      else
      {
        ach->AddFail("Parameter #3 (characteristics) item is not TYPED");
      }
    }
  }
  else
  {
    ach->AddFail("Parameter #3 (characteristics) is not a LIST");
  }

  ent->Init(aName, aCharacterAppearance, aCharacteristics);
}

void RWStepVisual_RWTextStyleWithBoxCharacteristics::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepVisual_TextStyleWithBoxCharacteristics>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->CharacterAppearance());

  SW.Send(ent->Characteristics());
}

void RWStepVisual_RWTextStyleWithBoxCharacteristics::Share(
  const occ::handle<StepVisual_TextStyleWithBoxCharacteristics>& ent,
  Interface_EntityIterator&                                      iter) const
{

  iter.GetOneItem(ent->CharacterAppearance());
}
