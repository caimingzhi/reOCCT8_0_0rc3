

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWCsgSolid.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_BooleanResult.hpp>
#include <StepShape_CsgSolid.hpp>

RWStepShape_RWCsgSolid::RWStepShape_RWCsgSolid() = default;

void RWStepShape_RWCsgSolid::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepShape_CsgSolid>&      ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "csg_solid"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_BooleanResult> aBooleanResult;

  data->ReadEntity(num,
                   2,
                   "tree_root_expression",
                   ach,
                   STANDARD_TYPE(StepShape_BooleanResult),
                   aBooleanResult);
  StepShape_CsgSelect aTreeRootExpression;
  aTreeRootExpression.SetBooleanResult(aBooleanResult);

  ent->Init(aName, aTreeRootExpression);
}

void RWStepShape_RWCsgSolid::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepShape_CsgSolid>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->TreeRootExpression().BooleanResult());
}

void RWStepShape_RWCsgSolid::Share(const occ::handle<StepShape_CsgSolid>& ent,
                                   Interface_EntityIterator&              iter) const
{

  iter.GetOneItem(ent->TreeRootExpression().BooleanResult());
}
