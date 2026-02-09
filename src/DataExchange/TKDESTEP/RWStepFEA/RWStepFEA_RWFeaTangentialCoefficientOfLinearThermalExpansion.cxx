#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion.hpp>

RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion::
  RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion() = default;

void RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                  data,
  const int                                                                    num,
  occ::handle<Interface_Check>&                                                ach,
  const occ::handle<StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "fea_tangential_coefficient_of_linear_thermal_expansion"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  StepFEA_SymmetricTensor23d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  ent->Init(aRepresentationItem_Name, aFeaConstants);
}

void RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion::WriteStep(
  StepData_StepWriter&                                                         SW,
  const occ::handle<StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->FeaConstants().Value());
}

void RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion::Share(
  const occ::handle<StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion>& ent,
  Interface_EntityIterator&                                                    iter) const
{

  iter.AddItem(ent->FeaConstants().Value());
}
