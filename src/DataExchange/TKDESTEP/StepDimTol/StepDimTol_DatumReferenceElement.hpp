#pragma once


#include <Standard.hpp>
#include <Standard_Macro.hpp>

#include <StepDimTol_GeneralDatumReference.hpp>

//! Representation of STEP entity DatumReferenceElement
class StepDimTol_DatumReferenceElement : public StepDimTol_GeneralDatumReference
{

public:
  //! Empty constructor
  Standard_EXPORT StepDimTol_DatumReferenceElement();

  DEFINE_STANDARD_RTTIEXT(StepDimTol_DatumReferenceElement, StepDimTol_GeneralDatumReference)
};
