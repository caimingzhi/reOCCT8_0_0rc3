

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepVisual_MarkerMember.hpp>
#include <StepVisual_MarkerSelect.hpp>

StepVisual_MarkerSelect::StepVisual_MarkerSelect() = default;

int StepVisual_MarkerSelect::CaseNum(const occ::handle<Standard_Transient>&) const
{
  return 0;
}

occ::handle<StepData_SelectMember> StepVisual_MarkerSelect::NewMember() const
{
  return new StepVisual_MarkerMember;
}

int StepVisual_MarkerSelect::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  Interface_ParamType type = ent->ParamType();

  if (type != Interface_ParamVoid && type != Interface_ParamEnum)
    return 0;
  if (ent->Matches("MARKER_TYPE"))
    return 1;
  return 0;
}

occ::handle<StepVisual_MarkerMember> StepVisual_MarkerSelect::MarkerMember() const
{
  return GetCasted(StepVisual_MarkerMember, Value());
}
