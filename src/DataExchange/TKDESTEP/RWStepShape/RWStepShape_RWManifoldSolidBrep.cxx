

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWManifoldSolidBrep.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>

RWStepShape_RWManifoldSolidBrep::RWStepShape_RWManifoldSolidBrep() = default;

void RWStepShape_RWManifoldSolidBrep::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepShape_ManifoldSolidBrep>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "manifold_solid_brep"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_ConnectedFaceSet> aOuter;

  data->ReadEntity(num, 2, "outer", ach, STANDARD_TYPE(StepShape_ConnectedFaceSet), aOuter);

  ent->Init(aName, aOuter);
}

void RWStepShape_RWManifoldSolidBrep::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepShape_ManifoldSolidBrep>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Outer());
}

void RWStepShape_RWManifoldSolidBrep::Share(const occ::handle<StepShape_ManifoldSolidBrep>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Outer());
}
