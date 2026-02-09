

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWPlaneAngleUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_PlaneAngleUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWPlaneAngleUnit::RWStepBasic_RWPlaneAngleUnit() = default;

void RWStepBasic_RWPlaneAngleUnit::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepBasic_PlaneAngleUnit>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "plane_angle_unit"))
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

void RWStepBasic_RWPlaneAngleUnit::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepBasic_PlaneAngleUnit>& ent) const
{

  SW.Send(ent->Dimensions());
}

void RWStepBasic_RWPlaneAngleUnit::Share(const occ::handle<StepBasic_PlaneAngleUnit>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->Dimensions());
}
