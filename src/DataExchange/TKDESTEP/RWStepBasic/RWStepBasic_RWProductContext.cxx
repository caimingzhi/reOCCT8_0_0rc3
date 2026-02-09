

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductContext.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ProductContext.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductContext::RWStepBasic_RWProductContext() = default;

void RWStepBasic_RWProductContext::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepBasic_ProductContext>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "product_context"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepBasic_ApplicationContext> aFrameOfReference;

  data->ReadEntity(num,
                   2,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ApplicationContext),
                   aFrameOfReference);

  occ::handle<TCollection_HAsciiString> aDisciplineType;

  data->ReadString(num, 3, "discipline_type", ach, aDisciplineType);

  ent->Init(aName, aFrameOfReference, aDisciplineType);
}

void RWStepBasic_RWProductContext::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepBasic_ProductContext>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->FrameOfReference());

  SW.Send(ent->DisciplineType());
}

void RWStepBasic_RWProductContext::Share(const occ::handle<StepBasic_ProductContext>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->FrameOfReference());
}
