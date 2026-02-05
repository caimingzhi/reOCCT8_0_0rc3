#include <StepElement_CurveElementSectionDefinition.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_CurveElementSectionDefinition, Standard_Transient)

//=================================================================================================

StepElement_CurveElementSectionDefinition::StepElement_CurveElementSectionDefinition() = default;

//=================================================================================================

void StepElement_CurveElementSectionDefinition::Init(
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const double                                 aSectionAngle)
{

  theDescription = aDescription;

  theSectionAngle = aSectionAngle;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepElement_CurveElementSectionDefinition::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepElement_CurveElementSectionDefinition::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

double StepElement_CurveElementSectionDefinition::SectionAngle() const
{
  return theSectionAngle;
}

//=================================================================================================

void StepElement_CurveElementSectionDefinition::SetSectionAngle(const double aSectionAngle)
{
  theSectionAngle = aSectionAngle;
}
