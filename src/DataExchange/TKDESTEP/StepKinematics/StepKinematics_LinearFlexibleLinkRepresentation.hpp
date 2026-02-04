#pragma once


#include <Standard.hpp>
#include <StepKinematics_KinematicLinkRepresentation.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//! Representation of STEP entity LinearFlexibleLinkRepresentation
class StepKinematics_LinearFlexibleLinkRepresentation
    : public StepKinematics_KinematicLinkRepresentation
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_LinearFlexibleLinkRepresentation();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_LinearFlexibleLinkRepresentation,
                          StepKinematics_KinematicLinkRepresentation)
};
