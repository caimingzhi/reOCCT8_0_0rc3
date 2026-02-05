#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductDefinitionEffectivity.hpp>
class StepRepr_ConfigurationDesign;
class TCollection_HAsciiString;
class StepBasic_ProductDefinitionRelationship;

//! Representation of STEP entity ConfigurationEffectivity
class StepRepr_ConfigurationEffectivity : public StepBasic_ProductDefinitionEffectivity
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_ConfigurationEffectivity();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                aEffectivity_Id,
    const occ::handle<StepBasic_ProductDefinitionRelationship>& aProductDefinitionEffectivity_Usage,
    const occ::handle<StepRepr_ConfigurationDesign>&            aConfiguration);

  //! Returns field Configuration
  Standard_EXPORT occ::handle<StepRepr_ConfigurationDesign> Configuration() const;

  //! Set field Configuration
  Standard_EXPORT void SetConfiguration(
    const occ::handle<StepRepr_ConfigurationDesign>& Configuration);

  DEFINE_STANDARD_RTTIEXT(StepRepr_ConfigurationEffectivity, StepBasic_ProductDefinitionEffectivity)

private:
  occ::handle<StepRepr_ConfigurationDesign> theConfiguration;
};
