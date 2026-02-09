#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepRepr_ConfigurationDesign.hpp>
#include <StepRepr_ConfigurationEffectivity.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ConfigurationEffectivity,
                           StepBasic_ProductDefinitionEffectivity)

StepRepr_ConfigurationEffectivity::StepRepr_ConfigurationEffectivity() = default;

void StepRepr_ConfigurationEffectivity::Init(
  const occ::handle<TCollection_HAsciiString>&                aEffectivity_Id,
  const occ::handle<StepBasic_ProductDefinitionRelationship>& aProductDefinitionEffectivity_Usage,
  const occ::handle<StepRepr_ConfigurationDesign>&            aConfiguration)
{
  StepBasic_ProductDefinitionEffectivity::Init(aEffectivity_Id,
                                               aProductDefinitionEffectivity_Usage);

  theConfiguration = aConfiguration;
}

occ::handle<StepRepr_ConfigurationDesign> StepRepr_ConfigurationEffectivity::Configuration() const
{
  return theConfiguration;
}

void StepRepr_ConfigurationEffectivity::SetConfiguration(
  const occ::handle<StepRepr_ConfigurationDesign>& aConfiguration)
{
  theConfiguration = aConfiguration;
}
