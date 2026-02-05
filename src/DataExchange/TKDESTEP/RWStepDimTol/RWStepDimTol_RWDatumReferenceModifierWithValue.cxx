#include "RWStepDimTol_RWDatumReferenceModifierWithValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_DatumReferenceModifierWithValue.hpp>

//=================================================================================================

RWStepDimTol_RWDatumReferenceModifierWithValue::RWStepDimTol_RWDatumReferenceModifierWithValue() =
  default;

//=================================================================================================

void RWStepDimTol_RWDatumReferenceModifierWithValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepDimTol_DatumReferenceModifierWithValue>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "datum_reference_modifier_with_value"))
    return;

  // own fields of DatumReferenceModifierWithValue

  StepDimTol_DatumReferenceModifierType aModifierType = StepDimTol_CircularOrCylindrical;
  if (data->ParamType(num, 1) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 1);
    if (strcmp(text, ".CIRCULAR_OR_CYLINDRICAL.") == 0)
      aModifierType = StepDimTol_CircularOrCylindrical;
    else if (strcmp(text, ".DISTANCE.") == 0)
      aModifierType = StepDimTol_Distance;
    else if (strcmp(text, ".PROJECTED.") == 0)
      aModifierType = StepDimTol_Projected;
    else if (strcmp(text, ".SPHERICAL.") == 0)
      aModifierType = StepDimTol_Spherical;
    else
      ach->AddFail("Parameter #1 (modifier_type) has not allowed value");
  }
  else
    ach->AddFail("Parameter #1 (modifier_type) is not an enumeration");

  occ::handle<StepBasic_LengthMeasureWithUnit> aModifierValue;
  data->ReadEntity(num,
                   2,
                   "modifier_value",
                   ach,
                   STANDARD_TYPE(StepBasic_LengthMeasureWithUnit),
                   aModifierValue);

  // Initialize entity
  ent->Init(aModifierType, aModifierValue);
}

//=================================================================================================

void RWStepDimTol_RWDatumReferenceModifierWithValue::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepDimTol_DatumReferenceModifierWithValue>& ent) const
{
  // own fields of DatumReferenceModifierWithValue

  switch (ent->ModifierType())
  {
    case StepDimTol_CircularOrCylindrical:
      SW.SendEnum(".CIRCULAR_OR_CYLINDRICAL.");
      break;
    case StepDimTol_Distance:
      SW.SendEnum(".DISTANCE.");
      break;
    case StepDimTol_Projected:
      SW.SendEnum(".PROJECTED.");
      break;
    case StepDimTol_Spherical:
      SW.SendEnum(".SPHERICAL.");
      break;
  }

  SW.Send(ent->ModifierValue());
}
