#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity NameAssignment
class StepBasic_NameAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_NameAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aAssignedName);

  //! Returns field AssignedName
  Standard_EXPORT occ::handle<TCollection_HAsciiString> AssignedName() const;

  //! Set field AssignedName
  Standard_EXPORT void SetAssignedName(const occ::handle<TCollection_HAsciiString>& AssignedName);

  DEFINE_STANDARD_RTTIEXT(StepBasic_NameAssignment, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theAssignedName;
};
