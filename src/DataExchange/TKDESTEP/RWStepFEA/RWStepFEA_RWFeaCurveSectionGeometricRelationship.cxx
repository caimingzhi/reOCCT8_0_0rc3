#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaCurveSectionGeometricRelationship.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepElement_CurveElementSectionDefinition.hpp>
#include <StepFEA_FeaCurveSectionGeometricRelationship.hpp>

//=================================================================================================

RWStepFEA_RWFeaCurveSectionGeometricRelationship::
  RWStepFEA_RWFeaCurveSectionGeometricRelationship() = default;

//=================================================================================================

void RWStepFEA_RWFeaCurveSectionGeometricRelationship::ReadStep(
  const occ::handle<StepData_StepReaderData>&                      data,
  const int                                                        num,
  occ::handle<Interface_Check>&                                    ach,
  const occ::handle<StepFEA_FeaCurveSectionGeometricRelationship>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "fea_curve_section_geometric_relationship"))
    return;

  // Own fields of FeaCurveSectionGeometricRelationship

  occ::handle<StepElement_CurveElementSectionDefinition> aSectionRef;
  data->ReadEntity(num,
                   1,
                   "section_ref",
                   ach,
                   STANDARD_TYPE(StepElement_CurveElementSectionDefinition),
                   aSectionRef);

  occ::handle<StepElement_AnalysisItemWithinRepresentation> aItem;
  data->ReadEntity(num,
                   2,
                   "item",
                   ach,
                   STANDARD_TYPE(StepElement_AnalysisItemWithinRepresentation),
                   aItem);

  // Initialize entity
  ent->Init(aSectionRef, aItem);
}

//=================================================================================================

void RWStepFEA_RWFeaCurveSectionGeometricRelationship::WriteStep(
  StepData_StepWriter&                                             SW,
  const occ::handle<StepFEA_FeaCurveSectionGeometricRelationship>& ent) const
{

  // Own fields of FeaCurveSectionGeometricRelationship

  SW.Send(ent->SectionRef());

  SW.Send(ent->Item());
}

//=================================================================================================

void RWStepFEA_RWFeaCurveSectionGeometricRelationship::Share(
  const occ::handle<StepFEA_FeaCurveSectionGeometricRelationship>& ent,
  Interface_EntityIterator&                                        iter) const
{

  // Own fields of FeaCurveSectionGeometricRelationship

  iter.AddItem(ent->SectionRef());

  iter.AddItem(ent->Item());
}
