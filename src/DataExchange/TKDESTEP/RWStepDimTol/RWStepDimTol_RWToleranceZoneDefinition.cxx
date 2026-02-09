#include "RWStepDimTol_RWToleranceZoneDefinition.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_ToleranceZoneDefinition.hpp>
#include <StepRepr_ShapeAspect.hpp>

RWStepDimTol_RWToleranceZoneDefinition::RWStepDimTol_RWToleranceZoneDefinition() = default;

void RWStepDimTol_RWToleranceZoneDefinition::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepDimTol_ToleranceZoneDefinition>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "tolerance_zone_definition"))
    return;

  occ::handle<StepDimTol_ToleranceZone> aToleranceZone;
  data->ReadEntity(num, 1, "zone", ach, STANDARD_TYPE(StepDimTol_ToleranceZone), aToleranceZone);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>> anItems;
  occ::handle<StepRepr_ShapeAspect>                                   anEnt;
  int                                                                 nbSub;
  if (data->ReadSubList(num, 2, "boundaries", ach, nbSub))
  {
    int nbElements = data->NbParams(nbSub);
    anItems        = new NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>(1, nbElements);
    for (int i = 1; i <= nbElements; i++)
    {
      if (data
            ->ReadEntity(nbSub, i, "shape_aspect", ach, STANDARD_TYPE(StepRepr_ShapeAspect), anEnt))
        anItems->SetValue(i, anEnt);
    }
  }

  ent->Init(aToleranceZone, anItems);
}

void RWStepDimTol_RWToleranceZoneDefinition::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepDimTol_ToleranceZoneDefinition>& ent) const
{

  SW.Send(ent->Zone());

  SW.OpenSub();
  for (int i = 1; i <= ent->NbBoundaries(); i++)
  {
    SW.Send(ent->BoundariesValue(i));
  }
  SW.CloseSub();
}

void RWStepDimTol_RWToleranceZoneDefinition::Share(
  const occ::handle<StepDimTol_ToleranceZoneDefinition>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.AddItem(ent->Zone());

  int i, nb = ent->NbBoundaries();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->BoundariesValue(i));
}
