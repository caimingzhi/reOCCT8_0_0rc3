#pragma once


#include <Standard.hpp>

#include <StepFEA_SymmetricTensor42d.hpp>
#include <StepFEA_FeaMaterialPropertyRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity FeaShellBendingStiffness
class StepFEA_FeaShellBendingStiffness : public StepFEA_FeaMaterialPropertyRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaShellBendingStiffness();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const StepFEA_SymmetricTensor42d&            aFeaConstants);

  //! Returns field FeaConstants
  Standard_EXPORT StepFEA_SymmetricTensor42d FeaConstants() const;

  //! Set field FeaConstants
  Standard_EXPORT void SetFeaConstants(const StepFEA_SymmetricTensor42d& FeaConstants);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaShellBendingStiffness,
                          StepFEA_FeaMaterialPropertyRepresentationItem)

private:
  StepFEA_SymmetricTensor42d theFeaConstants;
};

