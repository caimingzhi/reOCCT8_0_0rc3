#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity FeaAreaDensity
class StepFEA_FeaAreaDensity : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaAreaDensity();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const double                                 aFeaConstant);

  //! Returns field FeaConstant
  Standard_EXPORT double FeaConstant() const;

  //! Set field FeaConstant
  Standard_EXPORT void SetFeaConstant(const double FeaConstant);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaAreaDensity, StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  double theFeaConstant;
};

