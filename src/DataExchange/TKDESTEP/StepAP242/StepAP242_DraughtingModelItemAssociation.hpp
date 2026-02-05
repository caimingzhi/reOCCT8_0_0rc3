#pragma once

#include <Standard.hpp>

#include <StepAP242_ItemIdentifiedRepresentationUsage.hpp>

//! Added for Dimensional Tolerances
class StepAP242_DraughtingModelItemAssociation : public StepAP242_ItemIdentifiedRepresentationUsage
{

public:
  Standard_EXPORT StepAP242_DraughtingModelItemAssociation();

  DEFINE_STANDARD_RTTIEXT(StepAP242_DraughtingModelItemAssociation,
                          StepAP242_ItemIdentifiedRepresentationUsage)
};
