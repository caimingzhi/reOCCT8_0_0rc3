#pragma once

#include <Standard.hpp>

#include <StepDimTol_GeneralDatumReference.hpp>

//! Representation of STEP entity DatumReferenceCompartment
class StepDimTol_DatumReferenceCompartment : public StepDimTol_GeneralDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_DatumReferenceCompartment();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumReferenceCompartment, StepDimTol_GeneralDatumReference)
};
