#pragma once

#include <Standard.hpp>

#include <StepFEA_FeaModel.hpp>

//! Representation of STEP entity FeaModel3d
class StepFEA_FeaModel3d : public StepFEA_FeaModel
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaModel3d();

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaModel3d, StepFEA_FeaModel)
};
