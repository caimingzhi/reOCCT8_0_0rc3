#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_OpenShell;
class StepShape_ClosedShell;

class StepShape_Shell : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a Shell SelectType
  Standard_EXPORT StepShape_Shell();

  //! Recognizes a Shell Kind Entity that is :
  //! 1 -> OpenShell
  //! 2 -> ClosedShell
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a OpenShell (Null if another type)
  Standard_EXPORT occ::handle<StepShape_OpenShell> OpenShell() const;

  //! returns Value as a ClosedShell (Null if another type)
  Standard_EXPORT occ::handle<StepShape_ClosedShell> ClosedShell() const;
};
