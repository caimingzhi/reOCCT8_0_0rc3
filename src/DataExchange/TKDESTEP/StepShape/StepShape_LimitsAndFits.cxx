

#include <StepShape_LimitsAndFits.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_LimitsAndFits, Standard_Transient)

StepShape_LimitsAndFits::StepShape_LimitsAndFits() = default;

void StepShape_LimitsAndFits::Init(const occ::handle<TCollection_HAsciiString>& form_variance,
                                   const occ::handle<TCollection_HAsciiString>& zone_variance,
                                   const occ::handle<TCollection_HAsciiString>& grade,
                                   const occ::handle<TCollection_HAsciiString>& source)
{
  theFormVariance = form_variance;
  theZoneVariance = zone_variance;
  theGrade        = grade;
  theSource       = source;
}

occ::handle<TCollection_HAsciiString> StepShape_LimitsAndFits::FormVariance() const
{
  return theFormVariance;
}

void StepShape_LimitsAndFits::SetFormVariance(
  const occ::handle<TCollection_HAsciiString>& form_variance)
{
  theFormVariance = form_variance;
}

occ::handle<TCollection_HAsciiString> StepShape_LimitsAndFits::ZoneVariance() const
{
  return theZoneVariance;
}

void StepShape_LimitsAndFits::SetZoneVariance(
  const occ::handle<TCollection_HAsciiString>& zone_variance)
{
  theZoneVariance = zone_variance;
}

occ::handle<TCollection_HAsciiString> StepShape_LimitsAndFits::Grade() const
{
  return theGrade;
}

void StepShape_LimitsAndFits::SetGrade(const occ::handle<TCollection_HAsciiString>& grade)
{
  theGrade = grade;
}

occ::handle<TCollection_HAsciiString> StepShape_LimitsAndFits::Source() const
{
  return theSource;
}

void StepShape_LimitsAndFits::SetSource(const occ::handle<TCollection_HAsciiString>& source)
{
  theSource = source;
}
