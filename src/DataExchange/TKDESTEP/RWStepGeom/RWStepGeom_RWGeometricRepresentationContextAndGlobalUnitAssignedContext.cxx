

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.hpp>

RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::
  RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext() = default;

void RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                             data,
  const int                                                                               num0,
  occ::handle<Interface_Check>&                                                           ach,
  const occ::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext>& ent) const
{

  int num = num0;

  if (!data->CheckNbParams(num, 1, ach, "geometric_representation_context"))
    return;

  int aCoordinateSpaceDimension;

  data->ReadInteger(num, 1, "coordinate_space_dimension", ach, aCoordinateSpaceDimension);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "global_unit_assigned_context"))
    return;

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> aUnits;
  occ::handle<StepBasic_NamedUnit>                                   anent2;
  int                                                                nsub2;
  if (data->ReadSubList(num, 1, "units", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aUnits  = new NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2, i2, "unit", ach, STANDARD_TYPE(StepBasic_NamedUnit), anent2))
        aUnits->SetValue(i2, anent2);
    }
  }

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 2, ach, "representation_context"))
    return;

  occ::handle<TCollection_HAsciiString> aContextIdentifier;

  data->ReadString(num, 1, "context_identifier", ach, aContextIdentifier);

  occ::handle<TCollection_HAsciiString> aContextType;

  data->ReadString(num, 2, "context_type", ach, aContextType);

  ent->Init(aContextIdentifier, aContextType, aCoordinateSpaceDimension, aUnits);
}

void RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::WriteStep(
  StepData_StepWriter&                                                                    SW,
  const occ::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext>& ent) const
{

  SW.StartEntity("GEOMETRIC_REPRESENTATION_CONTEXT");

  SW.Send(ent->CoordinateSpaceDimension());

  SW.StartEntity("GLOBAL_UNIT_ASSIGNED_CONTEXT");

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbUnits(); i2++)
  {
    SW.Send(ent->UnitsValue(i2));
  }
  SW.CloseSub();

  SW.StartEntity("REPRESENTATION_CONTEXT");

  SW.Send(ent->ContextIdentifier());

  SW.Send(ent->ContextType());
}

void RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext::Share(
  const occ::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext>& ent,
  Interface_EntityIterator& iter) const
{

  int nbElem1 = ent->NbUnits();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->UnitsValue(is1));
  }
}
