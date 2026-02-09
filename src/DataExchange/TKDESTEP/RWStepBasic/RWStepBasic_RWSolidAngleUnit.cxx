

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWSolidAngleUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SolidAngleUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWSolidAngleUnit::RWStepBasic_RWSolidAngleUnit() = default;

void RWStepBasic_RWSolidAngleUnit::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepBasic_SolidAngleUnit>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "solid_angle_unit"))
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

void RWStepBasic_RWSolidAngleUnit::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepBasic_SolidAngleUnit>& ent) const
{

  SW.Send(ent->Dimensions());
}

void RWStepBasic_RWSolidAngleUnit::Share(const occ::handle<StepBasic_SolidAngleUnit>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->Dimensions());
}
