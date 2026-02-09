

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWOffsetSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_OffsetSurface.hpp>
#include <StepGeom_Surface.hpp>

RWStepGeom_RWOffsetSurface::RWStepGeom_RWOffsetSurface() = default;

void RWStepGeom_RWOffsetSurface::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepGeom_OffsetSurface>&  ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "offset_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Surface> aBasisSurface;

  data->ReadEntity(num, 2, "basis_surface", ach, STANDARD_TYPE(StepGeom_Surface), aBasisSurface);

  double aDistance;

  data->ReadReal(num, 3, "distance", ach, aDistance);

  StepData_Logical aSelfIntersect;

  data->ReadLogical(num, 4, "self_intersect", ach, aSelfIntersect);

  ent->Init(aName, aBasisSurface, aDistance, aSelfIntersect);
}

void RWStepGeom_RWOffsetSurface::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepGeom_OffsetSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisSurface());

  SW.Send(ent->Distance());

  SW.SendLogical(ent->SelfIntersect());
}

void RWStepGeom_RWOffsetSurface::Share(const occ::handle<StepGeom_OffsetSurface>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->BasisSurface());
}
