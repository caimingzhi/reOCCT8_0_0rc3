#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductRelatedProductCategory.hpp>

class StepBasic_ProductType : public StepBasic_ProductRelatedProductCategory
{

public:
  Standard_EXPORT StepBasic_ProductType();

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductType, StepBasic_ProductRelatedProductCategory)
};
