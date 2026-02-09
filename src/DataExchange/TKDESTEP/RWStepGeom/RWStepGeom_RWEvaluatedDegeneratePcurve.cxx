

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWEvaluatedDegeneratePcurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_EvaluatedDegeneratePcurve.hpp>
#include <StepGeom_Surface.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>

RWStepGeom_RWEvaluatedDegeneratePcurve::RWStepGeom_RWEvaluatedDegeneratePcurve() = default;

void RWStepGeom_RWEvaluatedDegeneratePcurve::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepGeom_EvaluatedDegeneratePcurve>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "evaluated_degenerate_pcurve"))
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

  occ::handle<StepGeom_CartesianPoint> aEquivalentPoint;

  data->ReadEntity(num,
                   4,
                   "equivalent_point",
                   ach,
                   STANDARD_TYPE(StepGeom_CartesianPoint),
                   aEquivalentPoint);

  ent->Init(aName, aBasisSurface, aReferenceToCurve, aEquivalentPoint);
}

void RWStepGeom_RWEvaluatedDegeneratePcurve::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepGeom_EvaluatedDegeneratePcurve>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->BasisSurface());

  SW.Send(ent->ReferenceToCurve());

  SW.Send(ent->EquivalentPoint());
}

void RWStepGeom_RWEvaluatedDegeneratePcurve::Share(
  const occ::handle<StepGeom_EvaluatedDegeneratePcurve>& ent,
  Interface_EntityIterator&                              iter) const
{

  iter.GetOneItem(ent->BasisSurface());

  iter.GetOneItem(ent->ReferenceToCurve());

  iter.GetOneItem(ent->EquivalentPoint());
}
