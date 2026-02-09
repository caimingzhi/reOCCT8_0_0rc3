#pragma once

#include <Standard.hpp>
#include <StepKinematics_KinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepKinematics_ActuatedDirection.hpp>

class StepKinematics_ActuatedKinematicPair : public StepKinematics_KinematicPair
{
public:
  Standard_EXPORT StepKinematics_ActuatedKinematicPair();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const bool                                        hasTX,
    const StepKinematics_ActuatedDirection            theTX,
    const bool                                        hasTY,
    const StepKinematics_ActuatedDirection            theTY,
    const bool                                        hasTZ,
    const StepKinematics_ActuatedDirection            theTZ,
    const bool                                        hasRX,
    const StepKinematics_ActuatedDirection            theRX,
    const bool                                        hasRY,
    const StepKinematics_ActuatedDirection            theRY,
    const bool                                        hasRZ,
    const StepKinematics_ActuatedDirection            theRZ);

  Standard_EXPORT StepKinematics_ActuatedDirection TX() const;

  Standard_EXPORT void SetTX(const StepKinematics_ActuatedDirection theTX);

  Standard_EXPORT bool HasTX() const;

  Standard_EXPORT StepKinematics_ActuatedDirection TY() const;

  Standard_EXPORT void SetTY(const StepKinematics_ActuatedDirection theTY);

  Standard_EXPORT bool HasTY() const;

  Standard_EXPORT StepKinematics_ActuatedDirection TZ() const;

  Standard_EXPORT void SetTZ(const StepKinematics_ActuatedDirection theTZ);

  Standard_EXPORT bool HasTZ() const;

  Standard_EXPORT StepKinematics_ActuatedDirection RX() const;

  Standard_EXPORT void SetRX(const StepKinematics_ActuatedDirection theRX);

  Standard_EXPORT bool HasRX() const;

  Standard_EXPORT StepKinematics_ActuatedDirection RY() const;

  Standard_EXPORT void SetRY(const StepKinematics_ActuatedDirection theRY);

  Standard_EXPORT bool HasRY() const;

  Standard_EXPORT StepKinematics_ActuatedDirection RZ() const;

  Standard_EXPORT void SetRZ(const StepKinematics_ActuatedDirection theRZ);

  Standard_EXPORT bool HasRZ() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ActuatedKinematicPair, StepKinematics_KinematicPair)

private:
  StepKinematics_ActuatedDirection myTX;
  StepKinematics_ActuatedDirection myTY;
  StepKinematics_ActuatedDirection myTZ;
  StepKinematics_ActuatedDirection myRX;
  StepKinematics_ActuatedDirection myRY;
  StepKinematics_ActuatedDirection myRZ;
  bool                             defTX;
  bool                             defTY;
  bool                             defTZ;
  bool                             defRX;
  bool                             defRY;
  bool                             defRZ;
};
