

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWFillAreaStyle.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_FillStyleSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepVisual_RWFillAreaStyle::RWStepVisual_RWFillAreaStyle() = default;

void RWStepVisual_RWFillAreaStyle::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepVisual_FillAreaStyle>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "fill_area_style"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>> aFillStyles;
  StepVisual_FillStyleSelect                                   aFillStylesItem;
  int                                                          nsub2;
  if (data->ReadSubList(num, 2, "fill_styles", ach, nsub2))
  {
    int nb2     = data->NbParams(nsub2);
    aFillStyles = new NCollection_HArray1<StepVisual_FillStyleSelect>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2, i2, "fill_styles", ach, aFillStylesItem))
        aFillStyles->SetValue(i2, aFillStylesItem);
    }
  }

  ent->Init(aName, aFillStyles);
}

void RWStepVisual_RWFillAreaStyle::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepVisual_FillAreaStyle>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbFillStyles(); i2++)
  {
    SW.Send(ent->FillStylesValue(i2).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWFillAreaStyle::Share(const occ::handle<StepVisual_FillAreaStyle>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  int nbElem1 = ent->NbFillStyles();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->FillStylesValue(is1).Value());
  }
}
