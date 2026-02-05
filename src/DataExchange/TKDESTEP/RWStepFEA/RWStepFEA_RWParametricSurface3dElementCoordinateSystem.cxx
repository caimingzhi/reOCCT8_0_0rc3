#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWParametricSurface3dElementCoordinateSystem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_ParametricSurface3dElementCoordinateSystem.hpp>

//=================================================================================================

RWStepFEA_RWParametricSurface3dElementCoordinateSystem::
  RWStepFEA_RWParametricSurface3dElementCoordinateSystem() = default;

//=================================================================================================

void RWStepFEA_RWParametricSurface3dElementCoordinateSystem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                            data,
  const int                                                              num,
  occ::handle<Interface_Check>&                                          ach,
  const occ::handle<StepFEA_ParametricSurface3dElementCoordinateSystem>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "parametric_surface3d_element_coordinate_system"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of ParametricSurface3dElementCoordinateSystem

  int aAxis;
  data->ReadInteger(num, 2, "axis", ach, aAxis);

  double aAngle;
  data->ReadReal(num, 3, "angle", ach, aAngle);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aAxis, aAngle);
}

//=================================================================================================

void RWStepFEA_RWParametricSurface3dElementCoordinateSystem::WriteStep(
  StepData_StepWriter&                                                   SW,
  const occ::handle<StepFEA_ParametricSurface3dElementCoordinateSystem>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of ParametricSurface3dElementCoordinateSystem

  SW.Send(ent->Axis());

  SW.Send(ent->Angle());
}

//=================================================================================================

void RWStepFEA_RWParametricSurface3dElementCoordinateSystem::Share(
  const occ::handle<StepFEA_ParametricSurface3dElementCoordinateSystem>&,
  Interface_EntityIterator&) const
{
  // Inherited fields of RepresentationItem
  // Own fields of ParametricSurface3dElementCoordinateSystem
}
