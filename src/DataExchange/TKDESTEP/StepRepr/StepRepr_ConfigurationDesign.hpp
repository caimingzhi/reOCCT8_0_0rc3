#pragma once

#include <Standard.hpp>

#include <StepRepr_ConfigurationDesignItem.hpp>
#include <Standard_Transient.hpp>
class StepRepr_ConfigurationItem;

//! Representation of STEP entity ConfigurationDesign
class StepRepr_ConfigurationDesign : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_ConfigurationDesign();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepRepr_ConfigurationItem>& aConfiguration,
                            const StepRepr_ConfigurationDesignItem&        aDesign);

  //! Returns field Configuration
  Standard_EXPORT occ::handle<StepRepr_ConfigurationItem> Configuration() const;

  //! Set field Configuration
  Standard_EXPORT void SetConfiguration(
    const occ::handle<StepRepr_ConfigurationItem>& Configuration);

  //! Returns field Design
  Standard_EXPORT StepRepr_ConfigurationDesignItem Design() const;

  //! Set field Design
  Standard_EXPORT void SetDesign(const StepRepr_ConfigurationDesignItem& Design);

  DEFINE_STANDARD_RTTIEXT(StepRepr_ConfigurationDesign, Standard_Transient)

private:
  occ::handle<StepRepr_ConfigurationItem> theConfiguration;
  StepRepr_ConfigurationDesignItem        theDesign;
};
