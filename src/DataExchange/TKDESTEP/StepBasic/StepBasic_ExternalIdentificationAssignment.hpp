#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_IdentificationAssignment.hpp>
class StepBasic_ExternalSource;
class TCollection_HAsciiString;
class StepBasic_IdentificationRole;

//! Representation of STEP entity ExternalIdentificationAssignment
class StepBasic_ExternalIdentificationAssignment : public StepBasic_IdentificationAssignment
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ExternalIdentificationAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     aIdentificationAssignment_AssignedId,
    const occ::handle<StepBasic_IdentificationRole>& aIdentificationAssignment_Role,
    const occ::handle<StepBasic_ExternalSource>&     aSource);

  //! Returns field Source
  Standard_EXPORT occ::handle<StepBasic_ExternalSource> Source() const;

  //! Set field Source
  Standard_EXPORT void SetSource(const occ::handle<StepBasic_ExternalSource>& Source);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ExternalIdentificationAssignment,
                          StepBasic_IdentificationAssignment)

private:
  occ::handle<StepBasic_ExternalSource> theSource;
};

