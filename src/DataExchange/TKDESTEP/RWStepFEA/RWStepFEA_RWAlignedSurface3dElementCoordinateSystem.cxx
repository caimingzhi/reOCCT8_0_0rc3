#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWAlignedSurface3dElementCoordinateSystem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_AlignedSurface3dElementCoordinateSystem.hpp>
#include <StepFEA_FeaAxis2Placement3d.hpp>

//=================================================================================================

RWStepFEA_RWAlignedSurface3dElementCoordinateSystem::
  RWStepFEA_RWAlignedSurface3dElementCoordinateSystem() = default;

//=================================================================================================

void RWStepFEA_RWAlignedSurface3dElementCoordinateSystem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                         data,
  const int                                                           num,
  occ::handle<Interface_Check>&                                       ach,
  const occ::handle<StepFEA_AlignedSurface3dElementCoordinateSystem>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "aligned_surface3d_element_coordinate_system"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of AlignedSurface3dElementCoordinateSystem

  occ::handle<StepFEA_FeaAxis2Placement3d> aCoordinateSystem;
  data->ReadEntity(num,
                   2,
                   "coordinate_system",
                   ach,
                   STANDARD_TYPE(StepFEA_FeaAxis2Placement3d),
                   aCoordinateSystem);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aCoordinateSystem);
}

//=================================================================================================

void RWStepFEA_RWAlignedSurface3dElementCoordinateSystem::WriteStep(
  StepData_StepWriter&                                                SW,
  const occ::handle<StepFEA_AlignedSurface3dElementCoordinateSystem>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of AlignedSurface3dElementCoordinateSystem

  SW.Send(ent->CoordinateSystem());
}

//=================================================================================================

void RWStepFEA_RWAlignedSurface3dElementCoordinateSystem::Share(
  const occ::handle<StepFEA_AlignedSurface3dElementCoordinateSystem>& ent,
  Interface_EntityIterator&                                           iter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of AlignedSurface3dElementCoordinateSystem

  iter.AddItem(ent->CoordinateSystem());
}
