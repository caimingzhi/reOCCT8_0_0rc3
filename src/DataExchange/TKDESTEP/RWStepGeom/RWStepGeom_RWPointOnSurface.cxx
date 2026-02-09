

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWPointOnSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_PointOnSurface.hpp>
#include <StepGeom_Surface.hpp>

RWStepGeom_RWPointOnSurface::RWStepGeom_RWPointOnSurface() = default;

void RWStepGeom_RWPointOnSurface::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepGeom_PointOnSurface>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "point_on_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Surface> aBasisSurface;

  data->ReadEntity(num, 2, "basis_surface", ach, STANDARD_TYPE(StepGeom_Surface), aBasisSurface);

  double aPointParameterU;

  data->ReadReal(num, 3, "point_parameter_u", ach, aPointParameterU);

  double aPointParameterV;

  data->ReadReal(num, 4, "point_parameter_v", ach, aPointParameterV);

  ent->Init(aName, aBasisSurface, aPointParameterU, aPointParameterV);
}

void RWStepGeom_RWPointOnSurface::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepGeom_PointOnSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisSurface());

  SW.Send(ent->PointParameterU());

  SW.Send(ent->PointParameterV());
}

void RWStepGeom_RWPointOnSurface::Share(const occ::handle<StepGeom_PointOnSurface>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  iter.GetOneItem(ent->BasisSurface());
}
