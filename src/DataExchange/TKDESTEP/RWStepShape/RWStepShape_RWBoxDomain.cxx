

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWBoxDomain.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepShape_BoxDomain.hpp>

RWStepShape_RWBoxDomain::RWStepShape_RWBoxDomain() = default;

void RWStepShape_RWBoxDomain::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                       const int                                   num,
                                       occ::handle<Interface_Check>&               ach,
                                       const occ::handle<StepShape_BoxDomain>&     ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "box_domain"))
    return;

  occ::handle<StepGeom_CartesianPoint> aCorner;

  data->ReadEntity(num, 1, "corner", ach, STANDARD_TYPE(StepGeom_CartesianPoint), aCorner);

  double aXlength;

  data->ReadReal(num, 2, "xlength", ach, aXlength);

  double aYlength;

  data->ReadReal(num, 3, "ylength", ach, aYlength);

  double aZlength;

  data->ReadReal(num, 4, "zlength", ach, aZlength);

  ent->Init(aCorner, aXlength, aYlength, aZlength);
}

void RWStepShape_RWBoxDomain::WriteStep(StepData_StepWriter&                    SW,
                                        const occ::handle<StepShape_BoxDomain>& ent) const
{

  SW.Send(ent->Corner());

  SW.Send(ent->Xlength());

  SW.Send(ent->Ylength());

  SW.Send(ent->Zlength());
}

void RWStepShape_RWBoxDomain::Share(const occ::handle<StepShape_BoxDomain>& ent,
                                    Interface_EntityIterator&               iter) const
{

  iter.GetOneItem(ent->Corner());
}
