#include "RWStepDimTol_RWGeometricToleranceWithModifiers.hpp"

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_GeometricToleranceWithModifiers.hpp>
#include <StepDimTol_GeometricToleranceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepDimTol_RWGeometricToleranceWithModifiers::RWStepDimTol_RWGeometricToleranceWithModifiers() =
  default;

void RWStepDimTol_RWGeometricToleranceWithModifiers::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "geometric_tolerance_with_modifiers"))
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

  occ::handle<NCollection_HArray1<StepDimTol_GeometricToleranceModifier>> aModifiers;
  int                                                                     sub5 = 0;
  if (data->ReadSubList(num, 5, "modifiers", ach, sub5))
  {
    int nb0    = data->NbParams(sub5);
    aModifiers = new NCollection_HArray1<StepDimTol_GeometricToleranceModifier>(1, nb0);
    int num2   = sub5;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepDimTol_GeometricToleranceModifier anIt0 = StepDimTol_GTMMaximumMaterialRequirement;
      if (data->ParamType(num2, i0) == Interface_ParamEnum)
      {
        const char* text = data->ParamCValue(num2, i0);
        if (strcmp(text, ".ANY_CROSS_SECTION.") == 0)
          anIt0 = StepDimTol_GTMAnyCrossSection;
        else if (strcmp(text, ".COMMON_ZONE.") == 0)
          anIt0 = StepDimTol_GTMCommonZone;
        else if (strcmp(text, ".EACH_RADIAL_ELEMENT.") == 0)
          anIt0 = StepDimTol_GTMEachRadialElement;
        else if (strcmp(text, ".FREE_STATE.") == 0)
          anIt0 = StepDimTol_GTMFreeState;
        else if (strcmp(text, ".LEAST_MATERIAL_REQUIREMENT.") == 0)
          anIt0 = StepDimTol_GTMLeastMaterialRequirement;
        else if (strcmp(text, ".LINE_ELEMENT.") == 0)
          anIt0 = StepDimTol_GTMLineElement;
        else if (strcmp(text, ".MAJOR_DIAMETER.") == 0)
          anIt0 = StepDimTol_GTMMajorDiameter;
        else if (strcmp(text, ".MAXIMUM_MATERIAL_REQUIREMENT.") == 0)
          anIt0 = StepDimTol_GTMMaximumMaterialRequirement;
        else if (strcmp(text, ".MINOR_DIAMETER.") == 0)
          anIt0 = StepDimTol_GTMMinorDiameter;
        else if (strcmp(text, ".NOT_CONVEX.") == 0)
          anIt0 = StepDimTol_GTMNotConvex;
        else if (strcmp(text, ".PITCH_DIAMETER.") == 0)
          anIt0 = StepDimTol_GTMPitchDiameter;
        else if (strcmp(text, ".RECIPROCITY_REQUIREMENT.") == 0)
          anIt0 = StepDimTol_GTMReciprocityRequirement;
        else if (strcmp(text, ".SEPARATE_REQUIREMENT.") == 0)
          anIt0 = StepDimTol_GTMSeparateRequirement;
        else if (strcmp(text, ".STATISTICAL_TOLERANCE.") == 0)
          anIt0 = StepDimTol_GTMStatisticalTolerance;
        else if (strcmp(text, ".TANGENT_PLANE.") == 0)
          anIt0 = StepDimTol_GTMTangentPlane;
        else
          ach->AddFail("Parameter #5 (modifiers) has not allowed value");
      }
      else
        ach->AddFail("Parameter #5 (modifier) is not set of enumerations");
      aModifiers->SetValue(i0, anIt0);
    }
  }

  ent->Init(aName, aDescription, aMagnitude, aTolerancedShapeAspect, aModifiers);
}

void RWStepDimTol_RWGeometricToleranceWithModifiers::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->Magnitude());

  SW.Send(ent->TolerancedShapeAspect().Value());

  SW.OpenSub();
  for (int i = 1; i <= ent->NbModifiers(); i++)
  {
    switch (ent->ModifierValue(i))
    {
      case StepDimTol_GTMAnyCrossSection:
        SW.SendEnum(".ANY_CROSS_SECTION.");
        break;
      case StepDimTol_GTMCommonZone:
        SW.SendEnum(".COMMON_ZONE.");
        break;
      case StepDimTol_GTMEachRadialElement:
        SW.SendEnum(".EACH_RADIAL_ELEMENT.");
        break;
      case StepDimTol_GTMFreeState:
        SW.SendEnum(".FREE_STATE.");
        break;
      case StepDimTol_GTMLeastMaterialRequirement:
        SW.SendEnum(".LEAST_MATERIAL_REQUIREMENT.");
        break;
      case StepDimTol_GTMLineElement:
        SW.SendEnum(".LINE_ELEMENT.");
        break;
      case StepDimTol_GTMMajorDiameter:
        SW.SendEnum(".MAJOR_DIAMETER.");
        break;
      case StepDimTol_GTMMaximumMaterialRequirement:
        SW.SendEnum(".MAXIMUM_MATERIAL_REQUIREMENT.");
        break;
      case StepDimTol_GTMMinorDiameter:
        SW.SendEnum(".MINOR_DIAMETER.");
        break;
      case StepDimTol_GTMNotConvex:
        SW.SendEnum(".NOT_CONVEX.");
        break;
      case StepDimTol_GTMPitchDiameter:
        SW.SendEnum(".PITCH_DIAMETER.");
        break;
      case StepDimTol_GTMReciprocityRequirement:
        SW.SendEnum(".RECIPROCITY_REQUIREMENT.");
        break;
      case StepDimTol_GTMSeparateRequirement:
        SW.SendEnum(".SEPARATE_REQUIREMENT.");
        break;
      case StepDimTol_GTMStatisticalTolerance:
        SW.SendEnum(".STATISTICAL_TOLERANCE.");
        break;
      case StepDimTol_GTMTangentPlane:
        SW.SendEnum(".TANGENT_PLANE.");
        break;
    }
  }
  SW.CloseSub();
}

void RWStepDimTol_RWGeometricToleranceWithModifiers::Share(
  const occ::handle<StepDimTol_GeometricToleranceWithModifiers>& ent,
  Interface_EntityIterator&                                      iter) const
{

  iter.AddItem(ent->Magnitude());

  iter.AddItem(ent->TolerancedShapeAspect().Value());
}
