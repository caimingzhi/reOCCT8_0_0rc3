#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_Edge;
class StepShape_Path;
class StepShape_Face;
class StepShape_FaceBound;
class StepShape_ClosedShell;
class StepShape_OpenShell;

class StepShape_ReversibleTopologyItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_ReversibleTopologyItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepShape_Edge> Edge() const;

  Standard_EXPORT occ::handle<StepShape_Path> Path() const;

  Standard_EXPORT occ::handle<StepShape_Face> Face() const;

  Standard_EXPORT occ::handle<StepShape_FaceBound> FaceBound() const;

  Standard_EXPORT occ::handle<StepShape_ClosedShell> ClosedShell() const;

  Standard_EXPORT occ::handle<StepShape_OpenShell> OpenShell() const;
};
