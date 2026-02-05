#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWConversionBasedUnitAndVolumeUnit.hpp"
#include <StepBasic_ConversionBasedUnitAndVolumeUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWConversionBasedUnitAndVolumeUnit::RWStepBasic_RWConversionBasedUnitAndVolumeUnit() =
  default;

void RWStepBasic_RWConversionBasedUnitAndVolumeUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num0,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepBasic_ConversionBasedUnitAndVolumeUnit>& ent) const
{
  int num = num0;
  // --- Instance of plex component ConversionBasedUnit ---
  if (!data->CheckNbParams(num, 2, ach, "conversion_based_unit"))
    return;
  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  // --- field : conversionFactor ---
  occ::handle<Standard_Transient> aConversionFactor;
  data->ReadEntity(num,
                   2,
                   "conversion_factor",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aConversionFactor);

  num = data->NextForComplex(num);
  if (!data->CheckNbParams(num, 1, ach, "named_unit"))
    return;
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  data->ReadEntity(num,
                   1,
                   "dimensions",
                   ach,
                   STANDARD_TYPE(StepBasic_DimensionalExponents),
                   aDimensions);

  data->NamedForComplex("VOLUME_UNIT", "VLMUNT", num0, num, ach);
  if (!data->CheckNbParams(num, 0, ach, "volume_unit"))
    return;

  ent->Init(aDimensions, aName, aConversionFactor);
}

void RWStepBasic_RWConversionBasedUnitAndVolumeUnit::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepBasic_ConversionBasedUnitAndVolumeUnit>& ent) const
{
  SW.StartEntity("CONVERSION_BASED_UNIT");
  SW.Send(ent->Name());
  SW.Send(ent->ConversionFactor());
  SW.StartEntity("NAMED_UNIT");
  SW.Send(ent->Dimensions());
  SW.StartEntity("VOLUME_UNIT");
}

void RWStepBasic_RWConversionBasedUnitAndVolumeUnit::Share(
  const occ::handle<StepBasic_ConversionBasedUnitAndVolumeUnit>& ent,
  Interface_EntityIterator&                                      iter) const
{
  iter.GetOneItem(ent->Dimensions());
  iter.GetOneItem(ent->ConversionFactor());
}
