

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSweptSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SweptSurface.hpp>

RWStepGeom_RWSweptSurface::RWStepGeom_RWSweptSurface() = default;

void RWStepGeom_RWSweptSurface::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_SweptSurface>&   ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "swept_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aSweptCurve;

  data->ReadEntity(num, 2, "swept_curve", ach, STANDARD_TYPE(StepGeom_Curve), aSweptCurve);

  ent->Init(aName, aSweptCurve);
}

void RWStepGeom_RWSweptSurface::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_SweptSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->SweptCurve());
}

void RWStepGeom_RWSweptSurface::Share(const occ::handle<StepGeom_SweptSurface>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->SweptCurve());
}
