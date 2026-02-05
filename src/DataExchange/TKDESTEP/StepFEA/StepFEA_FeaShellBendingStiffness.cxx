#include <StepFEA_FeaShellBendingStiffness.hpp>
#include <StepFEA_SymmetricTensor42d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaShellBendingStiffness,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

//=================================================================================================

StepFEA_FeaShellBendingStiffness::StepFEA_FeaShellBendingStiffness() = default;

//=================================================================================================

void StepFEA_FeaShellBendingStiffness::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor42d&            aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

//=================================================================================================

StepFEA_SymmetricTensor42d StepFEA_FeaShellBendingStiffness::FeaConstants() const
{
  return theFeaConstants;
}

//=================================================================================================

void StepFEA_FeaShellBendingStiffness::SetFeaConstants(
  const StepFEA_SymmetricTensor42d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
