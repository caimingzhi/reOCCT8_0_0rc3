#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWParametricCurve3dElementCoordinateDirection.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_ParametricCurve3dElementCoordinateDirection.hpp>
#include <StepGeom_Direction.hpp>

RWStepFEA_RWParametricCurve3dElementCoordinateDirection::
  RWStepFEA_RWParametricCurve3dElementCoordinateDirection() = default;

void RWStepFEA_RWParametricCurve3dElementCoordinateDirection::ReadStep(
  const occ::handle<StepData_StepReaderData>&                             data,
  const int                                                               num,
  occ::handle<Interface_Check>&                                           ach,
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "parametric_curve3d_element_coordinate_direction"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<StepGeom_Direction> aOrientation;
  data->ReadEntity(num, 2, "orientation", ach, STANDARD_TYPE(StepGeom_Direction), aOrientation);

  ent->Init(aRepresentationItem_Name, aOrientation);
}

void RWStepFEA_RWParametricCurve3dElementCoordinateDirection::WriteStep(
  StepData_StepWriter&                                                    SW,
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->Orientation());
}

void RWStepFEA_RWParametricCurve3dElementCoordinateDirection::Share(
  const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& ent,
  Interface_EntityIterator&                                               iter) const
{

  iter.AddItem(ent->Orientation());
}
