

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepData_SelectMember.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_TrimmingMember.hpp>
#include <StepGeom_TrimmingSelect.hpp>

StepGeom_TrimmingSelect::StepGeom_TrimmingSelect() = default;

int StepGeom_TrimmingSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepGeom_CartesianPoint)))
    return 1;
  return 0;
}

occ::handle<StepData_SelectMember> StepGeom_TrimmingSelect::NewMember() const
{
  return new StepGeom_TrimmingMember;
}

int StepGeom_TrimmingSelect::CaseMem(const occ::handle<StepData_SelectMember>& ent) const
{
  if (ent.IsNull())
    return 0;
  Interface_ParamType type = ent->ParamType();

  if (type != Interface_ParamVoid && type != Interface_ParamReal)
    return 0;
  if (ent->Matches("PARAMETER_VALUE"))
    return 1;
  return 0;
}

occ::handle<StepGeom_CartesianPoint> StepGeom_TrimmingSelect::CartesianPoint() const
{
  return GetCasted(StepGeom_CartesianPoint, Value());
}

void StepGeom_TrimmingSelect::SetParameterValue(const double aParameterValue)
{
  SetReal(aParameterValue, "PARAMETER_VALUE");
}

double StepGeom_TrimmingSelect::ParameterValue() const
{
  return Real();
}
