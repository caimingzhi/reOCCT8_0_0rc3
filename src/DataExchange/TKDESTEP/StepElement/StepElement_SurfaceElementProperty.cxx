#include <StepElement_SurfaceElementProperty.hpp>
#include <StepElement_SurfaceSectionField.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_SurfaceElementProperty, Standard_Transient)

//=================================================================================================

StepElement_SurfaceElementProperty::StepElement_SurfaceElementProperty() = default;

//=================================================================================================

void StepElement_SurfaceElementProperty::Init(
  const occ::handle<TCollection_HAsciiString>&        aPropertyId,
  const occ::handle<TCollection_HAsciiString>&        aDescription,
  const occ::handle<StepElement_SurfaceSectionField>& aSection)
{

  thePropertyId = aPropertyId;

  theDescription = aDescription;

  theSection = aSection;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepElement_SurfaceElementProperty::PropertyId() const
{
  return thePropertyId;
}

//=================================================================================================

void StepElement_SurfaceElementProperty::SetPropertyId(
  const occ::handle<TCollection_HAsciiString>& aPropertyId)
{
  thePropertyId = aPropertyId;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepElement_SurfaceElementProperty::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepElement_SurfaceElementProperty::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

occ::handle<StepElement_SurfaceSectionField> StepElement_SurfaceElementProperty::Section() const
{
  return theSection;
}

//=================================================================================================

void StepElement_SurfaceElementProperty::SetSection(
  const occ::handle<StepElement_SurfaceSectionField>& aSection)
{
  theSection = aSection;
}
