#pragma once


#include <Standard.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>

#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepKinematics_KinematicJoint.hpp>

//! Representation of STEP entity KinematicPair
class StepKinematics_KinematicPair : public StepGeom_GeometricRepresentationItem
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_KinematicPair();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theJoint);

  //! Returns data for supertype ItemDefinedTransformation
  Standard_EXPORT occ::handle<StepRepr_ItemDefinedTransformation> ItemDefinedTransformation() const;
  //! Sets data for supertype ItemDefinedTransformation
  Standard_EXPORT void SetItemDefinedTransformation(
    const occ::handle<StepRepr_ItemDefinedTransformation>& theItemDefinedTransformation);

  //! Returns field Joint
  Standard_EXPORT occ::handle<StepKinematics_KinematicJoint> Joint() const;
  //! Sets field Joint
  Standard_EXPORT void SetJoint(const occ::handle<StepKinematics_KinematicJoint>& theJoint);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicPair, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepRepr_ItemDefinedTransformation> myItemDefinedTransformation; //!< supertype
  occ::handle<StepKinematics_KinematicJoint>      myJoint;
};
