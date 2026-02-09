#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductConceptContext.hpp"
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ProductConceptContext.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductConceptContext::RWStepBasic_RWProductConceptContext() = default;

void RWStepBasic_RWProductConceptContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepBasic_ProductConceptContext>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "product_concept_context"))
    return;

  occ::handle<TCollection_HAsciiString> aApplicationContextElement_Name;
  data->ReadString(num,
                   1,
                   "application_context_element.name",
                   ach,
                   aApplicationContextElement_Name);

  occ::handle<StepBasic_ApplicationContext> aApplicationContextElement_FrameOfReference;
  data->ReadEntity(num,
                   2,
                   "application_context_element.frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ApplicationContext),
                   aApplicationContextElement_FrameOfReference);

  occ::handle<TCollection_HAsciiString> aMarketSegmentType;
  data->ReadString(num, 3, "market_segment_type", ach, aMarketSegmentType);

  ent->Init(aApplicationContextElement_Name,
            aApplicationContextElement_FrameOfReference,
            aMarketSegmentType);
}

void RWStepBasic_RWProductConceptContext::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepBasic_ProductConceptContext>& ent) const
{

  SW.Send(ent->StepBasic_ApplicationContextElement::Name());

  SW.Send(ent->StepBasic_ApplicationContextElement::FrameOfReference());

  SW.Send(ent->MarketSegmentType());
}

void RWStepBasic_RWProductConceptContext::Share(
  const occ::handle<StepBasic_ProductConceptContext>& ent,
  Interface_EntityIterator&                           iter) const
{

  iter.AddItem(ent->StepBasic_ApplicationContextElement::FrameOfReference());
}
