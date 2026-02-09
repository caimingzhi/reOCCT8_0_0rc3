#include <StepFEA_FeaAreaDensity.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaAreaDensity, StepFEA_FeaMaterialPropertyRepresentationItem)

StepFEA_FeaAreaDensity::StepFEA_FeaAreaDensity() = default;

void StepFEA_FeaAreaDensity::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const double                                 aFeaConstant)
{
  StepFEA_FeaMaterialPropertyRepresentationItem::Init(aRepresentationItem_Name);

  theFeaConstant = aFeaConstant;
}

double StepFEA_FeaAreaDensity::FeaConstant() const
{
  return theFeaConstant;
}

void StepFEA_FeaAreaDensity::SetFeaConstant(const double aFeaConstant)
{
  theFeaConstant = aFeaConstant;
}
