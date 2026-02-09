#pragma once

#include <Standard.hpp>

#include <StepBasic_DocumentProductAssociation.hpp>

class StepBasic_DocumentProductEquivalence : public StepBasic_DocumentProductAssociation
{

public:
  Standard_EXPORT StepBasic_DocumentProductEquivalence();

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentProductEquivalence,
                          StepBasic_DocumentProductAssociation)
};
