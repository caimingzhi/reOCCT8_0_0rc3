#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaMassDensity.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaMassDensity.hpp>

//=================================================================================================

RWStepFEA_RWFeaMassDensity::RWStepFEA_RWFeaMassDensity() = default;

//=================================================================================================

void RWStepFEA_RWFeaMassDensity::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepFEA_FeaMassDensity>&  ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "fea_mass_density"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of FeaMassDensity

  double aFeaConstant;
  data->ReadReal(num, 2, "fea_constant", ach, aFeaConstant);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aFeaConstant);
}

//=================================================================================================

void RWStepFEA_RWFeaMassDensity::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepFEA_FeaMassDensity>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of FeaMassDensity

  SW.Send(ent->FeaConstant());
}

//=================================================================================================

void RWStepFEA_RWFeaMassDensity::Share(const occ::handle<StepFEA_FeaMassDensity>&,
                                       Interface_EntityIterator&) const
{
  // Inherited fields of RepresentationItem
  // Own fields of FeaMassDensity
}
