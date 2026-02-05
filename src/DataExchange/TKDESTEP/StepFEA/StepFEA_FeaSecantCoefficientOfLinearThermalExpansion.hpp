#pragma once

#include <Standard.hpp>

#include <StepFEA_SymmetricTensor23d.hpp>
#include <Standard_Real.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity FeaSecantCoefficientOfLinearThermalExpansion
class StepFEA_FeaSecantCoefficientOfLinearThermalExpansion
    : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaSecantCoefficientOfLinearThermalExpansion();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor23d&            aFeaConstants,
                            const double                                 aReferenceTemperature);

  //! Returns field FeaConstants
  Standard_EXPORT StepFEA_SymmetricTensor23d FeaConstants() const;

  //! Set field FeaConstants
  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor23d& FeaConstants);

  //! Returns field ReferenceTemperature
  Standard_EXPORT double ReferenceTemperature() const;

  //! Set field ReferenceTemperature
  Standard_EXPORT void SetReferenceTemperature(const double ReferenceTemperature);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaSecantCoefficientOfLinearThermalExpansion,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor23d theFeaConstants;
  double                     theReferenceTemperature;
};
