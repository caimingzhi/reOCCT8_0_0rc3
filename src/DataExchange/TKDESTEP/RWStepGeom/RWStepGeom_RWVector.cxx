

#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWVector.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Direction.hpp>
#include <StepGeom_Vector.hpp>

RWStepGeom_RWVector::RWStepGeom_RWVector() = default;

void RWStepGeom_RWVector::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                   const int                                   num,
                                   occ::handle<Interface_Check>&               ach,
                                   const occ::handle<StepGeom_Vector>&         ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "vector"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Direction> aOrientation;

  data->ReadEntity(num, 2, "orientation", ach, STANDARD_TYPE(StepGeom_Direction), aOrientation);

  double aMagnitude;

  data->ReadReal(num, 3, "magnitude", ach, aMagnitude);

  ent->Init(aName, aOrientation, aMagnitude);
}

void RWStepGeom_RWVector::WriteStep(StepData_StepWriter&                SW,
                                    const occ::handle<StepGeom_Vector>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Orientation());

  SW.Send(ent->Magnitude());
}

void RWStepGeom_RWVector::Share(const occ::handle<StepGeom_Vector>& ent,
                                Interface_EntityIterator&           iter) const
{

  iter.GetOneItem(ent->Orientation());
}

void RWStepGeom_RWVector::Check(const occ::handle<StepGeom_Vector>& ent,
                                const Interface_ShareTool&,
                                occ::handle<Interface_Check>& ach) const
{
  if (std::abs(ent->Magnitude()) < RealEpsilon())
  {
    ach->AddFail("ERROR: Magnitude of Vector = 0.0");
  }
}
