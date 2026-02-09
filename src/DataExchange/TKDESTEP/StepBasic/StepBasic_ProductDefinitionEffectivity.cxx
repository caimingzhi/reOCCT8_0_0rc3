

#include <StepBasic_ProductDefinitionEffectivity.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionEffectivity, StepBasic_Effectivity)

StepBasic_ProductDefinitionEffectivity::StepBasic_ProductDefinitionEffectivity() = default;

void StepBasic_ProductDefinitionEffectivity::Init(
  const occ::handle<TCollection_HAsciiString>&                aId,
  const occ::handle<StepBasic_ProductDefinitionRelationship>& aUsage)
{
  SetId(aId);
  theUsage = aUsage;
}

occ::handle<StepBasic_ProductDefinitionRelationship> StepBasic_ProductDefinitionEffectivity::Usage()
  const
{
  return theUsage;
}

void StepBasic_ProductDefinitionEffectivity::SetUsage(
  const occ::handle<StepBasic_ProductDefinitionRelationship>& aUsage)
{
  theUsage = aUsage;
}
