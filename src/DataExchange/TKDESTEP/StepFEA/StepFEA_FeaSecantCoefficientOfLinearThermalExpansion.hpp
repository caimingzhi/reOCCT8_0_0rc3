#pragma once

#include <Standard.hpp>

#include <StepFEA_SymmetricTensor23d.hpp>
#include <Standard_Real.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepFEA_FeaSecantCoefficientOfLinearThermalExpansion
    : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  Standard_EXPORT StepFEA_FeaSecantCoefficientOfLinearThermalExpansion();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor23d&            aFeaConstants,
                            const double                                 aReferenceTemperature);

  Standard_EXPORT StepFEA_SymmetricTensor23d FeaConstants() const;

  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor23d& FeaConstants);

  Standard_EXPORT double ReferenceTemperature() const;

  Standard_EXPORT void SetReferenceTemperature(const double ReferenceTemperature);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaSecantCoefficientOfLinearThermalExpansion,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor23d theFeaConstants;
  double                     theReferenceTemperature;
};
