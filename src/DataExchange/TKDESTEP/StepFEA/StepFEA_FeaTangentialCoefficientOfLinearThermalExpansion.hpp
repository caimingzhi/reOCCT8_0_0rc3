#pragma once

#include <Standard.hpp>

#include <StepFEA_SymmetricTensor23d.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion
    : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  Standard_EXPORT StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor23d&            aFeaConstants);

  Standard_EXPORT StepFEA_SymmetricTensor23d FeaConstants() const;

  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor23d& FeaConstants);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor23d theFeaConstants;
};
