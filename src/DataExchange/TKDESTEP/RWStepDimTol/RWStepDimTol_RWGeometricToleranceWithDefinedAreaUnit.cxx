#include "RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepBasic_LengthMeasureWithUnit.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_GeometricToleranceWithDefinedAreaUnit.hpp>

RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit::
  RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit() = default;

void RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&                          data,
  const int                                                            num,
  occ::handle<Interface_Check>&                                        ach,
  const occ::handle<StepDimTol_GeometricToleranceWithDefinedAreaUnit>& ent) const
{

  if (!data->CheckNbParams(num, 7, ach, "geometric_tolerance_with_defined_area_unit"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "geometric_tolerance.name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "geometric_tolerance.description", ach, aDescription);

  occ::handle<Standard_Transient> aMagnitude;
  data->ReadEntity(num,
                   3,
                   "geometric_tolerance.magnitude",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aMagnitude);

  StepDimTol_GeometricToleranceTarget aTolerancedShapeAspect;
  data->ReadEntity(num,
                   4,
                   "geometric_tolerance.toleranced_shape_aspect",
                   ach,
                   aTolerancedShapeAspect);

  occ::handle<StepBasic_LengthMeasureWithUnit> anUnitSize;
  data->ReadEntity(num,
                   5,
                   "geometric_tolerance_with_defined_unit.unit_size",
                   ach,
                   STANDARD_TYPE(StepBasic_LengthMeasureWithUnit),
                   anUnitSize);

  StepDimTol_AreaUnitType aType = StepDimTol_Circular;
  if (data->ParamType(num, 6) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 6);
    if (strcmp(text, ".CIRCULAR.") == 0)
      aType = StepDimTol_Circular;
    else if (strcmp(text, ".RECTANGULAR.") == 0)
      aType = StepDimTol_Rectangular;
    else if (strcmp(text, ".SQUARE.") == 0)
      aType = StepDimTol_Square;
    else
      ach->AddFail("Parameter #6 (area_type) has not allowed value");
  }
  else
    ach->AddFail("Parameter #6 (area_type) is not enumerations");

  occ::handle<StepBasic_LengthMeasureWithUnit> aSecondUnitSize;
  bool                                         hasSecondUnitSize = data->IsParamDefined(num, 7);
  if (hasSecondUnitSize)
    data->ReadEntity(num,
                     7,
                     "second_unit_size",
                     ach,
                     STANDARD_TYPE(StepBasic_LengthMeasureWithUnit),
                     aSecondUnitSize);

  ent->Init(aName,
            aDescription,
            aMagnitude,
            aTolerancedShapeAspect,
            anUnitSize,
            aType,
            hasSecondUnitSize,
            aSecondUnitSize);
}

void RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit::WriteStep(
  StepData_StepWriter&                                                 SW,
  const occ::handle<StepDimTol_GeometricToleranceWithDefinedAreaUnit>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Magnitude());

  SW.Send(ent->TolerancedShapeAspect().Value());

  SW.Send(ent->UnitSize());

  switch (ent->AreaType())
  {
    case StepDimTol_Circular:
      SW.SendEnum(".CIRCULAR.");
      break;
    case StepDimTol_Rectangular:
      SW.SendEnum(".RECTANGULAR.");
      break;
    case StepDimTol_Square:
      SW.SendEnum(".SQUARE.");
      break;
  }

  if (ent->HasSecondUnitSize())
    SW.Send(ent->SecondUnitSize());
  else
    SW.SendUndef();
}

void RWStepDimTol_RWGeometricToleranceWithDefinedAreaUnit::Share(
  const occ::handle<StepDimTol_GeometricToleranceWithDefinedAreaUnit>& ent,
  Interface_EntityIterator&                                            iter) const
{

  iter.AddItem(ent->Magnitude());

  iter.AddItem(ent->TolerancedShapeAspect().Value());
}
