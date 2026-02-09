#include <StepFEA_FeaShellShearStiffness.hpp>
#include <StepFEA_SymmetricTensor22d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaShellShearStiffness,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

StepFEA_FeaShellShearStiffness::StepFEA_FeaShellShearStiffness() = default;

void StepFEA_FeaShellShearStiffness::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor22d&            aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

StepFEA_SymmetricTensor22d StepFEA_FeaShellShearStiffness::FeaConstants() const
{
  return theFeaConstants;
}

void StepFEA_FeaShellShearStiffness::SetFeaConstants(
  const StepFEA_SymmetricTensor22d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
