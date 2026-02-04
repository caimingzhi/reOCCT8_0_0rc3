#pragma once


#include <Standard.hpp>

#include <StepAP242_ItemIdentifiedRepresentationUsage.hpp>

//! Added for Dimensional Tolerances
class StepAP242_GeometricItemSpecificUsage : public StepAP242_ItemIdentifiedRepresentationUsage
{

public:
  Standard_EXPORT StepAP242_GeometricItemSpecificUsage();

  DEFINE_STANDARD_RTTIEXT(StepAP242_GeometricItemSpecificUsage,
                          StepAP242_ItemIdentifiedRepresentationUsage)
};
