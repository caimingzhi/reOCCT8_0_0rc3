

#include "RWStepBasic_RWSiUnit.hpp"
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnit.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepBasic_RWSiPrefix.hpp"
#include "RWStepBasic_RWSiUnitName.hpp"

RWStepBasic_RWSiUnit::RWStepBasic_RWSiUnit() = default;

void RWStepBasic_RWSiUnit::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepBasic_SiUnit>&        ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "si_unit"))
    return;

  data->CheckDerived(num, 1, "dimensions", ach, false);

  StepBasic_SiPrefix aPrefix    = StepBasic_spExa;
  bool               hasAprefix = false;
  if (data->IsParamDefined(num, 2))
  {
    if (data->ParamType(num, 2) == Interface_ParamEnum)
    {
      const char* text = data->ParamCValue(num, 2);
      hasAprefix       = RWStepBasic_RWSiPrefix::ConvertToEnum(text, aPrefix);
      if (!hasAprefix)
      {
        ach->AddFail("Enumeration si_prefix has not an allowed value");
      }
    }
    else
    {
      ach->AddFail("Parameter #2 (prefix) is not an enumeration");
    }
  }

  StepBasic_SiUnitName aName = StepBasic_sunMetre;
  if (data->ParamType(num, 3) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 3);
    if (!RWStepBasic_RWSiUnitName::ConvertToEnum(text, aName))
    {
      ach->AddFail("Enumeration si_unit_name has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #3 (name) is not an enumeration");

  ent->Init(hasAprefix, aPrefix, aName);
}

void RWStepBasic_RWSiUnit::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepBasic_SiUnit>& ent) const
{

  SW.SendDerived();

  bool hasAprefix = ent->HasPrefix();
  if (hasAprefix)
    SW.SendEnum(RWStepBasic_RWSiPrefix::ConvertToString(ent->Prefix()));
  else
    SW.SendUndef();

  SW.SendEnum(RWStepBasic_RWSiUnitName::ConvertToString(ent->Name()));
}
