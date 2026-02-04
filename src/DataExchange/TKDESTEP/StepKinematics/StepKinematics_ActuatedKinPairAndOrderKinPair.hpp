#pragma once


#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepKinematics_KinematicPair.hpp>
class StepRepr_RepresentationItem;
class StepKinematics_ActuatedKinematicPair;

//! Representation of STEP entity ActuatedKinPairAndOrderKinPair
class StepKinematics_ActuatedKinPairAndOrderKinPair : public StepKinematics_KinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_ActuatedKinPairAndOrderKinPair();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theJoint,
    const occ::handle<StepKinematics_ActuatedKinematicPair>& theActuatedKinematicPair,
    const occ::handle<StepKinematics_KinematicPair>&         theOrderKinematicPair);

  inline void SetActuatedKinematicPair(const occ::handle<StepKinematics_ActuatedKinematicPair>& aKP)
  {
    myActuatedKinematicPair = aKP;
  }

  inline occ::handle<StepKinematics_ActuatedKinematicPair> GetActuatedKinematicPair() const
  {
    return myActuatedKinematicPair;
  }

  inline void SetOrderKinematicPair(const occ::handle<StepKinematics_KinematicPair>& aKP)
  {
    myOrderKinematicPair = aKP;
  }

  inline occ::handle<StepKinematics_KinematicPair> GetOrderKinematicPair() const
  {
    return myOrderKinematicPair;
  }

  DEFINE_STANDARD_RTTIEXT(StepKinematics_ActuatedKinPairAndOrderKinPair,
                          StepKinematics_KinematicPair)

private:
  occ::handle<StepKinematics_ActuatedKinematicPair> myActuatedKinematicPair;
  occ::handle<StepKinematics_KinematicPair>         myOrderKinematicPair;
};
