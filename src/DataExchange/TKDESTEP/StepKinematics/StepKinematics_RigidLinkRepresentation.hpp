#pragma once


#include <Standard.hpp>
#include <StepKinematics_KinematicLinkRepresentation.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//! Representation of STEP entity RigidLinkRepresentation
class StepKinematics_RigidLinkRepresentation : public StepKinematics_KinematicLinkRepresentation
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_RigidLinkRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_RigidLinkRepresentation,
                          StepKinematics_KinematicLinkRepresentation)
};
