#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Added for Dimensional Tolerances
class StepShape_LimitsAndFits : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_LimitsAndFits();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& form_variance,
                            const occ::handle<TCollection_HAsciiString>& zone_variance,
                            const occ::handle<TCollection_HAsciiString>& grade,
                            const occ::handle<TCollection_HAsciiString>& source);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FormVariance() const;

  Standard_EXPORT void SetFormVariance(const occ::handle<TCollection_HAsciiString>& form_variance);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ZoneVariance() const;

  Standard_EXPORT void SetZoneVariance(const occ::handle<TCollection_HAsciiString>& zone_variance);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Grade() const;

  Standard_EXPORT void SetGrade(const occ::handle<TCollection_HAsciiString>& grade);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Source() const;

  Standard_EXPORT void SetSource(const occ::handle<TCollection_HAsciiString>& source);

  DEFINE_STANDARD_RTTIEXT(StepShape_LimitsAndFits, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theFormVariance;
  occ::handle<TCollection_HAsciiString> theZoneVariance;
  occ::handle<TCollection_HAsciiString> theGrade;
  occ::handle<TCollection_HAsciiString> theSource;
};
