#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Group;

class StepBasic_GroupAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_GroupAssignment();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Group>& aAssignedGroup);

  Standard_EXPORT occ::handle<StepBasic_Group> AssignedGroup() const;

  Standard_EXPORT void SetAssignedGroup(const occ::handle<StepBasic_Group>& AssignedGroup);

  DEFINE_STANDARD_RTTIEXT(StepBasic_GroupAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Group> theAssignedGroup;
};
