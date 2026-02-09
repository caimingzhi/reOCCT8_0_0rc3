

#include "RWStepBasic_RWCoordinatedUniversalTimeOffset.hpp"
#include <StepBasic_CoordinatedUniversalTimeOffset.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepBasic_RWAheadOrBehind.hpp"

RWStepBasic_RWCoordinatedUniversalTimeOffset::RWStepBasic_RWCoordinatedUniversalTimeOffset() =
  default;

void RWStepBasic_RWCoordinatedUniversalTimeOffset::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepBasic_CoordinatedUniversalTimeOffset>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "coordinated_universal_time_offset"))
    return;

  int aHourOffset;

  data->ReadInteger(num, 1, "hour_offset", ach, aHourOffset);

  int  aMinuteOffset;
  bool hasAminuteOffset = true;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadInteger(num, 2, "minute_offset", ach, aMinuteOffset);
  }
  else
  {
    hasAminuteOffset = false;
    aMinuteOffset    = 0;
  }

  StepBasic_AheadOrBehind aSense = StepBasic_aobAhead;
  if (data->ParamType(num, 3) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 3);
    if (!RWStepBasic_RWAheadOrBehind::ConvertToEnum(text, aSense))
    {
      ach->AddFail("Enumeration ahead_or_behind has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #3 (sense) is not an enumeration");

  ent->Init(aHourOffset, hasAminuteOffset, aMinuteOffset, aSense);
}

void RWStepBasic_RWCoordinatedUniversalTimeOffset::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepBasic_CoordinatedUniversalTimeOffset>& ent) const
{

  SW.Send(ent->HourOffset());

  bool hasAminuteOffset = ent->HasMinuteOffset();
  if (hasAminuteOffset)
  {
    SW.Send(ent->MinuteOffset());
  }
  else
  {
    SW.SendUndef();
  }

  SW.SendEnum(RWStepBasic_RWAheadOrBehind::ConvertToString(ent->Sense()));
}
