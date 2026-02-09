#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWParametricCurve3dElementCoordinateSystem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_ParametricCurve3dElementCoordinateDirection.hpp>
#include <StepFEA_ParametricCurve3dElementCoordinateSystem.hpp>

RWStepFEA_RWParametricCurve3dElementCoordinateSystem::
  RWStepFEA_RWParametricCurve3dElementCoordinateSystem() = default;

void RWStepFEA_RWParametricCurve3dElementCoordinateSystem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                          data,
  const int                                                            num,
  occ::handle<Interface_Check>&                                        ach,
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateSystem>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "parametric_curve3d_element_coordinate_system"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection> aDirection;
  data->ReadEntity(num,
                   2,
                   "direction",
                   ach,
                   STANDARD_TYPE(StepFEA_ParametricCurve3dElementCoordinateDirection),
                   aDirection);

  ent->Init(aRepresentationItem_Name, aDirection);
}

void RWStepFEA_RWParametricCurve3dElementCoordinateSystem::WriteStep(
  StepData_StepWriter&                                                 SW,
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateSystem>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->Direction());
}

void RWStepFEA_RWParametricCurve3dElementCoordinateSystem::Share(
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateSystem>& ent,
  Interface_EntityIterator&                                            iter) const
{

  iter.AddItem(ent->Direction());
}
