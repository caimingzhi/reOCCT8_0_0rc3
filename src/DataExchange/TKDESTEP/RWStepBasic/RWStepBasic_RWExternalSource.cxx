#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWExternalSource.hpp"
#include <StepBasic_ExternalSource.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWExternalSource::RWStepBasic_RWExternalSource() = default;

void RWStepBasic_RWExternalSource::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepBasic_ExternalSource>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "external_source"))
    return;

  StepBasic_SourceItem aSourceId;
  data->ReadEntity(num, 1, "source_id", ach, aSourceId);

  ent->Init(aSourceId);
}

void RWStepBasic_RWExternalSource::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepBasic_ExternalSource>& ent) const
{

  SW.Send(ent->SourceId().Value());
}

void RWStepBasic_RWExternalSource::Share(const occ::handle<StepBasic_ExternalSource>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.AddItem(ent->SourceId().Value());
}
