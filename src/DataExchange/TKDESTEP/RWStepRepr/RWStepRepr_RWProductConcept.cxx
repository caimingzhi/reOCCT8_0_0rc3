#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWProductConcept.hpp"
#include <StepBasic_ProductConceptContext.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ProductConcept.hpp>

//=================================================================================================

RWStepRepr_RWProductConcept::RWStepRepr_RWProductConcept() = default;

//=================================================================================================

void RWStepRepr_RWProductConcept::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepRepr_ProductConcept>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 4, ach, "product_concept"))
    return;

  // Own fields of ProductConcept

  occ::handle<TCollection_HAsciiString> aId;
  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  bool                                  hasDescription = true;
  if (data->IsParamDefined(num, 3))
  {
    data->ReadString(num, 3, "description", ach, aDescription);
  }
  else
  {
    hasDescription = false;
  }

  occ::handle<StepBasic_ProductConceptContext> aMarketContext;
  data->ReadEntity(num,
                   4,
                   "market_context",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductConceptContext),
                   aMarketContext);

  // Initialize entity
  ent->Init(aId, aName, hasDescription, aDescription, aMarketContext);
}

//=================================================================================================

void RWStepRepr_RWProductConcept::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepRepr_ProductConcept>& ent) const
{

  // Own fields of ProductConcept

  SW.Send(ent->Id());

  SW.Send(ent->Name());

  if (ent->HasDescription())
  {
    SW.Send(ent->Description());
  }
  else
    SW.SendUndef();

  SW.Send(ent->MarketContext());
}

//=================================================================================================

void RWStepRepr_RWProductConcept::Share(const occ::handle<StepRepr_ProductConcept>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  // Own fields of ProductConcept

  iter.AddItem(ent->MarketContext());
}
