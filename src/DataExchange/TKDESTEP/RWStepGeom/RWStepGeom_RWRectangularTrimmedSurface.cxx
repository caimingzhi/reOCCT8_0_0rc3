

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWRectangularTrimmedSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>
#include <StepGeom_Surface.hpp>

RWStepGeom_RWRectangularTrimmedSurface::RWStepGeom_RWRectangularTrimmedSurface() = default;

void RWStepGeom_RWRectangularTrimmedSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepGeom_RectangularTrimmedSurface>& ent) const
{

  if (!data->CheckNbParams(num, 8, ach, "rectangular_trimmed_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Surface> aBasisSurface;

  data->ReadEntity(num, 2, "basis_surface", ach, STANDARD_TYPE(StepGeom_Surface), aBasisSurface);

  double aU1;

  data->ReadReal(num, 3, "u1", ach, aU1);

  double aU2;

  data->ReadReal(num, 4, "u2", ach, aU2);

  double aV1;

  data->ReadReal(num, 5, "v1", ach, aV1);

  double aV2;

  data->ReadReal(num, 6, "v2", ach, aV2);

  bool aUsense;

  data->ReadBoolean(num, 7, "usense", ach, aUsense);

  bool aVsense;

  data->ReadBoolean(num, 8, "vsense", ach, aVsense);

  ent->Init(aName, aBasisSurface, aU1, aU2, aV1, aV2, aUsense, aVsense);
}

void RWStepGeom_RWRectangularTrimmedSurface::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepGeom_RectangularTrimmedSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisSurface());

  SW.Send(ent->U1());

  SW.Send(ent->U2());

  SW.Send(ent->V1());

  SW.Send(ent->V2());

  SW.SendBoolean(ent->Usense());

  SW.SendBoolean(ent->Vsense());
}

void RWStepGeom_RWRectangularTrimmedSurface::Share(
  const occ::handle<StepGeom_RectangularTrimmedSurface>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->BasisSurface());
}
