#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaSecantCoefficientOfLinearThermalExpansion.hpp>

RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion::
  RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion() = default;

void RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion::ReadStep(
  const occ::handle<StepData_StepReaderData>&                              data,
  const int                                                                num,
  occ::handle<Interface_Check>&                                            ach,
  const occ::handle<StepFEA_FeaSecantCoefficientOfLinearThermalExpansion>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "fea_secant_coefficient_of_linear_thermal_expansion"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  StepFEA_SymmetricTensor23d aFeaConstants;
  data->ReadEntity(num, 2, "fea_constants", ach, aFeaConstants);

  double aReferenceTemperature;
  data->ReadReal(num, 3, "reference_temperature", ach, aReferenceTemperature);

  ent->Init(aRepresentationItem_Name, aFeaConstants, aReferenceTemperature);
}

void RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion::WriteStep(
  StepData_StepWriter&                                                     SW,
  const occ::handle<StepFEA_FeaSecantCoefficientOfLinearThermalExpansion>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->FeaConstants().Value());

  SW.Send(ent->ReferenceTemperature());
}

void RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion::Share(
  const occ::handle<StepFEA_FeaSecantCoefficientOfLinearThermalExpansion>& ent,
  Interface_EntityIterator&                                                iter) const
{

  iter.AddItem(ent->FeaConstants().Value());
}
