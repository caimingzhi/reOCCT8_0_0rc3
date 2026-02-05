#include <StepFEA_FeaShellMembraneStiffness.hpp>
#include <StepFEA_SymmetricTensor42d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaShellMembraneStiffness,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

//=================================================================================================

StepFEA_FeaShellMembraneStiffness::StepFEA_FeaShellMembraneStiffness() = default;

//=================================================================================================

void StepFEA_FeaShellMembraneStiffness::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor42d&            aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

//=================================================================================================

StepFEA_SymmetricTensor42d StepFEA_FeaShellMembraneStiffness::FeaConstants() const
{
  return theFeaConstants;
}

//=================================================================================================

void StepFEA_FeaShellMembraneStiffness::SetFeaConstants(
  const StepFEA_SymmetricTensor42d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
