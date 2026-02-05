#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_RoleSelect.hpp>
#include <Standard_Transient.hpp>
class StepBasic_ObjectRole;

//! Representation of STEP entity RoleAssociation
class StepBasic_RoleAssociation : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_RoleAssociation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_ObjectRole>& aRole,
                            const StepBasic_RoleSelect&              aItemWithRole);

  //! Returns field Role
  Standard_EXPORT occ::handle<StepBasic_ObjectRole> Role() const;

  //! Set field Role
  Standard_EXPORT void SetRole(const occ::handle<StepBasic_ObjectRole>& Role);

  //! Returns field ItemWithRole
  Standard_EXPORT StepBasic_RoleSelect ItemWithRole() const;

  //! Set field ItemWithRole
  Standard_EXPORT void SetItemWithRole(const StepBasic_RoleSelect& ItemWithRole);

  DEFINE_STANDARD_RTTIEXT(StepBasic_RoleAssociation, Standard_Transient)

private:
  occ::handle<StepBasic_ObjectRole> theRole;
  StepBasic_RoleSelect              theItemWithRole;
};
