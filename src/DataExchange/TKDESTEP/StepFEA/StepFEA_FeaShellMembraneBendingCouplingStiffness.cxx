#include <StepFEA_FeaShellMembraneBendingCouplingStiffness.hpp>
#include <StepFEA_SymmetricTensor42d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaShellMembraneBendingCouplingStiffness,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

StepFEA_FeaShellMembraneBendingCouplingStiffness::
  StepFEA_FeaShellMembraneBendingCouplingStiffness() = default;

void StepFEA_FeaShellMembraneBendingCouplingStiffness::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor42d&            aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

StepFEA_SymmetricTensor42d StepFEA_FeaShellMembraneBendingCouplingStiffness::FeaConstants() const
{
  return theFeaConstants;
}

void StepFEA_FeaShellMembraneBendingCouplingStiffness::SetFeaConstants(
  const StepFEA_SymmetricTensor42d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
