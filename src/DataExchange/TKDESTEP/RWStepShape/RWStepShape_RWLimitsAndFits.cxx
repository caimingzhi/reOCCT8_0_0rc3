

#include "RWStepShape_RWLimitsAndFits.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_LimitsAndFits.hpp>

RWStepShape_RWLimitsAndFits::RWStepShape_RWLimitsAndFits() = default;

void RWStepShape_RWLimitsAndFits::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepShape_LimitsAndFits>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "limits_and_fits"))
    return;

  occ::handle<TCollection_HAsciiString> fv;
  data->ReadString(num, 1, "form_variance", ach, fv);

  occ::handle<TCollection_HAsciiString> zv;
  data->ReadString(num, 2, "zone_variance", ach, zv);

  occ::handle<TCollection_HAsciiString> gr;
  data->ReadString(num, 3, "grade", ach, gr);

  occ::handle<TCollection_HAsciiString> sou;
  data->ReadString(num, 4, "source", ach, sou);

  ent->Init(fv, zv, gr, sou);
}

void RWStepShape_RWLimitsAndFits::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepShape_LimitsAndFits>& ent) const
{
  SW.Send(ent->FormVariance());
  SW.Send(ent->ZoneVariance());
  SW.Send(ent->Grade());
  SW.Send(ent->Source());
}
