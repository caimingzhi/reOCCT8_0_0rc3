#pragma once

#include <Standard.hpp>

#include <StepFEA_SymmetricTensor23d.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity FeaTangentialCoefficientOfLinearThermalExpansion
class StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion
    : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor23d&            aFeaConstants);

  //! Returns field FeaConstants
  Standard_EXPORT StepFEA_SymmetricTensor23d FeaConstants() const;

  //! Set field FeaConstants
  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor23d& FeaConstants);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor23d theFeaConstants;
};
