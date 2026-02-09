#pragma once

#include <Standard.hpp>
#include <StepRepr_RepresentationRelationship.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationOrRepresentationReference.hpp>

class StepKinematics_KinematicLinkRepresentationAssociation
    : public StepRepr_RepresentationRelationship
{
public:
  Standard_EXPORT StepKinematics_KinematicLinkRepresentationAssociation();

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicLinkRepresentationAssociation,
                          StepRepr_RepresentationRelationship)
};
