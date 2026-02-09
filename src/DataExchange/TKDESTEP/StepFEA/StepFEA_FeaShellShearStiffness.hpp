#pragma once

#include <Standard.hpp>

#include <StepFEA_SymmetricTensor22d.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepFEA_FeaShellShearStiffness : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  Standard_EXPORT StepFEA_FeaShellShearStiffness();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor22d&            aFeaConstants);

  Standard_EXPORT StepFEA_SymmetricTensor22d FeaConstants() const;

  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor22d& FeaConstants);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaShellShearStiffness,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor22d theFeaConstants;
};
