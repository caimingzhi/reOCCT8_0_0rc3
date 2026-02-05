// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_KinematicLinkRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_KinematicLinkRepresentation, StepRepr_Representation)

//=================================================================================================

StepKinematics_KinematicLinkRepresentation::StepKinematics_KinematicLinkRepresentation() = default;

//=================================================================================================

void StepKinematics_KinematicLinkRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                     theRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>& theRepresentation_ContextOfItems,
  const occ::handle<StepKinematics_KinematicLink>&   theRepresentedLink)
{
  StepRepr_Representation::Init(theRepresentation_Name,
                                theRepresentation_Items,
                                theRepresentation_ContextOfItems);

  myRepresentedLink = theRepresentedLink;
}

//=================================================================================================

occ::handle<StepKinematics_KinematicLink> StepKinematics_KinematicLinkRepresentation::
  RepresentedLink() const
{
  return myRepresentedLink;
}

//=================================================================================================

void StepKinematics_KinematicLinkRepresentation::SetRepresentedLink(
  const occ::handle<StepKinematics_KinematicLink>& theRepresentedLink)
{
  myRepresentedLink = theRepresentedLink;
}
