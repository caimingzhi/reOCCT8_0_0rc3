

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_OpenShell.hpp>
#include <StepShape_Shell.hpp>

StepShape_Shell::StepShape_Shell() = default;

int StepShape_Shell::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_OpenShell)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ClosedShell)))
    return 2;
  return 0;
}

occ::handle<StepShape_OpenShell> StepShape_Shell::OpenShell() const
{
  return GetCasted(StepShape_OpenShell, Value());
}

occ::handle<StepShape_ClosedShell> StepShape_Shell::ClosedShell() const
{
  return GetCasted(StepShape_ClosedShell, Value());
}
