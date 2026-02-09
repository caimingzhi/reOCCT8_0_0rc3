#include "RWStepDimTol_RWRunoutZoneDefinition.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_RunoutZoneDefinition.hpp>
#include <StepDimTol_RunoutZoneOrientation.hpp>
#include <StepDimTol_ToleranceZone.hpp>
#include <StepRepr_ShapeAspect.hpp>

RWStepDimTol_RWRunoutZoneDefinition::RWStepDimTol_RWRunoutZoneDefinition() = default;

void RWStepDimTol_RWRunoutZoneDefinition::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepDimTol_RunoutZoneDefinition>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "runout_zone_definition"))
    return;

  occ::handle<StepDimTol_ToleranceZone> aToleranceZone;
  data->ReadEntity(num,
                   1,
                   "tolerance_zone_definition.zone",
                   ach,
                   STANDARD_TYPE(StepDimTol_ToleranceZone),
                   aToleranceZone);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_ShapeAspect>>> anItems;
  occ::handle<StepRepr_ShapeAspect>                                   anEnt;
  int                                                                 nbSub;
  if (data->ReadSubList(num, 2, "tolerance_zone_definition.boundaries", ach, nbSub))
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

  occ::handle<StepDimTol_RunoutZoneOrientation> anOrientation;
  data->ReadEntity(num,
                   3,
                   "orientation",
                   ach,
                   STANDARD_TYPE(StepDimTol_RunoutZoneOrientation),
                   anOrientation);

  ent->Init(aToleranceZone, anItems, anOrientation);
}

void RWStepDimTol_RWRunoutZoneDefinition::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepDimTol_RunoutZoneDefinition>& ent) const
{

  SW.Send(ent->Zone());

  SW.OpenSub();
  for (int i = 1; i <= ent->NbBoundaries(); i++)
  {
    SW.Send(ent->BoundariesValue(i));
  }
  SW.CloseSub();
}

void RWStepDimTol_RWRunoutZoneDefinition::Share(
  const occ::handle<StepDimTol_RunoutZoneDefinition>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.AddItem(ent->Zone());

  int i, nb = ent->NbBoundaries();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->BoundariesValue(i));
}
