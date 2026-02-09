

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWLine.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Line.hpp>
#include <StepGeom_Vector.hpp>

RWStepGeom_RWLine::RWStepGeom_RWLine() = default;

void RWStepGeom_RWLine::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                 const int                                   num,
                                 occ::handle<Interface_Check>&               ach,
                                 const occ::handle<StepGeom_Line>&           ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "line"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_CartesianPoint> aPnt;

  data->ReadEntity(num, 2, "pnt", ach, STANDARD_TYPE(StepGeom_CartesianPoint), aPnt);

  occ::handle<StepGeom_Vector> aDir;

  data->ReadEntity(num, 3, "dir", ach, STANDARD_TYPE(StepGeom_Vector), aDir);

  ent->Init(aName, aPnt, aDir);
}

void RWStepGeom_RWLine::WriteStep(StepData_StepWriter&              SW,
                                  const occ::handle<StepGeom_Line>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Pnt());

  SW.Send(ent->Dir());
}

void RWStepGeom_RWLine::Share(const occ::handle<StepGeom_Line>& ent,
                              Interface_EntityIterator&         iter) const
{

  iter.GetOneItem(ent->Pnt());

  iter.GetOneItem(ent->Dir());
}
