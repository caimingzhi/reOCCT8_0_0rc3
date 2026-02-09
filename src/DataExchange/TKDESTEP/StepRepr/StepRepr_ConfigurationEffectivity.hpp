#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductDefinitionEffectivity.hpp>
class StepRepr_ConfigurationDesign;
class TCollection_HAsciiString;
class StepBasic_ProductDefinitionRelationship;

class StepRepr_ConfigurationEffectivity : public StepBasic_ProductDefinitionEffectivity
{

public:
  Standard_EXPORT StepRepr_ConfigurationEffectivity();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                aEffectivity_Id,
    const occ::handle<StepBasic_ProductDefinitionRelationship>& aProductDefinitionEffectivity_Usage,
    const occ::handle<StepRepr_ConfigurationDesign>&            aConfiguration);

  Standard_EXPORT occ::handle<StepRepr_ConfigurationDesign> Configuration() const;

  Standard_EXPORT void SetConfiguration(
    const occ::handle<StepRepr_ConfigurationDesign>& Configuration);

  DEFINE_STANDARD_RTTIEXT(StepRepr_ConfigurationEffectivity, StepBasic_ProductDefinitionEffectivity)

private:
  occ::handle<StepRepr_ConfigurationDesign> theConfiguration;
};
