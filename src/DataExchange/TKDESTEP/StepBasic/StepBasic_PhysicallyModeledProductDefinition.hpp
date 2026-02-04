#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductDefinition.hpp>

class StepBasic_PhysicallyModeledProductDefinition : public StepBasic_ProductDefinition
{

public:
  Standard_EXPORT StepBasic_PhysicallyModeledProductDefinition();

  DEFINE_STANDARD_RTTIEXT(StepBasic_PhysicallyModeledProductDefinition, StepBasic_ProductDefinition)
};

