#pragma once

#include <Standard.hpp>

#include <StepRepr_ConfigurationDesignItem.hpp>
#include <Standard_Transient.hpp>
class StepRepr_ConfigurationItem;

class StepRepr_ConfigurationDesign : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_ConfigurationDesign();

  Standard_EXPORT void Init(const occ::handle<StepRepr_ConfigurationItem>& aConfiguration,
                            const StepRepr_ConfigurationDesignItem&        aDesign);

  Standard_EXPORT occ::handle<StepRepr_ConfigurationItem> Configuration() const;

  Standard_EXPORT void SetConfiguration(
    const occ::handle<StepRepr_ConfigurationItem>& Configuration);

  Standard_EXPORT StepRepr_ConfigurationDesignItem Design() const;

  Standard_EXPORT void SetDesign(const StepRepr_ConfigurationDesignItem& Design);

  DEFINE_STANDARD_RTTIEXT(StepRepr_ConfigurationDesign, Standard_Transient)

private:
  occ::handle<StepRepr_ConfigurationItem> theConfiguration;
  StepRepr_ConfigurationDesignItem        theDesign;
};
