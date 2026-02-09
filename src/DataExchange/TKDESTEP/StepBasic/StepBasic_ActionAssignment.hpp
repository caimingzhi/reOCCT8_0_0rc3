#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Action;

class StepBasic_ActionAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ActionAssignment();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Action>& aAssignedAction);

  Standard_EXPORT occ::handle<StepBasic_Action> AssignedAction() const;

  Standard_EXPORT void SetAssignedAction(const occ::handle<StepBasic_Action>& AssignedAction);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ActionAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Action> theAssignedAction;
};
