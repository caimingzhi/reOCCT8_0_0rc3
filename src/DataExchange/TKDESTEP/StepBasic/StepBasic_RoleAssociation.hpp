#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_RoleSelect.hpp>
#include <Standard_Transient.hpp>
class StepBasic_ObjectRole;

class StepBasic_RoleAssociation : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_RoleAssociation();

  Standard_EXPORT void Init(const occ::handle<StepBasic_ObjectRole>& aRole,
                            const StepBasic_RoleSelect&              aItemWithRole);

  Standard_EXPORT occ::handle<StepBasic_ObjectRole> Role() const;

  Standard_EXPORT void SetRole(const occ::handle<StepBasic_ObjectRole>& Role);

  Standard_EXPORT StepBasic_RoleSelect ItemWithRole() const;

  Standard_EXPORT void SetItemWithRole(const StepBasic_RoleSelect& ItemWithRole);

  DEFINE_STANDARD_RTTIEXT(StepBasic_RoleAssociation, Standard_Transient)

private:
  occ::handle<StepBasic_ObjectRole> theRole;
  StepBasic_RoleSelect              theItemWithRole;
};
