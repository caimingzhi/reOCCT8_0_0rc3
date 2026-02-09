#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWAlignedCurve3dElementCoordinateSystem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_AlignedCurve3dElementCoordinateSystem.hpp>
#include <StepFEA_FeaAxis2Placement3d.hpp>

RWStepFEA_RWAlignedCurve3dElementCoordinateSystem::
  RWStepFEA_RWAlignedCurve3dElementCoordinateSystem() = default;

void RWStepFEA_RWAlignedCurve3dElementCoordinateSystem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                       data,
  const int                                                         num,
  occ::handle<Interface_Check>&                                     ach,
  const occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "aligned_curve3d_element_coordinate_system"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<StepFEA_FeaAxis2Placement3d> aCoordinateSystem;
  data->ReadEntity(num,
                   2,
                   "coordinate_system",
                   ach,
                   STANDARD_TYPE(StepFEA_FeaAxis2Placement3d),
                   aCoordinateSystem);

  ent->Init(aRepresentationItem_Name, aCoordinateSystem);
}

void RWStepFEA_RWAlignedCurve3dElementCoordinateSystem::WriteStep(
  StepData_StepWriter&                                              SW,
  const occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->CoordinateSystem());
}

void RWStepFEA_RWAlignedCurve3dElementCoordinateSystem::Share(
  const occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>& ent,
  Interface_EntityIterator&                                         iter) const
{

  iter.AddItem(ent->CoordinateSystem());
}
