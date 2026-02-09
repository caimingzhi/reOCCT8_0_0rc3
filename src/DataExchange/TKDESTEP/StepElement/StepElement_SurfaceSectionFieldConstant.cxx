#include <StepElement_SurfaceSection.hpp>
#include <StepElement_SurfaceSectionFieldConstant.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_SurfaceSectionFieldConstant, StepElement_SurfaceSectionField)

StepElement_SurfaceSectionFieldConstant::StepElement_SurfaceSectionFieldConstant() = default;

void StepElement_SurfaceSectionFieldConstant::Init(
  const occ::handle<StepElement_SurfaceSection>& aDefinition)
{

  theDefinition = aDefinition;
}

occ::handle<StepElement_SurfaceSection> StepElement_SurfaceSectionFieldConstant::Definition() const
{
  return theDefinition;
}

void StepElement_SurfaceSectionFieldConstant::SetDefinition(
  const occ::handle<StepElement_SurfaceSection>& aDefinition)
{
  theDefinition = aDefinition;
}
