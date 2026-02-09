

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSurfaceOfRevolution.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceOfRevolution.hpp>

RWStepGeom_RWSurfaceOfRevolution::RWStepGeom_RWSurfaceOfRevolution() = default;

void RWStepGeom_RWSurfaceOfRevolution::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepGeom_SurfaceOfRevolution>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "surface_of_revolution"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aSweptCurve;

  data->ReadEntity(num, 2, "swept_curve", ach, STANDARD_TYPE(StepGeom_Curve), aSweptCurve);

  occ::handle<StepGeom_Axis1Placement> aAxisPosition;

  data->ReadEntity(num,
                   3,
                   "axis_position",
                   ach,
                   STANDARD_TYPE(StepGeom_Axis1Placement),
                   aAxisPosition);

  ent->Init(aName, aSweptCurve, aAxisPosition);
}

void RWStepGeom_RWSurfaceOfRevolution::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepGeom_SurfaceOfRevolution>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptCurve());

  SW.Send(ent->AxisPosition());
}

void RWStepGeom_RWSurfaceOfRevolution::Share(const occ::handle<StepGeom_SurfaceOfRevolution>& ent,
                                             Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->SweptCurve());

  iter.GetOneItem(ent->AxisPosition());
}
