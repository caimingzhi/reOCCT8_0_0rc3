#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_IdentificationRole;

//! Representation of STEP entity IdentificationAssignment
class StepBasic_IdentificationAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_IdentificationAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aAssignedId,
                            const occ::handle<StepBasic_IdentificationRole>& aRole);

  //! Returns field AssignedId
  Standard_EXPORT occ::handle<TCollection_HAsciiString> AssignedId() const;

  //! Set field AssignedId
  Standard_EXPORT void SetAssignedId(const occ::handle<TCollection_HAsciiString>& AssignedId);

  //! Returns field Role
  Standard_EXPORT occ::handle<StepBasic_IdentificationRole> Role() const;

  //! Set field Role
  Standard_EXPORT void SetRole(const occ::handle<StepBasic_IdentificationRole>& Role);

  DEFINE_STANDARD_RTTIEXT(StepBasic_IdentificationAssignment, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>     theAssignedId;
  occ::handle<StepBasic_IdentificationRole> theRole;
};

