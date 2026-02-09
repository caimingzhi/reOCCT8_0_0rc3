

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWBlock.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepShape_Block.hpp>

RWStepShape_RWBlock::RWStepShape_RWBlock() = default;

void RWStepShape_RWBlock::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepShape_Block>&         ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "block"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  data->ReadEntity(num, 2, "position", ach, STANDARD_TYPE(StepGeom_Axis2Placement3d), aPosition);

  double aX;

  data->ReadReal(num, 3, "x", ach, aX);

  double aY;

  data->ReadReal(num, 4, "y", ach, aY);

  double aZ;

  data->ReadReal(num, 5, "z", ach, aZ);

  ent->Init(aName, aPosition, aX, aY, aZ);
}

void RWStepShape_RWBlock::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepShape_Block>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position());

  SW.Send(ent->X());

  SW.Send(ent->Y());

  SW.Send(ent->Z());
}

void RWStepShape_RWBlock::Share(const occ::handle<StepShape_Block>& ent,
                                Interface_EntityIterator&           iter) const
{

  iter.GetOneItem(ent->Position());
}
