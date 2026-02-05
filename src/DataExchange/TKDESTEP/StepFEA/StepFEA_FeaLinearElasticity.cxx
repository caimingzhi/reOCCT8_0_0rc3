#include <StepFEA_FeaLinearElasticity.hpp>
#include <StepFEA_SymmetricTensor43d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaLinearElasticity,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

//=================================================================================================

StepFEA_FeaLinearElasticity::StepFEA_FeaLinearElasticity() = default;

//=================================================================================================

void StepFEA_FeaLinearElasticity::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor43d&            aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

//=================================================================================================

StepFEA_SymmetricTensor43d StepFEA_FeaLinearElasticity::FeaConstants() const
{
  return theFeaConstants;
}

//=================================================================================================

void StepFEA_FeaLinearElasticity::SetFeaConstants(const StepFEA_SymmetricTensor43d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
