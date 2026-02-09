#pragma once

#include <Standard.hpp>
#include <StepRepr_Representation.hpp>

#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepKinematics_KinematicLink.hpp>

class StepKinematics_KinematicLinkRepresentation : public StepRepr_Representation
{
public:
  Standard_EXPORT StepKinematics_KinematicLinkRepresentation();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                       theRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>& theRepresentation_ContextOfItems,
    const occ::handle<StepKinematics_KinematicLink>&   theRepresentedLink);

  Standard_EXPORT occ::handle<StepKinematics_KinematicLink> RepresentedLink() const;

  Standard_EXPORT void SetRepresentedLink(
    const occ::handle<StepKinematics_KinematicLink>& theRepresentedLink);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_KinematicLinkRepresentation, StepRepr_Representation)

private:
  occ::handle<StepKinematics_KinematicLink> myRepresentedLink;
};
