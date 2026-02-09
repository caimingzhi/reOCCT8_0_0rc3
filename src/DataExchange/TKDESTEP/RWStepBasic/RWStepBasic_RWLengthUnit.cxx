

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWLengthUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_LengthUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWLengthUnit::RWStepBasic_RWLengthUnit() = default;

void RWStepBasic_RWLengthUnit::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepBasic_LengthUnit>&    ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "length_unit"))
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

void RWStepBasic_RWLengthUnit::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepBasic_LengthUnit>& ent) const
{

  SW.Send(ent->Dimensions());
}

void RWStepBasic_RWLengthUnit::Share(const occ::handle<StepBasic_LengthUnit>& ent,
                                     Interface_EntityIterator&                iter) const
{

  iter.GetOneItem(ent->Dimensions());
}
