#include <StepFEA_FeaMassDensity.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaMassDensity, StepFEA_FeaMaterialPropertyRepresentationItem)

//=================================================================================================

StepFEA_FeaMassDensity::StepFEA_FeaMassDensity() = default;

//=================================================================================================

void StepFEA_FeaMassDensity::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const double                                 aFeaConstant)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstant = aFeaConstant;
}

//=================================================================================================

double StepFEA_FeaMassDensity::FeaConstant() const
{
  return theFeaConstant;
}

//=================================================================================================

void StepFEA_FeaMassDensity::SetFeaConstant(const double aFeaConstant)
{
  theFeaConstant = aFeaConstant;
}
