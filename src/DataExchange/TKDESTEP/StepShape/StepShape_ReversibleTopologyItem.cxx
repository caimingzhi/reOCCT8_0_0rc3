

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_Face.hpp>
#include <StepShape_FaceBound.hpp>
#include <StepShape_OpenShell.hpp>
#include <StepShape_Path.hpp>
#include <StepShape_ReversibleTopologyItem.hpp>

StepShape_ReversibleTopologyItem::StepShape_ReversibleTopologyItem() = default;

int StepShape_ReversibleTopologyItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Edge)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Path)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepShape_Face)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepShape_FaceBound)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ClosedShell)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepShape_OpenShell)))
    return 6;
  return 0;
}

occ::handle<StepShape_Edge> StepShape_ReversibleTopologyItem::Edge() const
{
  return GetCasted(StepShape_Edge, Value());
}

occ::handle<StepShape_Path> StepShape_ReversibleTopologyItem::Path() const
{
  return GetCasted(StepShape_Path, Value());
}

occ::handle<StepShape_Face> StepShape_ReversibleTopologyItem::Face() const
{
  return GetCasted(StepShape_Face, Value());
}

occ::handle<StepShape_FaceBound> StepShape_ReversibleTopologyItem::FaceBound() const
{
  return GetCasted(StepShape_FaceBound, Value());
}

occ::handle<StepShape_ClosedShell> StepShape_ReversibleTopologyItem::ClosedShell() const
{
  return GetCasted(StepShape_ClosedShell, Value());
}

occ::handle<StepShape_OpenShell> StepShape_ReversibleTopologyItem::OpenShell() const
{
  return GetCasted(StepShape_OpenShell, Value());
}
