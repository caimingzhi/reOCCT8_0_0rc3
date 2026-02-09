

#include "RWStepShape_RWSolidModel.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_SolidModel.hpp>

RWStepShape_RWSolidModel::RWStepShape_RWSolidModel() = default;

void RWStepShape_RWSolidModel::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepShape_SolidModel>&    ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "solid_model"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepShape_RWSolidModel::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepShape_SolidModel>& ent) const
{

  SW.Send(ent->Name());
}
