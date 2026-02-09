

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWOffsetCurve3d.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Direction.hpp>
#include <StepGeom_OffsetCurve3d.hpp>

RWStepGeom_RWOffsetCurve3d::RWStepGeom_RWOffsetCurve3d() = default;

void RWStepGeom_RWOffsetCurve3d::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepGeom_OffsetCurve3d>&  ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "offset_curve_3d"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aBasisCurve;

  data->ReadEntity(num, 2, "basis_curve", ach, STANDARD_TYPE(StepGeom_Curve), aBasisCurve);

  double aDistance;

  data->ReadReal(num, 3, "distance", ach, aDistance);

  StepData_Logical aSelfIntersect;

  data->ReadLogical(num, 4, "self_intersect", ach, aSelfIntersect);

  occ::handle<StepGeom_Direction> aRefDirection;

  data->ReadEntity(num, 5, "ref_direction", ach, STANDARD_TYPE(StepGeom_Direction), aRefDirection);

  ent->Init(aName, aBasisCurve, aDistance, aSelfIntersect, aRefDirection);
}

void RWStepGeom_RWOffsetCurve3d::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepGeom_OffsetCurve3d>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisCurve());

  SW.Send(ent->Distance());

  SW.SendLogical(ent->SelfIntersect());

  SW.Send(ent->RefDirection());
}

void RWStepGeom_RWOffsetCurve3d::Share(const occ::handle<StepGeom_OffsetCurve3d>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->BasisCurve());

  iter.GetOneItem(ent->RefDirection());
}
