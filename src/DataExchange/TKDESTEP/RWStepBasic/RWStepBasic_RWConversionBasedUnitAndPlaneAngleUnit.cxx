

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit.hpp"
#include <StepBasic_ConversionBasedUnitAndPlaneAngleUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_PlaneAngleUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit::
  RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit() = default;

void RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&                        data,
  const int                                                          num0,
  occ::handle<Interface_Check>&                                      ach,
  const occ::handle<StepBasic_ConversionBasedUnitAndPlaneAngleUnit>& ent) const
{

  int num = 0;
  data->NamedForComplex("CONVERSION_BASED_UNIT", "CNBSUN", num0, num, ach);
  if (!data->CheckNbParams(num, 2, ach, "conversion_based_unit"))
    return;
  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);
  occ::handle<Standard_Transient> aConversionFactor;
  data->ReadEntity(num,
                   2,
                   "conversion_factor",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aConversionFactor);

  data->NamedForComplex("NAMED_UNIT", "NMDUNT", num0, num, ach);
  if (!data->CheckNbParams(num, 1, ach, "named_unit"))
    return;
  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  data->ReadEntity(num,
                   1,
                   "dimensions",
                   ach,
                   STANDARD_TYPE(StepBasic_DimensionalExponents),
                   aDimensions);

  data->NamedForComplex("PLANE_ANGLE_UNIT", "PLANUN", num0, num, ach);
  if (!data->CheckNbParams(num, 0, ach, "plane_angle_unit"))
    return;

  ent->Init(aDimensions, aName, aConversionFactor);
}

void RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit::WriteStep(
  StepData_StepWriter&                                               SW,
  const occ::handle<StepBasic_ConversionBasedUnitAndPlaneAngleUnit>& ent) const
{

  SW.StartEntity("CONVERSION_BASED_UNIT");

  SW.Send(ent->Name());

  SW.Send(ent->ConversionFactor());

  SW.StartEntity("NAMED_UNIT");

  SW.Send(ent->Dimensions());

  SW.StartEntity("PLANE_ANGLE_UNIT");
}

void RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit::Share(
  const occ::handle<StepBasic_ConversionBasedUnitAndPlaneAngleUnit>& ent,
  Interface_EntityIterator&                                          iter) const
{

  iter.GetOneItem(ent->Dimensions());

  iter.GetOneItem(ent->ConversionFactor());
}
