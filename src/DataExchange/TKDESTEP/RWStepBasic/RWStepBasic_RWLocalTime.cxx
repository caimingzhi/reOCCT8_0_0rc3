

#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWLocalTime.hpp"
#include <StepBasic_CoordinatedUniversalTimeOffset.hpp>
#include <StepBasic_LocalTime.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWLocalTime::RWStepBasic_RWLocalTime() = default;

void RWStepBasic_RWLocalTime::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                       const int                                   num,
                                       occ::handle<Interface_Check>&               ach,
                                       const occ::handle<StepBasic_LocalTime>&     ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "local_time"))
    return;

  int aHourComponent;

  data->ReadInteger(num, 1, "hour_component", ach, aHourComponent);

  int  aMinuteComponent;
  bool hasAminuteComponent = true;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadInteger(num, 2, "minute_component", ach, aMinuteComponent);
  }
  else
  {
    hasAminuteComponent = false;
    aMinuteComponent    = 0;
  }

  double aSecondComponent;
  bool   hasAsecondComponent = true;
  if (data->IsParamDefined(num, 3))
  {

    data->ReadReal(num, 3, "second_component", ach, aSecondComponent);
  }
  else
  {
    hasAsecondComponent = false;
    aSecondComponent    = 0.;
  }

  occ::handle<StepBasic_CoordinatedUniversalTimeOffset> aZone;

  data->ReadEntity(num,
                   4,
                   "zone",
                   ach,
                   STANDARD_TYPE(StepBasic_CoordinatedUniversalTimeOffset),
                   aZone);

  ent->Init(aHourComponent,
            hasAminuteComponent,
            aMinuteComponent,
            hasAsecondComponent,
            aSecondComponent,
            aZone);
}

void RWStepBasic_RWLocalTime::WriteStep(StepData_StepWriter&                    SW,
                                        const occ::handle<StepBasic_LocalTime>& ent) const
{

  SW.Send(ent->HourComponent());

  bool hasAminuteComponent = ent->HasMinuteComponent();
  if (hasAminuteComponent)
  {
    SW.Send(ent->MinuteComponent());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAsecondComponent = ent->HasSecondComponent();
  if (hasAsecondComponent)
  {
    SW.Send(ent->SecondComponent());
  }
  else
  {
    SW.SendUndef();
  }

  SW.Send(ent->Zone());
}

void RWStepBasic_RWLocalTime::Share(const occ::handle<StepBasic_LocalTime>& ent,
                                    Interface_EntityIterator&               iter) const
{

  iter.GetOneItem(ent->Zone());
}
