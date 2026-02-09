

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSphere.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Point.hpp>
#include <StepShape_Sphere.hpp>

RWStepShape_RWSphere::RWStepShape_RWSphere() = default;

void RWStepShape_RWSphere::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepShape_Sphere>&        ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "sphere"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  double aRadius;

  data->ReadReal(num, 2, "radius", ach, aRadius);

  occ::handle<StepGeom_Point> aCentre;

  data->ReadEntity(num, 3, "centre", ach, STANDARD_TYPE(StepGeom_Point), aCentre);

  ent->Init(aName, aRadius, aCentre);
}

void RWStepShape_RWSphere::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepShape_Sphere>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Radius());

  SW.Send(ent->Centre());
}

void RWStepShape_RWSphere::Share(const occ::handle<StepShape_Sphere>& ent,
                                 Interface_EntityIterator&            iter) const
{

  iter.GetOneItem(ent->Centre());
}
