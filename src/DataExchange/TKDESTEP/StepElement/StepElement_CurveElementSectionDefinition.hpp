#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity CurveElementSectionDefinition
class StepElement_CurveElementSectionDefinition : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_CurveElementSectionDefinition();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aDescription,
                            const double                                 aSectionAngle);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns field SectionAngle
  Standard_EXPORT double SectionAngle() const;

  //! Set field SectionAngle
  Standard_EXPORT void SetSectionAngle(const double SectionAngle);

  DEFINE_STANDARD_RTTIEXT(StepElement_CurveElementSectionDefinition, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theDescription;
  double                                theSectionAngle;
};
