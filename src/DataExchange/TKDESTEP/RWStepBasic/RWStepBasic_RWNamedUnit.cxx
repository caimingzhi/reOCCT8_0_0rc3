

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWNamedUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_NamedUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWNamedUnit::RWStepBasic_RWNamedUnit() = default;

void RWStepBasic_RWNamedUnit::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                       const int                                   num,
                                       occ::handle<Interface_Check>&               ach,
                                       const occ::handle<StepBasic_NamedUnit>&     ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "named_unit"))
    return;

  occ::handle<StepBasic_DimensionalExponents> aDimensions;

  data->ReadEntity(num,
                   1,
                   "dimensions",
                   ach,
                   STANDARD_TYPE(StepBasic_DimensionalExponents),
                   aDimensions);

  ent->Init(aDimensions);
}

void RWStepBasic_RWNamedUnit::WriteStep(StepData_StepWriter&                    SW,
                                        const occ::handle<StepBasic_NamedUnit>& ent) const
{

  SW.Send(ent->Dimensions());
}

void RWStepBasic_RWNamedUnit::Share(const occ::handle<StepBasic_NamedUnit>& ent,
                                    Interface_EntityIterator&               iter) const
{

  iter.GetOneItem(ent->Dimensions());
}
