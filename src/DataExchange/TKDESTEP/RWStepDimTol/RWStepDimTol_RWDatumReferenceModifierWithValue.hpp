#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepDimTol_DatumReferenceModifierWithValue;
class StepData_StepWriter;

//! Read & Write tool for DatumReferenceModifierWithValue
class RWStepDimTol_RWDatumReferenceModifierWithValue
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepDimTol_RWDatumReferenceModifierWithValue();

  //! Reads DatumReferenceModifierWithValue
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                    data,
    const int                                                      num,
    occ::handle<Interface_Check>&                                  ach,
    const occ::handle<StepDimTol_DatumReferenceModifierWithValue>& ent) const;

  //! Writes DatumReferenceModifierWithValue
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                           SW,
    const occ::handle<StepDimTol_DatumReferenceModifierWithValue>& ent) const;
};
