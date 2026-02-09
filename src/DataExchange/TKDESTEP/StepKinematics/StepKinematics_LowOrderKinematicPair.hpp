#pragma once

#include <Standard.hpp>
#include <StepKinematics_KinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>

class StepKinematics_LowOrderKinematicPair : public StepKinematics_KinematicPair
{
public:
  Standard_EXPORT StepKinematics_LowOrderKinematicPair();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const bool                                        theTX,
    const bool                                        theTY,
    const bool                                        theTZ,
    const bool                                        theRX,
    const bool                                        theRY,
    const bool                                        theRZ);

  Standard_EXPORT bool TX() const;

  Standard_EXPORT void SetTX(const bool theTX);

  Standard_EXPORT bool TY() const;

  Standard_EXPORT void SetTY(const bool theTY);

  Standard_EXPORT bool TZ() const;

  Standard_EXPORT void SetTZ(const bool theTZ);

  Standard_EXPORT bool RX() const;

  Standard_EXPORT void SetRX(const bool theRX);

  Standard_EXPORT bool RY() const;

  Standard_EXPORT void SetRY(const bool theRY);

  Standard_EXPORT bool RZ() const;

  Standard_EXPORT void SetRZ(const bool theRZ);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_LowOrderKinematicPair, StepKinematics_KinematicPair)

private:
  bool myTX;
  bool myTY;
  bool myTZ;
  bool myRX;
  bool myRY;
  bool myRZ;
};
