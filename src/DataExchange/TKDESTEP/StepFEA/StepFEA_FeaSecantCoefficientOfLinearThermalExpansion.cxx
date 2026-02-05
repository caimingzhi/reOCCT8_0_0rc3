#include <StepFEA_FeaSecantCoefficientOfLinearThermalExpansion.hpp>
#include <StepFEA_SymmetricTensor23d.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaSecantCoefficientOfLinearThermalExpansion,
                           StepFEA_FeaMaterialPropertyRepresentationItem)

//=================================================================================================

StepFEA_FeaSecantCoefficientOfLinearThermalExpansion::
  StepFEA_FeaSecantCoefficientOfLinearThermalExpansion() = default;

//=================================================================================================

void StepFEA_FeaSecantCoefficientOfLinearThermalExpansion::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const StepFEA_SymmetricTensor23d&            aFeaConstants,
  const double                                 aReferenceTemperature)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstants = aFeaConstants;

  theReferenceTemperature = aReferenceTemperature;
}

//=================================================================================================

StepFEA_SymmetricTensor23d StepFEA_FeaSecantCoefficientOfLinearThermalExpansion::FeaConstants()
  const
{
  return theFeaConstants;
}

//=================================================================================================

void StepFEA_FeaSecantCoefficientOfLinearThermalExpansion::SetFeaConstants(
  const StepFEA_SymmetricTensor23d& aFeaConstants)
{
  theFeaConstants = aFeaConstants;
}

//=================================================================================================

double StepFEA_FeaSecantCoefficientOfLinearThermalExpansion::ReferenceTemperature() const
{
  return theReferenceTemperature;
}

//=================================================================================================

void StepFEA_FeaSecantCoefficientOfLinearThermalExpansion::SetReferenceTemperature(
  const double aReferenceTemperature)
{
  theReferenceTemperature = aReferenceTemperature;
}
