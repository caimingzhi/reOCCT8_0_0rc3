

#include "RWStepShape_RWVertex.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Vertex.hpp>

RWStepShape_RWVertex::RWStepShape_RWVertex() = default;

void RWStepShape_RWVertex::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepShape_Vertex>&        ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "vertex"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepShape_RWVertex::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepShape_Vertex>& ent) const
{

  SW.Send(ent->Name());
}
