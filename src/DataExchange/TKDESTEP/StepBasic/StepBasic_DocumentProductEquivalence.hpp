#pragma once


#include <Standard.hpp>

#include <StepBasic_DocumentProductAssociation.hpp>

//! Representation of STEP entity DocumentProductEquivalence
class StepBasic_DocumentProductEquivalence : public StepBasic_DocumentProductAssociation
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_DocumentProductEquivalence();

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentProductEquivalence,
                          StepBasic_DocumentProductAssociation)
};

