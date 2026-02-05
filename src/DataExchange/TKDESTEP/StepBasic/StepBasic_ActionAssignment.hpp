#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Action;

//! Representation of STEP entity ActionAssignment
class StepBasic_ActionAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ActionAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_Action>& aAssignedAction);

  //! Returns field AssignedAction
  Standard_EXPORT occ::handle<StepBasic_Action> AssignedAction() const;

  //! Set field AssignedAction
  Standard_EXPORT void SetAssignedAction(const occ::handle<StepBasic_Action>& AssignedAction);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ActionAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Action> theAssignedAction;
};
