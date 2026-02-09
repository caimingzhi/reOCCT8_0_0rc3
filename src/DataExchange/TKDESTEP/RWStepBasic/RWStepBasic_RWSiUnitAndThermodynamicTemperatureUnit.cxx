

#include "RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitAndThermodynamicTemperatureUnit.hpp>
#include <StepBasic_SiUnitName.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

#include "RWStepBasic_RWSiUnitName.hpp"
#include "RWStepBasic_RWSiPrefix.hpp"

RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit::
  RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit() = default;

void RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit::ReadStep(
  const occ::handle<StepData_StepReaderData>&                         data,
  const int                                                           num0,
  occ::handle<Interface_Check>&                                       ach,
  const occ::handle<StepBasic_SiUnitAndThermodynamicTemperatureUnit>& ent) const
{
  int num = num0;

  if (!data->CheckNbParams(num, 1, ach, "named_unit"))
    return;

  data->CheckDerived(num, 1, "dimensions", ach, false);

  num = data->NextForComplex(num);
  if (!data->CheckNbParams(num, 2, ach, "si_unit"))
    return;

  StepBasic_SiPrefix aPrefix    = StepBasic_spExa;
  bool               hasAprefix = false;
  if (data->IsParamDefined(num, 1))
  {
    if (data->ParamType(num, 1) == Interface_ParamEnum)
    {
      const char* text = data->ParamCValue(num, 1);
      hasAprefix       = RWStepBasic_RWSiPrefix::ConvertToEnum(text, aPrefix);
      if (!hasAprefix)
      {
        ach->AddFail("Enumeration si_prefix has not an allowed value");
        return;
      }
    }
    else
    {
      ach->AddFail("Parameter #1 (prefix) is not an enumeration");
      return;
    }
  }

  StepBasic_SiUnitName aName;
  if (data->ParamType(num, 2) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 2);
    if (!RWStepBasic_RWSiUnitName::ConvertToEnum(text, aName))
    {
      ach->AddFail("Enumeration si_unit_name has not an allowed value");
      return;
    }
  }
  else
  {
    ach->AddFail("Parameter #2 (name) is not an enumeration");
    return;
  }

  num = data->NextForComplex(num);
  if (!data->CheckNbParams(num, 0, ach, "thermodynamic_temperature_unit"))
    return;

  ent->Init(hasAprefix, aPrefix, aName);
}

void RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit::WriteStep(
  StepData_StepWriter&                                                SW,
  const occ::handle<StepBasic_SiUnitAndThermodynamicTemperatureUnit>& ent) const
{

  SW.StartEntity("NAMED_UNIT");

  SW.SendDerived();

  SW.StartEntity("SI_UNIT");

  bool hasAprefix = ent->HasPrefix();
  if (hasAprefix)
    SW.SendEnum(RWStepBasic_RWSiPrefix::ConvertToString(ent->Prefix()));
  else
    SW.SendUndef();

  SW.SendEnum(RWStepBasic_RWSiUnitName::ConvertToString(ent->Name()));

  SW.StartEntity("THERMODYNAMIC_TEMPERATURE_UNIT");
}
