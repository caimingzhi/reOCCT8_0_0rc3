#include <StepRepr_ConfigurationDesign.hpp>
#include <StepRepr_ConfigurationDesignItem.hpp>
#include <StepRepr_ConfigurationItem.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ConfigurationDesign, Standard_Transient)

StepRepr_ConfigurationDesign::StepRepr_ConfigurationDesign() = default;

void StepRepr_ConfigurationDesign::Init(
  const occ::handle<StepRepr_ConfigurationItem>& aConfiguration,
  const StepRepr_ConfigurationDesignItem&        aDesign)
{

  theConfiguration = aConfiguration;

  theDesign = aDesign;
}

occ::handle<StepRepr_ConfigurationItem> StepRepr_ConfigurationDesign::Configuration() const
{
  return theConfiguration;
}

void StepRepr_ConfigurationDesign::SetConfiguration(
  const occ::handle<StepRepr_ConfigurationItem>& aConfiguration)
{
  theConfiguration = aConfiguration;
}

StepRepr_ConfigurationDesignItem StepRepr_ConfigurationDesign::Design() const
{
  return theDesign;
}

void StepRepr_ConfigurationDesign::SetDesign(const StepRepr_ConfigurationDesignItem& aDesign)
{
  theDesign = aDesign;
}
