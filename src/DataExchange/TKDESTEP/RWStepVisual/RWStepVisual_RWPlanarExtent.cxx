

#include "RWStepVisual_RWPlanarExtent.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_PlanarExtent.hpp>

RWStepVisual_RWPlanarExtent::RWStepVisual_RWPlanarExtent() = default;

void RWStepVisual_RWPlanarExtent::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepVisual_PlanarExtent>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "planar_extent"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  double aSizeInX;

  data->ReadReal(num, 2, "size_in_x", ach, aSizeInX);

  double aSizeInY;

  data->ReadReal(num, 3, "size_in_y", ach, aSizeInY);

  ent->Init(aName, aSizeInX, aSizeInY);
}

void RWStepVisual_RWPlanarExtent::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepVisual_PlanarExtent>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SizeInX());

  SW.Send(ent->SizeInY());
}
