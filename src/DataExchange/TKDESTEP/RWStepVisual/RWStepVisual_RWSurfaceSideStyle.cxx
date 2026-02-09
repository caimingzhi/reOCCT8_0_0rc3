

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceSideStyle.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_SurfaceSideStyle.hpp>
#include <StepVisual_SurfaceStyleElementSelect.hpp>

RWStepVisual_RWSurfaceSideStyle::RWStepVisual_RWSurfaceSideStyle() = default;

void RWStepVisual_RWSurfaceSideStyle::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepVisual_SurfaceSideStyle>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "surface_side_style"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>> aStyles;
  StepVisual_SurfaceStyleElementSelect                                   aStylesItem;
  int                                                                    nsub2;
  if (data->ReadSubList(num, 2, "styles", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aStyles = new NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2, i2, "styles", ach, aStylesItem))
        aStyles->SetValue(i2, aStylesItem);
    }
  }

  ent->Init(aName, aStyles);
}

void RWStepVisual_RWSurfaceSideStyle::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepVisual_SurfaceSideStyle>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbStyles(); i2++)
  {
    SW.Send(ent->StylesValue(i2).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWSurfaceSideStyle::Share(const occ::handle<StepVisual_SurfaceSideStyle>& ent,
                                            Interface_EntityIterator& iter) const
{

  int nbElem1 = ent->NbStyles();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->StylesValue(is1).Value());
  }
}
