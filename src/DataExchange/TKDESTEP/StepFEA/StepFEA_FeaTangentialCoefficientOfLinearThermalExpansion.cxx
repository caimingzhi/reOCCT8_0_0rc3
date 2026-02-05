#include <StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion.hpp>
#include <StepFEA_SymmetricTensor23d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

//=================================================================================================

StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::
  StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion() = default;

//=================================================================================================

void StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor23d&            aFeaConstants)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;
}

//=================================================================================================

StepFEA_SymmetricTensor23d StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::FeaConstants()
  const
{
  return theFeaConstants;
}

//=================================================================================================

void StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion::SetFeaConstants(
  const StepFEA_SymmetricTensor23d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}
