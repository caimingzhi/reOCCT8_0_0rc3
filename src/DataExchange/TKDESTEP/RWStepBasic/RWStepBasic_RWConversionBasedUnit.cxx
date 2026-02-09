

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWConversionBasedUnit.hpp"
#include <StepBasic_ConversionBasedUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWConversionBasedUnit::RWStepBasic_RWConversionBasedUnit() = default;

void RWStepBasic_RWConversionBasedUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepBasic_ConversionBasedUnit>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "conversion_based_unit"))
    return;

  occ::handle<StepBasic_DimensionalExponents> aDimensions;

  data->ReadEntity(num,
                   1,
                   "dimensions",
                   ach,
                   STANDARD_TYPE(StepBasic_DimensionalExponents),
                   aDimensions);

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<Standard_Transient> aConversionFactor;

  data->ReadEntity(num,
                   3,
                   "conversion_factor",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aConversionFactor);

  ent->Init(aDimensions, aName, aConversionFactor);
}

void RWStepBasic_RWConversionBasedUnit::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepBasic_ConversionBasedUnit>& ent) const
{

  SW.Send(ent->Dimensions());

  SW.Send(ent->Name());

  SW.Send(ent->ConversionFactor());
}

void RWStepBasic_RWConversionBasedUnit::Share(const occ::handle<StepBasic_ConversionBasedUnit>& ent,
                                              Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Dimensions());

  iter.GetOneItem(ent->ConversionFactor());
}
