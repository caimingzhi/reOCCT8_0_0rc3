#pragma once

#include <Standard.hpp>
#include <StepKinematics_RackAndPinionPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity RackAndPinionPairWithRange
class StepKinematics_RackAndPinionPairWithRange : public StepKinematics_RackAndPinionPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RackAndPinionPairWithRange();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const double                                      theRackAndPinionPair_PinionRadius,
    const bool                                        hasLowerLimitRackDisplacement,
    const double                                      theLowerLimitRackDisplacement,
    const bool                                        hasUpperLimitRackDisplacement,
    const double                                      theUpperLimitRackDisplacement);

  //! Returns field LowerLimitRackDisplacement
  Standard_EXPORT double LowerLimitRackDisplacement() const;
  //! Sets field LowerLimitRackDisplacement
  Standard_EXPORT void SetLowerLimitRackDisplacement(const double theLowerLimitRackDisplacement);
  //! Returns True if optional field LowerLimitRackDisplacement is defined
  Standard_EXPORT bool HasLowerLimitRackDisplacement() const;

  //! Returns field UpperLimitRackDisplacement
  Standard_EXPORT double UpperLimitRackDisplacement() const;
  //! Sets field UpperLimitRackDisplacement
  Standard_EXPORT void SetUpperLimitRackDisplacement(const double theUpperLimitRackDisplacement);
  //! Returns True if optional field UpperLimitRackDisplacement is defined
  Standard_EXPORT bool HasUpperLimitRackDisplacement() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RackAndPinionPairWithRange,
                          StepKinematics_RackAndPinionPair)

private:
  double myLowerLimitRackDisplacement; //!< optional
  double myUpperLimitRackDisplacement; //!< optional
  // clang-format off
  bool defLowerLimitRackDisplacement; //!< flag "is LowerLimitRackDisplacement defined"
  bool defUpperLimitRackDisplacement; //!< flag "is UpperLimitRackDisplacement defined"
  // clang-format on
};
