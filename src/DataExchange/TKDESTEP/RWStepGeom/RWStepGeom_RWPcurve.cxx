

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWPcurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>

RWStepGeom_RWPcurve::RWStepGeom_RWPcurve() = default;

void RWStepGeom_RWPcurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepGeom_Pcurve>&         ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "pcurve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Surface> aBasisSurface;

  data->ReadEntity(num, 2, "basis_surface", ach, STANDARD_TYPE(StepGeom_Surface), aBasisSurface);

  occ::handle<StepRepr_DefinitionalRepresentation> aReferenceToCurve;

  data->ReadEntity(num,
                   3,
                   "reference_to_curve",
                   ach,
                   STANDARD_TYPE(StepRepr_DefinitionalRepresentation),
                   aReferenceToCurve);

  ent->Init(aName, aBasisSurface, aReferenceToCurve);
}

void RWStepGeom_RWPcurve::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepGeom_Pcurve>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisSurface());

  SW.Send(ent->ReferenceToCurve());
}

void RWStepGeom_RWPcurve::Share(const occ::handle<StepGeom_Pcurve>& ent,
                                Interface_EntityIterator&           iter) const
{

  iter.GetOneItem(ent->BasisSurface());

  iter.GetOneItem(ent->ReferenceToCurve());
}
