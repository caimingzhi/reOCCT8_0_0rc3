#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_IdentificationRole;

class StepBasic_IdentificationAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_IdentificationAssignment();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aAssignedId,
                            const occ::handle<StepBasic_IdentificationRole>& aRole);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AssignedId() const;

  Standard_EXPORT void SetAssignedId(const occ::handle<TCollection_HAsciiString>& AssignedId);

  Standard_EXPORT occ::handle<StepBasic_IdentificationRole> Role() const;

  Standard_EXPORT void SetRole(const occ::handle<StepBasic_IdentificationRole>& Role);

  DEFINE_STANDARD_RTTIEXT(StepBasic_IdentificationAssignment, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>     theAssignedId;
  occ::handle<StepBasic_IdentificationRole> theRole;
};
