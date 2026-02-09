#include <Interface_EntityIterator.hpp>
#include "RWStepDimTol_RWModifiedGeometricTolerance.hpp"
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_ModifiedGeometricTolerance.hpp>

RWStepDimTol_RWModifiedGeometricTolerance::RWStepDimTol_RWModifiedGeometricTolerance() = default;

void RWStepDimTol_RWModifiedGeometricTolerance::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepDimTol_ModifiedGeometricTolerance>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "modified_geometric_tolerance"))
    return;

  occ::handle<TCollection_HAsciiString> aGeometricTolerance_Name;
  data->ReadString(num, 1, "geometric_tolerance.name", ach, aGeometricTolerance_Name);

  occ::handle<TCollection_HAsciiString> aGeometricTolerance_Description;
  data->ReadString(num, 2, "geometric_tolerance.description", ach, aGeometricTolerance_Description);

  occ::handle<Standard_Transient> aGeometricTolerance_Magnitude;
  data->ReadEntity(num,
                   3,
                   "geometric_tolerance.magnitude",
                   ach,
                   STANDARD_TYPE(Standard_Transient),
                   aGeometricTolerance_Magnitude);

  StepDimTol_GeometricToleranceTarget aGeometricTolerance_TolerancedShapeAspect;
  data->ReadEntity(num,
                   4,
                   "geometric_tolerance.toleranced_shape_aspect",
                   ach,
                   aGeometricTolerance_TolerancedShapeAspect);

  StepDimTol_LimitCondition aModifier = StepDimTol_MaximumMaterialCondition;
  if (data->ParamType(num, 5) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 5);
    if (strcmp(text, ".MAXIMUM_MATERIAL_CONDITION.") == 0)
      aModifier = StepDimTol_MaximumMaterialCondition;
    else if (strcmp(text, ".LEAST_MATERIAL_CONDITION.") == 0)
      aModifier = StepDimTol_LeastMaterialCondition;
    else if (strcmp(text, ".REGARDLESS_OF_FEATURE_SIZE.") == 0)
      aModifier = StepDimTol_RegardlessOfFeatureSize;
    else
      ach->AddFail("Parameter #5 (modifier) has not allowed value");
  }
  else
    ach->AddFail("Parameter #5 (modifier) is not enumeration");

  ent->Init(aGeometricTolerance_Name,
            aGeometricTolerance_Description,
            aGeometricTolerance_Magnitude,
            aGeometricTolerance_TolerancedShapeAspect,
            aModifier);
}

void RWStepDimTol_RWModifiedGeometricTolerance::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepDimTol_ModifiedGeometricTolerance>& ent) const
{

  SW.Send(ent->StepDimTol_GeometricTolerance::Name());

  SW.Send(ent->StepDimTol_GeometricTolerance::Description());

  SW.Send(ent->StepDimTol_GeometricTolerance::Magnitude());

  SW.Send(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());

  switch (ent->Modifier())
  {
    case StepDimTol_MaximumMaterialCondition:
      SW.SendEnum(".MAXIMUM_MATERIAL_CONDITION.");
      break;
    case StepDimTol_LeastMaterialCondition:
      SW.SendEnum(".LEAST_MATERIAL_CONDITION.");
      break;
    case StepDimTol_RegardlessOfFeatureSize:
      SW.SendEnum(".REGARDLESS_OF_FEATURE_SIZE.");
      break;
  }
}

void RWStepDimTol_RWModifiedGeometricTolerance::Share(
  const occ::handle<StepDimTol_ModifiedGeometricTolerance>& ent,
  Interface_EntityIterator&                                 iter) const
{

  iter.AddItem(ent->StepDimTol_GeometricTolerance::Magnitude());

  iter.AddItem(ent->StepDimTol_GeometricTolerance::TolerancedShapeAspect().Value());
}
