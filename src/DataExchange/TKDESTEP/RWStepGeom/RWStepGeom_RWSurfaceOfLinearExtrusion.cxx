

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSurfaceOfLinearExtrusion.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceOfLinearExtrusion.hpp>
#include <StepGeom_Vector.hpp>

RWStepGeom_RWSurfaceOfLinearExtrusion::RWStepGeom_RWSurfaceOfLinearExtrusion() = default;

void RWStepGeom_RWSurfaceOfLinearExtrusion::ReadStep(
  const occ::handle<StepData_StepReaderData>&           data,
  const int                                             num,
  occ::handle<Interface_Check>&                         ach,
  const occ::handle<StepGeom_SurfaceOfLinearExtrusion>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "surface_of_linear_extrusion"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aSweptCurve;

  data->ReadEntity(num, 2, "swept_curve", ach, STANDARD_TYPE(StepGeom_Curve), aSweptCurve);

  occ::handle<StepGeom_Vector> aExtrusionAxis;

  data->ReadEntity(num, 3, "extrusion_axis", ach, STANDARD_TYPE(StepGeom_Vector), aExtrusionAxis);

  ent->Init(aName, aSweptCurve, aExtrusionAxis);
}

void RWStepGeom_RWSurfaceOfLinearExtrusion::WriteStep(
  StepData_StepWriter&                                  SW,
  const occ::handle<StepGeom_SurfaceOfLinearExtrusion>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptCurve());

  SW.Send(ent->ExtrusionAxis());
}

void RWStepGeom_RWSurfaceOfLinearExtrusion::Share(
  const occ::handle<StepGeom_SurfaceOfLinearExtrusion>& ent,
  Interface_EntityIterator&                             iter) const
{

  iter.GetOneItem(ent->SweptCurve());

  iter.GetOneItem(ent->ExtrusionAxis());
}
