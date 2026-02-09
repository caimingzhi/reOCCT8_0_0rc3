#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWMassUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MassUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWMassUnit::RWStepBasic_RWMassUnit() = default;

void RWStepBasic_RWMassUnit::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepBasic_MassUnit>&      ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "mass_unit"))
    return;

  occ::handle<StepBasic_DimensionalExponents> aNamedUnit_Dimensions;
  data->ReadEntity(num,
                   1,
                   "named_unit.dimensions",
                   ach,
                   STANDARD_TYPE(StepBasic_DimensionalExponents),
                   aNamedUnit_Dimensions);

  ent->Init(aNamedUnit_Dimensions);
}

void RWStepBasic_RWMassUnit::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepBasic_MassUnit>& ent) const
{

  SW.Send(ent->StepBasic_NamedUnit::Dimensions());
}

void RWStepBasic_RWMassUnit::Share(const occ::handle<StepBasic_MassUnit>& ent,
                                   Interface_EntityIterator&              iter) const
{

  iter.AddItem(ent->StepBasic_NamedUnit::Dimensions());
}
