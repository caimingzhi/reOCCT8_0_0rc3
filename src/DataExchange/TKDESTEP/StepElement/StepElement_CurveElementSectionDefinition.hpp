#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepElement_CurveElementSectionDefinition : public Standard_Transient
{

public:
  Standard_EXPORT StepElement_CurveElementSectionDefinition();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aDescription,
                            const double                                 aSectionAngle);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT double SectionAngle() const;

  Standard_EXPORT void SetSectionAngle(const double SectionAngle);

  DEFINE_STANDARD_RTTIEXT(StepElement_CurveElementSectionDefinition, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theDescription;
  double                                theSectionAngle;
};
