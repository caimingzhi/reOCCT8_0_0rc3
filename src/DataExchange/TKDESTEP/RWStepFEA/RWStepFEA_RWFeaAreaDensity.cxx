#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaAreaDensity.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaAreaDensity.hpp>

//=================================================================================================

RWStepFEA_RWFeaAreaDensity::RWStepFEA_RWFeaAreaDensity() = default;

//=================================================================================================

void RWStepFEA_RWFeaAreaDensity::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepFEA_FeaAreaDensity>&  ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "fea_area_density"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of FeaAreaDensity

  double aFeaConstant;
  data->ReadReal(num, 2, "fea_constant", ach, aFeaConstant);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aFeaConstant);
}

//=================================================================================================

void RWStepFEA_RWFeaAreaDensity::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepFEA_FeaAreaDensity>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of FeaAreaDensity

  SW.Send(ent->FeaConstant());
}

//=================================================================================================

void RWStepFEA_RWFeaAreaDensity::Share(const occ::handle<StepFEA_FeaAreaDensity>&,
                                       Interface_EntityIterator&) const
{
  // Inherited fields of RepresentationItem
  // Own fields of FeaAreaDensity
}
