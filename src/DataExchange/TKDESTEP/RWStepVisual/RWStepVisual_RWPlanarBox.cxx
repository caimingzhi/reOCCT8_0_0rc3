

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPlanarBox.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PlanarBox.hpp>

RWStepVisual_RWPlanarBox::RWStepVisual_RWPlanarBox() = default;

void RWStepVisual_RWPlanarBox::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepVisual_PlanarBox>&    ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "planar_box"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  double aSizeInX;

  data->ReadReal(num, 2, "size_in_x", ach, aSizeInX);

  double aSizeInY;

  data->ReadReal(num, 3, "size_in_y", ach, aSizeInY);

  StepGeom_Axis2Placement aPlacement;

  data->ReadEntity(num, 4, "placement", ach, aPlacement);

  ent->Init(aName, aSizeInX, aSizeInY, aPlacement);
}

void RWStepVisual_RWPlanarBox::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepVisual_PlanarBox>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SizeInX());

  SW.Send(ent->SizeInY());

  SW.Send(ent->Placement().Value());
}

void RWStepVisual_RWPlanarBox::Share(const occ::handle<StepVisual_PlanarBox>& ent,
                                     Interface_EntityIterator&                iter) const
{

  iter.GetOneItem(ent->Placement().Value());
}
