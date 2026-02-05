#include <Interface_EntityIterator.hpp>
#include "RWStepDimTol_RWDatumReference.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepDimTol_DatumReference.hpp>

//=================================================================================================

RWStepDimTol_RWDatumReference::RWStepDimTol_RWDatumReference() = default;

//=================================================================================================

void RWStepDimTol_RWDatumReference::ReadStep(
  const occ::handle<StepData_StepReaderData>&   data,
  const int                                     num,
  occ::handle<Interface_Check>&                 ach,
  const occ::handle<StepDimTol_DatumReference>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "datum_reference"))
    return;

  // Own fields of DatumReference

  int aPrecedence;
  data->ReadInteger(num, 1, "precedence", ach, aPrecedence);

  occ::handle<StepDimTol_Datum> aReferencedDatum;
  data->ReadEntity(num,
                   2,
                   "referenced_datum",
                   ach,
                   STANDARD_TYPE(StepDimTol_Datum),
                   aReferencedDatum);

  // Initialize entity
  ent->Init(aPrecedence, aReferencedDatum);
}

//=================================================================================================

void RWStepDimTol_RWDatumReference::WriteStep(
  StepData_StepWriter&                          SW,
  const occ::handle<StepDimTol_DatumReference>& ent) const
{

  // Own fields of DatumReference

  SW.Send(ent->Precedence());

  SW.Send(ent->ReferencedDatum());
}

//=================================================================================================

void RWStepDimTol_RWDatumReference::Share(const occ::handle<StepDimTol_DatumReference>& ent,
                                          Interface_EntityIterator&                     iter) const
{

  // Own fields of DatumReference

  iter.AddItem(ent->ReferencedDatum());
}
