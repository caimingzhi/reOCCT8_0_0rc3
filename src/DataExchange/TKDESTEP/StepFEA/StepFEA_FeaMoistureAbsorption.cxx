#include <StepFEA_FeaMoistureAbsorption.hpp>
#include <StepFEA_SymmetricTensor23d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaMoistureAbsorption,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

//=================================================================================================

StepFEA_FeaMoistureAbsorption::StepFEA_FeaMoistureAbsorption() = default;

//=================================================================================================

void StepFEA_FeaMoistureAbsorption::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor23d&            aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

//=================================================================================================

StepFEA_SymmetricTensor23d StepFEA_FeaMoistureAbsorption::FeaConstants() const
{
  return theFeaConstants;
}

//=================================================================================================

void StepFEA_FeaMoistureAbsorption::SetFeaConstants(const StepFEA_SymmetricTensor23d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
