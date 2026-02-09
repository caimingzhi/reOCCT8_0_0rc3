#pragma once

#include <Standard.hpp>

#include <StepFEA_SymmetricTensor43d.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepFEA_FeaLinearElasticity : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  Standard_EXPORT StepFEA_FeaLinearElasticity();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor43d&            aFeaConstants);

  Standard_EXPORT StepFEA_SymmetricTensor43d FeaConstants() const;

  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor43d& FeaConstants);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaLinearElasticity,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor43d theFeaConstants;
};
