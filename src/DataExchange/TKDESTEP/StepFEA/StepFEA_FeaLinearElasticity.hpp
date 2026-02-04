#pragma once


#include <Standard.hpp>

#include <StepFEA_SymmetricTensor43d.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity FeaLinearElasticity
class StepFEA_FeaLinearElasticity : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaLinearElasticity();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor43d&            aFeaConstants);

  //! Returns field FeaConstants
  Standard_EXPORT StepFEA_SymmetricTensor43d FeaConstants() const;

  //! Set field FeaConstants
  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor43d& FeaConstants);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaLinearElasticity,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor43d theFeaConstants;
};

