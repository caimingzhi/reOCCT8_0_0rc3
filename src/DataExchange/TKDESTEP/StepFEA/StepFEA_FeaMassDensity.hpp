#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepFEA_FeaMassDensity : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  Standard_EXPORT StepFEA_FeaMassDensity();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const double                                 aFeaConstant);

  Standard_EXPORT double FeaConstant() const;

  Standard_EXPORT void SetFeaConstant(const double FeaConstant);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaMassDensity, StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  double theFeaConstant;
};
